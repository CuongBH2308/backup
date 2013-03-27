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
#include "fw_winapp.h"
#include <evalkey.h>
#include "fw_mdiframewnd.h"
#include "fw_docmanager.h"
#include "fw_multidoctemplate.h"
#include "fw_addinmanager.h"
#include "fw_uimanager.h"
#include "fw_cmdmanager.h"
#include "fw_eventmanager.h"
#include "fw_environmentmanager.h"
#include "fw_oleipframewnd.h"
#include "mm_manager.h"
#include "pt_mdichildwnd.h"
#include "pt_document.h"
#include "pt_view.h"

// We should add the idl file of XCADShell.idl to this project.
// The compile of this idl will generate this header file
#include "xcadshell_h.h"
#include "xcadshell_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LICENSEKEY    wszEvalLicKey
#define FILTER "All Reference Files (*.mpad,*.tlb,*.olb,*.dll,*.exe,*.ocx)\0*.mpad;*.tlb;*.olb;*.dll;*.exe;*.ocx\0Documents (*.mpad)\0*.mpad\0"

FW_Module _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

LONG FW_Module::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG FW_Module::Lock()
{
	AfxOleLockApp();
	return 1;
}

BEGIN_MESSAGE_MAP(FW_WinApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

FW_WinApp::FW_WinApp()
: m_bCloseFrame(FALSE),
m_spIFWWinApp(NULL),
m_pAddInManager(NULL),
m_pUIManager(NULL),
m_pCmdManager(NULL),
m_pEventManager(NULL),
m_pEnvironmentManager(NULL)
{
}

FW_WinApp::~FW_WinApp()
{
}

// The one and only FW_WinApp object

FW_WinApp theApp;
// This identifier was generated to be statistically unique for your app
// You may change it if you prefer to choose a specific identifier

// {90FEFA6F-7CF9-40DD-A894-E985C24C5CE6}
static const CLSID clsid =
{ 0x90FEFA6F, 0x7CF9, 0x40DD, { 0xA8, 0x94, 0xE9, 0x85, 0xC2, 0x4C, 0x5C, 0xE6 } };
const GUID CDECL BASED_CODE _tlid =
		{ 0x1582B9D0, 0x5B4D, 0x44C5, { 0xBB, 0x48, 0x99, 0x16, 0xF4, 0x9B, 0x9, 0xA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

FW_WinApp* FW_WinApp::GetWinApp()
{
	return &theApp;
}

// Get m_spFWWinApp;
CComPtr<IFWWinApp> FW_WinApp::GetInterface()
{
	if(!m_spIFWWinApp)
	{
		HRESULT hr = m_spIFWWinApp.CoCreateInstance(CLSID_FWWinApp,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWWinApp;
}

// Set m_spIFWWinApp to NULL
void FW_WinApp::ResetInterface()
{
	if(m_spIFWWinApp)
		m_spIFWWinApp.p = NULL;
}

// Get m_spIFWDocuments;
CComPtr<IFWDocuments> FW_WinApp::GetDocsInterface()
{
	if(!m_spIFWDocuments)
	{
		HRESULT hr = m_spIFWDocuments.CoCreateInstance(CLSID_FWDocuments,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWDocuments;
}

// Set m_spIFWDocuments to NULL
void FW_WinApp::ResetDocsInterface()
{
	if(m_spIFWDocuments)
		m_spIFWDocuments.p = NULL;
}

// Set the value of m_bCloseFrame
void FW_WinApp::SetCloseFrame(BOOL bCloseFrame)
{
	m_bCloseFrame = bCloseFrame;
}

// Get the value of m_bCloseFrame
BOOL FW_WinApp::GetCloseFrame() const
{
	return m_bCloseFrame;
}

// FW_WinApp initialization
BOOL FW_WinApp::InitInstance()
{
	if (!ApcOleInit())
		return FALSE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	// Call basic initialize function
	CWinApp::InitInstance();

	// Create AddIn Manager
	GetAddInManager();

	// Enable support for containment of OLE controls.
	AfxEnableControlContainer();

	// The registry key under which our settings are stored
	SetRegistryKey(_T("XZH\\XCAD"));

	// Enable and load the list of most recently used (MRU) files and last preview state
	LoadStdProfileSettings(4);

	// Create doc manager
	m_pDocManager = new FW_DocManager();
	if(!m_pDocManager)
		return FALSE;

	FW_MultiDocTemplate* pDocTemplate;
	pDocTemplate = new FW_MultiDocTemplate(IDR_XCADTYPE,
		RUNTIME_CLASS(PT_Document),
		RUNTIME_CLASS(PT_MDIChildWnd), // custom MDI child frame
		RUNTIME_CLASS(PT_View));
	if (!pDocTemplate)
		return FALSE;

	pDocTemplate->SetServerInfo(
		IDR_XCADTYPE, IDR_XCADTYPE,
		RUNTIME_CLASS(FW_OleIPFrameWnd), RUNTIME_CLASS(PT_View));

	// This method adds a document template to the list of available document templates that the application maintains
	// should add all document templates to an application before you call RegisterShellFileTypes
	AddDocTemplate(pDocTemplate);

	// Connects the document template pointed to by pDocTemplate to the underlying COleObjectFactory object
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Registers all of the application's object factories with the system DLLs
	COleTemplateServer::RegisterAll();

	// create main MDI Frame window
	FW_MDIFrameWnd* pMainFrame = new FW_MDIFrameWnd;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

    // CreateAPCHost
	GetInterface();
	if(!m_spIFWWinApp)
		return FALSE;

	static int nVBALanguage = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), SORT_DEFAULT);
	HRESULT hr = ApcHost.Create(pMainFrame->m_hWnd, 
		CComBSTR(m_pszAppName),
		m_spIFWWinApp,
		CComBSTR(LICENSEKEY),
		nVBALanguage);
	if(FAILED(hr))
		return FALSE;
	 //End CreateAPCHost

	// Set the flag
	m_bCloseFrame = FALSE;

	// call DragAcceptFiles only if there's a suffix
	// In an MDI app, this should occur immediately after setting m_pMainWnd
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Run with switch /Embedding or /Automation.
	// Run as automation server.
	// Not show main window
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
		return TRUE;

	// Run with switch /Unregserver »ò /Unregister.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
		m_server.UpdateRegistry(OAT_INPLACE_SERVER, NULL, NULL, FALSE);

	// Run with standalone (or /Register, /Regserver)
	else
		m_server.UpdateRegistry(OAT_INPLACE_SERVER);

	// Enable open data files when double-clicking the files within the Windows File Manager.
	EnableShellOpen();

	// Registration of document types that will be open by this application
	RegisterShellFileTypes(TRUE);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Show the main window
	pMainFrame->ShowWindow(m_nCmdShow);

	// Enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();

	// Updates the client area by sending a WM_PAINT message 
	// if the update region is not empty
	pMainFrame->UpdateWindow();

	return TRUE;
}

// virtual 
int FW_WinApp::ExitInstance()
{	
	if(m_spIFWWinApp)
		m_spIFWWinApp = NULL;

	if(m_spIFWDocuments)
		m_spIFWDocuments = NULL;

	if(m_pAddInManager)
	{
		delete m_pAddInManager;
		m_pAddInManager = NULL;
	}

	if(m_pUIManager)
	{
		delete m_pUIManager;
		m_pUIManager = NULL;
	}

	if(m_pCmdManager)
	{
		delete m_pCmdManager;
		m_pCmdManager = NULL;
	}

	if(m_pEventManager)
	{
		delete m_pEventManager;
		m_pEventManager = NULL;
	}

	if(m_pEnvironmentManager)
	{
		delete m_pEnvironmentManager;
		m_pEnvironmentManager = NULL;
	}

	int iRet = CApcApplication<FW_WinApp>::ExitInstance();
	_Module.Term();
	return iRet;
}


// Controlling function for threads with a message pump
// Override to customize the default message loop.
// virtual 
int FW_WinApp::Run()
{
	int retval = 0;
	__try 
	{
		retval = CApcApplication<FW_WinApp,CWinApp>::Run();
	} 
	__except(MM_Manager::Get()->ExceptionFilter(GetExceptionInformation()))
	{
		ASSERT(0); // unreachable
	}	
	return retval;	
}

HRESULT FW_WinApp::ApcHost_OnCreate()
{
	BSTR bstrFilter = SysAllocStringLen(OLESTR("All Reference Files (*.mpad,*.tlb,*.olb,*.dll,*.exe,*.ocx)\0*.mpad;*.tlb;*.olb;*.dll;*.exe;*.ocx\0Documents (*.mpad)\0*.mpad\0"), sizeof(FILTER));
	ApcHost->APC_PUT(FileFilter)(bstrFilter);

	//Set the mini bitmaps for use in the VBA IDE
	PICTDESC pictdesc;

	//see stdafx.h for definition and explanation of PicturePtr
	CComPtr<IPictureDisp> pAppPict;
	CComPtr<IApcMiniBitmaps> pMiniBitmaps;
	CBitmap bitApp;

	bitApp.LoadBitmap(IDB_FWAPP);

	::OLE_COLOR clrTrans = RGB(255, 255, 255);

	pictdesc.cbSizeofstruct = sizeof(pictdesc);
	pictdesc.picType = PICTYPE_BITMAP;
	pictdesc.bmp.hbitmap = (HBITMAP)bitApp.Detach();
	pictdesc.bmp.hpal = NULL;

	//if any of this stuff fails, we'll just live with it, just window dressing
	if(SUCCEEDED(OleCreatePictureIndirect(&pictdesc, IID_IPictureDisp, TRUE, (LPVOID*)&pAppPict)))
	{
		ApcHost->APC_PUT(Picture)(pAppPict);
		ApcHost->APC_PUT(BackColor)(clrTrans);
	}

	return CApcApplication<FW_WinApp>::ApcHost_OnCreate();
}

HRESULT FW_WinApp::ApcHost_OpenProject(BSTR bstrProjectFileName, IApcProject* pReferencingProject, IApcProject** pProject )
{
	CString strFile(bstrProjectFileName);

	FW_Document * pDoc=(FW_Document *)OpenDocumentFile(strFile);
	if (pDoc)
	{
		*pProject=pDoc->ApcProject.GetApcProject();
		(*pProject)->AddRef();
	}
	return S_OK;
}

// Get AddIn Manager
FW_AddInManager* FW_WinApp::GetAddInManager()
{
	if(!m_pAddInManager)
		m_pAddInManager = new FW_AddInManager(this);
	return m_pAddInManager;
}

// Get UI Manager
FW_UIManager* FW_WinApp::GetUIManager()
{
	if(!m_pUIManager)
		m_pUIManager = new FW_UIManager(this);
	return m_pUIManager;
}

// Get Command Manager
FW_CmdManager* FW_WinApp::GetCmdManager()
{
	if(!m_pCmdManager)
		m_pCmdManager = new FW_CmdManager(this);
	return m_pCmdManager;
}

// Get Event Manager
FW_EventManager* FW_WinApp::GetEventManager()
{
	if(!m_pEventManager)
		m_pEventManager = new FW_EventManager(this);
	return m_pEventManager;
}

// Get Env Manager
FW_EnvironmentManager* FW_WinApp::GetEnvironmentManager()
{
	if(!m_pEnvironmentManager)
		m_pEnvironmentManager = new FW_EnvironmentManager(this);
	return m_pEnvironmentManager;
}

// App command to run the dialog
void FW_WinApp::OnAppAbout()
{
}