#include "StdAfx.h"
#include "DebugManager.h"
#include "DiagnosticWnd.h"

CDebugManager::CDebugManager(void)
{
	m_pDGWnd = CDiagnosticWnd::GetDiagnosticWnd();

	ReadSettings();

	CTime time = CTime::GetCurrentTime();
	CString strTick;
	strTick.Format( _T( "[%d]" ), GetTickCount() );

	m_strDebugLogFileName = m_strDebugLogPath + _T("\\") + time.Format( _T( "DebugLog[%Y-%m-%d][%H-%M-%S]" ) ) + strTick + _T( ".txt" );
}

CDebugManager::~CDebugManager(void)
{
	m_debugLogFile.Close();
}

CDebugManager* CDebugManager::GetDebugManager()
{
	static CDebugManager debugMgr;
	return &debugMgr;
}


BOOL CDebugManager::ReadSettings()
{
	m_strTempPath = DiagnosticSettings::DefaultTempPath;
	m_strDebugLogPath = DiagnosticSettings::DefaultDebugLogPath;
	m_bStopOnError = DiagnosticSettings::DefaultStopOnError;
	m_bIgnoreAsserts = DiagnosticSettings::DefaultIgnoreAsserts;
	m_bHookAsserts = DiagnosticSettings::DefaultHookAsserts;

	return TRUE;
}
BOOL CDebugManager::WriteSettings()
{
	return TRUE;
}

/**
* Hook procedure to track _CRT_ASSERTs
*/
int CDebugManager::ReportHookProc( int nReportType, char *szMessage, int *pnReturnValue )
{

	if( nReportType == _CRT_ASSERT )
	{
		// Asserts caught!
		CString str( szMessage );
		//GetDebugService()->LogLine( 0, str );

		if( GetDebugManager()->GetIgnoreAsserts() && m_pDGWnd->GetShowDGWnd())
		{
			*pnReturnValue = 0;

			return TRUE;
		}
		else
		{
			// Display
			int nSelection = ::MessageBox(m_pDGWnd->m_hWnd, str, _T( "ASSERT" ), MB_OK | MB_ICONSTOP | MB_ABORTRETRYIGNORE );            

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


CDebugManager::Option CDebugManager::ReportError(PCTSTR szError, PCTSTR szFileName, int nLineNumber)
{
	// report to log file first
	CString strLogLine;

	// Time
	CTime time = CTime::GetCurrentTime();
	DWORD dTickCount = ::GetTickCount();
	CString strDetailedTime;
	strDetailedTime.Format(_T( "[%s(%d)]" ),static_cast<LPCTSTR>( time.Format( _T( "%H:%M:%S" ) ) ),dTickCount );

	// Location
	CString strErrorInfo;
	strErrorInfo.Format( _T( "%s(%d) : %s" ), szFileName, nLineNumber, szError);
	strLogLine = strDetailedTime + strErrorInfo + _T("\r\n");
	if(!m_debugLogFile.m_pStream)
	{
		if( !m_debugLogFile.Open( m_strDebugLogFileName, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite ) )
		{
			// Creation file failed, please check the log path & your hard disk
			DebugBreak();
		}
	}
	m_debugLogFile.WriteString( strLogLine);

	if(m_pDGWnd->GetShowDGWnd() == TRUE)
	{
		CString strTime;
		strTime.Format(_T( "[%s]" ),static_cast<LPCTSTR>( time.Format( _T( "%H:%M:%S" ) ) ) );

		m_pDGWnd->InsertDebugItem(strTime, dTickCount, szFileName, nLineNumber, szError);
	}
	else
	{
		::OutputDebugString(strLogLine);
	}
	

	if( m_bStopOnError)
	{
		// Display a message box
		int nSelection = ::MessageBox( NULL, strLogLine, _T( "ERROR" ), MB_OK | MB_ICONSTOP | MB_ABORTRETRYIGNORE );

		if( nSelection == IDABORT )
		{
			TerminateProcess( ::GetCurrentProcess(), 0 );

			// Well, never gets here
			return kIgnore;
		}
		else if( nSelection == IDRETRY )
		{
			return kBreakInto;
		}
		else
		{
			return kIgnore;
		}
	}
	else
		return kIgnore;    
}

void CDebugManager::ReportToLogFile(CString strLogLine)
{

}
void CDebugManager::ReportToDGWnd(CString strTime, DWORD dTickCount, CString strFileName, int nLineNumber, CString strError)
{

}
void CDebugManager::ReportToOutputWnd(CString strLogLine)
{

}