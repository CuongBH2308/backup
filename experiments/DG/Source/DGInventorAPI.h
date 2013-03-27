/**
 * @file DGInventorAPI.h Intergrate DG with Inventor, implement function UTxUtil__MCADError with CustomAssert
 *

 *
 * @author Baiyan Huang
 *
 * @date 12/16/2008 [Baiyan Huang] Created
 */
#pragma once
#include "DGExport.h"
namespace DGInventor
{
	/**
	* Create the debug window.
	*/
	DG_API void CreateDebugWnd();

	/**
	* Destroy the debug window
	*/
	DG_API void DestroyDebugWnd();

	DG_API bool CustomAssert(const char* strError, const char* strFileName, int nLineNum);
}