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
#include "fw_cmd.h"
#include "fw_cmds.h"
#include "fw_cmdmanager.h"
#include "fw_eventmanager.h"
#include "fw_mdiframewnd.h"
#include "fw_mouseevents.h"
#include "fw_view.h"
#include "fw_winapp.h"

IMPLEMENT_DYNAMIC(FW_Cmd,CCmdTarget)

FW_Cmd::FW_Cmd(UINT nDisplayName,
			   UINT nTooltip,
			   UINT nImages,
			   const CString& strInternalName,
			   const int& iCmdId)
:m_strInternalName(strInternalName),
m_iCmdId(iCmdId),
m_bActive(false),
m_pView(NULL),
m_pDoc(NULL)
{
	FW_Cmds* pCmds = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds();
	ASSERT(pCmds);
	pCmds->Add(this);

	m_strDisplayName.LoadString(nDisplayName);
	m_strTooltip.LoadString(nTooltip);
	m_imageList.Create(nImages,16,3,RGB(255,0,255));

	// If we have not specified the command id, generate one
	if(iCmdId==-1)
		m_iCmdId = pCmds->GenerateCmdId();

	// Create cmd object
	GetInterface();
}

// Once a command is new up, it will be added into FW_Cmds that will 
// manage the life cycle of this command
FW_Cmd::FW_Cmd(const CString& strDisplayName,
			   const CString& strTooltip,
			   CImageList& imageList,
			   const CString& strInternalName,
			   const int& iCmdId)
:m_strDisplayName(strDisplayName),
m_strTooltip(strTooltip),
m_strInternalName(strInternalName),
m_iCmdId(iCmdId),
m_bActive(false),
m_pView(NULL),
m_pDoc(NULL)
{
	FW_Cmds* pCmds = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds();
	ASSERT(pCmds);
	pCmds->Add(this);

	// Create an image list
	m_imageList.Create(&imageList);

	// If we have not specified the command id, generate one
	if(iCmdId==-1)
		m_iCmdId = pCmds->GenerateCmdId();

	// Create cmd object
	GetInterface();
}

FW_Cmd::~FW_Cmd(void)
{
}

// Get m_spIFWCmd;
CComPtr<IFWCmd> FW_Cmd::GetInterface()
{
	if(!m_spIFWCmd)
	{
		HRESULT hr = m_spIFWCmd.CoCreateInstance(CLSID_FWCmd,NULL,CLSCTX_INPROC_SERVER);
		if(SUCCEEDED(hr) && m_spIFWCmd)
			m_spIFWCmd->SetPrimary(reinterpret_cast<unsigned char*>(this));
	}
	return m_spIFWCmd;
}

// Set m_spIFWCmd to NULL
void FW_Cmd::ResetInterface()
{
	if(m_spIFWCmd)
		m_spIFWCmd.p = NULL;
}

BEGIN_MESSAGE_MAP(FW_Cmd,CCmdTarget)
END_MESSAGE_MAP()

// virtual 
BOOL FW_Cmd::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	BOOL bOK = CCmdTarget::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
	if(!bOK)
	{
		if(nID == GetCmdId())
		{
			switch(nCode)
			{
			case CN_COMMAND:
				{
					// pHandlerInfo!=NULL means it is checking whether the command should be enable,
					// otherwise the command is executed
					if(!pHandlerInfo)
					{
						if(!OnExecute())
							OnTerminate();
					}
					bOK = TRUE;
				}
				break;
			case CN_UPDATE_COMMAND_UI:
				{
					OnUpdateCmdUI((CCmdUI*)pExtra);
					bOK = TRUE;	// Enable the command
				}
				break;
			default:
				break;
			}
		}
	}
	return bOK;
}

