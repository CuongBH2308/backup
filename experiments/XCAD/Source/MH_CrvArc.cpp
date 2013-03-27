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
#include "mh_crvarc.h"
#include <math.h>
#include "mh_crdsys.h"
#include "mh_util.h"
#include "sl_mm.h"

MH_CrvArc::MH_CrvArc(void)
{
}

MH_CrvArc::MH_CrvArc(const MH_Point3& ptCenter, 
					 const MH_Vector3& vNormal, 
					 const MH_Point3& ptFrom,
					 float fAngle)
:m_ptCenter(ptCenter),
m_vNormal(vNormal),
m_ptFrom(ptFrom),
m_fAngle(fAngle)
{
	if(m_fAngle <= 0.0f)
		m_fAngle += (int(-m_fAngle/(PI*2.0f))+1) * (PI*2.0f);
	else if(m_fAngle > PI*2.0f)
		m_fAngle -= ( int(m_fAngle/(PI*2.0f)) * (PI*2.0f) );
}

MH_CrvArc::~MH_CrvArc(void)
{
}

// Tessellate the curve
// The points are stored in m_vPts
// virtual 
bool MH_CrvArc::Tessellate(float fTolerance)
{
	Cleanup();

	MH_CrvNurbs nurbs = GetNurbs();
	nurbs.Tessellate(fTolerance);
	m_vCrvPt = nurbs.GetPts();

	return MH_Crv::Tessellate(fTolerance);
}

// Transform this object
// virtual 
void MH_CrvArc::Transform(const MH_Matrix44& mtx)
{
	m_ptCenter.Transform(mtx);
	m_vNormal.Transform(mtx);
	m_ptFrom.Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvArc::Copy()
{
	MH_CrvArc* pCrv = NEW_OBJ(MH_CrvArc, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual
MH_CrvNurbs MH_CrvArc::GetNurbs() const
{
	ASSERT(m_fAngle > 0);
	
	MH_CVVect vCV;
	FloatVect vKnot;

	MH_Point3 ptTo = m_ptFrom.Rotate(m_ptCenter, m_vNormal, m_fAngle);
	MH_Vector3 vMid = (ptTo-m_ptCenter) + (m_ptFrom-m_ptCenter);
	vMid.Normalize();
	float fRadius = GetRadius();
    if(m_fAngle>0 && m_fAngle<=PI/2)
	{
		float fTemp = cos(m_fAngle/2.0f);
		MH_Point3 ptMid = m_ptCenter + vMid*fRadius/fTemp;

		vCV.push_back(m_ptFrom);
		vCV.push_back(MH_CV(ptMid, fTemp));
		vCV.push_back(ptTo);

		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);

		return MH_CrvNurbs(3, vCV, vKnot);
	}
	else if(m_fAngle>PI/2 && m_fAngle<=PI)
	{
		float fTemp = cos(m_fAngle/4.0f);
		MH_Point3 ptMid = m_ptCenter + vMid*fRadius;
		MH_Vector3 v1 = (ptMid-m_ptCenter)+(m_ptFrom-m_ptCenter);
		v1.Normalize();
		MH_Point3 pt1 = m_ptCenter + v1*fRadius/fTemp;
		MH_Vector3 v2 = (ptMid-m_ptCenter)+(ptTo-m_ptCenter);
		v2.Normalize();
		MH_Point3 pt2 = m_ptCenter + v2*fRadius/fTemp;

		vCV.push_back(m_ptFrom);
		vCV.push_back(MH_CV(pt1,fTemp*fTemp));
		vCV.push_back(MH_CV(pt2,fTemp*fTemp));
		vCV.push_back(ptTo);

		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(0.5f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
	}
	else if(m_fAngle>PI && m_fAngle<=PI*1.5f)
	{
		float fTemp = cos(m_fAngle/6.0f);
		MH_Vector3 v1 = m_ptFrom.Rotate(m_ptCenter, m_vNormal, m_fAngle/6.0f) - m_ptCenter;
		v1.Normalize();
		MH_Point3 pt1 = m_ptCenter + v1*fRadius/fTemp;
		MH_Point3 pt2 = pt1.Rotate(m_ptCenter, m_vNormal, m_fAngle/3.0f);
		MH_Point3 pt3 = m_ptFrom.Rotate(m_ptCenter, m_vNormal, m_fAngle*2.0f/3.0f);
		MH_Point3 pt4 = pt2.Rotate(m_ptCenter, m_vNormal, m_fAngle/3.0f);

		vCV.push_back(m_ptFrom);
		vCV.push_back(MH_CV(pt1,fTemp*fTemp));
		vCV.push_back(MH_CV(pt2,fTemp*fTemp));
		vCV.push_back(pt3);
		vCV.push_back(MH_CV(pt4,fTemp));
		vCV.push_back(ptTo);

		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(1.0f/3.0f);
		vKnot.push_back(2.0f/3.0f);
		vKnot.push_back(2.0f/3.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
	}
	else if(m_fAngle>PI*1.5f && m_fAngle<=PI*2.0f)
	{
		float fTemp = cos(m_fAngle/8.0f);
		MH_Vector3 v1 = m_ptFrom.Rotate(m_ptCenter, m_vNormal, m_fAngle/8.0f) - m_ptCenter;
		v1.Normalize();
		MH_Point3 pt1 = m_ptCenter + v1*fRadius/fTemp;
		MH_Point3 pt2 = pt1.Rotate(m_ptCenter, m_vNormal, m_fAngle/4.0f);
		MH_Point3 pt3 = m_ptFrom.Rotate(m_ptCenter, m_vNormal, m_fAngle/2.0f);
		MH_Point3 pt4 = pt2.Rotate(m_ptCenter, m_vNormal, m_fAngle/4.0f);
		MH_Point3 pt5 = pt4.Rotate(m_ptCenter, m_vNormal, m_fAngle/4.0f);

		vCV.push_back(m_ptFrom);
		vCV.push_back(MH_CV(pt1,fTemp*fTemp));
		vCV.push_back(MH_CV(pt2,fTemp*fTemp));
		vCV.push_back(pt3);
		vCV.push_back(MH_CV(pt4,fTemp*fTemp));
		vCV.push_back(MH_CV(pt5,fTemp*fTemp));
		vCV.push_back(ptTo);

		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(0.0f);
		vKnot.push_back(1.0f/4.0f);
		vKnot.push_back(1.0f/2.0f);
		vKnot.push_back(1.0f/2.0f);
		vKnot.push_back(3.0f/4.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
		vKnot.push_back(1.0f);
	}
	else
	{
		ASSERT(0);
	}

	return MH_CrvNurbs(3, vCV, vKnot);
}

// Assignment
MH_CrvArc& MH_CrvArc::operator = (const MH_CrvArc& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_ptCenter	= crv.m_ptCenter;
	m_vNormal	= crv.m_vNormal;
	m_ptFrom	= crv.m_ptFrom;
	m_fAngle	= crv.m_fAngle;
	return *this;
}

const MH_Point3& MH_CrvArc::GetCenter() const
{
	return m_ptCenter;
}

const MH_Vector3& MH_CrvArc::GetNormal() const
{
	return m_vNormal;
}

float MH_CrvArc::GetRadius() const
{
	return sqrt(m_ptFrom.DistanceTo2(m_ptCenter));
}