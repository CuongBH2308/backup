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
#include "mh_srfbezier.h"
#include "mh_collect.h"

class MH_SrfBezierNode
{
public:
	MH_SrfBezierNode(MH_SrfBezierNode* pParent, const MH_SrfBezier& srfBezier);
	MH_SrfBezierNode(const MH_SrfBezierVect& vSrfBezier, size_t nChildNumS);
	virtual ~MH_SrfBezierNode();

	// Subdivide the surface
	bool SubdivideChildren(float fTol);

	// Subdivide the surface
	bool Subdivision(float fTol);

	// Before this function be called, we should call Subdivision first
	bool GetFacets(MH_SrfFacetVect& vSrfFacet);

	// In s direction, get next in the same level
	MH_SrfBezierNode* GetRight() const;

	// In s direction, get previous in the same level
	MH_SrfBezierNode* GetLeft() const;

	// In s direction, get next in the same level
	MH_SrfBezierNode* GetDown() const;

	// In s direction, get previous in the same level
	MH_SrfBezierNode* GetUp() const;

private:
	MH_SrfBezierNode*			m_pParent;
	MH_SrfBezier				m_srfBezier;
	MH_SrfBezierNodeNPtrVect	m_vChild;
	size_t						m_nChildNumS;
};