// virtual 
BOOL FW_Cmd::OnExecute()
{
	// Terminate the previous active command
	FW_Cmds* pCmds = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds();
	ASSERT(pCmds);
	FW_Cmd* pCmd = pCmds->GetActiveCmd();
	if(pCmd)
		pCmd->OnTerminate();

	// Set this command as active command
	SetActive(true);

	// Get previous status
	m_strStatusPrev = FW_MDIFrameWnd::GetMDIFrameWnd()->GetStatus(0);

	// Set status
	FW_MDIFrameWnd::GetMDIFrameWnd()->SetStatus(0, GetTooltip());

	// Get active view
	m_pView = FW_MDIFrameWnd::GetActiveView();

	// Get active document
	m_pDoc	= FW_MDIFrameWnd::GetActiveDoc();

	return TRUE;
}

// Enable/Disable Check/Uncheck the button
// virtual 
BOOL FW_Cmd::OnUpdateCmdUI(CCmdUI* pCmdUI)
{
	if(m_bActive)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);

	return TRUE;
}

// Terminate the command. Such as when ESC is pressed
// virtual 
BOOL FW_Cmd::OnTerminate()
{
	SetActive(false);
	FW_MDIFrameWnd::GetMDIFrameWnd()->SetStatus(0, m_strStatusPrev);
	m_pView->Invalidate();
	return TRUE;
}

// MouseMove message
// virtual
void FW_Cmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	FW_WinApp::GetWinApp()->GetEventManager()->GetMouseEvents()->OnMove(pWnd->GetSafeHwnd(),
		nFlags,
		point);
}

// MouseMove message
// virtual
void FW_Cmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	//FW_WinApp::GetWinApp()->GetEventManager()->GetMouseEvents()->OnMove(pWnd->GetSafeHwnd(),
	//	nFlags,
	//	point);
}

// MouseMove message
// virtual
void FW_Cmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	//FW_WinApp::GetWinApp()->GetEventManager()->GetMouseEvents()->OnMove(pWnd->GetSafeHwnd(),
	//	nFlags,
	//	point);
}

// Right button message
// virtual
void FW_Cmd::OnRButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	//FW_WinApp::GetWinApp()->GetEventManager()->GetMouseEvents()->OnMove(pWnd->GetSafeHwnd(),
	//	nFlags,
	//	point);
}

// Right button message
// virtual
void FW_Cmd::OnRButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	//FW_WinApp::GetWinApp()->GetEventManager()->GetMouseEvents()->OnMove(pWnd->GetSafeHwnd(),
	//	nFlags,
	//	point);
}


// KeyDown message
// virtual 
void FW_Cmd::OnKeyDown(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_ESCAPE)
		OnTerminate();
}

// KeyDown message
// virtual 
void FW_Cmd::OnKeyUp(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void FW_Cmd::SetDisplayName(const CString& strDisplayName)
{
	m_strDisplayName = strDisplayName;
}

CString FW_Cmd::GetDisplayName()
{
	return m_strDisplayName;
}

void FW_Cmd::SetTooltip(const CString& strTooltip)
{
	m_strTooltip = strTooltip;
}

CString FW_Cmd::GetTooltip()
{
	return m_strTooltip;
}

void FW_Cmd::SetInternalName(const CString& strInternalName)
{
	m_strInternalName = strInternalName;
}

CString FW_Cmd::GetInternalName() const
{
	return m_strInternalName;
}

void FW_Cmd::SetCmdId(const int& iCmdId)
{
	m_iCmdId = iCmdId;
}

int FW_Cmd::GetCmdId() const
{
	return m_iCmdId;
}

void FW_Cmd::SetState(const UINT& nState)
{
	m_nState = nState;
}

UINT FW_Cmd::GetState() const
{
	return m_nState;
}

void FW_Cmd::SetImages(CImageList& imageList)
{
	m_imageList.Create(&imageList);
}

CImageList* FW_Cmd::GetImages()
{
	return &m_imageList;
}

void FW_Cmd::SetActive(bool bActive)
{
	m_bActive = bActive;
}

bool FW_Cmd::GetActive() const
{
	return m_bActive;
}

FW_View* FW_Cmd::GetView() const
{
	return m_pView;
}

FW_Document* FW_Cmd::GetDocument() const
{
	return m_pDoc;
}

