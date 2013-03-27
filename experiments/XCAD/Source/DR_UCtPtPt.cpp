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
#include "dr_uctptpt.h"

DR_UCtPtPt::DR_UCtPtPt(const SL_Ptr<DR_DCtSolver>& pSolver, 
					   const SL_Ptr<DR_StPoint>& pStPt1,
					   const SL_Ptr<DR_StPoint>& pStPt2)
:DR_UCt(pSolver),
m_pStPt1(pStPt1),
m_pStPt2(pStPt2)
{
}

DR_UCtPtPt::~DR_UCtPtPt(void)
{
}
