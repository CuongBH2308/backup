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
#include "afxole.h"

class FW_Document;
class FW_OleServerItem : public COleServerItem
{
	DECLARE_DYNAMIC(FW_OleServerItem)
public:
	FW_OleServerItem(FW_Document* pContainerDoc);
	virtual ~FW_OleServerItem(void);

	FW_Document* GetDocument() const;
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

protected:
	virtual void Serialize(CArchive& ar);
};
