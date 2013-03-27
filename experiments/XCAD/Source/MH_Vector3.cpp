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
#include "mh_vector3.h"
#include <math.h>
#include "mh_matrix44.h"

MH_Vector3::MH_Vector3(void)
{
	m_f[0] = 0;
	m_f[1] = 0;
	m_f[2] = 1;
}

MH_Vector3::MH_Vector3 (float x, float y, float z)
{
	m_f[0] = x;
	m_f[1] = y;
	m_f[2] = z;
}

MH_Vector3::~MH_Vector3(void)
{
}

// Transform this vector
// v = mtx * [m_f[0], m_f[1], m_f[2], 1]t
// virtual
void MH_Vector3::Transform(const MH_Matrix44& mtx)
{
	MH_Vector3 vNew;
	vNew.m_f[0] = mtx[0]*m_f[0] + mtx[1]*m_f[1] + mtx[2]*m_f[2] + mtx[3];
	vNew.m_f[1] = mtx[4]*m_f[0] + mtx[5]*m_f[1] + mtx[6]*m_f[2] + mtx[7];
	vNew.m_f[2] = mtx[8]*m_f[0] + mtx[9]*m_f[1] + mtx[10]*m_f[2] + mtx[11];
	float w = mtx[12]*m_f[0] + mtx[13]*m_f[1] + mtx[14]*m_f[2] + mtx[15];
	vNew.m_f[0] /= w;
	vNew.m_f[1] /= w;
	vNew.m_f[2] /= w;
	*this = vNew;
}

void MH_Vector3::Set(float x, float y, float z)
{
	m_f[0] = x;
	m_f[1] = y;
	m_f[2] = z;
}

// Normalize vector
void MH_Vector3::Normalize()
{
	float fLen = sqrt(m_f[0]*m_f[0]+m_f[1]*m_f[1]+m_f[2]*m_f[2]);
	m_f[0] /= fLen;
	m_f[1] /= fLen;
	m_f[2] /= fLen;
}

// If m_f[0]==m_f[1]==m_f[2] return false
bool MH_Vector3::IsValid() const
{
	if(m_f[0]==0.0f && m_f[1]==0.0f && m_f[2]==0.0f)
		return false;

	return true;	
}

//whether the 2 vector equal
bool MH_Vector3::operator ==(const MH_Vector3& A) const
{
	if(m_f[0]==A.m_f[0] && m_f[1]==A.m_f[1] && m_f[2]==A.m_f[2])
		return true;

	return false;		
}

MH_Vector3& MH_Vector3::operator = (const MH_Vector3& A)
{
	m_f[0]=A.m_f[0]; 
	m_f[1]=A.m_f[1]; 
	m_f[2]=A.m_f[2]; 
	return(*this);
}

MH_Vector3  MH_Vector3::operator + (const MH_Vector3& A) const
{
	MH_Vector3 Sum(m_f[0]+A.m_f[0], m_f[1]+A.m_f[1], m_f[2]+A.m_f[2]);
	return Sum; 
}
MH_Vector3  MH_Vector3::operator - (const MH_Vector3& A) const
{
	MH_Vector3 Diff(m_f[0]-A.m_f[0], m_f[1]-A.m_f[1], m_f[2]-A.m_f[2]);
	return Diff; 
}

float MH_Vector3::operator * (const MH_Vector3& A) const
{
	float DotProd = m_f[0]*A.m_f[0]+m_f[1]*A.m_f[1]+m_f[2]*A.m_f[2]; 
	return DotProd;
}

//Cross Product
MH_Vector3  MH_Vector3::operator ^ (const MH_Vector3& A) const
{ 
	MH_Vector3 CrossProd(m_f[1]*A.m_f[2]-m_f[2]*A.m_f[1],
		m_f[2]*A.m_f[0]-m_f[0]*A.m_f[2], 
		m_f[0]*A.m_f[1]-m_f[1]*A.m_f[0]); 
	return CrossProd; 
}

MH_Vector3  MH_Vector3::operator * (const float s) const
{
	MH_Vector3 Scaled(m_f[0]*s, m_f[1]*s, m_f[2]*s); 
	return Scaled; 
}

MH_Vector3  MH_Vector3::operator / (const float s) const
{
	MH_Vector3 Scaled(m_f[0]/s, m_f[1]/s, m_f[2]/s);
	return Scaled; 
}

float MH_Vector3::operator / (const MH_Vector3& A) const
{
	if(A.m_f[0]!=0)
		return m_f[0]/A.m_f[0];
	else if(A.m_f[1]!=0)
		return m_f[1]/A.m_f[1];
	else if(A.m_f[2]!=0)
		return m_f[2]/A.m_f[2];
	else
	{
		ASSERT(0);
		return 0.0f;
	}
}

void MH_Vector3::operator +=(const MH_Vector3 A)
{
	m_f[0]+=A.m_f[0]; 
	m_f[1]+=A.m_f[1]; 
	m_f[2]+=A.m_f[2];
}

void MH_Vector3::operator -=(const MH_Vector3 A)
{
	m_f[0]-=A.m_f[0]; 
	m_f[1]-=A.m_f[1]; 
	m_f[2]-=A.m_f[2];
}

void MH_Vector3::operator *=(const float s)
{
	m_f[0]*=s; 
	m_f[1]*=s; 
	m_f[2]*=s; 
}

void MH_Vector3::operator /=(const float s)
{
	m_f[0]/=s; 
	m_f[1]/=s; 
	m_f[2]/=s; 
}

MH_Vector3 MH_Vector3::operator - (void) const
{
	MH_Vector3 Negated(-m_f[0], -m_f[1], -m_f[2]);
	return Negated;
}

