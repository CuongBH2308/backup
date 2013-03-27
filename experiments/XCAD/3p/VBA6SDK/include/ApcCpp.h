/* --------------------------------------------------------------------------
 * apcCpp.h 
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
#ifndef APCCPP_H_INCLUDED
#define APCCPP_H_INCLUDED
/*
 * Use this file for non-MFC applications, or MFC applications that
 * deviate so significantly from standard MFC usage that the classes
 * in apcMfc.h are not of use.
 *
 * Preprocessor modifiers for this file:
 *
 * define an APC_IMPORT mode as described in Apc.h and ApcMidl.h:
 *      * Depending on the definition of this token, one of 
 *        Apc.h or ApcMidl.h will be included by apcCpp.h
 *      * Apc.h uses the VC #import feature for type libraries,
 *        resulting in the generation of .tli and .tlh files,
 *        which have advanced features which may be desireable.
 *        Consult the VC documentation for #import for details.
 *      * ApcMidl.h uses generated type library header files,
 *        which do not have the high level interfaces or proxy
 *        stub generation provided by #import.
 * define APC_MANGLED_ID if there is a conflict with ID() in 
 *        ApcProjectItem and ApcControl
 */
/* --------------------------------------------------------------------------
 * APC/C++ template library
 * --------------------------------------------------------------------------
 *
 *  CApcHost<T> -- base class for your application class
 *  CApcProject<T> - base class for your document class
 *  CApcProjectItem<T> - base class for project item
 *  CApcControl<T> - base class for control site or control
 *  CApcMacrosDialog<T> - base class for client of macros dialog
 * 
 * 
 * --------------------------------------------------------------------------
 * CApcHost<T> -- base class for your application class
 * --------------------------------------------------------------------------
 * 
 * features:
 *
 *	This template class provides:
 *	- a smart pointer to an IApc*
 *	- get functions for IApcEngine* and IApcCompManager*
 *	- an event sink for IApcEvents and an object that implements IApcSite
 *	- default handler functions for IApcEvents and IApcSite
 *	- an easy way to override those default handler functions
 *
 * declaration:
 *	
 *	For the template parameter T, pass the name of the class that is derived 
 *	from CApcHost. This allows the CApcHost template to call functions
 *	declared in your derived class. Example:
 *
 *	class CTTHost: public CApcHost<CTTHost> { ... };
 *
 * requirements:
 *
 *	Your derived class does not have to be a COM object, but it must:
 *	- call ApcHost.Create and ApcHost.Destroy to start up and shut down APC
 *	- notify APC when your main window receives certain window messages
 *	- defer closing the main window until the stack is unwound
 *	- provide an interface pointer to COM object that defines predefined 
 *	  global functions and variables in VBA
 *
 * MFC Notes:
 *
 *  MFC users should use CApcApplication instead. CApcApplication does derive 
 *	from CApcHost, so the members of this class will be available to a class
 *	derived from CApcApplication.
 *
 * accessors:
 * 
 *  ApcHost.GetAppObj			-- get ptr to IDispatch* of application object
 * 	ApcHost.GetMainWnd			-- get HWND that VBA thinks is the main window
 * 	ApcHost.operator ->			-- get ptr to IApc
 * 	ApcHost.GetApcCompManager	-- get ptr to IApcCompManager
 * 	ApcHost.GetApcHost			-- get ptr to IApc
 * 
 * data members:
 *
 *	ApcHost.m_fShutDownAfterUnwind	-- for WM_CLOSE handling
 *  ApcHost.m_fWmEnableFromCompMgr	-- for WM_ENABLE handling
 *	ApcHost.m_fHostIsActiveComponent-- for WM_ACTIVATE handling
 *	ApcHost.m_cModal				-- nesting count on modal state
 *	ApcHost.m_cMsgLoop				-- nesting count on message loops
 *	ApcHost.m_cFirstMsgLoop			-- nesting count of main message loop
 
operations:
 
  	HRESULT ApcHost.Create(			-- begin the VBA session

 	    HWND hWnd,
        BSTR bstrHostName,
        IDispatch* pdisp,
        BSTR bstrLicenseKey = NULL,
        long nLcid = NULL,
        BSTR bstrFileFilter = NULL,
        BSTR bstrRegKey = NULL)

		This function:
		1. creates IApcSite and CoCreates APCEngine
		2. calls ApcHost_OnCreate

		The ApcHost_OnCreate function is expected to
		call ApcHost.OnCreate().

	HRESULT ApcHost.OnCreate(		-- called by ApcHost_OnCreate

	    HWND hWnd,
        BSTR bstrHostName,
        IDispatch* pdisp,
        BSTR bstrLicenseKey,
        long nLcid,
        BSTR bstrFileFilter,
        BSTR bstrRegKey,
		IApcSite* pApcSite)

  	HRESULT ApcHost.Destroy()		-- end the VBA session

		stack must be unwound when calling this function
		calls ApcHost_OnDestroy

  	HRESULT ApcHost.MessageLoop(	-- run the main message loop

		BOOL* pfAborted = NULL)

 	HRESULT ApcHost.OnIdle(			-- call idle-time handlers in VBA

		BOOL* pfContinue, 
		BOOL fPeriodic = TRUE, 
		BOOL fPriority = TRUE, 
		BOOL fNonPeriodic = TRUE)

  	HRESULT ApcHost.End(			-- terminate execution of VBA code

		BOOL& fTerminated)

  	HRESULT ApcHost.WmActivate(		-- call in response to WM_ACTIVATE on main window

		WPARAM wParam)

  	HRESULT ApcHost.WmEnable(		-- call in response to WM_ENABLE on main window

		WPARAM wParam)

  	HRESULT ApcHost.WmClose(		-- call in response to WM_CLOSE on main window or child windows
	                                   setting hWnd as appropriate
		BOOL& fTerminated,
		HWND hWnd = NULL)			   set hWnd = NULL for the application window, 
									   or the the hWnd of the closing child window
		if (hWnd == NULL)
			if this function returns with fTerminated==TRUE, it is safe to shut down
			if this function returns with fTerminated==FALSE, then eat the WM_CLOSE
			message, and eventually the ApcHost_OnCloseHost function will get called.
		if (hWnd == child window hWnd)
			if this function returns with fTerminated==FALSE, then eat the WM_CLOSE
			This indicates a Reset has been initiated.

		This function calls ApcHost_OnWmClose.

 	HRESULT ApcHost.WmDestroy()		-- call in response to WM_DESTROY on main window

		this function will assert if the stack has not been unwound

   
IApcEvents notification:

	HRESULT ApcHost_BeforeRun()

	HRESULT ApcHost_AfterRun()

	HRESULT ApcHost_BeforePause()

	HRESULT ApcHost_AfterPause()

	HRESULT ApcHost_BeforeModalDialog(
		IApcProject* pProject)

	HRESULT ApcHost_AfterModalDialog(
		IApcProject* pProject)

	HRESULT ApcHost_Activate(
		BOOL* pfActivate)

	HRESULT ApcHost_NameChange(
		IApcProject* pProject,
		BSTR bstrOldName)

	HRESULT ApcHost_OpenProject(
		BSTR bstrProjectFileName, 
		IApcProject* pReferencingProject,
  		IApcProject** ppProject)

	HRESULT ApcHost_ShowHelp(
		BSTR bstrHelpFileName, 
		LONG lCommand, 
  		LONG lCommandData, 
		BOOL IsWinHelp,
		BOOL* pfShowHelp)

	HRESULT ApcHost_FindFile(
		BSTR bstrFileName, 
		BSTR* pbstrFullPath)
 
	HRESULT ApcHost_CreateMacro(
		BSTR ProcedureName, 
		IApcScope* CurrentScope, 
		BSTR Description, 
		VARIANT_BOOL* Created)

	HRESULT ApcHost_HostCheckReference(
		BOOL bSaving, 
		BSTR bstrLibraryGuid, 
		LONG* lMajorVersion, 
		LONG* lMinorVersion)

IApcSite notification:

	HRESULT ApcHost_ContinueIdle(
		BOOL* pfContinue)

	HRESULT ApcHost_DoIdle(
		BOOL* pfContinue)

	HRESULT ApcHost_EnterModalState()

	HRESULT ApcHost_LeaveModalState()

	HRESULT ApcHost_LostActivation()

	HRESULT ApcHost_HideBorderTools()

	HRESULT ApcHost_TrackingBegins()

	HRESULT ApcHost_TrackingEnds()

	HRESULT ApcHost_ShutDown()

overrides:

	HRESULT ApcHost_OnCreate()

	HRESULT ApcHost_OnDestroy()

	void ApcHost_OnMessageLoop(
		AxMessageLoopReason loopreason, 
		BOOL* pfAborted, 
		int* pnExitCode, 
		BOOL fPushedByHost)

	HRESULT ApcHost_OnIdle(
		BOOL* pfContinue)
	HRESULT ApcHost_OnTranslateMessage(
		MSG* pmsg, 
		BOOL* pfConsumed)

	HRESULT ApcHost_OnWmEnable(
		BOOL fEnable)
	HRESULT ApcHost_OnWmActivate()

	HRESULT ApcHost_OnWmClose(
		BOOL& fTerminated,
		HWND hWnd)
	HRESULT ApcHost_OnEnd(
		BOOL& fTerminated,
		HWND hWndClosing = NULL)
	HRESULT ApcHost_OnEnd(                    // provided for compatibility with RC4
		BOOL& fTerminated,
		BOOL fShuttingDownApp = FALSE)

	void ApcHost_OnStackUnwound()
	void ApcHost_OnCloseHost()
	void ApcHost_OnCloseProject()
 * 
 * 
 * --------------------------------------------------------------------------
 * CApcProject<T> - base class for your document class
 * --------------------------------------------------------------------------
 * 
 * features:
 *
 *	This template class provides:
 *	- a smart pointer to an IApcProject*
 *	- an event sink for IApcProjectEvents
 *	- default handler functions 
 *	- an easy way to override those default handler functions
 *	- management of the substorage for the APC project
 *	
 * declaration:
 *
 *	For the template parameter T, pass the name of the class that is derived 
 *	from CApcProject. This allows the CApcProject template to call functions
 *	declared in your derived class. Example:
 *
 *	class CGame: public CApcProject<CGame> { ... };
 *
 * requirements:
 *
 *	Your derived class does not have to be a COM object, but it must:
 *	- make a specific sequence of calls to Create, Open or Close a project
 *	- manage the parent IStorage* for the document
 *
 * To create a new project:
 *
 *	(1) create a docfile so that you'll have an IStorage* for ApcProject.InitNew
 *	(2) call ApcProject.Create(), then
 *	(3) call ApcProject.InitNew(), then
 *	(4) define project items and controls
 *	If Create() or InitNew() fails, call Close() to clean up
 *
 *	For example Tthost first creates a temporary docfile:
 *	
 *	Then it creates the ApcProject:
 *
 *	The document is now fully open.
 *	Next Tthost defines the game project item:
 *
 *	Then it defines a control for each square:
 *
 *
 * To open a project from storage:
 *
 *	(1) open a docfile so that you'll have an IStorage* for ApcProject.Load
 *	(2) register project items and controls, then
 *	(3) call ApcProject.Open(), then
 *	(4) call ApcProject.Load(), then
 *	(5) call ApcProject.FinishLoading()
 *	If Open(), Load() or FinishLoading() fails, call Close() to clean up
 *
 *	For example Tthost first opens an existing docfile:
 *	
 *	Then it reads its own data, creating the game project item and each control.
 *	When loading the game project item from a file, it calls Register:
 *
 *	When loading a square control from a file, it calls Register:
 *
 *	Then it finishs the load with these three calls:
 *
 *	During the above FinishLoad call, all the registered controls and 
 *	project items will receive the OnAttach() notification. If the registered
 *	controls and project items correspond to those in the VBA project, and
 *	if all of the OnAttach() notifications succeed, then the project will
 *	be open.
 *
 * To close a project:
 *
 *	(1) all the project items and controls should call Detach() (or be destructed)
 *	(2) call ApcProject.Close()
 *	(3) release the IStorage* of the docfile
 *
 *	When closing a document, Tthost calls RemoveAllSquares.
 *	When a square is destroying itself, it calls ApcControl.Detach():
 *
 *	Then the Game project item is destroyed, causing it to detach:
 *
 *	Then the APC project is closed:
 *
 *	Then the containing docfile is released:
 *
 * MFC Notes:
 *
 *  MFC users should use CApcDocument instead. CApcDocument does derive from
 *	CApcProject, so the members of this class will be available to a class
 *	derived from CApcDocument.
 *
 * accessors:
 * 
 * 	ApcProject.operator ->			-- get ptr to IApcProject
 * 	ApcProject.GetApcProject		-- get ptr to IApcProject
 * 
 * operations:
 * 
 * 	ApcProject.Create -- create a new APC project
 * 	ApcProject.Open -- open an existing APC project
 *	ApcProject.FinishLoading -- hook up project items and controls
 * 	ApcProject.Close -- shuts down project, discarding changes
 *
 * IPersistStorage operations:
 *
 * 	ApcProject.IsDirty()
 *	ApcProject.InitNew(IStorage* pStg)
 *	ApcProject.Load(IStorage* pStg)
 *	ApcProject.Save(IStorage* pStg, BOOL fSameAsLoad)
 *	ApcProject.SaveCompleted(IStorage* pStg)
 *	ApcProject.HandsOffStorage()
 *
 * notifications:
 * 
 * 	HRESULT ApcProject_Reset()
 * 	HRESULT ApcProject_Save()
 *	HRESULT ApcProject_ProjectItemCreated(IApcProjectItem* pProjectItem)
 * 	HRESULT ApcProject_ProjectItemDelete(IApcProjectItem* pProjectItem)
 * 	HRESULT ApcProject_ModeChange(AxProjectMode NewMode)
 * 	HRESULT ApcProject_NameChange(IApcProjectItem* pProjectItem, BSTR bstrOldName)
 * 	HRESULT ApcProject_ProcedureAdd(IApcProcedure* pProcedure)
 * 	HRESULT ApcProject_ProcedureDelete(IApcProjectItem* pProjectItem, 
 *		BSTR bstrName, AxProcedureType ProcedureType)
 * 	HRESULT ApcProject_ModuleChange(IApcProjectItem* pProjectItem)
 *  HRESULT ApcProject_OpenProjectItem(BSTR bstrName, long nID, IDispatch** ppHostProjectItem)
 * 	HRESULT ApcProject_ModuleDirtyChange(IApcProjectItem* pProjectItem, VARIANT_BOOL fDirty)
 *
 * overrides:
 * 
 * 	HRESULT ApcProject_OnAttach(IApcProject* pProject)
 * 	void	ApcProject_OnClose()
 * 	HRESULT ApcProject_OnMove(IStorage* pStg, BOOL fFullySaved)
 *	HRESULT ApcProject_OnRequestProjectItem(BSTR bstrName)
 * 
 * 
 * --------------------------------------------------------------------------
 * CApcProjectItem<T> - base class for project item
 * --------------------------------------------------------------------------
 *
 * features:
 *
 *	This template class provides:
 *	- a smart pointer to an IApcProjectItem*
 *	- an event sink for IApcProjectItemEvents
 *	- default handler functions 
 *	- an easy way to override those default handler functions
 *	- a Register function to reattach when the project loads
 *
 * declaration:
 *	
 *	For the template parameter T, pass the name of the class that is derived 
 *	from CApcProjectItem. This allows the CApcProjectItem template to call 
 *	functions declared in your derived class. Example:
 *
 *	class CPlayer: public CApcProjectItem<CPlayer> { ... };
 *
 * requiements:
 *
 *	Your derived class does not have to be a COM object, but it must:
 *	- provide an interface pointer to a COM object that acts as the HostObject
 *	- call Register() before the project is loaded
 *	- persist one BSTR so that it knows how to call Register
 *
 * MFC Notes:
 *
 *  MFC users can use this class directly. The MFC object should call 
 *	Register() in the IsLoading() case of its Serialize() function.
 * 
 * accessors:
 * 
 * 	ApcProjectItem.operator ->			-- get ptr to IApcProjectItem
 * 	ApcProjectItem.GetApcProjectItem	-- get ptr to IApcProjectItem
 * 
 * operations:
 * 
 * 	ApcProjectItem.Define -- add a new project item 
 *	ApcProjectItem.Undefine -- remove this project item 
 *	ApcProjectItem.Register -- call before loading the project
 * 	ApcProjectItem.Detach -- break the connection with the IApcProjectItem
 * 	ApcProjectItem.RegisterControl -- for controls with no CApcControl
 * 
 * notifications:
 * 
 * 	HRESULT ApcProjectItem_View()
 * 	HRESULT ApcProjectItem_Activate()
 *	HRESULT ApcProjectItem_CreateInstance(IDispatch **Instance);
 *	HRESULT ApcProjectItem_ReleaseInstances();
 *	HRESULT ApcProjectItem_InstanceCreated(IDispatch *Instance);
 *
 * overrides:
 * 
 *  template <class _Project> HRESULT ApcProjectItem_OnDefine(_Project& project, IDispatch* pdisp, BSTR bstrRequestName, BSTR* pbstrActualName)
 *	HRESULT ApcProjectItem_OnUndefine()
 * 	HRESULT ApcProjectItem_OnAttach(IApcProjectItem* pApcProjectItem)
 * 	void ApcProjectItem_OnDetach()
 *	void ApcProjectItem_OnLoadComplete()
 *
 * 
 * --------------------------------------------------------------------------
 * CApcControl<T> - base class for control site or control
 * --------------------------------------------------------------------------
 *
 * features:
 * 
 *	This template class provides:
 *	- a smart pointer to an IApcControl*
 *	- an event sink for IApcControlEvents
 *	- default handler functions 
 *	- an easy way to override those default handler functions
 *	- a Register function to reattach when the project loads
 *	
 * declaration:
 *
 *	For the template parameter T, pass the name of the class that is derived 
 *	from CApcControl. This allows the CApcControl template to call functions 
 *	declared in your derived class. Example:
 *
 *	class CSquareSite: public CApcControl<CSquareSite> { ... };
 *
 * requirements:
 *
 *	Your derived class does not have to be a COM object, but it must:
 *	- provide an interface pointer to a COM object that acts as the HostObject
 *	- call Register() before the project is loaded
 *	- persist one DWORD or one BSTR so that it knows how to call Register
 *
 * MFC Notes:
 *
 *  MFC users can use this class directly. The MFC object should call 
 *	Register() in the IsLoading() case of its Serialize() function.
 *
 * accessors:
 * 
 * 	ApcControl.operator ->			-- get ptr to IApcControl
 * 	ApcControl.GetApcControl		-- get ptr to IApcControl
 * 
 * operations:
 * 
 * 	ApcControl.Define -- add a new control 

		_ProjectItem& projectItem
		IDispatch* pHostControl
		IDispatch* pExtender = NULL

 *	ApcControl.Undefine -- remove this control 

 *	ApcControl.Register -- call before loading the project

		ProjItem& projItem or IApcRegControls* pRegs
		BSTR bstrName or long nID
		IDispatch* pHostControl
		IDispatch* pExtender = NULL

 * 	ApcControl.Detach - break the connection with the IApcControl
 * 
 * IApcControlEvents notification:
 *  
 * 	HRESULT ApcControl_Activate()
 * 
 * overrides:
 *  
 *	HRESULT ApcControl_OnUndefine()
 *	HRESULT ApcControl_OnRegister(REFIID riid, void** ppv)
 * 	HRESULT ApcControl_OnAttach(IApcControl* pApcControl)
 * 	HRESULT ApcControl_OnAttach(IApcControl* pApcControl)
 * 	void	ApcControl_OnDetach()
 * 
 * 
 * --------------------------------------------------------------------------
 * boolean conversions  - the conversion is named after the expected type
 * --------------------------------------------------------------------------
 * 
 *  ApcInBOOL			- returns a BOOL given a VARIANT_BOOL argument
 *  ApcInVARIANT_BOOL	- returns a VARIANT_BOOL given a BOOL argument
 *  ApcInOutBOOL		- provides a BOOL* given a VARIANT_BOOL* argument
 *  ApcInOutVARIANT_BOOL- provides a VARIANT_BOOL* given a BOOL* argument
 *  ApcOutBOOL			- provides a BOOL* given a VARIANT_BOOL* argument
 *  ApcOutVARIANT_BOOL	- provides a VARIANT_BOOL* given a BOOL* argument
 * 
 * -------------------------------------------------------------------------- */

