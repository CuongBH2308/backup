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
#include "mh_point3.h"
#include <math.h>
#include "mh_vector3.h"
#include "mh_crvline.h"
#include "mh_crvlineseg.h"
#include "mh_plane.h"
#include "mh_facet.h"
#include "mh_matrix44.h"
#include "mh_crdsys.h"

MH_Point3::MH_Point3(void)
{
	m_f[0] = 0;
	m_f[1] = 0;
	m_f[2] = 0;
}

MH_Point3::MH_Point3(const MH_Point3& pt)
{
	m_f[0] = pt.m_f[0];
	m_f[1] = pt.m_f[1];
	m_f[2] = pt.m_f[2];
}

MH_Point3::MH_Point3(const MH_Vector3& A)
{
	m_f[0] = A.m_f[0];
	m_f[1] = A.m_f[1];
	m_f[2] = A.m_f[2];
}

MH_Point3::MH_Point3(float x, float y, float z)
{
	m_f[0] = x;
	m_f[1] = y;
	m_f[2] = z;
}

MH_Point3::~MH_Point3(void)
{
}

void MH_Point3::Set(float x, float y, float z)
{
	m_f[0] = x;
	m_f[1] = y;
	m_f[2] = z;
}

bool MH_Point3::operator ==(const MH_Point3& pt) const
{
	if(m_f[0]==pt.m_f[0] &&	m_f[1]==pt.m_f[1] && m_f[2]==pt.m_f[2])
		return true;

	return false;
}

bool MH_Point3::operator !=(const MH_Point3& pt) const
{
	return !((*this)==pt);
}

MH_Point3& MH_Point3::operator = (const MH_Point3& pt)
{
	m_f[0]=pt.m_f[0]; 
	m_f[1]=pt.m_f[1]; 
	m_f[2]=pt.m_f[2]; 
	return(*this);
}

MH_Point3 MH_Point3::operator + (const MH_Vector3& A) const
{
	MH_Point3 ptNew(m_f[0]+A.m_f[0], m_f[1]+A.m_f[1], m_f[2]+A.m_f[2]);
	return ptNew;
}

MH_Point3 MH_Point3::operator - (void) const
{
	return MH_Point3(-m_f[0], -m_f[1], -m_f[2]);
}

MH_Vector3 MH_Point3::operator - (const MH_Point3& pt) const
{
	MH_Vector3 vSub(m_f[0]-pt.m_f[0], m_f[1]-pt.m_f[1], m_f[2]-pt.m_f[2]);
	return vSub;
}

MH_Point3 MH_Point3::operator * (const float s) const
{
	MH_Point3 ptNew(m_f[0]*s, m_f[1]*s, m_f[2]*s); 
	return ptNew; 
}

MH_Point3 MH_Point3::operator / (const float s) const
{
	ASSERT(s!=0);
	MH_Point3 ptNew(m_f[0]/s, m_f[1]/s, m_f[2]/s); 
	return ptNew; 
}

MH_Point3 MH_Point3::operator + (const MH_Point3& A) const
{
	MH_Point3 ptNew(m_f[0]+A.m_f[0], m_f[1]+A.m_f[1], m_f[2]+A.m_f[2]);
	return ptNew;
}


float MH_Point3::DistanceTo2(const MH_Point3& pt) const
{
	return (((*this)-pt)*((*this)-pt));
}

float MH_Point3::DistanceTo2(const MH_CrvLine& line, MH_Point3& ptCross) const
{
	const MH_Point3& ptInLine = line.GetPtInLine();
	const MH_Vector3& vDir = line.GetDir();

	ptCross = ptInLine + vDir*(((*this - ptInLine)*vDir)/(vDir*vDir));
	return DistanceTo2(ptCross);
}

float MH_Point3::DistanceTo2(const MH_CrvLineSeg& lineSeg, MH_Point3& ptCross) const
{
	float fLen2 = DistanceTo2(MH_CrvLine(lineSeg), ptCross);
	int nRegion=0;
	lineSeg.CheckPoint(*this, &nRegion);
	switch(nRegion)
	{
	case 0:
		break;
	case 1:
		ptCross = lineSeg.GetFrom();
		break;
	case 2:
		ptCross = lineSeg.GetTo();
		break;
	default:
		ASSERT(0);
		break;
	}
	
	return DistanceTo2(ptCross);
}

