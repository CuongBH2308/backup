// ModelTree.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "MainFrm.h"

#include "ModelView.h"
#include "ModelTree.h"
#include "DiagnoseDoc.h"
#include "DiagnoseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelTree

IMPLEMENT_DYNCREATE(CModelTree, CTreeView)
CModelTree * pModelView = NULL;

CModelTree::CModelTree()
{
	m_TreeView = &GetTreeCtrl();
}

CModelTree::~CModelTree()
{
}


BEGIN_MESSAGE_MAP(CModelTree, CTreeView)
	//{{AFX_MSG_MAP(CModelTree)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelTree drawing

void CModelTree::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pModelView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CModelTree diagnostics

#ifdef _DEBUG
void CModelTree::AssertValid() const
{
	CTreeView::AssertValid();
}

void CModelTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModelTree message handlers

void CModelTree::AddBitmap(UINT nIDResource) 
{
	CBitmap bitmap;
	bitmap.LoadBitmap(nIDResource);
	m_pImageList->Add( &bitmap, (COLORREF)0xFFFFFF);
	bitmap.DeleteObject();
}

void CModelTree::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CTreeCtrl& m_ctlTree = GetTreeCtrl();
	m_ctlTree.ModifyStyle(TVS_EDITLABELS, TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_DISABLEDRAGDROP);

	//???ImageList的次序：virtual root、com1, com2...的顺序放
	CBitmap bitmap;
	m_pImageList = new CImageList;
	// 16x16 pixels, 8 of them
	m_pImageList->Create(16, 16, TRUE, 1, 4);

	//根
	AddBitmap(IDB_ROOT);
	AddBitmap(IDB_ROOT);
	//com1
	AddBitmap(IDB_COM1);
	AddBitmap(IDB_COM1);
	//com2
	AddBitmap(IDB_COM2);
	AddBitmap(IDB_COM2);
	//com3
	AddBitmap(IDB_COM3);
	AddBitmap(IDB_COM3);
	//com4
	AddBitmap(IDB_COM4);
	AddBitmap(IDB_COM4);
	//com5
	AddBitmap(IDB_COM5);
	AddBitmap(IDB_COM5);
	//com6
	AddBitmap(IDB_COM6);
	AddBitmap(IDB_COM6);
	//com7
	AddBitmap(IDB_FILE);
	AddBitmap(IDB_FILEOPEN);
	//com8
	AddBitmap(IDB_FILE);
	AddBitmap(IDB_FILEOPEN);
	//com9
	AddBitmap(IDB_FILE);
	AddBitmap(IDB_FILEOPEN);

	m_ctlTree.SetImageList(m_pImageList, TVSIL_NORMAL );
	//HTREEITEM RootItem;
	m_Tree.root = m_ctlTree.InsertItem(_T("VIRTUAL ROOT"),0,1, 0, TVI_ROOT);
}

void CModelTree::ExpandAll(HTREEITEM root_item) 
{
	HTREEITEM Item;
	CTreeCtrl& m_ctlTree = GetTreeCtrl();
	
	m_ctlTree.Expand(root_item,TVE_EXPAND);
	Item=m_ctlTree.GetChildItem(root_item);
	while (Item!=NULL)
	{
		ExpandAll(Item);
		Item=m_ctlTree.GetNextItem(Item,TVGN_NEXT);
	}
}

int CModelTree::Get_No_In_TreeItem(HTREEITEM item, int itemcount)
{
	int i;
	for (i=0; i<itemcount;i++)
		if (m_Tree.TreeItem[i]==item)
			return i;
	return -1;
}

void CModelTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl& m_ctlTree = GetTreeCtrl();
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelView * pModelView = (CModelView *)pFWnd->m_wndSplitter1.GetPane(0,1);
	CDiagnoseView *pDiagnose = (CDiagnoseView *)pFWnd->m_wndSplitter1.GetPane(0,0);

	int no=Get_No_In_TreeItem(m_ctlTree.GetSelectedItem(),m_ctlTree.GetCount()-1);
	if (no!=-1)
	{
		Node *pNode=m_Tree.NodeArray.GetAt(no);

		//修改diagnoseview
		pDiagnose->m_nodename=pNode->GetName();
		pDiagnose->m_compname=pNode->rgnName;
		pDiagnose->UpdateData(false);

		//修改modelview
		int count = pModelView->SelectedObjects.GetSize();
		for (int i=0; i<count; i++)
			pModelView->SelectedObjects.GetAt(i)->SetActive(FALSE);
		pModelView->SelectedObjects.RemoveAll();
		pModelView->SelectedObjects.Add(pNode);
		pModelView->curObject=pNode;
		pNode->SetActive(TRUE);
		CPoint topleft = pNode->GetTopLeft();
		if ( !(topleft.x >= 0 && topleft.y >= 0) )
		{
			CPoint scrollpos = topleft+pNode->GetScrPos()-CPoint(100, 100);
			pModelView->SetScrollPos(SB_VERT, scrollpos.y, TRUE);
			pModelView->SetScrollPos(SB_HORZ, scrollpos.x, TRUE);
			pModelView->scrollpos = scrollpos;
		}
		pModelView->Invalidate(TRUE);
	}
	pFWnd->SetActiveView(pModelView); //激活窗口
	//CTreeView::OnLButtonUp(nFlags, point);
}
