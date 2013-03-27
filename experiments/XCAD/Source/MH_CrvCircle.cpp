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
#include "mh_crvcircle.h"
#include <math.h>
#include "mh_crdsys.h"
#include "mh_util.h"
#include "sl_mm.h"

MH_CrvCircle::MH_CrvCircle(void)
{
}

MH_CrvCircle::MH_CrvCircle(const MH_Point3& ptCenter, const MH_Vector3& vNormal, float fRadius)
:m_ptCenter(ptCenter),
m_vNormal(vNormal),
m_fRadius(fRadius)
{
}

MH_CrvCircle::~MH_CrvCircle(void)
{
}

// Tessellate the curve
// The points are stored in m_vPts
// virtual 
bool MH_CrvCircle::Tessellate(float fTolerance)
{
	Cleanup();

/*	MH_CrdSys crdSys(m_ptCenter, m_vNormal);
	float fDelta = acos(1-fTolerance/m_fRadius)*2;
	float fCosDelta = cos(fDelta);
	float fSinDelta = sin(fDelta);
	int nSteps = int(2*PI/fDelta);

	// Get the points in 2D space
	m_vPts.push_back(NEW_OBJ(MH_Point3, this)(fCosDelta, fSinDelta, 0));
	for(int i=1; i<nSteps; i++)
	{
		m_vPts.push_back(NEW_OBJ(MH_Point3, this)(m_vPts[i-1]->m_f[0]*fCosDelta-m_vPts[i-1]->m_f[1]*fSinDelta,
			m_vPts[i-1]->m_f[1]*fCosDelta+m_vPts[i-1]->m_f[0]*fSinDelta, 0) );
	}
	m_vPts.push_back(NEW_OBJ(MH_Point3, this)(*m_vPts[0]));


	// Convert the points into 3D space in world coordinate system
	for(MH_Point3Vect::iterator it = m_vPts.begin(); it != m_vPts.end(); ++it)
	{
		*(*it) = crdSys.PointAt((*it)->m_f[0]*m_fRadius, (*it)->m_f[1]*m_fRadius);
	}
*/
	return MH_Crv::Tessellate(fTolerance);
}

// Transform this object
// virtual 
void MH_CrvCircle::Transform(const MH_Matrix44& mtx)
{
	m_ptCenter.Transform(mtx);
	m_vNormal.Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvCircle::Copy()
{
	MH_CrvCircle* pCrv = NEW_OBJ(MH_CrvCircle, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual
MH_CrvNurbs MH_CrvCircle::GetNurbs() const
{
	MH_CVVect vCV;
	MH_CrdSys cs(m_ptCenter, m_vNormal);
	const float w = float(1.0/sqrt(2.0));
	vCV.push_back( MH_CV(cs.PointAt(m_fRadius, 0.0f), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(m_fRadius, m_fRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(0.0f, m_fRadius), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(-m_fRadius, m_fRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(-m_fRadius, 0.0f), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(-m_fRadius, -m_fRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(0.0f, -m_fRadius), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(m_fRadius, -m_fRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(m_fRadius, 0.0f), 1.0f) );

	FloatVect vKnot;
	vKnot.push_back(0.0f);
	vKnot.push_back(0.0f);
	vKnot.push_back(0.0f);
	vKnot.push_back(0.25f);
	vKnot.push_back(0.25f);
	vKnot.push_back(0.5f);
	vKnot.push_back(0.5f);
	vKnot.push_back(0.75f);
	vKnot.push_back(0.75f);
	vKnot.push_back(1.0f);
	vKnot.push_back(1.0f);
	vKnot.push_back(1.0f);

	return MH_CrvNurbs(3, vCV, vKnot);
}

// Assignment
MH_CrvCircle& MH_CrvCircle::operator = (const MH_CrvCircle& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_ptCenter	= crv.m_ptCenter;
	m_vNormal	= crv.m_vNormal;
	m_fRadius	= crv.m_fRadius;
	return *this;
}

const MH_Point3& MH_CrvCircle::GetCenter() const
{
	return m_ptCenter;
}

const MH_Vector3& MH_CrvCircle::GetNormal() const
{
	return m_vNormal;
}

float MH_CrvCircle::GetRadius() const
{
	return m_fRadius;
}