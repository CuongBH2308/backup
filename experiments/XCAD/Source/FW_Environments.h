/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>

class FW_Environment;
class FW_EnvironmentManager;
class FW_Environments
{
	friend FW_EnvironmentManager;

public:
	FW_Environment* Add(const CString& strInternalName);
	void Add(FW_Environment* pEnvironment);

protected:
	FW_Environments(FW_EnvironmentManager* pEnvironmentManager);
	virtual ~FW_Environments(void);

private:
	FW_EnvironmentManager*	m_pEnvironmentManager;
	std::vector<FW_Environment*> m_vEnvironment;
};
