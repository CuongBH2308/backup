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
#include "mh_crvellipse.h"
#include "sl_mm.h"

MH_CrvEllipse::MH_CrvEllipse(void)
{
}

MH_CrvEllipse::~MH_CrvEllipse(void)
{
}

// Tessellate the curve
// The points are stored in m_vPts
// virtual 
bool MH_CrvEllipse::Tessellate(float fTolerance)
{
	return false;
}

// Transform this object
// virtual 
void MH_CrvEllipse::Transform(const MH_Matrix44& mtx)
{
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvEllipse::Copy()
{
	MH_CrvEllipse* pCrv = NEW_OBJ(MH_CrvEllipse, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual 
MH_CrvNurbs MH_CrvEllipse::GetNurbs() const
{
	return MH_CrvNurbs();
}

// Assignment
MH_CrvEllipse& MH_CrvEllipse::operator = (const MH_CrvEllipse& crv)
{
	m_nVersion	= crv.m_nVersion;
	return *this;
}