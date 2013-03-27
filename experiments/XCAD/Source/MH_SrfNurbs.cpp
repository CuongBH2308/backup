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
#include "mh_srfnurbs.h"
#include "mh_srfbezier.h"
#include "mh_srfbeziernode.h"
#include "mh_srffacet.h"
#include "mh_crvnurbs.h"
#include "mh_crvbezier.h"
#include "mh_cv.h"
#include "sl_mm.h"

#ifdef _DEBUG
void MH_SrfNurbs::Dump()
{
	CString str, s;
	for(MH_CVVect::const_iterator it = m_vCV.begin(); it != m_vCV.end(); it++)
	{
		s.Format(_T("(%f,%f,%f,%f),"), (*it).m_f[0]/(*it).m_f[3], (*it).m_f[1]/(*it).m_f[3], (*it).m_f[2]/(*it).m_f[3], (*it).m_f[3]);
		str += s;
	}
	str += _T("\n");

	for(FloatVect::const_iterator it = m_vKnotS.begin(); it != m_vKnotS.end(); it++)
	{
		s.Format(_T("%f,"), *it);
		str += s;
	}
	str += _T("\n");

	for(FloatVect::const_iterator it = m_vKnotT.begin(); it != m_vKnotT.end(); it++)
	{
		s.Format(_T("%f,"), *it);
		str += s;
	}

	::MessageBox(NULL,str,"",MB_OK);
}
#endif

MH_SrfNurbs::MH_SrfNurbs()
{
}

MH_SrfNurbs::MH_SrfNurbs(MH_CVVect vCV, 
						 size_t nCVNumS,  
						 size_t nOrderS,
						 size_t nOrderT,
						 const FloatVect& vKnotS, 
						 const FloatVect& vKnotT)
:m_vCV(vCV),
m_nCVNumS(nCVNumS),
m_nOrderS(nOrderS),
m_nOrderT(nOrderT),
m_vKnotS(vKnotS),
m_vKnotT(vKnotT)
{
}

MH_SrfNurbs::MH_SrfNurbs(const MH_SrfBezier& srfBezier)
{
	m_vCV		= srfBezier.GetCVs();
	m_nCVNumS	= srfBezier.GetCVNumS();
	m_nOrderS	= m_nCVNumS;
	m_nOrderT	= m_vCV.size()/m_nCVNumS;
	float fU[2];
	srfBezier.GetDomain(true, fU[0], fU[1]);
	m_vKnotS.insert(m_vKnotS.end(), m_nOrderS, fU[0]);
	m_vKnotS.insert(m_vKnotS.end(), m_nOrderS, fU[1]);

	srfBezier.GetDomain(false, fU[0], fU[1]);
	m_vKnotT.insert(m_vKnotT.end(), m_nOrderT, fU[0]);
	m_vKnotT.insert(m_vKnotT.end(), m_nOrderT, fU[1]);
}

MH_SrfNurbs::~MH_SrfNurbs(void)
{
}

// Triangulate the surface
// The triangles are stored in m_vTriangles
// virtual 
bool MH_SrfNurbs::Facet(float fTolerance)
{
	fTolerance = 0.05f;

	// Clean the points
	Cleanup();

	MH_SrfBezierVect vSrfBezier;
	size_t nBezierNumS;

	// Convert this surface into bezier patches
	bool bOK = ConvertToBeziers(vSrfBezier, nBezierNumS, MH_SrfNurbs());
	if(!bOK)
		return bOK;

	// Construct MH_SrfBezierNode which is used to get facets of the surface
	MH_SrfBezierNode* pSrfBezierNode = new MH_SrfBezierNode(vSrfBezier, nBezierNumS);
	if(!pSrfBezierNode)
		return false;

	// Subdivide the surface
	bOK = pSrfBezierNode->SubdivideChildren(fTolerance);

	// Get facets of the surface
	MH_SrfFacetVect vSrfFacet;
	pSrfBezierNode->GetFacets(vSrfFacet);

	// Delete 
	delete pSrfBezierNode;

	// Set Facet Type
	SetFacetType(MH_Srf::eTriangles);
	MH_SrfFacetVect::const_iterator itSrfFacet		= vSrfFacet.begin();
	MH_SrfFacetVect::const_iterator itSrfFacetEnd	= vSrfFacet.end();
	for(; itSrfFacet!=itSrfFacetEnd; ++itSrfFacet)
	{
		m_vSrfPt.push_back((*itSrfFacet).m_srfPt[0]);
		m_vSrfPt.push_back((*itSrfFacet).m_srfPt[1]);
		m_vSrfPt.push_back((*itSrfFacet).m_srfPt[2]);
	}

	return bOK;
}

