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
#include "dr_uctcvcrv.h"

class DR_StCrvNurbs;
class DR_UCtCVCrvNurbs : public DR_UCtCVCrv
{
public:
	DR_UCtCVCrvNurbs(const SL_Ptr<DR_DCtSolver>& pSolver, 
		const SL_Ptr<DR_StPoint>&		pStCV,
		const SL_Ptr<DR_StCrvNurbs>&	pStCrvNurbs,
		size_t nIndex);
	virtual ~DR_UCtCVCrvNurbs(void);

	// Compute the output in new condition
	virtual HRESULT Compute();

private:
	SL_Ptr<DR_StCrvNurbs> m_pStCrvNurbs;
};
