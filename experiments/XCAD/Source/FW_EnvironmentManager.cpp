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
#include "fw_environmentmanager.h"
#include "fw_environments.h"

FW_EnvironmentManager::FW_EnvironmentManager(FW_WinApp*	pApp)
:m_pApp(pApp),
m_pEnvironments(NULL)
{
}

FW_EnvironmentManager::~FW_EnvironmentManager(void)
{
	if(m_pEnvironments)
	{
		delete m_pEnvironments;
		m_pEnvironments = NULL;
	}
}

FW_Environments* FW_EnvironmentManager::GetEnvironments()
{
	if(!m_pEnvironments)
		m_pEnvironments = new FW_Environments(this);
	return m_pEnvironments;
}