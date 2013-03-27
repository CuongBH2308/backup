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


#pragma once

#define PI 3.1415926f
namespace MH_Util
{
	// Get tolerance
	float GetTolerance();

	// Get Tessellate tolerance
	float GetTessellateTolerance();

	/**
	* [M][X]=[B]
	* [M] is a matrix of n*n
	* [X] is a matrix of n*h
	* [B] is a matrix of n*h
	* this function get [X] from [M],[B]
	* LU decomposition technique, decomposes A = LU, 
	* where L and U are lower triangular and upper triangular matrices,then
	* B=(LU)X => B=L(UX) => B=LY, Y=UX
	* 1. Solving for Y from B=LY 
	* 2. Solving for X from Y=UX 
	*/
	bool SolveEquation(const float* M, const float* B, int n, int h, float* X);

	/**
	* Calculate Ckl
	*/
	size_t GetCkl(size_t k, size_t l);
};
