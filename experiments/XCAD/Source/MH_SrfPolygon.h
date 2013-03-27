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

class MH_SrfPolygon : public MH_Srf
{
public:
	MH_SrfPolygon();
	MH_SrfPolygon(const MH_Point3Vect& vPt3);
	virtual ~MH_SrfPolygon(void);

	// Triangulate the surface
	// The triangles are stored in m_vPt3
	virtual bool Facet(float fTolerance);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this surface
	virtual MH_Srf* Copy();

	// Assignment
	MH_SrfPolygon& operator = (const MH_SrfPolygon& srf);
};