#pragma warning(disable: 4786)

#ifndef __ATLCOM_H__
	#error apcCpp.h requires atlcom.h to be included first
	//
	// For an MFC or mixed MFC/CPP application, use apcMfc.h instead
	//
	// An ATL application, somewhere prior to the #include <apcCpp.h>, should 
	// have something like these lines in an internal header file (typically 
	// in precomp.h or stdafx.h):
	// 
	//	// ATL stuff
	//	//
	//	#include <atlbase.h>
	//	extern CComModule _Module;
	//	#include <atlcom.h>
	//	#include <atlctl.h>
	//
	//	// APC stuff
	//	//
	//	#include <apcCpp.h>
	//
	// ATL requires that the symbol "_Module" be global to the DLL or EXE in 
	// which it resides, but should not be exported beyond the DLL or EXE.
	//
	// It is also common to define the global "_Module" differently.
	//
	// An ATL application should have something like these lines in a CPP file
	// that is not often compiled (typically in precomp.cpp or stdafx.cpp):
	//
	//	#include <initguid.h>
	//
	//	// ATL stuff
	//	//
	//	#include <atlimpl.cpp>
	//	#include <atlctl.cpp>
	//	#ifdef _ATL_STATIC_REGISTRY
	//	#include <statreg.h>
	//	#include <statreg.cpp>
	//	#endif
	//
	//	// APC stuff
	//	//
	//	#include <apcGuids.h>
	//	#include <apcImpl.cpp>
	//
	// An ATL application should at mimimum have these lines somewhere
	// in a CPP file:
	//
	//	CComModule _Module;
	//
	//	BEGIN_OBJECT_MAP(ObjectMap)
	//	END_OBJECT_MAP()
	//
	// Also, if there are any entries in the object map, a full declaration
	// of the class for each entry must appear before the object map.
	//
#endif

/////////////////////////////////////////////////////////////////////////////

#if (defined(APC_IMPORT_MODE) && !defined(APC_IMPORT_FULL))
	#error *** APC_IMPORT_MODE is no longer supported.  See comments below ***
	//
	// Release Note:
	// -------------
	// Previous beta releases of this SDK had an alternate mechanism for 
	// specifying the import mode.  This involved #defining APC_IMPORT_MODE
	// to be one of, or a bitwise combination of the above import modes.
	//
	// Because of restructuring intended to simplify these header files, 
	// that mechanism had to be changed.  Typically, to convert to the 
	// new mechanism, simply #define any import mode modifiers needed
	// and #include one of either apcMidl.h or apc.h.  The file apcMidl.h
	// is for APC_IMPORT_MIDL, which uses type library header files.  The 
	// file apc.h is for the remaining import modes (except custom), which
	// uses #import to generate .tlh and .tli files.
	//
	// For example.
	//
	// If formerly you specified...
	//    #define APC_IMPORT_MODE APC_IMPORT_MIDL
	// ...substitute the following:
	//    #define APC_IMPORT_MIDL
	//
	// If formerly you specified...
	//    #define APC_IMPORT_MODE APC_IMPORT_FULL
	// ...substitute the following:
	//    #define APC_IMPORT_FULL
	//
	// Likewise, if you formerly specified...
	//    #define APC_IMPORT_MODE APC_IMPORT_NAMED_GUIDS | APC_IMPORT_RAW_ONLY
	// ...substitute the following:
	//    #define APC_IMPORT_NAMED_GUIDS
	//    #define APC_IMPORT_RAW_ONLY
	//
#endif

#if (!defined(APC_IMPORT_FULL) && !defined(APC_IMPORT_CUSTOM) && !defined(APC_IMPORT_NAMED_GUIDS) && !defined(APC_IMPORT_RAW_ONLY) && !defined(APC_IMPORT_MIDL))
	//
	// APC_IMPORT_MIDL is the default
	//
	#pragma message(__FILE__ " : APC warning : APC_IMPORT_MIDL not defined, using default")
	#define APC_IMPORT_MIDL
#endif

#ifdef APC_IMPORT_CUSTOM
	// custom includes required
#elif defined(APC_IMPORT_MIDL)
	#include "apcMidl.h"
#else
	#include "apc.h"
#endif

/////////////////////////////////////////////////////////////////////////////

