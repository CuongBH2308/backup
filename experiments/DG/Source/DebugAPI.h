/**
* @file DebugAPI.h Simple API Wrapper of CDebugManager.
* Simply Delegate calls to CDebugManager
*

*
* @author Baiyan Huang
*
* @date 11/1/2008 [Baiyan Huang] Created
*/
#pragma once
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "DGExport.h"


/**
* Namespace for Debug Utilities.
*/
namespace DG
{
	/**
	* Create the debug window.
	*/
	DG_API void CreateDebugWnd();

	/**
	* Destroy the debug window
	*/
	DG_API void DestroyDebugWnd();

	/**
	* Pupup an custom assert dialog.
	* @return true means to break into the source code.
	*/
	DG_API bool CustomAssert(const CString& strError, const CString& strFileName, int nLineNum);

	/**
	* Trigger a custom error.
	*/
	DG_API bool CustomError(const CString& strError, const CString& strFileName, int nLineNum);

	/**
	* Report a message, both to debug window and log file.
	*/
	DG_API void ReportMsg(const CString& strMsg, const CString& strFileName, int nLineNum);
}

#endif