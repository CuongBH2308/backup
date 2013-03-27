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
#include "fw_addinmanager.h"
#include "fw_addins.h"

FW_AddInManager::FW_AddInManager(FW_WinApp* pApp)
:m_pApp(pApp),
m_pAddIns(NULL)
{
	// Load a sample add-in
	static const CLSID clsidAddInServer =
	{ 0x0F98901D, 0xE956, 0x4B71, { 0xA8, 0x39, 0x8F, 0xBD, 0x5E, 0x4A, 0x74, 0x6C } };
	GetAddIns()->Add(clsidAddInServer);
}

FW_AddInManager::~FW_AddInManager(void)
{
	if(m_pAddIns)
	{
		delete m_pAddIns;
		m_pAddIns = NULL;
	}
}

FW_AddIns* FW_AddInManager::GetAddIns(void)
{
	if(!m_pAddIns)
		m_pAddIns = new FW_AddIns(this);
	return m_pAddIns;
}