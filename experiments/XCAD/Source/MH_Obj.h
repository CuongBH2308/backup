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

class MH_Matrix44;
class MH_Obj : public SL_Obj
{
public:
	MH_Obj(void);
	virtual ~MH_Obj(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx) = 0;
};
