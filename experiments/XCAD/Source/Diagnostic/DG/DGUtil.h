#pragma once
#include "DebugManager.h"
#include "ProfileManager.h"

//#define INITDGWND CDebugManager::GetDebugManager();

#define DBGERROR(msg) \
{\
	CString strMsg( msg ); \
	CDebugManager::Option opt = CDebugManager::GetDebugManager()->ReportError( strMsg, _T( __FILE__ ),  __LINE__ ); \
	if( opt == CDebugManager::kBreakInto ) \
		DebugBreak(); \
}

#define DECLARE_PROFILE_SCOPE(RootRoutineName)	\
	CProfileScope oSocpe(_T(RootRoutineName));\
	static ProfileData * _pProfileData = \
	CProfileManager::GetProfileManager()->GetProfileData(_T(RootRoutineName), _T("")); \
	CProfiler _oProfile(_pProfileData);\
	_oProfile.StartProfile();

#define DECLARE_PROFILER(RoutineName, ParentRoutineName)						\
	static ProfileData * _pProfileData =										\
	CProfileManager::GetProfileManager()->GetProfileData(_T(RoutineName), _T(ParentRoutineName));		\
	CProfiler _oProfiler(_pProfileData);										\
	_oProfiler.StartProfile();