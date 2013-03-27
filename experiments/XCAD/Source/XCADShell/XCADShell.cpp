#include "stdafx.h"
#include "xcadshell.h"
#include <initguid.h>
#include "xcadshell_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CXCADShellApp


class CXCADShellModule : public CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_XCADShell);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_XCADSHELL, "{4C328C7E-2AEF-4701-BF54-CCAA3F2135CF}");
};

CXCADShellModule _AtlModule;

BEGIN_MESSAGE_MAP(CXCADShellApp, CWinApp)
END_MESSAGE_MAP()

CXCADShellApp::CXCADShellApp()
{
}

CXCADShellApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x693A6269, 0x9D47, 0x43B3, { 0x92, 0xA1, 0xEE, 0xA2, 0xB5, 0x2C, 0xF5, 0x4E } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


BOOL CXCADShellApp::InitInstance()
{
	CWinApp::InitInstance();

	// 将所有 OLE 服务器(工厂)注册为运行。这将使
	//  OLE 库得以从其他应用程序创建对象。
	COleObjectFactory::RegisterAll();

	CString strModuleName;
	CComPtr<ITypeLib> spTLib;
	HRESULT hr = E_FAIL;
	if(GetModuleFileName(NULL, strModuleName.GetBuffer(_MAX_PATH), _MAX_PATH))
	{
		strModuleName.ReleaseBuffer();
		if(SUCCEEDED(hr = LoadTypeLib(strModuleName.AllocSysString(), &spTLib)))
		{
			hr = RegisterTypeLib(spTLib, strModuleName.AllocSysString(), NULL);
			ASSERT(SUCCEEDED(hr));
		}

		ITypeLib* pTypeLib = NULL;
		hr = LoadRegTypeLib(LIBID_XCADShell, 1, 0, 0x400, &pTypeLib);
	}

	return TRUE;
}


// DllGetClassObject - 返回类工厂

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if (S_OK == _AtlModule.GetClassObject(rclsid, riid, ppv))
		return S_OK;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - 允许 COM 卸载 DLL

#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")

STDAPI DllCanUnloadNow(void)
{
	if (_AtlModule.GetLockCount() > 0)
		return S_FALSE;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	_AtlModule.UpdateRegistryAppId(TRUE);
	HRESULT hRes = _AtlModule.RegisterServer(TRUE);
	if (hRes != S_OK)
		return hRes;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;
	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;
 
	return S_OK;
}


// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	_AtlModule.UpdateRegistryAppId(FALSE);
	HRESULT hRes = _AtlModule.UnregisterServer(TRUE);
	if (hRes != S_OK)
		return hRes;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}
