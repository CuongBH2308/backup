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
#include "dr_stset.h"
#include "dr_collect.h"

class BREP_Body;
class DR_StSetBodyWire : public DR_StSet
{
public:
	DR_StSetBodyWire(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_StSetBodyWire(void);

	// Get combined BREP_Body
	HRESULT GetBody(BREP_Body*& pBody) const;

private:
	DR_StBodyWireVect m_vStBodyWire;
};
