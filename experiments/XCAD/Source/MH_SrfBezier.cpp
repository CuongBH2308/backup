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
#include "mh_srfbezier.h"
#include "mh_srffacet.h"
#include "mh_plane.h"
#include "sl_mm.h"

MH_SrfBezier::MH_SrfBezier(void)
{
}

MH_SrfBezier::MH_SrfBezier(const MH_CVVect& vCV,
						   size_t nCVNumS,
						   float fS0, float fS1,
						   float fT0, float fT1)
						   :m_vCV(vCV),
						   m_nCVNumS(nCVNumS)
{
	m_fS[0] = fS0;
	m_fS[1] = fS1;
	m_fT[0] = fT0;
	m_fT[1] = fT1;
}

MH_SrfBezier::~MH_SrfBezier(void)
{
}

// Tessellate the surface
// The points are stored in m_vCrvPt
// virtual 
bool MH_SrfBezier::Facet(float fTolerance)
{
	return 1;
}

// Transform this object
// virtual
void MH_SrfBezier::Transform(const MH_Matrix44& mtx)
{
	MH_CVVect::iterator it		= m_vCV.begin();
	MH_CVVect::iterator itCVEnd	= m_vCV.end();
	for(; it!=itCVEnd; ++it)
		(*it).Transform(mtx);
}

// Copy this surface
// virtual 
MH_Srf* MH_SrfBezier::Copy()
{
	MH_SrfBezier* pSrf = NEW_OBJ(MH_SrfBezier, this)();
	*pSrf = *this;
	return pSrf;
}

// Get the nurbs expression
// virtual 
MH_SrfNurbs MH_SrfBezier::GetNurbs() const
{
	size_t nCVNumT = m_vCV.size()/m_nCVNumS;
	FloatVect vKnotS, vKnotT;
	vKnotS.insert(vKnotS.end(), m_nCVNumS, m_fS[0]);
	vKnotS.insert(vKnotS.end(), m_nCVNumS, m_fS[1]);
	vKnotT.insert(vKnotT.end(), nCVNumT, m_fT[0]);
	vKnotT.insert(vKnotT.end(), nCVNumT, m_fT[1]);
	return MH_SrfNurbs(m_vCV, m_nCVNumS, m_nCVNumS, nCVNumT, vKnotS, vKnotT);
}

// Assignment
MH_SrfBezier& MH_SrfBezier::operator = (const MH_SrfBezier& srf)
{
	m_nVersion  = srf.m_nVersion;
	m_vCV		= srf.m_vCV;
	m_nCVNumS	= srf.m_nCVNumS;
	memcpy(m_fS, srf.m_fS, sizeof(m_fS[0])*2);
	memcpy(m_fT, srf.m_fT, sizeof(m_fT[0])*2);
	return *this;
}

// Get control points
const MH_CVVect& MH_SrfBezier::GetCVs() const
{
	return m_vCV;
}

// Get CV NO. in S
size_t MH_SrfBezier::GetCVNumS() const
{
	return m_nCVNumS;
}

// Set the range of the surface 
void MH_SrfBezier::SetDomain(bool bS, float u0, float u1)
{
	if(bS)
	{
		m_fS[0] = u0;
		m_fS[1] = u1;
	}
	else
	{
		m_fT[0] = u0;
		m_fT[1] = u1;
	}
}

// Get the range of the surface
void MH_SrfBezier::GetDomain(bool bS, float& u0, float& u1) const
{
	if(bS)
	{
		u0 = m_fS[0];
		u1 = m_fS[1];
	}
	else
	{
		u0 = m_fT[0];
		u1 = m_fT[1];
	}
}

