#include "StdAfx.h"
#include "ProfileManager.h"
#include "DiagnosticWnd.h"
#include <algorithm>

CProfiler::CProfiler(ProfileData * pData)
{
	if (pData == NULL) {
		ASSERT(FALSE);
	}
	m_pData = pData;
}


void CProfiler::StartProfile()
{
	if (m_pData->m_bIsEntered) {
		m_bIsProfiling = false;
		return;
	}
	m_pData->m_bIsEntered = true;
	m_bIsProfiling = true;
	m_pData->m_iHitCount++;
	QueryPerformanceCounter(&m_start); 
}


void CProfiler::EndProfile()
{
	LARGE_INTEGER end, freq;
	QueryPerformanceCounter(&end); 
	QueryPerformanceFrequency(&freq);	

	if (!m_bIsProfiling) {
		return;
	}

	m_pData->m_bIsEntered = false;

	// Unit: s
	double time = 1000 * (end.QuadPart - m_start.QuadPart) / (double)freq.QuadPart;

	if (m_pData->m_dFirstTime == 0) {
		// first time be called
		m_pData->m_dFirstTime = time;
	}
	m_pData->m_dLastTime = time;
	m_pData->m_dTimeElapsed += time;
	m_bIsProfiling = false;
}


CProfiler::~CProfiler()
{
	if (m_bIsProfiling) {
		EndProfile();
	}
}

CProfileManager::CProfileManager(void)
{
	m_pDGWnd = CDiagnosticWnd::GetDiagnosticWnd();

	ReadSettings();

}

BOOL CProfileManager::ReadSettings()
{
	m_strProfileLogPath = DiagnosticSettings::DefaultProfileLogPath;
	return TRUE;
}


CProfileManager::~CProfileManager(void)
{
}

CProfileManager* CProfileManager::GetProfileManager()
{
	static CProfileManager profileMgr;
	return &profileMgr;
}

ProfileData* CProfileManager::GetProfileData(CString strRoutineName, CString strParentRoutingName)
{
	// if not found then allocate
	ProfileData* pData = NULL;
	ProfileDataMap::iterator itParent = m_mapProfileDatas.find(strParentRoutingName);
	if(itParent == m_mapProfileDatas.end())
	{
		if(m_mapProfileDatas.empty())
		{
			m_pRootProfileData = new ProfileData;
			m_pRootProfileData->m_strRoutineName = strRoutineName;
			m_mapProfileDatas.insert(std::make_pair(strRoutineName, m_pRootProfileData));
			return m_pRootProfileData;
		}
		else
		{
			ASSERT(FALSE);
			return NULL;
		}
	
	}
	ProfileDataMap::iterator it = m_mapProfileDatas.find(strRoutineName);
	if(it == m_mapProfileDatas.end())
	{
		pData = new ProfileData;
		m_mapProfileDatas.insert(std::make_pair(strRoutineName, pData));
	}
	else
	{
		pData = it->second;
	}
	itParent->second->AddChild(pData);
	pData->m_strRoutineName = strRoutineName;
	return pData;
}


void CProfileManager::ClearProfile()
{
	class Delete
	{
	public:
		void operator () (ProfileDataMap::value_type& pData)
		{
			delete pData.second;
		}
	};
	std::for_each(m_mapProfileDatas.begin(), m_mapProfileDatas.end(), Delete());
	m_mapProfileDatas.clear();
	m_pRootProfileData = NULL;
}

void CProfileManager::DumpToFile(ProfileData* pData)
{
	CString strLogLine;
	CString strTmp;
	strTmp.Format(_T("%-30s"), pData->m_strRoutineName);
	strLogLine = strLogLine + strTmp + _T("     ");

	strTmp.Format(_T("%-20.3f"), pData->m_dTimeElapsed);
	strLogLine = strLogLine + strTmp + _T("     ");

	strTmp.Format(_T("%-10d"), pData->m_iHitCount);
	strLogLine = strLogLine + strTmp + _T("     ");

	strTmp.Format(_T("%-4.2f"), pData->m_dbPercentage);
	strLogLine = strLogLine + strTmp + _T("     ");
	strLogLine += _T("\r\n");

	m_profileLogFile.WriteString(strLogLine);

	if(!pData->m_vectSubProfileDatas.empty())
	{
		std::vector<ProfileData*>::iterator it;
		for(it = pData->m_vectSubProfileDatas.begin(); it != pData->m_vectSubProfileDatas.end(); ++it)
		{
			DumpToFile(*it);
		}
	}
	return;

	
}

void CProfileManager::ReportProfile(CString strName)
{
	m_pDGWnd->DumpProfileInfo(m_pRootProfileData);

	CTime time = CTime::GetCurrentTime();
	m_strProfileLogFileName  = m_strProfileLogPath + _T("\\") + time.Format( _T( "ProfileLog[%Y-%m-%d][%H-%M-%S]" )) + strName + _T( ".txt" );
	if(!m_profileLogFile.m_pStream)
	{
		if( !m_profileLogFile.Open(m_strProfileLogFileName, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite ) )
		{
			// Creation file failed, please check the log path & your hard disk
			DebugBreak();
		}
	}

	CString strLogTitle;
	CString strTmp;
	strTmp.Format(_T("%-30s"), _T("Routine Name"));
	strLogTitle = strLogTitle + strTmp + _T("     ");

	strTmp.Format(_T("%-20s"), _T("Time"));
	strLogTitle = strLogTitle + strTmp + _T("     ");

	strTmp.Format(_T("%-10s"), _T("Hit Count"));
	strLogTitle = strLogTitle + strTmp + _T("     ");

	strTmp.Format(_T("%-4s"), _T("Percentage"));
	strLogTitle = strLogTitle + strTmp + _T("     ");
	strLogTitle += _T("\r\n");

	m_profileLogFile.WriteString(strLogTitle);

	DumpToFile(m_pRootProfileData);

	m_profileLogFile.Close();

}