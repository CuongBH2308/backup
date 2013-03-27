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
#include "fw_addins.h"
#include "fw_addin.h"
#include "fw_winapp.h"

FW_AddIns::FW_AddIns(FW_AddInManager* pAddInManager)
:m_pAddInManager(pAddInManager)
{
}

FW_AddIns::~FW_AddIns(void)
{
	for(std::vector<FW_AddIn*>::iterator it=m_vAddIn.begin();it!=m_vAddIn.end();it++)
		delete (*it);

	m_vAddIn.clear();
}

FW_AddIn* FW_AddIns::Add(const CLSID& clsidAddInServer)
{
	CComPtr<IXCADAddIn> spXCADAddIn;
	HRESULT hr = spXCADAddIn.CoCreateInstance(clsidAddInServer,NULL,CLSCTX_INPROC_SERVER);
	if(FAILED(hr))
		return NULL;

	CComPtr<IFWWinApp> spIFWWinApp = FW_WinApp::GetWinApp()->GetInterface();
	hr = spXCADAddIn->Initialize(spIFWWinApp,VARIANT_TRUE);
	if(FAILED(hr))
	{
		spXCADAddIn = NULL;
		return NULL;
	}

	FW_AddIn* pAddIn = new FW_AddIn(this,spXCADAddIn);
	if(!pAddIn)
	{
		spXCADAddIn->Uninitialize();
		spXCADAddIn = NULL;
		return NULL;
	}

	m_vAddIn.push_back(pAddIn);
	return pAddIn;
}
