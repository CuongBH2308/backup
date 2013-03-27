// DiagnoseView.cpp : implementation of the CDiagnoseView class
//

#include "stdafx.h"
#include "Diagnose.h"
#include "mainfrm.h"
#include "modelview.h"
#include "DiagnoseDoc.h"
#include "DiagnoseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseView

IMPLEMENT_DYNCREATE(CDiagnoseView, CFormView)

BEGIN_MESSAGE_MAP(CDiagnoseView, CFormView)
	//{{AFX_MSG_MAP(CDiagnoseView)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_DATA, OnData)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_ONESTEP, OnOnestep)
	ON_BN_CLICKED(IDC_CONTINUE, OnContinue)
	ON_BN_CLICKED(IDC_OUT, OnOut)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseView construction/destruction

CDiagnoseView::CDiagnoseView()
	: CFormView(CDiagnoseView::IDD)
{
	//{{AFX_DATA_INIT(CDiagnoseView)
	m_nodename = _T("");
	m_compname = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDiagnoseView::~CDiagnoseView()
{
}

void CDiagnoseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagnoseView)
	DDX_Text(pDX, IDC_NODENAME, m_nodename);
	DDX_Text(pDX, IDC_COMPNAME, m_compname);
	//}}AFX_DATA_MAP
}

BOOL CDiagnoseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CDiagnoseView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseView printing

BOOL CDiagnoseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDiagnoseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDiagnoseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDiagnoseView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseView diagnostics

#ifdef _DEBUG
void CDiagnoseView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDiagnoseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDiagnoseDoc* CDiagnoseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiagnoseDoc)));
	return (CDiagnoseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseView message handlers

HBRUSH CDiagnoseView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	switch (nCtlColor) 
	{ 

		case CTLCOLOR_BTN: 
		case CTLCOLOR_STATIC: 
		{ 

			pDC->SetBkMode(TRANSPARENT); 
		} 
		case CTLCOLOR_DLG: 
		{ 

			CBrush* back_brush; 
		//	COLORREF color(255,0,0); 
			//color = (COLORREF) GetSysColor(COLOR_BTNFACE); 
			back_brush = new CBrush(RGB(255,255,255)); 
			return (HBRUSH) (back_brush->m_hObject);

		}

	} 

	return hbr;
}

//DEL void CDiagnoseView::ShowBim(CPoint &point, float fscale)
//DEL {
//DEL 
//DEL }

void ActiveModelView()
{
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pFrm->SetActiveView(pView); //¼¤»î´°¿Ú
}

void CDiagnoseView::OnData() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pView->ShowData();

	ActiveModelView();
}

void CDiagnoseView::OnRun() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pView->ReasonAll();

	ActiveModelView();
}

void CDiagnoseView::OnOnestep() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pView->ReasonOnestep();

	ActiveModelView();
}

void CDiagnoseView::OnContinue() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pView->ContinueReason();

	ActiveModelView();
}

void CDiagnoseView::OnOut() 
{
	// TODO: Add your control notification handler code here
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pView->ReportOut();	

	ActiveModelView();
}

void CDiagnoseView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ActiveModelView();
}

void CDiagnoseView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ActiveModelView();
}
