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

class FW_MultiDocTemplate : public CMultiDocTemplate
{
	DECLARE_DYNAMIC(FW_MultiDocTemplate)

public:
	FW_MultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
	virtual ~FW_MultiDocTemplate();

protected:
	DECLARE_MESSAGE_MAP()
};


