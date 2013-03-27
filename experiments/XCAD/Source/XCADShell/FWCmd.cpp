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
#include "fwcmd.h"
#include "..\fw_cmd.h"

CFWCmd::CFWCmd()
:m_pCmd(NULL)
{
}

HRESULT CFWCmd::FinalConstruct()
{
	return S_OK;
}

void CFWCmd::FinalRelease() 
{
	if(m_pCmd)
		m_pCmd->ResetInterface();
}

STDMETHODIMP CFWCmd::SetPrimary(unsigned char* pVal)
{
	m_pCmd = reinterpret_cast<FW_Cmd*>(pVal);
	return S_OK;
}

STDMETHODIMP CFWCmd::get_CmdId(int* pVal)
{
	HRESULT hr = S_OK;
	*pVal = -1;
	if(m_pCmd)
		*pVal = m_pCmd->GetCmdId();
	else
		hr = E_FAIL;
	return hr;
}
