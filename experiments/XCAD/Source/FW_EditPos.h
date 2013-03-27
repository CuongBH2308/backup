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
#include "fw_edit.h"

class FW_EditPos : public FW_Edit
{
public:
	FW_EditPos(void);
	virtual ~FW_EditPos(void);

	BOOL GetValue(float& value) const;
protected:
	// Is the string in the edit is valid
	virtual BOOL IsValid() const;
};