namespace MSAPC 
{

///////////////////////////////////////////////////////////////////////////
// private:

extern "C" const IID IID_IApcRegProject;
extern "C" const IID IID_IApcRegProjItems;
extern "C" const IID IID_IApcRegProjItem;
extern "C" const IID IID_IApcRegControls;
extern "C" const IID IID_IApcRegControl;

struct __declspec(uuid("db117191-e5fa-11d1-9a70-00a024941ef0")) IApcRegProject: IUnknown
{
	STDMETHOD(Request)(BSTR bstrName) = 0;
};

struct __declspec(uuid("db117192-e5fa-11d1-9a70-00a024941ef0")) IApcRegProjItems: IUnknown
{
	STDMETHOD(Init)(IUnknown* pRegProject) = 0;
	STDMETHOD(Register)(IUnknown* pRegProjItem, BSTR bstrName, long nID, IDispatch* pdisp, DWORD* pdwCookie) = 0;
	STDMETHOD(Revoke)(DWORD dwCookie) = 0;
	STDMETHOD(Bind)(IApcProject*) = 0;
	STDMETHOD(FinishLoad)() = 0;
	STDMETHOD(LoadComplete)(BOOL fGood) = 0;
};

struct __declspec(uuid("db117193-e5fa-11d1-9a70-00a024941ef0")) IApcRegProjItem: IUnknown
{
	STDMETHOD(Attach)(IApcProjectItem*) = 0;
	STDMETHOD(FinishLoad)() = 0;
	STDMETHOD(LoadComplete)(BOOL fGood) = 0;
};

struct __declspec(uuid("db117194-e5fa-11d1-9a70-00a024941ef0")) IApcRegControls: IUnknown
{
	STDMETHOD(Register)(IUnknown* pRegControl, BSTR bstrName, long nID, IDispatch* pHostControl, IDispatch* pExtender, DWORD* pdwCookie) = 0;
	STDMETHOD(Revoke)(DWORD dwCookie) = 0;
	STDMETHOD(Bind)(IApcProjectItem*) = 0;
	STDMETHOD(FinishLoad)() = 0;
	STDMETHOD(LoadComplete)(BOOL fGood) = 0;
};

struct __declspec(uuid("db117195-e5fa-11d1-9a70-00a024941ef0")) IApcRegControl: IUnknown
{
	STDMETHOD(Attach)(IApcControl*) = 0;
	STDMETHOD(FinishLoad)() = 0;
	STDMETHOD(LoadComplete)(BOOL fGood) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// global functions

// see apcImpl.cpp

HRESULT ApcCreateRegProjItems(IApcRegProjItems**);
HRESULT ApcCreateRegControls(IApcRegControls**);
HRESULT ApcQueryService(IUnknown* punk, REFGUID guidService, REFIID iid, void** ppv);
HRESULT ApcFindProject(IApc* pHost, BSTR bstrRefName, IApcProject** ppProject);
HRESULT ApcFindProjectItem(IApcProject* pProject, long nID, IApcProjectItem** ppProjectItem);
HRESULT ApcFindProjectItem(IApcProject* pProject, BSTR bstrName, IApcProjectItem** ppProjectItem);
HRESULT ApcFindControl(IApcProjectItem* pProjectItem, long nID, IApcControl** ppControl);
HRESULT ApcFindControl(IApcProjectItem* pProjectItem, BSTR bstrName, IApcControl** ppControl);
HRESULT ApcFireEvent(IUnknown* punk, REFIID iid, DISPID dispid, DISPPARAMS* pDispParams /*= NULL*/, VARIANT* pVarResult /*= NULL*/);
HRESULT ApcApplyPropertyMap(IApcControl* pControl, const struct APC_PROPERTY_MAP* pmap);

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// ApcEntryHR	   - used at the top of each function
// ApcNotifyHR - used at the top of each event-notification function
// ApcCallHR   - used to wrap a call in functions that return an HRESULT
// ApcCallF	   - used to wrap a call in functions that return an BOOL
// ApcReturnHR - used to wrap a return in functions that return an HRESULT
// ApcReturnHR - used to wrap a return in functions that return an BOOL

#define ApcEntryV(name) 
#define ApcEntryHR(name) HRESULT hr;
#define ApcNotifyV(name,expr) { (expr); }
#define ApcNotifyHR(name,expr) (expr)
#define ApcCallHR(call) { hr=(call); if (FAILED(hr)) ApcReturnHR(hr); }
#define ApcCallF(call) { hr=(call); if (FAILED(hr)) ApcReturnF(FALSE); }
#define ApcCallV(call) { HRESULT hr=(call); if (FAILED(hr)) { _ASSERTE(FALSE); return; }}
#define ApcReturnHR(hr) { return (hr); }
#define ApcReturnF(f) { return SUCCEEDED(f); }

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use
// CApcComPtr - smart pointer
//
// like CComPtr<T>, but public interface is read-only
// protected interface has an assignment operator

template <class T>
class CApcComPtr: private CComPtr<T>
{
private:
	CApcComPtr<T>& operator=(const CApcComPtr<T>&){ return *this; }
protected:
	typedef CApcComPtr<T> _ApcComPtr;
	void OnAttach(T* pT){ _ASSERTE(pT); _ASSERTE(!p); p = pT; p->AddRef(); }
	void OnDetach(){Release();}
public:
	operator T*()	{return CComPtr<T>::operator T*();}
	T* operator->() {return CComPtr<T>::operator->();}
	bool operator!(){return CComPtr<T>::operator!(); }
	bool operator==(T* pT) const {return p == pT;}
	bool operator!=(T* pT) const {return p != pT;}
};

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// boolean conversions  - the conversion is named after the expected type
//
// use these functions in-line in the parameter list of a function call
// to select the proper function, use the name of the parameter type

inline BOOL ApcInBOOL(VARIANT_BOOL b) 
{
	return b != VARIANT_FALSE;
}

inline VARIANT_BOOL ApcInVARIANT_BOOL(BOOL f) 
{
	return f ? VARIANT_TRUE : VARIANT_FALSE;
}

class ApcInOutBOOL
{
	VARIANT_BOOL& b;
	BOOL f;
public:
	ApcInOutBOOL(VARIANT_BOOL* pb): b(*pb), f(ApcInBOOL(b)) {}
	~ApcInOutBOOL() { b = ApcInVARIANT_BOOL(f); }
	operator BOOL*() { return &f; }
	operator long*() { return (long*)&f; }
};

class ApcInOutVARIANT_BOOL
{
	BOOL& f;
	VARIANT_BOOL b;
public:
	ApcInOutVARIANT_BOOL(BOOL* pf): f(*pf), b(ApcInVARIANT_BOOL(f)) {}
	~ApcInOutVARIANT_BOOL() { f = ApcInBOOL(b); }
	operator VARIANT_BOOL*() { return &b; }
};

class ApcOutBOOL
{
	VARIANT_BOOL& b;
	BOOL f;
public:
	ApcOutBOOL(VARIANT_BOOL* pb): b(*pb), f(FALSE) {}
	~ApcOutBOOL() { b = ApcInVARIANT_BOOL(f); }
	operator BOOL*() { return &f; }
	operator long*() { return (long*)&f; }
};

class ApcOutVARIANT_BOOL
{
	BOOL& f;
	VARIANT_BOOL b;
public:
	ApcOutVARIANT_BOOL(BOOL* pf): f(*pf), b(VARIANT_FALSE) {}
	~ApcOutVARIANT_BOOL() { f = ApcInBOOL(b); }
	operator VARIANT_BOOL*() { return &b; }
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// ApcVariantAliasForBstr
// ApcVariantAliasForDispatch

struct ApcVariantAliasForBstr: public VARIANT
{
	ApcVariantAliasForBstr(BSTR bstr)
	{
		VariantInit(this);
		V_VT(this) = VT_BSTR;
		V_BSTR(this) = bstr;
	}
};

struct ApcVariantAliasForDispatch: public VARIANT
{
	ApcVariantAliasForDispatch(IDispatch* pdisp)
	{
		VariantInit(this);
		V_VT(this) = VT_DISPATCH;
		V_DISPATCH(this) = pdisp;
	}
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcHostEvents -- used internally by CApcHost and CApcHostMember to implement an event sink 
//

template <class HostOwner>
class ATL_NO_VTABLE CApcHostEvents 
:
	public ISupportErrorInfoImpl<&APC_IID(IApcEvents)>,
	public IApcEvents,
	public CComObjectRootEx< CComObjectThreadModel >
{
	HostOwner* m_pHostOwner;

public:
	typedef HostOwner _HostOwner;
	typedef CApcHostEvents<_HostOwner> _CApcHostEvents;
	typedef CComObjectNoLock<_CApcHostEvents> _Object;

	BEGIN_COM_MAP(_CApcHostEvents)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(APC_IID(IApcEvents), IApcEvents)
	END_COM_MAP()

	static HRESULT CreateInstance(_HostOwner* pHostOwner, IApcEvents** pp)
	{
		HRESULT hRes = E_OUTOFMEMORY;
		_Object* p = NULL;
		ATLTRY(p = new _Object(0))
		if (p != NULL)
		{
			p->SetVoid(0);
			p->InternalFinalConstructAddRef();

			p->Init(pHostOwner);

			hRes = p->FinalConstruct();
			p->InternalFinalConstructRelease();
			if (hRes == S_OK)
				hRes = p->QueryInterface(APC_IID(IApcEvents), (void**)pp);
			if (hRes != S_OK)
				delete p;
		}
		return NOERROR;
	}

	CApcHostEvents()
	{
		m_pHostOwner = 0;
	}

	HRESULT Init(_HostOwner* pHostOwner)
	{
		_ASSERTE(0 == m_pHostOwner); // already attached?
		_ASSERTE(0 != pHostOwner); // argument is required
		m_pHostOwner = pHostOwner;
		return NOERROR;
	}

	// IApcEvents
	//
	STDMETHODIMP APC_RAW(BeforeRun)()
	{
		return ApcNotifyHR(("ApcHost_BeforeRun"), m_pHostOwner->ApcHost_BeforeRun());
	}
	STDMETHODIMP APC_RAW(AfterRun)()
	{
		return ApcNotifyHR(("ApcHost_AfterRun"), m_pHostOwner->ApcHost_AfterRun());
	}
	STDMETHODIMP APC_RAW(BeforePause)()
	{
		return ApcNotifyHR(("ApcHost_BeforePause"), m_pHostOwner->ApcHost_BeforePause());
	}
	STDMETHODIMP APC_RAW(AfterPause)()
	{
		return ApcNotifyHR(("ApcHost_AfterPause"), m_pHostOwner->ApcHost_AfterPause());
	}
	STDMETHODIMP APC_RAW(BeforeModalDialog)(IApcProject* pProject)
	{
		return ApcNotifyHR(("ApcHost_BeforeModalDialog"), m_pHostOwner->ApcHost_BeforeModalDialog(pProject));
	}
	STDMETHODIMP APC_RAW(AfterModalDialog)(IApcProject* pProject)
	{
		return ApcNotifyHR(("ApcHost_AfterModalDialog"), m_pHostOwner->ApcHost_AfterModalDialog(pProject));
	}
	STDMETHODIMP APC_RAW(Activate)(VARIANT_BOOL* pbActivate)
	{
		return ApcNotifyHR(("ApcHost_Activate"), m_pHostOwner->ApcHost_Activate(ApcInOutBOOL(pbActivate)));
	}
	STDMETHODIMP APC_RAW(NameChange)(IApcProject* pProject, BSTR bstrOldName)
	{
		return ApcNotifyHR(("ApcHost_NameChange"), m_pHostOwner->ApcHost_NameChange(pProject, bstrOldName));
	}
	STDMETHODIMP APC_RAW(OpenProject)(BSTR bstrProjectFileName, IApcProject* pReferencingProject, IApcProject** ppProject)
	{
		return ApcNotifyHR(("ApcHost_OpenProject"), m_pHostOwner->ApcHost_OpenProject(bstrProjectFileName, pReferencingProject, ppProject));
	}
	STDMETHODIMP APC_RAW(ShowHelp)(BSTR bstrHelpFileName, LONG lCommand, LONG lCommandData, VARIANT_BOOL bIsWinHelp, VARIANT_BOOL* pbShowHelp)
	{
		return ApcNotifyHR(("ApcHost_ShowHelp"), m_pHostOwner->ApcHost_ShowHelp(bstrHelpFileName, lCommand, lCommandData, ApcInBOOL(bIsWinHelp), ApcInOutBOOL(pbShowHelp)));
	}
	STDMETHODIMP APC_RAW(FindFile)(BSTR bstrFileName, BSTR* pbstrFullPath)
	{
		return ApcNotifyHR(("ApcHost_FindFile"), m_pHostOwner->ApcHost_FindFile(bstrFileName, pbstrFullPath));
	}
	STDMETHODIMP APC_RAW(CreateMacro)(BSTR bstrProcedureName, IApcScope* pCurrentScope, BSTR bstrDescription, VARIANT_BOOL* pfCreated)
	{
		return ApcNotifyHR(("ApcHost_CreateMacro"), m_pHostOwner->ApcHost_CreateMacro(bstrProcedureName, pCurrentScope, bstrDescription, ApcInOutBOOL(pfCreated)));
	}
	STDMETHODIMP APC_RAW(HostCheckReference)(VARIANT_BOOL bSaving, BSTR bstrLibraryGuid, LONG* lMajorVersion, LONG* lMinorVersion)
	{
		return ApcNotifyHR(("ApcHost_HostCheckReference"), m_pHostOwner->ApcHost_HostCheckReference(ApcInBOOL(bSaving), bstrLibraryGuid, lMajorVersion, lMinorVersion));
	}
}; // class CApcHostEvents 


/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcSite -- used internally by CApcHost and CApcHostMember to implement an IApcSite
//

template <class HostOwner>
class ATL_NO_VTABLE CApcSite:
	public CComCoClass<CApcSite<HostOwner>, NULL>,
	public CComObjectRootEx< CComObjectThreadModel >,
	public IApcSite
{
	HostOwner* m_pHostOwner;

public:
	typedef HostOwner _HostOwner;
	typedef CApcSite< _HostOwner> _CApcSite;
	typedef CComObjectNoLock<_CApcSite> _Object;

	BEGIN_COM_MAP(_CApcSite)
		COM_INTERFACE_ENTRY_IID(APC_IID(IApcSite), IApcSite)
	END_COM_MAP()

	static HRESULT CreateInstance(_HostOwner* pHostOwner, _CApcSite** pp)
	{
		HRESULT hRes = E_OUTOFMEMORY;
		_Object* p = NULL;
		ATLTRY(p = new _Object(0))
		if (p != NULL)
		{
			p->SetVoid(0);
			p->InternalAddRef();

			p->Init(pHostOwner);

			hRes = p->FinalConstruct();

			if (hRes != S_OK)
				delete p;

			*pp = p;
		}
		return NOERROR;
	}

	CApcSite()
	{
		m_pHostOwner = 0;
	}

	HRESULT Init(_HostOwner* pHostOwner)
	{
		_ASSERTE(0 == m_pHostOwner); // already attached?
		_ASSERTE(0 != pHostOwner); // argument is required?
		m_pHostOwner = pHostOwner;
		return NOERROR;
	}

	// IApcSite
	//

	STDMETHODIMP APC_RAW(ContinueIdle)(APC_BOOL* pfContinue)
	{
		return ApcNotifyHR(("ApcHost_ContinueIdle"), m_pHostOwner->ApcHost_ContinueIdle((BOOL*)pfContinue));
	}

	STDMETHODIMP APC_RAW(DoIdle)()
	{
		BOOL fContinue;
		return ApcNotifyHR(("ApcHost_DoIdle"), m_pHostOwner->ApcHost_DoIdle(&fContinue));
	}

	STDMETHODIMP APC_RAW(EnterModalState)()
	{
		return ApcNotifyHR(("ApcHost_EnterModalState"), m_pHostOwner->ApcHost_EnterModalState());
	}

	STDMETHODIMP APC_RAW(LeaveModalState)()
	{
		return ApcNotifyHR(("ApcHost_LeaveModalState"), m_pHostOwner->ApcHost_LeaveModalState());
	}

	STDMETHODIMP APC_RAW(LostActivation)()
	{
		return ApcNotifyHR(("ApcHost_LostActivation"), m_pHostOwner->ApcHost_LostActivation());
	}

	STDMETHODIMP APC_RAW(HideBorderTools)()
	{
		return ApcNotifyHR(("ApcHost_HideBorderTools"), m_pHostOwner->ApcHost_HideBorderTools());
	}

	STDMETHODIMP APC_RAW(TrackingBegins)()
	{
		return ApcNotifyHR(("ApcHost_TrackingBegins"), m_pHostOwner->ApcHost_TrackingBegins());
	}

	STDMETHODIMP APC_RAW(TrackingEnds)()
	{
		return ApcNotifyHR(("ApcHost_TrackingEnds"), m_pHostOwner->ApcHost_TrackingEnds());
	}

	STDMETHODIMP APC_RAW(PushMessageLoop)(AxMessageLoopReason LoopReason, APC_BOOL* pfAborted)
	{
		return ApcNotifyHR(("ApcHost_PushMessageLoop"), m_pHostOwner->ApcHost_PushMessageLoop(LoopReason, (BOOL*) pfAborted));
	}

	STDMETHODIMP APC_RAW(ShutDown)()
	{
		return ApcNotifyHR(("ApcHost_ShutDown"), m_pHostOwner->ApcHost_ShutDown());
	}
}; // class CApcSite

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcHostMember -- this is the "ApcHost" member of CApcHost
//

template <class _HostOwner, class _ApcSite = CApcSite<_HostOwner> >
class CApcHostMember: public CApcComPtr<IApc>
{
	_HostOwner* m_pHostOwner;
	_ApcSite* m_pApcSite;

	typedef CApcHostEvents<_HostOwner> _Sink;
	CComPtr<IApcEvents> m_spHostEvents;
	long m_dwAdvise;

	HWND m_hWnd;
	CComPtr<IApcCompManager> m_spApcCompManager;
	CComPtr<IDispatch> m_spAppObj;

public:
	//
	// Members
	//

	HWND m_hWndClosing;
    BOOL m_fWmEnableFromCompMgr;
    BOOL m_fHostIsActiveComponent;
	int m_cMsgLoop;
	int m_cModal;
	int m_cFirstMsgLoop;

	//
	// Accessors
	// 

	IDispatch*				GetAppObj() { return m_spAppObj; }
	HWND					GetMainWnd() { return m_hWnd; }
	IApc*					GetApcHost() { return *this; }
	IApcCompManager*		GetApcCompManager() { return m_spApcCompManager; }

	//
	// Lifetime
	//

	CApcHostMember(_HostOwner* pHostOwner)
	:
		m_pHostOwner(pHostOwner),
		m_pApcSite(NULL),
		m_dwAdvise(0),
		m_hWndClosing(NULL),
		m_fWmEnableFromCompMgr(FALSE),
		m_fHostIsActiveComponent(TRUE),
		m_cMsgLoop(0),
		m_cModal(0),
		m_cFirstMsgLoop(0)
	{
		_ASSERTE(pHostOwner); // argument is required
	}

	~CApcHostMember()
	{
		_ASSERTE(!GetApcHost()); // forgot to call Destroy?
		if (GetApcHost())
			Destroy(); // still fully attached, so call ApcHost_Destroy
		else
			OnDestroy(); // not fully attached, so quietly shut down
	}

	//
	// Operations
	//

	// ApcHost.Create
	HRESULT Create(
	    HWND hWnd,
        BSTR bstrHostName,
        IDispatch* pdisp,
        BSTR bstrLicenseKey = NULL,
        long nLcid = 0,
        BSTR bstrFileFilter = NULL,
        BSTR bstrRegKey = NULL)
	{
		ApcEntryHR(CApcHostMember::Create);

		//
		// _Create does the work
		//
		hr = _Create(hWnd, bstrHostName, pdisp, bstrLicenseKey, 
			nLcid, bstrFileFilter, bstrRegKey);

		if (FAILED(hr))
			Destroy();

		ApcReturnHR(hr);
	}

	// ApcHost.OnCreate
	HRESULT OnCreate()
	{
		ApcEntryHR(CApcHostMember::OnCreate);

		ApcCallHR(_Sink::CreateInstance(m_pHostOwner, &m_spHostEvents.p));
		ApcCallHR(GetApcHost()->APC_RAW(AdviseApcEvents)(m_spHostEvents.p, &m_dwAdvise));

		ApcCallHR(GetApcHost()->QueryInterface(APC_IID(IApcCompManager), (void**)&m_spApcCompManager));

		hr = GetApcCompManager()->APC_RAW(HostActivate)();
		_ASSERTE(SUCCEEDED(hr));

		ApcReturnHR(hr);
	}

	// ApcHost.Destroy
	void Destroy()
	{
		ApcEntryV(CApcHostMember::Destroy);

		// assert that the stack has been unwound
		_ASSERTE(m_cMsgLoop == m_cFirstMsgLoop || 0 == m_cFirstMsgLoop); // forgot to call WmClose()?
		_ASSERTE(!m_hWndClosing); // ignoring fTerminated from WmClose()?

		ApcNotifyV(("ApcHost_OnDestroy"), m_pHostOwner->ApcHost_OnDestroy());
	}

	// ApcHost.OnDestroy
	void OnDestroy()
	{
		ApcEntryV(CApcHostMember::OnDetach);

		if (GetApcHost() && m_dwAdvise)
		{
			GetApcHost()->APC_RAW(UnadviseApcEvents)(m_dwAdvise);
			m_dwAdvise = 0;
		}

		if (m_pApcSite)
		{
			m_pApcSite->InternalRelease();
			m_pApcSite = 0;
		}

		m_spApcCompManager.Release();
		m_spAppObj.Release();
		m_spHostEvents.Release();

		_ApcComPtr::OnDetach();
	}

