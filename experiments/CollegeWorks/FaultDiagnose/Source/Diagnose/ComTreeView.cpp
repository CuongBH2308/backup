// ComTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "ComTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComTreeView

IMPLEMENT_DYNCREATE(CComTreeView, CTreeView)

CComTreeView::CComTreeView()
{
}

CComTreeView::~CComTreeView()
{
}


BEGIN_MESSAGE_MAP(CComTreeView, CTreeView)
	//{{AFX_MSG_MAP(CComTreeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComTreeView drawing

void CComTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CComTreeView diagnostics

#ifdef _DEBUG
void CComTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CComTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CComTreeView message handlers
