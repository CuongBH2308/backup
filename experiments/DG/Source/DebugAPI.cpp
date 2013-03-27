#include "stdafx.h"
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "DebugAPI.h"
#include "DebugManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void DG::CreateDebugWnd()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDebugManager::GetInstance();
}

void DG::DestroyDebugWnd()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDebugManager::DeleteInstance();
}

bool DG::CustomAssert(const CString& strError, const CString& strFileName, int nLineNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDebugManager::Option opt = CDebugManager::GetInstance()->CustomAssert(strError, strFileName, nLineNum);
	if( opt == CDebugManager::kBreakInto) 
		return true;
	else
		return false;
}

bool DG::CustomError(const CString& strError, const CString& strFileName, int nLineNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDebugManager::Option opt = CDebugManager::GetInstance()->CustomError(strError, strFileName, nLineNum);
	if( opt == CDebugManager::kBreakInto )
		return true;
	else
		return false;
}
void DG::ReportMsg(const CString& strMsg, const CString& strFileName, int nLineNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDebugManager::GetInstance()->ReportMsg(strMsg, strFileName, nLineNum); 
}

#endif