	// MessageLoop - generic host message loop
	int MessageLoop(BOOL* pfAborted = NULL)
	{
		ApcEntryV(CApcHostMember::MessageLoop);

		int nExitCode = 0;
		ApcNotifyV(("ApcHost_OnMessageLoop"), m_pHostOwner->ApcHost_OnMessageLoop((AxMessageLoopReason) 0, pfAborted, &nExitCode, TRUE));
		return nExitCode;
	}

	void OnIdle(BOOL* pfContinue, BOOL fPeriodic = TRUE, BOOL fPriority = TRUE, BOOL fNonPeriodic = TRUE)
	{
		*pfContinue = FALSE;

		if (!GetApcCompManager()) 
			return;

		// if we have periodic idle tasks that to be done, 
		// do them and return TRUE.
		if (fPeriodic) 
		{
			GetApcCompManager()->APC_RAW(DoIdle)(axIdlePeriodic, (APC_BOOL*)pfContinue);
			if (*pfContinue) 
				return;
		}

		// if any high priority idle tasks need to be done,
		// do it, and return TRUE.
		if (fPriority)
		{
			GetApcCompManager()->APC_RAW(DoIdle)(axIdlePriority, (APC_BOOL*)pfContinue);
			if (*pfContinue) 
				return;
		}

		// if any lower priority idle tasks need to be done,
		// do it, and return TRUE.
		if (fNonPeriodic)
		{
			GetApcCompManager()->APC_RAW(DoIdle)(axIdleNonPeriodic, (APC_BOOL*)pfContinue);
			if (*pfContinue) 
				return;
		}
	}


	// End - terminate macro execution
	//
	// on return, if fTerminated is false, then stack is being unwound
	//
	void End(BOOL& fTerminated, HWND hWndClosing)
	{
		ApcEntryV(CApcHostMember::End);

		if (!GetApcHost())
		{
			fTerminated = TRUE;
			return;
		}

		ApcNotifyV(("ApcHost_OnEnd"), m_pHostOwner->ApcHost_OnEnd(fTerminated, hWndClosing));
	}

	void OnEnd(BOOL& fTerminated, HWND hWndClosing)
	{
		ApcEntryV(CApcHostMember::OnEnd);

		// can only fail because of RPC error
		if (FAILED(GetApcHost()->APC_RAW(End)(ApcInOutVARIANT_BOOL(&fTerminated))))
			fTerminated = FALSE;

		if (hWndClosing && !fTerminated)
		{
			if (m_hWndClosing != GetMainWnd())
				m_hWndClosing = hWndClosing;
		}
	}

	// WmActivate - call this when your main window gets WM_ACTIVATE
	void WmActivate(WPARAM wParam)
	{
		ApcEntryV(CApcHostMember::WmActivate);

		if (WA_INACTIVE != LOWORD(wParam))
			ApcNotifyV(("ApcHost_OnWmActivate"), m_pHostOwner->ApcHost_OnWmActivate());
	}

	void OnWmActivate()
	{
		// our main window got a WM_ACTIVATE

		// tell the component manager that we are the active component
        if (GetApcCompManager())
			GetApcCompManager()->APC_RAW(HostActivate)();

		// remember that we told the component manager
		// ApcHost.LostActivation will clear this value
        m_fHostIsActiveComponent = TRUE;
	}

	// WmEnable - call this when your main window gets WM_ENABLE
	void WmEnable(WPARAM wParam)
	{
		ApcEntryV(CApcHostMember::WmEnable);

		ApcNotifyV(("ApcHost_OnWmEnable"), m_pHostOwner->ApcHost_OnWmEnable(0 != wParam));
	}

	void OnWmEnable(BOOL fEnable)
	{
		// main window got a WM_ENABLE

		// notify the component manager (if there is one), unless we
		// are already responding to a component manager notification.
		// (that would cause infinite recursion)

		if (!m_fWmEnableFromCompMgr && GetApcCompManager())
			GetApcCompManager()->APC_PUT(ModalState)(!fEnable);
	}

	// WmClose - call this when your main window gets WM_CLOSE
	//
	// on return, if fTerminated is false, then ignore the WM_CLOSE message
	//
	void WmClose(BOOL& fTerminated, HWND hWndClosing = NULL)
	{
		ApcEntryV(CApcHostMember::WmClose);

		if (hWndClosing == NULL)
			hWndClosing = GetMainWnd();

		ApcNotifyV(("ApcHost_OnWmClose"), m_pHostOwner->ApcHost_OnWmClose(fTerminated, hWndClosing));
	}

	void OnWmClose(BOOL& fTerminated, HWND hWnd)
	{
		ApcEntryV(CApcHostMember::OnWmClose);
		End(fTerminated, hWnd);
	}

	// ApcHost.WmDestroy
	void WmDestroy()
	{
		_ASSERTE(m_cMsgLoop == m_cFirstMsgLoop); // forgot to call WmClose()?
		_ASSERTE(!m_hWndClosing); // ignoring fTerminated from WmClose()?
	}

	void StackUnwound()
	{
		ApcEntryV(CApcHostMember::StackUnwound);
		ApcNotifyV(("ApcHost_OnStackUnwound"), m_pHostOwner->ApcHost_OnStackUnwound());
	}

	void OnStackUnwound()
	{
		ApcEntryV(CApcHostMember::OnStackUnwound);

		_ASSERTE(m_cMsgLoop == m_cFirstMsgLoop); // stack should be empty

		if (m_hWndClosing)
		{
			HWND hWndClosing = m_hWndClosing;
			m_hWndClosing = NULL;
			if (hWndClosing == GetMainWnd())
				ApcNotifyV(("ApcHost_OnCloseHost"), m_pHostOwner->ApcHost_OnCloseHost())
			else
				ApcNotifyV(("ApcHost_OnCloseProject"), m_pHostOwner->ApcHost_OnCloseProject(hWndClosing));
		}
	}

	void OnCloseHost()
	{
		ApcEntryV(CApcHostMember::CloseHost);

		_ASSERTE(m_cMsgLoop == m_cFirstMsgLoop); // stack should be empty

		// post WM_CLOSE to main window to continue shutting down app
		// this time macro code has already terminated, so shutdown should be synchronous

		PostMessage(GetMainWnd(), WM_CLOSE, 0, 0);
	}

	void OnCloseProject(HWND hWndClosing)
	{
		ApcEntryV(CApcHostMember::OnCloseProject);

		_ASSERTE(m_cMsgLoop == m_cFirstMsgLoop); // stack should be empty

		// post WM_CLOSE to main window to continue shutting down app
		// this time macro code has already terminated, so shutdown should be synchronous

		PostMessage(hWndClosing, WM_CLOSE, 0, 0);
	}

	//
	// Implementation (intended for internal use)
	//

	// ApcHost._Create - called by ApcHost.Create
	HRESULT _Create(
	    HWND hWnd,
        BSTR bstrHostName,
        IDispatch* pdisp,
        BSTR bstrLicenseKey,
        long nLcid,
        BSTR bstrFileFilter,
        BSTR bstrRegKey)
	{
		ApcEntryHR(CApcHostMember::_Create);

		CComPtr<IApc> spApcHost;

		ApcCallHR(::CoCreateInstance( APC_CLSID(Apc), 
			NULL, CLSCTX_INPROC_SERVER, APC_IID(IApc), 
			(void**)&spApcHost));

		_ApcComPtr::OnAttach(spApcHost);

		m_hWnd = hWnd;
		m_spAppObj = pdisp;

		if (hWnd)
			ApcCallHR(GetApcHost()->APC_PUT(hWnd)((long) hWnd));
		if (bstrHostName)
			ApcCallHR(GetApcHost()->APC_PUT(HostName)(bstrHostName));
		if (pdisp)
			ApcCallHR(GetApcHost()->APC_PUT(ApplicationObject)(pdisp));
		if (bstrLicenseKey)
			ApcCallHR(GetApcHost()->APC_PUT(LicenseKey)(bstrLicenseKey));
		if (bstrFileFilter)
			ApcCallHR(GetApcHost()->APC_PUT(FileFilter)(bstrFileFilter));
		if (bstrRegKey)
			ApcCallHR(GetApcHost()->APC_PUT(RegistryKey)(bstrRegKey));
		if (nLcid)
			ApcCallHR(GetApcHost()->APC_PUT(Locale)(nLcid));

		ApcCallHR(_ApcSite::CreateInstance(m_pHostOwner, &m_pApcSite));
		ApcCallHR(GetApcHost()->APC_PUT(MessageLoopSite)(m_pApcSite));

		ApcCallHR(ApcNotifyHR(("ApcHost_OnCreate"), m_pHostOwner->ApcHost_OnCreate()));

		ApcReturnHR(NOERROR);
	}

}; // class CApcHostMember

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcHost -- base class for your application class
//

template <class T, class _HostMember = CApcHostMember<T> >
class CApcHost
{
public:
	// 
	// Members
	// 

	_HostMember ApcHost;

	//
	// Lifetime
	//

	CApcHost() : ApcHost(static_cast<T*>(this)) {}

	//
	// IApcEvents Notification 
	// 

	HRESULT ApcHost_BeforeRun()
	{
		return NOERROR;
	}

	HRESULT ApcHost_AfterRun()
	{
		return NOERROR;
	}

	HRESULT ApcHost_BeforePause()
	{
		return NOERROR;
	}

	HRESULT ApcHost_AfterPause()
	{
		return NOERROR;
	}

	HRESULT ApcHost_BeforeModalDialog(IApcProject* pProject)
	{
		return NOERROR;
	}

	HRESULT ApcHost_AfterModalDialog(IApcProject* pProject)
	{
		return NOERROR;
	}

	HRESULT ApcHost_Activate(BOOL* pfActivate)
	{
		return NOERROR;
	}

	HRESULT ApcHost_NameChange(IApcProject* pProject, BSTR bstrOldName)
	{
		return NOERROR;
	}

	HRESULT ApcHost_OpenProject(BSTR bstrProjectFileName, IApcProject* pReferencingProject, IApcProject** ppProject)
	{
		return NOERROR;
	}

	HRESULT ApcHost_ShowHelp(BSTR bstrHelpFileName, LONG lCommand, LONG lCommandData, BOOL bIsWinHelp, BOOL* pfShowHelp)
	{
		return NOERROR;
	}

	HRESULT ApcHost_FindFile(BSTR bstrFileName, BSTR* pbstrFullPath)
	{
		return NOERROR;
	}

	HRESULT ApcHost_CreateMacro(BSTR bstrProcedureName, IApcScope* pCurrentScope, BSTR bstrDescription, BOOL* pfCreated)
	{
		*pfCreated = FALSE;
		return NOERROR;
	}

	HRESULT ApcHost_HostCheckReference(BOOL bSaving, BSTR bstrLibraryGuid, LONG* lMajorVersion, LONG* lMinorVersion)
	{
		return NOERROR;
	}

	//
	// IApcSite Notification
	// 

	HRESULT ApcHost_ContinueIdle(BOOL* pfContinue)
	{
		// return E_NOTIMPL to use default handing of ContinueIdle
		return E_NOTIMPL;
	}

	HRESULT ApcHost_DoIdle(BOOL* pfContinue)
	{
		T* pT = static_cast<T*>(this);
		ApcNotifyV(("ApcHost_OnIdle"), pT->ApcHost_OnIdle(pfContinue));
		return NOERROR;
	}

	HRESULT ApcHost_EnterModalState()
	{
		// component manager is telling us that we're entering a modal state

		ApcHost.m_cModal++;

		// Q: are we leaving the modeless state?
		if (ApcHost.m_cModal == 1)
		{
			// Y: disable the main window 

			// set guard to prevent infinite recursion in ApcHost_OnWmEnable
			ApcHost.m_fWmEnableFromCompMgr = TRUE;

			// send WM_ENABLE(FALSE) to main window
			EnableWindow(ApcHost.GetMainWnd(), FALSE);

			// done preventing infinite recursion in ApcHost_OnWmEnable
			ApcHost.m_fWmEnableFromCompMgr = FALSE;
		}

		return NOERROR;
	}

	HRESULT ApcHost_LeaveModalState()
	{
		// component manager is telling us that we're leaving a modal state

		ApcHost.m_cModal--;

		// Q: are we entering the modeless state?
		if (ApcHost.m_cModal == 0)
		{
			// Y: enable the main window

			// set guard to prevent infinite recursion in ApcHost_OnWmEnable
			ApcHost.m_fWmEnableFromCompMgr = TRUE;

			// send WM_ENABLE(TRUE) to main window
			EnableWindow(ApcHost.GetMainWnd(), TRUE);

			// done preventing infinite recursion in ApcHost_OnWmEnable
			ApcHost.m_fWmEnableFromCompMgr = FALSE;
		}

		return NOERROR;
	}

	HRESULT ApcHost_LostActivation()
	{
		// component manager is telling us we're no longer the active component

		// remember what the component manager told us
		ApcHost.m_fHostIsActiveComponent = FALSE;

		return NOERROR;
	}

	HRESULT ApcHost_HideBorderTools()
	{
		return NOERROR;
	}

	HRESULT ApcHost_TrackingBegins()
	{
		return NOERROR;
	}

	HRESULT ApcHost_TrackingEnds()
	{
		return NOERROR;
	}

	HRESULT ApcHost_PushMessageLoop(AxMessageLoopReason LoopReason, BOOL* pfAborted)
	{
		T* pT = static_cast<T*>(this);
		ApcNotifyV(("ApcHost_OnMessageLoop"), pT->ApcHost_OnMessageLoop(LoopReason, pfAborted, NULL, FALSE));
		return NOERROR;
	}

	HRESULT ApcHost_ShutDown()
	{
		return NOERROR;
	}

	//
	// Overrides
	//

	// ApcHost_OnCreate - called by ApcHost.Create
	HRESULT ApcHost_OnCreate()
	{
		ApcEntryHR(CApcHost::ApcHost_OnCreate);

		ApcCallHR(ApcHost.OnCreate());

		ApcReturnHR(NOERROR);
	}

	// ApcHost_OnDestroy - called by ApcHost.Destroy
	void ApcHost_OnDestroy()
	{
		ApcHost.OnDestroy();
	}

