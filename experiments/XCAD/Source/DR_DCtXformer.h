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

class DR_StXform;
class DR_DCtXformer : public DR_DCt
{
public:
	DR_DCtXformer(const SL_Ptr<DR_Fragment>& pFragment, const SL_Ptr<DR_StXform>& pStXform);
	virtual ~DR_DCtXformer(void);

	// Set transform
	void SetStXform(const SL_Ptr<DR_StXform>& pStXform);

	// Get transform
	const SL_Ptr<DR_StXform>& GetStXform() const;
private:
	// Output
	SL_Ptr<DR_StXform>	m_pStXform;
};
