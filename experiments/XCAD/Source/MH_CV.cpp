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
#include "mh_cv.h"

MH_CV::MH_CV(void)
{
}

MH_CV::MH_CV(float wx, float wy, float wz, float w)
{
	m_f[0] = wx;
	m_f[1] = wy;
	m_f[2] = wz;
	m_f[3] = w;
}

MH_CV::MH_CV(const MH_Point3& pt3, float w)
{
	m_f[0] = pt3.m_f[0]*w;
	m_f[1] = pt3.m_f[1]*w;
	m_f[2] = pt3.m_f[2]*w;
	m_f[3] = w;
}

MH_CV::~MH_CV(void)
{
}

// Transform this control point
// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
// virtual 
void MH_CV::Transform(const MH_Matrix44& mtx)
{
	MH_Point3 ptNew(m_f[0], m_f[1], m_f[2]);
	ptNew.Transform(mtx);
	m_f[0] = ptNew.m_f[0];
	m_f[1] = ptNew.m_f[1];
	m_f[2] = ptNew.m_f[2];
}

// Equals
bool MH_CV::operator ==(const MH_CV& cv) const
{
	if(m_f[0]==cv.m_f[0] && m_f[1]==cv.m_f[1] && m_f[2]==cv.m_f[2] && m_f[3]==cv.m_f[3])
		return true;
	return false;
}

// Set point
void MH_CV::SetPoint3(const MH_Point3& pt)
{
	m_f[0] = pt.m_f[0]*m_f[3];
	m_f[1] = pt.m_f[1]*m_f[3];
	m_f[2] = pt.m_f[2]*m_f[3];
}

// Get coordinate 
MH_Point3 MH_CV::GetPoint3() const
{
	MH_Point3 ptNew(m_f[0]/m_f[3], m_f[1]/m_f[3], m_f[2]/m_f[3]);
	return ptNew;
}

MH_CV MH_CV::operator + (const MH_CV& cv) const
{
	MH_CV cvNew(m_f[0]+cv.m_f[0], m_f[1]+cv.m_f[1], m_f[2]+cv.m_f[2], m_f[3]+cv.m_f[3]); 
	return cvNew; 
}

MH_CV MH_CV::operator - (const MH_CV& cv) const
{
	MH_CV cvNew(m_f[0]-cv.m_f[0], m_f[1]-cv.m_f[1], m_f[2]-cv.m_f[2], m_f[3]-cv.m_f[3]); 
	return cvNew; 
}

MH_CV MH_CV::operator * (const float s) const
{
	MH_CV cvNew(m_f[0]*s, m_f[1]*s, m_f[2]*s, m_f[3]*s); 
	return cvNew; 
}

MH_CV MH_CV::operator / (const float s) const
{
	MH_CV cvNew(m_f[0]/s, m_f[1]/s, m_f[2]/s, m_f[3]/s); 
	return cvNew; 
}