	// ApcHost_OnMessageLoop - called by ApcHost.MessageLoop and ApcHost_PushMessageLoop
	void ApcHost_OnMessageLoop(AxMessageLoopReason loopreason, BOOL* pfAborted, int* pnExitCode, BOOL fPushedByHost)
	{
		ApcEntryV(CApcHost::ApcHost_OnMessageLoop);

        MSG msg;
        APC_BOOL fContinue, fConsumed;

		T* pT = static_cast<T*>(this);

        ApcHost.m_cMsgLoop++;

		if (fPushedByHost && 0 == ApcHost.m_cFirstMsgLoop)
		{
			_ASSERTE(pnExitCode); // first message loop should want an exit code
			ApcHost.m_cFirstMsgLoop = ApcHost.m_cMsgLoop;
		}

		while (TRUE)
		{
			if (ApcHost.GetApcCompManager())
			{
				fContinue = TRUE;
				ApcHost.GetApcCompManager()->APC_RAW(ContinueMessageLoop)(fPushedByHost, &fContinue);

				if (!fContinue)
				{
					if (pfAborted)
						*pfAborted = FALSE;

					break;
				}
			}

			if (!PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				fContinue = FALSE;
				ApcNotifyV(("ApcHost_OnIdle"), pT->ApcHost_OnIdle((BOOL*)&fContinue));

				if (fContinue == FALSE)
				{
					if (ApcHost.GetApcCompManager())
						ApcHost.GetApcCompManager()->APC_RAW(WaitForMessage)();

					if (!PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
						WaitMessage();
				}

				continue;
			}

			if (msg.message == WM_QUIT)
			{
				if (ApcHost.m_cMsgLoop > 1)
					PostQuitMessage(msg.wParam);
				else
				{
					_ASSERTE(pnExitCode); // first message loop should want an exit code

					if (pnExitCode)
						*pnExitCode = msg.wParam;
				}

				break;
			}

			fConsumed = FALSE;

			if (ApcHost.GetApcCompManager())
				ApcHost.GetApcCompManager()->APC_RAW(PreTranslateMessage)(&msg, &fConsumed);

			if (fConsumed)
				continue;

            if (!ApcHost.m_fHostIsActiveComponent)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}

			ApcNotifyV(("ApcHost_OnTranslateMessage"), pT->ApcHost_OnTranslateMessage(&msg, (BOOL*)&fConsumed));

			if (fConsumed)
				continue;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (fPushedByHost && ApcHost.m_cMsgLoop == ApcHost.m_cFirstMsgLoop)
			ApcHost.m_cFirstMsgLoop = 0;

        ApcHost.m_cMsgLoop--;

		if (ApcHost.m_cMsgLoop == ApcHost.m_cFirstMsgLoop)
			ApcHost.StackUnwound();
	}

#ifdef UNICODE
	// Override DispatchMessage and PeekMessage to use ANSI version for ANSI receiving windows.
	LONG DispatchMessage(LPMSG lpMsg) { return (IsWindowUnicode(lpMsg->hwnd)) ? ::DispatchMessageW(lpMsg) : ::DispatchMessageA(lpMsg); }

	BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
	{
		if (!::PeekMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, PM_NOREMOVE)) return FALSE;
		
		if (IsWindowUnicode(lpMsg->hwnd))
		{
			return ::PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
		}
		else
		{
			return ::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
		}
	}
#endif

	// ApcHost_OnIdle - called by ApcHost_OnMessageLoop and ApcHost_DoIdle
	void ApcHost_OnIdle(BOOL* pfContinue)
	{
		ApcHost.OnIdle(pfContinue);
	}

	// ApcHost_OnTranslateMessage - called by ApcHost_OnMessageLoop
	HRESULT ApcHost_OnTranslateMessage(MSG* pmsg, BOOL* pfConsumed)
	{
		*pfConsumed = FALSE;
		return NOERROR;
	}

	// ApcHost_OnWmEnable - called by ApcHost.WmEnable
	void ApcHost_OnWmEnable(BOOL fEnable)
	{
		ApcHost.OnWmEnable(fEnable);
	}

	// ApcHost_OnWmActivate - called by ApcHost.WmActivate
	void ApcHost_OnWmActivate()
	{
		ApcHost.OnWmActivate();
	}

	// ApcHost_OnWmClose - called by ApcHost.WmClose
	void ApcHost_OnWmClose(BOOL& fTerminated, HWND hWnd)
	{
		ApcHost.OnWmClose(fTerminated, hWnd);
	}

	// ApcHost_OnEnd - called by ApcHost.End
	void ApcHost_OnEnd(BOOL& fTerminated, HWND hWndClosing)
	{
		ApcHost.OnEnd(fTerminated, hWndClosing);
	}

	// ApcHost_OnStackUnwound - called by message loop
	void ApcHost_OnStackUnwound()
	{
		ApcHost.OnStackUnwound();
	}

	// ApcHost_OnCloseHost - called by ApcHost.OnStackUnwound
	void ApcHost_OnCloseHost()
	{
		ApcHost.OnCloseHost();
	}

	void ApcHost_OnCloseProject(HWND hWndClosing)
	{
		ApcHost.OnCloseProject(hWndClosing);
	}
}; // class CApcHost

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcProjectEvents -- used internally by CApcProjectMember to implement an event sink 
//

template <class ProjectOwner>
class ATL_NO_VTABLE CApcProjectEvents 
:
	public ISupportErrorInfoImpl<&APC_IID(IApcProjectEvents)>,
	public IApcProjectEvents,
	public IApcRegProject,
	public CComObjectRootEx< CComObjectThreadModel >
{
	ProjectOwner* m_pProjectOwner;

public:
	typedef ProjectOwner _ProjectOwner;
	typedef CApcProjectEvents<_ProjectOwner> _CApcProjectEvents;
	typedef CComObject<_CApcProjectEvents> _Object;

	BEGIN_COM_MAP(_CApcProjectEvents)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(APC_IID(IApcProjectEvents), IApcProjectEvents)
		COM_INTERFACE_ENTRY(IApcRegProject)
	END_COM_MAP()

	static HRESULT CreateInstance(_ProjectOwner* pProjectOwner, IApcProjectEvents** pp)
	{
		HRESULT hRes = E_OUTOFMEMORY;
		_Object* p = NULL;
		ATLTRY(p = new _Object(0))
		if (p != NULL)
		{
			p->SetVoid(0);
			p->InternalFinalConstructAddRef();

			p->Init(pProjectOwner);

			hRes = p->FinalConstruct();
			p->InternalFinalConstructRelease();
			if (hRes == S_OK)
				hRes = p->QueryInterface(APC_IID(IApcProjectEvents), (void**)pp);
			if (hRes != S_OK)
				delete p;
		}
		return NOERROR;
	}

	CApcProjectEvents()
	{
		m_pProjectOwner = 0;
	}

	HRESULT Init(_ProjectOwner* pProjectOwner)
	{
		_ASSERTE(0 == m_pProjectOwner); // already attached
		_ASSERTE(0 != pProjectOwner); // arguement required
		m_pProjectOwner = pProjectOwner;
		return NOERROR;
	}

	// IApcProjectEvents
	//
	STDMETHODIMP APC_RAW(Reset)()
	{
		return ApcNotifyHR(("ApcProject_Reset"), m_pProjectOwner->ApcProject_Reset());
	}

	STDMETHODIMP APC_RAW(Save)()
	{
		return ApcNotifyHR(("ApcProject_Save"), m_pProjectOwner->ApcProject_Save());
	}

	STDMETHODIMP APC_RAW(ProjectItemCreated)(IApcProjectItem* pProjectItem)
	{
		return ApcNotifyHR(("ApcProject_ProjectItemCreated"), m_pProjectOwner->ApcProject_ProjectItemCreated(pProjectItem));
	}

	STDMETHODIMP APC_RAW(ProjectItemDelete)(IApcProjectItem* pProjectItem)
	{
		return ApcNotifyHR(("ApcProject_ProjectItemDelete"), m_pProjectOwner->ApcProject_ProjectItemDelete(pProjectItem));
	}

	STDMETHODIMP APC_RAW(ModeChange)(AxProjectMode NewMode)
	{
		return ApcNotifyHR(("ApcProject_ModeChange"), m_pProjectOwner->ApcProject_ModeChange(NewMode));
	}

	STDMETHODIMP APC_RAW(NameChange)(IApcProjectItem* pProjectItem, BSTR bstrOldName)
	{
		return ApcNotifyHR(("ApcProject_NameChange"), m_pProjectOwner->ApcProject_NameChange(pProjectItem, bstrOldName));
	}

	STDMETHODIMP APC_RAW(ProcedureAdd)(IApcProcedure* pProcedure)
	{
		return ApcNotifyHR(("ApcProject_ProcedureAdd"), m_pProjectOwner->ApcProject_ProcedureAdd(pProcedure));
	}

	STDMETHODIMP APC_RAW(ProcedureDelete)(IApcProjectItem* pProjectItem, BSTR bstrName, AxProcedureType ProcedureType)
	{
		return ApcNotifyHR(("ApcProject_ProcedureDelete"), m_pProjectOwner->ApcProject_ProcedureDelete(pProjectItem, bstrName, ProcedureType));
	}
	STDMETHODIMP APC_RAW(ModuleChange)(IApcProjectItem* pProjectItem)
	{
		return ApcNotifyHR(("ApcProject_ModuleChange"), m_pProjectOwner->ApcProject_ModuleChange(pProjectItem));
	}
	STDMETHODIMP APC_RAW(OpenProjectItem)(BSTR bstrName, long nID, IDispatch **ppHostProjectItem)
	{
		return ApcNotifyHR(("ApcProject_OpenProjectItem"), m_pProjectOwner->ApcProject_OpenProjectItem(bstrName, nID, ppHostProjectItem));
	}
	STDMETHODIMP APC_RAW(ModuleDirtyChange)(IApcProjectItem* pProjectItem, VARIANT_BOOL fDirty)
	{
		return ApcNotifyHR(("ApcProject_ModuleDirtyChange"), m_pProjectOwner->ApcProject_ModuleDirtyChange(pProjectItem, fDirty));
	}

	// IApcRegProject
	//

	STDMETHOD(Request)(BSTR bstrName)
	{
		return ApcNotifyHR(("ApcProject_OnRequestProjectItem"),
			m_pProjectOwner->ApcProject_OnRequestProjectItem(bstrName));
	}

}; // class CApcProjectEvents

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcProjectMember - 
//

template <class _ProjectOwner>
class CApcProjectMember: public CApcComPtr<IApcProject>
{
protected:
	CComQIPtr<IPersistStorage, &IID_IPersistStorage> m_spProjPS;
	CComPtr<IStorage> m_spStg;
	CComPtr<IStorage> m_spProjStg;
	const OLECHAR* m_pwszName;
	_ProjectOwner* m_pProjectOwner;
	enum PersistState { NeedsInit, Init, Normal, NoScribble, HandsOff, Closed } m_PersistState;
	BOOL m_fSaveOccurred;

	typedef CApcProjectEvents<_ProjectOwner> _Sink;
	CComPtr<IApcProjectEvents> m_spProjectEvents;
	long m_dwAdvise;
	BOOL m_fClosing;

	CComPtr<IApcRegProjItems> m_spRegProjItems;

	HRESULT CreateRegProjItems()
	{
		ApcEntryHR(CApcProjectMember::CreateRegProjItems);

		_ASSERTE(!GetApcProject()); // must not be attached
		_ASSERTE(!m_spProjectEvents.p); // prior call to CreateRegProjItems?

		CComPtr<IApcProjectEvents> spProjectEvents;
		CComPtr<IApcRegProjItems> spRegProjItems;

		ApcCallHR(_Sink::CreateInstance(m_pProjectOwner, &spProjectEvents.p));
		ApcCallHR(ApcCreateRegProjItems(&spRegProjItems));
		ApcCallHR(spRegProjItems->Init(spProjectEvents));
		//success!
		m_spProjectEvents = spProjectEvents;
		m_spRegProjItems = spRegProjItems;
		ApcReturnHR(NOERROR);
	}

public:
	//
	// Lifetime
	//

	CApcProjectMember(_ProjectOwner* pProjectOwner, const OLECHAR* pwszStgName)
	: 
		m_pProjectOwner(pProjectOwner), 
		m_pwszName(pwszStgName), 
		m_dwAdvise(0),
		m_PersistState(NeedsInit),
		m_fSaveOccurred(FALSE),
		m_fClosing(FALSE)
	{
		_ASSERTE(pProjectOwner); // argument is required
		_ASSERTE(pwszStgName); // argument is required
	}

	~CApcProjectMember()
	{ 
		if (GetApcProject())
			Close(); // still fully attached, so call ApcProject_Close
		else
			OnClose();// not fully attached, so quietly shut down
	}


	//
	// Accessors
	//

	IApcRegProjItems* GetApcRegProjItems() 
	{
		if (!m_spRegProjItems) CreateRegProjItems();
		return m_spRegProjItems;
	}

	IApcProject* GetApcProject() 
	{
		return *this; 
	}


	//
	// Operations
	//

	// Exists -- test storage for project
	//
	// If host does not keep a flag or version info on whether host document
	// contains a APC project, this function may be used to determine if there
	// is a substorage for the project prior to the Open/Load/FinishLoading sequence.
	//
	// old code:
	//
	//	// begin loading document...
	//	//	(register all project items and controls)
	//	// ...end loading document
	//
	//	IfFailGo(ApcProject.Open(GetApp()->ApcHost, APC::AxProjectNormal));
	//	IfFailGo(ApcProject.Load(m_pStg));
	//	IfFailGo(ApcProject.FinishLoading());
	//
	// new code:
	//
	//	// Q: is there a APC project already?
	//	if (S_OK == ApcProject.Exists(m_pStg))
	//	{
	//		// Y: reopen with existing APC project
	//
	//		// begin loading document...
	//		//	(register all project items and controls)
	//		// ...end loading document
	//
	//		IfFailGo(ApcProject.Open(GetApp()->ApcHost, APC::AxProjectNormal));
	//		IfFailGo(ApcProject.Load(m_pStg));
	//		IfFailGo(ApcProject.FinishLoading());
	//	}
	//	else
	//	{
	//		// N: no APC project yet, so create a new one
	//
	//		IfFailGo(ApcProject.Create(GetApp()->ApcHost, APC::AxProjectNormal));
	//		IfFailGo(ApcProject.InitNew(m_pStg));
	//
	//		// ApcProject has an associated IApcProject, so that's how 
	//		// we will detect we're in convert-to-VBA mode
	//
	//		// begin loading document...
	//		//	(define all project items and controls)
	//		// ...end loading document
	//	}
	//
	// Then each spot in the code where a project item or control is registered 
	// would be changed. When in conversion mode, call define instead of calling 
	// register. Using the ApcProject member of a CApcProject as the expression 
	// for an "if" statement tells you if you're in conversion mode.
	//
	// old code:
	//
	//	IfFailGo(ApcProjectItem.Register(...));
	//
	// new code:
	//
	//	// Q: in convert-to-APC mode?
	//	if (GetDocument()->ApcProject)
	//	{
	//		// Y: convert to APC--we are populating the APC project for the first time
	//		// add this project item to project
	//		IfFailGo(ApcProjectItem.Define(...));
	//	}
	//	else
	//	{
	//		// N: already using APC--we are hooking up internal objects to APC objects
	//		// reassociate with existing project item
	//		IfFailGo(ApcProjectItem.Register(...));
	//	}
	//
	// Similar changes would apply to CApcControl.

	HRESULT Exists(IStorage* pStg)
	{
		_ASSERTE(pStg); // argument required
		CComPtr<IStorage> spProjStg;
		return (SUCCEEDED(OpenStg(pStg, &spProjStg.p))) ? S_OK : S_FALSE;
	}

	// Create -- create a new APC project
	//
	// If this fails, call Close() to clean up
	//
	HRESULT Create(IApc* pApcHost, AxProjectFlag Flags, BSTR bstrName = NULL)
	{
		ApcEntryHR(CApcProjectMember::Create);
		CComPtr<IApcProjects> spProjects;
		CComPtr<IApcProject> spProject;

		_ASSERTE(pApcHost); // argument required
		_ASSERTE(!GetApcProject()); // already attached?

		ApcCallHR(pApcHost->APC_GET(Projects)( &spProjects ));
		ApcCallHR(spProjects->APC_RAW(Add)(Flags, bstrName, &spProject));
		ApcCallHR(ApcNotifyHR(("ApcProject_OnAttach"), m_pProjectOwner->ApcProject_OnAttach( spProject )));
		ApcReturnHR(NOERROR);
	}


