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
#include "mh_cv.h"
#include "mh_collect.h"

class MH_CrvNurbs :	public MH_Crv
{
public:
#ifdef _DEBUG
	void Dump();
#endif

	MH_CrvNurbs(void);
	MH_CrvNurbs(const MH_CrvNurbs& nurbs);
	MH_CrvNurbs(size_t nOrder, const MH_CVVect& vCV, const FloatVect& vKnot);
	virtual ~MH_CrvNurbs(void);

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
	MH_CrvNurbs& operator = (const MH_CrvNurbs& crv);

	// Equals
	bool operator == (const MH_CrvNurbs& nurbs) const;

	// Is the NURBS valid
	bool IsValid() const;

	// Set curve's info
	void SetInfo(size_t nOrder, const MH_CVVect& vCV, const FloatVect& vKnot);

	// Get curve's info
	void GetInfo(size_t& nOrder, MH_CVVect& vCV, FloatVect& vKnot) const;

	// Get order of the curve
	size_t GetOrder() const;

	// Get all control points
	const MH_CVVect& GetCVs() const;

	// Get knot vector
	const FloatVect& GetKnots() const;

	// Set the nIndex-th CV
	bool SetCV(size_t nIndex, const MH_CV& cv);

	// Get the nIndex-th CV
	bool GetCV(size_t nIndex, MH_CV& cv) const;

	// Get point at param u, upon De Boor Algorithm
	bool GetPoint(float u, MH_CV& cv) const;

	// Get derivative at param u
	// u, double
	// return k+1 items if OK
	MH_CVVect GetDrv(size_t k, float u) const;

	// Insert a knot
	bool InsertKnot(float u);

	// Remove a knot
	bool RemoveKnot(float u);

	// Insert u h times
	bool InsertKnot(float u, size_t h);

	// Elevate degree from p to p+1
	bool ElevateDegree();

	// Divide this curve into two curves at u
	bool Divide(float u, MH_CrvNurbs& nurbs1, MH_CrvNurbs& nurbs2) const;

	// Divide this curve into two curves at u/2
	bool DivideHalf(MH_CrvNurbs& nurbs1, MH_CrvNurbs& nurbs2) const;

	// Subdivide the curve
	bool Subdivision(float fTol, MH_CrvPtVect& vCrvPt, MH_CrvNurbsVect* pvCrvNurbs = NULL);

	// Convert this curve to Bezier curves
	// After inserting knot, nurbs
	bool ConvertToBeziers(MH_CrvBezierVect& beziers, MH_CrvNurbs& nurbs = MH_CrvNurbs()) const;

	// Revolve this nurbs around crvLine 
	MH_SrfNurbs Revolve(const MH_CrvLine& crvLine) const;

private:
	size_t			m_nOrder;
	MH_CVVect		m_vCV;
	FloatVect		m_vKnot;
};
