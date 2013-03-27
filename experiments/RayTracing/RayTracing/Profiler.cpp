#include "Profiler.h"
#ifdef _PROFILE
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ctime>
#include <atlstr.h>
using namespace std;

typedef struct 
{
	bool bValid;							//Whether this data is valid
	unsigned int iProfileInstances;			//# of times ProfileBegin called
	int iOpenProfiles;						//# of times ProfileBegin w/o ProfileEnd
	char szName[256];						//Name of sample
	float fStartTime;						//The current open profile start time
	float fAccumulator;						//All samples this frame added together
	float fChildrenSampleTime;				//Time taken by all children
	float fMaxTime;
	float fMinTime;
	unsigned int iNumParents;				//Number of profile parents
} ProfileSample;

#define NUM_PROFILE_SAMPLES 50
ProfileSample g_samples[NUM_PROFILE_SAMPLES];
float g_startProfile = 0.0f;
float g_endProfile = 0.0f;
LARGE_INTEGER g_QPFrequency;

float GetExactTime()
{
	LARGE_INTEGER tickCounter;
	QueryPerformanceCounter(&tickCounter);
	return (float)(tickCounter.QuadPart * 1000)/g_QPFrequency.QuadPart;
}


void ProfileInit()
{
	unsigned int i;

	for( i=0; i<NUM_PROFILE_SAMPLES; i++ ) {
		g_samples[i].bValid = false;
		//g_history[i].bValid = false;
	}

	QueryPerformanceFrequency(&g_QPFrequency);

	g_startProfile = GetExactTime();
}




void ProfileBegin(const char* name)
{
	unsigned int i = 0;

	while( i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true ) {
		if( strcmp( g_samples[i].szName, name ) == 0 ) {
			//Found the sample
			g_samples[i].iOpenProfiles++;
			g_samples[i].iProfileInstances++;
			g_samples[i].fStartTime = GetExactTime();
			assert( g_samples[i].iOpenProfiles == 1 ); //max 1 open at once
			return;
		}
		i++;	
	}

	if( i >= NUM_PROFILE_SAMPLES ) {
		assert( !"Exceeded Max Available Profile Samples" );
		return;
	}

	strcpy( g_samples[i].szName, name );
	g_samples[i].bValid = true;
	g_samples[i].iOpenProfiles = 1;
	g_samples[i].iProfileInstances = 1;
	g_samples[i].fAccumulator = 0.0f;
	g_samples[i].fStartTime = GetExactTime();
	g_samples[i].fChildrenSampleTime = 0.0f;
	g_samples[i].fMaxTime = 0.0f;
	g_samples[i].fMinTime = 100000000.0f;
}


void ProfileEnd(const char* name)
{
	unsigned int i = 0;
	unsigned int numParents = 0;

	while( i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true )
	{
		if( strcmp( g_samples[i].szName, name ) == 0 )
		{  //Found the sample
			unsigned int inner = 0;
			int parent = -1;
			float fEndTime = GetExactTime();
			g_samples[i].iOpenProfiles--;

			//Count all parents and find the immediate parent
			while( g_samples[inner].bValid == true ) {
				if( g_samples[inner].iOpenProfiles > 0 )
				{  //Found a parent (any open profiles are parents)
					numParents++;
					if( parent < 0 )
					{  //Replace invalid parent (index)
						parent = inner;
					}
					else if( g_samples[inner].fStartTime >=
						g_samples[parent].fStartTime )
					{  //Replace with more immediate parent
						parent = inner;
					}
				}
				inner++;
			}

			//Remember the current number of parents of the sample
			g_samples[i].iNumParents = numParents;

			float fElapsedTime = fEndTime - g_samples[i].fStartTime;
			if( parent >= 0 )
			{  //Record this time in fChildrenSampleTime (add it in)
				g_samples[parent].fChildrenSampleTime += fElapsedTime;
			}

			//Save sample time in accumulator
			g_samples[i].fAccumulator += fElapsedTime;
			if(fElapsedTime < g_samples[i].fMinTime) g_samples[i].fMinTime = fElapsedTime;
			if(fElapsedTime > g_samples[i].fMaxTime) g_samples[i].fMaxTime = fElapsedTime;
			return;
		}
		i++;	
	}
}

string GetCurTimeStr()
{
	struct tm* pt;
	time_t t;
	time(&t);
	pt = localtime(&t);
	char sResult[MAX_PATH] ;
	sprintf(sResult, "%d-%d-%d-%d-%d-%d", pt->tm_year+1900,pt->tm_mon, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
	return sResult;
}

//const char* ReportDir = "C:\\RayTracing\\Report\\";
void ProfileDumpOutputToBuffer(const char* filename)
{
	unsigned int i = 0;

	ofstream  streamProfile;
	string strReport;
	if (!filename) 
	{
		//TCHAR szCurDir[256];
		//GetModuleFileName(NULL, szCurDir, 256);

		//CString strReport(szCurDir);
		//int pos = strReport.ReverseFind(_T('\\'));
		//strReport = strReport.Left(pos+1);

		strReport = "C:\\";
		strReport.append(GetCurTimeStr());
		strReport.append(".txt");

		filename = strReport.c_str();
	}

	streamProfile.open(filename);

	g_endProfile = GetExactTime();
	float totalMain = g_endProfile - g_startProfile;

	const char* title =		"    % :   Total :     Ave :     Min :     Max :     # : Profile Name\n";
	const char* separator = "--------------------------------------------------------------------------------\n";

	streamProfile << title;
	streamProfile << separator;

	while( i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true ) {		
		unsigned int indent = 0;
		float percentTime, totalTime, aveTime, minTime, maxTime;
		char line[256], name[256], indentedName[256];
		char percent[16], total[16], ave[16], min[16], max[16], num[16];

		if( g_samples[i].iOpenProfiles < 0 ) {
			assert( !"ProfileEnd() called without a ProfileBegin()" );	
		}
		else if( g_samples[i].iOpenProfiles > 0 ) {
			assert( !"ProfileBegin() called without a ProfileEnd()" );
		}

		percentTime = g_samples[i].fAccumulator / totalMain;
		totalTime = g_samples[i].fAccumulator;
		aveTime = g_samples[i].fAccumulator / g_samples[i].iProfileInstances;
		minTime = g_samples[i].fMinTime;
		maxTime = g_samples[i].fMaxTime;


		//Format the data
		sprintf( percent, "%3.1f", percentTime * 100.0f);
		sprintf( total, "%3.1f", totalTime );
		sprintf( ave, "%3.1f", aveTime );
		sprintf( min, "%3.1f", minTime );
		sprintf( max, "%3.1f", maxTime );
		sprintf( num, "%3d", g_samples[i].iProfileInstances );

		if(g_samples[i].iProfileInstances == 1)
		{
			strcpy(ave, "NaN");
			strcpy(min, "NaN");
			strcpy(max, "NaN");
	
		}

		strcpy( indentedName, g_samples[i].szName );
		for( indent=0; indent<g_samples[i].iNumParents; indent++ ) {
			sprintf( name, "   %s", indentedName );
			strcpy( indentedName, name );
		}

		sprintf(line,"%5s : %7s : %7s : %7s : %7s : %5s : %s\n", percent, total, ave, min, max, num, indentedName);
		streamProfile << line;
		i++;
	}
	char summary[16];
	sprintf(summary, "%3.1f", totalMain);
	streamProfile << separator;
	streamProfile << summary;

	//cout<<streamProfile.rdbuf();


	streamProfile.close();
}
#endif