	// Open -- open an existing APC project
	//
	// If this fails, call Close() to clean up
	//
	HRESULT Open(IApc* pApcHost, AxProjectFlag Flags)
	{
		ApcEntryHR(CApcProjectMember::Open);
		CComPtr<IApcProjects> spProjects;
		CComPtr<IApcProject> spProject;
		CComQIPtr<IDispatch, &IID_IDispatch> spProjectItems(m_spRegProjItems);

		_ASSERTE(pApcHost); // argument required
		_ASSERTE(!GetApcProject()); // already attached?
		_ASSERTE(spProjectItems.p || !m_spRegProjItems.p); // QI for VBA::_Collection failed?

		ApcCallHR(pApcHost->APC_GET(Projects)( &spProjects ));
		ApcCallHR(spProjects->APC_RAW(Open)(Flags, NULL, spProjectItems, &spProject));
		ApcCallHR(ApcNotifyHR(("ApcProject_OnAttach"), m_pProjectOwner->ApcProject_OnAttach( spProject )));
		ApcReturnHR(NOERROR);
	}

	// OnAttach -- default handler for ApcProject_OnAttach()
	//
	//	To undo an attach, call Close()
	//	If Attach() fails, call Close() to clean up
	//	
	HRESULT OnAttach(IApcProject* pProject)
	{
		ApcEntryHR(CApcProjectMember::OnAttach);

		if (!m_spProjectEvents)
		{
			ApcCallHR(_Sink::CreateInstance(m_pProjectOwner, &m_spProjectEvents.p));
		}
		ApcCallHR(pProject->APC_RAW(AdviseProjectEvents)(m_spProjectEvents, &m_dwAdvise));

		// success!
		_ApcComPtr::OnAttach(pProject);
		m_spProjPS = pProject; //performs QI for IPersistStorage
		ApcReturnHR(NOERROR);
	}

	// FinishLoading -- hook up project items and controls
	//
	// If this fails, call Close() to clean up
	//
	HRESULT FinishLoading()
	{
		ApcEntryHR(CApcProjectMember::FinishLoading);

		if (m_spRegProjItems)
		{
			ApcCallHR(m_spRegProjItems->Bind(*this));
			ApcCallHR(m_spRegProjItems->FinishLoad());
			ApcCallHR(m_spRegProjItems->LoadComplete(TRUE));
			m_spRegProjItems.Release();
		}

		ApcReturnHR(NOERROR);
	}

	// Close -- shuts down project, discarding changes
	//
	// after calling Close it is safe to call Create or Open again
	// (CApcDocument needs this for MFC's SDI documents)
	//
	void Close()
	{
		ApcNotifyV(("ApcProject_OnClose"), m_pProjectOwner->ApcProject_OnClose());
	}

	void OnClose()
	{
		ApcEntryV(CApcProjectMember::OnClose);

		// notify each CApcProjectItem and CApcControl that we're finished loading
		if (m_spRegProjItems)
		{
			m_spRegProjItems->LoadComplete(FALSE);
			m_spRegProjItems.Release();
		}

		if (GetApcProject())
		{
			if (m_dwAdvise)
			{
				GetApcProject()->APC_RAW(UnadviseProjectEvents)(m_dwAdvise);
				m_dwAdvise = 0;
			}

			// close the VBA project, discarding changes
			HRESULT hr = (*this)->APC_RAW(Close)(VARIANT_FALSE);
			switch (hr)
			{
				case APC_E_VBAMACROENABLE_DONTOPEN:
				case APC_E_ZOMBIED:
				case APC_E_NOTATTACHED:
					break;
				default:
					// IApcProject::Close() failed
					_ASSERTE(SUCCEEDED(hr));
			}
		}

		_ApcComPtr::OnDetach();
		m_spProjectEvents.Release();
		m_spProjPS.Release();
		m_spProjStg.Release();
		m_spStg.Release();
	}


	// CreateStg -- called to create a new substorage for apc
	HRESULT CreateStg(IStorage* pStg, IStorage** ppStg)
	{
		ApcEntryHR(CApcProjectMember::CreateStg);
		ApcCallHR(ApcNotifyHR(("ApcProject_OnCreateStg"), m_pProjectOwner->ApcProject_OnCreateStg( pStg, m_pwszName, ppStg )));
		ApcReturnHR(NOERROR);
	}

	HRESULT OnCreateStg(IStorage* pStg, const OLECHAR* pwszName, IStorage** ppStg)
	{
		ApcEntryHR(CApcProjectMember::OnCreateStg);

		_ASSERTE(pStg); // argument is required
		_ASSERTE(ppStg && !*ppStg); // arg should be ptr to NULL

		ApcCallHR(pStg->CreateStorage(pwszName,
			STGM_CREATE | STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
			0, 0, ppStg));

		_ASSERTE(*ppStg); // should have a value for substorage now

		ApcReturnHR(NOERROR);
	}

	// OpenStg -- called to open an existing substorage for apc
	HRESULT OpenStg(IStorage* pStg, IStorage** ppStg)
	{
		ApcEntryHR(CApcProjectMember::OpenStg);
		ApcCallHR(ApcNotifyHR(("ApcProject_OnOpenStg"), m_pProjectOwner->ApcProject_OnOpenStg( pStg, m_pwszName, ppStg )));
		ApcReturnHR(NOERROR);
	}

	HRESULT OnOpenStg(IStorage* pStg, const OLECHAR* pwszName, IStorage** ppStg)
	{
		ApcEntryHR(CApcProjectMember::OnOpenStg);

		_ASSERTE(pStg); // argument is required
		_ASSERTE(ppStg && !*ppStg); // arg should be ptr to NULL

		hr = pStg->OpenStorage(pwszName, NULL,
						STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
						0, 0, ppStg);

		// If we cannot open with READWRITE permission, try READONLY.
		if (FAILED(hr)) 
			ApcCallHR(pStg->OpenStorage(pwszName, NULL,
							STGM_TRANSACTED | STGM_READ | STGM_SHARE_EXCLUSIVE,
							0, 0, ppStg));

		_ASSERTE(*ppStg); // should have a value for substorage now

		ApcReturnHR(NOERROR);
	}

	// IPersistStorage Operations
	//

	STDMETHOD(IsDirty)()
	{
		ApcEntryHR(CApcProjectMember::IsDirty);

		if (m_spProjPS.p)
		{
			// delegate to Apc project
			ApcCallHR(m_spProjPS->IsDirty());
			if (S_OK == hr)
				ApcReturnHR(hr); // this one's dirty--stop here
		}

		// didn't find a dirty one
		ApcReturnHR(S_FALSE);
	}

	// InitNew -- use during your IPersistStorage::InitNew
	//
	// call Create() before calling this function
	// If InitNew() fails, call Close() to clean up
	//
	STDMETHOD(InitNew)(IStorage* pStg)
	{
		ApcEntryHR(CApcProjectMember::InitNew);
		if (!pStg) ApcReturnHR(E_INVALIDARG);
		CComPtr<IStorage> spProjStg;

		// delegate to Apc project
		if (m_spProjPS.p)
		{
			_ASSERTE(!m_spStg.p); // already attached?
			_ASSERTE(!m_spProjStg.p); // already attached?
			if (m_spStg.p) ApcReturnHR(CO_E_ALREADYINITIALIZED);

			// create IStorage for Apc project
			ApcCallHR(CreateStg(pStg, &spProjStg.p));

			// init Apc project into IStorage
			ApcCallHR(m_spProjPS->InitNew(spProjStg));
		}

		// success! 
		m_spStg = pStg;
		m_spProjStg = spProjStg;
		m_PersistState = Normal;
		ApcReturnHR(NOERROR);
	}

	// Load -- use during your IPersistStorage::Load
	//
	// call Open() before calling this function
	// If Load() fails, call Close() to clean up
	//
	STDMETHOD(Load)(IStorage* pStg)
	{
		ApcEntryHR(CApcProjectMember::Load);
		if (!pStg) ApcReturnHR(E_INVALIDARG);
		CComPtr<IStorage> spProjStg;

		// delegate to Apc project
		if (m_spProjPS.p)
		{
			_ASSERTE(!m_spStg.p); // already attached?
			_ASSERTE(!m_spProjStg.p); // already attached?
			if (m_spStg.p) ApcReturnHR(CO_E_ALREADYINITIALIZED);
	
			// open IStorage for Apc project
			ApcCallHR(OpenStg(pStg, &spProjStg.p));

			// update reference name
			ApcCallHR(ApcNotifyHR(("ApcProject_OnMove"), m_pProjectOwner->ApcProject_OnMove(pStg, TRUE)));

			// load Apc project from storage
			ApcCallHR(m_spProjPS->Load(spProjStg));
		}

		// success! 
		m_spStg = pStg;
		m_spProjStg = spProjStg;
		m_PersistState = Normal;
		ApcReturnHR(NOERROR);
	}

	STDMETHOD(Save)(IStorage* pStg, BOOL fSame)
	{
		ApcEntryHR(CApcProjectMember::Save);
		CComPtr<IStorage> spProjStg;

		// delegate to Apc project
		if (m_spProjPS.p)
		{
			_ASSERTE(m_spStg.p); // no prior call to InitNew or Load?
			_ASSERTE(m_spProjStg.p); // no prior call to InitNew or Load?

			if (fSame) {
				// use same substg for apc
				spProjStg=m_spProjStg;
			} else {
				// update reference name
				ApcCallHR(ApcNotifyHR(("ApcProject_OnMove"), m_pProjectOwner->ApcProject_OnMove(pStg, FALSE)));

				// create substg for apc
				ApcCallHR(CreateStg(pStg, &spProjStg.p));
				_ASSERTE(spProjStg.p); // Create should have set a value
			}

			// save Apc project into storage
			ApcCallHR(m_spProjPS->Save(spProjStg, fSame));

			// commit storage
			ApcCallHR(spProjStg->Commit(STGC_ONLYIFCURRENT));
		}

		// success!
        m_PersistState = NoScribble;
        m_fSaveOccurred = TRUE;
		ApcReturnHR(NOERROR);
	}

	STDMETHOD(SaveCompleted)(IStorage* pStg)
	{
		ApcEntryHR(CApcProjectMember::SaveComplete);
		CComPtr<IStorage> spProjStg;

		// delegate to Apc project
		if (m_spProjPS.p)
		{
			_ASSERTE(pStg || m_spStg.p); // SaveCompleted(NULL) after HandsOffStorage() is not legal

			// Q: switching to new stg?
			if (pStg) {
				// Y: open substg for apc
				ApcCallHR(OpenStg(pStg, &spProjStg.p))
				_ASSERTE(spProjStg.p); // Open should have set a value
			} else {
				// N: send a NULL to apc's SaveCompleted
				_ASSERTE(!spProjStg.p); // how did this get to be non-NULL?
			}

			// call apc's SaveCompleted
			ApcCallHR(m_spProjPS->SaveCompleted(spProjStg));
		}

		// success!
		if (pStg) {
			m_spStg = pStg;
			m_spProjStg = spProjStg;
			m_PersistState = Normal;
		}
		_ASSERTE(m_spStg.p); 
		_ASSERTE(m_spProjStg.p);

		// update reference name, ignoring errors
		ApcNotifyHR(("ApcProject_OnMove"), m_pProjectOwner->ApcProject_OnMove(m_spStg, TRUE));

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(HandsOffStorage)()
	{
		ApcEntryHR(CApcProjectMember::HandsOffStorage);
		if (!m_fSaveOccurred){
			// some IPersistStorage clients behave poorly and end up calling
			// HandsOffStorage prior to saving, we will accept this special
			// case by calling save for them here
			ApcCallHR(Save(m_spStg, TRUE));
		}

		// delegate to Apc project
		if (m_spProjPS)
		{
			_ASSERTE(m_spStg.p); // prior call to HandsOffStorage?
			_ASSERTE(m_spProjStg.p);

			ApcCallHR(m_spProjPS->HandsOffStorage());
		}

		// success!
		m_spProjStg.Release();
		m_spStg.Release();
		m_PersistState = HandsOff;
		ApcReturnHR(NOERROR);
	}
}; // class CApcProjectMember

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcProject<T> - base class for your document class

template <class T, class _ProjectMember = CApcProjectMember<T> >
class CApcProject
{
public:
	// 
	// Members
	// 

	_ProjectMember ApcProject;

	// 
	// Lifetime
	// 

	CApcProject(const OLECHAR* pszStgName = L"apc")
		: ApcProject(static_cast<T*>(this), pszStgName) {}

	// 
	// IApcProjectEvents Notification
	// 

	HRESULT ApcProject_Reset()
	{
		return NOERROR;
	}

	HRESULT ApcProject_Save()
	{
		return NOERROR;
	}

	HRESULT ApcProject_ProjectItemCreated(IApcProjectItem* pProjectItem)
	{
		return NOERROR;
	}

	HRESULT ApcProject_ProjectItemDelete(IApcProjectItem* pProjectItem)
	{
		return NOERROR;
	}

	HRESULT ApcProject_ModeChange(AxProjectMode NewMode)
	{
		return NOERROR;
	}

	HRESULT ApcProject_NameChange(IApcProjectItem* pProjectItem, BSTR bstrOldName)
	{
		return NOERROR;
	}

	HRESULT ApcProject_ProcedureAdd(IApcProcedure* pProcedure)
	{
		return NOERROR;
	}

	HRESULT ApcProject_ProcedureDelete(IApcProjectItem* pProjectItem, BSTR bstrName, AxProcedureType ProcedureType)
	{
		return NOERROR;
	}

	HRESULT ApcProject_ModuleChange(IApcProjectItem* pProjectItem)
	{
		return NOERROR;
	}

	HRESULT ApcProject_OpenProjectItem(BSTR bstrName, long nID, IDispatch **ppHostProjectItem)
	{
		return NOERROR;
	}

	HRESULT ApcProject_ModuleDirtyChange(IApcProjectItem* pProjectItem, VARIANT_BOOL fDirty)
	{
		return NOERROR;
	}

	// 
	// Overrides
	// 

	HRESULT ApcProject_OnAttach(IApcProject* pProject)
	{
		return ApcProject.OnAttach(pProject);
	}

	void ApcProject_OnClose()
	{
		ApcProject.OnClose();
	}

	// ApcProject_OnMove
	//
	// Parameters:
	//	pStg - (IN) containing storage
	//	fFullySaved - (IN) true if in Normal mode
	//
	// callback to set the reference name on a project
	//
	// called during initial Load with fFullySaved==true
	// called during Save with fFullySaved==false
	// called during SaveCompleted with fFullySaved==true
	//
	HRESULT ApcProject_OnMove(IStorage* pStg, BOOL /*fFullySaved*/)
	{
		ApcEntryHR(CApcProject::ApcProject_OnMove);

		CComQIPtr<IRootStorage, &IID_IRootStorage> spRootStg(pStg);
		if (!spRootStg)
			ApcReturnHR(S_FALSE); // cannot determine filename because pStg is not a root

		CComPtr<IMalloc> spMalloc;
		CoGetMalloc(MEMCTX_TASK, &spMalloc.p);

		STATSTG statstg;
		ApcCallHR(pStg->Stat(&statstg, STATFLAG_DEFAULT));
		if (statstg.pwcsName == NULL)
			ApcReturnHR(S_FALSE); // Non-file based storage.  Override ApcProject_OnMove and provide naming scheme.

		CComBSTR bstr(statstg.pwcsName);
		spMalloc->Free(statstg.pwcsName);

		ApcCallHR(ApcProject->APC_PUT(ReferenceName)(bstr));

		ApcReturnHR(NOERROR);
	}