// Transform this object
// virtual 
void MH_SrfNurbs::Transform(const MH_Matrix44& mtx)
{
	MH_CVVect::iterator it		= m_vCV.begin();
	MH_CVVect::iterator itCVEnd	= m_vCV.end();
	for(; it!=itCVEnd; ++it)
		(*it).Transform(mtx);
}

// Copy this surface
// virtual 
MH_Srf* MH_SrfNurbs::Copy()
{
	MH_SrfNurbs* pSrf = NEW_OBJ(MH_SrfNurbs, this)();
	*pSrf = *this;
	return pSrf;
}

// Get the nurbs expression
// virtual
MH_SrfNurbs MH_SrfNurbs::GetNurbs() const
{
	return (*this);
}

// Assignment
MH_SrfNurbs& MH_SrfNurbs::operator = (const MH_SrfNurbs& nurbs)
{
	m_vCV		= nurbs.m_vCV;
	m_nCVNumS	= nurbs.m_nCVNumS;
	m_vKnotS	= nurbs.m_vKnotS;
	m_vKnotT	= nurbs.m_vKnotT;
	m_nOrderS	= nurbs.m_nOrderS;
	m_nOrderT	= nurbs.m_nOrderT;
	return *this;
}

// Equals
bool MH_SrfNurbs::operator == (const MH_SrfNurbs& nurbs) const
{
	if(	m_vCV		== nurbs.m_vCV		&&
		m_nCVNumS	== nurbs.m_nCVNumS	&&
		m_vKnotS	== nurbs.m_vKnotS	&&
		m_vKnotT	== nurbs.m_vKnotT	&&
		m_nOrderS	== nurbs.m_nOrderS	&&
		m_nOrderT	== nurbs.m_nOrderT)
		return true;

	return false;
}

// Is the NURBS valid
bool MH_SrfNurbs::IsValid() const
{
	if(m_vCV.size()%m_nCVNumS != 0)
		return false;

	size_t nCVNumT = m_vCV.size()/m_nCVNumS;
	if( m_nCVNumS <2 || m_vKnotS.size()<2 || m_nOrderS+m_nCVNumS!=m_vKnotS.size() ||
		nCVNumT <2 || m_vKnotT.size()<2 || m_nOrderT+nCVNumT!=m_vKnotT.size() )
		return false;

	return true;
}

// Get order in S
size_t MH_SrfNurbs::GetOrderS() const
{
	return m_nOrderS;
}

// Get order in T
size_t MH_SrfNurbs::GetOrderT() const
{
	return m_nOrderT;
}

// Get all control points
const MH_CVVect& MH_SrfNurbs::GetCVs() const
{
	return m_vCV;
}

// Get CV NO. in S
size_t MH_SrfNurbs::GetCVNumS() const
{
	return m_nCVNumS;
}

// Get CV NO. in T
size_t MH_SrfNurbs::GetCVNumT() const
{
	ASSERT(m_vCV.size() % m_nCVNumS == 0);
	return m_vCV.size() / m_nCVNumS;
}

// Get knots in S
const FloatVect& MH_SrfNurbs::GetKnotsS() const
{
	return m_vKnotS;
}

// Get knots in T
const FloatVect& MH_SrfNurbs::GetKnotsT() const
{
	return m_vKnotT;
}

// How many time does u repeat
size_t MH_SrfNurbs::GetRepeatTimes(bool bS, float u) const
{
	size_t nTimes = 0;
	FloatVect::const_iterator it, itEnd;
	if(bS)
	{
		it = m_vKnotS.begin();
		itEnd = m_vKnotS.end();
	}
	else
	{
		it = m_vKnotT.begin();
		itEnd = m_vKnotT.end();
	}

	for(; it!=itEnd; ++it)
	{
		if(*it == u)
			nTimes++;
		if(*it > u)
			break;
	}
	return nTimes;
}

// Get iIndexth nurbs curve
// t is not changed in the curve
MH_CrvNurbs MH_SrfNurbs::GetCrvS(size_t iIndex) const
{
	MH_CVVect vCV;
	for(size_t i=0; i<m_nCVNumS; i++)
		vCV.push_back(m_vCV[m_nCVNumS*iIndex+i]);
	return MH_CrvNurbs(m_nOrderS, vCV, m_vKnotS);
}

// Get iIndexth nurbs curve
// s is not changed in the curve
MH_CrvNurbs MH_SrfNurbs::GetCrvT(size_t iIndex) const
{
	size_t nCVNumT = m_vCV.size()/m_nCVNumS;
	MH_CVVect vCV;
	for(size_t i=0; i<nCVNumT; i++)
		vCV.push_back(m_vCV[m_nCVNumS*i+iIndex]);
	return MH_CrvNurbs(m_nOrderT, vCV, m_vKnotT);
}

