// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Diagnose.h"

#include "MainFrm.h"

#include "DiagnoseDoc.h"
#include "DiagnoseView.h"
#include "ModelView.h"
#include "TipView.h"
#include "modeltree.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_HELP_TOPIC, OnHelpTopic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect rect(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	size1.cx = rect.Width()/6;
	size1.cy = 4*rect.Height()/5-100;
	size3.cx = rect.Width()/5;
	size3.cy = size1.cy;

	size2.cx =rect.Width()-size1.cx-size3.cx;;
	size2.cy = size1.cy;

	size4.cx = rect.Width();
	size4.cy = rect.Height()-size1.cy;

	if (m_wndSplitter3.CreateStatic(this,2,1, WS_CHILD|WS_VISIBLE))
	{
		m_wndSplitter3.SetRowInfo(0, rect.Height()-size4.cy, 10);
		if (m_wndSplitter3.CreateView(1,0,RUNTIME_CLASS(CTipView),size4,pContext))
		{
			//pContext1=pContext;
			if(m_wndSplitter1.CreateStatic(&m_wndSplitter3,1,3,WS_CHILD|WS_VISIBLE,m_wndSplitter3.IdFromRowCol(0,0)))	//m_wndSplitter3.GetWindow(GW_HWNDLAST)
				if (m_wndSplitter1.CreateView(0,0,RUNTIME_CLASS(CDiagnoseView),size1,pContext))
					if (m_wndSplitter1.CreateView(0,1,RUNTIME_CLASS(CModelView),size2,pContext))	//RUNTIME_CLASS(CModelView)
						if (m_wndSplitter1.CreateView(0,2,RUNTIME_CLASS(CModelTree),size3,pContext))	//RUNTIME_CLASS(CModelTree)
						{
							//m_wndSplitter1.SetRowInfo(0, rect.Height()-size4.cy, 10);
							m_wndSplitter1.SetColumnInfo(0, size1.cx, 30);
							m_wndSplitter1.SetColumnInfo(1, size2.cx, 30);
							m_wndSplitter1.SetColumnInfo(2, size3.cx, 30);
							m_wndSplitter1.RecalcLayout();
							m_wndSplitter3.RecalcLayout();
							return TRUE;
						}
		}
	}

	return FALSE;
}

void CMainFrame::OnHelpTopic() 
{
	// TODO: Add your command handler code here
	ShellExecute(NULL,NULL,"诊断运行界面.chm","","",SW_SHOW);
}
