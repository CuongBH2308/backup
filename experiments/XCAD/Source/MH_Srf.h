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
#include "mh_obj.h"
#include "mh_collect.h"
#include "mh_srfpt.h"

class MH_CrvRay;
class MH_Srf : public MH_Obj
{
public:
	MH_Srf(void);
	virtual ~MH_Srf(void);

	enum EFacetType
	{
		// Vertices n, n+1 define a line segment. N-1 line segments are drawn
		eLineStrip,

		// Vertices 3n-2, 3n-1, and 3n define triangle n (n>=1). N/3 triangles are drawn
		eTriangles,

		// For odd n, vertices n, n + 1, and n + 2 define triangle n.
		// For even n, vertices n + 1, n, and n + 2 define triangle n. 
		// N/2 triangles are drawn. 
		eTriangleStrip,

		// Vertices 1, n + 1, and n + 2 define triangle n. 
		// N/2 triangles are drawn
		eTriangleFan
	};

	// Triangulate the surface
	// The triangles are stored in m_vPt3
	virtual bool Facet(float fTolerance) = 0;

	// Copy this surface
	virtual MH_Srf* Copy() = 0;

	// Get the nurbs expression
	virtual MH_SrfNurbs GetNurbs() const = 0;

	// Cleanup m_vPts
	bool Cleanup();

	// Get points
	const MH_SrfPtVect& GetPts() const;

	// Set facet type
	void SetFacetType(const EFacetType& eFacetType);

	// Get facet type
	const EFacetType& GetFacetType() const;

	// Is the surface selected
	virtual bool HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const;

protected:
	MH_SrfPtVect	m_vSrfPt;

private:
	EFacetType		m_eFacetType;
};
