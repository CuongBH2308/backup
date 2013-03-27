// AlgorithmCOM.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <objbase.h>
#include <initguid.h>
#include "AlgorithmCOM_i.c"
#include "AlgoFactory.h"
#include "Algorithm.h"


LONG g_cObjectAndLocks=0;
//standard self-registration table
const char * g_RegTable[][3]={
	{"CLSID\\{495FA11F-036E-4b49-834F-51566E89D00B}",0,"AlgorithmCOM"},
	{"CLSID\\{495FA11F-036E-4b49-834F-51566E89D00B}\\InprocServer32",0,(const char * )-1 /*表示文件名的值*/},
	{"CLSID\\{495FA11F-036E-4b49-834F-51566E89D00B}\\ProgID",0,"tulip.AlgorithmCOM.1"},
	{"tulip.AlgorithmCOM.1",0,"AlgorithmCOM"},
	{"tulip.AlgorithmCOM.1\\CLSID",0,"{495FA11F-036E-4b49-834F-51566E89D00B}"},
};

HINSTANCE  g_hinstDll;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	g_hinstDll=(HINSTANCE)hModule;
    return TRUE;
}

/*********************************************************************
 * Function Declare : DllUnregisterServer
 * Explain : self-unregistration routine
 * Parameters : 
 * void -- 
 * Return : 
 * STDAPI  -- 
 * Author : tulip 
 * Time : 2003-10-29 19:07:42 
*********************************************************************/
STDAPI DllUnregisterServer(void)
{
	HRESULT hr=S_OK;
	char szFileName [MAX_PATH];
	::GetModuleFileName(g_hinstDll,szFileName,MAX_PATH);

	int nEntries=sizeof(g_RegTable)/sizeof(*g_RegTable);
	for(int i =0;SUCCEEDED(hr)&&i<nEntries;i++)
	{
		const char * pszKeyName=g_RegTable[i][0];
		long err=::RegDeleteKey(HKEY_CLASSES_ROOT,pszKeyName);
		if(err!=ERROR_SUCCESS)
			hr=S_FALSE;
	}

	return hr;
}

/*********************************************************************
 * Function Declare : DllRegisterServer
 * Explain : self Registration routine
 * Parameters : 
 * void -- 
 * Return : 
 * STDAPI  -- 
 * Author : tulip 
 * Time : 2003-10-29 19:43:51 
*********************************************************************/
STDAPI DllRegisterServer(void)
{
	HRESULT hr=S_OK;
	char szFileName [MAX_PATH];
	::GetModuleFileName(g_hinstDll,szFileName,MAX_PATH);

	int nEntries=sizeof(g_RegTable)/sizeof(*g_RegTable);
	for(int i =0;SUCCEEDED(hr)&&i<nEntries;i++)
	{
		const char * pszKeyName=g_RegTable[i][0];
		const char * pszValueName=g_RegTable[i][1];
		const char * pszValue=g_RegTable[i][2];

		if(pszValue==(const char *)-1)
		{
			pszValue=szFileName;
		}

		HKEY hkey;
		long err=::RegCreateKey(HKEY_CLASSES_ROOT,pszKeyName,&hkey);
		if(err==ERROR_SUCCESS)
		{
			err=::RegSetValueEx(hkey,pszValueName,0,REG_SZ,(const BYTE*)pszValue,(strlen(pszValue)+1));
			::RegCloseKey(hkey);
		}
		if(err!=ERROR_SUCCESS)
		{
			::DllUnregisterServer();
			hr=E_FAIL;
		}

	}
   return hr;
}
						
/*********************************************************************
 * Function Declare : DllGetClassObject
 * Explain : 
 * Parameters : 
 * REFCLSID rclsid  -- 
 * REFIID riid -- 
 * void **ppv -- 
 * Return : 
 * STDAPI  -- 
 * Author : tulip 
 * Time : 2003-10-29 22:03:53 
 * Change by: Venture
*********************************************************************/
STDAPI DllGetClassObject(REFCLSID rclsid ,REFIID riid,void **ppv)
{
	//	changed by venture at 2003-11-12 23:15:00
	//	start
	if(rclsid==CLSID_AlgorithmCOM)
	{
		CAlgoFactory *pFactory = new CAlgoFactory;
		if(pFactory == NULL)
			return E_OUTOFMEMORY;

		HRESULT hr = pFactory->QueryInterface(riid, ppv);
		return hr;
	}
	//	end
	return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow(void)
{
	return (g_cObjectAndLocks==0)?S_OK:E_FAIL;
}

