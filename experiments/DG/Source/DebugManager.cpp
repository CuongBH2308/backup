#include "StdAfx.h"
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "DebugManager.h"
#include "DebugWnd.h"
#include "Logger.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace DG;

// Settings: save in registry.
const TCHAR* DG_REGKEY          = _T("Software\\lzprgmr\\DG");
const TCHAR* LOG_PATH           = _T("C:\\");
const BOOL   IGNORE_ASSERT      = 0;
const BOOL   STOP_ON_ERROR      = 0;
const BOOL   HOOK_SYSTEM_ASSERT = 1;

// Prefix String
const TCHAR* ASSERT_PREFIX      = _T("ASSERT=>");
const TCHAR* ERROR_PREFIX       = _T("ERROR =>");

CDebugManager::CDebugManager(void)
{
	// 1 get settings from registry
	CString strLogPath          = LOG_PATH;
	BOOL	bIgnoreAssert       = IGNORE_ASSERT;
	BOOL	bStopOnError        = STOP_ON_ERROR;
	BOOL	bHookSystemAssert   = HOOK_SYSTEM_ASSERT;
	CRegKey regKey;
	if(regKey.Open(HKEY_CURRENT_USER, DG_REGKEY) == ERROR_SUCCESS)
	{
		// Log Path
		ULONG ulSize;
		TCHAR tszTempPath[_MAX_PATH];
		ulSize = _MAX_PATH;
		if(regKey.QueryStringValue(_T("LOG_PATH"), tszTempPath, &ulSize ) == ERROR_SUCCESS)
			strLogPath = tszTempPath;

		// Ignore Assert
		DWORD dwValue;
		if(regKey.QueryDWORDValue(_T("IGNORE_ASSERT"), dwValue ) == ERROR_SUCCESS)
		{
			if( dwValue == 0 )
				bIgnoreAssert = FALSE;
			else
				bIgnoreAssert = TRUE;
		}

		// Stop On Error
		if(regKey.QueryDWORDValue(_T("STOP_ON_ERROR"), dwValue ) == ERROR_SUCCESS)
		{
			if( dwValue == 0 )
				bStopOnError = FALSE;
			else
				bStopOnError = TRUE;
		}

		// Hook System Assert
		if(regKey.QueryDWORDValue(_T("HOOK_SYSTEM_ASSERT"), dwValue ) == ERROR_SUCCESS)
		{
			if( dwValue == 0 )
				bHookSystemAssert = FALSE;
			else
				bHookSystemAssert = TRUE;
		}

	}
	m_strLogPath = strLogPath;

	// 2 create debug window
	m_pDebugWnd = new CDebugWnd(CWnd::FromHandle(::GetDesktopWindow()));
	m_pDebugWnd->Create(IDD_DIALOG_DEBUG, CWnd::FromHandle(::GetDesktopWindow()));
	m_pDebugWnd->SetIgnoreAssert(bIgnoreAssert);
	m_pDebugWnd->SetStopOnError(bStopOnError);
	m_pDebugWnd->SetHookSystemAssert(bHookSystemAssert);

#ifdef _DEBUG
	m_pDebugWnd->ShowWindow(SW_SHOW);
#else
	m_pDebugWnd->ShowWindow(SW_HIDE);
#endif

	// 3 create tracer
	CTime time = CTime::GetCurrentTime();
	CString strTick;
	strTick.Format( _T( "[%d]" ), GetTickCount() );
	m_strFullLogFileName = strLogPath + _T("\\") + time.Format( _T( "DebugLog[%Y-%m-%d][%H-%M-%S]" ) ) + strTick + _T( ".txt" );

	m_pLogger = new CLogger(m_strFullLogFileName);

	CString strWindow;
	m_pDebugWnd->GetWindowText(strWindow);
	m_pDebugWnd->SetWindowText(strWindow + _T("->") + m_strFullLogFileName);

	// 4. Hook System Assert
	ToggleSystemAssert();

}
	

CDebugManager::~CDebugManager(void)
{
	ToggleSystemAssert();

	// write settings
	bool bKeyExist(true);
	CRegKey regKey;
	if(regKey.Open(HKEY_CURRENT_USER, DG_REGKEY) != ERROR_SUCCESS)
	{
		if( regKey.Create(HKEY_CURRENT_USER, DG_REGKEY) != ERROR_SUCCESS)
			bKeyExist = false;
	}
	if (bKeyExist)
	{
		regKey.SetStringValue(_T("LOG_PATH"), m_strLogPath);
		regKey.SetDWORDValue(_T("IGNORE_ASSERT"), m_pDebugWnd->GetIgnoreAssert());
		regKey.SetDWORDValue(_T("STOP_ON_ERROR"), m_pDebugWnd->GetStopOnError());
		regKey.SetDWORDValue(_T("HOOK_SYSTEM_ASSERT"), m_pDebugWnd->GetHookSystemAssert());
	}

	if(NULL != m_pLogger)
	{
		delete m_pLogger;
		m_pLogger = NULL;
	}

	if(NULL != m_pDebugWnd)
	{
		m_pDebugWnd->DestroyWindow();
		delete m_pDebugWnd;
		m_pDebugWnd = NULL;
	}

}

void CDebugManager::ToggleSystemAssert()
{	
#ifdef _DEBUG
	static bool bIsHooked = false;
	if(m_pDebugWnd->GetHookSystemAssert())
	{
		if(!bIsHooked)
		{
			::_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL , CDebugManager::NativeAssert );
			bIsHooked = true;
		}
	}
	else
	{
		if(bIsHooked)
		{
			::_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE, CDebugManager::NativeAssert);
			bIsHooked = false;
		}
	}
