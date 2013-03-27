// DiagnosticWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DG.h"
#include "DiagnosticWnd.h"
#include "ProfileManager.h"
#include <cstdlib>

// general
const float   DiagnosticSettings::CurrentVersion		= 0.90f;							//Current version of this Debug Tool
const BOOL    DiagnosticSettings::DefaultShowDebugWin	= TRUE;								//Show the debug window or not
// debug
const PCTSTR  DiagnosticSettings::DefaultTempPath		= _T( "X:\\LOG\\Temp" );			//Default Path for Temporary files
const PCTSTR  DiagnosticSettings::DefaultDebugLogPath	= _T( "X:\\LOG\\DebugLog" );        //Default Path for debug Log files
const BOOL    DiagnosticSettings::DefaultStopOnError	= FALSE;							//Show Assert Dialog when occur an error
const BOOL    DiagnosticSettings::DefaultIgnoreAsserts	= FALSE;							//Ignore the Assert Dialog
const BOOL    DiagnosticSettings::DefaultHookAsserts	= TRUE;								//Hook Assert to customize its behavior
// profile
const PCTSTR  DiagnosticSettings::DefaultProfileLogPath	= _T( "X:\\LOG\\ProfileLog" );      //Default Path for profile Log files
// unit test
const PCTSTR  DiagnosticSettings::DefaultUnitTestLogPath= _T( "X:\\LOG\\UnitTestLog" );     //Default Path for unit test Log files

// general
PCTSTR DiagnosticKeyNames::ApplicationKey		=	_T("Software\\Diagnostics" );
PCTSTR DiagnosticKeyNames::VersionKey			=	_T("Version");
PCTSTR DiagnosticKeyNames::ShowDGWndKey			=	_T("ShowDiagnosticWnd");
// debug
PCTSTR DiagnosticKeyNames::TempPathKey			=	_T("TempPath");
PCTSTR DiagnosticKeyNames::DebugLogPathKey		=	_T("DebugLogPath");
PCTSTR DiagnosticKeyNames::StopOnErrorKey		=	_T("StopOnError");
PCTSTR DiagnosticKeyNames::IgnoreAssertsKey		=	_T("IgnoreAsserts");
PCTSTR DiagnosticKeyNames::HookAssertsKey		=	_T("HookAsserts");
// profile
PCTSTR DiagnosticKeyNames::ProfileLogPathKey	=	_T("ProfileLogPath");
// unit test
PCTSTR DiagnosticKeyNames::UnitTestLogPathKey	=	_T("UnitTestLogPath");




CDiagnosticWnd* CDiagnosticWnd::m_pDGWnd = NULL;
// CDiagnosticWnd dialog

IMPLEMENT_DYNAMIC(CDiagnosticWnd, CDialog)

CDiagnosticWnd::CDiagnosticWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagnosticWnd::IDD, pParent)
{

}

CDiagnosticWnd::~CDiagnosticWnd()
{
}

void CDiagnosticWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEBUG, m_listDebugInfo);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tabMain);
	DDX_Control(pDX, IDC_TREE_PROFILE, m_treeProfileInfo);
}

CDiagnosticWnd* CDiagnosticWnd::GetDiagnosticWnd()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	// here use CDiagnosticWnd dgWnd met some problem when destruct, use heap allocated memory instead
	if(NULL == m_pDGWnd)
	{
		m_pDGWnd = new CDiagnosticWnd();
		m_pDGWnd->Create(IDD_DIAGNOSTICWND, CWnd::FromHandle(::GetDesktopWindow()));
		m_pDGWnd->ShowWindow(SW_SHOW);

		//atexit(DeleteDiagnosticWnd);
	}
	return m_pDGWnd;
}

void CDiagnosticWnd::DeleteDiagnosticWnd()
{
	delete m_pDGWnd;
	m_pDGWnd = NULL;
}


BEGIN_MESSAGE_MAP(CDiagnosticWnd, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CDiagnosticWnd::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// CDiagnosticWnd message handlers

BOOL CDiagnosticWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tabMain.InsertItem(0, _T("Debug"));
	m_tabMain.InsertItem(1, _T("Profile"));
	m_tabMain.InsertItem(2, _T("UnitTest"));

	// Set current active pane
	m_tabMain.SetCurSel( 0 );

	m_listDebugInfo.Initialize();

	m_treeProfileInfo.ModifyStyle(0, TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CDiagnosticWnd::InsertDebugItem(CString strTime, DWORD dTickCount, CString strFileName, int nLineNumber, CString strError)
{
	return m_listDebugInfo.InsertItem( strTime, dTickCount, strFileName, nLineNumber, strError);
}

inline static ProfileItem ProfileDataToItem(ProfileData* pData)
{
	ProfileItem profileItem;
	profileItem.strRoutineName = pData->m_strRoutineName;
	profileItem.dbTime = pData->m_dTimeElapsed;
	profileItem.iHitCount = pData->m_iHitCount;
	profileItem.dbPercentage = pData->m_dbPercentage;
	return profileItem;
}

void CDiagnosticWnd::RecursiveDump(ProfileData* pData, HTREEITEM hParentItem /*= TVI_ROOT*/)
{
	ProfileItem item = ProfileDataToItem(pData);
	HTREEITEM hItem = m_treeProfileInfo.InsertItem(&item, hParentItem);
	if(!pData->m_vectSubProfileDatas.empty())
	{
		std::vector<ProfileData*>::iterator it;
		for(it = pData->m_vectSubProfileDatas.begin(); it != pData->m_vectSubProfileDatas.end(); ++it)
		{
			RecursiveDump(*it, hItem);
		}
	}
	return;
}

void CDiagnosticWnd::DumpProfileInfo(ProfileData* pRootData)
{
	RecursiveDump(pRootData);
}

void CDiagnosticWnd::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nActivePane = m_tabMain.GetCurSel();
	if(0 == nActivePane)
	{
		m_treeProfileInfo.ShowWindow(SW_HIDE);
		m_listDebugInfo.ShowWindow(SW_SHOW);
	}
	if(1 == nActivePane)
	{
		m_listDebugInfo.ShowWindow(SW_HIDE);
		m_treeProfileInfo.ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}
