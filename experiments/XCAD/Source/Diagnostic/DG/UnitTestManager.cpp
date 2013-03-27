#include "StdAfx.h"
#include "UnitTestManager.h"
#include "DiagnosticWnd.h"

CUnitTestManager::CUnitTestManager(void)
{
	m_pDGWnd = CDiagnosticWnd::GetDiagnosticWnd();
}

CUnitTestManager::~CUnitTestManager(void)
{
}

CUnitTestManager* CUnitTestManager::GetUnitTestManager()
{
	static CUnitTestManager utMgr;
	return &utMgr;
}