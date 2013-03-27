// TipView.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "TipView.h"
#include "mainfrm.h"
#include "modelview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipView

IMPLEMENT_DYNCREATE(CTipView, CListView)

CTipView::CTipView()
{
}

CTipView::~CTipView()
{
}


BEGIN_MESSAGE_MAP(CTipView, CListView)
	//{{AFX_MSG_MAP(CTipView)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipView drawing

void CTipView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTipView diagnostics

#ifdef _DEBUG
void CTipView::AssertValid() const
{
	CListView::AssertValid();
}

void CTipView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTipView message handlers

void CTipView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	// get list
	CListCtrl& cThisList = GetListCtrl();
	cThisList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	// set up the grid column titles
	LPTSTR StrField[]={"步骤号", "运行结点", "推理类型","匹配规则序号","输出结点", "规则内容","诊断结论"};
	int collen;
	for(int i=0;i<7;i++)
	{
		switch(i)
		{
			case 0:	collen = 100; break;
			case 1:	collen = 100; break;
			case 2:	collen = 100; break;
			case 3:	collen = 100; break;
			case 4: collen = 100; break;
			case 5:	collen = 270; break;
			case 6:	collen = 250; break;
			
				
		}
		cThisList.InsertColumn(i, StrField[i], LVCFMT_LEFT, collen);
	}
	item_count=0;
}

void CTipView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListView::CalcWindowRect(lpClientRect, nAdjustType);
}

BOOL CTipView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	dwStyle	|=	LVS_REPORT|LVS_EDITLABELS|LVS_SINGLESEL;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

//在视图显示相应的item
void CTipView::DisplayItem(TipShowData curdata)
{
	CListCtrl& cThisList = GetListCtrl();
	CString str;
	LV_ITEM lvitem;

	// text and image
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE|LVIF_STATE;
	lvitem.state=0;
	lvitem.stateMask=LVIS_SELECTED ;
	lvitem.iImage=0;
	lvitem.iItem=item_count;
	lvitem.iSubItem=0;
	lvitem.pszText="";
	cThisList.InsertItem(&lvitem);

	str.Format("%ld",curdata.step_id);
	cThisList.SetItemText(item_count,0,str);
	cThisList.SetItemText(item_count,1,curdata.run_node_name);
	cThisList.SetItemText(item_count,2,curdata.diagnose_type);
	str.Format("%ld",curdata.match_rule_id);
	cThisList.SetItemText(item_count,3,str);
	cThisList.SetItemText(item_count,4,curdata.out_node_name);
	cThisList.SetItemText(item_count,5,curdata.rule_content);
	cThisList.SetItemText(item_count,6,curdata.diagnose_result);

	item_count++;
}

//清除视图中所有item
void CTipView::ClearTipData()
{
	CListCtrl& cThisList = GetListCtrl();
	item_count=0;
	cThisList.DeleteAllItems();
}

void CTipView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pFrm->SetActiveView(pView); //激活窗口
}


void CTipView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pFrm->SetActiveView(pView); //激活窗口
}
