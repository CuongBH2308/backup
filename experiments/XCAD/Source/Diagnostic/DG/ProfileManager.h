#pragma once
#include "DGExports.h"
#include <hash_map>
#include <map>
#include <vector>
class CDiagnosticWnd;

/**
* Profile Data struct
* Contain the whole code section Stat. information
* Each code section to be profiled has only one ProfileData
* No matter how much times it will be executed
*/
struct ProfileData
{
	CString		m_strRoutineName;
	double		m_dTimeElapsed;
	int			m_iHitCount;
	double		m_dbPercentage;

	double		m_dFirstTime;
	double		m_dLastTime;
	bool		m_bIsEntered;

	std::vector<ProfileData*> m_vectSubProfileDatas;

	ProfileData() : m_strRoutineName(_T("")), m_iHitCount(0), m_dTimeElapsed(0),
					m_dFirstTime(0), m_dLastTime(0),m_bIsEntered(false), m_dbPercentage(0){}

	void AddChild(ProfileData* pChildData)
	{
		m_vectSubProfileDatas.push_back(pChildData);
	}
	/** 
	*  Clear all the Stat. data and flag except m_bIsLocked
	*/
	void Clear()
	{
		m_strRoutineName = _T("");
		m_iHitCount = 0;
		m_dTimeElapsed = 0;
		m_dFirstTime = 0;
		m_dLastTime = 0;
		m_bIsEntered = false;
	}

};

/**
*	class CProfiler
*	
*	Class to do profile, every time the code is executed 
*	an instance will be created if there is a profiler
*	installed
*/
class DGEXPORTS_API CProfiler
{
public:
	CProfiler(ProfileData * pData);
	~CProfiler();

	void StartProfile();
	void EndProfile();
protected:
	bool					 m_bIsProfiling;
	LARGE_INTEGER			 m_start;
	ProfileData			   * m_pData;
};


class DGEXPORTS_API CProfileManager
{
private:
	CProfileManager(void);
	~CProfileManager(void);
public:
	static CProfileManager* GetProfileManager();

	ProfileData*	GetProfileData(CString strRoutineName, CString strParentRoutingName);

	void ClearProfile();
	void ReportProfile(CString strName);
	void DumpToFile(ProfileData* pData);

private:
	BOOL ReadSettings();
	BOOL WriteSettings();
	CString m_strProfileLogPath;
private:
	CDiagnosticWnd*	m_pDGWnd;

	CStdioFile	m_profileLogFile;
	CString m_strProfileLogFileName;

	ProfileData*	m_pRootProfileData;

	typedef std::map<CString, ProfileData*> ProfileDataMap;
	ProfileDataMap	 m_mapProfileDatas;
};

/*
*	Class CProfileScope
*
*	Declare a code scope to begin profilers
*	At the end of the scope a log file will be created
*/
class DGEXPORTS_API  CProfileScope
{
public:
	CProfileScope(CString cstrName) 
		: m_cstrName(cstrName)
	{
		CProfileManager::GetProfileManager()->ClearProfile();

	}
	~CProfileScope() 
	{
		CProfileManager::GetProfileManager()->ReportProfile(m_cstrName);
		CProfileManager::GetProfileManager()->ClearProfile();
	}
protected:
	CString				m_cstrName;
};