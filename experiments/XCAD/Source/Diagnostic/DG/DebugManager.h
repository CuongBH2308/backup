#pragma once

#include "DGExports.h"
class CDiagnosticWnd;

class DGEXPORTS_API CDebugManager
{
public:
	/**
	* kBreakInto or kIgnore. Returned by ReportError.
	*/
	enum Option     { kBreakInto, kIgnore };

private:
	CDebugManager(void);
	~CDebugManager(void);

public:
	static CDebugManager* GetDebugManager();
	BOOL GetIgnoreAsserts(){return m_bIgnoreAsserts;}
	void SetIgnoreAsserts(BOOL bIgnoreAsserts){m_bIgnoreAsserts = bIgnoreAsserts;}

	BOOL GetStopOnError(){return m_bStopOnError;}
	void SetStopOnError(BOOL bStopOnError){m_bStopOnError = bStopOnError;}




public:
	int ReportHookProc( int nReportType, char *szMessage, int *pnReturnValue );
	Option ReportError(PCTSTR szError, PCTSTR szFileName, int nLineNumber);

	void ReportToLogFile(CString strLogLine);
	void ReportToDGWnd(CString strTime, DWORD dTickCount, CString strFileName, int nLineNumber, CString strError);
	void ReportToOutputWnd(CString strLogLine);


private:
	BOOL ReadSettings();
	BOOL WriteSettings();

private:
	CDiagnosticWnd* m_pDGWnd;

	CStdioFile	m_debugLogFile;
	CString m_strDebugLogFileName;

private:

	CString		m_strTempPath;                      //Default Path for Temporary files
	CString		m_strDebugLogPath;                  //Default Path for debug Log files
	BOOL		m_bStopOnError;						//Show Assert Dialog when occur an error
	BOOL		m_bIgnoreAsserts;					//Ignore the Assert Dialog
	BOOL		m_bHookAsserts;						//Hook Assert to customize its behavior
};
