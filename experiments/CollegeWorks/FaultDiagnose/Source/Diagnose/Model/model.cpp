// model.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f modelps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "model.h"

#include "model_i.c"
#include "MyCom1.h"
#include "MyCom2.h"
#include "MyCom3.h"
#include "MyCom4.h"
#include "MyCom5.h"
#include "MyCom6.h"
#include "MyCom11.h"
#include "MyCom12.h"
#include "MyLineCom.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_MyCom1, CMyCom1)
OBJECT_ENTRY(CLSID_MyCom2, CMyCom2)
OBJECT_ENTRY(CLSID_MyLineCom, CMyLineCom)
OBJECT_ENTRY(CLSID_MyCom11, CMyCom11)
OBJECT_ENTRY(CLSID_MyCom12, CMyCom12)
OBJECT_ENTRY(CLSID_MyCom3, CMyCom3)
OBJECT_ENTRY(CLSID_MyCom4, CMyCom4)
OBJECT_ENTRY(CLSID_MyCom5, CMyCom5)
OBJECT_ENTRY(CLSID_MyCom6, CMyCom6)
END_OBJECT_MAP()

class CModelApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CModelApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CModelApp, CWinApp)
	//{{AFX_MSG_MAP(CModelApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CModelApp theApp;

BOOL CModelApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_MODELLib);
    return CWinApp::InitInstance();
}

int CModelApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


#include "MyLineCom.h"

#include "MyCom11.h"
#include "MyCom12.h"
#include "MyCom3.h"
#include "MyCom4.h"
#include "MyCom5.h"
#include "MyCom6.h"
