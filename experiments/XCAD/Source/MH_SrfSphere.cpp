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
#include "mh_srfsphere.h"
#include <math.h>
#include "mh_crvarc.h"
#include "mh_crvline.h"
#include "mh_facet.h"
#include "mh_vector3.h"
#include "mh_plane.h"
#include "mh_srfpt.h"
#include "mh_util.h"
#include "sl_mm.h"

MH_SrfSphere::MH_SrfSphere(void)
{
}

MH_SrfSphere::MH_SrfSphere(const MH_Point3& ptCenter,const float& fRadius)
:m_ptCenter(ptCenter),
m_fRadius(fRadius)
{
}

MH_SrfSphere::~MH_SrfSphere(void)
{
}

// Triangulate the surface
// The triangles are stored in m_vFacets
// virtual 
bool MH_SrfSphere::Facet(float fTolerance)
{
	// Clean the points
	Cleanup();

	fTolerance = m_fRadius/200.0f;
	MH_SrfNurbs srfNurbs = GetNurbs();
	srfNurbs.Facet(fTolerance);
	m_vSrfPt = srfNurbs.GetPts();

	// Set Facet Type
	SetFacetType(MH_Srf::eTriangles);

	//MH_Point3 pt[6];
	//pt[0].Set( 0, 0, 1);
	//pt[1].Set( 0, 0,-1);
	//pt[2].Set(-1,-1, 0);
	//pt[3].Set( 1,-1, 0);
	//pt[4].Set( 1, 1, 0);
	//pt[5].Set(-1, 1, 0);

	//// Create the level 0 object 
	//float a = float(1.0/sqrt(2.0));
	//for (int i=0;i<6;i++)
	//{
	//	pt[i].m_f[0] *= a;
	//	pt[i].m_f[1] *= a;
	//}

	//MH_Facet facet[8];
	//facet[0].Set(pt[0],pt[3],pt[4]);
	//facet[1].Set(pt[0],pt[4],pt[5]);
	//facet[2].Set(pt[0],pt[5],pt[2]);
	//facet[3].Set(pt[0],pt[2],pt[3]);
	//facet[4].Set(pt[1],pt[4],pt[3]);
	//facet[5].Set(pt[1],pt[5],pt[4]);
	//facet[6].Set(pt[1],pt[2],pt[5]);
	//facet[7].Set(pt[1],pt[3],pt[2]);
	//int nt = 8;
	//int ntold;
	//MH_Vector3 pta, ptb, ptc;
	//MH_Point3 ptOrigin(0,0,0);
	//static int iterations = 500;
	//// Bisect each edge and move to the surface of a unit sphere 
	//for (int it=0;it<iterations;it++) 
	//{
	//	ntold = nt;
	//	for (i=0;i<ntold;i++) 
	//	{
	//		pta.Set( (m_vFacets[i]->m_pt[0].m_f[0]+m_vFacets[i]->m_pt[1].m_f[0])/2,
	//				 (m_vFacets[i]->m_pt[0].m_f[1]+m_vFacets[i]->m_pt[1].m_f[1])/2,
	//				 (m_vFacets[i]->m_pt[0].m_f[2]+m_vFacets[i]->m_pt[1].m_f[2])/2 );

	//		ptb.Set( (m_vFacets[i]->m_pt[1].m_f[0]+m_vFacets[i]->m_pt[2].m_f[0])/2,
	//				 (m_vFacets[i]->m_pt[1].m_f[1]+m_vFacets[i]->m_pt[2].m_f[1])/2,
	//				 (m_vFacets[i]->m_pt[1].m_f[2]+m_vFacets[i]->m_pt[2].m_f[2])/2 );

	//		ptb.Set( (m_vFacets[i]->m_pt[2].m_f[0]+m_vFacets[i]->m_pt[0].m_f[0])/2,
	//				 (m_vFacets[i]->m_pt[2].m_f[1]+m_vFacets[i]->m_pt[0].m_f[1])/2,
	//				 (m_vFacets[i]->m_pt[2].m_f[2]+m_vFacets[i]->m_pt[0].m_f[2])/2 );

	//		pta.Normalize();
	//		ptb.Normalize();
	//		ptc.Normalize();

	//		while(m_vFacets.size() <= size_t(nt+2))
	//			m_vFacets.push_back(new MH_Facet());

	//		m_vFacets[nt]->Set( m_vFacets[i]->m_pt[0],
	//			MH_Point3(pta),
	//			MH_Point3(ptc) );
	//		nt++;

	//		m_vFacets[nt]->Set( MH_Point3(pta),
	//			m_vFacets[i]->m_pt[1],
	//			MH_Point3(ptb) );
	//		nt++;

	//		m_vFacets[nt]->Set( MH_Point3(ptb),
	//			m_vFacets[i]->m_pt[2],
	//			MH_Point3(ptc) );
	//		nt++;

	//		m_vFacets[i]->Set( MH_Point3(pta),
	//			MH_Point3(ptb),
	//			MH_Point3(ptc) );
	//	}

	//	float fTol = m_fRadius*(1-sqrt(ptOrigin.DistanceTo2(MH_Plane(m_vFacets[0]->m_pt[0],m_vFacets[0]->GetNormal()), MH_Point3())));
	//	if(-fTolerance<fTol && fTol<fTolerance)
	//		break;
	//}
	//
	//for(std::vector<MH_Facet*>::iterator it = m_vFacets.begin(); it != m_vFacets.end(); it++)
	//{
	//	MH_Facet* pFacet = *it;
	//	pFacet->m_pt[0].m_f[0] = pFacet->m_pt[0].m_f[0]*m_fRadius+m_ptCenter.m_f[0];
	//	pFacet->m_pt[0].m_f[1] = pFacet->m_pt[0].m_f[1]*m_fRadius+m_ptCenter.m_f[1];
	//	pFacet->m_pt[0].m_f[2] = pFacet->m_pt[0].m_f[2]*m_fRadius+m_ptCenter.m_f[2];

	//	pFacet->m_pt[1].m_f[0] = pFacet->m_pt[1].m_f[0]*m_fRadius+m_ptCenter.m_f[0];
	//	pFacet->m_pt[1].m_f[1] = pFacet->m_pt[1].m_f[1]*m_fRadius+m_ptCenter.m_f[1];
	//	pFacet->m_pt[1].m_f[2] = pFacet->m_pt[1].m_f[2]*m_fRadius+m_ptCenter.m_f[2];

	//	pFacet->m_pt[2].m_f[0] = pFacet->m_pt[2].m_f[0]*m_fRadius+m_ptCenter.m_f[0];
	//	pFacet->m_pt[2].m_f[1] = pFacet->m_pt[2].m_f[1]*m_fRadius+m_ptCenter.m_f[1];
	//	pFacet->m_pt[2].m_f[2] = pFacet->m_pt[2].m_f[2]*m_fRadius+m_ptCenter.m_f[2];

	//}

    return true;
}

