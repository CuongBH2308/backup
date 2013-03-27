// AddInSample.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "AddInSample.h"
#include <initguid.h>
#include "AddInSample_i.c"

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

// CAddInSampleApp


class CAddInSampleModule :
	public CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_AddInSampleLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ADDINSAMPLE, "{CA5721CD-5868-429C-ABD2-6A1BF13FDD08}");};

CAddInSampleModule _AtlModule;

BEGIN_MESSAGE_MAP(CAddInSampleApp, CWinApp)
END_MESSAGE_MAP()


// CAddInSampleApp 构造

CAddInSampleApp::CAddInSampleApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CAddInSampleApp 对象

CAddInSampleApp theApp;


// CAddInSampleApp 初始化

BOOL CAddInSampleApp::InitInstance()
{
	COleObjectFactory::RegisterAll();
	CWinApp::InitInstance();

	return TRUE;
}

// DllCanUnloadNow - Allows COM to unload DLL
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (_AtlModule.GetLockCount() > 0)
		return S_FALSE;
	return S_OK;
}

// DllGetClassObject - Returns class factory
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (S_OK == _AtlModule.GetClassObject(rclsid, riid, ppv))
		return S_OK;
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	_AtlModule.UpdateRegistryAppId(TRUE);
	HRESULT hRes = _AtlModule.RegisterServer(TRUE);
	if (hRes != S_OK)
		return hRes;
	if (!COleObjectFactory::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);
	return S_OK;
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	_AtlModule.UpdateRegistryAppId(FALSE);
	HRESULT hRes = _AtlModule.UnregisterServer(TRUE);
	if (hRes != S_OK)
		return hRes;
	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	return S_OK;
}
