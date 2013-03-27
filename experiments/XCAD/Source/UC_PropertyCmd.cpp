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
#include "uc_propertycmd.h"
#include "uc_propertydlg.h"
#include "fw_mdiframewnd.h"
#include "resource.h"

UC_PropertyCmd::UC_PropertyCmd(void)
:FW_Cmd(IDS_UC_PROPERTY_DISPNAME,
		IDS_UC_PROPERTY_TOOLTIP,
		IDB_UC_PROPERTY,
		_T("UC_PropertyCmd"), 
		IDR_UC_PROPERTY),
m_pPropertyDlg(NULL)
{
}

UC_PropertyCmd::~UC_PropertyCmd(void)
{
}

UC_PropertyCmd* UC_PropertyCmd::GetCmd()
{
	static UC_PropertyCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_PropertyCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_PropertyCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_PropertyCmd::OnExecute()
{
	// Execute basic function to terminate previous command
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	// UC_PropertyDlg will be created in the constructor
	m_pPropertyDlg = new UC_PropertyDlg(this, FW_MDIFrameWnd::GetMDIFrameWnd());
	if(m_pPropertyDlg)
		m_pPropertyDlg->ShowWindow(SW_SHOW);

	return TRUE;
}

// Some other command is activated, so this command will be terminated
// virtual 
BOOL UC_PropertyCmd::OnTerminate()
{
	// OnCancel will destroy the dialog and delete m_pPropertyDlg
	if(m_pPropertyDlg && m_pPropertyDlg->GetSafeHwnd())
	{
		// UC_PropertyDlg::PostNcDestroy will delete m_pPropertyDlg
		m_pPropertyDlg->DestroyWindow();
		m_pPropertyDlg = NULL;
	}

	FW_Cmd::OnTerminate();
	return TRUE;
}