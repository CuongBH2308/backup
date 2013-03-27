#pragma once
#include "afxcmn.h"
#include "Controls/DebugListCtrl.h"
#include "Controls/DGTreeCtrl.h"

struct ProfileData;
/**
* Default settings for Diagnostics
*/
class DiagnosticSettings
{
public :
	// general
	static const float   CurrentVersion;			           //Current version of this Debug Tool
	static const BOOL    DefaultShowDebugWin;                  //Show the debug window or not

	// debug
	static const PCTSTR  DefaultTempPath;                      //Default Path for Temporary files
	static const PCTSTR  DefaultDebugLogPath;                  //Default Path for debug Log files
	static const BOOL    DefaultStopOnError;				   //Show Assert Dialog when occur an error
	static const BOOL    DefaultIgnoreAsserts;				   //Ignore the Assert Dialog
	static const BOOL    DefaultHookAsserts;                   //Hook Assert to customize its behavior

	// profile
	static const PCTSTR  DefaultProfileLogPath;                //Default Path for profile Log files

	// unit test
	static const PCTSTR  DefaultUnitTestLogPath;               //Default Path for unit test Log files
	
};

/**
* Registry key names for the default settings
*/
class DiagnosticKeyNames
{
public :
	// general
	static PCTSTR ApplicationKey;
	static PCTSTR VersionKey;
	static PCTSTR ShowDGWndKey;

	// debug
	static PCTSTR TempPathKey;
	static PCTSTR DebugLogPathKey;
	static PCTSTR StopOnErrorKey;
	static PCTSTR IgnoreAssertsKey;
	static PCTSTR HookAssertsKey;

	// profile
	static PCTSTR ProfileLogPathKey;

	// unit test
	static PCTSTR UnitTestLogPathKey;
};


// CDiagnosticWnd dialog

class CDiagnosticWnd : public CDialog
{
	DECLARE_DYNAMIC(CDiagnosticWnd)

private:
	CDiagnosticWnd(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiagnosticWnd();

public:
	static  CDiagnosticWnd* GetDiagnosticWnd();
	static  void DeleteDiagnosticWnd();

	BOOL GetShowDGWnd(){return TRUE;}

	void RecursiveDump(ProfileData* pData, HTREEITEM hParentItem = TVI_ROOT);


	int InsertDebugItem(CString strTime, DWORD dTickCount, CString strFileName, int nLineNumber, CString strError);

	void DumpProfileInfo(ProfileData* pRootData);

// Dialog Data
	enum { IDD = IDD_DIAGNOSTICWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	static CDiagnosticWnd* m_pDGWnd;


	DECLARE_MESSAGE_MAP()
	CDebugListCtrl m_listDebugInfo;
	virtual BOOL OnInitDialog();
	CTabCtrl m_tabMain;
	CDGTreeCtrl m_treeProfileInfo;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
};

