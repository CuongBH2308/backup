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
#include "mh_srfcylinder.h"
#include <math.h>
#include "mh_crdsys.h"
#include "mh_cv.h"
#include "mh_facet.h"
#include "sl_mm.h"

MH_SrfCylinder::MH_SrfCylinder(void)
{
}

MH_SrfCylinder::MH_SrfCylinder(const MH_Point3& ptBtmCenter,
							   const MH_Vector3& vAxis,
							   float fBtmRadius,
							   float fTopRadius)
:m_ptBtmCenter(ptBtmCenter),
m_vAxis(vAxis),
m_fBtmRadius(fBtmRadius),
m_fTopRadius(fTopRadius)
{
}

MH_SrfCylinder::~MH_SrfCylinder(void)
{
}

// Triangulate the surface
// The triangles are stored in m_vFacets
// virtual
bool MH_SrfCylinder::Facet(float fTolerance)
{
	// Clean the points
	Cleanup();

	if(m_fTopRadius>m_fBtmRadius)
	{
		if(m_fBtmRadius>0)
			fTolerance = m_fBtmRadius/200.0f;
		else
			fTolerance = m_fTopRadius/200.0f;
	}
	else
	{
		if(m_fTopRadius>0)
			fTolerance = m_fTopRadius/200.0f;
		else
			fTolerance = m_fBtmRadius/200.0f;
	}

	MH_SrfNurbs srfNurbs = GetNurbs();
	srfNurbs.Facet(fTolerance);
	m_vSrfPt = srfNurbs.GetPts();

	// Set Facet Type
	SetFacetType(MH_Srf::eTriangles);

	// float fAngle = 2*acos(1-fTolerance/m_fBtmRadius);

	//for(std::vector<MH_Facet*>::iterator it = m_vFacets.begin(); it !=m_vFacets.end(); it++)
	//	delete (*it);
	//m_vFacets.clear();

	//MH_CrdSys localCoordinate(m_ptBtmCenter, m_vAxis);
	//MH_Point3 ptBtmStart = localCoordinate.PointAt(m_fBtmRadius, 0, 0);
	//MH_Point3 ptTopStart = localCoordinate.PointAt(m_fTopRadius, 0, m_fHeight);
	//MH_Point3 pt1(ptBtmStart);
	//MH_Point3 pt2(ptTopStart);
	//MH_Point3 pt3, pt4;
	//MH_Facet* pFacet = NULL;
	//for(int i=1;i<2*PI/fAngle; i++)
	//{
	//	pt3 = localCoordinate.PointAt(m_fBtmRadius*cos(fAngle*i), m_fBtmRadius*sin(fAngle*i), 0);
	//	pt4 = localCoordinate.PointAt(m_fTopRadius*cos(fAngle*i), m_fTopRadius*sin(fAngle*i), m_fHeight);

	//	pFacet = new MH_Facet(pt1,pt2,pt3);
	//	m_vFacets.push_back(pFacet);

	//	pFacet = new MH_Facet(pt2,pt3,pt4);
	//	m_vFacets.push_back(pFacet);

	//	pt1 = pt3;
	//	pt2 = pt4;
	//}

	//pFacet = new MH_Facet(pt1,pt2,ptBtmStart);
	//m_vFacets.push_back(pFacet);

	//pFacet = new MH_Facet(pt2,ptBtmStart,ptTopStart);
	//m_vFacets.push_back(pFacet);

	return true;

}

// Transform this object
// virtual
void MH_SrfCylinder::Transform(const MH_Matrix44& mtx)
{
	m_ptBtmCenter.Transform(mtx);
	m_vAxis.Transform(mtx);
}

// Copy this surface
// virtual 
MH_Srf* MH_SrfCylinder::Copy()
{
	MH_SrfCylinder* pSrf = NEW_OBJ(MH_SrfCylinder, this)();
	*pSrf = *this;
	return pSrf;
}

// Get the nurbs expression
// virtual 
MH_SrfNurbs MH_SrfCylinder::GetNurbs() const
{
	MH_Vector3 vZ = m_vAxis;
	vZ.Normalize();

	MH_CVVect vCV;
	MH_CrdSys cs(m_ptBtmCenter, vZ);
	const float w = float(1.0/sqrt(2.0));
	vCV.push_back( MH_CV(cs.PointAt(m_fBtmRadius, 0.0f), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(m_fBtmRadius, m_fBtmRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(0.0f, m_fBtmRadius), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(-m_fBtmRadius, m_fBtmRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(-m_fBtmRadius, 0.0f), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(-m_fBtmRadius, -m_fBtmRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(0.0f, -m_fBtmRadius), 1.0f) );
	vCV.push_back( MH_CV(cs.PointAt(m_fBtmRadius, -m_fBtmRadius), w) );
	vCV.push_back( MH_CV(cs.PointAt(m_fBtmRadius, 0.0f), 1.0f) );

	MH_CrdSys csTop(m_ptBtmCenter+m_vAxis, vZ, cs.GetXAxis());
	vCV.push_back( MH_CV(csTop.PointAt(m_fTopRadius, 0.0f), 1.0f) );
	vCV.push_back( MH_CV(csTop.PointAt(m_fTopRadius, m_fTopRadius), w) );
	vCV.push_back( MH_CV(csTop.PointAt(0.0f, m_fTopRadius), 1.0f) );
	vCV.push_back( MH_CV(csTop.PointAt(-m_fTopRadius, m_fTopRadius), w) );
	vCV.push_back( MH_CV(csTop.PointAt(-m_fTopRadius, 0.0f), 1.0f) );
	vCV.push_back( MH_CV(csTop.PointAt(-m_fTopRadius, -m_fTopRadius), w) );
	vCV.push_back( MH_CV(csTop.PointAt(0.0f, -m_fTopRadius), 1.0f) );
	vCV.push_back( MH_CV(csTop.PointAt(m_fTopRadius, -m_fTopRadius), w) );
	vCV.push_back( MH_CV(csTop.PointAt(m_fTopRadius, 0.0f), 1.0f) );

	FloatVect vKnotS;
	vKnotS.push_back(0.0f);
	vKnotS.push_back(0.0f);
	vKnotS.push_back(0.0f);
	vKnotS.push_back(0.25f);
	vKnotS.push_back(0.25f);
	vKnotS.push_back(0.5f);
	vKnotS.push_back(0.5f);
	vKnotS.push_back(0.75f);
	vKnotS.push_back(0.75f);
	vKnotS.push_back(1.0f);
	vKnotS.push_back(1.0f);
	vKnotS.push_back(1.0f);

	FloatVect vKnotT;
	vKnotT.push_back(0);
	vKnotT.push_back(0);
	vKnotT.push_back(1);
	vKnotT.push_back(1);
	
	return MH_SrfNurbs(vCV, 9, 3, 2, vKnotS, vKnotT);
}

// Assignment
MH_SrfCylinder& MH_SrfCylinder::operator = (const MH_SrfCylinder& srf)
{
	m_nVersion		= srf.m_nVersion;
	m_ptBtmCenter	= srf.m_ptBtmCenter;
	m_vAxis			= srf.m_vAxis;
	m_fBtmRadius	= srf.m_fBtmRadius;
	m_fTopRadius	= srf.m_fTopRadius;
	return *this;
}