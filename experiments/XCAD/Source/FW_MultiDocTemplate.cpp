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


#include "stdafx.h"
#include "FW_MultiDocTemplate.h"

IMPLEMENT_DYNAMIC(FW_MultiDocTemplate, CMultiDocTemplate)

FW_MultiDocTemplate::FW_MultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
							   CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
							   :CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
}

FW_MultiDocTemplate::~FW_MultiDocTemplate()
{
}

BEGIN_MESSAGE_MAP(FW_MultiDocTemplate, CMultiDocTemplate)
END_MESSAGE_MAP()
