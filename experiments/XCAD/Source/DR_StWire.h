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
#include "dr_st.h"

class BREP_Wire;
class DR_StWire : public DR_St
{
public:
	DR_StWire(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_StWire(void);

	// Set BREP_Wire
	void SetWire(const SL_Ptr<BREP_Wire>& pWire);

	// Get BREP_Wire
	const SL_Ptr<BREP_Wire>& GetWire() const;

private:
	SL_Ptr<BREP_Wire> m_pWire;
};
