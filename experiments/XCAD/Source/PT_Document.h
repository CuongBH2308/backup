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
#include "fw_document.h"

class PT_Document : public FW_Document
{
	DECLARE_DYNCREATE(PT_Document)
public:
	PT_Document();
	virtual ~PT_Document();

	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCSTR);
	virtual BOOL OnSaveDocument(LPCSTR);
	virtual void OnCloseDocument();

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


