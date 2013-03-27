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
#include "mh_matrix44.h"
#include "mh_util.h"
#include "mh_vector3.h"

MH_Matrix44::MH_Matrix44(void)
{
	Identity();
}

MH_Matrix44::~MH_Matrix44(void)
{
}

// Transform this object
// virtual 
void MH_Matrix44::Transform(const MH_Matrix44& mtx)
{
	*this = *this * mtx;
}

// Identify this matrix
void MH_Matrix44::Identity()
{
	memset(&m_f[0][0],0,sizeof(float)*16);
	m_f[0][0] = 1.0;
	m_f[1][1] = 1.0;
	m_f[2][2] = 1.0;
	m_f[3][3] = 1.0;
}

// Cross-Product
MH_Matrix44 MH_Matrix44::operator*(const MH_Matrix44& m) const
{
	MH_Matrix44 mNew;
	mNew.m_f[0][0] = m_f[0][0]*m.m_f[0][0]+
		m_f[0][1]*m.m_f[1][0]+
		m_f[0][2]*m.m_f[2][0]+
		m_f[0][3]*m.m_f[3][0];

	mNew.m_f[0][1] = m_f[0][0]*m.m_f[0][1]+
		m_f[0][1]*m.m_f[1][1]+
		m_f[0][2]*m.m_f[2][1]+
		m_f[0][3]*m.m_f[3][1];

	mNew.m_f[0][2] = m_f[0][0]*m.m_f[0][2]+
		m_f[0][1]*m.m_f[1][2]+
		m_f[0][2]*m.m_f[2][2]+
		m_f[0][3]*m.m_f[3][2];

	mNew.m_f[0][3] = m_f[0][0]*m.m_f[0][3]+
		m_f[0][1]*m.m_f[1][3]+
		m_f[0][2]*m.m_f[2][3]+
		m_f[0][3]*m.m_f[3][3];

	//--------------------------------------------------------------------------
	mNew.m_f[1][0] = m_f[1][0]*m.m_f[0][0]+
		m_f[1][1]*m.m_f[1][0]+
		m_f[1][2]*m.m_f[2][0]+
		m_f[1][3]*m.m_f[3][0];

	mNew.m_f[1][1] = m_f[1][0]*m.m_f[0][1]+
		m_f[1][1]*m.m_f[1][1]+
		m_f[1][2]*m.m_f[2][1]+
		m_f[1][3]*m.m_f[3][1];

	mNew.m_f[1][2] = m_f[1][0]*m.m_f[0][2]+
		m_f[1][1]*m.m_f[1][2]+
		m_f[1][2]*m.m_f[2][2]+
		m_f[1][3]*m.m_f[3][2];

	mNew.m_f[1][3] = m_f[1][0]*m.m_f[0][3]+
		m_f[1][1]*m.m_f[1][3]+
		m_f[1][2]*m.m_f[2][3]+
		m_f[1][3]*m.m_f[3][3];	

	//--------------------------------------------------------------------------
	mNew.m_f[2][0] = m_f[2][0]*m.m_f[0][0]+
		m_f[2][1]*m.m_f[1][0]+
		m_f[2][2]*m.m_f[2][0]+
		m_f[2][3]*m.m_f[3][0];

	mNew.m_f[2][1] = m_f[2][0]*m.m_f[0][1]+
		m_f[2][1]*m.m_f[1][1]+
		m_f[2][2]*m.m_f[2][1]+
		m_f[2][3]*m.m_f[3][1];

	mNew.m_f[2][2] = m_f[2][0]*m.m_f[0][2]+
		m_f[2][1]*m.m_f[1][2]+
		m_f[2][2]*m.m_f[2][2]+
		m_f[2][3]*m.m_f[3][2];

	mNew.m_f[2][3] = m_f[2][0]*m.m_f[0][3]+
		m_f[2][1]*m.m_f[1][3]+
		m_f[2][2]*m.m_f[2][3]+
		m_f[2][3]*m.m_f[3][3];

	//--------------------------------------------------------------------------
	mNew.m_f[3][0] = m_f[3][0]*m.m_f[0][0]+
		m_f[3][1]*m.m_f[1][0]+
		m_f[3][2]*m.m_f[2][0]+
		m_f[3][3]*m.m_f[3][0];

	mNew.m_f[3][1] = m_f[3][0]*m.m_f[0][1]+
		m_f[3][1]*m.m_f[1][1]+
		m_f[3][2]*m.m_f[2][1]+
		m_f[3][3]*m.m_f[3][1];

	mNew.m_f[3][2] = m_f[3][0]*m.m_f[0][2]+
		m_f[3][1]*m.m_f[1][2]+
		m_f[3][2]*m.m_f[2][2]+
		m_f[3][3]*m.m_f[3][2];

	mNew.m_f[3][3] = m_f[3][0]*m.m_f[0][3]+
		m_f[3][1]*m.m_f[1][3]+
		m_f[3][2]*m.m_f[2][3]+
		m_f[3][3]*m.m_f[3][3];

	return mNew;
}

// Assignment (=)
MH_Matrix44& MH_Matrix44::operator = (const MH_Matrix44& m)
{
	memcpy(&m_f[0][0], &m.m_f[0][0], sizeof(float)*16);
	return *this;
}

// Get m_f[i/4][i%4]
float& MH_Matrix44::operator [] (const int& i)
{
	return m_f[i/4][i%4];
}

// Get m_f[i/4][i%4]
const float& MH_Matrix44::operator [] (const int& i) const
{
	return m_f[i/4][i%4];
}

// Reverse-Matrix
MH_Matrix44 MH_Matrix44::Reverse() const
{
	MH_Matrix44 mNew;
	MH_Matrix44 mIdentity;
	MH_Util::SolveEquation(&m_f[0][0], &mIdentity.m_f[0][0], 4, 4, &mNew.m_f[0][0]);
	return mNew;
}

// Transpose-Matrix
MH_Matrix44 MH_Matrix44::Transpose() const
{
	MH_Matrix44 mNew;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			mNew.m_f[i][j] = m_f[j][i];
		}
	}

	return mNew;
}

// Get the translation matrix
// static
MH_Matrix44 MH_Matrix44::Translate(const MH_Vector3& v)
{
	MH_Matrix44 mtx;
	mtx.m_f[0][3] = v.m_f[0];
	mtx.m_f[1][3] = v.m_f[1];
	mtx.m_f[2][3] = v.m_f[2];
	return mtx;
}