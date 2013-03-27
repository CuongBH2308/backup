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
#include "fw_request.h"

class UC_UndoReq : public FW_Request
{
public:
	UC_UndoReq(FW_Document* pDoc);
	virtual ~UC_UndoReq(void);

	virtual HRESULT Script();
	virtual HRESULT InitFromScript();
	virtual HRESULT Execute();
};
