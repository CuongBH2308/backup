// ResultChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ResultChecker.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include "../RayTracing/Geometry.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ResultChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// 1. Compare the generating result (First time run: warm up + data compare)
// 2. Performance (5 times run: get the average time needed)
// Output: (screen and file, same directory)
// Correct: Yes/No
// Time: xxx


int ExecuteCommand(CString& sCommand)
{
	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 
	BOOL bRet;
	DWORD lpExitCode;
	memset(&si, 0, sizeof(si)); 
	si.cb = sizeof(si); 
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	bRet = CreateProcess( 
		NULL, // pointer to name of executable module
		sCommand.GetBuffer(MAX_PATH), // pointer to command line string
		NULL, // process security attributes
		NULL, // thread security attributes
		FALSE, // handle inheritance flag
		NORMAL_PRIORITY_CLASS, // creation flags
		NULL, // pointer to new environment block
		NULL, // pointer to current directory name
		&si, // pointer to STARTUPINFO
		&pi // pointer to PROCESS_INFORMATION
		); 

	sCommand.ReleaseBuffer();
	if(bRet) WaitForSingleObject(pi.hProcess, INFINITE); // wait for process to finish

	GetExitCodeProcess(pi.hProcess, &lpExitCode);

	CloseHandle(pi.hThread); 
	CloseHandle(pi.hProcess); 

	return lpExitCode;
}

bool FloatEqual2(float f1, float f2)
{
	return fabs(f1 - f2) < 0.002;
}
bool IsSamePosition(const point3d& p1, const point3d& p2)
{
	if (FloatEqual2(p1.x, p2.x) && FloatEqual2(p1.y, p2.y) && FloatEqual2(p1.z, p2.z))
	{
		return true;
	}
	else
		return false;
}
bool CompareResult(const TCHAR* outputFile, const TCHAR* answerFile)
{
	ifstream streamOutput(outputFile);
	ifstream streamAnswer(answerFile);
	assert(streamOutput && streamAnswer);

	// First, number
	int num1 = 0, num2 = 0;
	streamOutput >> num1;
	streamAnswer >> num2;

	//float f;
	//streamOutput >> f;
	if (num2 != num1)
	{
		return false;
	}

	// Second, each point
	list<point3d> ptsAnswer;
	for (int i = 0; i < num1; i++)
	{
		point3d pt;
		streamAnswer >> pt.x >> pt.y >> pt.z;
		ptsAnswer.push_back(pt);
	}

	for (int i = 0; i < num1; i++)
	{
		point3d ptRes;
		streamOutput >> ptRes.x >> ptRes.y >> ptRes.z;

		bool bHasEqual = false;

		list<point3d>::iterator it;
		for (it = ptsAnswer.begin(); it != ptsAnswer.end(); it++)
		{
			if(IsSamePosition(ptRes, *it))
			{
				bHasEqual = true;
				ptsAnswer.erase(it);
				break;
			}
		}
		// If this point don't have equal one, return false;
		if(!bHasEqual)
		{
			cout << "The " << i << " th number doesn't match\n";
			cout << "Output:"<<ptRes.x <<" "<<ptRes.y << " " << ptRes.z<<endl;
			return false;
		}
	}

	return true;
}


// The one and only application object

CWinApp theApp;

LARGE_INTEGER g_QPFrequency;

float GetExactTime()
{
	LARGE_INTEGER tickCounter;
	QueryPerformanceCounter(&tickCounter);
	return (float)(tickCounter.QuadPart * 1000)/g_QPFrequency.QuadPart;
}
//C:\Disk\Source\baiyanhuang\Projects\RayTracing\lib\Release\ResultChecker.exe C:\RayTracing\Input\geom_big_size.txt C:\RayTracing\Input\ray_big_size.txt C:\RayTracing\Input\big_my_result.txt C:\RayTracing\Input\out_big_size.txt
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		if (argc != 5)
		{
			printf("Usage: ContestSample.exe geometry_input.txt ray_input.txt output.txt answer.txt\n");
			return 0;
		}

		const TCHAR* geomFile = argv[1];
		const TCHAR* rayFile = argv[2];
		const TCHAR* outputFile = argv[3];
		const TCHAR* answerFile = argv[4];


		// Step 1: Run first time to warm up the program and compare the data

		TCHAR szCurDir[256];
		GetModuleFileName(NULL, szCurDir, 256);

		CString strCmd(szCurDir);
		int pos = strCmd.ReverseFind(_T('\\'));
		strCmd = strCmd.Left(pos);
		strCmd += _T("\\RayTracing.exe ");
		strCmd += geomFile; strCmd += _T(" ");
		strCmd += rayFile; strCmd += _T(" ");
		strCmd += outputFile; 

		int res = ExecuteCommand(strCmd);
		if (res == 0)
		{
			bool bSame = CompareResult(outputFile, answerFile);
			cout << "Correct: ";
			bSame ? cout << "Yes" : cout << "No";
			cout << endl;
		}

		// Step 2: Run 5 times to get the average time

		const int NUM_OF_RUN = 3;
		QueryPerformanceFrequency(&g_QPFrequency);
		float fStart = GetExactTime();

		for (int i = 0; i < NUM_OF_RUN; i++)
		{
			ExecuteCommand(strCmd);
		}

		float fEnd = GetExactTime();

		float fTime = (fEnd - fStart) / NUM_OF_RUN;
		cout << "Time: " << fTime << endl;

		system("pause");

		return 0;
	}

	return nRetCode;
}
