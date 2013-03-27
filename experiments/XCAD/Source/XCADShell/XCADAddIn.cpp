#include "stdafx.h"
#include "xcadaddin.h"

STDMETHODIMP CXCADAddIn::Initialize(IFWWinApp* pApp, VARIANT_BOOL bFirstTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CXCADAddIn::Uninitialize(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}
