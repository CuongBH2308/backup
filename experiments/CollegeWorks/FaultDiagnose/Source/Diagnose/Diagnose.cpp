// Diagnose.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Diagnose.h"

#include "MainFrm.h"
#include "DiagnoseDoc.h"
#include "DiagnoseView.h"
#include<string>
//#include "diagnoseclass\\MalfuncDeduce.h"
#include <map>

using namespace std;
//#include "diagnoseclass\\ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CADODatabase GlDataBase;

extern bool SetParaTable(map<string,int>& ParaTable);
extern map<string,int> g_ParaTable;  //用来放征兆数据ID和征兆数据符号（如U，I R）

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseApp



BEGIN_MESSAGE_MAP(CDiagnoseApp, CWinApp)
	//{{AFX_MSG_MAP(CDiagnoseApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseApp construction

CDiagnoseApp::CDiagnoseApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	//AfxOleInit();

	::CoInitialize(0);


}

CDiagnoseApp::~CDiagnoseApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	
	//AfxOleInit();
	
	::CoUninitialize();
	
	
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CDiagnoseApp object

CDiagnoseApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseApp initialization

BOOL CDiagnoseApp::InitInstance()
{
	AfxEnableControlContainer();

	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	//读输入文件
	CString strFile="user_info.txt";
	CStdioFile file;
	CFileException e;
	CString str;
	int length;
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone,&e);
	while(file.ReadString(str)!=NULL)
	{
		length=str.GetLength();
		if (str.Find("数据源=")==0)
		{
			m_sqlserver_db.dbsrc=str.Right(length-strlen("数据源="));
			m_sqlserver_db.dbsrc.TrimLeft();
			m_sqlserver_db.dbsrc.TrimRight();
		}
		else if (str.Find("用户名=")==0)
		{
			m_sqlserver_db.user=str.Right(length-strlen("用户名="));
			m_sqlserver_db.user.TrimLeft();
			m_sqlserver_db.user.TrimRight();
		}
		else if (str.Find("密码=")==0)
		{
			m_sqlserver_db.pass=str.Right(length-strlen("密码="));
			m_sqlserver_db.pass.TrimLeft();
			m_sqlserver_db.pass.TrimRight();
		}
		
	}
	file.Close();
	
	CString Datasource;
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=TDESdb; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
	
	
	GlDataBase.SetConnectionString(Datasource);//"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=TDESdb");
	if(GlDataBase.Open()!=TRUE){
		AfxMessageBox("连接数据库失败!");
		return FALSE;
	}

	if(!SetParaTable(g_ParaTable))
		return FALSE;


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDiagnoseDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDiagnoseView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	UpdatePrinterSelection(TRUE);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	m_pMainWnd->SetWindowText("可视化建模及错误诊断专家系统－诊断运行管理模块界面");

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDiagnoseApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseApp message handlers


int CDiagnoseApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::ExitInstance();
}