	HRESULT ApcProject_OnRequestProjectItem(BSTR bstrName)
	{
		return E_FAIL;
	}

	HRESULT ApcProject_OnCreateStg(IStorage* pStg, const OLECHAR* pwszName, IStorage** ppStg)
	{
		return ApcProject.OnCreateStg(pStg, pwszName, ppStg);
	}

	HRESULT ApcProject_OnOpenStg(IStorage* pStg, const OLECHAR* pwszName, IStorage** ppStg)
	{
		return ApcProject.OnOpenStg(pStg, pwszName, ppStg);
	}

}; // class CApcProject

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcProjectItemEvents -- used internally by CApcProjectItemMember to implement an event sink 
//
// the ProjectItemOwner class should define the following methods:
//
// HRESULT ApcProjectItem_View()
// HRESULT ApcProjectItem_Activate()
//
// CApcProjectItem provides default implementations of these functions

template <class ProjectItemOwner>
class ATL_NO_VTABLE CApcProjectItemEvents 
:
	public ISupportErrorInfoImpl<&APC_IID(IApcProjectItemEvents )>,
	public IApcProjectItemEvents,
	public IApcRegProjItem,
	public CComObjectRootEx< CComObjectThreadModel >
{
	ProjectItemOwner* m_pProjectItemOwner;

public:
	typedef ProjectItemOwner _ProjectItemOwner;
	typedef CApcProjectItemEvents<_ProjectItemOwner> _CApcProjectItemEvents;
	typedef CComObject<_CApcProjectItemEvents> _Object;

	BEGIN_COM_MAP(_CApcProjectItemEvents)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(APC_IID(IApcProjectItemEvents), IApcProjectItemEvents)
		COM_INTERFACE_ENTRY(IApcRegProjItem)
	END_COM_MAP()


	static HRESULT CreateInstance(_ProjectItemOwner* pProjectItemOwner, IApcProjectItemEvents** pp)
	{
		HRESULT hRes = E_OUTOFMEMORY;
		_Object* p = NULL;
		ATLTRY(p = new _Object(0))
		if (p != NULL)
		{
			p->SetVoid(0);
			p->InternalFinalConstructAddRef();

			p->Init(pProjectItemOwner);

			hRes = p->FinalConstruct();
			p->InternalFinalConstructRelease();
			if (hRes == S_OK)
				hRes = p->QueryInterface(APC_IID(IApcProjectItemEvents), (void**)pp);
			if (hRes != S_OK)
				delete p;
		}
		return NOERROR;
	}

	CApcProjectItemEvents()
	{
		m_pProjectItemOwner = 0;
	}

	HRESULT Init(_ProjectItemOwner* pProjectItemOwner)
	{
		_ASSERTE(0 == m_pProjectItemOwner); // already attached?
		_ASSERTE(0 != pProjectItemOwner); // argument is required
		m_pProjectItemOwner = pProjectItemOwner;
		return NOERROR;
	}

	//
	// IApcProjectItemEvents
	//

	STDMETHODIMP APC_RAW(View)()
	{
		return ApcNotifyHR(("ApcProjectItem_View"), m_pProjectItemOwner->ApcProjectItem_View());
	}

	STDMETHODIMP APC_RAW(Activate)()
	{
		return ApcNotifyHR(("ApcProjectItem_Activate"), m_pProjectItemOwner->ApcProjectItem_Activate());
	}

	STDMETHODIMP APC_RAW(CreateInstance)(IDispatch **ppInstance)
	{
		return ApcNotifyHR(("ApcProjectItem_CreateInstance"), m_pProjectItemOwner->ApcProjectItem_CreateInstance(ppInstance));
	}

	STDMETHODIMP APC_RAW(ReleaseInstances)()
	{
		return ApcNotifyHR(("ApcProjectItem_ReleaseInstances"), m_pProjectItemOwner->ApcProjectItem_ReleaseInstances());
	}

	STDMETHODIMP APC_RAW(InstanceCreated)(IDispatch *pInstance)
	{
		return ApcNotifyHR(("ApcProjectItem_InstanceCreated"), m_pProjectItemOwner->ApcProjectItem_InstanceCreated(pInstance));
	}

	//
	// IApcRegProjItem
	//

	STDMETHOD(Attach)(IApcProjectItem* pProjectItem)
	{
		return ApcNotifyHR(("ApcProjectItem_OnAttach"), m_pProjectItemOwner->ApcProjectItem_OnAttach(pProjectItem));
	}

	STDMETHOD(FinishLoad)()
	{
		return ApcNotifyHR(("ApcProjectItem_OnFinishLoad"), m_pProjectItemOwner->ApcProjectItem_OnFinishLoad());
	}

	STDMETHOD(LoadComplete)(BOOL fGood)
	{
		if (fGood)
		{
			ApcNotifyV(("ApcProjectItem_OnLoadComplete"), m_pProjectItemOwner->ApcProjectItem_OnLoadComplete());
		}
		else
		{
			ApcNotifyV(("ApcProjectItem_OnDetach"), m_pProjectItemOwner->ApcProjectItem_OnDetach());
		}
		return NOERROR;
	}

}; // class CApcProjectItemEvents

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcProjectItemPtr - base class for the the "ApcProjectItem" member 
//

class CApcProjectItemPtr: public CApcComPtr<IApcProjectItem>
{
protected:
	CComPtr<IApcProjectItemEvents> m_spProjectItemEvents;
	long m_dwAdvise;

	CComPtr<IApcRegProjItems> m_spRegProjItems;
	DWORD m_dwRegister;

	CComPtr<IApcRegControls> m_spRegControls;

public:
	// 
	// Accessors
	// 

	IApcRegControls*		GetApcRegControls() 
	{
		if (!m_spRegControls) ApcCreateRegControls(&m_spRegControls);
		return m_spRegControls; 
	}

	IApcProjectItem*		GetApcProjectItem() { return *this; }

#ifdef APC_MANGLED_ID
	long ApcID();
#else
	long ID();
#endif

	//
	// Lifetime
	//

	CApcProjectItemPtr();
	~CApcProjectItemPtr();

	//
	// Operations
	//

	HRESULT OnDefine(IApcProject* pProject, IDispatch* pdisp, AxProjectItemType projectItemType, BSTR bstrRequestName, IApcProjectItem** ppProjectItem);
	// OnUndefine - default handler for ApcProjectItem_OnUndefine
	HRESULT OnUndefine();
	// OnRegister -- used internally by ApcProjectItem_OnRegister
	HRESULT OnRegister(IApcRegProjItems* pRegProjItems, IDispatch* pdisp, BSTR bstrName, long nID);
	// OnAttach -- called by ApcProjectItem_OnAttach
	HRESULT OnAttach(IApcProjectItem* pProjectItem);
	// OnDetach -- called by ApcProjectItem_OnDetach
	void OnDetach();
	// OnFinishLoad -- called by ApcProjectItem_OnFinishLoad
	HRESULT OnFinishLoad();
	// OnLoadComplete -- called by ApcProjectItem_OnLoadComplete
	void OnLoadComplete();

	// RegisterControl -- register a host control
	//
	// host controls must be registered before calling ApcProject.Open
	// use ApcControl.Register for controls that have an associated CApcControl
	//
	HRESULT RegisterControl(BSTR bstrName, IDispatch* pHostControl, IDispatch* pExtender = NULL);
	HRESULT RegisterControl(long nID,	   IDispatch* pHostControl, IDispatch* pExtender = NULL);
};


/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcProjectItemMember - the "ApcProjectItem" member of CApcProjectItem
//

template <class _ProjectItemOwner>
class CApcProjectItemMember: public CApcProjectItemPtr
{
	_ProjectItemOwner* m_pProjectItemOwner;

	typedef CApcProjectItemEvents<_ProjectItemOwner> _Sink;
public:
	//
	// Lifetime
	//

	CApcProjectItemMember(_ProjectItemOwner* pProjectItemOwner)
	: 
		m_pProjectItemOwner(pProjectItemOwner)
	{
		_ASSERTE(pProjectItemOwner); // argument is required
	}
	
	~CApcProjectItemMember()
	{ 
		if (GetApcProjectItem())
			Detach(); // still fully attached, so call ApcProjectItem_Detach
		else
			OnDetach(); // not fully attached, so quietly shut down
	}


	//
	// Operations
	//

	// Define -- define a new project item
	//
	// project item definitions are persisted with the project
	// call this after the project is fully created or loaded
	//
	template <class _Project>
	HRESULT Define(_Project& project, IDispatch* pdisp, AxProjectItemType projectItemType, BSTR bstrRequestName, BSTR* pbstrActualName = NULL)
	{
		ApcEntryHR(CApcProjectItemMember::Define);

		_ASSERTE(!pbstrActualName || !*pbstrActualName); // pbstrActualName should be NULL or ptr to NULL

		hr = ApcNotifyHR(("ApcProjectItem_OnDefine"), 
			m_pProjectItemOwner->ApcProjectItem_OnDefine(project, pdisp, projectItemType, bstrRequestName, pbstrActualName));
		
		if (FAILED(hr))
			Undefine();

		ApcReturnHR(hr);
	}

	template <class _Project>
	HRESULT OnDefine(_Project& project, IDispatch* pdisp, AxProjectItemType projectItemType, BSTR bstrRequestName, BSTR* pbstrActualName)
	{
		ApcEntryHR(CApcProjectItemMember::OnDefine);
		CComPtr<IApcProjectItem> spProjectItem;
		ApcCallHR(CApcProjectItemPtr::OnDefine(project, pdisp, projectItemType, bstrRequestName, &spProjectItem.p));
		ApcCallHR(Attach(spProjectItem));
		if (pbstrActualName) 
		{ 
			ApcCallHR(spProjectItem->APC_GET(Name)(pbstrActualName)); 
		}
		ApcReturnHR(NOERROR);
	}

	// Undefine -- remove this project item from the project
	//
	// project item definitions are persisted with the project
	// call this after the project is fully created or loaded
	//
	HRESULT Undefine()
	{
		ApcEntryHR(ApcProjectItem::Undefine);

		if (!GetApcProjectItem())
			ApcReturnHR(S_FALSE);

		hr = ApcNotifyHR(("ApcProjectItem_OnUndefine"), m_pProjectItemOwner->ApcProjectItem_OnUndefine());

		Detach();
		
		ApcReturnHR(hr);
	}

	// Register -- register a project item
	//
	// project items are registered prior to ApcProject.Open
	//
	template <class Project>
	HRESULT Register(Project& project, IDispatch* pdisp, BSTR bstrName)
	{
		return Register(project.GetApcRegProjItems(), pdisp, bstrName);
	}

	template <class Project>
	HRESULT Register(Project& project, IDispatch* pdisp, long nID)
	{
		return Register(project.GetApcRegProjItems(), pdisp, nID);
	}

	HRESULT Register(IApcRegProjItems* pRegProjItems, IDispatch* pdisp, BSTR bstrName)
	{
		ApcEntryHR(CApcProjectItemMember::Register);

		_ASSERTE(pRegProjItems); // required argument
		_ASSERTE(pdisp); // required argument
		_ASSERTE(bstrName); // required argument

		if (!m_spProjectItemEvents.p)
			ApcCallHR(_Sink::CreateInstance(m_pProjectItemOwner, &m_spProjectItemEvents.p));

		ApcCallHR(ApcNotifyHR(("ApcProjectItem_OnRegister"), 
			m_pProjectItemOwner->ApcProjectItem_OnRegister(pRegProjItems, pdisp, bstrName, -1)));

		ApcReturnHR(NOERROR);
	}

	HRESULT Register(IApcRegProjItems* pRegProjItems, IDispatch* pdisp, long nID)
	{
		ApcEntryHR(CApcProjectItemMember::Register);

		_ASSERTE(pRegProjItems); // required argument
		_ASSERTE(pdisp); // required argument
		_ASSERTE(nID != -1); // required argument

		if (!m_spProjectItemEvents.p)
			ApcCallHR(_Sink::CreateInstance(m_pProjectItemOwner, &m_spProjectItemEvents.p));

		ApcCallHR(ApcNotifyHR(("ApcProjectItem_OnRegister"), 
			m_pProjectItemOwner->ApcProjectItem_OnRegister(pRegProjItems, pdisp, NULL, nID)));

		ApcReturnHR(NOERROR);
	}

	// Attach -- establish a connection with an IApcProjectItem
	//
	HRESULT Attach(IApcProjectItem* pProjectItem)
	{
		ApcEntryHR(CApcProjectItemMember::Attach);

		hr = ApcNotifyHR(("ApcProjectItem_OnAttach"), m_pProjectItemOwner->ApcProjectItem_OnAttach(pProjectItem));

		if (FAILED(hr))
			Detach();

		return hr;
	}

	// OnAttach -- called by ApcProjectItem_OnAttach
	HRESULT OnAttach(IApcProjectItem* pProjectItem)
	{
		ApcEntryHR(CApcProjectItemMember::OnAttach);

		_ASSERTE(pProjectItem); // argument is required
		_ASSERTE(!GetApcProjectItem()); // already attached?

		if (!m_spProjectItemEvents.p)
			ApcCallHR(_Sink::CreateInstance(m_pProjectItemOwner, &m_spProjectItemEvents.p));

		ApcCallHR(CApcProjectItemPtr::OnAttach(pProjectItem));

		// success!
		ApcReturnHR(NOERROR);
	}

	// Detach -- break the connection with the IApcProjectItem
	//
	void Detach()
	{
		ApcEntryV(CApcProjectItemMember::Detach);
		ApcNotifyV(("ApcProjectItem_OnDetach"), m_pProjectItemOwner->ApcProjectItem_OnDetach());
	}

}; // class CApcProjectItemMember

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcProjectItem<T> - base class for project item

template <class T, class _ProjectItemMember = CApcProjectItemMember<T> >
class CApcProjectItem
{
public:
	// 
	// Members
	// 

	_ProjectItemMember ApcProjectItem;

	// 
	// Lifetime
	// 

	CApcProjectItem() : ApcProjectItem(static_cast<T*>(this)) {}

	// 
	// Notifications
	// 

	HRESULT ApcProjectItem_View()
	{
		return NOERROR;
	}

	HRESULT ApcProjectItem_Activate()
	{
		return NOERROR;
	}

	HRESULT ApcProjectItem_CreateInstance(IDispatch **ppInstance)
	{
		return NOERROR;
	}

	HRESULT ApcProjectItem_ReleaseInstances()
	{
		return NOERROR;
	}

	HRESULT ApcProjectItem_InstanceCreated(IDispatch *pInstance)
	{
		return NOERROR;
	}

	// 
	// Overrides
	// 

	template <class _Project>
	HRESULT ApcProjectItem_OnDefine(_Project& project, IDispatch* pdisp, AxProjectItemType projectItemType, BSTR bstrRequestName, BSTR* pbstrActualName)
	{
		return ApcProjectItem.OnDefine(project, pdisp, projectItemType, bstrRequestName, pbstrActualName);
	}

	HRESULT ApcProjectItem_OnUndefine()
	{
		return ApcProjectItem.OnUndefine();
	}

