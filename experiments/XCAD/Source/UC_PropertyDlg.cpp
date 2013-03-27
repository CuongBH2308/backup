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
#include "uc_propertydlg.h"
#include <typeinfo.h>
#include "fw_cmd.h"
#include "fw_mdiframewnd.h"
#include "fw_propertysheet.h"
#include "fw_view.h"
#include "uc_propertypagepoint.h"
#include "uc_propertypagecurve.h"
#include "uc_propertypagesurface.h"
#include "gr_dlnode.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "gr_dlsrf.h"

IMPLEMENT_DYNAMIC(UC_PropertyDlg, FW_Dialog)
UC_PropertyDlg::UC_PropertyDlg(FW_Cmd* pCmd, CWnd* pParent /*=NULL*/)
: FW_Dialog(UC_PropertyDlg::IDD, pParent),
m_pPropertySheet(NULL),
m_pPagePoint(NULL),
m_pPageCurve(NULL),
m_pPageSurface(NULL),
m_pCmd(pCmd)
{
	Create(UC_PropertyDlg::IDD, pParent);
}

UC_PropertyDlg::~UC_PropertyDlg()
{
	if(m_pPropertySheet)
		delete m_pPropertySheet;
	if(m_pPagePoint)
		delete m_pPagePoint;
	if(m_pPageCurve)
		delete m_pPageCurve;
	if(m_pPageSurface)
		delete m_pPageSurface;
}

void UC_PropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	FW_Dialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UC_PROPERTY_TREE, m_tree);
}

BEGIN_MESSAGE_MAP(UC_PropertyDlg, FW_Dialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_UC_PROPERTY_TREE, TreeNodeSelected)
END_MESSAGE_MAP()

BOOL UC_PropertyDlg::OnInitDialog()
{
	FW_Dialog::OnInitDialog();

	m_pPropertySheet	= new FW_PropertySheet();
	m_pPagePoint		= new UC_PropertyPagePoint();
	m_pPageCurve		= new UC_PropertyPageCurve();
	m_pPageSurface		= new UC_PropertyPageSurface();
	m_pPropertySheet->AddPage(m_pPagePoint);
	m_pPropertySheet->AddPage(m_pPageCurve);
	m_pPropertySheet->AddPage(m_pPageSurface);

	// create a mode-less property page
	if (!m_pPropertySheet->Create(this, DS_SETFONT | WS_CHILD | WS_VISIBLE))
	{
		DestroyWindow();
		return FALSE;
	}

	CRect rc;
	GetDlgItem(IDC_UC_PROPERTY_SHEET_RECT)->GetWindowRect(rc);
	ScreenToClient(&rc);
	m_pPropertySheet->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

	BuildTree();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// virtual 
void UC_PropertyDlg::OnOK()
{
	// Apply the setting
	OnApply();

	ASSERT(m_pCmd);
	// UC_PropertyCmd::OnTerminate will destroy the window
	m_pCmd->OnTerminate();
}

// virtual 
void UC_PropertyDlg::OnCancel()
{
	ASSERT(m_pCmd);
	// UC_PropertyCmd::OnTerminate will destroy the window
	m_pCmd->OnTerminate();
}

void UC_PropertyDlg::OnApply()
{
	if(m_pPagePoint)
		m_pPagePoint->OnApply();
	if(m_pPageCurve)
		m_pPageCurve->OnApply();
	if(m_pPageSurface)
		m_pPageSurface->OnApply();

	FW_MDIFrameWnd::GetMDIFrameWnd()->UpdateActiveView();
}

// virtual 
void UC_PropertyDlg::PostNcDestroy()
{
	delete this;
}

BOOL UC_PropertyDlg::BuildTree()
{
	CFrameWnd* pChildFrameWnd = FW_MDIFrameWnd::GetMDIFrameWnd()->GetActiveFrame();
	if(!pChildFrameWnd)
		return FALSE;

	CMDIChildWnd* pChild = dynamic_cast<CMDIChildWnd*>(pChildFrameWnd);
	if(!pChild)
		return FALSE;

	CView* pCView = pChild->GetActiveView();
	if(!pCView)
		return FALSE;

	FW_View* pView = dynamic_cast<FW_View*>(pCView);
	if(!pView)
		return FALSE;

	GR_DLNode* pDLNode = pView->GetDLNode();
	if(!pDLNode)
		return FALSE;

	HTREEITEM hRoot = m_tree.InsertItem(CString(typeid(*pDLNode).name()).TrimLeft("class "));
	m_tree.SetItemData(hRoot, DWORD_PTR(pDLNode));
	AddChildren(hRoot, pDLNode);

	return TRUE;
}

BOOL UC_PropertyDlg::AddChildren(HTREEITEM hItem, const SL_Ptr<GR_DLNode>& pDLNode)
{
	if(!hItem || !pDLNode.GetTarget())
		return TRUE;

	GR_DLNodePtrVect* pvDLNode = NULL;
	GR_DLPtrVect* pvDL = NULL;
	pDLNode->GetChildren(pvDLNode, pvDL);

	if(pvDLNode)
	{
		for(GR_DLNodePtrVect::iterator itDLNode = pvDLNode->begin(); itDLNode != pvDLNode->end(); itDLNode++)
		{
			HTREEITEM h = m_tree.InsertItem(CString(typeid(**itDLNode).name()).TrimLeft("class "), hItem);
			m_tree.SetItemData(h, DWORD_PTR((*itDLNode).GetTarget()));
			AddChildren(h, *itDLNode);
		}
	}

	if(pvDL)
	{
		for(GR_DLPtrVect::iterator itDL = pvDL->begin(); itDL != pvDL->end(); itDL++)
		{
			HTREEITEM h = m_tree.InsertItem(CString(typeid(**itDL).name()).TrimLeft("class "), hItem);
			m_tree.SetItemData(h, DWORD_PTR((*itDL).GetTarget()));
		}
	}

	return TRUE;
}

void UC_PropertyDlg::TreeNodeSelected(LPNMHDR pnmhdr, LRESULT* pLResult)
{
	LPNMTREEVIEW pnmtv = (LPNMTREEVIEW) pnmhdr;
	*pLResult = NULL;

	if(pnmtv && pnmtv->itemNew.hItem)
	{
		DWORD_PTR data = m_tree.GetItemData(pnmtv->itemNew.hItem);
		if(data)
		{
			GR_DL* pObj = reinterpret_cast<GR_DL*>(data);
			GR_DLPoint* pDLPoint = dynamic_cast<GR_DLPoint*>(pObj);
			GR_DLCrv* pDLCrv = dynamic_cast<GR_DLCrv*>(pObj);
			GR_DLSrf* pDLSrf = dynamic_cast<GR_DLSrf*>(pObj);

			if(pDLPoint)
				m_pPropertySheet->SetActivePage(m_pPagePoint);
			else if(pDLCrv)
				m_pPropertySheet->SetActivePage(m_pPageCurve);
			else if(pDLSrf)
				m_pPropertySheet->SetActivePage(m_pPageSurface);

			if(m_pPagePoint)
			{
				m_pPagePoint->SetObj(pObj);
				m_pPageCurve->SetObj(NULL);
				m_pPageSurface->SetObj(NULL);
			}
			if(m_pPageCurve)
			{
				m_pPagePoint->SetObj(NULL);
				m_pPageCurve->SetObj(pObj);
				m_pPageSurface->SetObj(NULL);
			}
			if(m_pPageSurface)
			{
				m_pPagePoint->SetObj(NULL);
				m_pPageCurve->SetObj(NULL);
				m_pPageSurface->SetObj(pObj);
			}
		}
	}
}



