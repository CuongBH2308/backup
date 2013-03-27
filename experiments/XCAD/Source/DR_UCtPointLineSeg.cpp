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
#include "dr_uctpointlineseg.h"
#include "dr_dctsolver.h"
#include "dr_stcrvlineseg.h"
#include "dr_stpoint.h"
#include "mh_crvlineseg.h"
#include "mh_util.h"

DR_UCtPointLineSeg::DR_UCtPointLineSeg(const SL_Ptr<DR_DCtSolver>& pSolver, 
									   const SL_Ptr<DR_StPoint>& pStPoint,
									   const SL_Ptr<DR_StCrvLineSeg>& pStCrvLineSeg)
:DR_UCt(pSolver),
m_pStPoint(pStPoint),
m_pStCrvLineSeg(pStCrvLineSeg)
{
	AddOutput(m_pStPoint.GetTarget());
	AddOutput(m_pStCrvLineSeg.GetTarget());

	if(m_pStCrvLineSeg->GetLineSeg().GetFrom().DistanceTo2(m_pStPoint->GetPoint()) < MH_Util::GetTolerance())
		m_ePtInLnSeg = eStart;
	else
		m_ePtInLnSeg = eEnd;
}

DR_UCtPointLineSeg::~DR_UCtPointLineSeg(void)
{
}

// Compute the output in new condition
// virtual 
HRESULT DR_UCtPointLineSeg::Compute()
{
	return S_OK;
}

// Get point
const SL_Ptr<DR_StPoint>& DR_UCtPointLineSeg::GetStPoint() const
{
	return m_pStPoint;
}

// Get line segment
const SL_Ptr<DR_StCrvLineSeg>& DR_UCtPointLineSeg::GetStCrvLineSeg() const
{
	return m_pStCrvLineSeg;
}

// Get EPtInLnSeg
DR_UCtPointLineSeg::EPtInLnSeg DR_UCtPointLineSeg::GetType() const
{
	return m_ePtInLnSeg;
}