// Get distance from this point to the plane
float MH_Point3::DistanceTo2(const MH_Plane& plane, MH_Point3& ptCross) const
{
	const MH_Point3& ptInPlane	= plane.GetPoint();
	const MH_Vector3& vNormal	= plane.GetNormal();
	
	ptCross = (*this) + vNormal*((ptInPlane-(*this))*vNormal/(vNormal*vNormal));
	return DistanceTo2(ptCross);
}

/************************************************************************/
/*        \ 4/
		   \/p2
		   /\
	 <5>  /  \  <3>
		 /    \  
	 ---/------\---
   <6> /p  <1>  \p1  <2>

p1 = p + v1*s
p2 = p1 + v2*t

All points in the triangle can be expressed as:
p + v1*s + v2*s*t. 0<=s<=1, 0<=t<=1

Assuming p0 is outside this triangle in 3d space, then the distance to this triangle is
s^2*t^2*(v2*v2) + 2*s^2*t*(v1*v2) + s^2*(v1*v1) + 2*s*t*(B*v2) + 2*s*(B*v1) + (B*B)
where B = p-p0.

Then the question become: get the min value of above expression.

region <1>: 0<=s<=1; t<=0
region <2>: s>=1;t<=0
region <3>: s>=1; 0<=t<=1
region <4>: s>=1; t>=1
region <6>: s<=0; 0<=t<=1
region <5>: others
*/
/************************************************************************/
float MH_Point3::DistanceTo2(const MH_Facet& fct, MH_Point3& ptCross) const
{
	float fDist2 = DistanceTo2(MH_Plane(fct), ptCross);

	int nRegion;
	fct.CheckPoint(ptCross, &nRegion);

	switch(nRegion)
	{
	case 0: 
		return fDist2;
	case 1:
		return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0], fct.m_pt[1]), ptCross);
	case 2:
		ptCross = fct.m_pt[1];
		return DistanceTo2(ptCross);
	case 3:
		return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1], fct.m_pt[2]), ptCross);
	case 4:
		ptCross = fct.m_pt[2];
		return DistanceTo2(ptCross);
	case 5:
		return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2], fct.m_pt[0]), ptCross);
	case 6:
		ptCross = fct.m_pt[0];
		return DistanceTo2(ptCross);
	default:
		ASSERT(0);
		break;
	}
	return 0.0f;
}

// Transform this point
// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
void MH_Point3::Transform(const MH_Matrix44& mtx)
{
	MH_Point3 ptNew;
	ptNew.m_f[0] = mtx[0]*m_f[0] + mtx[1]*m_f[1] + mtx[2]*m_f[2] + mtx[3];
	ptNew.m_f[1] = mtx[4]*m_f[0] + mtx[5]*m_f[1] + mtx[6]*m_f[2] + mtx[7];
	ptNew.m_f[2] = mtx[8]*m_f[0] + mtx[9]*m_f[1] + mtx[10]*m_f[2] + mtx[11];
	float w = mtx[12]*m_f[0] + mtx[13]*m_f[1] + mtx[14]*m_f[2] + mtx[15];
	ptNew.m_f[0] /= w;
	ptNew.m_f[1] /= w;
	ptNew.m_f[2] /= w;
	*this = ptNew;
}

// Rotate this point around vAxis which is through pt
// Right-hand rotation
MH_Point3 MH_Point3::Rotate(const MH_Point3& pt, const MH_Vector3& vAxis, float fAngle) const
{
	MH_CrdSys crdSys(pt, vAxis);
	MH_Matrix44 mtxCrdSys			= crdSys.GetTransform();
	MH_Matrix44 mtxCrdSysReverse	= mtxCrdSys.Reverse();

	MH_Matrix44 m = mtxCrdSys * mtxCrdSysReverse;
	MH_Matrix44 mtx;
	mtx[0] = cos(fAngle);
	mtx[1] = -sin(fAngle);
	mtx[4] = sin(fAngle);
	mtx[5] = cos(fAngle);

	MH_Point3 ptTemp = *this;
	// mtxCrdSysReverse * pt: transform pt's coordinate in global sys to the local sys
	// mtx * (mtxCrdSysReverse * pt): in local sys, rotate it around z axis
	// mtxCrdSys * (mtx * (mtxCrdSysReverse * pt)): transform it to global sys
	ptTemp.Transform(mtxCrdSys*mtx*mtxCrdSysReverse);
	return ptTemp;
}
