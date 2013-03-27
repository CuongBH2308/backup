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


#include "stdafx.h"
#include "fw_environments.h"
#include "fw_environment.h"

FW_Environments::FW_Environments(FW_EnvironmentManager* pEnvironmentManager)
:m_pEnvironmentManager(pEnvironmentManager)
{
}

FW_Environments::~FW_Environments(void)
{
	for(std::vector<FW_Environment*>::const_iterator it=m_vEnvironment.begin();it!=m_vEnvironment.end();it++)
		delete (*it);

	m_vEnvironment.clear();
}

FW_Environment* FW_Environments::Add(const CString& strInternalName)
{
	FW_Environment* pEnvironment = new FW_Environment(this,strInternalName);
	return pEnvironment;
}

void FW_Environments::Add(FW_Environment* pEnvironment)
{
	m_vEnvironment.push_back(pEnvironment);
}