	HRESULT ApcProjectItem_OnRegister(IApcRegProjItems* pRegs, IDispatch* pdisp, BSTR bstrName, long nID)
	{
		return ApcProjectItem.OnRegister(pRegs, pdisp, bstrName, nID);
	}

	HRESULT ApcProjectItem_OnAttach(IApcProjectItem* pProjectItem)
	{
		return ApcProjectItem.OnAttach(pProjectItem);
	}

	HRESULT ApcProjectItem_OnFinishLoad()
	{
		return ApcProjectItem.OnFinishLoad();
	}

	void ApcProjectItem_OnDetach()
	{
		ApcProjectItem.OnDetach();
	}

	void ApcProjectItem_OnLoadComplete()
	{
		ApcProjectItem.OnLoadComplete();
	}

}; // class CApcProjectItem

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcControlEvents -- used internally by CApcControlMember to implement an event sink 
//

template <class ControlOwner>
class ATL_NO_VTABLE CApcControlEvents 
:
	public ISupportErrorInfoImpl<&APC_IID(IApcControlEvents)>,
	public IApcControlEvents,
	public IApcRegControl,
	public CComObjectRootEx< CComObjectThreadModel >
{
	ControlOwner* m_pControlOwner;

public:
	typedef ControlOwner _ControlOwner;
	typedef CApcControlEvents<_ControlOwner> _CApcControlEvents;
	typedef CComObject<_CApcControlEvents> _Object;

	BEGIN_COM_MAP(_CApcControlEvents)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(APC_IID(IApcControlEvents), IApcControlEvents)
		COM_INTERFACE_ENTRY(IApcRegControl)
	END_COM_MAP()

	static HRESULT CreateInstance(_ControlOwner* pControlOwner, IApcControlEvents** pp)
	{
		HRESULT hRes = E_OUTOFMEMORY;
		_Object* p = NULL;
		ATLTRY(p = new _Object(0))
		if (p != NULL)
		{
			p->SetVoid(0);
			p->InternalFinalConstructAddRef();

			p->Init(pControlOwner);

			hRes = p->FinalConstruct();
			p->InternalFinalConstructRelease();
			if (hRes == S_OK)
				hRes = p->QueryInterface(APC_IID(IApcControlEvents), (void**)pp);
			if (hRes != S_OK)
				delete p;
		}
		return NOERROR;
	}

	CApcControlEvents()
	{
		m_pControlOwner = 0;
	}

	HRESULT Init(_ControlOwner* pControlOwner)
	{
		_ASSERTE(0 == m_pControlOwner); // already attached?
		_ASSERTE(0 != pControlOwner); // argument is required
		m_pControlOwner = pControlOwner;
		return NOERROR;
	}

	// IApcControlEvents
	//

	STDMETHODIMP APC_RAW(Activate)()
	{
		return ApcNotifyHR(("ApcControl_Activate"), m_pControlOwner->ApcControl_Activate());
	}

	// IApcRegControl
	//

	STDMETHOD(Attach)(IApcControl* pControl)
	{
		return ApcNotifyHR(("ApcControl_OnAttach"), m_pControlOwner->ApcControl_OnAttach(pControl));
	}

	STDMETHOD(FinishLoad)()
	{
		return ApcNotifyHR(("ApcControl_OnFinishLoad"), m_pControlOwner->ApcControl_OnFinishLoad());
	}

	STDMETHOD(LoadComplete)(BOOL fGood)
	{
		if (fGood)
		{
			ApcNotifyV(("ApcControl_OnLoadComplete"), m_pControlOwner->ApcControl_OnLoadComplete());
		}
		else
		{
			ApcNotifyV(("ApcControl_OnDetach"), m_pControlOwner->ApcControl_OnDetach());
		}
		return NOERROR;
	}

}; // class CApcControlEvents

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
//
// BEGIN_APC_PROPCAT_MAP
//	APC_PROPCAT_STOCK( dispId, propCat )
//	APC_PROPCAT_USER( dispId, propCat, descrip )
// END_APC_PROPCAT_MAP

struct APC_PROPERTY_MAP
{
	DWORD				m_apcreserved;
	LPCTSTR 			m_name;
	AxPropertyCategory	m_propcat;
	LPCTSTR				m_user;
};

#define BEGIN_APC_PROPCAT_MAP \
	void ApcControl_OnGetPropertyMap(const APC_PROPERTY_MAP** ppMap) const \
	{ \
		static const APC_PROPERTY_MAP pMap[] = {

#define   APC_PROPCAT_STOCK(__d, __p) { 0, (__d), (__p), NULL },
#define   APC_PROPCAT_USER(__d, __u) { 0, (__d), axCategoryUserDefined, (__u) },

#define END_APC_PROPCAT_MAP \
			{ -1, 0, axCategoryNil, 0 } };\
		*ppMap = pMap; \
	} 

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcControlPtr - base class for the "ApcControl" member of CApcControl
//

class CApcControlPtr: public CApcComPtr<IApcControl>
{
protected:
	CComPtr<IApcRegControls> m_spRegs;
	DWORD m_dwRegister;

	CComPtr<IApcControlEvents> m_spControlEvents;
	long m_dwAdvise;

public:
	// 
	// Accessors
	// 

	IApcControl*		GetApcControl() { return *this; }
#ifdef APC_MANGLED_ID
	long ApcID();
#else
	long ID();
#endif

	//
	// Lifetime
	//

	CApcControlPtr();
	~CApcControlPtr();

	//
	// Operations
	//

	// OnDefine - default handler for ApcControl_OnDefine
	HRESULT OnDefine(IApcProjectItem* pProjectItem, IDispatch* pHostControl, AxControlFlag controlFlag, IDispatch* pExtender, IApcControl** ppControl);
	// OnUndefine - default handler for ApcControl_OnUndefine
	HRESULT OnUndefine();
	// OnRegister -- used internally by ApcProjectItem_OnRegister
	HRESULT OnRegister(IApcRegControls* pRegs, BSTR bstrName, long nID, IDispatch* pHostControl, IDispatch* pExtender);
	// OnAttach - default handler for ApcControl_OnAttach
	HRESULT OnAttach(IApcControl* pControl);
	// OnDetach - default handler for ApcControl_OnDetach
	void OnDetach();
};

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcControlMember - the "ApcControl" member of CApcControl
//

template <class _ControlOwner>
class CApcControlMember: public CApcControlPtr
{
	_ControlOwner* m_pControlOwner;
	typedef CApcControlEvents<_ControlOwner> _Sink;

public:
	//
	// Lifetime
	//

	CApcControlMember(_ControlOwner* pControlOwner)
	: 
		m_pControlOwner(pControlOwner)
	{
		_ASSERTE(pControlOwner); // argument is required
	}
	
	~CApcControlMember()
	{ 
		if (GetApcControl())
			Detach(); // still fully attached, so call ApcControl_Detach
		else
			OnDetach(); // not fully attached, so quietly shut down
	}


	//
	// Operations
	//

	// Define - define a new control
	//
	// add a new control to the project item
	// this change will be persisted with the project
	// the project should be fully created or loaded before adding new controls
	//
	template <class _ProjectItem>
	HRESULT Define(_ProjectItem& projectItem, IDispatch* pHostControl, AxControlFlag controlFlag, IDispatch* pExtender = NULL)
	{
		ApcEntryHR(CApcControlMember::Define);

		_ASSERTE(!GetApcControl()); // already attached?

		hr = ApcNotifyHR(("ApcControl_OnDefine"), m_pControlOwner->ApcControl_OnDefine(projectItem, pHostControl, controlFlag, pExtender));
		
		if (FAILED(hr))
			Undefine();

		ApcReturnHR(hr);
	}

	// OnDefine - default handler for ApcControl_OnDefine
	HRESULT OnDefine(IApcProjectItem* pProjectItem, IDispatch* pHostControl, AxControlFlag controlFlag, IDispatch* pExtender)
	{
		ApcEntryHR(CApcControlMember::OnDefine);
		
		_ASSERTE(!GetApcControl()); // already attached?

		CComPtr<IApcControl> spControl;
		ApcCallHR(CApcControlPtr::OnDefine( pProjectItem, pHostControl, controlFlag, pExtender, &spControl.p ));
		ApcCallHR(Attach( spControl ));

		const APC_PROPERTY_MAP* pmap = NULL;
		ApcNotifyV(("ApcControl_OnGetPropertyMap"), m_pControlOwner->ApcControl_OnGetPropertyMap(&pmap));
		ApcCallHR(ApcApplyPropertyMap(GetApcControl(), pmap));

		ApcReturnHR(NOERROR);
	}

	// Undefine - undefine a control
	//
	// remove the control from the project item
	// this change will be persisted with the project
	// the project should be fully created or loaded before removing controls
	//
	HRESULT Undefine()
	{
		ApcEntryHR(CApcControlMember::Undefine);

		if (!GetApcControl())
			ApcReturnHR(S_FALSE);

		hr = ApcNotifyHR(("ApcControl_OnUndefine"), m_pControlOwner->ApcControl_OnUndefine());

		Detach();
		
		ApcReturnHR(hr);
	}

	// Register - 
	//
	// controls are registered prior to ApcProject.Open
	//
	template <class ProjItem>
	HRESULT Register(ProjItem& projItem, BSTR bstrName, IDispatch* pHostControl, IDispatch* pExtender = NULL)
	{
		IApcRegControls* pRegs = projItem.GetApcRegControls();
		_ASSERTE(pRegs); // already attached or out of memory?
		return Register(projItem.GetApcRegControls(), bstrName, pHostControl, pExtender);
	}

	HRESULT Register(IApcRegControls* pRegs, BSTR bstrName, IDispatch* pHostControl, IDispatch* pExtender = NULL)
	{
		ApcEntryHR(CApcControlMember::Register);

		_ASSERTE(pRegs); // required argument
		_ASSERTE(bstrName); // required argument
		_ASSERTE(pHostControl); // required argument

		if (!m_spControlEvents.p)
			ApcCallHR(_Sink::CreateInstance(m_pControlOwner, &m_spControlEvents.p));

		ApcCallHR(ApcNotifyHR(("ApcControl_OnRegister"), 
			m_pControlOwner->ApcControl_OnRegister(pRegs, bstrName, -1, pHostControl, pExtender)));

		ApcReturnHR(NOERROR);
	}

	template <class ProjItem>
	HRESULT Register(ProjItem& projItem, long nID, IDispatch* pHostControl, IDispatch* pExtender = NULL)
	{
		IApcRegControls* pRegs = projItem.GetApcRegControls();
		_ASSERTE(pRegs); // already attached or out of memory?
		return Register(pRegs, nID, pHostControl, pExtender);
	}

	HRESULT Register(IApcRegControls* pRegs, long nID, IDispatch* pHostControl, IDispatch* pExtender = NULL)
	{
		ApcEntryHR(CApcControlMember::Register);

		_ASSERTE(pRegs); // required argument
		_ASSERTE(nID != -1); // required argument
		_ASSERTE(pHostControl); // required argument

		if (!m_spControlEvents.p)
			ApcCallHR(_Sink::CreateInstance(m_pControlOwner, &m_spControlEvents.p));

		ApcCallHR(ApcNotifyHR(("ApcControl_OnRegister"), 
			m_pControlOwner->ApcControl_OnRegister(pRegs, NULL, nID, pHostControl, pExtender)));

		ApcReturnHR(NOERROR);
	}

	// Attach - establish connection between this object and the IApcControl
	//
	HRESULT Attach(IApcControl* pControl)
	{
		HRESULT hr = ApcNotifyHR(("ApcControl_OnAttach"), m_pControlOwner->ApcControl_OnAttach(pControl));

		if (FAILED(hr))
			Detach(); 

		return hr;
	}

	// OnAttach - default handler for ApcControl_OnAttach
	HRESULT OnAttach(IApcControl* pControl)
	{
		ApcEntryHR(CApcControlMember::OnAttach);

		_ASSERTE(pControl); // argument is required
		_ASSERTE(!GetApcControl()); // already attached?

		if (!m_spControlEvents.p)
			ApcCallHR(_Sink::CreateInstance(m_pControlOwner, &m_spControlEvents.p));

		ApcCallHR(CApcControlPtr::OnAttach(pControl));

		// success!
		ApcReturnHR(NOERROR);
	}

	// Detach - break the connection between this object and the IApcControl
	//
	void Detach()
	{
		ApcEntryV(ApcControl::Detach);
		ApcNotifyV(("ApcControl_OnDetach"), m_pControlOwner->ApcControl_OnDetach());
	}

	HRESULT OnFinishLoad()
	{
		ApcEntryHR(CApcControlMember::OnFinishLoad);

		_ASSERTE(GetApcControl());

		const APC_PROPERTY_MAP* pmap = NULL;
		ApcNotifyV(("ApcControl_OnGetPropertyMap"), m_pControlOwner->ApcControl_OnGetPropertyMap(&pmap));
		ApcCallHR(ApcApplyPropertyMap(GetApcControl(), pmap));

		// success!
		ApcReturnHR(NOERROR);
	}

}; // class CApcControlMember

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcControl<T> - base class for control site or control

template <class T, class _ControlMember = CApcControlMember<T> >
class CApcControl
{
public:
	// 
	// Members
	// 

	_ControlMember ApcControl;

	// 
	// Lifetime
	// 

	CApcControl() : ApcControl(static_cast<T*>(this)) {}


	// 
	// IApcControlEvents Notification
	// 

	HRESULT ApcControl_Activate()
	{
		return NOERROR;
	}

	// 
	// Overrides
	// 

	// ApcControl_OnDefine - called by ApcControl.Define
	//
	HRESULT ApcControl_OnDefine(IApcProjectItem* pProjectItem, IDispatch* pHostControl, AxControlFlag controlFlag, IDispatch* pExtender)
	{
		return ApcControl.OnDefine(pProjectItem, pHostControl, controlFlag, pExtender);
	}

	// ApcControl_OnUndefine - called by ApcControl.Undefine
	//
	HRESULT ApcControl_OnUndefine()
	{
		return ApcControl.OnUndefine();
	}

	// ApcControl_OnRegister - register for hookup at project load-time
	//
	HRESULT ApcControl_OnRegister(IApcRegControls* pRegs, BSTR bstrName, long nID, IDispatch* pHostControl, IDispatch* pExtender)
	{
		return ApcControl.OnRegister(pRegs, bstrName, nID, pHostControl, pExtender);
	}

	// ApcControl_OnGetPropertyMap - called by ApcControl_OnAttach
	//
	void ApcControl_OnGetPropertyMap(const APC_PROPERTY_MAP** ppmap) const 
	{ 
		*ppmap = NULL;
	}

	// ApcControl_OnAttach - called by ApcControl.Attach
	//
	HRESULT ApcControl_OnAttach(IApcControl* pControl)
	{
		return ApcControl.OnAttach(pControl);
	}

	// ApcControl_OnDetach - called by ApcControl.Detach
	//
	void ApcControl_OnDetach()
	{
		ApcControl.OnDetach();
	}

	// ApcControl_OnFinishLoad - everything loaded and hooked up
	//
	HRESULT ApcControl_OnFinishLoad()
	{
		ApcEntryHR(CApcControl_OnFinishLoad);
		ApcCallHR(ApcControl.OnFinishLoad());
		ApcReturnHR(NOERROR);
	}

	// ApcControl_OnLoadComplete - entire project has loaded
	//
	void ApcControl_OnLoadComplete()
	{
	}

}; // class CApcControl

/////////////////////////////////////////////////////////////////////////////

} // namespace MSAPC

#endif//APCCPP_H_INCLUDED