#endif
}

void CDebugManager::OpenLogFile()
{

	HINSTANCE hInst = ::ShellExecute(m_pDebugWnd->GetSafeHwnd(), _T( "open" ), m_strFullLogFileName, NULL, NULL, SW_SHOWNORMAL);
	if( hInst <= reinterpret_cast<HINSTANCE>(32) )
	{
		::MessageBox( m_pDebugWnd->GetSafeHwnd(), m_strFullLogFileName + _T("Can't be opened"), _T( "Error" ), MB_OK | MB_ICONEXCLAMATION );
	}
}


int CDebugManager::NativeAssert( int nReportType, char *szMessage, int *pnReturnValue )
{
	if( nReportType == _CRT_ASSERT )
	{
		// Asserts caught! Analyse following string to get Error, Filename, and line number
		//  "x:\diagnostic\test\test.cpp(75) : Assertion failed!"
		CString str( szMessage );
		int nPos1 = str.Find(_T('('));
		int nPos2 = str.Find(_T(')'));
		int nPos3 = str.ReverseFind(_T(':'));

		CString strFileName = str.Left(nPos1);
		CString strLineNumber = str.Mid(nPos1 + 1, nPos2-nPos1-1);
		int nLineNumber = _ttoi(strLineNumber.GetBuffer(0));
		CString strError = str.Mid(nPos3+1);
		strError.TrimRight(); //trim the "\n" at right

		// Log the asserts to file/DGWnd Wnd
		CDebugManager::GetInstance()->ReportMsg(ASSERT_PREFIX + strError, strFileName, nLineNumber);
	
		// Show assert dialog if needed
		if(CDebugManager::GetInstance()->GetDebugWnd()->GetIgnoreAssert())
		{
			*pnReturnValue = 0;

			return TRUE;
		}
		else
		{
			int nSelection = ::MessageBox(NULL, str, _T( "ASSERT" ), MB_OK | MB_ICONSTOP | MB_ABORTRETRYIGNORE );            
			if( nSelection == IDABORT )
			{
				*pnReturnValue = 0;
				TerminateProcess( ::GetCurrentProcess(), 0 );
				return TRUE;
			}
			else if( nSelection == IDRETRY )
			{
				*pnReturnValue = 1;
				return TRUE;
			}
			else
			{
				*pnReturnValue = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

CDebugManager::Option CDebugManager::CustomAssert(const CString& strError, const CString& strFileName, int nLineNum)
{
	// Log the asserts to file/DGWnd Wnd
	CDebugManager::GetInstance()->ReportMsg(ASSERT_PREFIX + strError, strFileName, nLineNum);

	// Show assert dialog if needed
	if(CDebugManager::GetInstance()->GetDebugWnd()->GetIgnoreAssert())
	{
		return CDebugManager::kIgnore;
	}
	else
	{
		CString strAssertMsg;
		strAssertMsg.Format(_T("%s(%d):%s"), strFileName, nLineNum, strError);
		int nSelection = ::MessageBox(NULL, strAssertMsg, _T( "ASSERT" ), MB_OK | MB_ICONSTOP | MB_ABORTRETRYIGNORE );            
		if( nSelection == IDABORT )
		{
			TerminateProcess( ::GetCurrentProcess(), 0 );
			return CDebugManager::kIgnore;
		}
		else if( nSelection == IDRETRY )
		{
			return CDebugManager::kBreakInto;
		}
		else
		{
			return CDebugManager::kIgnore; 
		}
	}

	return CDebugManager::kIgnore;;
}

CDebugManager::Option CDebugManager::CustomError(const CString& strError, const CString& strFileName, int nLineNum)
{
	// Log the asserts to file/DGWnd Wnd
	CDebugManager::GetInstance()->ReportMsg(ERROR_PREFIX + strError, strFileName, nLineNum);

	// Show assert dialog if needed
	if(!CDebugManager::GetInstance()->GetDebugWnd()->GetStopOnError())
	{
		return CDebugManager::kIgnore;
	}
	else
	{
		CString strAssertMsg;
		strAssertMsg.Format(_T("%s(%d):%s"), strFileName, nLineNum, strError);
		int nSelection = ::MessageBox(NULL, strAssertMsg, _T( "ASSERT" ), MB_OK | MB_ICONSTOP | MB_ABORTRETRYIGNORE );            
		if( nSelection == IDABORT )
		{
			TerminateProcess( ::GetCurrentProcess(), 0 );
			return CDebugManager::kIgnore;
		}
		else if( nSelection == IDRETRY )
		{
			return CDebugManager::kBreakInto;
		}
		else
		{
			return CDebugManager::kIgnore; 
		}
	}

	return CDebugManager::kIgnore;;
}

void CDebugManager::ReportMsg(const CString& strMsg, const CString& strFileName, int nLineNum)
{
	// the msg will be reported in following form
	// Time(H:M:S + TickCount)  | Place(File Name + Line Number) | Msg

	// 1. Time(H:M:S + TickCount)
	CTime time = CTime::GetCurrentTime();
	DWORD dTickCount = ::GetTickCount();
	CString strTime;
	strTime.Format(_T("%s(%d)"), time.Format(_T("%H:%M:%S")), dTickCount);

	// 2. Place(File Name + Line Number)
	CString strLineNum;
	strLineNum.Format((_T("(%d)")), nLineNum);
	CString strPlace = strFileName + strLineNum;

	//3. Reort to debug window and log file
	m_pDebugWnd->Report(strTime, strPlace, strMsg);
	m_pLogger->Log(strTime + _T("\t") + strPlace + _T("\t") + strMsg);
}
#endif