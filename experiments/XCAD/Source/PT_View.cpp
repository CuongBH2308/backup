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
#include "pt_document.h"
#include "pt_view.h"

// PT_View
IMPLEMENT_DYNCREATE(PT_View, FW_View)

BEGIN_MESSAGE_MAP(PT_View, FW_View)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, FW_View::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, FW_View::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, FW_View::OnFilePrintPreview)
END_MESSAGE_MAP()

// PT_View construction/destruction

PT_View::PT_View()
{
	// TODO: add construction code here

}

PT_View::~PT_View()
{
}

BOOL PT_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return FW_View::PreCreateWindow(cs);
}


// PT_View printing

BOOL PT_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void PT_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void PT_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// PT_View diagnostics

#ifdef _DEBUG
void PT_View::AssertValid() const
{
	FW_View::AssertValid();
}

void PT_View::Dump(CDumpContext& dc) const
{
	FW_View::Dump(dc);
}

PT_Document* PT_View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(PT_Document)));
	return (PT_Document*)m_pDocument;
}
#endif //_DEBUG


// PT_View message handlers
