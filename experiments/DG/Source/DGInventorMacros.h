/**
 * @file DGInventorMacros.h DG macros used to integrate with Inventor
 *

 *
 * @author Baiyan Huang
 *
 * @date 12/16/2008 [Baiyan Huang] Created
 *
 */
#pragma once
#include "BuildOption.h"
#include "DGInventorAPI.h"
#pragma comment(lib, "R:\\lib\\Debug\\dg.lib")

/**
 * Create the debug window, always called when the application starts up.
 */
#ifdef ENABLE_REPORT
#define CREATE_DEBUGWND   DG::CreateDebugWnd()
#else
#define CREATE_DEBUGWND
#endif

/**
 * Destroy the debug window, always called when application.shuts down.
 */
#ifdef ENABLE_REPORT
#define DESTROY_DEBUGWND   DG::DestroyDebugWnd()
#else
#define DESTROY_DEBUGWND
#endif