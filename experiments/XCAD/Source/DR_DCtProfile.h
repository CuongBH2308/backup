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
#include "dr_dct.h"

class DR_StSetBodyWire;
class DR_DCtProfile : public DR_DCt
{
public:
	DR_DCtProfile(const SL_Ptr<DR_Fragment>& pFragment,
		const SL_Ptr<DR_StSetBodyWire>& pStSetBodyWire);
	virtual ~DR_DCtProfile(void);

	// Compute the output in new condition
	virtual HRESULT Compute();

private:
	SL_Ptr<DR_StSetBodyWire> m_pStSetBodyWire;
};
