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
#include "mh_collect.h"

class MH_SrfNurbs :	public MH_Srf
{
public:
#ifdef _DEBUG
	void Dump();
#endif

	MH_SrfNurbs();
	MH_SrfNurbs(MH_CVVect vCV, 
		size_t nCVNumS,  
		size_t nOrderS,
		size_t nOrderT,
		const FloatVect& vKnotS, 
		const FloatVect& vKnotT);
	MH_SrfNurbs(const MH_SrfBezier& srfBezier);
	virtual ~MH_SrfNurbs(void);

	// Triangulate the surface
	// The triangles are stored in m_vTriangles
	virtual bool Facet(float fTolerance);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this surface
	virtual MH_Srf* Copy();

	// Get the nurbs expression
	virtual MH_SrfNurbs GetNurbs() const;

	// Assignment
	MH_SrfNurbs& operator = (const MH_SrfNurbs& srf);

	// Equals
	bool operator == (const MH_SrfNurbs& nurbs) const;

	// Is the NURBS valid
	bool IsValid() const;

	// Get order in S
	size_t	GetOrderS() const;
	
	// Get order in T
	size_t	GetOrderT() const;

	// Get all control points
	const MH_CVVect& GetCVs() const;

	// Get CV NO. in S
	size_t GetCVNumS() const;

	// Get CV NO. in T
	size_t GetCVNumT() const;

	// Get knots in S
	const FloatVect& GetKnotsS() const;

	// Get knots in T
	const FloatVect& GetKnotsT() const;

	// How many time does u repeat
	size_t GetRepeatTimes(bool bS, float u) const;

	// Get iIndexth nurbs curve
	// t is not changed in the curve
	MH_CrvNurbs GetCrvS(size_t iIndex) const;

	// Get iIndexth nurbs curve
	// s is not changed in the curve
	MH_CrvNurbs GetCrvT(size_t iIndex) const;

	// Insert s h times
	bool InsertKnotS(float s, size_t h);

	// Insert t h times
	bool InsertKnotT(float t, size_t h);

	// Convert this curve to Bezier surfaces
	// After inserting knot, nurbs
	bool ConvertToBeziers(MH_SrfBezierVect& beziers, size_t& nBezierS, MH_SrfNurbs& nurbs) const;

private:
	// m_nCVNumS*i+0, m_nCVNumS*i+1, ..m_nCVNumS*i+m_nCVNumS-1 is for the i-th curve s
	MH_CVVect		m_vCV;
	size_t			m_nCVNumS;
	FloatVect		m_vKnotS;
	FloatVect		m_vKnotT;
	size_t			m_nOrderS;
	size_t			m_nOrderT;
};
