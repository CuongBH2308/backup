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
#include "fw_toolbar.h"
#include "fw_cmd.h"
#include "fw_cmds.h"
#include "fw_cmdmanager.h"
#include "fw_uicmdbar.h"
#include "fw_uicmdbarctrls.h"
#include "fw_winapp.h"

IMPLEMENT_DYNAMIC(FW_ToolBar, CToolBar)
FW_ToolBar::FW_ToolBar(CWnd* pParent)
:m_pToolTipCtrl(NULL),
m_pImageList(NULL),
m_pImageListDisabled(NULL),
m_pImageListHot(NULL)
{
	CreateEx(pParent,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
}

FW_ToolBar::~FW_ToolBar()
{
	m_mToolTip.clear();

	if(m_pToolTipCtrl)
		delete m_pToolTipCtrl;
	if(m_pImageList)
		delete m_pImageList;
	if(m_pImageListDisabled)
		delete m_pImageListDisabled;
	if(m_pImageListHot)
		delete m_pImageListHot;
}


BEGIN_MESSAGE_MAP(FW_ToolBar, CToolBar)
END_MESSAGE_MAP()

// virtual 
BOOL FW_ToolBar::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	BOOL bOK = CToolBar::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
	if(!bOK)
	{
		switch(nCode)
		{
		case CN_COMMAND:
		case CN_UPDATE_COMMAND_UI:
			{
				FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetCmd(nID);
				if(pCmd)
					bOK = pCmd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
			}
			break;
		default:
			break;
		}
	}
	return bOK;
}


void FW_ToolBar::AdjustRows(int iWidth)
{
	CToolBarCtrl& tbCtrl = GetToolBarCtrl();
	int iCount = tbCtrl.GetButtonCount();

	int iRows = 1;
	int iRowWidth = 0;
	CRect rect;
	for(int i=0;i<iCount;i++)
	{
		tbCtrl.GetItemRect(i,&rect);
		iRowWidth += rect.Width();
		if(iRowWidth>iWidth)
		{
			iRowWidth = rect.Width();
			iRows++;
		}
	}
	tbCtrl.SetRows(iRows,FALSE,&rect);
}

// Show pUICmdBar
bool FW_ToolBar::Activate(FW_UICmdBar* pUICmdBar)
{
	BOOL bOK = FALSE;

	// Get CToolBarCtrl
	CToolBarCtrl& tbCtrl = GetToolBarCtrl();

	// Delete all buttons
	for(int i=tbCtrl.GetButtonCount()-1;i>=0;i--)
		tbCtrl.DeleteButton(i);

	// Delete image lists
	tbCtrl.SetImageList(NULL);
	tbCtrl.SetDisabledImageList(NULL);
	tbCtrl.SetHotImageList(NULL);
	if(m_pImageList)			m_pImageList->DeleteImageList();
	if(m_pImageListDisabled)	m_pImageListDisabled->DeleteImageList();
	if(m_pImageListHot)			m_pImageListHot->DeleteImageList();
	
	if(!pUICmdBar)
	{
		m_pUICmdBar = NULL;
		return false;
	}

	FW_UICmdBarCtrls* pUICmdBarCtrls = pUICmdBar->GetUICmdBarCtrls();
	if(!pUICmdBarCtrls)
		return false;

	if(!m_pToolTipCtrl)			
	{
		m_pToolTipCtrl = new CToolTipCtrl();
		if(m_pToolTipCtrl->Create(this))
			tbCtrl.SetToolTips(m_pToolTipCtrl);
	}


	int iCount = int(pUICmdBarCtrls->GetCount());
	if(!m_pImageList)			m_pImageList			= new CImageList();
	if(!m_pImageListDisabled)	m_pImageListDisabled	= new CImageList();
	if(!m_pImageListHot)		m_pImageListHot			= new CImageList();

	bOK = m_pImageList->Create(16,16,ILC_COLOR24|ILC_MASK,0,iCount);
	bOK = m_pImageListDisabled->Create(16,16,ILC_COLOR24|ILC_MASK,0,iCount);
	bOK = m_pImageListHot->Create(16,16,ILC_COLOR24|ILC_MASK,0,iCount);

	for(int i=0;i<iCount;i++)
	{
		CImageList* pImageListCmd = pUICmdBarCtrls->GetCmd(i)->GetImages();
		if(pImageListCmd->GetImageCount() == 3)
		{
			m_pImageList->Add(pImageListCmd->ExtractIcon(0));
			m_pImageListDisabled->Add(pImageListCmd->ExtractIcon(1));
			m_pImageListHot->Add(pImageListCmd->ExtractIcon(2));
		}
	}

	if(m_pImageList->GetSafeHandle())
	{
		m_pImageList->SetBkColor(CLR_NONE);
		CImageList* pImageListOld = tbCtrl.SetImageList(m_pImageList);
		if(pImageListOld)			
			delete pImageListOld;
	}

	if(m_pImageListDisabled->GetSafeHandle())
	{
		m_pImageListDisabled->SetBkColor(CLR_NONE);
		CImageList* pImageListDisabledOld = tbCtrl.SetDisabledImageList(m_pImageListDisabled);
		if(pImageListDisabledOld)	
			delete pImageListDisabledOld;
	}

	if(m_pImageListHot->GetSafeHandle())
	{
		m_pImageListHot->SetBkColor(CLR_NONE);
		CImageList* pImageListHotOld = tbCtrl.SetHotImageList(m_pImageListHot);
		if(pImageListHotOld)		
			delete pImageListHotOld;
	}

	TBBUTTON* pBtns = new TBBUTTON[iCount];
	if(!pBtns)
		return false;
	ZeroMemory(pBtns,sizeof(TBBUTTON)*iCount);

	m_mToolTip.clear();
	for(int i=0;i<iCount;i++)
	{
		pBtns[i].iBitmap = i;
		pBtns[i].idCommand = pUICmdBarCtrls->GetCmd(i)->GetCmdId();
		pBtns[i].fsState = TBSTATE_ENABLED;
		pBtns[i].fsStyle = TBSTYLE_BUTTON;
		pBtns[i].iString = -1; //Zero-based index of the string to use as the button's label, -1 if there is no string for this button
		m_mToolTip[pBtns[i].idCommand] = pUICmdBarCtrls->GetCmd(i)->GetTooltip();
	}
	tbCtrl.AddButtons(iCount,pBtns);
	delete [] pBtns;

	//for(int i=0;i<iCount;i++)
	//	SetButtonText(i,pUICmdBarCtrls->GetCmd(i)->GetDisplayName());

	m_pUICmdBar = pUICmdBar;
	return true;
}

// Get tool tip
CString FW_ToolBar::GetToolTip(UINT nCmdId)
{
	CString strToolTip;
	std::map<UINT,CString>::const_iterator it = m_mToolTip.find(nCmdId);
	if(it!=m_mToolTip.end())
		strToolTip = m_mToolTip[nCmdId];

	return strToolTip;
}

// Get active FW_UICmdBar
FW_UICmdBar* FW_ToolBar::GetActive()
{
	return m_pUICmdBar;
}

// Is command in this tool bar
bool FW_ToolBar::HasCmd(UINT nCmdId) const
{
	// Get CToolBarCtrl
	CToolBarCtrl& tbCtrl = GetToolBarCtrl();
	for(int i = 0; i<tbCtrl.GetButtonCount(); i++)
	{
		TBBUTTON btn;
		tbCtrl.GetButton(i, &btn);
		if(btn.idCommand == nCmdId)
			return true;
	}
	return false;
}