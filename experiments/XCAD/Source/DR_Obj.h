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
#include "sl_obj.h"
#include "sl_ptr.h"

class DR_Fragment;
class DR_Obj : public SL_Obj
{
public:
	DR_Obj(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_Obj(void);

	const SL_Ptr<DR_Fragment>& GetFragment() const;
private:
	SL_Ptr<DR_Fragment> m_pFragment;
};
