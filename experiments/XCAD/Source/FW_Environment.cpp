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
#include "fw_environment.h"
#include "fw_environments.h"

FW_Environment::FW_Environment(FW_Environments* pEnvironments,const CString& strInternalName)
:m_pEnvironments(pEnvironments),
m_strInternalName(strInternalName),
m_pUICmdBar(NULL)
{
	pEnvironments->Add(this);
}

FW_Environment::~FW_Environment(void)
{
}

// Add command bar that should be displayed in this env
void FW_Environment::Add(FW_UICmdBar* pUICmdBar)
{
	m_vUICmdBar.push_back(pUICmdBar);
}

void FW_Environment::SetDefaultCmdBar(FW_UICmdBar* pUICmdBar)
{
	m_pUICmdBar = pUICmdBar;
}

FW_UICmdBar* FW_Environment::GetDefaultCmdBar() const
{
	if(m_pUICmdBar)
		return m_pUICmdBar;
	else if(m_vUICmdBar.size()>0)
		return m_vUICmdBar.front();
	else
		return NULL;
}