// Insert s h times
bool MH_SrfNurbs::InsertKnotS(float s, size_t h)
{
	bool bOK = false;

	// There are nCVNumT S-curve
	size_t nCVNumT = m_vCV.size()/m_nCVNumS;

	MH_CVVect vCV;
	FloatVect vKnot;
	for(size_t i=0; i<nCVNumT; i++)
	{
		MH_CrvNurbs crv = GetCrvS(i);

		// Insert the parameter s h times
		bOK = crv.InsertKnot(s, h);
		ASSERT(bOK);
		if(!bOK)
			break;

		const MH_CVVect& vCVTemp = crv.GetCVs();
		vCV.insert(vCV.end(), vCVTemp.begin(), vCVTemp.end());
		if(vKnot.size() == 0)
			vKnot = crv.GetKnots();
	}

	if(bOK)
	{
		m_vCV		= vCV;
		m_vKnotS	= vKnot;
		m_nCVNumS++;
		bOK = true;
	}
	return bOK;
}

// Insert t h times
bool MH_SrfNurbs::InsertKnotT(float t, size_t h)
{
	bool bOK = false;

	MH_CVVect vCV;
	FloatVect vKnot;

	// There are m_nCVNumS T-curve
	for(size_t i=0; i<m_nCVNumS; i++)
	{
		MH_CrvNurbs crv = GetCrvT(i);

		// Insert the parameter s h times
		bOK = crv.InsertKnot(t, h);
		ASSERT(bOK);
		if(!bOK)
			break;

		const MH_CVVect& vCVTemp = crv.GetCVs();
		vCV.insert(vCV.end(), vCVTemp.begin(), vCVTemp.end());
		if(vKnot.size() == 0)
			vKnot = crv.GetKnots();
	}

	if(bOK)
	{
		m_vCV.clear();
		size_t nCVNum = vCV.size();
		size_t nCVNumT = size_t(nCVNum/m_nCVNumS);
		m_vCV.reserve(nCVNum);
		for(size_t i=0; i<nCVNum; ++i)
			m_vCV.push_back(vCV[i%m_nCVNumS*nCVNumT+i/m_nCVNumS]);

		m_vKnotT = vKnot;
		bOK = true;
	}
	return bOK;
}

// Convert this curve to Bezier surfaces
// After inserting knot, nurbs
bool MH_SrfNurbs::ConvertToBeziers(MH_SrfBezierVect& beziers, size_t& nBezierS, MH_SrfNurbs& nurbs) const
{
	nurbs = *this;

	FloatVect vS, vT;
	FloatVect::const_iterator it	= m_vKnotS.begin();
	FloatVect::const_iterator itEnd = m_vKnotS.end();
	for(; it!=itEnd; )
	{
		vS.push_back(*it);
		size_t nTimes = GetRepeatTimes(true, *it);
		if(m_nOrderS-1 > nTimes)
			nurbs.InsertKnotS(*it, int(m_nOrderS-1-nTimes));
		it = it+nTimes;
	}

	it	= m_vKnotT.begin();
	itEnd = m_vKnotT.end();
	for(; it!=itEnd; )
	{
		vT.push_back(*it);
		size_t nTimes = GetRepeatTimes(false, *it);
		if(m_nOrderT-1 > nTimes)
			nurbs.InsertKnotT(*it, int(m_nOrderT-1-nTimes));
		it = it+nTimes;
	}

	beziers.clear();

	const MH_CVVect& vCV = nurbs.GetCVs();
	size_t nOrderS = nurbs.GetOrderS();
	size_t nOrderT = nurbs.GetOrderT();
	size_t nCVNumS = nurbs.GetCVNumS();
	size_t nCVNumT = nurbs.GetCVNumT();

	// After conversion, there are nBezierS Bezier-srf in S
	// nBezierT Bezier-srf in T
	ASSERT((nCVNumS-1)%(nOrderS-1) == 0);
	ASSERT((nCVNumT-1)%(nOrderT-1) == 0);
	nBezierS = (nCVNumS-1)/(nOrderS-1);
	size_t nBezierT = (nCVNumT-1)/(nOrderT-1);

	for(size_t t=0; t<nBezierT; t++)
	{
		for(size_t s=0; s<nBezierS; s++)
		{
			MH_CVVect vCVTemp;
			for(size_t h = 0; h<nOrderT; h++)
			{
				MH_CVVect::const_iterator itCV = 
					vCV.begin() + (t*(nOrderT-1)+h)*nCVNumS + nOrderS*s-s;
				vCVTemp.insert(vCVTemp.end(), itCV, itCV+nOrderS);
			}
			MH_SrfBezier bezier(vCVTemp, nOrderS, vS[s], vS[s+1], vT[t], vT[t+1]);
			beziers.push_back(bezier);
		}
	}
	return true;
}