#include "stdafx.h"
#include "DGInventorAPI.h"
#include "DebugAPI.h"


/**
* Create the debug window.
*/
void DGInventor::CreateDebugWnd()
{
	return DG::CreateDebugWnd();
}

/**
* Destroy the debug window
*/
void DGInventor::DestroyDebugWnd()
{
	return DG::DestroyDebugWnd();
}

bool DGInventor::CustomAssert(const char* strError, const char* strFileName, int nLineNum)
{
	return DG::CustomAssert(CString(strError), CString(strFileName), nLineNum);
}