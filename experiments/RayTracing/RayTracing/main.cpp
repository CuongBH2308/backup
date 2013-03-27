// ContestSample.cpp : Defines the entry point for the console application.
//
//Questions
//////////////////////////////////////////////////////////////////////////
// 1. You test data will cover small number and large number data, right?
// 2. The ray's direction provided are normalized, right?


// Requirement:
// 1. Install VC Redistributable: \\shanetapp01b\MSD_Products\Inventor\R15\M15_197a_x86_srv\Server\Support\VCRedist
//        This package installs runtime components of C Runtime (CRT), Standard C++, ATL, MFC, OpenMP and MSDIA libraries

// Command line
//C:\Disk\Source\baiyanhuang\Projects\RayTracing\lib\Release\RayTracing.exe C:\RayTracing\Input\geom_big_size.txt C:\RayTracing\Input\ray_big_size.txt C:\RayTracing\Input\big_my_result.txt

#include "Profiler.h"
#include "Octree.h"
#include "Utils.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
using namespace std;

// Work flows and code are specially optimized for 8 core machine if following macro is defined
#define OPTIMIZE_FOR_8_CORE

#define MAX_OUTPUT_SIZE 100*1024*1024 // I assume the output file won't exceed 100M
#define MAX_LINE_SIZE 80
#define MAX_INTERSECTION_PER_RAY 10000