// Transform this object
// virtual 
void MH_SrfSphere::Transform(const MH_Matrix44& mtx)
{
	m_ptCenter.Transform(mtx);
}

// Copy this surface
// virtual 
MH_Srf* MH_SrfSphere::Copy()
{
	MH_SrfSphere* pSrf = NEW_OBJ(MH_SrfSphere, this)();
	*pSrf = *this;
	return pSrf;
}

// Get the nurbs expression
// virtual 
MH_SrfNurbs MH_SrfSphere::GetNurbs() const
{
	MH_Vector3 vX(m_fRadius, 0, 0);
	MH_Vector3 vY(0, m_fRadius, 0);
	MH_Vector3 vZ(0, 0, m_fRadius);
	const float w = float(1.0/sqrt(2.0));

	MH_Point3 ptZ = m_ptCenter+vZ;
	MH_Point3 ptAZ = m_ptCenter-vZ;
	MH_CVVect vCV;
	vCV.reserve(45);
	vCV.push_back( MH_CV(ptZ, 1) );
	vCV.push_back( MH_CV(ptZ+vX, w) );
	vCV.push_back( MH_CV(m_ptCenter+vX, 1) );
	vCV.push_back( MH_CV(ptAZ+vX, w) );
	vCV.push_back( MH_CV(ptAZ, 1) );

	vCV.push_back( MH_CV(ptZ, w) );
	vCV.push_back( MH_CV(ptZ+vX+vY, 0.5f) );
	vCV.push_back( MH_CV(m_ptCenter+vX+vY, w) );
	vCV.push_back( MH_CV(ptAZ+vX+vY, 0.5f) );
	vCV.push_back( MH_CV(ptAZ, w) );

	vCV.push_back( MH_CV(ptZ, 1) );
	vCV.push_back( MH_CV(ptZ+vY, w) );
	vCV.push_back( MH_CV(m_ptCenter+vY, 1) );
	vCV.push_back( MH_CV(ptAZ+vY, w) );
	vCV.push_back( MH_CV(ptAZ, 1) );

	vCV.push_back( MH_CV(ptZ, w) );
	vCV.push_back( MH_CV(ptZ-vX+vY, 0.5f) );
	vCV.push_back( MH_CV(m_ptCenter-vX+vY, w) );
	vCV.push_back( MH_CV(ptAZ-vX+vY, 0.5f) );
	vCV.push_back( MH_CV(ptAZ, w) );

	vCV.push_back( MH_CV(ptZ, 1) );
	vCV.push_back( MH_CV(ptZ-vX, w) );
	vCV.push_back( MH_CV(m_ptCenter-vX, 1) );
	vCV.push_back( MH_CV(ptAZ-vX, w) );
	vCV.push_back( MH_CV(ptAZ, 1) );

	vCV.push_back( MH_CV(ptZ, w) );
	vCV.push_back( MH_CV(ptZ-vX-vY, 0.5f) );
	vCV.push_back( MH_CV(m_ptCenter-vX-vY, w) );
	vCV.push_back( MH_CV(ptAZ-vX-vY, 0.5f) );
	vCV.push_back( MH_CV(ptAZ, w) );

	vCV.push_back( MH_CV(ptZ, 1) );
	vCV.push_back( MH_CV(ptZ-vY, w) );
	vCV.push_back( MH_CV(m_ptCenter-vY, 1) );
	vCV.push_back( MH_CV(ptAZ-vY, w) );
	vCV.push_back( MH_CV(ptAZ, 1) );

	vCV.push_back( MH_CV(ptZ, w) );
	vCV.push_back( MH_CV(ptZ+vX-vY, 0.5f) );
	vCV.push_back( MH_CV(m_ptCenter+vX-vY, w) );
	vCV.push_back( MH_CV(ptAZ+vX-vY, 0.5f) );
	vCV.push_back( MH_CV(ptAZ, w) );

	vCV.push_back( MH_CV(ptZ, 1) );
	vCV.push_back( MH_CV(ptZ+vX, w) );
	vCV.push_back( MH_CV(m_ptCenter+vX, 1) );
	vCV.push_back( MH_CV(ptAZ+vX, w) );
	vCV.push_back( MH_CV(ptAZ, 1) );

	FloatVect vKnotS;
	vKnotS.reserve(8);
	vKnotS.push_back(0);
	vKnotS.push_back(0);
	vKnotS.push_back(0);
	vKnotS.push_back(0.5f);
	vKnotS.push_back(0.5f);
	vKnotS.push_back(1);
	vKnotS.push_back(1);
	vKnotS.push_back(1);

	FloatVect vKnotT;
	vKnotT.reserve(12);
	vKnotT.push_back(0.0f);
	vKnotT.push_back(0.0f);
	vKnotT.push_back(0.0f);
	vKnotT.push_back(0.25f);
	vKnotT.push_back(0.25f);
	vKnotT.push_back(0.5f);
	vKnotT.push_back(0.5f);
	vKnotT.push_back(0.75f);
	vKnotT.push_back(0.75f);
	vKnotT.push_back(1.0f);
	vKnotT.push_back(1.0f);
	vKnotT.push_back(1.0f);

	return MH_SrfNurbs(vCV, 5, 3, 3, vKnotS, vKnotT);
}

// Assignment
MH_SrfSphere& MH_SrfSphere::operator = (const MH_SrfSphere& srf)
{
	m_nVersion	= srf.m_nVersion;
	m_ptCenter	= srf.m_ptCenter;
	m_fRadius	= srf.m_fRadius;
	return *this;
}