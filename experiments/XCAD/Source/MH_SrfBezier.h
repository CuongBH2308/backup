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


#pragma once
#include "mh_srf.h"
#include "mh_cv.h"
#include "mh_srfnurbs.h"

class MH_SrfBezier : public MH_Srf
{
	friend class MH_SrfBezierNode;
public:
	MH_SrfBezier(void);
	MH_SrfBezier(const MH_CVVect& vCV,
		size_t nCVNumS,
		float fS0, float fS1,
		float fT0, float fT1);
	virtual ~MH_SrfBezier(void);

	// Tessellate the surface
	// The points are stored in m_vCrvPt
	virtual bool Facet(float fTolerance);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this surface
	virtual MH_Srf* Copy();

	// Get the nurbs expression
	virtual MH_SrfNurbs GetNurbs() const;

	// Assignment
	MH_SrfBezier& operator = (const MH_SrfBezier& srf);

	// Get control points
	const MH_CVVect& GetCVs() const;

	// Get CV NO. in S
	size_t GetCVNumS() const;

	// Set the range of the surface 
	void SetDomain(bool bS, float u0, float u1);

	// Get the range of the surface
	void GetDomain(bool bS, float& u0, float& u1) const;

	// Divide this surface into two surfaces at u in 
	// S direction if bS is true
	// T direction if bS is false
	bool Divide(bool bS, float u, MH_SrfBezier& bezier1, MH_SrfBezier& bezier2) const;

	// Divide this surface into two surfaces in
	// S direction if bS is true,	u = (m_fS[0]+m_fS[1])/2
	// T direction if bS is false,	u = (m_fT[0]+m_fT[1])/2
	bool DivideHalf(bool bS, MH_SrfBezier& bezier1, MH_SrfBezier& bezier2) const;

	// Subdivide the surface
	bool Subdivision(float fTol, MH_SrfFacetVect& vSrfFacet, MH_SrfBezierVect* pvSrfBezier);
private:
	// m_nCVNumS*i+0, m_nCVNumS*i+1, ..m_nCVNumS*i+m_nCVNumS-1 is for the i-th curve s
	MH_CVVect		m_vCV;
	size_t			m_nCVNumS;
	float			m_fS[2];
	float			m_fT[2];
};
