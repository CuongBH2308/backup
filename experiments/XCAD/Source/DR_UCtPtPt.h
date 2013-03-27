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
#include "dr_uct.h"

class DR_StPoint;
class DR_UCtPtPt : public DR_UCt
{
public:
	DR_UCtPtPt(const SL_Ptr<DR_DCtSolver>& pSolver, 
		const SL_Ptr<DR_StPoint>& pStPt1,
		const SL_Ptr<DR_StPoint>& pStPt2);
	virtual ~DR_UCtPtPt(void);

private:
	SL_Ptr<DR_StPoint> m_pStPt1;
	SL_Ptr<DR_StPoint> m_pStPt2;
};
