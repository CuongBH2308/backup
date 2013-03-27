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
#include "mh_crvbezier.h"
#include "mh_cv.h"
#include "mh_point3.h"
#include "mh_crvline.h"
#include "sl_mm.h"

MH_CrvBezier::MH_CrvBezier()
{
	m_fU[0] = 0;
	m_fU[1] = 1.0f;
}

MH_CrvBezier::MH_CrvBezier(const MH_CVVect& vCV)
:m_vCV(vCV)
{
	m_fU[0] = 0;
	m_fU[1] = 1.0f;
}

MH_CrvBezier::~MH_CrvBezier(void)
{
}

// Tessellate the curve
// The points are stored in m_vPts
// virtual 
bool MH_CrvBezier::Tessellate(float fTolerance)
{
	Cleanup();

#ifdef _DEBUG
	DWORD dw1 = GetTickCount();
#endif
	bool bOK = Subdivision(fTolerance, m_vCrvPt);

#ifdef _DEBUG
	DWORD dwTimeCost = GetTickCount() - dw1;
#endif
	return bOK;
}

// Transform this object
// virtual 
void MH_CrvBezier::Transform(const MH_Matrix44& mtx)
{
	MH_CVVect::iterator it		= m_vCV.begin();
	MH_CVVect::iterator itCVEnd	= m_vCV.end();
	for(; it!=itCVEnd; ++it)
		(*it).Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvBezier::Copy()
{
	MH_CrvBezier* pCrv = NEW_OBJ(MH_CrvBezier, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual 
MH_CrvNurbs MH_CrvBezier::GetNurbs() const
{
	size_t nCVNum = m_vCV.size();
	MH_CVVect vCV;
	FloatVect vKnot;
	vKnot.insert(vKnot.end(), nCVNum, m_fU[0]);
	vKnot.insert(vKnot.end(), nCVNum, m_fU[1]);
	return MH_CrvNurbs(nCVNum, m_vCV, vKnot);
}

// Assignment
MH_CrvBezier& MH_CrvBezier::operator = (const MH_CrvBezier& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_vCV		= crv.m_vCV;
	m_fU[0]		= crv.m_fU[0];
	m_fU[1]		= crv.m_fU[1];
	return *this;
}

// Set control points
void MH_CrvBezier::SetCVs(const MH_CVVect& vCV)
{
	m_vCV = vCV;
}

// Get control points
const MH_CVVect& MH_CrvBezier::GetCVs() const
{
	return m_vCV;
}

// Set the range of the curve
void MH_CrvBezier::SetDomain(float u0, float u1)
{
	m_fU[0] = u0;
	m_fU[1] = u1;
}

// Get the range of the curve
void MH_CrvBezier::GetDomain(float& u0, float& u1) const
{
	u0 = m_fU[0];
	u1 = m_fU[1];
}

// Get point at param u, upon De Casteljau's Algorithm
bool MH_CrvBezier::GetPoint(float u, MH_Point3& pt3) const
{
	size_t nCV = m_vCV.size();
	if(nCV < 2)
		return false;

	if(m_fU[0] > u || m_fU[1] < u)
		return false;

	size_t n = nCV-1;
	bool bOK = false;
	MH_CV* pPt3 = new MH_CV[nCV];
	if(!pPt3)
		goto wrapup;

	for(size_t i=0; i<nCV; i++)
		pPt3[i] = m_vCV[i];

	for(size_t i=1; i<=n; i++)
	{
		for(size_t j=0; j<=n-i; j++)
		{
			float uT = (u-m_fU[0])/(m_fU[1]-m_fU[0]);
			pPt3[j] = pPt3[j]*(1-uT) + pPt3[j+1]*uT;
		}
	}

	pt3 = pPt3[0].GetPoint3();
	bOK = true;
wrapup:
	if(pPt3)
		delete [] pPt3;
	return bOK;
}

// Elevate the degree
// Then the number of the control points add n
bool MH_CrvBezier::DegreeElevate(size_t n)
{
	for(size_t i=0; i<n; i++)
		DegreeElevate();

	return true;
}

// Elevate the degree
// Then the number of the control points add 1
bool MH_CrvBezier::DegreeElevate()
{
	MH_CVVect vPt3;
	vPt3.push_back(m_vCV.front());
	size_t nCV = m_vCV.size();
	for(size_t i=1; i<=(nCV-1); i++)
	{
		MH_CV pt = m_vCV[i-1]*(float(i)/float(nCV)) +
			m_vCV[i]*(1-float(i)/float(nCV));
		vPt3.push_back(pt);
	}
	vPt3.push_back(m_vCV.back());
	m_vCV = vPt3;
	return true;
}

// Divide this curve into two curves at u
bool MH_CrvBezier::Divide(float u, MH_CrvBezier& bezier1, MH_CrvBezier& bezier2) const
{
	size_t nCV = m_vCV.size();
	if(nCV < 2)
		return false;

	float fU[2];
	GetDomain(fU[0], fU[1]);
	if(fU[0] >= u || fU[1] <= u)
		return false;

	MH_CVVect vCV1;
	MH_CVVect vCV2;
	size_t n = nCV-1;
	bool bOK = false;
	MH_CV* pPt3 = new MH_CV[nCV];
	if(!pPt3)
		goto wrapup;

	for(size_t i=0; i<nCV; i++)
		pPt3[i] = m_vCV[i];

	vCV1.push_back(m_vCV.front());
	vCV2.insert(vCV2.begin(), m_vCV.back());

	for(size_t i=1; i<=n; i++)
	{
		for(size_t j=0; j<=n-i; j++)
		{
			pPt3[j] = pPt3[j]*((1-(u-fU[0])/(fU[1]-fU[0]))) + pPt3[j+1]*((u-fU[0])/(fU[1]-fU[0]));
			if(j == 0)
				vCV1.push_back(pPt3[j]);
			if(j == (n-i))
				vCV2.insert(vCV2.begin(), pPt3[j]);
		}
	}

	bezier1.SetCVs(vCV1);
	bezier1.SetDomain(fU[0], u);
    bezier2.SetCVs(vCV2);
	bezier1.SetDomain(u, fU[1]);
	bOK = true;
wrapup:
	if(pPt3)
		delete [] pPt3;
	return bOK;
}

// Divide this curve into two curves
bool MH_CrvBezier::DivideHalf(MH_CrvBezier& bezier1, MH_CrvBezier& bezier2) const
{
	return Divide((m_fU[0]+m_fU[1])/2.0f, bezier1, bezier2);
}

// Subdivide the curve
bool MH_CrvBezier::Subdivision(float fTol, MH_CrvPtVect& vCrvPt,  MH_CrvBezierVect* pvCrvBezier)
{
	size_t nCVNum = m_vCV.size();
	if(nCVNum < 2)
		return false;

	float fTol2			= fTol*fTol;
	MH_Point3 ptStart	= m_vCV[0].GetPoint3();
	MH_Point3 ptEnd		= m_vCV[nCVNum-1].GetPoint3();
	MH_CrvLine line(ptStart, ptEnd-ptStart);

	bool bStop			= true;
	for(size_t i = 1; i<(nCVNum-1); ++i)
	{
		if(m_vCV[i].GetPoint3().DistanceTo2(line, MH_Point3()) > fTol2)
		{
			bStop = false;
			break;
		}
	}
	if(bStop)
	{
		if(pvCrvBezier)
			pvCrvBezier->push_back(*this);

		// Store the start point of the curve
		// And later, only store the end point of each sub-curve
		if(vCrvPt.size() == 0)
			vCrvPt.push_back(MH_CrvPt(ptStart, m_fU[0]));
		vCrvPt.push_back(MH_CrvPt(ptEnd, m_fU[1]));
	}
	else
	{
		MH_CrvBezier bezier1, bezier2;

		// Divide this curve into two curves
		if(DivideHalf(bezier1, bezier2))
		{
			// Subdivide the 1st sub-curve
			bezier1.Subdivision(fTol, vCrvPt, pvCrvBezier);

			// Subdivide the 2nd sub-curve
			bezier2.Subdivision(fTol, vCrvPt, pvCrvBezier);
		}
	}
	return true;
}