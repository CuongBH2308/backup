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
#include "sl_ptr.h"

class FW_Document;
class FW_RequestTxn : public FW_Request
{
public:
	FW_RequestTxn(FW_Document* pDoc);
	virtual ~FW_RequestTxn(void);

	virtual HRESULT Execute();

protected:
	virtual HRESULT OnExecute() = 0;
};
