/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "mh_util.h"
#include <map>

//static 
float MH_Util::GetTolerance()
{
	return 10E-5f;
}

// Get Tessellate tolerance
// static 
float MH_Util::GetTessellateTolerance()
{
	return 10E-4f; 
}

//M=LU => B=(LU)X => B=L(UX) => B=LY, Y=UX
bool MH_Util::SolveEquation(const float* M,
							const float* B,
							int n, int h,
							float* X)
{
	bool bOK = false;
	std::map<int, int> mExchangeColumn;

	float *A = new float [n*n];
	float *L = new float [n*n];
	float *U = new float [n*n];
	float *Y = new float [n*h];
	if(L==NULL || Y==NULL || U==NULL)
		goto wrapup;

	memcpy(A, M, sizeof(float)*n*n);
	memset(L,0,sizeof(float)*n*n);
	memset(U,0,sizeof(float)*n*n);
	memset(Y,0,sizeof(float)*n*h);

	int i,j,k;
	for(i=0;i<n;i++)
		L[i*n+i] = 1;

	for(i=0; i<n; i++)
	{
		if(A[i*n+i] == 0.0f)
		{
			for(j=i+1;j<n;j++)
			{
				if(A[i*n+j] != 0.0f)
				{
					for(k=0; k<n; k++)
					{
						float temp = A[k*n+i];
						A[k*n+i] = A[k*n+j];
						A[k*n+j] = temp;
					}
					mExchangeColumn[i] = j; // column j become column i
					break;
				}
			}
		}
	}

	for(j=0;j<n;j++)
	{
		for(i=0;i<=j;i++)
		{
			if(i==0)
				U[i*n+j] = A[i*n+j];
			else
			{
				U[i*n+j] = A[i*n+j];
				for(k=0;k<=i-1;k++)
					U[i*n+j] -= L[i*n+k]*U[k*n+j];
			}
		}
		for(i=j+1;i<n;i++)
		{
			L[i*n+j] = A[i*n+j];
			for(k=0;k<=j-1;k++)
				L[i*n+j] -= L[i*n+k]*U[k*n+j];

			if(U[j*n+j] != 0.0)
				L[i*n+j] /= U[j*n+j];		
			else
				ASSERT(0);
		}
	}

	//[B]nh=[L]nn * [Y]nh, get [Y]nh
	for(j=0;j<h;j++)
	{
		for(i=0;i<n;i++)
		{
			if(i==0)
				Y[i*h+j] = B[j]/L[0];
			else
			{
				Y[i*h+j] = B[i*h+j];
				for(k=0;k<=i-1;k++)
					Y[i*h+j] -= L[i*n+k]*Y[k*h+j];

				if(L[i*n+i] != 0.0)
					Y[i*h+j] /= L[i*n+i];
				else
					ASSERT(0);
			}
		}
	}

	//[Y]nh = [U]nn * [X]nh, get [X]nh
	for(j=0;j<h;j++)
	{
		for(i=n-1;i>=0;i--)
		{
			X[i*h+j] = Y[i*h+j];
			for(k=i+1;k<=n-1;k++)
				X[i*h+j] -= U[i*n+k]*X[k*h+j];

			if(U[i*n+i] != 0.0)
				X[i*h+j] /= U[i*n+i];
			else
				ASSERT(0);
		}
	}
	bOK = true;

	i = int(mExchangeColumn.size());
	if(i> 0)
	{
		std::map<int, int>::iterator it = mExchangeColumn.end();
		it--;
		for(; i>=1; it--,i--)
		{
			memcpy(A, &X[it->first * n], sizeof(float)*n);
			memcpy(&X[it->first * n], &X[it->second * n], sizeof(float)*n);
			memcpy(&X[it->second * n], A, sizeof(float)*n);
		}
	}

wrapup:
	if(A)
		delete [] A;
    if(L)
		delete [] L;
	if(Y)
		delete [] Y;
	if(U)
		delete [] U;
	return bOK;
}

size_t MH_Util::GetCkl(size_t k, size_t l)
{
	if(l>=0 && l<=k)
	{
		size_t i;
		size_t lFactorial=1;
		for(i=1;i<=l;i++)
			lFactorial*=i;

		size_t kArrange=1;
		for(i=k-l+1;i<=k;i++)
			kArrange*=i;

		return (kArrange/lFactorial);
	}
	else
		return 0;
}