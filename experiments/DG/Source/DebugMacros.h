/**
 * @file DebugMacros.h .A Macro Wrapper of this debug classes, users only need to kown macros in the file
 *

 *
 * @remark 
 * 1. Note for the "msg" parameter for assert macros such as "DGASSERT2" and error macros such as "ON_ERROR_RETURN2":\n
 *  a). Must be literal constant. If you use a variable here, the msg shown at last is just the variable name.\n
 *  b). When provide the additional message, please use TCHAR  such as  _T("My Message")\n
 * 2. "assert" macro provided in assert.h can't be hooked by this tool.
 *
 * @author Baiyan Huang
 *
 * @date 11/1/2007 [Baiyan Huang] Created
 *
 */
#pragma once
#include "BuildOption.h"
#include "DebugAPI.h"

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


template<bool> struct CompileTimeError;
template<> struct CompileTimeError<true> {};
/**
 * Compile time check.
 * How to use: DGCHECK(sizeof(CMyClass) == 12);
 * @param expr The expression which can be evaluated in compile time.
 * @param msg  Additional error message which will be shown in compile error.
 */
#define DGCHECK(expr, msg)   { CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 

/**
 * Raise a custom assert.
 * How to use: DGASSERT(NULL != pGraphics && "description text here so we can see it in the assert dialog");
 * @param expr The expression to be evaluated.
 */
#ifdef ENABLE_REPORT
#define DGASSERT(expr)   if(!(expr) && DG::CustomAssert(_T(#expr), _T(__FILE__), __LINE__)) DebugBreak();
#else
#define DGASSERT(expr)
#endif

/**
 * Raise a custom assert, with an additional message.
 * How to use: DGASSERT2(NULL != pGraphics, "description text here so we can see it in the assert dialog");
 * @param expr The expression to be evaluated.
 * @param msg  Additional error message.
 */
#ifdef ENABLE_REPORT
#define DGASSERT2(expr, msg)   DGASSERT((expr) && (msg))
#else
#define DGASSERT2(expr, msg)
#endif

/**
 * Raise a custom assert, return if assert failed.
 * How to use: SAFE_ASSERT(NULL != pGraphics);
 * @param expr    The expression to be evaluated.
 * @param retval  The return value.
 */
#define SAFE_ASSERT(expr, retval)   {DGASSERT(expr); if(!(expr)) return retval;}

/**
 * Raise a custom assert with an additional message, return if assert failed.
 * How to use: SAFE_ASSERT2(NULL != pGraphics, "description text here so we can see it in the assert dialog");
 * @param expr    The expression to be evaluated.
 * @param msg     Additional error message.
 * @param retval  The return value.
 */
#define SAFE_ASSERT2(expr, retval, msg)   SAFE_ASSERT((expr) && (msg), retval)	

/**
 * Report a custom error.
 * This macro is not recommend to use directly,Instead, we use ON_ERROR_XXX oftenly.
 * How to use: DGERROR(_T("Error"));
 * @param msg  The error message.
 */
#ifdef ENABLE_REPORT
#define DGERROR(msg)   if(DG::CustomError(msg, _T(__FILE__), __LINE__)) DebugBreak();
#else
#define DGERROR(msg)
#endif

/**
 * If the expression succeeded, report an error then return.
 * @param expr    The expression to be evaluated.
 * @param retval  The return value.
 */
#define ON_ERROR_RETURN(expr, retval)   if(expr) {DGERROR(_T(#expr)); return retval;}

 /**
 * If the expression succeeded, report an error then return.
 * @param expr    The expression to be evaluated.
 * @param retval  The return value.
 * @param msg     Additional error message.
 */
#define ON_ERROR_RETURN2(expr, retval, msg)   ON_ERROR_RETURN((expr) && (msg), retval)	

/**
 * If the expression succeeded, report an error then goto the specified label.
 * @param expr    The expression to be evaluated.
 * @param label   Label.
 */
#define ON_ERROR_GOTO(expr, label)   if(expr) {DGERROR(_T(#expr)); goto label; } 

/**
 * If the expression succeeded, report an error then goto the specified label.
 * @param expr    The expression to be evaluated.
 * @param label   Label.
 * @param msg     Additional error message.
 */
#define ON_ERROR_GOTO2(expr, label, msg)   ON_ERROR_GOTO((expr) && (msg),  label)

/**
 * If the expression succeeded, report an error then continue the loop.
 * @param expr    The expression to be evaluated.
 */
#define ON_ERROR_CONTINUE(expr)   if(expr) {DGERROR(_T(#expr)); continue; }

/**
 * If the expression succeeded, report an error then continue the loop.
 * @param expr    The expression to be evaluated.
 * @param msg     Additional error message.
 */
#define ON_ERROR_CONTINUE2(expr, msg)   ON_ERROR_CONTINUE((expr) && (msg))

/**
 * If the expression succeeded, report an error.
 * @param expr    The expression to be evaluated.
 */
#define ON_ERROR_REPORT(expr)   if(expr) {DGERROR(_T(#expr));}

/**
 * If the expression succeeded, report an error.
 * @param expr    The expression to be evaluated.
 * @param msg     Additional error message.
 */
#define ON_ERROR_REPORT2(expr, msg)   ON_ERROR_REPORT((expr) && (msg))

/**
 * Just report a message
 * How to use: DGREPORT(_T("Hello, World"));
 * @param msg  The error message.
 */
#ifdef ENABLE_REPORT
#define DGREPORT(msg)   {DG::ReportMsg(msg, _T(__FILE__), __LINE__);}
#else
#define DGREPORT(msg)
#endif
