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
#include "fwcmds.h"
#include "..\fw_winapp.h"
#include "..\fw_cmdmanager.h"
#include "..\fw_cmds.h"
#include "..\fw_cmd.h"

CFWCmds::CFWCmds()
:m_pCmds(NULL)
{
}

HRESULT CFWCmds::FinalConstruct()
{
	m_pCmds = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds();
	return S_OK;
}

void CFWCmds::FinalRelease() 
{
	if(m_pCmds)
		m_pCmds->ResetInterface();
}

STDMETHODIMP CFWCmds::Add(BSTR bstrDisplayName, 
						  BSTR bstrTooltip,
						  BSTR bstrInternalName,
						  IPictureDisp* pPictureDispEnable,
						  IPictureDisp* pPictureDispDisable,
						  IPictureDisp* pPictureDispHot,
						  IFWCmd* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;
	CComQIPtr<IPicture> spEnable = pPictureDispEnable;
	CComQIPtr<IPicture> spDisable = pPictureDispDisable;
	CComQIPtr<IPicture> spHot = pPictureDispHot;

	CImageList imageList;
	OLE_HANDLE hEnable = NULL, hDisable = NULL, hHot = NULL;
	if(spEnable)
		spEnable->get_Handle(&hEnable);
	if(spDisable)
		spDisable->get_Handle(&hDisable);
	if(spHot)
		spHot->get_Handle(&hHot);

	BOOL bOK = imageList.Create(16, 16, ILC_COLOR24|ILC_MASK, 0, 3);
	if(bOK)
	{
		if(hEnable)
		{
			CBitmap bmp;
			bmp.Attach((HGDIOBJ)hEnable);
			imageList.Add(&bmp,RGB(255,0,255));
			bmp.Detach();
		}
		if(hDisable && imageList.GetImageCount()==1)
		{
			CBitmap bmp;
			bmp.Attach((HGDIOBJ)hDisable);
			imageList.Add(&bmp,RGB(255,0,255));
			bmp.Detach();
		}
		if(hHot && imageList.GetImageCount()==2)
		{
			CBitmap bmp;
			bmp.Attach((HGDIOBJ)hHot);
			imageList.Add(&bmp,RGB(255,0,255));
			bmp.Detach();
		}
	}

	FW_Cmd* pCmd = m_pCmds->Add(CString(bstrDisplayName),
		CString(bstrTooltip),
		imageList,
		CString(bstrInternalName));

	if(pCmd)
		*ppVal = pCmd->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;
	return S_OK;
}