// Divide this surface into two surfaces at u in S direction
bool MH_SrfBezier::Divide(bool bS, float u, MH_SrfBezier& bezier1, MH_SrfBezier& bezier2) const
{
	if(bS)
	{
		if(m_fS[0]>=u || m_fS[1]<=u)
			return false;
	}
	else
	{
		if(m_fT[0]>=u || m_fT[1]<=u)
			return false;
	}

	MH_SrfNurbs nurbs = GetNurbs();
	if(bS)
		nurbs.InsertKnotS(u, 1);
	else
		nurbs.InsertKnotT(u, 1);

	MH_SrfBezierVect vSrfBezier;
	size_t nNumS;
	nurbs.ConvertToBeziers(vSrfBezier, nNumS, MH_SrfNurbs());
	ASSERT(vSrfBezier.size() == 2);
	if(vSrfBezier.size() != 2)
		return false;

	bezier1 = vSrfBezier[0];
	bezier2 = vSrfBezier[1];
	return true;
}

// Divide this surface into two surfaces in
// S direction if bS is true,	u = (m_fS[0]+m_fS[1])/2
// T direction if bS is false,	u = (m_fT[0]+m_fT[1])/2
bool MH_SrfBezier::DivideHalf(bool bS, MH_SrfBezier& bezier1, MH_SrfBezier& bezier2) const
{
	float u;
	if(bS)
		u = (m_fS[0]+m_fS[1])/2.0f;
	else
		u = (m_fT[0]+m_fT[1])/2.0f;

	return Divide(bS, u, bezier1, bezier2);
}

// Subdivide the surface
bool MH_SrfBezier::Subdivision(float fTol, MH_SrfFacetVect& vSrfFacet, MH_SrfBezierVect* pvSrfBezier)
{
	size_t nCVNum = m_vCV.size();
	if(nCVNum < 2)
		return false;

	float fTol2			= fTol*fTol;
	MH_Point3 ptStart	= m_vCV[0].GetPoint3();
	MH_Point3 ptS		= m_vCV[m_nCVNumS-1].GetPoint3();
	MH_Point3 ptT		= m_vCV[nCVNum-m_nCVNumS].GetPoint3();
	MH_Point3 ptEnd		= m_vCV[nCVNum-1].GetPoint3();
	MH_Plane plane(ptStart, ptS, ptEnd);

	bool bStop			= true;
	for(size_t i = 1; i<(nCVNum-1); ++i)
	{
		if(m_vCV[i].GetPoint3().DistanceTo2(plane, MH_Point3()) > fTol2)
		{
			bStop = false;
			break;
		}
	}
	if(bStop)
	{
		if(pvSrfBezier)
			pvSrfBezier->push_back(*this);
		MH_SrfFacet srfFacet1(MH_SrfPt(ptStart, m_fS[0], m_fT[0]), 
			MH_SrfPt(ptS, m_fS[1], m_fT[0]),
			MH_SrfPt(ptEnd, m_fS[1], m_fT[1]));
		vSrfFacet.push_back(srfFacet1);

		MH_SrfFacet srfFacet2(MH_SrfPt(ptStart, m_fS[0], m_fT[0]), 
			MH_SrfPt(ptT, m_fS[0], m_fT[1]),
			MH_SrfPt(ptEnd, m_fS[1], m_fT[1]));
		vSrfFacet.push_back(srfFacet2);
	}
	else
	{
		MH_SrfBezier bezier1, bezier2;

		// Divide S
		if(DivideHalf(true, bezier1, bezier2))
		{
			MH_SrfBezier bezierNew[4];

			if(bezier1.DivideHalf(false, bezierNew[0], bezierNew[1]))
			{
				bezierNew[0].Subdivision(fTol, vSrfFacet, pvSrfBezier);
				bezierNew[1].Subdivision(fTol, vSrfFacet, pvSrfBezier);
			}
			if(bezier2.DivideHalf(false, bezierNew[2], bezierNew[3]))
			{
				bezierNew[2].Subdivision(fTol, vSrfFacet, pvSrfBezier);
				bezierNew[3].Subdivision(fTol, vSrfFacet, pvSrfBezier);
			}
		}
	}
	return true;
}