int main(int argc, char* argv[])
{
	//////////////////////////////////////////////////////////////////////////
	// In order for the parallelism, the execution sequence might be not very logical
	//////////////////////////////////////////////////////////////////////////
	// Jobs
	// 1. Load Triangle File
	// 2. Parse Triangles into memory
	// 3. Load Ray File
	// 4. Parse Ray into memory (Compute Caches in Rays)
	// 5. Build Octree
	// 6. Compute Intersections (Format output strings)
	// 7. Save Output File


	INIT_PROFILER;

	// input files
	if (argc != 4)
	{
		printf("Usage: ContestSample.exe geometry_input.txt ray_input.txt output.txt\n");
		return 0;
	}

	const char* geomFile = argv[1];
	const char* rayFile = argv[2];
	const char* outputFile = argv[3];

	// important variables...
	int numOfTriangles = 0;
	int numOfRays = 0;
	ray* arrRays = NULL;
	triangle* arrTriangles = NULL;

	char* geomBufferCopy = NULL;
	char* geomBuffer = NULL;
	long geomSize = 0;

	char* rayBufferCopy = NULL;
	char* rayBuffer = NULL;
	long raySize = 0;

	octree* pTree = NULL;

// Specialized algorithm for 8 core machine
#ifdef OPTIMIZE_FOR_8_CORE 
	// settings...
	omp_set_nested(1); // enable nested parallelism


	// Total =~ 700ms
	// 1. Load triangle file (1 thread, 7 wasted) = 16ms
	BEGIN_PROFILE("LoadTriangleFile");
	bool bSuccess = LoadFile(geomFile, geomBuffer, geomSize);
	END_PROFILE("LoadTriangleFile");

	// 2. Parse triangles into memory (7 threads) || Load rays file (1 thread) = 27.5ms
	#pragma omp parallel sections
	{

		#pragma omp section
		{
			BEGIN_PROFILE("ParseTrianglesIntoMemory");

			// Get triangle number
			char* szTriangleNum = geomBuffer;
			while(*geomBuffer++ != '\n');
			numOfTriangles = atoi(szTriangleNum);
			arrTriangles = new triangle[numOfTriangles];


			// divide into 7 portions
			int portionIndex[8];
			int portionNum = numOfTriangles / 7;

			// Get the start memory address of each portion
			char* ppPortionStart[7];
			ppPortionStart[0] = geomBuffer;
			char* pTmp = geomBuffer;


			portionIndex[0] = 0;
			for (int k = 1; k < 7; k++)
			{
				portionIndex[k] = portionNum * k;
				int numLines = portionNum * 3;
				while (numLines--)
				{
					while(*pTmp++ != '\n');
				}
				ppPortionStart[k] = pTmp;
			}
			portionIndex[7] = numOfTriangles;

			// Parse the string into values, parallelly.
			#pragma omp parallel for num_threads(7)
			for (int k = 0; k < 7; k++)
			{
				char* pStart = ppPortionStart[k];
				for (int i = portionIndex[k]; i < portionIndex[k+1]; i++)
				{
					arrTriangles[i].v0.x = GetNextValue(pStart);
					arrTriangles[i].v0.y = GetNextValue(pStart);
					arrTriangles[i].v0.z = GetLastValue(pStart);

					arrTriangles[i].v1.x = GetNextValue(pStart);
					arrTriangles[i].v1.y = GetNextValue(pStart);
					arrTriangles[i].v1.z = GetLastValue(pStart);

					arrTriangles[i].v2.x = GetNextValue(pStart);
					arrTriangles[i].v2.y = GetNextValue(pStart);
					arrTriangles[i].v2.z = GetLastValue(pStart);
				}
			}
			
			END_PROFILE("ParseTrianglesIntoMemory");
		}

		#pragma omp section
		{
			// 3. Load ray file
			BEGIN_PROFILE("LoadRayFile");
			bSuccess = LoadFile(rayFile, rayBuffer, raySize);
			END_PROFILE("LoadRayFile");
		}

}

	// 3. Parse rays into memory (8 threads)
	BEGIN_PROFILE("ParseRaysIntoMemory");
	char* szRayNum = rayBuffer;
	while(*rayBuffer++ != '\n');
	numOfRays = atoi(szRayNum);

	arrRays = new ray[numOfRays];


	// divide into 6 portions
	int portionIndex[9];
	int portionNum = numOfRays / 8;

	// Get the start memory address of each portion
	char* ppPortionStart[8];
	ppPortionStart[0] = rayBuffer;
	char* pTmp = rayBuffer;

	portionIndex[0] = 0;
	for (int k = 1; k < 8; k++)
	{
		portionIndex[k] = portionNum * k;
		int numLines = portionNum * 2;
		while (numLines--)
		{
			while(*pTmp++ != '\n');
		}
		ppPortionStart[k] = pTmp;
	}
	portionIndex[8] = numOfRays;

	// Parse the string into values, parallelly.
	#pragma omp parallel for num_threads(8)
	for(int k = 0; k < 8; k++)
	{
		char* pStart = ppPortionStart[k];
		for (int i = portionIndex[k]; i < portionIndex[k+1]; i++)
		{
			arrRays[i].origin.x = GetNextValue(pStart);
			arrRays[i].origin.y = GetNextValue(pStart);
			arrRays[i].origin.z = GetLastValue(pStart);

			arrRays[i].direction.x = GetNextValue(pStart);
			arrRays[i].direction.y = GetNextValue(pStart);
			arrRays[i].direction.z = GetLastValue(pStart);

			// cache this value as it is used frequently later
			arrRays[i].divx = 1.0f / arrRays[i].direction.x; 
			arrRays[i].divy = 1.0f / arrRays[i].direction.y;
			arrRays[i].divz = 1.0f / arrRays[i].direction.z;
		}
	}

	END_PROFILE("ParseRaysIntoMemory");


	// 4. Build octree (8 threads)
	// TODO: Build the tree parallelly
	BEGIN_PROFILE("BuildOctree");
	pTree = new octree(arrTriangles, numOfTriangles);
	// Optimization_point
	pTree->Build(1.5f);
	END_PROFILE("BuildOctree");


	// Output string, part1: Number of intersections
	// It will be filled at last when all intersections are calculated
	char szOut1[MAX_LINE_SIZE];

	// Output string, part2: intersection points
	bool bFinishCompute = false;
	char* pszOut2 = (char*)malloc(MAX_OUTPUT_SIZE);
	char* pszEachRayEnd = pszOut2;
	int numofIntersections = 0;

	BEGIN_PROFILE("ComputeIntersections");
	int maxcount = 0;
	char* pszOneRay = NULL;
	// 5. Compute intersections (8 threads) = 600ms
	#pragma omp parallel for firstprivate(pszOneRay) num_threads(8)
	for (int i = 0; i < numOfRays; i++)
	{
		// Memory leak here
		if(!pszOneRay)
		{
			pszOneRay = (char*)malloc(numOfTriangles * MAX_LINE_SIZE);
		}
		vector<point3d> intersections;
		pTree->Intersect(arrRays[i], intersections);
		if (!intersections.empty())
		{
			char* pEachEnd = pszOneRay;

			for (vector<point3d>::iterator it = intersections.begin(); it != intersections.end(); it++)
			{
				char szLine[MAX_LINE_SIZE];
				sprintf(szLine, "%f %f %f\n", it->x, it->y, it->z);
				pEachEnd = dbger_strcpy(pEachEnd, szLine);
			}

			#pragma omp critical
			{
				pszEachRayEnd = dbger_strcpy(pszEachRayEnd, pszOneRay);
				numofIntersections += intersections.size();
			}
		}
	}
	END_PROFILE("ComputeIntersections");


	// 6. Save output file (1 thread, 7 wasted) = 32ms
	BEGIN_PROFILE("SaveIntersections");

	ofstream streamOut;
	streamOut.open(outputFile);

	sprintf(szOut1, "%d\n", numofIntersections);

	streamOut << szOut1;
	streamOut << pszOut2;

	streamOut.close();
	END_PROFILE("SaveIntersections");

	BEGIN_PROFILE("FreeMemory");
	// free memories
	delete[] arrTriangles;
	delete[] arrRays;
	free(geomBuffer);
	free(rayBuffer);
	free(pszOut2);
	delete pTree;
	END_PROFILE("FreeMemory");

// General algorithm which is scalable.
#else //#ifdef OPTIMIZE_FOR_8_CORE 

	// settings...
	omp_set_nested(1); // enable nested parallelism


	// 1. Load triangle file
	BEGIN_PROFILE("LoadTriangleFile");
	bool bSuccess = LoadFile(geomFile, geomBuffer, geomSize);
	END_PROFILE("LoadTriangleFile");

	// 2. Parse triangles into memory
	BEGIN_PROFILE("ParseTrianglesIntoMemory");

	// Get triangle number
	char* szTriangleNum = geomBuffer;
	while(*geomBuffer++ != '\n');
	numOfTriangles = atoi(szTriangleNum);
	arrTriangles = new triangle[numOfTriangles];

	// new a copy of geom buffer. (for mulithread query)
	geomBufferCopy = (char*)malloc(geomSize + 1);
	// TODO: Optimize
	strcpy(geomBufferCopy, geomBuffer);
	int nDiff = geomBuffer - geomBufferCopy;


	// Parse the string into values, parallelly.
	char* pStart = NULL;
	#pragma omp parallel for firstprivate(pStart)
	for (int i = 0; i < numOfTriangles; i++)
	{
		// Move to the right memory position for each thread
		if(!pStart)
		{
			char* pStartCopy = MoveToTriangle(geomBufferCopy, i);
			pStart = pStartCopy + nDiff;
		}

		arrTriangles[i].v0.x = GetNextValue(pStart);
		arrTriangles[i].v0.y = GetNextValue(pStart);
		arrTriangles[i].v0.z = GetLastValue(pStart);
		
		arrTriangles[i].v1.x = GetNextValue(pStart);
		arrTriangles[i].v1.y = GetNextValue(pStart);
		arrTriangles[i].v1.z = GetLastValue(pStart);
	
		arrTriangles[i].v2.x = GetNextValue(pStart);
		arrTriangles[i].v2.y = GetNextValue(pStart);
		arrTriangles[i].v2.z = GetLastValue(pStart);
	}
	END_PROFILE("ParseTrianglesIntoMemory");

	
	octree* pTree = NULL;
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			// 3. Load ray file
			BEGIN_PROFILE("LoadRayFile");
			bSuccess = LoadFile(rayFile, rayBuffer, raySize);
			END_PROFILE("LoadRayFile");

			// 4. Parse rays into memory
			BEGIN_PROFILE("ParseRaysIntoMemory");
			char* szRayNum = rayBuffer;
			while(*rayBuffer++ != '\n');
			numOfRays = atoi(szRayNum);

			arrRays = new ray[numOfRays];

			rayBufferCopy = (char*)malloc(raySize+1);
			strcpy(rayBufferCopy, rayBuffer);
			int nDiff = rayBuffer - rayBufferCopy;

			// Parse the string into values, parallelly.
			char* pStart = NULL;
			#pragma omp parallel for firstprivate(pStart)
			for (int i = 0; i < numOfRays; i++)
			{
				// Move to the right memory position for each thread
				if(!pStart)
				{
					char* pStartCopy = MoveToRay(rayBufferCopy, i);
					pStart = pStartCopy + nDiff;

				}

				arrRays[i].origin.x = GetNextValue(pStart);
				arrRays[i].origin.y = GetNextValue(pStart);
				arrRays[i].origin.z = GetLastValue(pStart);

				arrRays[i].direction.x = GetNextValue(pStart);
				arrRays[i].direction.y = GetNextValue(pStart);
				arrRays[i].direction.z = GetLastValue(pStart);

				// cache this value as it is used frequently later
				arrRays[i].divx = 1.0f / arrRays[i].direction.x; 
				arrRays[i].divy = 1.0f / arrRays[i].direction.y;
				arrRays[i].divz = 1.0f / arrRays[i].direction.z;
			}
			END_PROFILE("ParseRaysIntoMemory");
		}

		#pragma omp section
		{
			// 5. Build octree
			// TODO: Build the tree parallelly
			BEGIN_PROFILE("BuildOctree");
			pTree = new octree(arrTriangles, numOfTriangles);
			// Optimization_point
			pTree->Build(1.5f);
			END_PROFILE("BuildOctree");
		}
	}
	

	// Output string, part1: Number of intersections
	// It will be filled at last when all intersections are calculated
	char szOut1[MAX_LINE_SIZE];

	// Output string, part2: intersection points
	bool bFinishCompute = false;
	char* pszOut2 = (char*)malloc(MAX_OUTPUT_SIZE);
	char* pszEachRayEnd = pszOut2;
	int numofIntersections = 0;

	// 6. Compute intersection (Format output strings)
	BEGIN_PROFILE("ComputeIntersections");
	int maxcount = 0;
	char* pszOneRay = NULL;
	#pragma omp parallel for firstprivate(pszOneRay)/* num_threads(computing_threads_num)*/
	for (int i = 0; i < numOfRays; i++)
	{
		// Memory leak here
		if(!pszOneRay)
		{
			pszOneRay = (char*)malloc(numOfTriangles * MAX_LINE_SIZE);
		}
		vector<point3d> intersections;
		pTree->Intersect(arrRays[i], intersections);
		if (!intersections.empty())
		{
			char* pEachEnd = pszOneRay;
			
			for (vector<point3d>::iterator it = intersections.begin(); it != intersections.end(); it++)
			{
				char szLine[MAX_LINE_SIZE];
				sprintf(szLine, "%f %f %f\n", it->x, it->y, it->z);
				pEachEnd = dbger_strcpy(pEachEnd, szLine);
			}
			
			#pragma omp critical
			{
				pszEachRayEnd = dbger_strcpy(pszEachRayEnd, pszOneRay);
				numofIntersections += intersections.size();
			}
		}
	}
	END_PROFILE("ComputeIntersections");


	// 7. Save output file
	BEGIN_PROFILE("SaveIntersections");

	ofstream streamOut;
	streamOut.open(outputFile);

	sprintf(szOut1, "%d\n", numofIntersections);

	streamOut << szOut1;
	streamOut << pszOut2;

	streamOut.close();
	END_PROFILE("SaveIntersections");

	BEGIN_PROFILE("FreeMemory");
	// free memories
	delete[] arrTriangles;
	delete[] arrRays;
	free(geomBufferCopy);
	free(geomBuffer);
	free(rayBufferCopy);
	free(rayBuffer);
	free(pszOut2);
	delete pTree;
	END_PROFILE("FreeMemory");

#endif

	DONE_PROFILER(NULL);
	return 0;
}

