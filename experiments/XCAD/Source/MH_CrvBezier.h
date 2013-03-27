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
#include "mh_crv.h"

class MH_CrvBezier : public MH_Crv
{
public:
	MH_CrvBezier();
	MH_CrvBezier(const MH_CVVect& vCV);
	virtual ~MH_CrvBezier(void);

	// Tessellate the curve
	// The points are stored in m_vPts
	virtual bool Tessellate(float fTolerance);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this curve
	virtual MH_Crv*	Copy();

	// Get the nurbs expression
	virtual MH_CrvNurbs GetNurbs() const;

	// Assignment
	MH_CrvBezier& operator = (const MH_CrvBezier& crv);

	// Set the range of the curve
	void SetDomain(float u0, float u1);

	// Get the range of the curve
	void GetDomain(float& u0, float& u1) const;

	// Set control points
	void SetCVs(const MH_CVVect& vCV);

	// Get control points
	const MH_CVVect& GetCVs() const;

	// Get point at param u, upon De Casteljau's Algorithm
	bool GetPoint(float u, MH_Point3& pt3) const;

	// Elevate the degree
	// Then the number of the control points add n
	bool DegreeElevate(size_t n);

	// Divide this curve into two curves at u
	bool Divide(float u, MH_CrvBezier& bezier1, MH_CrvBezier& bezier2) const;

	// Divide this curve into two curves
	bool DivideHalf(MH_CrvBezier& bezier1, MH_CrvBezier& bezier2) const;

	// Subdivide the curve
	bool Subdivision(float fTol, MH_CrvPtVect& vCrvPt,  MH_CrvBezierVect* pvCrvBezier = NULL);

private:
	// Elevate the degree
	// Then the number of the control points add 1
	bool DegreeElevate();

	// Control points
	MH_CVVect	m_vCV;

	// domain of the curve 
	float		m_fU[2];
};
