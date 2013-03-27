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
#include "mh_srffacet.h"

MH_SrfFacet::MH_SrfFacet(const MH_SrfPt& srfPt1, const MH_SrfPt& srfPt2, const MH_SrfPt& srfPt3)
{
	m_srfPt[0] = srfPt1;
	m_srfPt[1] = srfPt2;
	m_srfPt[2] = srfPt3;
}

MH_SrfFacet::~MH_SrfFacet(void)
{
}

// Transform this object
// virtual 
void MH_SrfFacet::Transform(const MH_Matrix44& mtx)
{
	m_srfPt[0].Transform(mtx);
	m_srfPt[1].Transform(mtx);
	m_srfPt[2].Transform(mtx);
}