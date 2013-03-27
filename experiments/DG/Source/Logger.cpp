#include "StdAfx.h"
#include "BuildOption.h"
#ifdef ENABLE_REPORT
#include "Logger.h"
#include "DebugMacros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace DG;

CLogger::CLogger(const CString& strFileName):m_strFileName(strFileName)
{
}

CLogger::~CLogger(void)
{
}

void CLogger::Log(const CString& strMsg)
{
	// only occupy the file when we write, or else we can't open this file when the application is running
	BOOL bOk = m_file.Open(m_strFileName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	DGASSERT(bOk);
	if(!bOk) return;

	m_file.SeekToEnd();
	m_file.WriteString(strMsg + _T("\n"));
	m_file.Flush();

	m_file.Close();
}

#endif