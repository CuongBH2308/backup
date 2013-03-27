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
#include "fwuicmdbarctrls.h"
#include "..\fw_cmd.h"
#include "..\fw_cmdmanager.h"
#include "..\fw_cmds.h"
#include "..\fw_uicmdbarctrl.h"
#include "..\fw_uicmdbarctrls.h"
#include "..\fw_winapp.h"

CFWUICmdBarCtrls::CFWUICmdBarCtrls()
:m_pUICmdBarCtrls(NULL)
{
}

HRESULT CFWUICmdBarCtrls::FinalConstruct()
{
	return S_OK;
}

void CFWUICmdBarCtrls::FinalRelease() 
{
	if(m_pUICmdBarCtrls)
		m_pUICmdBarCtrls->ResetInterface();
}

STDMETHODIMP CFWUICmdBarCtrls::SetPrimary(unsigned char* pVal)
{
	m_pUICmdBarCtrls = reinterpret_cast<FW_UICmdBarCtrls*>(pVal);
	return S_OK;
}

// Associate a FW_UICmdBarCtrl with a command
STDMETHODIMP CFWUICmdBarCtrls::Add(IFWCmd* pIFWCmd, IFWUICmdBarCtrl* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	int iCmdId = -1;
	pIFWCmd->get_CmdId(&iCmdId);
	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetCmd(iCmdId);
	if(!pCmd)
		return E_FAIL;

	FW_UICmdBarCtrl* pUICmdBarCtrl = m_pUICmdBarCtrls->Add(pCmd);
	if(pUICmdBarCtrl)
		*ppVal = pUICmdBarCtrl->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	return S_OK;
}
