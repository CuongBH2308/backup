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
#include "mh_crv.h"
#include "mh_crvlineseg.h"
#include "sl_mm.h"

MH_Crv::MH_Crv(void)
:m_bInvalid(true)
{
}

MH_Crv::~MH_Crv(void)
{
	Cleanup();
}

// Is it invalid
const bool&	MH_Crv::IsInvalid() const
{
	return m_bInvalid;
}

// Invalidate the obj. We need to tessellate it 
void MH_Crv::Invalidate(bool bInvalid)
{
	m_bInvalid = bInvalid;
}

// Tessellate the curve
// The points are stored in m_vPts
// virtual 
bool MH_Crv::Tessellate(float fTolerance)
{
	m_bInvalid = false;
	return false;
}

// Get points
const MH_CrvPtVect& MH_Crv::GetPts() const
{
	return m_vCrvPt;
}

// Cleanup the MH_LineSeg in m_vLineSegs
bool MH_Crv::Cleanup()
{
	m_vCrvPt.clear();
	return true;
}