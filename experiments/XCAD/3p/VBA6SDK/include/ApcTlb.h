/* --------------------------------------------------------------------------
* ApcTlb.h
*
* Header file for the APC COM interfaces.
*
* This file is part of the Microsoft OneTool Wrapper (APC)
* Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
* Information Contained Herein Is Proprietary and Confidential.
* -------------------------------------------------------------------------- */
/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Wed Sep 24 07:45:49 2003
 */
/* Compiler settings for .\vbahost.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __vbatlb_h__
#define __vbatlb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IApcX_FWD_DEFINED__
#define __IApcX_FWD_DEFINED__
typedef interface IApcX IApcX;
#endif 	/* __IApcX_FWD_DEFINED__ */


#ifndef __IApcGlobal_FWD_DEFINED__
#define __IApcGlobal_FWD_DEFINED__
typedef interface IApcGlobal IApcGlobal;
#endif 	/* __IApcGlobal_FWD_DEFINED__ */


#ifndef __IApc_FWD_DEFINED__
#define __IApc_FWD_DEFINED__
typedef interface IApc IApc;
#endif 	/* __IApc_FWD_DEFINED__ */


#ifndef __IApcEvents_FWD_DEFINED__
#define __IApcEvents_FWD_DEFINED__
typedef interface IApcEvents IApcEvents;
#endif 	/* __IApcEvents_FWD_DEFINED__ */


#ifndef __IApcIde_FWD_DEFINED__
#define __IApcIde_FWD_DEFINED__
typedef interface IApcIde IApcIde;
#endif 	/* __IApcIde_FWD_DEFINED__ */


#ifndef __IApcIdeEvents_FWD_DEFINED__
#define __IApcIdeEvents_FWD_DEFINED__
typedef interface IApcIdeEvents IApcIdeEvents;
#endif 	/* __IApcIdeEvents_FWD_DEFINED__ */


#ifndef __IApcPropertiesWindow_FWD_DEFINED__
#define __IApcPropertiesWindow_FWD_DEFINED__
typedef interface IApcPropertiesWindow IApcPropertiesWindow;
#endif 	/* __IApcPropertiesWindow_FWD_DEFINED__ */


#ifndef __IApcProjects_FWD_DEFINED__
#define __IApcProjects_FWD_DEFINED__
typedef interface IApcProjects IApcProjects;
#endif 	/* __IApcProjects_FWD_DEFINED__ */


#ifndef __IApcProject_FWD_DEFINED__
#define __IApcProject_FWD_DEFINED__
typedef interface IApcProject IApcProject;
#endif 	/* __IApcProject_FWD_DEFINED__ */


#ifndef __IApcProjectEvents_FWD_DEFINED__
#define __IApcProjectEvents_FWD_DEFINED__
typedef interface IApcProjectEvents IApcProjectEvents;
#endif 	/* __IApcProjectEvents_FWD_DEFINED__ */


#ifndef __IApcProjectItems_FWD_DEFINED__
#define __IApcProjectItems_FWD_DEFINED__
typedef interface IApcProjectItems IApcProjectItems;
#endif 	/* __IApcProjectItems_FWD_DEFINED__ */


#ifndef __IApcProjectItem_FWD_DEFINED__
#define __IApcProjectItem_FWD_DEFINED__
typedef interface IApcProjectItem IApcProjectItem;
#endif 	/* __IApcProjectItem_FWD_DEFINED__ */


#ifndef __IApcProjectItemEvents_FWD_DEFINED__
#define __IApcProjectItemEvents_FWD_DEFINED__
typedef interface IApcProjectItemEvents IApcProjectItemEvents;
#endif 	/* __IApcProjectItemEvents_FWD_DEFINED__ */


#ifndef __IApcControls_FWD_DEFINED__
#define __IApcControls_FWD_DEFINED__
typedef interface IApcControls IApcControls;
#endif 	/* __IApcControls_FWD_DEFINED__ */


#ifndef __IApcControl_FWD_DEFINED__
#define __IApcControl_FWD_DEFINED__
typedef interface IApcControl IApcControl;
#endif 	/* __IApcControl_FWD_DEFINED__ */


#ifndef __IApcControlEvents_FWD_DEFINED__
#define __IApcControlEvents_FWD_DEFINED__
typedef interface IApcControlEvents IApcControlEvents;
#endif 	/* __IApcControlEvents_FWD_DEFINED__ */


#ifndef __IApcProcedures_FWD_DEFINED__
#define __IApcProcedures_FWD_DEFINED__
typedef interface IApcProcedures IApcProcedures;
#endif 	/* __IApcProcedures_FWD_DEFINED__ */


#ifndef __IApcProcedure_FWD_DEFINED__
#define __IApcProcedure_FWD_DEFINED__
typedef interface IApcProcedure IApcProcedure;
#endif 	/* __IApcProcedure_FWD_DEFINED__ */


#ifndef __IApcCategories_FWD_DEFINED__
#define __IApcCategories_FWD_DEFINED__
typedef interface IApcCategories IApcCategories;
#endif 	/* __IApcCategories_FWD_DEFINED__ */


#ifndef __IApcCategory_FWD_DEFINED__
#define __IApcCategory_FWD_DEFINED__
typedef interface IApcCategory IApcCategory;
#endif 	/* __IApcCategory_FWD_DEFINED__ */


#ifndef __IApcMiniBitmaps_FWD_DEFINED__
#define __IApcMiniBitmaps_FWD_DEFINED__
typedef interface IApcMiniBitmaps IApcMiniBitmaps;
#endif 	/* __IApcMiniBitmaps_FWD_DEFINED__ */


#ifndef __IApcMiniBitmap_FWD_DEFINED__
#define __IApcMiniBitmap_FWD_DEFINED__
typedef interface IApcMiniBitmap IApcMiniBitmap;
#endif 	/* __IApcMiniBitmap_FWD_DEFINED__ */


#ifndef __IApcRecorder_FWD_DEFINED__
#define __IApcRecorder_FWD_DEFINED__
typedef interface IApcRecorder IApcRecorder;
#endif 	/* __IApcRecorder_FWD_DEFINED__ */


#ifndef __IApcScopes_FWD_DEFINED__
#define __IApcScopes_FWD_DEFINED__
typedef interface IApcScopes IApcScopes;
#endif 	/* __IApcScopes_FWD_DEFINED__ */


#ifndef __IApcScope_FWD_DEFINED__
#define __IApcScope_FWD_DEFINED__
typedef interface IApcScope IApcScope;
#endif 	/* __IApcScope_FWD_DEFINED__ */


#ifndef __IApcMacrosDialog_FWD_DEFINED__
#define __IApcMacrosDialog_FWD_DEFINED__
typedef interface IApcMacrosDialog IApcMacrosDialog;
#endif 	/* __IApcMacrosDialog_FWD_DEFINED__ */


#ifndef __IApcStorage_FWD_DEFINED__
#define __IApcStorage_FWD_DEFINED__
typedef interface IApcStorage IApcStorage;
#endif 	/* __IApcStorage_FWD_DEFINED__ */


#ifndef __IApcStream_FWD_DEFINED__
#define __IApcStream_FWD_DEFINED__
typedef interface IApcStream IApcStream;
#endif 	/* __IApcStream_FWD_DEFINED__ */


#ifndef __IApcRequiredClasses_FWD_DEFINED__
#define __IApcRequiredClasses_FWD_DEFINED__
typedef interface IApcRequiredClasses IApcRequiredClasses;
#endif 	/* __IApcRequiredClasses_FWD_DEFINED__ */


#ifndef __IApcRequiredClass_FWD_DEFINED__
#define __IApcRequiredClass_FWD_DEFINED__
typedef interface IApcRequiredClass IApcRequiredClass;
#endif 	/* __IApcRequiredClass_FWD_DEFINED__ */


#ifndef __IApcExtender_FWD_DEFINED__
#define __IApcExtender_FWD_DEFINED__
typedef interface IApcExtender IApcExtender;
#endif 	/* __IApcExtender_FWD_DEFINED__ */


#ifndef __IApcSite_FWD_DEFINED__
#define __IApcSite_FWD_DEFINED__
typedef interface IApcSite IApcSite;
#endif 	/* __IApcSite_FWD_DEFINED__ */


#ifndef __IApcCompManager_FWD_DEFINED__
#define __IApcCompManager_FWD_DEFINED__
typedef interface IApcCompManager IApcCompManager;
#endif 	/* __IApcCompManager_FWD_DEFINED__ */


#ifndef __IApcInstances_FWD_DEFINED__
#define __IApcInstances_FWD_DEFINED__
typedef interface IApcInstances IApcInstances;
#endif 	/* __IApcInstances_FWD_DEFINED__ */


#ifndef __IApcHostAddIns_FWD_DEFINED__
#define __IApcHostAddIns_FWD_DEFINED__
typedef interface IApcHostAddIns IApcHostAddIns;
#endif 	/* __IApcHostAddIns_FWD_DEFINED__ */


#ifndef __IApcLegacyEvents_FWD_DEFINED__
#define __IApcLegacyEvents_FWD_DEFINED__
typedef interface IApcLegacyEvents IApcLegacyEvents;
#endif 	/* __IApcLegacyEvents_FWD_DEFINED__ */


#ifndef __ApcEvents_FWD_DEFINED__
#define __ApcEvents_FWD_DEFINED__
typedef interface ApcEvents ApcEvents;
#endif 	/* __ApcEvents_FWD_DEFINED__ */


#ifndef __ApcIdeEvents_FWD_DEFINED__
#define __ApcIdeEvents_FWD_DEFINED__
typedef interface ApcIdeEvents ApcIdeEvents;
#endif 	/* __ApcIdeEvents_FWD_DEFINED__ */


#ifndef __ApcProjectEvents_FWD_DEFINED__
#define __ApcProjectEvents_FWD_DEFINED__
typedef interface ApcProjectEvents ApcProjectEvents;
#endif 	/* __ApcProjectEvents_FWD_DEFINED__ */


#ifndef __ApcProjectItemEvents_FWD_DEFINED__
#define __ApcProjectItemEvents_FWD_DEFINED__
typedef interface ApcProjectItemEvents ApcProjectItemEvents;
#endif 	/* __ApcProjectItemEvents_FWD_DEFINED__ */


#ifndef __ApcControlEvents_FWD_DEFINED__
#define __ApcControlEvents_FWD_DEFINED__
typedef interface ApcControlEvents ApcControlEvents;
#endif 	/* __ApcControlEvents_FWD_DEFINED__ */


#ifndef __ApcExtenderDisp_FWD_DEFINED__
#define __ApcExtenderDisp_FWD_DEFINED__
typedef interface ApcExtenderDisp ApcExtenderDisp;
#endif 	/* __ApcExtenderDisp_FWD_DEFINED__ */


#ifndef __ApcExtenderEvents_FWD_DEFINED__
#define __ApcExtenderEvents_FWD_DEFINED__
typedef interface ApcExtenderEvents ApcExtenderEvents;
#endif 	/* __ApcExtenderEvents_FWD_DEFINED__ */


#ifndef __IApcCollection_FWD_DEFINED__
#define __IApcCollection_FWD_DEFINED__
typedef interface IApcCollection IApcCollection;
#endif 	/* __IApcCollection_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "servprov.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 


#pragma warning( disable : 4514 )		


extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;


#ifndef __MSAPC_LIBRARY_DEFINED__
#define __MSAPC_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MSAPC
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [version][helpfile][helpstring][uuid] */ 


#define SID_SApc IID_IApcX
typedef /* [uuid] */ 
enum AxProjectProtection
    {	axProtectionNone	= 0,
	axProtectionUser	= 1,
	axProtectionHost	= 2,
	axProtectionVBA	= 4
    }	AxProjectProtection;

typedef AxProjectProtection APCPROJECTPROTECTION;

typedef /* [uuid] */ 
enum AxProjectFlag
    {	axProjectNormal	= 0,
	axProjectHidden	= 1,
	axProjectDisableMacros	= 2,
	axProjectDisableSave	= 4,
	axProjectThrowAwayCompiledState	= 8
    }	AxProjectFlag;

typedef AxProjectFlag APCPROJECTFLAG;

typedef /* [uuid] */ 
enum AxProcedureScope
    {	axScopePublic	= 0,
	axScopePrivate	= 1
    }	AxProcedureScope;

typedef enum AxProcedureScope APCPROCEDURESCOPE;

typedef /* [uuid] */ 
enum AxProcedureType
    {	axProcTypePropertyLet	= 0,
	axProcTypePropertySet	= 1,
	axProcTypePropertyGet	= 2,
	axProcTypeFunction	= 3,
	axProcTypeSub	= 4,
	axProcTypeEventSub	= 5
    }	AxProcedureType;

typedef enum AxProcedureType APCPROCEDURETYPE;

typedef /* [uuid] */ 
enum AxControlFlag
    {	axControlNormal	= 0,
	axControlNotInPropertiesWindow	= 1,
	axControlNoCodeBehind	= 2
    }	AxControlFlag;

typedef enum AxControlFlag APCCONTROLFLAG;

typedef /* [uuid] */ 
enum AxProjectItemType
    {	axTypeCodeModule	= 0,
	axTypeClassModule	= 1,
	axTypeDesigner	= 2,
	axTypeHostProjectItem	= 3,
	axTypeHostClass	= 4,
	axTypeOther	= 5
    }	AxProjectItemType;

typedef enum AxProjectItemType APCPROJECTITEMTYPE;

typedef /* [uuid] */ 
enum AxProjectMode
    {	axModeDesign	= 0,
	axModeRun	= axModeDesign + 1
    }	AxProjectMode;

typedef enum AxProjectMode APCPROJECTMODE;

typedef /* [uuid] */ 
enum AxStepMode
    {	axStepNone	= 0,
	axStepInto	= 1,
	axStepOver	= 2
    }	AxStepMode;

typedef enum AxStepMode APCSTEPMODE;

typedef /* [uuid] */ 
enum AxAccessMode
    {	axAccessTransacted	= 0x1L,
	axAccessRead	= 0x2L,
	axAccessWrite	= 0x4L,
	axAccessReadWrite	= 0x8L,
	axAccessShared	= 0x10L,
	axAccessLockRead	= 0x20L,
	axAccessLockWrite	= 0x40L,
	axAccessExclusive	= 0x80L,
	axAccessPreserveStorage	= 0x100L,
	axAccessPreserveFlags	= 0x10000000L
    }	AxAccessMode;

typedef enum AxAccessMode APCACCESSMODE;

typedef /* [uuid] */ 
enum AxPropertyCategory
    {	axCategoryNil	= 0xffffffffL,
	axCategoryMisc	= 0xfffffffeL,
	axCategoryFont	= 0xfffffffdL,
	axCategoryPosition	= 0xfffffffcL,
	axCategoryAppearance	= 0xfffffffbL,
	axCategoryBehavior	= 0xfffffffaL,
	axCategoryData	= 0xfffffff9L,
	axCategoryList	= 0xfffffff8L,
	axCategoryText	= 0xfffffff7L,
	axCategoryScale	= 0xfffffff6L,
	axCategoryDDE	= 0xfffffff5L,
	axCategoryUserDefined	= 0L
    }	AxPropertyCategory;

typedef enum AxPropertyCategory APCPROPERTYCATEGORY;

typedef /* [uuid] */ 
enum AxDialogStartUpPosition
    {	axPositionManual	= 0,
	axPositionCenterOwner	= 1,
	axPositionCenterScreen	= 2,
	axPositionWindowsDefault	= 3
    }	AxDialogStartUpPosition;

typedef enum AxDialogStartUpPosition APCDIALOGSTARTUPPOSITION;

typedef /* [restricted][uuid] */ 
enum AxMessageLoopReason
    {	axMsgLoopFocusWait	= 0,
	axMsgLoopDoEvents	= 1,
	axMsgLoopDebug	= 2,
	axMsgLoopModalUserForm	= 3
    }	AxMessageLoopReason;

typedef enum AxMessageLoopReason APCLOOPREASON;

typedef /* [restricted][uuid] */ 
enum AxIdleFlag
    {	axIdlePeriodic	= 1,
	axIdleNonPeriodic	= 2,
	axIdlePriority	= 4
    }	AxIdleFlag;

typedef enum AxIdleFlag APCIDLEFLAG;


enum AxError
    {	APC_E_INVALIDINDEX	= 0x80040500L,
	APC_E_ZOMBIED	= 0x80040501L,
	APC_E_UNEXPECTED	= 0x80040502L,
	APC_E_OUTOFMEMORY	= 0x80040503L,
	APC_E_OPENFILEFAILED	= 0x80040504L,
	APC_E_ONLYDOCITEMS	= 0x80040505L,
	APC_E_VBA	= 0x80040506L,
	APC_E_OUTOFSYNC	= 0x80040507L,
	APC_E_INVALIDITEM	= 0x80040508L,
	APC_E_ONLYCODEMODULES	= 0x80040509L,
	APC_E_PROJECTLOCKED	= 0x8004050aL,
	APC_E_TYPELIBCHANGED	= 0x8004050bL,
	APC_E_CLASSNOTFOUND	= 0x8004050cL,
	APC_E_ONLYSUBROUTINES	= 0x8004050dL,
	APC_E_ALREADYRECORDING	= 0x8004050eL,
	APC_E_UNDOEMPTY	= 0x8004050fL,
	APC_E_NOTEVENT	= 0x80040510L,
	APC_E_TOOMANYCONTROLS	= 0x80040511L,
	APC_E_BADOBJ	= 0x80040512L,
	APC_E_SUBORFUNCEXPECTED	= 0x80040513L,
	APC_E_CANTCOPYTYPELIB	= 0x80040514L,
	APC_E_NOSCOPES	= 0x80040515L,
	APC_E_NOPERMISSION	= 0x80040516L,
	APC_E_TOOMANYOPENFILES	= 0x80040517L,
	APC_E_FILEALREADYEXISTS	= 0x80040518L,
	APC_E_OUTOFDISKSPACE	= 0x80040519L,
	APC_E_ONLYFORINMEMORY	= 0x8004051aL,
	APC_E_CANTACCESSARRAY	= 0x8004051bL,
	APC_E_NOREADORLOCKSTORAGE	= 0x8004051cL,
	APC_E_INVALIDFILENAME	= 0x8004051dL,
	APC_E_INVALIDINMEMORYSTG	= 0x8004051eL,
	APC_E_UNKNOWN	= 0x8004051fL,
	APC_E_INVALIDARG	= 0x80040520L,
	APC_E_INVALIDARG_SPECIFIC	= 0x80040521L,
	APC_E_BADPARMCOUNT	= 0x80040522L,
	APC_E_BADVARTYPE	= 0x80040523L,
	APC_E_OVERFLOW	= 0x80040524L,
	APC_E_TYPEMISMATCH	= 0x80040525L,
	APC_E_PARMNOTOPTIONAL	= 0x80040526L,
	APC_E_UNKNOWNLCID	= 0x80040527L,
	APC_E_CONNECTION_TERMINATED	= 0x80040528L,
	APC_E_CALL_REJECTED	= 0x80040529L,
	APC_E_BUSY	= 0x8004052aL,
	APC_E_CALLFAILED	= 0x8004052bL,
	APC_E_EXCEPTION	= 0x8004052cL,
	APC_E_NOCOLLECTION	= 0x8004052dL,
	APC_E_CANT_CREATE_PROJECTITEMS_COLLECTION	= 0x8004052eL,
	APC_E_CANT_CREATE_APC_DATA_STREAM	= 0x8004052fL,
	APC_E_CANT_CREATE_PROJITEM_DATA_STREAM	= 0x80040530L,
	APC_E_CANT_CREATE_VBA_STREAM	= 0x80040531L,
	APC_E_COULDNOTACCESSSTREAM	= 0x80040532L,
	APC_E_DISKERROR	= 0x80040533L,
	APC_E_INVALIDSEEKPOS	= 0x80040534L,
	APC_E_REVERTED	= 0x80040535L,
	APC_E_UNKNOWNPROPERTYNAME	= 0x80040536L,
	APC_E_HOSTCONTROLALREADYSET	= 0x80040537L,
	APC_E_EXTENDERALREADYSET	= 0x80040538L,
	APC_E_NOTATTACHED	= 0x80040539L,
	APC_E_INVALIDFILEFILTER	= 0x8004053aL,
	APC_E_SHAREVIOLATION	= 0x8004053bL,
	APC_E_NOTCURRENT	= 0x8004053cL,
	APC_E_UNDEFINEDPROC	= 0x8004053dL,
	APC_E_INVALIDPROCNAME	= 0x8004053eL,
	APC_E_CANTEXITDESIGNMODE	= 0x8004053fL,
	APC_E_HOSTPROJITEM_NOEVENT	= 0x80040540L,
	APC_E_CONTROL_NOEVENT	= 0x80040541L,
	APC_E_EXTENDER_NOEVENT	= 0x80040542L,
	APC_E_PROJ_STG_ALREADYINITIALIZED	= 0x80040543L,
	APC_E_MODNAMECONFLICT	= 0x80040544L,
	APC_E_INVALID_IDENT_STRING	= 0x80040545L,
	APC_E_HOSTCONTROLNOTSET	= 0x80040546L,
	APC_E_EXTENDERNOTSET	= 0x80040547L,
	APC_E_CANT_CREATE_TEMP_DIR	= 0x80040548L,
	APC_E_OBJECTNOTSET	= 0x80040549L,
	APC_E_CORRUPTSTORAGE	= 0x8004054aL,
	APC_E_COULD_NOT_REMOVE_OBJ	= 0x8004054bL,
	APC_E_COULD_NOT_ADD_OBJ	= 0x8004054cL,
	APC_E_COULD_NOT_CREATE_CODEMODULE	= 0x8004054dL,
	APC_E_COULD_NOT_CREATE_CLASSMODULE	= 0x8004054eL,
	APC_E_CANT_CREATE_PROJITEM	= 0x8004054fL,
	APC_E_CANT_ACCESS_TYPELIB	= 0x80040550L,
	APC_E_NO_VBA_PROJECT	= 0x80040551L,
	APC_E_COMPILEERROR	= 0x80040552L,
	APC_E_TOO_MANY_HOSTS	= 0x80040553L,
	APC_E_PROJECT_ITEM_COUNT_MISMATCH	= 0x80040554L,
	APC_E_PROJECT_ITEM_MISMATCH	= 0x80040555L,
	APC_E_INVALID_PROJECT_ITEM	= 0x80040556L,
	APC_E_CANT_READ_APC_DATA	= 0x80040557L,
	APC_E_INCORRECT_VERSION	= 0x80040558L,
	APC_E_INVALID_PICTURE	= 0x80040559L,
	APC_E_EXCEEDED_HOST_COUNT	= 0x8004055aL,
	APC_E_BAD_VBA_INSTALLATION	= 0x8004055bL,
	APC_E_EXPIRED	= 0x8004055cL,
	APC_E_INCORRECT_VBA_VERSION	= 0x8004055dL,
	APC_E_CLASS_NOT_FOUND	= 0x8004055eL,
	APC_E_CANT_FIRE_EVENT	= 0x8004055fL,
	APC_E_PROJECT_ALREADY_EXISTS	= 0x80040560L,
	APC_E_USER_INTERRUPT	= 0x80040561L,
	APC_E_INVALID_APP_OBJ	= 0x80040562L,
	APC_E_STORAGE_NOPERMISSION	= 0x80040563L,
	APC_E_MINIBITMAP_CANT_BE_CHANGED	= 0x80040564L,
	APC_E_CANTSAVE	= 0x80040565L,
	APC_E_APP_OBJECT_REQUIRED	= 0x80040566L,
	APC_E_NO_COMP_MANAGER	= 0x80040567L,
	APC_E_NOT_A_FORM	= 0x80040568L,
	APC_E_NO_UI	= 0x80040569L,
	APC_E_STILL_LOADING_CONTROLS	= 0x8004056aL,
	APC_E_MACRO_NAME_CONFLICT	= 0x8004056bL,
	APC_E_BROKEN_REFERENCE	= 0x8004056cL,
	APC_E_FILENOTFOUND	= 0x8004056dL,
	APC_E_NO_VBA_PROJECTITEM	= 0x8004056eL,
	APC_E_CONTROLNOTREGISTERED	= 0x8004056fL,
	APC_E_BADLICENSEDCONTROL	= 0x80040570L,
	APC_E_CANTREGISTERCONTROL	= 0x80040571L,
	APC_E_CANTREADREGISTRY	= 0x80040572L,
	APC_E_NOAGGREGATION	= 0x80040573L,
	APC_E_INVALIDCLASSID	= 0x80040574L,
	APC_E_EXTCLASSNOTREGISTERED	= 0x80040575L,
	APC_E_STREAM_OR_STORAGE_ALREADYEXISTS	= 0x80040576L,
	APC_E_NOTIMPLEMENTED	= 0x80040577L,
	APC_E_PROJECT_IS_PROTECTED	= 0x80040578L,
	APC_E_NOT_IN_DESIGN_MODE	= 0x80040579L,
	APC_E_MACROS_ARE_DISABLED	= 0x8004057aL,
	APC_E_NO_CONTROL_TYPELIBRARY_GUID	= 0x8004057bL,
	APC_E_USERFORM_NOT_SUPPORTED	= 0x8004057cL,
	APC_E_DUPLICATE_DOCUMENT_OBJECT_SPECIFIED	= 0x8004057dL,
	APC_E_INVALID_PROPERTY_TYPE	= 0x8004057eL,
	APC_E_INVALIDVARIANT_OR_INVALIDSEEKPOS	= 0x8004057fL,
	APC_E_HOSTOBJECT_REQUIRED	= 0x80040580L,
	APC_E_INVALID_HOSTOBJECT	= 0x80040581L,
	APC_E_HOST_ALREADYINITIALIZED	= 0x80040582L,
	APC_E_EVENTSINK_ALREADYINITIALIZED	= 0x80040583L,
	APC_E_EVENTSINK_INVALID	= 0x80040584L,
	APC_E_EVENTSINK_INVALIDCOOKIE	= 0x80040585L,
	APC_E_VBAMACROENABLE_DONTOPEN	= 0x80040586L,
	APC_E_CONTROL_LIBRARY_ALREADY_MADE	= 0x80040587L,
	APC_E_FAILED_VBASIGNPROJECT	= 0x80040588L,
	APC_E_INVALID_USERPASSWORD	= 0x80040589L,
	APC_E_ONLYDOCCLASSES	= 0x8004058aL,
	APC_E_HOSTADDINS_ALREADYINITIALIZED	= 0x8004058bL,
	APC_E_HOSTADDINSINIT_NOREGISTRYPATH	= 0x8004058cL,
	APC_E_HOSTADDINSINIT_NOLICENSEKEY	= 0x8004058dL,
	APC_E_HOSTADDINSINIT_NOHOSTOBJECT	= 0x8004058eL,
	APC_E_HOSTADDINSINIT_NOAPCOBJECT	= 0x8004058fL,
	APC_E_HOSTADDINSPUT_INVALID_REGISTRYPATH	= 0x80040590L,
	APC_E_BACKCOLOR_CANT_BE_CHANGED	= 0x80040591L,
	APC_E_CONTROL_MARKED_FOR_DELETE	= 0x80040592L,
	APC_E_HOSTADDINSINIT_FAILED	= 0x80040593L,
	APC_E_SHOWADDINSDIALOG_FAILED	= 0x80040594L,
	APC_E_NOTRECORDING	= 0x80040595L,
	APC_E_ROUNDTRIP_STREAM_NOT_FOUND	= 0x80040596L,
	APC_E_ROUNDTRIP_STORAGE_NOT_FOUND	= 0x80040597L,
	APC_E_ROUNDTRIP_STORAGE_NOT_INITIALIZED	= 0x80040598L,
	APC_E_INVALID_LICENSE_KEY	= 0x80040599L,
	APC_E_CANT_RUN_IN_BREAK_MODE	= 0x8004059aL,
	APC_E_DIGITAL_SIGNING_DISABLED	= 0x8004059bL,
	APC_E_ACTIONCANCELLED	= 0x8004059cL,
	APC_E_COLLECTION_ADD_DUPLICATEKEY	= 0x8004059dL,
	APC_E_COLLECTION_ITEMS_NOT_IDISPATCH	= 0x8004059eL,
	APC_S_SIGNFAILED	= 0x4004059fL,
	APC_E_LAST_ERROR	= 0x800405a0L
    };
typedef /* [uuid] */ 
enum AxProcKind
    {	axProcKindProc	= 0,
	axProcKindLet	= 1,
	axProcKindSet	= 2,
	axProcKindGet	= 3
    }	AxProcKind;

typedef enum AxProcKind APCPROCKIND;

typedef /* [uuid] */ 
enum AxSecurityLevel
    {	axSecurityNone	= 1,
	axSecurityMedium	= 2,
	axSecurityHigh	= 3,
	axSecurityVeryHigh	= 4
    }	AxSecurityLevel;

typedef enum AxSecurityLevel APCSECURITYLEVEL;

typedef /* [uuid] */ 
enum AxHelpStyle
    {	axHelpHTML	= 0,
	axHelpWindows	= 1
    }	AxHelpStyle;

typedef enum AxHelpStyle APCHELPSTYLE;





































EXTERN_C const IID LIBID_MSAPC;

#ifndef __IApcX_INTERFACE_DEFINED__
#define __IApcX_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcX
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [local][restricted][uuid] */ 



EXTERN_C const IID IID_IApcX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcX
    {
    public:
        BEGIN_INTERFACE
        END_INTERFACE
    };
    
#else 	/* C style interface */

    typedef struct IApcXVtbl
    {
        BEGIN_INTERFACE
        
        END_INTERFACE
    } IApcXVtbl;

    interface IApcX
    {
        CONST_VTBL struct IApcXVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IApcX_INTERFACE_DEFINED__ */


#ifndef __IApcGlobal_INTERFACE_DEFINED__
#define __IApcGlobal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcGlobal
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][helpcontext][helpstring][uuid] */ 



EXTERN_C const IID IID_IApcGlobal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcGlobal : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateStorage( 
            /* [optional][in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OpenStorage( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [defaultvalue][in] */ VARIANT_BOOL inMemory,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateStorageInMemory( 
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OpenStorageInMemory( 
            /* [in] */ VARIANT byteArray,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppIApcStorage) = 0;
        
        virtual /* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE WrapStorage( 
            /* [in] */ IUnknown __RPC_FAR *pSource,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppDest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcGlobalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcGlobal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcGlobal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcGlobal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStorage )( 
            IApcGlobal __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStorage )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [defaultvalue][in] */ VARIANT_BOOL inMemory,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStorageInMemory )( 
            IApcGlobal __RPC_FAR * This,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStorageInMemory )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ VARIANT byteArray,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppIApcStorage);
        
        /* [helpcontext][helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WrapStorage )( 
            IApcGlobal __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pSource,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppDest);
        
        END_INTERFACE
    } IApcGlobalVtbl;

    interface IApcGlobal
    {
        CONST_VTBL struct IApcGlobalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcGlobal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcGlobal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcGlobal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcGlobal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcGlobal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcGlobal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcGlobal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcGlobal_CreateStorage(This,Name,AccessMode,ppStorage)	\
    (This)->lpVtbl -> CreateStorage(This,Name,AccessMode,ppStorage)

#define IApcGlobal_OpenStorage(This,Name,AccessMode,inMemory,ppStorage)	\
    (This)->lpVtbl -> OpenStorage(This,Name,AccessMode,inMemory,ppStorage)

#define IApcGlobal_CreateStorageInMemory(This,AccessMode,ppStorage)	\
    (This)->lpVtbl -> CreateStorageInMemory(This,AccessMode,ppStorage)

#define IApcGlobal_OpenStorageInMemory(This,byteArray,AccessMode,ppIApcStorage)	\
    (This)->lpVtbl -> OpenStorageInMemory(This,byteArray,AccessMode,ppIApcStorage)

#define IApcGlobal_WrapStorage(This,pSource,ppDest)	\
    (This)->lpVtbl -> WrapStorage(This,pSource,ppDest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcGlobal_CreateStorage_Proxy( 
    IApcGlobal __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcGlobal_CreateStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcGlobal_OpenStorage_Proxy( 
    IApcGlobal __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [defaultvalue][in] */ VARIANT_BOOL inMemory,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcGlobal_OpenStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcGlobal_CreateStorageInMemory_Proxy( 
    IApcGlobal __RPC_FAR * This,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcGlobal_CreateStorageInMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcGlobal_OpenStorageInMemory_Proxy( 
    IApcGlobal __RPC_FAR * This,
    /* [in] */ VARIANT byteArray,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppIApcStorage);


void __RPC_STUB IApcGlobal_OpenStorageInMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IApcGlobal_WrapStorage_Proxy( 
    IApcGlobal __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pSource,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppDest);


void __RPC_STUB IApcGlobal_WrapStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcGlobal_INTERFACE_DEFINED__ */


#ifndef __IApc_INTERFACE_DEFINED__
#define __IApc_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApc
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApc : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Projects( 
            /* [retval][out] */ IApcProjects __RPC_FAR *__RPC_FAR *ppProjects) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VBE( 
            /* [retval][out] */ /* external definition not present */ VBE __RPC_FAR *__RPC_FAR *ppVBE) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PropertiesWindow( 
            /* [retval][out] */ IApcPropertiesWindow __RPC_FAR *__RPC_FAR *ppPropertiesWindow) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *pPicture) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppPicture) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MiniBitmaps( 
            /* [retval][out] */ IApcMiniBitmaps __RPC_FAR *__RPC_FAR *ppMiniBitmaps) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_TypeLibraryGuid( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTypeLibGuid) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TypeLibraryChecksum( 
            /* [retval][out] */ long __RPC_FAR *pChecksum) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TypeLibraryChecksum( 
            /* [in] */ long Checksum) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RunningInVB( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRunningInVB) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Paused( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPaused) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Running( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRunning) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExecutingProject( 
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StepMode( 
            /* [in] */ APCSTEPMODE NewStepMode) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StepMode( 
            /* [retval][out] */ APCSTEPMODE __RPC_FAR *pStepMode) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_hWnd( 
            /* [in] */ long NewWindow) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long __RPC_FAR *phWnd) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propput] */ HRESULT STDMETHODCALLTYPE put_ControlLibraryGuid( 
            /* [in] */ BSTR Guid) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_ControlLibraryGuid( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrGuid) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LicenseKey( 
            /* [in] */ BSTR bstrKey) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LicenseKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HostName( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RegistryKey( 
            /* [in] */ BSTR bstrKey) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RegistryKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FileFilter( 
            /* [in] */ BSTR bstrFilter) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FileFilter( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilter) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Locale( 
            /* [in] */ long lcid) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Locale( 
            /* [retval][out] */ long __RPC_FAR *plcid) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ /* external definition not present */ OLE_COLOR BackColor) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ApplicationObject( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppApplicationObject) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ApplicationObject( 
            /* [in] */ IDispatch __RPC_FAR *pApplicationObject) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_MessageLoopSite( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSite) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propput] */ HRESULT STDMETHODCALLTYPE put_MessageLoopSite( 
            /* [in] */ IUnknown __RPC_FAR *pSite) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VBAVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_APCVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Debug( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbDebug) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Recorder( 
            /* [retval][out] */ IApcRecorder __RPC_FAR *__RPC_FAR *ppRecorder) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ide( 
            /* [retval][out] */ IApcIde __RPC_FAR *__RPC_FAR *ppIde) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EnableDigitalSignatures( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EnableDigitalSignatures( 
            /* [in] */ VARIANT_BOOL Enable) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SecurityLevel( 
            /* [retval][out] */ APCSECURITYLEVEL __RPC_FAR *pSecurityLevel) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SecurityLevel( 
            /* [in] */ APCSECURITYLEVEL NewSecurityLevel) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SupportVbaDesigners( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSupported) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SupportVbaDesigners( 
            /* [in] */ VARIANT_BOOL Supported) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExecutingHostClassInstance( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HelpStyle( 
            /* [retval][out] */ APCHELPSTYLE __RPC_FAR *pStyle) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HelpStyle( 
            /* [in] */ APCHELPSTYLE Style) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MoreInfoHelpFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHelpFile) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MoreInfoHelpFile( 
            /* [in] */ BSTR bstrHelpFile) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MoreInfoContextID( 
            /* [retval][out] */ long __RPC_FAR *pContextID) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MoreInfoContextID( 
            /* [in] */ long ContextID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Format( 
            /* [in] */ VARIANT Expression,
            /* [optional][in] */ BSTR Format,
            /* [defaultvalue][in] */ short firstdayofweek,
            /* [defaultvalue][in] */ short firstweekofyear,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFormattedText) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BeginModalDialog( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE EndModalDialog( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Break( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE End( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFinished) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RegisterExtenderClass( 
            BSTR ClassName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ShowError( 
            /* [defaultvalue][in] */ long Error) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateScopes( 
            /* [defaultvalue][in] */ VARIANT_BOOL AutoFill,
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AdviseApcEvents( 
            /* [in] */ IApcEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UnadviseApcEvents( 
            /* [in] */ long Cookie) = 0;
        
        virtual /* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE AdviseLegacyEvents( 
            /* [in] */ IApcLegacyEvents __RPC_FAR *LegacyEvents,
            /* [retval][out] */ long __RPC_FAR *pCookie) = 0;
        
        virtual /* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE UnadviseLegacyEvents( 
            /* [in] */ long Cookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ShowSecurityLevelDialog( 
            /* [retval][out] */ APCSECURITYLEVEL __RPC_FAR *SecurityLevel) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SupportDesigner( 
            /* [in] */ BSTR ClsidDesigner,
            /* [in] */ VARIANT_BOOL Supported) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CanTerminate( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *CanTerminate) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PreTerminate( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddMTProjectType( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR RegistryPath,
            /* [in] */ BSTR HostObjectName,
            /* [in] */ BSTR HostApplicationName,
            /* [defaultvalue][in] */ long MajorVersion,
            /* [defaultvalue][in] */ long MinorVersion,
            /* [defaultvalue][in] */ VARIANT_BOOL AllowCommandLineExecution) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_ApplicationObject( 
            /* [in] */ IDispatch __RPC_FAR *pApplicationObject) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ContinueOnError( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ContinueOnError( 
            /* [in] */ VARIANT_BOOL Continue) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedLibraryPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPathName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExtendedLibraryPath( 
            /* [in] */ BSTR PathName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApc __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApc __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApc __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Projects )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IApcProjects __RPC_FAR *__RPC_FAR *ppProjects);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VBE )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ VBE __RPC_FAR *__RPC_FAR *ppVBE);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PropertiesWindow )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IApcPropertiesWindow __RPC_FAR *__RPC_FAR *ppPropertiesWindow);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Picture )( 
            IApc __RPC_FAR * This,
            /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *pPicture);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Picture )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppPicture);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MiniBitmaps )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IApcMiniBitmaps __RPC_FAR *__RPC_FAR *ppMiniBitmaps);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApc __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TypeLibraryGuid )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTypeLibGuid);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TypeLibraryChecksum )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pChecksum);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TypeLibraryChecksum )( 
            IApc __RPC_FAR * This,
            /* [in] */ long Checksum);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RunningInVB )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRunningInVB);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Paused )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPaused);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Running )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRunning);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExecutingProject )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StepMode )( 
            IApc __RPC_FAR * This,
            /* [in] */ APCSTEPMODE NewStepMode);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StepMode )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ APCSTEPMODE __RPC_FAR *pStepMode);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hWnd )( 
            IApc __RPC_FAR * This,
            /* [in] */ long NewWindow);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hWnd )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *phWnd);
        
        /* [helpcontext][helpstring][hidden][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ControlLibraryGuid )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR Guid);
        
        /* [helpcontext][helpstring][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ControlLibraryGuid )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrGuid);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LicenseKey )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR bstrKey);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LicenseKey )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostName )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostName )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RegistryKey )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR bstrKey);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RegistryKey )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileFilter )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR bstrFilter);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileFilter )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilter);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locale )( 
            IApc __RPC_FAR * This,
            /* [in] */ long lcid);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locale )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plcid);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IApc __RPC_FAR * This,
            /* [in] */ /* external definition not present */ OLE_COLOR BackColor);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ApplicationObject )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppApplicationObject);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ApplicationObject )( 
            IApc __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pApplicationObject);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageLoopSite )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSite);
        
        /* [helpcontext][helpstring][restricted][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MessageLoopSite )( 
            IApc __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pSite);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VBAVersion )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_APCVersion )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Debug )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbDebug);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Recorder )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IApcRecorder __RPC_FAR *__RPC_FAR *ppRecorder);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ide )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IApcIde __RPC_FAR *__RPC_FAR *ppIde);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableDigitalSignatures )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableDigitalSignatures )( 
            IApc __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Enable);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecurityLevel )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ APCSECURITYLEVEL __RPC_FAR *pSecurityLevel);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SecurityLevel )( 
            IApc __RPC_FAR * This,
            /* [in] */ APCSECURITYLEVEL NewSecurityLevel);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SupportVbaDesigners )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSupported);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SupportVbaDesigners )( 
            IApc __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Supported);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExecutingHostClassInstance )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpStyle )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ APCHELPSTYLE __RPC_FAR *pStyle);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpStyle )( 
            IApc __RPC_FAR * This,
            /* [in] */ APCHELPSTYLE Style);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MoreInfoHelpFile )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHelpFile);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MoreInfoHelpFile )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR bstrHelpFile);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MoreInfoContextID )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pContextID);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MoreInfoContextID )( 
            IApc __RPC_FAR * This,
            /* [in] */ long ContextID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Format )( 
            IApc __RPC_FAR * This,
            /* [in] */ VARIANT Expression,
            /* [optional][in] */ BSTR Format,
            /* [defaultvalue][in] */ short firstdayofweek,
            /* [defaultvalue][in] */ short firstweekofyear,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFormattedText);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginModalDialog )( 
            IApc __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndModalDialog )( 
            IApc __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Break )( 
            IApc __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *End )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFinished);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterExtenderClass )( 
            IApc __RPC_FAR * This,
            BSTR ClassName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowError )( 
            IApc __RPC_FAR * This,
            /* [defaultvalue][in] */ long Error);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateScopes )( 
            IApc __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL AutoFill,
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseApcEvents )( 
            IApc __RPC_FAR * This,
            /* [in] */ IApcEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnadviseApcEvents )( 
            IApc __RPC_FAR * This,
            /* [in] */ long Cookie);
        
        /* [helpcontext][helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseLegacyEvents )( 
            IApc __RPC_FAR * This,
            /* [in] */ IApcLegacyEvents __RPC_FAR *LegacyEvents,
            /* [retval][out] */ long __RPC_FAR *pCookie);
        
        /* [helpcontext][helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnadviseLegacyEvents )( 
            IApc __RPC_FAR * This,
            /* [in] */ long Cookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowSecurityLevelDialog )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ APCSECURITYLEVEL __RPC_FAR *SecurityLevel);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SupportDesigner )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR ClsidDesigner,
            /* [in] */ VARIANT_BOOL Supported);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanTerminate )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *CanTerminate);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PreTerminate )( 
            IApc __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMTProjectType )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR RegistryPath,
            /* [in] */ BSTR HostObjectName,
            /* [in] */ BSTR HostApplicationName,
            /* [defaultvalue][in] */ long MajorVersion,
            /* [defaultvalue][in] */ long MinorVersion,
            /* [defaultvalue][in] */ VARIANT_BOOL AllowCommandLineExecution);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_ApplicationObject )( 
            IApc __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pApplicationObject);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContinueOnError )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbContinue);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContinueOnError )( 
            IApc __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Continue);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedLibraryPath )( 
            IApc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPathName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ExtendedLibraryPath )( 
            IApc __RPC_FAR * This,
            /* [in] */ BSTR PathName);
        
        END_INTERFACE
    } IApcVtbl;

    interface IApc
    {
        CONST_VTBL struct IApcVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApc_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApc_get_Projects(This,ppProjects)	\
    (This)->lpVtbl -> get_Projects(This,ppProjects)

#define IApc_get_VBE(This,ppVBE)	\
    (This)->lpVtbl -> get_VBE(This,ppVBE)

#define IApc_get_PropertiesWindow(This,ppPropertiesWindow)	\
    (This)->lpVtbl -> get_PropertiesWindow(This,ppPropertiesWindow)

#define IApc_put_Picture(This,pPicture)	\
    (This)->lpVtbl -> put_Picture(This,pPicture)

#define IApc_get_Picture(This,ppPicture)	\
    (This)->lpVtbl -> get_Picture(This,ppPicture)

#define IApc_get_MiniBitmaps(This,ppMiniBitmaps)	\
    (This)->lpVtbl -> get_MiniBitmaps(This,ppMiniBitmaps)

#define IApc_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApc_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApc_get_TypeLibraryGuid(This,pbstrTypeLibGuid)	\
    (This)->lpVtbl -> get_TypeLibraryGuid(This,pbstrTypeLibGuid)

#define IApc_get_TypeLibraryChecksum(This,pChecksum)	\
    (This)->lpVtbl -> get_TypeLibraryChecksum(This,pChecksum)

#define IApc_put_TypeLibraryChecksum(This,Checksum)	\
    (This)->lpVtbl -> put_TypeLibraryChecksum(This,Checksum)

#define IApc_get_RunningInVB(This,pbRunningInVB)	\
    (This)->lpVtbl -> get_RunningInVB(This,pbRunningInVB)

#define IApc_get_Paused(This,pbPaused)	\
    (This)->lpVtbl -> get_Paused(This,pbPaused)

#define IApc_get_Running(This,pbRunning)	\
    (This)->lpVtbl -> get_Running(This,pbRunning)

#define IApc_get_ExecutingProject(This,ppProject)	\
    (This)->lpVtbl -> get_ExecutingProject(This,ppProject)

#define IApc_put_StepMode(This,NewStepMode)	\
    (This)->lpVtbl -> put_StepMode(This,NewStepMode)

#define IApc_get_StepMode(This,pStepMode)	\
    (This)->lpVtbl -> get_StepMode(This,pStepMode)

#define IApc_put_hWnd(This,NewWindow)	\
    (This)->lpVtbl -> put_hWnd(This,NewWindow)

#define IApc_get_hWnd(This,phWnd)	\
    (This)->lpVtbl -> get_hWnd(This,phWnd)

#define IApc_put_ControlLibraryGuid(This,Guid)	\
    (This)->lpVtbl -> put_ControlLibraryGuid(This,Guid)

#define IApc_get_ControlLibraryGuid(This,pbstrGuid)	\
    (This)->lpVtbl -> get_ControlLibraryGuid(This,pbstrGuid)

#define IApc_put_LicenseKey(This,bstrKey)	\
    (This)->lpVtbl -> put_LicenseKey(This,bstrKey)

#define IApc_get_LicenseKey(This,pbstrKey)	\
    (This)->lpVtbl -> get_LicenseKey(This,pbstrKey)

#define IApc_put_HostName(This,bstrName)	\
    (This)->lpVtbl -> put_HostName(This,bstrName)

#define IApc_get_HostName(This,pbstrName)	\
    (This)->lpVtbl -> get_HostName(This,pbstrName)

#define IApc_put_RegistryKey(This,bstrKey)	\
    (This)->lpVtbl -> put_RegistryKey(This,bstrKey)

#define IApc_get_RegistryKey(This,pbstrKey)	\
    (This)->lpVtbl -> get_RegistryKey(This,pbstrKey)

#define IApc_put_FileFilter(This,bstrFilter)	\
    (This)->lpVtbl -> put_FileFilter(This,bstrFilter)

#define IApc_get_FileFilter(This,pbstrFilter)	\
    (This)->lpVtbl -> get_FileFilter(This,pbstrFilter)

#define IApc_put_Locale(This,lcid)	\
    (This)->lpVtbl -> put_Locale(This,lcid)

#define IApc_get_Locale(This,plcid)	\
    (This)->lpVtbl -> get_Locale(This,plcid)

#define IApc_get_BackColor(This,pBackColor)	\
    (This)->lpVtbl -> get_BackColor(This,pBackColor)

#define IApc_put_BackColor(This,BackColor)	\
    (This)->lpVtbl -> put_BackColor(This,BackColor)

#define IApc_get_ApplicationObject(This,ppApplicationObject)	\
    (This)->lpVtbl -> get_ApplicationObject(This,ppApplicationObject)

#define IApc_put_ApplicationObject(This,pApplicationObject)	\
    (This)->lpVtbl -> put_ApplicationObject(This,pApplicationObject)

#define IApc_get_MessageLoopSite(This,ppSite)	\
    (This)->lpVtbl -> get_MessageLoopSite(This,ppSite)

#define IApc_put_MessageLoopSite(This,pSite)	\
    (This)->lpVtbl -> put_MessageLoopSite(This,pSite)

#define IApc_get_VBAVersion(This,pbstrVersion)	\
    (This)->lpVtbl -> get_VBAVersion(This,pbstrVersion)

#define IApc_get_APCVersion(This,pbstrVersion)	\
    (This)->lpVtbl -> get_APCVersion(This,pbstrVersion)

#define IApc_get_Debug(This,pbDebug)	\
    (This)->lpVtbl -> get_Debug(This,pbDebug)

#define IApc_get_Recorder(This,ppRecorder)	\
    (This)->lpVtbl -> get_Recorder(This,ppRecorder)

#define IApc_get_Ide(This,ppIde)	\
    (This)->lpVtbl -> get_Ide(This,ppIde)

#define IApc_get_EnableDigitalSignatures(This,pbEnabled)	\
    (This)->lpVtbl -> get_EnableDigitalSignatures(This,pbEnabled)

#define IApc_put_EnableDigitalSignatures(This,Enable)	\
    (This)->lpVtbl -> put_EnableDigitalSignatures(This,Enable)

#define IApc_get_SecurityLevel(This,pSecurityLevel)	\
    (This)->lpVtbl -> get_SecurityLevel(This,pSecurityLevel)

#define IApc_put_SecurityLevel(This,NewSecurityLevel)	\
    (This)->lpVtbl -> put_SecurityLevel(This,NewSecurityLevel)

#define IApc_get_SupportVbaDesigners(This,pbSupported)	\
    (This)->lpVtbl -> get_SupportVbaDesigners(This,pbSupported)

#define IApc_put_SupportVbaDesigners(This,Supported)	\
    (This)->lpVtbl -> put_SupportVbaDesigners(This,Supported)

#define IApc_get_ExecutingHostClassInstance(This,ppInstance)	\
    (This)->lpVtbl -> get_ExecutingHostClassInstance(This,ppInstance)

#define IApc_get_HelpStyle(This,pStyle)	\
    (This)->lpVtbl -> get_HelpStyle(This,pStyle)

#define IApc_put_HelpStyle(This,Style)	\
    (This)->lpVtbl -> put_HelpStyle(This,Style)

#define IApc_get_MoreInfoHelpFile(This,pbstrHelpFile)	\
    (This)->lpVtbl -> get_MoreInfoHelpFile(This,pbstrHelpFile)

#define IApc_put_MoreInfoHelpFile(This,bstrHelpFile)	\
    (This)->lpVtbl -> put_MoreInfoHelpFile(This,bstrHelpFile)

#define IApc_get_MoreInfoContextID(This,pContextID)	\
    (This)->lpVtbl -> get_MoreInfoContextID(This,pContextID)

#define IApc_put_MoreInfoContextID(This,ContextID)	\
    (This)->lpVtbl -> put_MoreInfoContextID(This,ContextID)

#define IApc_Format(This,Expression,Format,firstdayofweek,firstweekofyear,pbstrFormattedText)	\
    (This)->lpVtbl -> Format(This,Expression,Format,firstdayofweek,firstweekofyear,pbstrFormattedText)

#define IApc_BeginModalDialog(This)	\
    (This)->lpVtbl -> BeginModalDialog(This)

#define IApc_EndModalDialog(This)	\
    (This)->lpVtbl -> EndModalDialog(This)

#define IApc_Break(This)	\
    (This)->lpVtbl -> Break(This)

#define IApc_End(This,pbFinished)	\
    (This)->lpVtbl -> End(This,pbFinished)

#define IApc_RegisterExtenderClass(This,ClassName)	\
    (This)->lpVtbl -> RegisterExtenderClass(This,ClassName)

#define IApc_ShowError(This,Error)	\
    (This)->lpVtbl -> ShowError(This,Error)

#define IApc_CreateScopes(This,AutoFill,ppScopes)	\
    (This)->lpVtbl -> CreateScopes(This,AutoFill,ppScopes)

#define IApc_AdviseApcEvents(This,EventSink,pCookie)	\
    (This)->lpVtbl -> AdviseApcEvents(This,EventSink,pCookie)

#define IApc_UnadviseApcEvents(This,Cookie)	\
    (This)->lpVtbl -> UnadviseApcEvents(This,Cookie)

#define IApc_AdviseLegacyEvents(This,LegacyEvents,pCookie)	\
    (This)->lpVtbl -> AdviseLegacyEvents(This,LegacyEvents,pCookie)

#define IApc_UnadviseLegacyEvents(This,Cookie)	\
    (This)->lpVtbl -> UnadviseLegacyEvents(This,Cookie)

#define IApc_ShowSecurityLevelDialog(This,SecurityLevel)	\
    (This)->lpVtbl -> ShowSecurityLevelDialog(This,SecurityLevel)

#define IApc_SupportDesigner(This,ClsidDesigner,Supported)	\
    (This)->lpVtbl -> SupportDesigner(This,ClsidDesigner,Supported)

#define IApc_CanTerminate(This,CanTerminate)	\
    (This)->lpVtbl -> CanTerminate(This,CanTerminate)

#define IApc_PreTerminate(This)	\
    (This)->lpVtbl -> PreTerminate(This)

#define IApc_AddMTProjectType(This,Name,RegistryPath,HostObjectName,HostApplicationName,MajorVersion,MinorVersion,AllowCommandLineExecution)	\
    (This)->lpVtbl -> AddMTProjectType(This,Name,RegistryPath,HostObjectName,HostApplicationName,MajorVersion,MinorVersion,AllowCommandLineExecution)

#define IApc_putref_ApplicationObject(This,pApplicationObject)	\
    (This)->lpVtbl -> putref_ApplicationObject(This,pApplicationObject)

#define IApc_get_ContinueOnError(This,pbContinue)	\
    (This)->lpVtbl -> get_ContinueOnError(This,pbContinue)

#define IApc_put_ContinueOnError(This,Continue)	\
    (This)->lpVtbl -> put_ContinueOnError(This,Continue)

#define IApc_get_ExtendedLibraryPath(This,pbstrPathName)	\
    (This)->lpVtbl -> get_ExtendedLibraryPath(This,pbstrPathName)

#define IApc_put_ExtendedLibraryPath(This,PathName)	\
    (This)->lpVtbl -> put_ExtendedLibraryPath(This,PathName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Projects_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IApcProjects __RPC_FAR *__RPC_FAR *ppProjects);


void __RPC_STUB IApc_get_Projects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_VBE_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ VBE __RPC_FAR *__RPC_FAR *ppVBE);


void __RPC_STUB IApc_get_VBE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_PropertiesWindow_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IApcPropertiesWindow __RPC_FAR *__RPC_FAR *ppPropertiesWindow);


void __RPC_STUB IApc_get_PropertiesWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_Picture_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *pPicture);


void __RPC_STUB IApc_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Picture_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppPicture);


void __RPC_STUB IApc_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_MiniBitmaps_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IApcMiniBitmaps __RPC_FAR *__RPC_FAR *ppMiniBitmaps);


void __RPC_STUB IApc_get_MiniBitmaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_Tag_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApc_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Tag_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApc_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_TypeLibraryGuid_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTypeLibGuid);


void __RPC_STUB IApc_get_TypeLibraryGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_TypeLibraryChecksum_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pChecksum);


void __RPC_STUB IApc_get_TypeLibraryChecksum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_TypeLibraryChecksum_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ long Checksum);


void __RPC_STUB IApc_put_TypeLibraryChecksum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_RunningInVB_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRunningInVB);


void __RPC_STUB IApc_get_RunningInVB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Paused_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPaused);


void __RPC_STUB IApc_get_Paused_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Running_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRunning);


void __RPC_STUB IApc_get_Running_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_ExecutingProject_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);


void __RPC_STUB IApc_get_ExecutingProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_StepMode_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ APCSTEPMODE NewStepMode);


void __RPC_STUB IApc_put_StepMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_StepMode_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ APCSTEPMODE __RPC_FAR *pStepMode);


void __RPC_STUB IApc_get_StepMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_hWnd_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ long NewWindow);


void __RPC_STUB IApc_put_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_hWnd_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *phWnd);


void __RPC_STUB IApc_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_ControlLibraryGuid_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR Guid);


void __RPC_STUB IApc_put_ControlLibraryGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_ControlLibraryGuid_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrGuid);


void __RPC_STUB IApc_get_ControlLibraryGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_LicenseKey_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR bstrKey);


void __RPC_STUB IApc_put_LicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_LicenseKey_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);


void __RPC_STUB IApc_get_LicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_HostName_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IApc_put_HostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_HostName_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApc_get_HostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_RegistryKey_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR bstrKey);


void __RPC_STUB IApc_put_RegistryKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_RegistryKey_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);


void __RPC_STUB IApc_get_RegistryKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_FileFilter_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR bstrFilter);


void __RPC_STUB IApc_put_FileFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_FileFilter_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFilter);


void __RPC_STUB IApc_get_FileFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_Locale_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ long lcid);


void __RPC_STUB IApc_put_Locale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Locale_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plcid);


void __RPC_STUB IApc_get_Locale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_BackColor_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor);


void __RPC_STUB IApc_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_BackColor_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ /* external definition not present */ OLE_COLOR BackColor);


void __RPC_STUB IApc_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_ApplicationObject_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppApplicationObject);


void __RPC_STUB IApc_get_ApplicationObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_ApplicationObject_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pApplicationObject);


void __RPC_STUB IApc_put_ApplicationObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_MessageLoopSite_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSite);


void __RPC_STUB IApc_get_MessageLoopSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_MessageLoopSite_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pSite);


void __RPC_STUB IApc_put_MessageLoopSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_VBAVersion_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion);


void __RPC_STUB IApc_get_VBAVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_APCVersion_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrVersion);


void __RPC_STUB IApc_get_APCVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Debug_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbDebug);


void __RPC_STUB IApc_get_Debug_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Recorder_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IApcRecorder __RPC_FAR *__RPC_FAR *ppRecorder);


void __RPC_STUB IApc_get_Recorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_Ide_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IApcIde __RPC_FAR *__RPC_FAR *ppIde);


void __RPC_STUB IApc_get_Ide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_EnableDigitalSignatures_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEnabled);


void __RPC_STUB IApc_get_EnableDigitalSignatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_EnableDigitalSignatures_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Enable);


void __RPC_STUB IApc_put_EnableDigitalSignatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_SecurityLevel_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ APCSECURITYLEVEL __RPC_FAR *pSecurityLevel);


void __RPC_STUB IApc_get_SecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_SecurityLevel_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ APCSECURITYLEVEL NewSecurityLevel);


void __RPC_STUB IApc_put_SecurityLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_SupportVbaDesigners_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSupported);


void __RPC_STUB IApc_get_SupportVbaDesigners_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_SupportVbaDesigners_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Supported);


void __RPC_STUB IApc_put_SupportVbaDesigners_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_ExecutingHostClassInstance_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);


void __RPC_STUB IApc_get_ExecutingHostClassInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_HelpStyle_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ APCHELPSTYLE __RPC_FAR *pStyle);


void __RPC_STUB IApc_get_HelpStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_HelpStyle_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ APCHELPSTYLE Style);


void __RPC_STUB IApc_put_HelpStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_MoreInfoHelpFile_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrHelpFile);


void __RPC_STUB IApc_get_MoreInfoHelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_MoreInfoHelpFile_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR bstrHelpFile);


void __RPC_STUB IApc_put_MoreInfoHelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_MoreInfoContextID_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pContextID);


void __RPC_STUB IApc_get_MoreInfoContextID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_MoreInfoContextID_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ long ContextID);


void __RPC_STUB IApc_put_MoreInfoContextID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_Format_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ VARIANT Expression,
    /* [optional][in] */ BSTR Format,
    /* [defaultvalue][in] */ short firstdayofweek,
    /* [defaultvalue][in] */ short firstweekofyear,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFormattedText);


void __RPC_STUB IApc_Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_BeginModalDialog_Proxy( 
    IApc __RPC_FAR * This);


void __RPC_STUB IApc_BeginModalDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_EndModalDialog_Proxy( 
    IApc __RPC_FAR * This);


void __RPC_STUB IApc_EndModalDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_Break_Proxy( 
    IApc __RPC_FAR * This);


void __RPC_STUB IApc_Break_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_End_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFinished);


void __RPC_STUB IApc_End_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_RegisterExtenderClass_Proxy( 
    IApc __RPC_FAR * This,
    BSTR ClassName);


void __RPC_STUB IApc_RegisterExtenderClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_ShowError_Proxy( 
    IApc __RPC_FAR * This,
    /* [defaultvalue][in] */ long Error);


void __RPC_STUB IApc_ShowError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_CreateScopes_Proxy( 
    IApc __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL AutoFill,
    /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes);


void __RPC_STUB IApc_CreateScopes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_AdviseApcEvents_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ IApcEvents __RPC_FAR *EventSink,
    /* [retval][out] */ long __RPC_FAR *pCookie);


void __RPC_STUB IApc_AdviseApcEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_UnadviseApcEvents_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ long Cookie);


void __RPC_STUB IApc_UnadviseApcEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IApc_AdviseLegacyEvents_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ IApcLegacyEvents __RPC_FAR *LegacyEvents,
    /* [retval][out] */ long __RPC_FAR *pCookie);


void __RPC_STUB IApc_AdviseLegacyEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IApc_UnadviseLegacyEvents_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ long Cookie);


void __RPC_STUB IApc_UnadviseLegacyEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_ShowSecurityLevelDialog_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ APCSECURITYLEVEL __RPC_FAR *SecurityLevel);


void __RPC_STUB IApc_ShowSecurityLevelDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_SupportDesigner_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR ClsidDesigner,
    /* [in] */ VARIANT_BOOL Supported);


void __RPC_STUB IApc_SupportDesigner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_CanTerminate_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *CanTerminate);


void __RPC_STUB IApc_CanTerminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_PreTerminate_Proxy( 
    IApc __RPC_FAR * This);


void __RPC_STUB IApc_PreTerminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApc_AddMTProjectType_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR RegistryPath,
    /* [in] */ BSTR HostObjectName,
    /* [in] */ BSTR HostApplicationName,
    /* [defaultvalue][in] */ long MajorVersion,
    /* [defaultvalue][in] */ long MinorVersion,
    /* [defaultvalue][in] */ VARIANT_BOOL AllowCommandLineExecution);


void __RPC_STUB IApc_AddMTProjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE IApc_putref_ApplicationObject_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pApplicationObject);


void __RPC_STUB IApc_putref_ApplicationObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_ContinueOnError_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbContinue);


void __RPC_STUB IApc_get_ContinueOnError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_ContinueOnError_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Continue);


void __RPC_STUB IApc_put_ContinueOnError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApc_get_ExtendedLibraryPath_Proxy( 
    IApc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrPathName);


void __RPC_STUB IApc_get_ExtendedLibraryPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApc_put_ExtendedLibraryPath_Proxy( 
    IApc __RPC_FAR * This,
    /* [in] */ BSTR PathName);


void __RPC_STUB IApc_put_ExtendedLibraryPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApc_INTERFACE_DEFINED__ */


#ifndef __IApcEvents_INTERFACE_DEFINED__
#define __IApcEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][helpcontext][helpstring][uuid] */ 



EXTERN_C const IID IID_IApcEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE BeforeRun( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AfterRun( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE BeforePause( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AfterPause( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE BeforeModalDialog( 
            /* [in] */ IApcProject __RPC_FAR *Project) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AfterModalDialog( 
            /* [in] */ IApcProject __RPC_FAR *Project) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Activate( 
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *Activate) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE NameChange( 
            /* [in] */ IApcProject __RPC_FAR *Project,
            /* [in] */ BSTR OldName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenProject( 
            /* [in] */ BSTR ProjectFileName,
            IApcProject __RPC_FAR *ReferencingProject,
            /* [out][in] */ IApcProject __RPC_FAR *__RPC_FAR *Project) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowHelp( 
            /* [in] */ BSTR HelpFileName,
            /* [in] */ long Command,
            /* [in] */ long CommandData,
            /* [in] */ VARIANT_BOOL IsWinHelp,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *pbShowHelp) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FindFile( 
            /* [in] */ BSTR FileName,
            /* [out][in] */ BSTR __RPC_FAR *FullPath) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateMacro( 
            /* [in] */ BSTR ProcedureName,
            /* [in] */ IApcScope __RPC_FAR *CurrentScope,
            /* [in] */ BSTR Description,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *Created) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HostCheckReference( 
            /* [in] */ VARIANT_BOOL Saving,
            /* [in] */ BSTR LibraryGuid,
            /* [out][in] */ long __RPC_FAR *MajorVersion,
            /* [out][in] */ long __RPC_FAR *MinorVersion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeforeRun )( 
            IApcEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AfterRun )( 
            IApcEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeforePause )( 
            IApcEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AfterPause )( 
            IApcEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeforeModalDialog )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ IApcProject __RPC_FAR *Project);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AfterModalDialog )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ IApcProject __RPC_FAR *Project);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IApcEvents __RPC_FAR * This,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *Activate);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NameChange )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ IApcProject __RPC_FAR *Project,
            /* [in] */ BSTR OldName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenProject )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ BSTR ProjectFileName,
            IApcProject __RPC_FAR *ReferencingProject,
            /* [out][in] */ IApcProject __RPC_FAR *__RPC_FAR *Project);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowHelp )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ BSTR HelpFileName,
            /* [in] */ long Command,
            /* [in] */ long CommandData,
            /* [in] */ VARIANT_BOOL IsWinHelp,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *pbShowHelp);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFile )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ BSTR FileName,
            /* [out][in] */ BSTR __RPC_FAR *FullPath);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateMacro )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ IApcScope __RPC_FAR *CurrentScope,
            /* [in] */ BSTR Description,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *Created);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HostCheckReference )( 
            IApcEvents __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Saving,
            /* [in] */ BSTR LibraryGuid,
            /* [out][in] */ long __RPC_FAR *MajorVersion,
            /* [out][in] */ long __RPC_FAR *MinorVersion);
        
        END_INTERFACE
    } IApcEventsVtbl;

    interface IApcEvents
    {
        CONST_VTBL struct IApcEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcEvents_BeforeRun(This)	\
    (This)->lpVtbl -> BeforeRun(This)

#define IApcEvents_AfterRun(This)	\
    (This)->lpVtbl -> AfterRun(This)

#define IApcEvents_BeforePause(This)	\
    (This)->lpVtbl -> BeforePause(This)

#define IApcEvents_AfterPause(This)	\
    (This)->lpVtbl -> AfterPause(This)

#define IApcEvents_BeforeModalDialog(This,Project)	\
    (This)->lpVtbl -> BeforeModalDialog(This,Project)

#define IApcEvents_AfterModalDialog(This,Project)	\
    (This)->lpVtbl -> AfterModalDialog(This,Project)

#define IApcEvents_Activate(This,Activate)	\
    (This)->lpVtbl -> Activate(This,Activate)

#define IApcEvents_NameChange(This,Project,OldName)	\
    (This)->lpVtbl -> NameChange(This,Project,OldName)

#define IApcEvents_OpenProject(This,ProjectFileName,ReferencingProject,Project)	\
    (This)->lpVtbl -> OpenProject(This,ProjectFileName,ReferencingProject,Project)

#define IApcEvents_ShowHelp(This,HelpFileName,Command,CommandData,IsWinHelp,pbShowHelp)	\
    (This)->lpVtbl -> ShowHelp(This,HelpFileName,Command,CommandData,IsWinHelp,pbShowHelp)

#define IApcEvents_FindFile(This,FileName,FullPath)	\
    (This)->lpVtbl -> FindFile(This,FileName,FullPath)

#define IApcEvents_CreateMacro(This,ProcedureName,CurrentScope,Description,Created)	\
    (This)->lpVtbl -> CreateMacro(This,ProcedureName,CurrentScope,Description,Created)

#define IApcEvents_HostCheckReference(This,Saving,LibraryGuid,MajorVersion,MinorVersion)	\
    (This)->lpVtbl -> HostCheckReference(This,Saving,LibraryGuid,MajorVersion,MinorVersion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_BeforeRun_Proxy( 
    IApcEvents __RPC_FAR * This);


void __RPC_STUB IApcEvents_BeforeRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_AfterRun_Proxy( 
    IApcEvents __RPC_FAR * This);


void __RPC_STUB IApcEvents_AfterRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_BeforePause_Proxy( 
    IApcEvents __RPC_FAR * This);


void __RPC_STUB IApcEvents_BeforePause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_AfterPause_Proxy( 
    IApcEvents __RPC_FAR * This);


void __RPC_STUB IApcEvents_AfterPause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_BeforeModalDialog_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ IApcProject __RPC_FAR *Project);


void __RPC_STUB IApcEvents_BeforeModalDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_AfterModalDialog_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ IApcProject __RPC_FAR *Project);


void __RPC_STUB IApcEvents_AfterModalDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_Activate_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *Activate);


void __RPC_STUB IApcEvents_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_NameChange_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ IApcProject __RPC_FAR *Project,
    /* [in] */ BSTR OldName);


void __RPC_STUB IApcEvents_NameChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_OpenProject_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ BSTR ProjectFileName,
    IApcProject __RPC_FAR *ReferencingProject,
    /* [out][in] */ IApcProject __RPC_FAR *__RPC_FAR *Project);


void __RPC_STUB IApcEvents_OpenProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_ShowHelp_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ BSTR HelpFileName,
    /* [in] */ long Command,
    /* [in] */ long CommandData,
    /* [in] */ VARIANT_BOOL IsWinHelp,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *pbShowHelp);


void __RPC_STUB IApcEvents_ShowHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_FindFile_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ BSTR FileName,
    /* [out][in] */ BSTR __RPC_FAR *FullPath);


void __RPC_STUB IApcEvents_FindFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_CreateMacro_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ BSTR ProcedureName,
    /* [in] */ IApcScope __RPC_FAR *CurrentScope,
    /* [in] */ BSTR Description,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *Created);


void __RPC_STUB IApcEvents_CreateMacro_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcEvents_HostCheckReference_Proxy( 
    IApcEvents __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Saving,
    /* [in] */ BSTR LibraryGuid,
    /* [out][in] */ long __RPC_FAR *MajorVersion,
    /* [out][in] */ long __RPC_FAR *MinorVersion);


void __RPC_STUB IApcEvents_HostCheckReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcEvents_INTERFACE_DEFINED__ */


#ifndef __IApcIde_INTERFACE_DEFINED__
#define __IApcIde_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcIde
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcIde;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcIde : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreventShow( 
            /* [in] */ VARIANT_BOOL PreventShow) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreventShow( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPreventShow) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AdviseIdeEvents( 
            /* [in] */ IApcIdeEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UnadviseIdeEvents( 
            /* [in] */ long Cookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcIdeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcIde __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcIde __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcIde __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IApcIde __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PreventShow )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL PreventShow);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreventShow )( 
            IApcIde __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPreventShow);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcIde __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcIde __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcIde __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseIdeEvents )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ IApcIdeEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnadviseIdeEvents )( 
            IApcIde __RPC_FAR * This,
            /* [in] */ long Cookie);
        
        END_INTERFACE
    } IApcIdeVtbl;

    interface IApcIde
    {
        CONST_VTBL struct IApcIdeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcIde_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcIde_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcIde_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcIde_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcIde_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcIde_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcIde_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcIde_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IApcIde_get_Visible(This,pbVisible)	\
    (This)->lpVtbl -> get_Visible(This,pbVisible)

#define IApcIde_put_PreventShow(This,PreventShow)	\
    (This)->lpVtbl -> put_PreventShow(This,PreventShow)

#define IApcIde_get_PreventShow(This,pbPreventShow)	\
    (This)->lpVtbl -> get_PreventShow(This,pbPreventShow)

#define IApcIde_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcIde_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcIde_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcIde_get_Parent(This,ppApc)	\
    (This)->lpVtbl -> get_Parent(This,ppApc)

#define IApcIde_AdviseIdeEvents(This,EventSink,pCookie)	\
    (This)->lpVtbl -> AdviseIdeEvents(This,EventSink,pCookie)

#define IApcIde_UnadviseIdeEvents(This,Cookie)	\
    (This)->lpVtbl -> UnadviseIdeEvents(This,Cookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcIde_put_Visible_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IApcIde_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcIde_get_Visible_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible);


void __RPC_STUB IApcIde_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcIde_put_PreventShow_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL PreventShow);


void __RPC_STUB IApcIde_put_PreventShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcIde_get_PreventShow_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbPreventShow);


void __RPC_STUB IApcIde_get_PreventShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcIde_put_Tag_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcIde_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcIde_get_Tag_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcIde_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcIde_get_Apc_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcIde_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcIde_get_Parent_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcIde_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcIde_AdviseIdeEvents_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [in] */ IApcIdeEvents __RPC_FAR *EventSink,
    /* [retval][out] */ long __RPC_FAR *pCookie);


void __RPC_STUB IApcIde_AdviseIdeEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcIde_UnadviseIdeEvents_Proxy( 
    IApcIde __RPC_FAR * This,
    /* [in] */ long Cookie);


void __RPC_STUB IApcIde_UnadviseIdeEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcIde_INTERFACE_DEFINED__ */


#ifndef __IApcIdeEvents_INTERFACE_DEFINED__
#define __IApcIdeEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcIdeEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][uuid] */ 



EXTERN_C const IID IID_IApcIdeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcIdeEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowHide( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToolbarReset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcIdeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcIdeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcIdeEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcIdeEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowHide )( 
            IApcIdeEvents __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ToolbarReset )( 
            IApcIdeEvents __RPC_FAR * This);
        
        END_INTERFACE
    } IApcIdeEventsVtbl;

    interface IApcIdeEvents
    {
        CONST_VTBL struct IApcIdeEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcIdeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcIdeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcIdeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcIdeEvents_ShowHide(This,Visible)	\
    (This)->lpVtbl -> ShowHide(This,Visible)

#define IApcIdeEvents_ToolbarReset(This)	\
    (This)->lpVtbl -> ToolbarReset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcIdeEvents_ShowHide_Proxy( 
    IApcIdeEvents __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IApcIdeEvents_ShowHide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcIdeEvents_ToolbarReset_Proxy( 
    IApcIdeEvents __RPC_FAR * This);


void __RPC_STUB IApcIdeEvents_ToolbarReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcIdeEvents_INTERFACE_DEFINED__ */


#ifndef __IApcPropertiesWindow_INTERFACE_DEFINED__
#define __IApcPropertiesWindow_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcPropertiesWindow
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcPropertiesWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcPropertiesWindow : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcPropertiesWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcPropertiesWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcPropertiesWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcPropertiesWindow __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        END_INTERFACE
    } IApcPropertiesWindowVtbl;

    interface IApcPropertiesWindow
    {
        CONST_VTBL struct IApcPropertiesWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcPropertiesWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcPropertiesWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcPropertiesWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcPropertiesWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcPropertiesWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcPropertiesWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcPropertiesWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcPropertiesWindow_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IApcPropertiesWindow_get_Visible(This,pbVisible)	\
    (This)->lpVtbl -> get_Visible(This,pbVisible)

#define IApcPropertiesWindow_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcPropertiesWindow_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcPropertiesWindow_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcPropertiesWindow_get_Parent(This,ppApc)	\
    (This)->lpVtbl -> get_Parent(This,ppApc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcPropertiesWindow_put_Visible_Proxy( 
    IApcPropertiesWindow __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IApcPropertiesWindow_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcPropertiesWindow_get_Visible_Proxy( 
    IApcPropertiesWindow __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible);


void __RPC_STUB IApcPropertiesWindow_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcPropertiesWindow_put_Tag_Proxy( 
    IApcPropertiesWindow __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcPropertiesWindow_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcPropertiesWindow_get_Tag_Proxy( 
    IApcPropertiesWindow __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcPropertiesWindow_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcPropertiesWindow_get_Apc_Proxy( 
    IApcPropertiesWindow __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcPropertiesWindow_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcPropertiesWindow_get_Parent_Proxy( 
    IApcPropertiesWindow __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcPropertiesWindow_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcPropertiesWindow_INTERFACE_DEFINED__ */


#ifndef __IApcProjects_INTERFACE_DEFINED__
#define __IApcProjects_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProjects
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcProjects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProjects : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VBProjects( 
            /* [retval][out] */ /* external definition not present */ _VBProjects __RPC_FAR *__RPC_FAR *ppVBProjects) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ APCPROJECTFLAG ProjectFlags,
            /* [optional][in] */ BSTR ProjectName,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ APCPROJECTFLAG Flags,
            /* [defaultvalue][in] */ IApcStorage __RPC_FAR *Storage,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *ProjectItemCollection,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProjects __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProjects __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcProjects __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcProjects __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcProjects __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcProjects __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcProjects __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcProjects __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VBProjects )( 
            IApcProjects __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ _VBProjects __RPC_FAR *__RPC_FAR *ppVBProjects);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ APCPROJECTFLAG ProjectFlags,
            /* [optional][in] */ BSTR ProjectName,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IApcProjects __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IApcProjects __RPC_FAR * This,
            /* [in] */ APCPROJECTFLAG Flags,
            /* [defaultvalue][in] */ IApcStorage __RPC_FAR *Storage,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *ProjectItemCollection,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);
        
        END_INTERFACE
    } IApcProjectsVtbl;

    interface IApcProjects
    {
        CONST_VTBL struct IApcProjectsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProjects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProjects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProjects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProjects_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcProjects_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcProjects_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcProjects_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcProjects_get_Parent(This,ppApc)	\
    (This)->lpVtbl -> get_Parent(This,ppApc)

#define IApcProjects_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcProjects_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcProjects_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcProjects_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcProjects_get_Item(This,Index,ppProject)	\
    (This)->lpVtbl -> get_Item(This,Index,ppProject)

#define IApcProjects_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcProjects_get_VBProjects(This,ppVBProjects)	\
    (This)->lpVtbl -> get_VBProjects(This,ppVBProjects)

#define IApcProjects_Add(This,ProjectFlags,ProjectName,ppProject)	\
    (This)->lpVtbl -> Add(This,ProjectFlags,ProjectName,ppProject)

#define IApcProjects_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IApcProjects_Open(This,Flags,Storage,ProjectItemCollection,ppProject)	\
    (This)->lpVtbl -> Open(This,Flags,Storage,ProjectItemCollection,ppProject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_Parent_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProjects_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_Count_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcProjects_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjects_put_Tag_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcProjects_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_Tag_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcProjects_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_Apc_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProjects_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_Item_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);


void __RPC_STUB IApcProjects_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_NewEnum_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcProjects_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjects_get_VBProjects_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ _VBProjects __RPC_FAR *__RPC_FAR *ppVBProjects);


void __RPC_STUB IApcProjects_get_VBProjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjects_Add_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [in] */ APCPROJECTFLAG ProjectFlags,
    /* [optional][in] */ BSTR ProjectName,
    /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);


void __RPC_STUB IApcProjects_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjects_Close_Proxy( 
    IApcProjects __RPC_FAR * This);


void __RPC_STUB IApcProjects_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjects_Open_Proxy( 
    IApcProjects __RPC_FAR * This,
    /* [in] */ APCPROJECTFLAG Flags,
    /* [defaultvalue][in] */ IApcStorage __RPC_FAR *Storage,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *ProjectItemCollection,
    /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);


void __RPC_STUB IApcProjects_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProjects_INTERFACE_DEFINED__ */


#ifndef __IApcProject_INTERFACE_DEFINED__
#define __IApcProject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProject
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcProject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProject : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDisplayName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR NewDisplayName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ReferenceName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ReferenceName( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [retval][out] */ APCPROJECTMODE __RPC_FAR *pMode) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ APCPROJECTMODE NewMode) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dirty( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbIsDirty) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dirty( 
            /* [in] */ VARIANT_BOOL IsDirty) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProjects __RPC_FAR *__RPC_FAR *ppProjects) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HostProtection( 
            /* [in] */ VARIANT_BOOL Protected) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HostProtection( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_ProtectionState( 
            /* [retval][out] */ APCPROJECTPROTECTION __RPC_FAR *pState) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UserProtection( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SystemProtection( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DelayProtection( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbDelayedProtection) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DelayProtection( 
            /* [in] */ VARIANT_BOOL DelayedProtection) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProjectItems( 
            /* [out][retval] */ IApcProjectItems __RPC_FAR *__RPC_FAR *ppProjectItems) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Locked( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbLocked) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VBProject( 
            /* [out][retval] */ /* external definition not present */ VBProject __RPC_FAR *__RPC_FAR *ppVBProject) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [out][retval] */ APCPROJECTFLAG __RPC_FAR *pFlags) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Storage( 
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_IStorage( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventsFrozen( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEventsFrozen) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ParseLineError( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrError) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Compiled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasDigitalSignature( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbHasSignature) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL ForceSave) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SaveAs( 
            /* [in] */ IApcStorage __RPC_FAR *Storage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SaveCopyAs( 
            /* [in] */ IApcStorage __RPC_FAR *Storage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SaveCompleted( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveSucceeded) = 0;
        
        virtual /* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ BSTR ModuleName,
            /* [in] */ BSTR Name,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
            /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Compile( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ExecuteLine( 
            /* [in] */ BSTR ExecuteText) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ParseLine( 
            /* [in] */ BSTR ParseText,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuccess) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveChanges) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AdviseProjectEvents( 
            /* [in] */ IApcProjectEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UnadviseProjectEvents( 
            /* [in] */ long Cookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateScopes( 
            /* [defaultvalue][in] */ VARIANT_BOOL AutoFill,
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ChangeUserProtection( 
            /* [in] */ VARIANT_BOOL Protected,
            /* [in] */ BSTR Password) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FormsSFILevel( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwLevel) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FormsSFILevel( 
            /* [in] */ DWORD dwLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcProject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ BSTR NewName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDisplayName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ BSTR NewDisplayName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferenceName )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReferenceName )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ BSTR NewName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Mode )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ APCPROJECTMODE __RPC_FAR *pMode);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Mode )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ APCPROJECTMODE NewMode);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dirty )( 
            IApcProject __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbIsDirty);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Dirty )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL IsDirty);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ IApcProjects __RPC_FAR *__RPC_FAR *ppProjects);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostProtection )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Protected);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostProtection )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProtectionState )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ APCPROJECTPROTECTION __RPC_FAR *pState);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserProtection )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SystemProtection )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DelayProtection )( 
            IApcProject __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbDelayedProtection);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DelayProtection )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL DelayedProtection);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectItems )( 
            IApcProject __RPC_FAR * This,
            /* [out][retval] */ IApcProjectItems __RPC_FAR *__RPC_FAR *ppProjectItems);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locked )( 
            IApcProject __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbLocked);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VBProject )( 
            IApcProject __RPC_FAR * This,
            /* [out][retval] */ /* external definition not present */ VBProject __RPC_FAR *__RPC_FAR *ppVBProject);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Flags )( 
            IApcProject __RPC_FAR * This,
            /* [out][retval] */ APCPROJECTFLAG __RPC_FAR *pFlags);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Storage )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IStorage )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventsFrozen )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEventsFrozen);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParseLineError )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrError);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compiled )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasDigitalSignature )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbHasSignature);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IApcProject __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL ForceSave);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAs )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ IApcStorage __RPC_FAR *Storage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveCopyAs )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ IApcStorage __RPC_FAR *Storage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveCompleted )( 
            IApcProject __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveSucceeded);
        
        /* [vararg][helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ BSTR ModuleName,
            /* [in] */ BSTR Name,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
            /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compile )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteLine )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ BSTR ExecuteText);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParseLine )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ BSTR ParseText,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuccess);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IApcProject __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveChanges);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseProjectEvents )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ IApcProjectEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnadviseProjectEvents )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ long Cookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateScopes )( 
            IApcProject __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL AutoFill,
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeUserProtection )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Protected,
            /* [in] */ BSTR Password);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FormsSFILevel )( 
            IApcProject __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwLevel);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FormsSFILevel )( 
            IApcProject __RPC_FAR * This,
            /* [in] */ DWORD dwLevel);
        
        END_INTERFACE
    } IApcProjectVtbl;

    interface IApcProject
    {
        CONST_VTBL struct IApcProjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcProject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcProject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcProject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcProject_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcProject_put_Name(This,NewName)	\
    (This)->lpVtbl -> put_Name(This,NewName)

#define IApcProject_get_DisplayName(This,pbstrDisplayName)	\
    (This)->lpVtbl -> get_DisplayName(This,pbstrDisplayName)

#define IApcProject_put_DisplayName(This,NewDisplayName)	\
    (This)->lpVtbl -> put_DisplayName(This,NewDisplayName)

#define IApcProject_get_ReferenceName(This,pbstrName)	\
    (This)->lpVtbl -> get_ReferenceName(This,pbstrName)

#define IApcProject_put_ReferenceName(This,NewName)	\
    (This)->lpVtbl -> put_ReferenceName(This,NewName)

#define IApcProject_get_Mode(This,pMode)	\
    (This)->lpVtbl -> get_Mode(This,pMode)

#define IApcProject_put_Mode(This,NewMode)	\
    (This)->lpVtbl -> put_Mode(This,NewMode)

#define IApcProject_get_Dirty(This,pbIsDirty)	\
    (This)->lpVtbl -> get_Dirty(This,pbIsDirty)

#define IApcProject_put_Dirty(This,IsDirty)	\
    (This)->lpVtbl -> put_Dirty(This,IsDirty)

#define IApcProject_get_Parent(This,ppProjects)	\
    (This)->lpVtbl -> get_Parent(This,ppProjects)

#define IApcProject_put_HostProtection(This,Protected)	\
    (This)->lpVtbl -> put_HostProtection(This,Protected)

#define IApcProject_get_HostProtection(This,pbProtected)	\
    (This)->lpVtbl -> get_HostProtection(This,pbProtected)

#define IApcProject_get_ProtectionState(This,pState)	\
    (This)->lpVtbl -> get_ProtectionState(This,pState)

#define IApcProject_get_UserProtection(This,pbProtected)	\
    (This)->lpVtbl -> get_UserProtection(This,pbProtected)

#define IApcProject_get_SystemProtection(This,pbProtected)	\
    (This)->lpVtbl -> get_SystemProtection(This,pbProtected)

#define IApcProject_get_DelayProtection(This,pbDelayedProtection)	\
    (This)->lpVtbl -> get_DelayProtection(This,pbDelayedProtection)

#define IApcProject_put_DelayProtection(This,DelayedProtection)	\
    (This)->lpVtbl -> put_DelayProtection(This,DelayedProtection)

#define IApcProject_get_ProjectItems(This,ppProjectItems)	\
    (This)->lpVtbl -> get_ProjectItems(This,ppProjectItems)

#define IApcProject_get_Locked(This,pbLocked)	\
    (This)->lpVtbl -> get_Locked(This,pbLocked)

#define IApcProject_get_VBProject(This,ppVBProject)	\
    (This)->lpVtbl -> get_VBProject(This,ppVBProject)

#define IApcProject_get_Flags(This,pFlags)	\
    (This)->lpVtbl -> get_Flags(This,pFlags)

#define IApcProject_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcProject_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcProject_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcProject_get_Storage(This,ppStorage)	\
    (This)->lpVtbl -> get_Storage(This,ppStorage)

#define IApcProject_get_IStorage(This,ppStorage)	\
    (This)->lpVtbl -> get_IStorage(This,ppStorage)

#define IApcProject_get_EventsFrozen(This,pbEventsFrozen)	\
    (This)->lpVtbl -> get_EventsFrozen(This,pbEventsFrozen)

#define IApcProject_get_ParseLineError(This,pbstrError)	\
    (This)->lpVtbl -> get_ParseLineError(This,pbstrError)

#define IApcProject_get_Compiled(This,pbCompiled)	\
    (This)->lpVtbl -> get_Compiled(This,pbCompiled)

#define IApcProject_get_HasDigitalSignature(This,pbHasSignature)	\
    (This)->lpVtbl -> get_HasDigitalSignature(This,pbHasSignature)

#define IApcProject_Save(This,ForceSave)	\
    (This)->lpVtbl -> Save(This,ForceSave)

#define IApcProject_SaveAs(This,Storage)	\
    (This)->lpVtbl -> SaveAs(This,Storage)

#define IApcProject_SaveCopyAs(This,Storage)	\
    (This)->lpVtbl -> SaveCopyAs(This,Storage)

#define IApcProject_SaveCompleted(This,SaveSucceeded)	\
    (This)->lpVtbl -> SaveCompleted(This,SaveSucceeded)

#define IApcProject_Run(This,ModuleName,Name,Arguments,pReturnValue)	\
    (This)->lpVtbl -> Run(This,ModuleName,Name,Arguments,pReturnValue)

#define IApcProject_Compile(This,pbCompiled)	\
    (This)->lpVtbl -> Compile(This,pbCompiled)

#define IApcProject_ExecuteLine(This,ExecuteText)	\
    (This)->lpVtbl -> ExecuteLine(This,ExecuteText)

#define IApcProject_ParseLine(This,ParseText,pbSuccess)	\
    (This)->lpVtbl -> ParseLine(This,ParseText,pbSuccess)

#define IApcProject_Close(This,SaveChanges)	\
    (This)->lpVtbl -> Close(This,SaveChanges)

#define IApcProject_AdviseProjectEvents(This,EventSink,pCookie)	\
    (This)->lpVtbl -> AdviseProjectEvents(This,EventSink,pCookie)

#define IApcProject_UnadviseProjectEvents(This,Cookie)	\
    (This)->lpVtbl -> UnadviseProjectEvents(This,Cookie)

#define IApcProject_CreateScopes(This,AutoFill,ppScopes)	\
    (This)->lpVtbl -> CreateScopes(This,AutoFill,ppScopes)

#define IApcProject_ChangeUserProtection(This,Protected,Password)	\
    (This)->lpVtbl -> ChangeUserProtection(This,Protected,Password)

#define IApcProject_get_FormsSFILevel(This,pdwLevel)	\
    (This)->lpVtbl -> get_FormsSFILevel(This,pdwLevel)

#define IApcProject_put_FormsSFILevel(This,dwLevel)	\
    (This)->lpVtbl -> put_FormsSFILevel(This,dwLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Name_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcProject_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_Name_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB IApcProject_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_DisplayName_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDisplayName);


void __RPC_STUB IApcProject_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_DisplayName_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ BSTR NewDisplayName);


void __RPC_STUB IApcProject_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_ReferenceName_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcProject_get_ReferenceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_ReferenceName_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB IApcProject_put_ReferenceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Mode_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ APCPROJECTMODE __RPC_FAR *pMode);


void __RPC_STUB IApcProject_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_Mode_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ APCPROJECTMODE NewMode);


void __RPC_STUB IApcProject_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Dirty_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbIsDirty);


void __RPC_STUB IApcProject_get_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_Dirty_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL IsDirty);


void __RPC_STUB IApcProject_put_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Parent_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ IApcProjects __RPC_FAR *__RPC_FAR *ppProjects);


void __RPC_STUB IApcProject_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_HostProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Protected);


void __RPC_STUB IApcProject_put_HostProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_HostProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected);


void __RPC_STUB IApcProject_get_HostProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_ProtectionState_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ APCPROJECTPROTECTION __RPC_FAR *pState);


void __RPC_STUB IApcProject_get_ProtectionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_UserProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected);


void __RPC_STUB IApcProject_get_UserProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_SystemProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbProtected);


void __RPC_STUB IApcProject_get_SystemProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_DelayProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbDelayedProtection);


void __RPC_STUB IApcProject_get_DelayProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_DelayProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL DelayedProtection);


void __RPC_STUB IApcProject_put_DelayProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_ProjectItems_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [out][retval] */ IApcProjectItems __RPC_FAR *__RPC_FAR *ppProjectItems);


void __RPC_STUB IApcProject_get_ProjectItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Locked_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbLocked);


void __RPC_STUB IApcProject_get_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_VBProject_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [out][retval] */ /* external definition not present */ VBProject __RPC_FAR *__RPC_FAR *ppVBProject);


void __RPC_STUB IApcProject_get_VBProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Flags_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [out][retval] */ APCPROJECTFLAG __RPC_FAR *pFlags);


void __RPC_STUB IApcProject_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_Tag_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcProject_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Tag_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcProject_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Apc_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProject_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Storage_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcProject_get_Storage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_IStorage_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcProject_get_IStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_EventsFrozen_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbEventsFrozen);


void __RPC_STUB IApcProject_get_EventsFrozen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_ParseLineError_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrError);


void __RPC_STUB IApcProject_get_ParseLineError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_Compiled_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled);


void __RPC_STUB IApcProject_get_Compiled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_HasDigitalSignature_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbHasSignature);


void __RPC_STUB IApcProject_get_HasDigitalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_Save_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL ForceSave);


void __RPC_STUB IApcProject_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_SaveAs_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ IApcStorage __RPC_FAR *Storage);


void __RPC_STUB IApcProject_SaveAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_SaveCopyAs_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ IApcStorage __RPC_FAR *Storage);


void __RPC_STUB IApcProject_SaveCopyAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_SaveCompleted_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveSucceeded);


void __RPC_STUB IApcProject_SaveCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_Run_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ BSTR ModuleName,
    /* [in] */ BSTR Name,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
    /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue);


void __RPC_STUB IApcProject_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_Compile_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled);


void __RPC_STUB IApcProject_Compile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_ExecuteLine_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ BSTR ExecuteText);


void __RPC_STUB IApcProject_ExecuteLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_ParseLine_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ BSTR ParseText,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuccess);


void __RPC_STUB IApcProject_ParseLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_Close_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveChanges);


void __RPC_STUB IApcProject_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_AdviseProjectEvents_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ IApcProjectEvents __RPC_FAR *EventSink,
    /* [retval][out] */ long __RPC_FAR *pCookie);


void __RPC_STUB IApcProject_AdviseProjectEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_UnadviseProjectEvents_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ long Cookie);


void __RPC_STUB IApcProject_UnadviseProjectEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_CreateScopes_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL AutoFill,
    /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes);


void __RPC_STUB IApcProject_CreateScopes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProject_ChangeUserProtection_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Protected,
    /* [in] */ BSTR Password);


void __RPC_STUB IApcProject_ChangeUserProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProject_get_FormsSFILevel_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwLevel);


void __RPC_STUB IApcProject_get_FormsSFILevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProject_put_FormsSFILevel_Proxy( 
    IApcProject __RPC_FAR * This,
    /* [in] */ DWORD dwLevel);


void __RPC_STUB IApcProject_put_FormsSFILevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProject_INTERFACE_DEFINED__ */


#ifndef __IApcProjectEvents_INTERFACE_DEFINED__
#define __IApcProjectEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProjectEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][uuid] */ 



EXTERN_C const IID IID_IApcProjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProjectEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ProjectItemCreated( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ProjectItemDelete( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModeChange( 
            /* [in] */ APCPROJECTMODE NewMode) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE NameChange( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            /* [in] */ BSTR OldName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ProcedureAdd( 
            /* [in] */ IApcProcedure __RPC_FAR *Procedure) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ProcedureDelete( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ APCPROCEDURETYPE ProcedureType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModuleChange( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenProjectItem( 
            /* [in] */ BSTR Name,
            /* [in] */ long ID,
            /* [out][in] */ IDispatch __RPC_FAR *__RPC_FAR *HostProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModuleDirtyChange( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            VARIANT_BOOL Dirty) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProjectEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProjectEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IApcProjectEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IApcProjectEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProjectItemCreated )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProjectItemDelete )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModeChange )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ APCPROJECTMODE NewMode);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NameChange )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            /* [in] */ BSTR OldName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProcedureAdd )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProcedure __RPC_FAR *Procedure);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProcedureDelete )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ APCPROCEDURETYPE ProcedureType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModuleChange )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenProjectItem )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ long ID,
            /* [out][in] */ IDispatch __RPC_FAR *__RPC_FAR *HostProjectItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModuleDirtyChange )( 
            IApcProjectEvents __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            VARIANT_BOOL Dirty);
        
        END_INTERFACE
    } IApcProjectEventsVtbl;

    interface IApcProjectEvents
    {
        CONST_VTBL struct IApcProjectEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProjectEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProjectEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProjectEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProjectEvents_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IApcProjectEvents_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define IApcProjectEvents_ProjectItemCreated(This,ProjectItem)	\
    (This)->lpVtbl -> ProjectItemCreated(This,ProjectItem)

#define IApcProjectEvents_ProjectItemDelete(This,ProjectItem)	\
    (This)->lpVtbl -> ProjectItemDelete(This,ProjectItem)

#define IApcProjectEvents_ModeChange(This,NewMode)	\
    (This)->lpVtbl -> ModeChange(This,NewMode)

#define IApcProjectEvents_NameChange(This,ProjectItem,OldName)	\
    (This)->lpVtbl -> NameChange(This,ProjectItem,OldName)

#define IApcProjectEvents_ProcedureAdd(This,Procedure)	\
    (This)->lpVtbl -> ProcedureAdd(This,Procedure)

#define IApcProjectEvents_ProcedureDelete(This,ProjectItem,ProcedureName,ProcedureType)	\
    (This)->lpVtbl -> ProcedureDelete(This,ProjectItem,ProcedureName,ProcedureType)

#define IApcProjectEvents_ModuleChange(This,ProjectItem)	\
    (This)->lpVtbl -> ModuleChange(This,ProjectItem)

#define IApcProjectEvents_OpenProjectItem(This,Name,ID,HostProjectItem)	\
    (This)->lpVtbl -> OpenProjectItem(This,Name,ID,HostProjectItem)

#define IApcProjectEvents_ModuleDirtyChange(This,ProjectItem,Dirty)	\
    (This)->lpVtbl -> ModuleDirtyChange(This,ProjectItem,Dirty)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_Reset_Proxy( 
    IApcProjectEvents __RPC_FAR * This);


void __RPC_STUB IApcProjectEvents_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_Save_Proxy( 
    IApcProjectEvents __RPC_FAR * This);


void __RPC_STUB IApcProjectEvents_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ProjectItemCreated_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem);


void __RPC_STUB IApcProjectEvents_ProjectItemCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ProjectItemDelete_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem);


void __RPC_STUB IApcProjectEvents_ProjectItemDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ModeChange_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ APCPROJECTMODE NewMode);


void __RPC_STUB IApcProjectEvents_ModeChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_NameChange_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
    /* [in] */ BSTR OldName);


void __RPC_STUB IApcProjectEvents_NameChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ProcedureAdd_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProcedure __RPC_FAR *Procedure);


void __RPC_STUB IApcProjectEvents_ProcedureAdd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ProcedureDelete_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
    /* [in] */ BSTR ProcedureName,
    /* [in] */ APCPROCEDURETYPE ProcedureType);


void __RPC_STUB IApcProjectEvents_ProcedureDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ModuleChange_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem);


void __RPC_STUB IApcProjectEvents_ModuleChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_OpenProjectItem_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ long ID,
    /* [out][in] */ IDispatch __RPC_FAR *__RPC_FAR *HostProjectItem);


void __RPC_STUB IApcProjectEvents_OpenProjectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectEvents_ModuleDirtyChange_Proxy( 
    IApcProjectEvents __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
    VARIANT_BOOL Dirty);


void __RPC_STUB IApcProjectEvents_ModuleDirtyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProjectEvents_INTERFACE_DEFINED__ */


#ifndef __IApcProjectItems_INTERFACE_DEFINED__
#define __IApcProjectItems_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProjectItems
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcProjectItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProjectItems : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemByID( 
            /* [in] */ long ID,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VBComponents( 
            /* [retval][out] */ /* external definition not present */ _VBComponents __RPC_FAR *__RPC_FAR *ppVBComponents) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddCodeModule( 
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddClassModule( 
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddHostProjectItem( 
            /* [in] */ VARIANT __RPC_FAR *HostObject,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddDesignerProjectItem( 
            /* [in] */ BSTR Designer,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddHostClass( 
            /* [in] */ VARIANT __RPC_FAR *HostObject,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            /* [optional][in] */ BSTR NewName,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *HostObject,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppNewProjItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ValidName( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProjectItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProjectItems __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProjectItems __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcProjectItems __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcProjectItems __RPC_FAR * This,
            /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcProjectItems __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcProjectItems __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcProjectItems __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemByID )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ long ID,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VBComponents )( 
            IApcProjectItems __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ _VBComponents __RPC_FAR *__RPC_FAR *ppVBComponents);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddCodeModule )( 
            IApcProjectItems __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddClassModule )( 
            IApcProjectItems __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddHostProjectItem )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *HostObject,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddDesignerProjectItem )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ BSTR Designer,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddHostClass )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *HostObject,
            /* [optional][in] */ BSTR Name,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcProjectItems __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
            /* [optional][in] */ BSTR NewName,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *HostObject,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppNewProjItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ValidName )( 
            IApcProjectItems __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbValid);
        
        END_INTERFACE
    } IApcProjectItemsVtbl;

    interface IApcProjectItems
    {
        CONST_VTBL struct IApcProjectItemsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProjectItems_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProjectItems_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProjectItems_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProjectItems_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcProjectItems_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcProjectItems_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcProjectItems_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcProjectItems_get_Parent(This,ppProject)	\
    (This)->lpVtbl -> get_Parent(This,ppProject)

#define IApcProjectItems_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcProjectItems_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcProjectItems_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcProjectItems_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcProjectItems_get_Item(This,Index,ppProjectItem)	\
    (This)->lpVtbl -> get_Item(This,Index,ppProjectItem)

#define IApcProjectItems_get_ItemByID(This,ID,ppProjectItem)	\
    (This)->lpVtbl -> get_ItemByID(This,ID,ppProjectItem)

#define IApcProjectItems_get_VBComponents(This,ppVBComponents)	\
    (This)->lpVtbl -> get_VBComponents(This,ppVBComponents)

#define IApcProjectItems_AddCodeModule(This,Name,ppProjectItem)	\
    (This)->lpVtbl -> AddCodeModule(This,Name,ppProjectItem)

#define IApcProjectItems_AddClassModule(This,Name,ppProjectItem)	\
    (This)->lpVtbl -> AddClassModule(This,Name,ppProjectItem)

#define IApcProjectItems_AddHostProjectItem(This,HostObject,Name,ppProjectItem)	\
    (This)->lpVtbl -> AddHostProjectItem(This,HostObject,Name,ppProjectItem)

#define IApcProjectItems_AddDesignerProjectItem(This,Designer,Name,ppProjectItem)	\
    (This)->lpVtbl -> AddDesignerProjectItem(This,Designer,Name,ppProjectItem)

#define IApcProjectItems_AddHostClass(This,HostObject,Name,ppProjectItem)	\
    (This)->lpVtbl -> AddHostClass(This,HostObject,Name,ppProjectItem)

#define IApcProjectItems_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcProjectItems_Copy(This,ProjectItem,NewName,HostObject,ppNewProjItem)	\
    (This)->lpVtbl -> Copy(This,ProjectItem,NewName,HostObject,ppNewProjItem)

#define IApcProjectItems_ValidName(This,Name,pbValid)	\
    (This)->lpVtbl -> ValidName(This,Name,pbValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_Parent_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [retval][out] */ IApcProject __RPC_FAR *__RPC_FAR *ppProject);


void __RPC_STUB IApcProjectItems_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_Count_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcProjectItems_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_put_Tag_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcProjectItems_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_Tag_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcProjectItems_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_Apc_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProjectItems_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_Item_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_ItemByID_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ long ID,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_get_ItemByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_VBComponents_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ _VBComponents __RPC_FAR *__RPC_FAR *ppVBComponents);


void __RPC_STUB IApcProjectItems_get_VBComponents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_AddCodeModule_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_AddCodeModule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_AddClassModule_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_AddClassModule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_AddHostProjectItem_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *HostObject,
    /* [optional][in] */ BSTR Name,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_AddHostProjectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_AddDesignerProjectItem_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ BSTR Designer,
    /* [optional][in] */ BSTR Name,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_AddDesignerProjectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_AddHostClass_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *HostObject,
    /* [optional][in] */ BSTR Name,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItems_AddHostClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_get_NewEnum_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcProjectItems_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_Copy_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ IApcProjectItem __RPC_FAR *ProjectItem,
    /* [optional][in] */ BSTR NewName,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *HostObject,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppNewProjItem);


void __RPC_STUB IApcProjectItems_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItems_ValidName_Proxy( 
    IApcProjectItems __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbValid);


void __RPC_STUB IApcProjectItems_ValidName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProjectItems_INTERFACE_DEFINED__ */


#ifndef __IApcProjectItem_INTERFACE_DEFINED__
#define __IApcProjectItem_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProjectItem
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcProjectItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProjectItem : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProjectItems __RPC_FAR *__RPC_FAR *ppProjectItems) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ APCPROJECTITEMTYPE __RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CompositeObject( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long __RPC_FAR *pID) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Procedures( 
            /* [retval][out] */ IApcProcedures __RPC_FAR *__RPC_FAR *ppProceduress) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDisplayName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR NewDisplayName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Controls( 
            /* [retval][out] */ IApcControls __RPC_FAR *__RPC_FAR *ppControls) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Categories( 
            /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppIApcCategorizedProperties) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VBComponent( 
            /* [out][retval] */ /* external definition not present */ _VBComponent __RPC_FAR *__RPC_FAR *ppVBComponent) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HostObject( 
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostObject) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AllowViewObject( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbAllowViewObject) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AllowViewObject( 
            /* [in] */ VARIANT_BOOL AllowViewObject) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *pPicture) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppPicture) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ /* external definition not present */ OLE_COLOR BackColor) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_RequiredClasses( 
            /* [out][retval] */ IApcRequiredClasses __RPC_FAR *__RPC_FAR *ppRequiredClasses) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Instances( 
            /* [out][retval] */ IApcInstances __RPC_FAR *__RPC_FAR *ppInstances) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AppendTextFromFile( 
            /* [in] */ BSTR FileName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ViewEventHandler( 
            /* [optional][in] */ BSTR EventName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ViewCode( 
            /* [optional][in] */ BSTR ProcedureName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
        virtual /* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ BSTR Name,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
            /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AdviseProjectItemEvents( 
            /* [in] */ IApcProjectItemEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UnadviseProjectItemEvents( 
            /* [in] */ long Cookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Compile( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetHostClassBase( 
            /* [in] */ IDispatch __RPC_FAR *HostClassBase) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProjectItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProjectItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProjectItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcProjectItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ IApcProjectItems __RPC_FAR *__RPC_FAR *ppProjectItems);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ APCPROJECTITEMTYPE __RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CompositeObject )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ BSTR NewName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pID);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Procedures )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ IApcProcedures __RPC_FAR *__RPC_FAR *ppProceduress);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDisplayName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ BSTR NewDisplayName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Controls )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ IApcControls __RPC_FAR *__RPC_FAR *ppControls);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Categories )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppIApcCategorizedProperties);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VBComponent )( 
            IApcProjectItem __RPC_FAR * This,
            /* [out][retval] */ /* external definition not present */ _VBComponent __RPC_FAR *__RPC_FAR *ppVBComponent);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostObject )( 
            IApcProjectItem __RPC_FAR * This,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostObject);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AllowViewObject )( 
            IApcProjectItem __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbAllowViewObject);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AllowViewObject )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL AllowViewObject);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Picture )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *pPicture);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Picture )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppPicture);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ /* external definition not present */ OLE_COLOR BackColor);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequiredClasses )( 
            IApcProjectItem __RPC_FAR * This,
            /* [out][retval] */ IApcRequiredClasses __RPC_FAR *__RPC_FAR *ppRequiredClasses);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Instances )( 
            IApcProjectItem __RPC_FAR * This,
            /* [out][retval] */ IApcInstances __RPC_FAR *__RPC_FAR *ppInstances);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendTextFromFile )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ BSTR FileName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ViewEventHandler )( 
            IApcProjectItem __RPC_FAR * This,
            /* [optional][in] */ BSTR EventName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ViewCode )( 
            IApcProjectItem __RPC_FAR * This,
            /* [optional][in] */ BSTR ProcedureName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IApcProjectItem __RPC_FAR * This);
        
        /* [vararg][helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
            /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcProjectItem __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseProjectItemEvents )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ IApcProjectItemEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnadviseProjectItemEvents )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ long Cookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compile )( 
            IApcProjectItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHostClassBase )( 
            IApcProjectItem __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *HostClassBase);
        
        END_INTERFACE
    } IApcProjectItemVtbl;

    interface IApcProjectItem
    {
        CONST_VTBL struct IApcProjectItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProjectItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProjectItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProjectItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProjectItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcProjectItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcProjectItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcProjectItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcProjectItem_get_Parent(This,ppProjectItems)	\
    (This)->lpVtbl -> get_Parent(This,ppProjectItems)

#define IApcProjectItem_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define IApcProjectItem_get_CompositeObject(This,ppProjectItem)	\
    (This)->lpVtbl -> get_CompositeObject(This,ppProjectItem)

#define IApcProjectItem_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcProjectItem_put_Name(This,NewName)	\
    (This)->lpVtbl -> put_Name(This,NewName)

#define IApcProjectItem_get_ID(This,pID)	\
    (This)->lpVtbl -> get_ID(This,pID)

#define IApcProjectItem_get_Procedures(This,ppProceduress)	\
    (This)->lpVtbl -> get_Procedures(This,ppProceduress)

#define IApcProjectItem_get_DisplayName(This,pbstrDisplayName)	\
    (This)->lpVtbl -> get_DisplayName(This,pbstrDisplayName)

#define IApcProjectItem_put_DisplayName(This,NewDisplayName)	\
    (This)->lpVtbl -> put_DisplayName(This,NewDisplayName)

#define IApcProjectItem_get_Controls(This,ppControls)	\
    (This)->lpVtbl -> get_Controls(This,ppControls)

#define IApcProjectItem_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcProjectItem_get_Categories(This,ppIApcCategorizedProperties)	\
    (This)->lpVtbl -> get_Categories(This,ppIApcCategorizedProperties)

#define IApcProjectItem_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcProjectItem_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcProjectItem_get_VBComponent(This,ppVBComponent)	\
    (This)->lpVtbl -> get_VBComponent(This,ppVBComponent)

#define IApcProjectItem_get_HostObject(This,ppHostObject)	\
    (This)->lpVtbl -> get_HostObject(This,ppHostObject)

#define IApcProjectItem_get_AllowViewObject(This,pbAllowViewObject)	\
    (This)->lpVtbl -> get_AllowViewObject(This,pbAllowViewObject)

#define IApcProjectItem_put_AllowViewObject(This,AllowViewObject)	\
    (This)->lpVtbl -> put_AllowViewObject(This,AllowViewObject)

#define IApcProjectItem_put_Picture(This,pPicture)	\
    (This)->lpVtbl -> put_Picture(This,pPicture)

#define IApcProjectItem_get_Picture(This,ppPicture)	\
    (This)->lpVtbl -> get_Picture(This,ppPicture)

#define IApcProjectItem_get_BackColor(This,pBackColor)	\
    (This)->lpVtbl -> get_BackColor(This,pBackColor)

#define IApcProjectItem_put_BackColor(This,BackColor)	\
    (This)->lpVtbl -> put_BackColor(This,BackColor)

#define IApcProjectItem_get_RequiredClasses(This,ppRequiredClasses)	\
    (This)->lpVtbl -> get_RequiredClasses(This,ppRequiredClasses)

#define IApcProjectItem_get_Instances(This,ppInstances)	\
    (This)->lpVtbl -> get_Instances(This,ppInstances)

#define IApcProjectItem_AppendTextFromFile(This,FileName)	\
    (This)->lpVtbl -> AppendTextFromFile(This,FileName)

#define IApcProjectItem_ViewEventHandler(This,EventName)	\
    (This)->lpVtbl -> ViewEventHandler(This,EventName)

#define IApcProjectItem_ViewCode(This,ProcedureName)	\
    (This)->lpVtbl -> ViewCode(This,ProcedureName)

#define IApcProjectItem_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#define IApcProjectItem_Run(This,Name,Arguments,pReturnValue)	\
    (This)->lpVtbl -> Run(This,Name,Arguments,pReturnValue)

#define IApcProjectItem_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IApcProjectItem_AdviseProjectItemEvents(This,EventSink,pCookie)	\
    (This)->lpVtbl -> AdviseProjectItemEvents(This,EventSink,pCookie)

#define IApcProjectItem_UnadviseProjectItemEvents(This,Cookie)	\
    (This)->lpVtbl -> UnadviseProjectItemEvents(This,Cookie)

#define IApcProjectItem_Compile(This,pbCompiled)	\
    (This)->lpVtbl -> Compile(This,pbCompiled)

#define IApcProjectItem_SetHostClassBase(This,HostClassBase)	\
    (This)->lpVtbl -> SetHostClassBase(This,HostClassBase)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Parent_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ IApcProjectItems __RPC_FAR *__RPC_FAR *ppProjectItems);


void __RPC_STUB IApcProjectItem_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Type_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ APCPROJECTITEMTYPE __RPC_FAR *pType);


void __RPC_STUB IApcProjectItem_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_CompositeObject_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProjectItem_get_CompositeObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Name_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcProjectItem_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_put_Name_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB IApcProjectItem_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_ID_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pID);


void __RPC_STUB IApcProjectItem_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Procedures_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ IApcProcedures __RPC_FAR *__RPC_FAR *ppProceduress);


void __RPC_STUB IApcProjectItem_get_Procedures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_DisplayName_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDisplayName);


void __RPC_STUB IApcProjectItem_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_put_DisplayName_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ BSTR NewDisplayName);


void __RPC_STUB IApcProjectItem_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Controls_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ IApcControls __RPC_FAR *__RPC_FAR *ppControls);


void __RPC_STUB IApcProjectItem_get_Controls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_put_Tag_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcProjectItem_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Categories_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppIApcCategorizedProperties);


void __RPC_STUB IApcProjectItem_get_Categories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Tag_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcProjectItem_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Apc_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProjectItem_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_VBComponent_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [out][retval] */ /* external definition not present */ _VBComponent __RPC_FAR *__RPC_FAR *ppVBComponent);


void __RPC_STUB IApcProjectItem_get_VBComponent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_HostObject_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostObject);


void __RPC_STUB IApcProjectItem_get_HostObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_AllowViewObject_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbAllowViewObject);


void __RPC_STUB IApcProjectItem_get_AllowViewObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_put_AllowViewObject_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL AllowViewObject);


void __RPC_STUB IApcProjectItem_put_AllowViewObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_put_Picture_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *pPicture);


void __RPC_STUB IApcProjectItem_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Picture_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppPicture);


void __RPC_STUB IApcProjectItem_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_BackColor_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor);


void __RPC_STUB IApcProjectItem_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_put_BackColor_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ /* external definition not present */ OLE_COLOR BackColor);


void __RPC_STUB IApcProjectItem_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_RequiredClasses_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [out][retval] */ IApcRequiredClasses __RPC_FAR *__RPC_FAR *ppRequiredClasses);


void __RPC_STUB IApcProjectItem_get_RequiredClasses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_get_Instances_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [out][retval] */ IApcInstances __RPC_FAR *__RPC_FAR *ppInstances);


void __RPC_STUB IApcProjectItem_get_Instances_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_AppendTextFromFile_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ BSTR FileName);


void __RPC_STUB IApcProjectItem_AppendTextFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_ViewEventHandler_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [optional][in] */ BSTR EventName);


void __RPC_STUB IApcProjectItem_ViewEventHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_ViewCode_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [optional][in] */ BSTR ProcedureName);


void __RPC_STUB IApcProjectItem_ViewCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_Activate_Proxy( 
    IApcProjectItem __RPC_FAR * This);


void __RPC_STUB IApcProjectItem_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_Run_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
    /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue);


void __RPC_STUB IApcProjectItem_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_Delete_Proxy( 
    IApcProjectItem __RPC_FAR * This);


void __RPC_STUB IApcProjectItem_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_AdviseProjectItemEvents_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ IApcProjectItemEvents __RPC_FAR *EventSink,
    /* [retval][out] */ long __RPC_FAR *pCookie);


void __RPC_STUB IApcProjectItem_AdviseProjectItemEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_UnadviseProjectItemEvents_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ long Cookie);


void __RPC_STUB IApcProjectItem_UnadviseProjectItemEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_Compile_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbCompiled);


void __RPC_STUB IApcProjectItem_Compile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProjectItem_SetHostClassBase_Proxy( 
    IApcProjectItem __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *HostClassBase);


void __RPC_STUB IApcProjectItem_SetHostClassBase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProjectItem_INTERFACE_DEFINED__ */


#ifndef __IApcProjectItemEvents_INTERFACE_DEFINED__
#define __IApcProjectItemEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProjectItemEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][uuid] */ 



EXTERN_C const IID IID_IApcProjectItemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProjectItemEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE View( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [out][in] */ IDispatch __RPC_FAR *__RPC_FAR *Instance) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseInstances( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE InstanceCreated( 
            /* [in] */ IDispatch __RPC_FAR *Instance) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProjectItemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProjectItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProjectItemEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProjectItemEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *View )( 
            IApcProjectItemEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IApcProjectItemEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstance )( 
            IApcProjectItemEvents __RPC_FAR * This,
            /* [out][in] */ IDispatch __RPC_FAR *__RPC_FAR *Instance);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseInstances )( 
            IApcProjectItemEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InstanceCreated )( 
            IApcProjectItemEvents __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Instance);
        
        END_INTERFACE
    } IApcProjectItemEventsVtbl;

    interface IApcProjectItemEvents
    {
        CONST_VTBL struct IApcProjectItemEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProjectItemEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProjectItemEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProjectItemEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProjectItemEvents_View(This)	\
    (This)->lpVtbl -> View(This)

#define IApcProjectItemEvents_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#define IApcProjectItemEvents_CreateInstance(This,Instance)	\
    (This)->lpVtbl -> CreateInstance(This,Instance)

#define IApcProjectItemEvents_ReleaseInstances(This)	\
    (This)->lpVtbl -> ReleaseInstances(This)

#define IApcProjectItemEvents_InstanceCreated(This,Instance)	\
    (This)->lpVtbl -> InstanceCreated(This,Instance)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectItemEvents_View_Proxy( 
    IApcProjectItemEvents __RPC_FAR * This);


void __RPC_STUB IApcProjectItemEvents_View_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectItemEvents_Activate_Proxy( 
    IApcProjectItemEvents __RPC_FAR * This);


void __RPC_STUB IApcProjectItemEvents_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectItemEvents_CreateInstance_Proxy( 
    IApcProjectItemEvents __RPC_FAR * This,
    /* [out][in] */ IDispatch __RPC_FAR *__RPC_FAR *Instance);


void __RPC_STUB IApcProjectItemEvents_CreateInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectItemEvents_ReleaseInstances_Proxy( 
    IApcProjectItemEvents __RPC_FAR * This);


void __RPC_STUB IApcProjectItemEvents_ReleaseInstances_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcProjectItemEvents_InstanceCreated_Proxy( 
    IApcProjectItemEvents __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Instance);


void __RPC_STUB IApcProjectItemEvents_InstanceCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProjectItemEvents_INTERFACE_DEFINED__ */


#ifndef __IApcControls_INTERFACE_DEFINED__
#define __IApcControls_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcControls
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcControls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcControls : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemByID( 
            /* [in] */ long ID,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDispatch __RPC_FAR *HostControl,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
            /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE AddByGuid( 
            /* [in] */ GUID guid,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
            /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE AddByProgID( 
            /* [in] */ BSTR ProgID,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
            /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl) = 0;
        
        virtual /* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE LoadControl( 
            /* [in] */ long ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FinishedLoadingControls( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcControls __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcControls __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcControls __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcControls __RPC_FAR * This,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcControls __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcControls __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcControls __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemByID )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ long ID,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcControls __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *HostControl,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
            /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddByGuid )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ GUID guid,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
            /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddByProgID )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ BSTR ProgID,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
            /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
            /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);
        
        /* [helpcontext][helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadControl )( 
            IApcControls __RPC_FAR * This,
            /* [in] */ long ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FinishedLoadingControls )( 
            IApcControls __RPC_FAR * This);
        
        END_INTERFACE
    } IApcControlsVtbl;

    interface IApcControls
    {
        CONST_VTBL struct IApcControlsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcControls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcControls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcControls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcControls_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcControls_get_Parent(This,ppProjectItem)	\
    (This)->lpVtbl -> get_Parent(This,ppProjectItem)

#define IApcControls_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcControls_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcControls_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcControls_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcControls_get_Item(This,Index,ppControl)	\
    (This)->lpVtbl -> get_Item(This,Index,ppControl)

#define IApcControls_get_ItemByID(This,ID,ppControl)	\
    (This)->lpVtbl -> get_ItemByID(This,ID,ppControl)

#define IApcControls_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcControls_Add(This,HostControl,Extender,Flags,ppControl)	\
    (This)->lpVtbl -> Add(This,HostControl,Extender,Flags,ppControl)

#define IApcControls_AddByGuid(This,guid,Extender,Flags,ppControl)	\
    (This)->lpVtbl -> AddByGuid(This,guid,Extender,Flags,ppControl)

#define IApcControls_AddByProgID(This,ProgID,Extender,Flags,ppControl)	\
    (This)->lpVtbl -> AddByProgID(This,ProgID,Extender,Flags,ppControl)

#define IApcControls_LoadControl(This,ID)	\
    (This)->lpVtbl -> LoadControl(This,ID)

#define IApcControls_FinishedLoadingControls(This)	\
    (This)->lpVtbl -> FinishedLoadingControls(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_Parent_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcControls_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_Count_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcControls_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcControls_put_Tag_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcControls_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_Tag_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcControls_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_Apc_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcControls_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_Item_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);


void __RPC_STUB IApcControls_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_ItemByID_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ long ID,
    /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);


void __RPC_STUB IApcControls_get_ItemByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcControls_get_NewEnum_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcControls_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControls_Add_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *HostControl,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
    /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
    /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);


void __RPC_STUB IApcControls_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcControls_AddByGuid_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ GUID guid,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
    /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
    /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);


void __RPC_STUB IApcControls_AddByGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcControls_AddByProgID_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ BSTR ProgID,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *Extender,
    /* [defaultvalue][in] */ APCCONTROLFLAG Flags,
    /* [retval][out] */ IApcControl __RPC_FAR *__RPC_FAR *ppControl);


void __RPC_STUB IApcControls_AddByProgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IApcControls_LoadControl_Proxy( 
    IApcControls __RPC_FAR * This,
    /* [in] */ long ID);


void __RPC_STUB IApcControls_LoadControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControls_FinishedLoadingControls_Proxy( 
    IApcControls __RPC_FAR * This);


void __RPC_STUB IApcControls_FinishedLoadingControls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcControls_INTERFACE_DEFINED__ */


#ifndef __IApcControl_INTERFACE_DEFINED__
#define __IApcControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcControl
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcControl : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long __RPC_FAR *pID) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PersistTag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PersistTag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HostControl( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostControl) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HostControl( 
            /* [in] */ IDispatch __RPC_FAR *HostControl) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Extender( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppExtender) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Extender( 
            /* [in] */ IDispatch __RPC_FAR *NewExtender) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CompositeControl( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppCompositeControl) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Categories( 
            /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppIApcCategorizedProperties) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcControls __RPC_FAR *__RPC_FAR *ppControls) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ APCCONTROLFLAG __RPC_FAR *pFlags) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ViewEventHandler( 
            /* [optional][in] */ BSTR EventName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AdviseControlEvents( 
            /* [in] */ IApcControlEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UnadviseControlEvents( 
            /* [in] */ long Cookie) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HostControl( 
            /* [in] */ IDispatch __RPC_FAR *HostControl) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Extender( 
            /* [in] */ IDispatch __RPC_FAR *NewExtender) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Disable( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbAllowViewObject) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL AllowViewObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ BSTR NewName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pID);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PersistTag )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PersistTag )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostControl )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostControl);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostControl )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *HostControl);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Extender )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppExtender);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Extender )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *NewExtender);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CompositeControl )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppCompositeControl);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Categories )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppIApcCategorizedProperties);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ IApcControls __RPC_FAR *__RPC_FAR *ppControls);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Flags )( 
            IApcControl __RPC_FAR * This,
            /* [retval][out] */ APCCONTROLFLAG __RPC_FAR *pFlags);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IApcControl __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ViewEventHandler )( 
            IApcControl __RPC_FAR * This,
            /* [optional][in] */ BSTR EventName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcControl __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseControlEvents )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ IApcControlEvents __RPC_FAR *EventSink,
            /* [retval][out] */ long __RPC_FAR *pCookie);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnadviseControlEvents )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ long Cookie);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_HostControl )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *HostControl);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Extender )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *NewExtender);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disable )( 
            IApcControl __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IApcControl __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbAllowViewObject);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IApcControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL AllowViewObject);
        
        END_INTERFACE
    } IApcControlVtbl;

    interface IApcControl
    {
        CONST_VTBL struct IApcControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcControl_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcControl_put_Name(This,NewName)	\
    (This)->lpVtbl -> put_Name(This,NewName)

#define IApcControl_get_ID(This,pID)	\
    (This)->lpVtbl -> get_ID(This,pID)

#define IApcControl_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcControl_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcControl_put_PersistTag(This,UserTag)	\
    (This)->lpVtbl -> put_PersistTag(This,UserTag)

#define IApcControl_get_PersistTag(This,pUserTag)	\
    (This)->lpVtbl -> get_PersistTag(This,pUserTag)

#define IApcControl_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcControl_get_HostControl(This,ppHostControl)	\
    (This)->lpVtbl -> get_HostControl(This,ppHostControl)

#define IApcControl_put_HostControl(This,HostControl)	\
    (This)->lpVtbl -> put_HostControl(This,HostControl)

#define IApcControl_get_Extender(This,ppExtender)	\
    (This)->lpVtbl -> get_Extender(This,ppExtender)

#define IApcControl_put_Extender(This,NewExtender)	\
    (This)->lpVtbl -> put_Extender(This,NewExtender)

#define IApcControl_get_CompositeControl(This,ppCompositeControl)	\
    (This)->lpVtbl -> get_CompositeControl(This,ppCompositeControl)

#define IApcControl_get_Categories(This,ppIApcCategorizedProperties)	\
    (This)->lpVtbl -> get_Categories(This,ppIApcCategorizedProperties)

#define IApcControl_get_Parent(This,ppControls)	\
    (This)->lpVtbl -> get_Parent(This,ppControls)

#define IApcControl_get_Flags(This,pFlags)	\
    (This)->lpVtbl -> get_Flags(This,pFlags)

#define IApcControl_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#define IApcControl_ViewEventHandler(This,EventName)	\
    (This)->lpVtbl -> ViewEventHandler(This,EventName)

#define IApcControl_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IApcControl_AdviseControlEvents(This,EventSink,pCookie)	\
    (This)->lpVtbl -> AdviseControlEvents(This,EventSink,pCookie)

#define IApcControl_UnadviseControlEvents(This,Cookie)	\
    (This)->lpVtbl -> UnadviseControlEvents(This,Cookie)

#define IApcControl_putref_HostControl(This,HostControl)	\
    (This)->lpVtbl -> putref_HostControl(This,HostControl)

#define IApcControl_putref_Extender(This,NewExtender)	\
    (This)->lpVtbl -> putref_Extender(This,NewExtender)

#define IApcControl_Disable(This)	\
    (This)->lpVtbl -> Disable(This)

#define IApcControl_get_Visible(This,pbAllowViewObject)	\
    (This)->lpVtbl -> get_Visible(This,pbAllowViewObject)

#define IApcControl_put_Visible(This,AllowViewObject)	\
    (This)->lpVtbl -> put_Visible(This,AllowViewObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Name_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcControl_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcControl_put_Name_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB IApcControl_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_ID_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pID);


void __RPC_STUB IApcControl_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcControl_put_Tag_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcControl_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Tag_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcControl_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcControl_put_PersistTag_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcControl_put_PersistTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_PersistTag_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcControl_get_PersistTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Apc_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcControl_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_HostControl_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostControl);


void __RPC_STUB IApcControl_get_HostControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcControl_put_HostControl_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *HostControl);


void __RPC_STUB IApcControl_put_HostControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Extender_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppExtender);


void __RPC_STUB IApcControl_get_Extender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcControl_put_Extender_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *NewExtender);


void __RPC_STUB IApcControl_put_Extender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_CompositeControl_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppCompositeControl);


void __RPC_STUB IApcControl_get_CompositeControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Categories_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppIApcCategorizedProperties);


void __RPC_STUB IApcControl_get_Categories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Parent_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ IApcControls __RPC_FAR *__RPC_FAR *ppControls);


void __RPC_STUB IApcControl_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Flags_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [retval][out] */ APCCONTROLFLAG __RPC_FAR *pFlags);


void __RPC_STUB IApcControl_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControl_Activate_Proxy( 
    IApcControl __RPC_FAR * This);


void __RPC_STUB IApcControl_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControl_ViewEventHandler_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [optional][in] */ BSTR EventName);


void __RPC_STUB IApcControl_ViewEventHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControl_Delete_Proxy( 
    IApcControl __RPC_FAR * This);


void __RPC_STUB IApcControl_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControl_AdviseControlEvents_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ IApcControlEvents __RPC_FAR *EventSink,
    /* [retval][out] */ long __RPC_FAR *pCookie);


void __RPC_STUB IApcControl_AdviseControlEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControl_UnadviseControlEvents_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ long Cookie);


void __RPC_STUB IApcControl_UnadviseControlEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE IApcControl_putref_HostControl_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *HostControl);


void __RPC_STUB IApcControl_putref_HostControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE IApcControl_putref_Extender_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *NewExtender);


void __RPC_STUB IApcControl_putref_Extender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcControl_Disable_Proxy( 
    IApcControl __RPC_FAR * This);


void __RPC_STUB IApcControl_Disable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcControl_get_Visible_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbAllowViewObject);


void __RPC_STUB IApcControl_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcControl_put_Visible_Proxy( 
    IApcControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL AllowViewObject);


void __RPC_STUB IApcControl_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcControl_INTERFACE_DEFINED__ */


#ifndef __IApcControlEvents_INTERFACE_DEFINED__
#define __IApcControlEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcControlEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][uuid] */ 



EXTERN_C const IID IID_IApcControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcControlEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcControlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcControlEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcControlEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IApcControlEvents __RPC_FAR * This);
        
        END_INTERFACE
    } IApcControlEventsVtbl;

    interface IApcControlEvents
    {
        CONST_VTBL struct IApcControlEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcControlEvents_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcControlEvents_Activate_Proxy( 
    IApcControlEvents __RPC_FAR * This);


void __RPC_STUB IApcControlEvents_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcControlEvents_INTERFACE_DEFINED__ */


#ifndef __IApcProcedures_INTERFACE_DEFINED__
#define __IApcProcedures_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProcedures
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcProcedures;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProcedures : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcProcedure __RPC_FAR *__RPC_FAR *ppProcedure) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProceduresVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProcedures __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProcedures __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProcedures __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcProcedures __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcProcedures __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcProcedures __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcProcedures __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcProcedures __RPC_FAR * This,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcProcedures __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcProcedures __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcProcedure __RPC_FAR *__RPC_FAR *ppProcedure);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcProcedures __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcProcedures __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcProcedures __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcProcedures __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        END_INTERFACE
    } IApcProceduresVtbl;

    interface IApcProcedures
    {
        CONST_VTBL struct IApcProceduresVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProcedures_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProcedures_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProcedures_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProcedures_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcProcedures_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcProcedures_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcProcedures_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcProcedures_get_Parent(This,ppProjectItem)	\
    (This)->lpVtbl -> get_Parent(This,ppProjectItem)

#define IApcProcedures_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcProcedures_get_Item(This,Index,ppProcedure)	\
    (This)->lpVtbl -> get_Item(This,Index,ppProcedure)

#define IApcProcedures_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcProcedures_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcProcedures_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcProcedures_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedures_get_Parent_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcProcedures_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedures_get_Count_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcProcedures_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedures_get_Item_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcProcedure __RPC_FAR *__RPC_FAR *ppProcedure);


void __RPC_STUB IApcProcedures_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedures_get_NewEnum_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcProcedures_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProcedures_put_Tag_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcProcedures_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedures_get_Tag_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcProcedures_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedures_get_Apc_Proxy( 
    IApcProcedures __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProcedures_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProcedures_INTERFACE_DEFINED__ */


#ifndef __IApcProcedure_INTERFACE_DEFINED__
#define __IApcProcedure_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcProcedure
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcProcedure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcProcedure : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProcedures __RPC_FAR *__RPC_FAR *ppProcedures) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR NewDescription) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDescription) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HostString( 
            /* [in] */ BSTR NewHostString) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HostString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHostString) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProcedureScope( 
            /* [out][retval] */ APCPROCEDURESCOPE __RPC_FAR *pScope) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasParameters( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbHasParameters) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Empty( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbEmpty) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [out][retval] */ APCPROCEDURETYPE __RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProcKind( 
            /* [out][retval] */ APCPROCKIND __RPC_FAR *pProcKind) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartLine( 
            /* [retval][out] */ long __RPC_FAR *pStartLine) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndLine( 
            /* [retval][out] */ long __RPC_FAR *pEndLine) = 0;
        
        virtual /* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
            /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ViewCode( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcProcedureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcProcedure __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcProcedure __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcProcedure __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ IApcProcedures __RPC_FAR *__RPC_FAR *ppProcedures);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ BSTR NewDescription);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDescription);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostString )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ BSTR NewHostString);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostString )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHostString);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProcedureScope )( 
            IApcProcedure __RPC_FAR * This,
            /* [out][retval] */ APCPROCEDURESCOPE __RPC_FAR *pScope);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasParameters )( 
            IApcProcedure __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbHasParameters);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Empty )( 
            IApcProcedure __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbEmpty);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IApcProcedure __RPC_FAR * This,
            /* [out][retval] */ APCPROCEDURETYPE __RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProcKind )( 
            IApcProcedure __RPC_FAR * This,
            /* [out][retval] */ APCPROCKIND __RPC_FAR *pProcKind);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartLine )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pStartLine);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndLine )( 
            IApcProcedure __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pEndLine);
        
        /* [vararg][helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IApcProcedure __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
            /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ViewCode )( 
            IApcProcedure __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcProcedure __RPC_FAR * This);
        
        END_INTERFACE
    } IApcProcedureVtbl;

    interface IApcProcedure
    {
        CONST_VTBL struct IApcProcedureVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcProcedure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcProcedure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcProcedure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcProcedure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcProcedure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcProcedure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcProcedure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcProcedure_get_Parent(This,ppProcedures)	\
    (This)->lpVtbl -> get_Parent(This,ppProcedures)

#define IApcProcedure_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcProcedure_put_Description(This,NewDescription)	\
    (This)->lpVtbl -> put_Description(This,NewDescription)

#define IApcProcedure_get_Description(This,pbstrDescription)	\
    (This)->lpVtbl -> get_Description(This,pbstrDescription)

#define IApcProcedure_put_HostString(This,NewHostString)	\
    (This)->lpVtbl -> put_HostString(This,NewHostString)

#define IApcProcedure_get_HostString(This,pbstrHostString)	\
    (This)->lpVtbl -> get_HostString(This,pbstrHostString)

#define IApcProcedure_get_ProcedureScope(This,pScope)	\
    (This)->lpVtbl -> get_ProcedureScope(This,pScope)

#define IApcProcedure_get_HasParameters(This,pbHasParameters)	\
    (This)->lpVtbl -> get_HasParameters(This,pbHasParameters)

#define IApcProcedure_get_Empty(This,pbEmpty)	\
    (This)->lpVtbl -> get_Empty(This,pbEmpty)

#define IApcProcedure_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define IApcProcedure_get_ProcKind(This,pProcKind)	\
    (This)->lpVtbl -> get_ProcKind(This,pProcKind)

#define IApcProcedure_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcProcedure_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcProcedure_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcProcedure_get_StartLine(This,pStartLine)	\
    (This)->lpVtbl -> get_StartLine(This,pStartLine)

#define IApcProcedure_get_EndLine(This,pEndLine)	\
    (This)->lpVtbl -> get_EndLine(This,pEndLine)

#define IApcProcedure_Run(This,Arguments,pReturnValue)	\
    (This)->lpVtbl -> Run(This,Arguments,pReturnValue)

#define IApcProcedure_ViewCode(This)	\
    (This)->lpVtbl -> ViewCode(This)

#define IApcProcedure_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Parent_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ IApcProcedures __RPC_FAR *__RPC_FAR *ppProcedures);


void __RPC_STUB IApcProcedure_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Name_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcProcedure_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProcedure_put_Description_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [in] */ BSTR NewDescription);


void __RPC_STUB IApcProcedure_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Description_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDescription);


void __RPC_STUB IApcProcedure_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProcedure_put_HostString_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [in] */ BSTR NewHostString);


void __RPC_STUB IApcProcedure_put_HostString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_HostString_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrHostString);


void __RPC_STUB IApcProcedure_get_HostString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_ProcedureScope_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [out][retval] */ APCPROCEDURESCOPE __RPC_FAR *pScope);


void __RPC_STUB IApcProcedure_get_ProcedureScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_HasParameters_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbHasParameters);


void __RPC_STUB IApcProcedure_get_HasParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Empty_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbEmpty);


void __RPC_STUB IApcProcedure_get_Empty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Type_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [out][retval] */ APCPROCEDURETYPE __RPC_FAR *pType);


void __RPC_STUB IApcProcedure_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_ProcKind_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [out][retval] */ APCPROCKIND __RPC_FAR *pProcKind);


void __RPC_STUB IApcProcedure_get_ProcKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcProcedure_put_Tag_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcProcedure_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Tag_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcProcedure_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_Apc_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcProcedure_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_StartLine_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pStartLine);


void __RPC_STUB IApcProcedure_get_StartLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcProcedure_get_EndLine_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pEndLine);


void __RPC_STUB IApcProcedure_get_EndLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProcedure_Run_Proxy( 
    IApcProcedure __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments,
    /* [retval][out] */ VARIANT __RPC_FAR *pReturnValue);


void __RPC_STUB IApcProcedure_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProcedure_ViewCode_Proxy( 
    IApcProcedure __RPC_FAR * This);


void __RPC_STUB IApcProcedure_ViewCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcProcedure_Delete_Proxy( 
    IApcProcedure __RPC_FAR * This);


void __RPC_STUB IApcProcedure_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcProcedure_INTERFACE_DEFINED__ */


#ifndef __IApcCategories_INTERFACE_DEFINED__
#define __IApcCategories_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcCategories
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcCategories;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcCategories : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ short __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcCategory __RPC_FAR *__RPC_FAR *ppCategory) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR PropertyName,
            /* [in] */ APCPROPERTYCATEGORY Category,
            /* [optional][in] */ BSTR CategoryName,
            /* [retval][out] */ IApcCategory __RPC_FAR *__RPC_FAR *ppCategory) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcCategoriesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcCategories __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcCategories __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcCategories __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcCategories __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcCategories __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcCategory __RPC_FAR *__RPC_FAR *ppCategory);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcCategories __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcCategories __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcCategories __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcCategories __RPC_FAR * This,
            /* [in] */ BSTR PropertyName,
            /* [in] */ APCPROPERTYCATEGORY Category,
            /* [optional][in] */ BSTR CategoryName,
            /* [retval][out] */ IApcCategory __RPC_FAR *__RPC_FAR *ppCategory);
        
        END_INTERFACE
    } IApcCategoriesVtbl;

    interface IApcCategories
    {
        CONST_VTBL struct IApcCategoriesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcCategories_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcCategories_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcCategories_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcCategories_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcCategories_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcCategories_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcCategories_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcCategories_get_Parent(This,ppParent)	\
    (This)->lpVtbl -> get_Parent(This,ppParent)

#define IApcCategories_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcCategories_get_Item(This,Index,ppCategory)	\
    (This)->lpVtbl -> get_Item(This,Index,ppCategory)

#define IApcCategories_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcCategories_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcCategories_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcCategories_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcCategories_Add(This,PropertyName,Category,CategoryName,ppCategory)	\
    (This)->lpVtbl -> Add(This,PropertyName,Category,CategoryName,ppCategory)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategories_get_Parent_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent);


void __RPC_STUB IApcCategories_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategories_get_Count_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pCount);


void __RPC_STUB IApcCategories_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcCategories_get_Item_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcCategory __RPC_FAR *__RPC_FAR *ppCategory);


void __RPC_STUB IApcCategories_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcCategories_get_NewEnum_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcCategories_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcCategories_put_Tag_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcCategories_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategories_get_Tag_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcCategories_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategories_get_Apc_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcCategories_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcCategories_Add_Proxy( 
    IApcCategories __RPC_FAR * This,
    /* [in] */ BSTR PropertyName,
    /* [in] */ APCPROPERTYCATEGORY Category,
    /* [optional][in] */ BSTR CategoryName,
    /* [retval][out] */ IApcCategory __RPC_FAR *__RPC_FAR *ppCategory);


void __RPC_STUB IApcCategories_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcCategories_INTERFACE_DEFINED__ */


#ifndef __IApcCategory_INTERFACE_DEFINED__
#define __IApcCategory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcCategory
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcCategory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcCategory : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Category( 
            /* [retval][out] */ APCPROPERTYCATEGORY __RPC_FAR *pCategory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CategoryName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCategoryName) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_DispatchID( 
            /* [retval][out] */ DISPID __RPC_FAR *pDispatchID) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppCategories) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcCategoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcCategory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcCategory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcCategory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcCategory __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcCategory __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcCategory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcCategory __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Category )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ APCPROPERTYCATEGORY __RPC_FAR *pCategory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CategoryName )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCategoryName);
        
        /* [helpcontext][helpstring][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DispatchID )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ DISPID __RPC_FAR *pDispatchID);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppCategories);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcCategory __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcCategory __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcCategory __RPC_FAR * This);
        
        END_INTERFACE
    } IApcCategoryVtbl;

    interface IApcCategory
    {
        CONST_VTBL struct IApcCategoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcCategory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcCategory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcCategory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcCategory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcCategory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcCategory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcCategory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcCategory_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcCategory_get_Category(This,pCategory)	\
    (This)->lpVtbl -> get_Category(This,pCategory)

#define IApcCategory_get_CategoryName(This,pbstrCategoryName)	\
    (This)->lpVtbl -> get_CategoryName(This,pbstrCategoryName)

#define IApcCategory_get_DispatchID(This,pDispatchID)	\
    (This)->lpVtbl -> get_DispatchID(This,pDispatchID)

#define IApcCategory_get_Parent(This,ppCategories)	\
    (This)->lpVtbl -> get_Parent(This,ppCategories)

#define IApcCategory_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcCategory_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcCategory_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcCategory_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_Name_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcCategory_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_Category_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ APCPROPERTYCATEGORY __RPC_FAR *pCategory);


void __RPC_STUB IApcCategory_get_Category_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_CategoryName_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCategoryName);


void __RPC_STUB IApcCategory_get_CategoryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_DispatchID_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ DISPID __RPC_FAR *pDispatchID);


void __RPC_STUB IApcCategory_get_DispatchID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_Parent_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ IApcCategories __RPC_FAR *__RPC_FAR *ppCategories);


void __RPC_STUB IApcCategory_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcCategory_put_Tag_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcCategory_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_Tag_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcCategory_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcCategory_get_Apc_Proxy( 
    IApcCategory __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcCategory_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcCategory_Delete_Proxy( 
    IApcCategory __RPC_FAR * This);


void __RPC_STUB IApcCategory_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcCategory_INTERFACE_DEFINED__ */


#ifndef __IApcMiniBitmaps_INTERFACE_DEFINED__
#define __IApcMiniBitmaps_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcMiniBitmaps
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcMiniBitmaps;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcMiniBitmaps : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ short __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcMiniBitmap __RPC_FAR *__RPC_FAR *ppMiniBitmap) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR ClassName,
            /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *MiniBitmap,
            /* [defaultvalue][in] */ /* external definition not present */ OLE_COLOR BackColor,
            /* [retval][out] */ IApcMiniBitmap __RPC_FAR *__RPC_FAR *ppMiniBitmap) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcMiniBitmapsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcMiniBitmaps __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcMiniBitmaps __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcMiniBitmap __RPC_FAR *__RPC_FAR *ppMiniBitmap);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcMiniBitmaps __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *MiniBitmap,
            /* [defaultvalue][in] */ /* external definition not present */ OLE_COLOR BackColor,
            /* [retval][out] */ IApcMiniBitmap __RPC_FAR *__RPC_FAR *ppMiniBitmap);
        
        END_INTERFACE
    } IApcMiniBitmapsVtbl;

    interface IApcMiniBitmaps
    {
        CONST_VTBL struct IApcMiniBitmapsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcMiniBitmaps_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcMiniBitmaps_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcMiniBitmaps_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcMiniBitmaps_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcMiniBitmaps_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcMiniBitmaps_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcMiniBitmaps_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcMiniBitmaps_get_Parent(This,ppApc)	\
    (This)->lpVtbl -> get_Parent(This,ppApc)

#define IApcMiniBitmaps_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcMiniBitmaps_get_Item(This,Index,ppMiniBitmap)	\
    (This)->lpVtbl -> get_Item(This,Index,ppMiniBitmap)

#define IApcMiniBitmaps_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcMiniBitmaps_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcMiniBitmaps_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcMiniBitmaps_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcMiniBitmaps_Add(This,ClassName,MiniBitmap,BackColor,ppMiniBitmap)	\
    (This)->lpVtbl -> Add(This,ClassName,MiniBitmap,BackColor,ppMiniBitmap)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_get_Parent_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcMiniBitmaps_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_get_Count_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pCount);


void __RPC_STUB IApcMiniBitmaps_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_get_Item_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcMiniBitmap __RPC_FAR *__RPC_FAR *ppMiniBitmap);


void __RPC_STUB IApcMiniBitmaps_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_get_NewEnum_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcMiniBitmaps_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_put_Tag_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcMiniBitmaps_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_get_Tag_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcMiniBitmaps_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_get_Apc_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcMiniBitmaps_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmaps_Add_Proxy( 
    IApcMiniBitmaps __RPC_FAR * This,
    /* [in] */ BSTR ClassName,
    /* [in] */ /* external definition not present */ IPictureDisp __RPC_FAR *MiniBitmap,
    /* [defaultvalue][in] */ /* external definition not present */ OLE_COLOR BackColor,
    /* [retval][out] */ IApcMiniBitmap __RPC_FAR *__RPC_FAR *ppMiniBitmap);


void __RPC_STUB IApcMiniBitmaps_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcMiniBitmaps_INTERFACE_DEFINED__ */


#ifndef __IApcMiniBitmap_INTERFACE_DEFINED__
#define __IApcMiniBitmap_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcMiniBitmap
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcMiniBitmap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcMiniBitmap : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppMiniBitMap) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcMiniBitmaps __RPC_FAR *__RPC_FAR *ppMiniBitmaps) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClassName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrClassName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ /* external definition not present */ OLE_COLOR BackColor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcMiniBitmapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcMiniBitmap __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcMiniBitmap __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Picture )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppMiniBitMap);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [retval][out] */ IApcMiniBitmaps __RPC_FAR *__RPC_FAR *ppMiniBitmaps);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassName )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrClassName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IApcMiniBitmap __RPC_FAR * This,
            /* [in] */ /* external definition not present */ OLE_COLOR BackColor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcMiniBitmap __RPC_FAR * This);
        
        END_INTERFACE
    } IApcMiniBitmapVtbl;

    interface IApcMiniBitmap
    {
        CONST_VTBL struct IApcMiniBitmapVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcMiniBitmap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcMiniBitmap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcMiniBitmap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcMiniBitmap_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcMiniBitmap_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcMiniBitmap_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcMiniBitmap_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcMiniBitmap_get_Picture(This,ppMiniBitMap)	\
    (This)->lpVtbl -> get_Picture(This,ppMiniBitMap)

#define IApcMiniBitmap_get_Parent(This,ppMiniBitmaps)	\
    (This)->lpVtbl -> get_Parent(This,ppMiniBitmaps)

#define IApcMiniBitmap_get_ClassName(This,pbstrClassName)	\
    (This)->lpVtbl -> get_ClassName(This,pbstrClassName)

#define IApcMiniBitmap_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcMiniBitmap_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcMiniBitmap_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcMiniBitmap_get_BackColor(This,pBackColor)	\
    (This)->lpVtbl -> get_BackColor(This,pBackColor)

#define IApcMiniBitmap_put_BackColor(This,BackColor)	\
    (This)->lpVtbl -> put_BackColor(This,BackColor)

#define IApcMiniBitmap_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_get_Picture_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ IPictureDisp __RPC_FAR *__RPC_FAR *ppMiniBitMap);


void __RPC_STUB IApcMiniBitmap_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_get_Parent_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [retval][out] */ IApcMiniBitmaps __RPC_FAR *__RPC_FAR *ppMiniBitmaps);


void __RPC_STUB IApcMiniBitmap_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_get_ClassName_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrClassName);


void __RPC_STUB IApcMiniBitmap_get_ClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_put_Tag_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcMiniBitmap_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_get_Tag_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcMiniBitmap_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_get_Apc_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcMiniBitmap_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_get_BackColor_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ OLE_COLOR __RPC_FAR *pBackColor);


void __RPC_STUB IApcMiniBitmap_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_put_BackColor_Proxy( 
    IApcMiniBitmap __RPC_FAR * This,
    /* [in] */ /* external definition not present */ OLE_COLOR BackColor);


void __RPC_STUB IApcMiniBitmap_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcMiniBitmap_Delete_Proxy( 
    IApcMiniBitmap __RPC_FAR * This);


void __RPC_STUB IApcMiniBitmap_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcMiniBitmap_INTERFACE_DEFINED__ */


#ifndef __IApcRecorder_INTERFACE_DEFINED__
#define __IApcRecorder_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcRecorder
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcRecorder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcRecorder : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [out][retval] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MacroName( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrMacroName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProjectItem( 
            /* [out][retval] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Recording( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbRecording) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Record( 
            /* [in] */ BSTR Text) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RecordLine( 
            /* [optional][in] */ BSTR Text) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Start( 
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Destination,
            /* [optional][in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetUndoMarking( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Undo( 
            /* [defaultvalue][in] */ long NumberOfLevels) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UndoCount( 
            /* [retval][out] */ long __RPC_FAR *pUndoCount) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Paused( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbPaused) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcRecorderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcRecorder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcRecorder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcRecorder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcRecorder __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcRecorder __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcRecorder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcRecorder __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcRecorder __RPC_FAR * This,
            /* [out][retval] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MacroName )( 
            IApcRecorder __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrMacroName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectItem )( 
            IApcRecorder __RPC_FAR * This,
            /* [out][retval] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Recording )( 
            IApcRecorder __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbRecording);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcRecorder __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcRecorder __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcRecorder __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Record )( 
            IApcRecorder __RPC_FAR * This,
            /* [in] */ BSTR Text);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RecordLine )( 
            IApcRecorder __RPC_FAR * This,
            /* [optional][in] */ BSTR Text);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IApcRecorder __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IApcRecorder __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IApcRecorder __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            IApcRecorder __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IApcRecorder __RPC_FAR * This,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Destination,
            /* [optional][in] */ BSTR Name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUndoMarking )( 
            IApcRecorder __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Undo )( 
            IApcRecorder __RPC_FAR * This,
            /* [defaultvalue][in] */ long NumberOfLevels);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UndoCount )( 
            IApcRecorder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pUndoCount);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Paused )( 
            IApcRecorder __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbPaused);
        
        END_INTERFACE
    } IApcRecorderVtbl;

    interface IApcRecorder
    {
        CONST_VTBL struct IApcRecorderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcRecorder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcRecorder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcRecorder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcRecorder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcRecorder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcRecorder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcRecorder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcRecorder_get_Parent(This,ppApc)	\
    (This)->lpVtbl -> get_Parent(This,ppApc)

#define IApcRecorder_get_MacroName(This,pbstrMacroName)	\
    (This)->lpVtbl -> get_MacroName(This,pbstrMacroName)

#define IApcRecorder_get_ProjectItem(This,ppProjectItem)	\
    (This)->lpVtbl -> get_ProjectItem(This,ppProjectItem)

#define IApcRecorder_get_Recording(This,pbRecording)	\
    (This)->lpVtbl -> get_Recording(This,pbRecording)

#define IApcRecorder_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcRecorder_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcRecorder_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcRecorder_Record(This,Text)	\
    (This)->lpVtbl -> Record(This,Text)

#define IApcRecorder_RecordLine(This,Text)	\
    (This)->lpVtbl -> RecordLine(This,Text)

#define IApcRecorder_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IApcRecorder_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define IApcRecorder_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IApcRecorder_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#define IApcRecorder_Start(This,Destination,Name)	\
    (This)->lpVtbl -> Start(This,Destination,Name)

#define IApcRecorder_SetUndoMarking(This)	\
    (This)->lpVtbl -> SetUndoMarking(This)

#define IApcRecorder_Undo(This,NumberOfLevels)	\
    (This)->lpVtbl -> Undo(This,NumberOfLevels)

#define IApcRecorder_get_UndoCount(This,pUndoCount)	\
    (This)->lpVtbl -> get_UndoCount(This,pUndoCount)

#define IApcRecorder_get_Paused(This,pbPaused)	\
    (This)->lpVtbl -> get_Paused(This,pbPaused)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_Parent_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [out][retval] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcRecorder_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_MacroName_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrMacroName);


void __RPC_STUB IApcRecorder_get_MacroName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_ProjectItem_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [out][retval] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcRecorder_get_ProjectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_Recording_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbRecording);


void __RPC_STUB IApcRecorder_get_Recording_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcRecorder_put_Tag_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcRecorder_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_Tag_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcRecorder_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_Apc_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcRecorder_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Record_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [in] */ BSTR Text);


void __RPC_STUB IApcRecorder_Record_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_RecordLine_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [optional][in] */ BSTR Text);


void __RPC_STUB IApcRecorder_RecordLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Stop_Proxy( 
    IApcRecorder __RPC_FAR * This);


void __RPC_STUB IApcRecorder_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Cancel_Proxy( 
    IApcRecorder __RPC_FAR * This);


void __RPC_STUB IApcRecorder_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Pause_Proxy( 
    IApcRecorder __RPC_FAR * This);


void __RPC_STUB IApcRecorder_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Resume_Proxy( 
    IApcRecorder __RPC_FAR * This);


void __RPC_STUB IApcRecorder_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Start_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *Destination,
    /* [optional][in] */ BSTR Name);


void __RPC_STUB IApcRecorder_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_SetUndoMarking_Proxy( 
    IApcRecorder __RPC_FAR * This);


void __RPC_STUB IApcRecorder_SetUndoMarking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRecorder_Undo_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [defaultvalue][in] */ long NumberOfLevels);


void __RPC_STUB IApcRecorder_Undo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_UndoCount_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pUndoCount);


void __RPC_STUB IApcRecorder_get_UndoCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRecorder_get_Paused_Proxy( 
    IApcRecorder __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbPaused);


void __RPC_STUB IApcRecorder_get_Paused_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcRecorder_INTERFACE_DEFINED__ */


#ifndef __IApcScopes_INTERFACE_DEFINED__
#define __IApcScopes_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcScopes
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcScopes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcScopes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcScope __RPC_FAR *__RPC_FAR *ppScope) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MacrosDialog( 
            /* [retval][out] */ IApcMacrosDialog __RPC_FAR *__RPC_FAR *ppMacrosDialog) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent) = 0;
        
        virtual /* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR ScopeName,
            /* [optional][in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ProjectItems,
            /* [retval][out] */ IApcScope __RPC_FAR *__RPC_FAR *ppScope) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CallMacro( 
            /* [in] */ BSTR MacroName) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcScopesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcScopes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcScopes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcScopes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcScopes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcScopes __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcScope __RPC_FAR *__RPC_FAR *ppScope);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MacrosDialog )( 
            IApcScopes __RPC_FAR * This,
            /* [retval][out] */ IApcMacrosDialog __RPC_FAR *__RPC_FAR *ppMacrosDialog);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcScopes __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcScopes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent);
        
        /* [vararg][helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ BSTR ScopeName,
            /* [optional][in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ProjectItems,
            /* [retval][out] */ IApcScope __RPC_FAR *__RPC_FAR *ppScope);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallMacro )( 
            IApcScopes __RPC_FAR * This,
            /* [in] */ BSTR MacroName);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcScopes __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        END_INTERFACE
    } IApcScopesVtbl;

    interface IApcScopes
    {
        CONST_VTBL struct IApcScopesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcScopes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcScopes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcScopes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcScopes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcScopes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcScopes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcScopes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcScopes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcScopes_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcScopes_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcScopes_get_Item(This,Index,ppScope)	\
    (This)->lpVtbl -> get_Item(This,Index,ppScope)

#define IApcScopes_get_MacrosDialog(This,ppMacrosDialog)	\
    (This)->lpVtbl -> get_MacrosDialog(This,ppMacrosDialog)

#define IApcScopes_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcScopes_get_Parent(This,ppParent)	\
    (This)->lpVtbl -> get_Parent(This,ppParent)

#define IApcScopes_Add(This,ScopeName,ProjectItems,ppScope)	\
    (This)->lpVtbl -> Add(This,ScopeName,ProjectItems,ppScope)

#define IApcScopes_CallMacro(This,MacroName)	\
    (This)->lpVtbl -> CallMacro(This,MacroName)

#define IApcScopes_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_Count_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcScopes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcScopes_put_Tag_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcScopes_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_Tag_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcScopes_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_Item_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcScope __RPC_FAR *__RPC_FAR *ppScope);


void __RPC_STUB IApcScopes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_MacrosDialog_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [retval][out] */ IApcMacrosDialog __RPC_FAR *__RPC_FAR *ppMacrosDialog);


void __RPC_STUB IApcScopes_get_MacrosDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_Apc_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcScopes_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_Parent_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent);


void __RPC_STUB IApcScopes_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [vararg][helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcScopes_Add_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [in] */ BSTR ScopeName,
    /* [optional][in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ProjectItems,
    /* [retval][out] */ IApcScope __RPC_FAR *__RPC_FAR *ppScope);


void __RPC_STUB IApcScopes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcScopes_CallMacro_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [in] */ BSTR MacroName);


void __RPC_STUB IApcScopes_CallMacro_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcScopes_get_NewEnum_Proxy( 
    IApcScopes __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcScopes_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcScopes_INTERFACE_DEFINED__ */


#ifndef __IApcScope_INTERFACE_DEFINED__
#define __IApcScope_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcScope
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcScope;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcScope : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProjectItems( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppProjectItems) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ProjectItems( 
            /* [in] */ IDispatch __RPC_FAR *pProjectItems) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_ProjectItems( 
            /* [in] */ IDispatch __RPC_FAR *pProjectItems) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcScopeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcScope __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcScope __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcScope __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcScope __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ BSTR NewName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectItems )( 
            IApcScope __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppProjectItems);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProjectItems )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pProjectItems);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcScope __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcScope __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcScope __RPC_FAR * This,
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_ProjectItems )( 
            IApcScope __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pProjectItems);
        
        END_INTERFACE
    } IApcScopeVtbl;

    interface IApcScope
    {
        CONST_VTBL struct IApcScopeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcScope_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcScope_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcScope_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcScope_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcScope_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcScope_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcScope_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcScope_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcScope_put_Name(This,NewName)	\
    (This)->lpVtbl -> put_Name(This,NewName)

#define IApcScope_get_ProjectItems(This,ppProjectItems)	\
    (This)->lpVtbl -> get_ProjectItems(This,ppProjectItems)

#define IApcScope_put_ProjectItems(This,pProjectItems)	\
    (This)->lpVtbl -> put_ProjectItems(This,pProjectItems)

#define IApcScope_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcScope_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcScope_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcScope_get_Parent(This,ppScopes)	\
    (This)->lpVtbl -> get_Parent(This,ppScopes)

#define IApcScope_putref_ProjectItems(This,pProjectItems)	\
    (This)->lpVtbl -> putref_ProjectItems(This,pProjectItems)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcScope_get_Name_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcScope_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcScope_put_Name_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB IApcScope_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScope_get_ProjectItems_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppProjectItems);


void __RPC_STUB IApcScope_get_ProjectItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcScope_put_ProjectItems_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pProjectItems);


void __RPC_STUB IApcScope_put_ProjectItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcScope_put_Tag_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcScope_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScope_get_Tag_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcScope_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScope_get_Apc_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcScope_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcScope_get_Parent_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppScopes);


void __RPC_STUB IApcScope_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE IApcScope_putref_ProjectItems_Proxy( 
    IApcScope __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pProjectItems);


void __RPC_STUB IApcScope_putref_ProjectItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcScope_INTERFACE_DEFINED__ */


#ifndef __IApcMacrosDialog_INTERFACE_DEFINED__
#define __IApcMacrosDialog_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcMacrosDialog
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcMacrosDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcMacrosDialog : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DialogTitle( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DialogTitle( 
            /* [in] */ BSTR NewDialogTitle) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HelpFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HelpFile( 
            /* [in] */ BSTR FileName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HelpContextID( 
            /* [retval][out] */ long __RPC_FAR *pContextID) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HelpContextID( 
            /* [in] */ long ContextID) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppParent) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long Left) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *pLeft) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long Top) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *pTop) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartUpPosition( 
            /* [in] */ APCDIALOGSTARTUPPOSITION Position) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartUpPosition( 
            /* [retval][out] */ APCDIALOGSTARTUPPOSITION __RPC_FAR *pPosition) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ParentWindow( 
            /* [retval][out] */ long __RPC_FAR *phWnd) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ParentWindow( 
            /* [in] */ long hWnd) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcMacrosDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcMacrosDialog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcMacrosDialog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DialogTitle )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DialogTitle )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ BSTR NewDialogTitle);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFile )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ BSTR FileName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContextID )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pContextID);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpContextID )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ long ContextID);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppParent);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ long Left);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pLeft);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ long Top);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pTop);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartUpPosition )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ APCDIALOGSTARTUPPOSITION Position);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartUpPosition )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ APCDIALOGSTARTUPPOSITION __RPC_FAR *pPosition);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParentWindow )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *phWnd);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ParentWindow )( 
            IApcMacrosDialog __RPC_FAR * This,
            /* [in] */ long hWnd);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IApcMacrosDialog __RPC_FAR * This);
        
        END_INTERFACE
    } IApcMacrosDialogVtbl;

    interface IApcMacrosDialog
    {
        CONST_VTBL struct IApcMacrosDialogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcMacrosDialog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcMacrosDialog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcMacrosDialog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcMacrosDialog_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcMacrosDialog_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcMacrosDialog_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcMacrosDialog_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcMacrosDialog_get_DialogTitle(This,pbstrTitle)	\
    (This)->lpVtbl -> get_DialogTitle(This,pbstrTitle)

#define IApcMacrosDialog_put_DialogTitle(This,NewDialogTitle)	\
    (This)->lpVtbl -> put_DialogTitle(This,NewDialogTitle)

#define IApcMacrosDialog_get_HelpFile(This,pbstrName)	\
    (This)->lpVtbl -> get_HelpFile(This,pbstrName)

#define IApcMacrosDialog_put_HelpFile(This,FileName)	\
    (This)->lpVtbl -> put_HelpFile(This,FileName)

#define IApcMacrosDialog_get_HelpContextID(This,pContextID)	\
    (This)->lpVtbl -> get_HelpContextID(This,pContextID)

#define IApcMacrosDialog_put_HelpContextID(This,ContextID)	\
    (This)->lpVtbl -> put_HelpContextID(This,ContextID)

#define IApcMacrosDialog_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcMacrosDialog_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcMacrosDialog_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcMacrosDialog_get_Parent(This,ppParent)	\
    (This)->lpVtbl -> get_Parent(This,ppParent)

#define IApcMacrosDialog_put_Left(This,Left)	\
    (This)->lpVtbl -> put_Left(This,Left)

#define IApcMacrosDialog_get_Left(This,pLeft)	\
    (This)->lpVtbl -> get_Left(This,pLeft)

#define IApcMacrosDialog_put_Top(This,Top)	\
    (This)->lpVtbl -> put_Top(This,Top)

#define IApcMacrosDialog_get_Top(This,pTop)	\
    (This)->lpVtbl -> get_Top(This,pTop)

#define IApcMacrosDialog_put_StartUpPosition(This,Position)	\
    (This)->lpVtbl -> put_StartUpPosition(This,Position)

#define IApcMacrosDialog_get_StartUpPosition(This,pPosition)	\
    (This)->lpVtbl -> get_StartUpPosition(This,pPosition)

#define IApcMacrosDialog_get_ParentWindow(This,phWnd)	\
    (This)->lpVtbl -> get_ParentWindow(This,phWnd)

#define IApcMacrosDialog_put_ParentWindow(This,hWnd)	\
    (This)->lpVtbl -> put_ParentWindow(This,hWnd)

#define IApcMacrosDialog_Show(This)	\
    (This)->lpVtbl -> Show(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_DialogTitle_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTitle);


void __RPC_STUB IApcMacrosDialog_get_DialogTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_DialogTitle_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ BSTR NewDialogTitle);


void __RPC_STUB IApcMacrosDialog_put_DialogTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_HelpFile_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcMacrosDialog_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_HelpFile_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ BSTR FileName);


void __RPC_STUB IApcMacrosDialog_put_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_HelpContextID_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pContextID);


void __RPC_STUB IApcMacrosDialog_get_HelpContextID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_HelpContextID_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ long ContextID);


void __RPC_STUB IApcMacrosDialog_put_HelpContextID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_Tag_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcMacrosDialog_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_Tag_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcMacrosDialog_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_Apc_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcMacrosDialog_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_Parent_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ IApcScopes __RPC_FAR *__RPC_FAR *ppParent);


void __RPC_STUB IApcMacrosDialog_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_Left_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ long Left);


void __RPC_STUB IApcMacrosDialog_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_Left_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pLeft);


void __RPC_STUB IApcMacrosDialog_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_Top_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ long Top);


void __RPC_STUB IApcMacrosDialog_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_Top_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pTop);


void __RPC_STUB IApcMacrosDialog_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_StartUpPosition_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ APCDIALOGSTARTUPPOSITION Position);


void __RPC_STUB IApcMacrosDialog_put_StartUpPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_StartUpPosition_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ APCDIALOGSTARTUPPOSITION __RPC_FAR *pPosition);


void __RPC_STUB IApcMacrosDialog_get_StartUpPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_get_ParentWindow_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *phWnd);


void __RPC_STUB IApcMacrosDialog_get_ParentWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_put_ParentWindow_Proxy( 
    IApcMacrosDialog __RPC_FAR * This,
    /* [in] */ long hWnd);


void __RPC_STUB IApcMacrosDialog_put_ParentWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcMacrosDialog_Show_Proxy( 
    IApcMacrosDialog __RPC_FAR * This);


void __RPC_STUB IApcMacrosDialog_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcMacrosDialog_INTERFACE_DEFINED__ */


#ifndef __IApcStorage_INTERFACE_DEFINED__
#define __IApcStorage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcStorage
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcStorage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcStorage : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CreationDate( 
            /* [retval][out] */ DATE __RPC_FAR *pDate) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LastModifiedDate( 
            /* [retval][out] */ DATE __RPC_FAR *pDate) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_IStorage( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Storages( 
            /* [retval][out] */ VARIANT __RPC_FAR *pStorages) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Streams( 
            /* [retval][out] */ VARIANT __RPC_FAR *pStreams) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InMemoryStorageBytes( 
            /* [retval][out] */ VARIANT __RPC_FAR *pBytes) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetCreationDate( 
            /* [optional][in] */ BSTR Name,
            /* [in] */ DATE Date) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLastModifiedDate( 
            /* [optional][in] */ BSTR Name,
            /* [in] */ DATE Date) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateStream( 
            /* [in] */ BSTR StreamName,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppStream) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OpenStream( 
            /* [in] */ BSTR StreamName,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppStream) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateStorage( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OpenStorage( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [optional][in] */ BSTR Name,
            /* [in] */ IApcStorage __RPC_FAR *DestinationStorage,
            /* [optional][in] */ BSTR NewStorageName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [optional][in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [optional][in] */ BSTR Name,
            /* [in] */ IApcStorage __RPC_FAR *DestinationStorage,
            /* [optional][in] */ BSTR NewName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Commit( 
            /* [defaultvalue][in] */ VARIANT_BOOL ForceCommit) = 0;
        
        virtual /* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE Rollback( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rename( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcStorageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcStorage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcStorage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcStorage __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationDate )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pDate);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastModifiedDate )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pDate);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent);
        
        /* [helpcontext][helpstring][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IStorage )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Storages )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pStorages);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Streams )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pStreams);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InMemoryStorageBytes )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pBytes);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcStorage __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCreationDate )( 
            IApcStorage __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [in] */ DATE Date);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLastModifiedDate )( 
            IApcStorage __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [in] */ DATE Date);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStream )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ BSTR StreamName,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppStream);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStream )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ BSTR StreamName,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppStream);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStorage )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStorage )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            IApcStorage __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [in] */ IApcStorage __RPC_FAR *DestinationStorage,
            /* [optional][in] */ BSTR NewStorageName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcStorage __RPC_FAR * This,
            /* [optional][in] */ BSTR Name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IApcStorage __RPC_FAR * This,
            /* [optional][in] */ BSTR Name,
            /* [in] */ IApcStorage __RPC_FAR *DestinationStorage,
            /* [optional][in] */ BSTR NewName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IApcStorage __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL ForceCommit);
        
        /* [helpcontext][helpstring][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rollback )( 
            IApcStorage __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rename )( 
            IApcStorage __RPC_FAR * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName);
        
        END_INTERFACE
    } IApcStorageVtbl;

    interface IApcStorage
    {
        CONST_VTBL struct IApcStorageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcStorage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcStorage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcStorage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcStorage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcStorage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcStorage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcStorage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcStorage_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcStorage_get_CreationDate(This,pDate)	\
    (This)->lpVtbl -> get_CreationDate(This,pDate)

#define IApcStorage_get_LastModifiedDate(This,pDate)	\
    (This)->lpVtbl -> get_LastModifiedDate(This,pDate)

#define IApcStorage_get_Parent(This,ppParent)	\
    (This)->lpVtbl -> get_Parent(This,ppParent)

#define IApcStorage_get_IStorage(This,ppStorage)	\
    (This)->lpVtbl -> get_IStorage(This,ppStorage)

#define IApcStorage_get_Storages(This,pStorages)	\
    (This)->lpVtbl -> get_Storages(This,pStorages)

#define IApcStorage_get_Streams(This,pStreams)	\
    (This)->lpVtbl -> get_Streams(This,pStreams)

#define IApcStorage_get_InMemoryStorageBytes(This,pBytes)	\
    (This)->lpVtbl -> get_InMemoryStorageBytes(This,pBytes)

#define IApcStorage_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcStorage_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcStorage_SetCreationDate(This,Name,Date)	\
    (This)->lpVtbl -> SetCreationDate(This,Name,Date)

#define IApcStorage_SetLastModifiedDate(This,Name,Date)	\
    (This)->lpVtbl -> SetLastModifiedDate(This,Name,Date)

#define IApcStorage_CreateStream(This,StreamName,AccessMode,ppStream)	\
    (This)->lpVtbl -> CreateStream(This,StreamName,AccessMode,ppStream)

#define IApcStorage_OpenStream(This,StreamName,AccessMode,ppStream)	\
    (This)->lpVtbl -> OpenStream(This,StreamName,AccessMode,ppStream)

#define IApcStorage_CreateStorage(This,Name,AccessMode,ppStorage)	\
    (This)->lpVtbl -> CreateStorage(This,Name,AccessMode,ppStorage)

#define IApcStorage_OpenStorage(This,Name,AccessMode,ppStorage)	\
    (This)->lpVtbl -> OpenStorage(This,Name,AccessMode,ppStorage)

#define IApcStorage_Copy(This,Name,DestinationStorage,NewStorageName)	\
    (This)->lpVtbl -> Copy(This,Name,DestinationStorage,NewStorageName)

#define IApcStorage_Delete(This,Name)	\
    (This)->lpVtbl -> Delete(This,Name)

#define IApcStorage_Move(This,Name,DestinationStorage,NewName)	\
    (This)->lpVtbl -> Move(This,Name,DestinationStorage,NewName)

#define IApcStorage_Commit(This,ForceCommit)	\
    (This)->lpVtbl -> Commit(This,ForceCommit)

#define IApcStorage_Rollback(This)	\
    (This)->lpVtbl -> Rollback(This)

#define IApcStorage_Rename(This,OldName,NewName)	\
    (This)->lpVtbl -> Rename(This,OldName,NewName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_Name_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcStorage_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_CreationDate_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pDate);


void __RPC_STUB IApcStorage_get_CreationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_LastModifiedDate_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pDate);


void __RPC_STUB IApcStorage_get_LastModifiedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_Parent_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppParent);


void __RPC_STUB IApcStorage_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_IStorage_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcStorage_get_IStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_Storages_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pStorages);


void __RPC_STUB IApcStorage_get_Storages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_Streams_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pStreams);


void __RPC_STUB IApcStorage_get_Streams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_InMemoryStorageBytes_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pBytes);


void __RPC_STUB IApcStorage_get_InMemoryStorageBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcStorage_put_Tag_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcStorage_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStorage_get_Tag_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcStorage_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_SetCreationDate_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [in] */ DATE Date);


void __RPC_STUB IApcStorage_SetCreationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_SetLastModifiedDate_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [in] */ DATE Date);


void __RPC_STUB IApcStorage_SetLastModifiedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_CreateStream_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [in] */ BSTR StreamName,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppStream);


void __RPC_STUB IApcStorage_CreateStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_OpenStream_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [in] */ BSTR StreamName,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppStream);


void __RPC_STUB IApcStorage_OpenStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_CreateStorage_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcStorage_CreateStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_OpenStorage_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ APCACCESSMODE AccessMode,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcStorage_OpenStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_Copy_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [in] */ IApcStorage __RPC_FAR *DestinationStorage,
    /* [optional][in] */ BSTR NewStorageName);


void __RPC_STUB IApcStorage_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_Delete_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [optional][in] */ BSTR Name);


void __RPC_STUB IApcStorage_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_Move_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [optional][in] */ BSTR Name,
    /* [in] */ IApcStorage __RPC_FAR *DestinationStorage,
    /* [optional][in] */ BSTR NewName);


void __RPC_STUB IApcStorage_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_Commit_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL ForceCommit);


void __RPC_STUB IApcStorage_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden] */ HRESULT STDMETHODCALLTYPE IApcStorage_Rollback_Proxy( 
    IApcStorage __RPC_FAR * This);


void __RPC_STUB IApcStorage_Rollback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStorage_Rename_Proxy( 
    IApcStorage __RPC_FAR * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName);


void __RPC_STUB IApcStorage_Rename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcStorage_INTERFACE_DEFINED__ */


#ifndef __IApcStream_INTERFACE_DEFINED__
#define __IApcStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcStream
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcStream : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ long __RPC_FAR *pSize) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_IStream( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStream) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ long SeekPosition) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ long __RPC_FAR *pSeekPosition) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [retval][out] */ VARIANT __RPC_FAR *pData) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Put( 
            /* [in] */ VARIANT __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [in] */ IApcStream __RPC_FAR *DestinationStream) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppClonedStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSize);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);
        
        /* [helpcontext][helpstring][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IStream )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStream);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ long SeekPosition);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSeekPosition);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pData);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Value);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            IApcStream __RPC_FAR * This,
            /* [in] */ IApcStream __RPC_FAR *DestinationStream);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IApcStream __RPC_FAR * This,
            /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppClonedStream);
        
        END_INTERFACE
    } IApcStreamVtbl;

    interface IApcStream
    {
        CONST_VTBL struct IApcStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcStream_get_Size(This,pSize)	\
    (This)->lpVtbl -> get_Size(This,pSize)

#define IApcStream_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IApcStream_get_Parent(This,ppStorage)	\
    (This)->lpVtbl -> get_Parent(This,ppStorage)

#define IApcStream_get_IStream(This,ppStream)	\
    (This)->lpVtbl -> get_IStream(This,ppStream)

#define IApcStream_put_Position(This,SeekPosition)	\
    (This)->lpVtbl -> put_Position(This,SeekPosition)

#define IApcStream_get_Position(This,pSeekPosition)	\
    (This)->lpVtbl -> get_Position(This,pSeekPosition)

#define IApcStream_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcStream_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcStream_Get(This,pData)	\
    (This)->lpVtbl -> Get(This,pData)

#define IApcStream_Put(This,Value)	\
    (This)->lpVtbl -> Put(This,Value)

#define IApcStream_Copy(This,DestinationStream)	\
    (This)->lpVtbl -> Copy(This,DestinationStream)

#define IApcStream_Clone(This,ppClonedStream)	\
    (This)->lpVtbl -> Clone(This,ppClonedStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStream_get_Size_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSize);


void __RPC_STUB IApcStream_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcStream_get_Name_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IApcStream_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStream_get_Parent_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ IApcStorage __RPC_FAR *__RPC_FAR *ppStorage);


void __RPC_STUB IApcStream_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][propget] */ HRESULT STDMETHODCALLTYPE IApcStream_get_IStream_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppStream);


void __RPC_STUB IApcStream_get_IStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcStream_put_Position_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [in] */ long SeekPosition);


void __RPC_STUB IApcStream_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStream_get_Position_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSeekPosition);


void __RPC_STUB IApcStream_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcStream_put_Tag_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcStream_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcStream_get_Tag_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcStream_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStream_Get_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pData);


void __RPC_STUB IApcStream_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStream_Put_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *Value);


void __RPC_STUB IApcStream_Put_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStream_Copy_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [in] */ IApcStream __RPC_FAR *DestinationStream);


void __RPC_STUB IApcStream_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcStream_Clone_Proxy( 
    IApcStream __RPC_FAR * This,
    /* [retval][out] */ IApcStream __RPC_FAR *__RPC_FAR *ppClonedStream);


void __RPC_STUB IApcStream_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcStream_INTERFACE_DEFINED__ */


#ifndef __IApcRequiredClasses_INTERFACE_DEFINED__
#define __IApcRequiredClasses_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcRequiredClasses
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][restricted][uuid] */ 



EXTERN_C const IID IID_IApcRequiredClasses;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcRequiredClasses : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemByClsid( 
            /* [in] */ REFCLSID clsid,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Clsid,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ REFCLSID Clsid,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcRequiredClassesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcRequiredClasses __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcRequiredClasses __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemByClsid )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ REFCLSID clsid,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ BSTR Clsid,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_Add )( 
            IApcRequiredClasses __RPC_FAR * This,
            /* [in] */ REFCLSID Clsid,
            /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);
        
        END_INTERFACE
    } IApcRequiredClassesVtbl;

    interface IApcRequiredClasses
    {
        CONST_VTBL struct IApcRequiredClassesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcRequiredClasses_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcRequiredClasses_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcRequiredClasses_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcRequiredClasses_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcRequiredClasses_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcRequiredClasses_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcRequiredClasses_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcRequiredClasses_get_Parent(This,ppProjectItem)	\
    (This)->lpVtbl -> get_Parent(This,ppProjectItem)

#define IApcRequiredClasses_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcRequiredClasses_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcRequiredClasses_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcRequiredClasses_get_Item(This,Index,ppRequiredClass)	\
    (This)->lpVtbl -> get_Item(This,Index,ppRequiredClass)

#define IApcRequiredClasses_get_ItemByClsid(This,clsid,ppRequiredClass)	\
    (This)->lpVtbl -> get_ItemByClsid(This,clsid,ppRequiredClass)

#define IApcRequiredClasses_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcRequiredClasses_Add(This,Clsid,ppRequiredClass)	\
    (This)->lpVtbl -> Add(This,Clsid,ppRequiredClass)

#define IApcRequiredClasses__Add(This,Clsid,ppRequiredClass)	\
    (This)->lpVtbl -> _Add(This,Clsid,ppRequiredClass)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_get_Parent_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcRequiredClasses_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_get_Count_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcRequiredClasses_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_put_Tag_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcRequiredClasses_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_get_Tag_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcRequiredClasses_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_get_Item_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);


void __RPC_STUB IApcRequiredClasses_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_get_ItemByClsid_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [in] */ REFCLSID clsid,
    /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);


void __RPC_STUB IApcRequiredClasses_get_ItemByClsid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_get_NewEnum_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcRequiredClasses_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses_Add_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [in] */ BSTR Clsid,
    /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);


void __RPC_STUB IApcRequiredClasses_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRequiredClasses__Add_Proxy( 
    IApcRequiredClasses __RPC_FAR * This,
    /* [in] */ REFCLSID Clsid,
    /* [retval][out] */ IApcRequiredClass __RPC_FAR *__RPC_FAR *ppRequiredClass);


void __RPC_STUB IApcRequiredClasses__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcRequiredClasses_INTERFACE_DEFINED__ */


#ifndef __IApcRequiredClass_INTERFACE_DEFINED__
#define __IApcRequiredClass_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcRequiredClass
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][restricted][uuid] */ 



EXTERN_C const IID IID_IApcRequiredClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcRequiredClass : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcRequiredClasses __RPC_FAR *__RPC_FAR *ppRequiredClasses) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClassObject( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppClassFactory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TypeLibrary( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppTypeLibrary) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ REFIID riid,
            /* [defaultvalue][in] */ IUnknown __RPC_FAR *pOuter,
            /* [retval][out] */ void __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcRequiredClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcRequiredClass __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcRequiredClass __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [retval][out] */ IApcRequiredClasses __RPC_FAR *__RPC_FAR *ppRequiredClasses);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassObject )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppClassFactory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TypeLibrary )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppTypeLibrary);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcRequiredClass __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IApcRequiredClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [defaultvalue][in] */ IUnknown __RPC_FAR *pOuter,
            /* [retval][out] */ void __RPC_FAR *__RPC_FAR *ppObject);
        
        END_INTERFACE
    } IApcRequiredClassVtbl;

    interface IApcRequiredClass
    {
        CONST_VTBL struct IApcRequiredClassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcRequiredClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcRequiredClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcRequiredClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcRequiredClass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcRequiredClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcRequiredClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcRequiredClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcRequiredClass_get_Parent(This,ppRequiredClasses)	\
    (This)->lpVtbl -> get_Parent(This,ppRequiredClasses)

#define IApcRequiredClass_get_ClassObject(This,ppClassFactory)	\
    (This)->lpVtbl -> get_ClassObject(This,ppClassFactory)

#define IApcRequiredClass_get_TypeLibrary(This,ppTypeLibrary)	\
    (This)->lpVtbl -> get_TypeLibrary(This,ppTypeLibrary)

#define IApcRequiredClass_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcRequiredClass_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcRequiredClass_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IApcRequiredClass_Create(This,riid,pOuter,ppObject)	\
    (This)->lpVtbl -> Create(This,riid,pOuter,ppObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_get_Parent_Proxy( 
    IApcRequiredClass __RPC_FAR * This,
    /* [retval][out] */ IApcRequiredClasses __RPC_FAR *__RPC_FAR *ppRequiredClasses);


void __RPC_STUB IApcRequiredClass_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_get_ClassObject_Proxy( 
    IApcRequiredClass __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppClassFactory);


void __RPC_STUB IApcRequiredClass_get_ClassObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_get_TypeLibrary_Proxy( 
    IApcRequiredClass __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppTypeLibrary);


void __RPC_STUB IApcRequiredClass_get_TypeLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_put_Tag_Proxy( 
    IApcRequiredClass __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcRequiredClass_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_get_Tag_Proxy( 
    IApcRequiredClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcRequiredClass_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_Delete_Proxy( 
    IApcRequiredClass __RPC_FAR * This);


void __RPC_STUB IApcRequiredClass_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcRequiredClass_Create_Proxy( 
    IApcRequiredClass __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [defaultvalue][in] */ IUnknown __RPC_FAR *pOuter,
    /* [retval][out] */ void __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IApcRequiredClass_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcRequiredClass_INTERFACE_DEFINED__ */


#ifndef __IApcExtender_INTERFACE_DEFINED__
#define __IApcExtender_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcExtender
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][uuid] */ 



EXTERN_C const IID IID_IApcExtender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcExtender : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Object( 
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Index( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcExtenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcExtender __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcExtender __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcExtender __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcExtender __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcExtender __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcExtender __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcExtender __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApcExtender __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IApcExtender __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Object )( 
            IApcExtender __RPC_FAR * This,
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcExtender __RPC_FAR * This,
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IApcExtender __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Index )( 
            IApcExtender __RPC_FAR * This);
        
        END_INTERFACE
    } IApcExtenderVtbl;

    interface IApcExtender
    {
        CONST_VTBL struct IApcExtenderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcExtender_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcExtender_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcExtender_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcExtender_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcExtender_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcExtender_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcExtender_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcExtender_get_Name(This,pbstr)	\
    (This)->lpVtbl -> get_Name(This,pbstr)

#define IApcExtender_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IApcExtender_get_Object(This,ppunk)	\
    (This)->lpVtbl -> get_Object(This,ppunk)

#define IApcExtender_get_Parent(This,ppunk)	\
    (This)->lpVtbl -> get_Parent(This,ppunk)

#define IApcExtender_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IApcExtender_Index(This)	\
    (This)->lpVtbl -> Index(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IApcExtender_get_Name_Proxy( 
    IApcExtender __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB IApcExtender_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IApcExtender_put_Name_Proxy( 
    IApcExtender __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IApcExtender_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IApcExtender_get_Object_Proxy( 
    IApcExtender __RPC_FAR * This,
    /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB IApcExtender_get_Object_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IApcExtender_get_Parent_Proxy( 
    IApcExtender __RPC_FAR * This,
    /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB IApcExtender_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IApcExtender_Delete_Proxy( 
    IApcExtender __RPC_FAR * This);


void __RPC_STUB IApcExtender_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IApcExtender_Index_Proxy( 
    IApcExtender __RPC_FAR * This);


void __RPC_STUB IApcExtender_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcExtender_INTERFACE_DEFINED__ */


#ifndef __IApcSite_INTERFACE_DEFINED__
#define __IApcSite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcSite
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][local][restricted][uuid] */ 



EXTERN_C const IID IID_IApcSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcSite : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE ContinueIdle( 
            BOOL __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE DoIdle( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE EnterModalState( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE LeaveModalState( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE LostActivation( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE PushMessageLoop( 
            APCLOOPREASON LoopReason,
            BOOL __RPC_FAR *pbAborted) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcSite __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ContinueIdle )( 
            IApcSite __RPC_FAR * This,
            BOOL __RPC_FAR *pbContinue);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoIdle )( 
            IApcSite __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnterModalState )( 
            IApcSite __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LeaveModalState )( 
            IApcSite __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LostActivation )( 
            IApcSite __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PushMessageLoop )( 
            IApcSite __RPC_FAR * This,
            APCLOOPREASON LoopReason,
            BOOL __RPC_FAR *pbAborted);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShutDown )( 
            IApcSite __RPC_FAR * This);
        
        END_INTERFACE
    } IApcSiteVtbl;

    interface IApcSite
    {
        CONST_VTBL struct IApcSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcSite_ContinueIdle(This,pbContinue)	\
    (This)->lpVtbl -> ContinueIdle(This,pbContinue)

#define IApcSite_DoIdle(This)	\
    (This)->lpVtbl -> DoIdle(This)

#define IApcSite_EnterModalState(This)	\
    (This)->lpVtbl -> EnterModalState(This)

#define IApcSite_LeaveModalState(This)	\
    (This)->lpVtbl -> LeaveModalState(This)

#define IApcSite_LostActivation(This)	\
    (This)->lpVtbl -> LostActivation(This)

#define IApcSite_PushMessageLoop(This,LoopReason,pbAborted)	\
    (This)->lpVtbl -> PushMessageLoop(This,LoopReason,pbAborted)

#define IApcSite_ShutDown(This)	\
    (This)->lpVtbl -> ShutDown(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_ContinueIdle_Proxy( 
    IApcSite __RPC_FAR * This,
    BOOL __RPC_FAR *pbContinue);


void __RPC_STUB IApcSite_ContinueIdle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_DoIdle_Proxy( 
    IApcSite __RPC_FAR * This);


void __RPC_STUB IApcSite_DoIdle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_EnterModalState_Proxy( 
    IApcSite __RPC_FAR * This);


void __RPC_STUB IApcSite_EnterModalState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_LeaveModalState_Proxy( 
    IApcSite __RPC_FAR * This);


void __RPC_STUB IApcSite_LeaveModalState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_LostActivation_Proxy( 
    IApcSite __RPC_FAR * This);


void __RPC_STUB IApcSite_LostActivation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_PushMessageLoop_Proxy( 
    IApcSite __RPC_FAR * This,
    APCLOOPREASON LoopReason,
    BOOL __RPC_FAR *pbAborted);


void __RPC_STUB IApcSite_PushMessageLoop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcSite_ShutDown_Proxy( 
    IApcSite __RPC_FAR * This);


void __RPC_STUB IApcSite_ShutDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcSite_INTERFACE_DEFINED__ */


#ifndef __IApcCompManager_INTERFACE_DEFINED__
#define __IApcCompManager_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcCompManager
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][local][nonextensible][oleautomation][restricted][uuid] */ 



EXTERN_C const IID IID_IApcCompManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcCompManager : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_ModalState( 
            /* [retval][out] */ BOOL __RPC_FAR *pbModalState) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propput] */ HRESULT STDMETHODCALLTYPE put_ModalState( 
            /* [in] */ BOOL bModalState) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE DoIdle( 
            /* [in] */ APCIDLEFLAG IdleFlag,
            /* [retval][out] */ BOOL __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE ContinueMessageLoop( 
            /* [in] */ BOOL bPushedByHost,
            /* [retval][out] */ BOOL __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE HostActivate( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE WaitForMessage( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE PreTranslateMessage( 
            /* [in] */ void __RPC_FAR *pMsg,
            /* [retval][out] */ BOOL __RPC_FAR *pbConsumed) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcCompManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcCompManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcCompManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcCompManager __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModalState )( 
            IApcCompManager __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbModalState);
        
        /* [helpcontext][helpstring][restricted][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ModalState )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ BOOL bModalState);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoIdle )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ APCIDLEFLAG IdleFlag,
            /* [retval][out] */ BOOL __RPC_FAR *pbContinue);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ContinueMessageLoop )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ BOOL bPushedByHost,
            /* [retval][out] */ BOOL __RPC_FAR *pbContinue);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HostActivate )( 
            IApcCompManager __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForMessage )( 
            IApcCompManager __RPC_FAR * This);
        
        /* [helpcontext][helpstring][restricted] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PreTranslateMessage )( 
            IApcCompManager __RPC_FAR * This,
            /* [in] */ void __RPC_FAR *pMsg,
            /* [retval][out] */ BOOL __RPC_FAR *pbConsumed);
        
        END_INTERFACE
    } IApcCompManagerVtbl;

    interface IApcCompManager
    {
        CONST_VTBL struct IApcCompManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcCompManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcCompManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcCompManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcCompManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcCompManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcCompManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcCompManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcCompManager_get_ModalState(This,pbModalState)	\
    (This)->lpVtbl -> get_ModalState(This,pbModalState)

#define IApcCompManager_put_ModalState(This,bModalState)	\
    (This)->lpVtbl -> put_ModalState(This,bModalState)

#define IApcCompManager_DoIdle(This,IdleFlag,pbContinue)	\
    (This)->lpVtbl -> DoIdle(This,IdleFlag,pbContinue)

#define IApcCompManager_ContinueMessageLoop(This,bPushedByHost,pbContinue)	\
    (This)->lpVtbl -> ContinueMessageLoop(This,bPushedByHost,pbContinue)

#define IApcCompManager_HostActivate(This)	\
    (This)->lpVtbl -> HostActivate(This)

#define IApcCompManager_WaitForMessage(This)	\
    (This)->lpVtbl -> WaitForMessage(This)

#define IApcCompManager_PreTranslateMessage(This,pMsg,pbConsumed)	\
    (This)->lpVtbl -> PreTranslateMessage(This,pMsg,pbConsumed)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcCompManager_get_ModalState_Proxy( 
    IApcCompManager __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbModalState);


void __RPC_STUB IApcCompManager_get_ModalState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][propput] */ HRESULT STDMETHODCALLTYPE IApcCompManager_put_ModalState_Proxy( 
    IApcCompManager __RPC_FAR * This,
    /* [in] */ BOOL bModalState);


void __RPC_STUB IApcCompManager_put_ModalState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcCompManager_DoIdle_Proxy( 
    IApcCompManager __RPC_FAR * This,
    /* [in] */ APCIDLEFLAG IdleFlag,
    /* [retval][out] */ BOOL __RPC_FAR *pbContinue);


void __RPC_STUB IApcCompManager_DoIdle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcCompManager_ContinueMessageLoop_Proxy( 
    IApcCompManager __RPC_FAR * This,
    /* [in] */ BOOL bPushedByHost,
    /* [retval][out] */ BOOL __RPC_FAR *pbContinue);


void __RPC_STUB IApcCompManager_ContinueMessageLoop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcCompManager_HostActivate_Proxy( 
    IApcCompManager __RPC_FAR * This);


void __RPC_STUB IApcCompManager_HostActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcCompManager_WaitForMessage_Proxy( 
    IApcCompManager __RPC_FAR * This);


void __RPC_STUB IApcCompManager_WaitForMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted] */ HRESULT STDMETHODCALLTYPE IApcCompManager_PreTranslateMessage_Proxy( 
    IApcCompManager __RPC_FAR * This,
    /* [in] */ void __RPC_FAR *pMsg,
    /* [retval][out] */ BOOL __RPC_FAR *pbConsumed);


void __RPC_STUB IApcCompManager_PreTranslateMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcCompManager_INTERFACE_DEFINED__ */


#ifndef __IApcInstances_INTERFACE_DEFINED__
#define __IApcInstances_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcInstances
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcInstances;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcInstances : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultInstance( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ VARIANT UserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Apc( 
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ResetDefaultInstance( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [defaultvalue][in] */ VARIANT_BOOL DefaultInstance,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Reserved,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcInstancesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcInstances __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcInstances __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcInstances __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcInstances __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcInstances __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcInstances __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcInstances __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApcInstances __RPC_FAR * This,
            /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IApcInstances __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IApcInstances __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewEnum )( 
            IApcInstances __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultInstance )( 
            IApcInstances __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            IApcInstances __RPC_FAR * This,
            /* [in] */ VARIANT UserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            IApcInstances __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Apc )( 
            IApcInstances __RPC_FAR * This,
            /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetDefaultInstance )( 
            IApcInstances __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcInstances __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL DefaultInstance,
            /* [defaultvalue][in] */ IDispatch __RPC_FAR *Reserved,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);
        
        END_INTERFACE
    } IApcInstancesVtbl;

    interface IApcInstances
    {
        CONST_VTBL struct IApcInstancesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcInstances_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcInstances_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcInstances_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcInstances_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcInstances_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcInstances_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcInstances_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcInstances_get_Parent(This,ppProjectItem)	\
    (This)->lpVtbl -> get_Parent(This,ppProjectItem)

#define IApcInstances_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IApcInstances_get_Item(This,Index,ppInstance)	\
    (This)->lpVtbl -> get_Item(This,Index,ppInstance)

#define IApcInstances_get_NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get_NewEnum(This,ppUnk)

#define IApcInstances_get_DefaultInstance(This,ppInstance)	\
    (This)->lpVtbl -> get_DefaultInstance(This,ppInstance)

#define IApcInstances_put_Tag(This,UserTag)	\
    (This)->lpVtbl -> put_Tag(This,UserTag)

#define IApcInstances_get_Tag(This,pUserTag)	\
    (This)->lpVtbl -> get_Tag(This,pUserTag)

#define IApcInstances_get_Apc(This,ppApc)	\
    (This)->lpVtbl -> get_Apc(This,ppApc)

#define IApcInstances_ResetDefaultInstance(This)	\
    (This)->lpVtbl -> ResetDefaultInstance(This)

#define IApcInstances_Add(This,DefaultInstance,Reserved,ppInstance)	\
    (This)->lpVtbl -> Add(This,DefaultInstance,Reserved,ppInstance)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_Parent_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [retval][out] */ IApcProjectItem __RPC_FAR *__RPC_FAR *ppProjectItem);


void __RPC_STUB IApcInstances_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_Count_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcInstances_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_Item_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);


void __RPC_STUB IApcInstances_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_NewEnum_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcInstances_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_DefaultInstance_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);


void __RPC_STUB IApcInstances_get_DefaultInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcInstances_put_Tag_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [in] */ VARIANT UserTag);


void __RPC_STUB IApcInstances_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_Tag_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUserTag);


void __RPC_STUB IApcInstances_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcInstances_get_Apc_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [retval][out] */ IApc __RPC_FAR *__RPC_FAR *ppApc);


void __RPC_STUB IApcInstances_get_Apc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcInstances_ResetDefaultInstance_Proxy( 
    IApcInstances __RPC_FAR * This);


void __RPC_STUB IApcInstances_ResetDefaultInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcInstances_Add_Proxy( 
    IApcInstances __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL DefaultInstance,
    /* [defaultvalue][in] */ IDispatch __RPC_FAR *Reserved,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppInstance);


void __RPC_STUB IApcInstances_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcInstances_INTERFACE_DEFINED__ */


#ifndef __IApcHostAddIns_INTERFACE_DEFINED__
#define __IApcHostAddIns_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcHostAddIns
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcHostAddIns;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcHostAddIns : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AddIns( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAddIns) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LicenseKey( 
            /* [in] */ BSTR Key) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LicenseKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RegistryPath( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RegistryPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPath) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RemoveOnFailure( 
            /* [in] */ VARIANT_BOOL Remove) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RemoveOnFailure( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRemove) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HostObject( 
            /* [in] */ IDispatch __RPC_FAR *pHostObject) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HostObject( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostObject) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DisableOnStartup( 
            /* [in] */ VARIANT_BOOL Disabled) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DisableOnStartup( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbDisabled) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Locale( 
            /* [in] */ long lcidHost) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Locale( 
            /* [retval][out] */ long __RPC_FAR *plcidHost) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LoadHostAddIns( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE NotifyBeginShutdown( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE NotifyStartupComplete( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ShowAddInsDialog( void) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HostObject( 
            /* [in] */ IDispatch __RPC_FAR *pHostObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcHostAddInsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcHostAddIns __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcHostAddIns __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddIns )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAddIns);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LicenseKey )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ BSTR Key);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LicenseKey )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RegistryPath )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ BSTR Path);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RegistryPath )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrPath);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoveOnFailure )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Remove);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoveOnFailure )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRemove);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostObject )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pHostObject);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostObject )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostObject);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisableOnStartup )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Disabled);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisableOnStartup )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbDisabled);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locale )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ long lcidHost);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locale )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plcidHost);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadHostAddIns )( 
            IApcHostAddIns __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyBeginShutdown )( 
            IApcHostAddIns __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyStartupComplete )( 
            IApcHostAddIns __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowAddInsDialog )( 
            IApcHostAddIns __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_HostObject )( 
            IApcHostAddIns __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pHostObject);
        
        END_INTERFACE
    } IApcHostAddInsVtbl;

    interface IApcHostAddIns
    {
        CONST_VTBL struct IApcHostAddInsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcHostAddIns_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcHostAddIns_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcHostAddIns_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcHostAddIns_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcHostAddIns_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcHostAddIns_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcHostAddIns_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcHostAddIns_get_AddIns(This,ppAddIns)	\
    (This)->lpVtbl -> get_AddIns(This,ppAddIns)

#define IApcHostAddIns_put_LicenseKey(This,Key)	\
    (This)->lpVtbl -> put_LicenseKey(This,Key)

#define IApcHostAddIns_get_LicenseKey(This,pbstrKey)	\
    (This)->lpVtbl -> get_LicenseKey(This,pbstrKey)

#define IApcHostAddIns_put_RegistryPath(This,Path)	\
    (This)->lpVtbl -> put_RegistryPath(This,Path)

#define IApcHostAddIns_get_RegistryPath(This,pbstrPath)	\
    (This)->lpVtbl -> get_RegistryPath(This,pbstrPath)

#define IApcHostAddIns_put_RemoveOnFailure(This,Remove)	\
    (This)->lpVtbl -> put_RemoveOnFailure(This,Remove)

#define IApcHostAddIns_get_RemoveOnFailure(This,pbRemove)	\
    (This)->lpVtbl -> get_RemoveOnFailure(This,pbRemove)

#define IApcHostAddIns_put_HostObject(This,pHostObject)	\
    (This)->lpVtbl -> put_HostObject(This,pHostObject)

#define IApcHostAddIns_get_HostObject(This,ppHostObject)	\
    (This)->lpVtbl -> get_HostObject(This,ppHostObject)

#define IApcHostAddIns_put_DisableOnStartup(This,Disabled)	\
    (This)->lpVtbl -> put_DisableOnStartup(This,Disabled)

#define IApcHostAddIns_get_DisableOnStartup(This,pbDisabled)	\
    (This)->lpVtbl -> get_DisableOnStartup(This,pbDisabled)

#define IApcHostAddIns_put_Locale(This,lcidHost)	\
    (This)->lpVtbl -> put_Locale(This,lcidHost)

#define IApcHostAddIns_get_Locale(This,plcidHost)	\
    (This)->lpVtbl -> get_Locale(This,plcidHost)

#define IApcHostAddIns_LoadHostAddIns(This)	\
    (This)->lpVtbl -> LoadHostAddIns(This)

#define IApcHostAddIns_NotifyBeginShutdown(This)	\
    (This)->lpVtbl -> NotifyBeginShutdown(This)

#define IApcHostAddIns_NotifyStartupComplete(This)	\
    (This)->lpVtbl -> NotifyStartupComplete(This)

#define IApcHostAddIns_ShowAddInsDialog(This)	\
    (This)->lpVtbl -> ShowAddInsDialog(This)

#define IApcHostAddIns_putref_HostObject(This,pHostObject)	\
    (This)->lpVtbl -> putref_HostObject(This,pHostObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_AddIns_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAddIns);


void __RPC_STUB IApcHostAddIns_get_AddIns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_put_LicenseKey_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ BSTR Key);


void __RPC_STUB IApcHostAddIns_put_LicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_LicenseKey_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrKey);


void __RPC_STUB IApcHostAddIns_get_LicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_put_RegistryPath_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IApcHostAddIns_put_RegistryPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_RegistryPath_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrPath);


void __RPC_STUB IApcHostAddIns_get_RegistryPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_put_RemoveOnFailure_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Remove);


void __RPC_STUB IApcHostAddIns_put_RemoveOnFailure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_RemoveOnFailure_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRemove);


void __RPC_STUB IApcHostAddIns_get_RemoveOnFailure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_put_HostObject_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pHostObject);


void __RPC_STUB IApcHostAddIns_put_HostObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_HostObject_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppHostObject);


void __RPC_STUB IApcHostAddIns_get_HostObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_put_DisableOnStartup_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Disabled);


void __RPC_STUB IApcHostAddIns_put_DisableOnStartup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_DisableOnStartup_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbDisabled);


void __RPC_STUB IApcHostAddIns_get_DisableOnStartup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_put_Locale_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ long lcidHost);


void __RPC_STUB IApcHostAddIns_put_Locale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_get_Locale_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plcidHost);


void __RPC_STUB IApcHostAddIns_get_Locale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_LoadHostAddIns_Proxy( 
    IApcHostAddIns __RPC_FAR * This);


void __RPC_STUB IApcHostAddIns_LoadHostAddIns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_NotifyBeginShutdown_Proxy( 
    IApcHostAddIns __RPC_FAR * This);


void __RPC_STUB IApcHostAddIns_NotifyBeginShutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_NotifyStartupComplete_Proxy( 
    IApcHostAddIns __RPC_FAR * This);


void __RPC_STUB IApcHostAddIns_NotifyStartupComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_ShowAddInsDialog_Proxy( 
    IApcHostAddIns __RPC_FAR * This);


void __RPC_STUB IApcHostAddIns_ShowAddInsDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE IApcHostAddIns_putref_HostObject_Proxy( 
    IApcHostAddIns __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pHostObject);


void __RPC_STUB IApcHostAddIns_putref_HostObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcHostAddIns_INTERFACE_DEFINED__ */


#ifndef __IApcLegacyEvents_INTERFACE_DEFINED__
#define __IApcLegacyEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcLegacyEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][local][nonextensible][oleautomation][hidden][uuid] */ 



EXTERN_C const IID IID_IApcLegacyEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcLegacyEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProjectItemCount( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SaveAsLegacy( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *SaveLegacy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ProjectItemName( 
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProjectItemName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ControlCount( 
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LicensedControlCount( 
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ControlName( 
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrControlName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ClassID( 
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ BSTR __RPC_FAR *bstrClassID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE TypeLibraryInfo( 
            /* [in] */ long ProjectItemIndex,
            /* [out][in] */ BSTR __RPC_FAR *bstrTypeLibraryGuid,
            /* [out][in] */ unsigned short __RPC_FAR *MajorVersion,
            /* [out][in] */ unsigned short __RPC_FAR *MinorVersion,
            /* [out][in] */ long __RPC_FAR *Lcid) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UseDefaultExtender( 
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UseExtender) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ControlCoClassGuid( 
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ BSTR __RPC_FAR *bstrControlCoClassGuid) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LicensedControlCoClassGuid( 
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ BSTR __RPC_FAR *bstrLicControlCoClassGuid) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ControlID( 
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ long __RPC_FAR *pControlID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcLegacyEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcLegacyEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcLegacyEvents __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectItemCount )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SaveAsLegacy )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *SaveLegacy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProjectItemName )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProjectItemName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlCount )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LicensedControlCount )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlName )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrControlName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClassID )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [retval][out] */ BSTR __RPC_FAR *bstrClassID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TypeLibraryInfo )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [out][in] */ BSTR __RPC_FAR *bstrTypeLibraryGuid,
            /* [out][in] */ unsigned short __RPC_FAR *MajorVersion,
            /* [out][in] */ unsigned short __RPC_FAR *MinorVersion,
            /* [out][in] */ long __RPC_FAR *Lcid);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UseDefaultExtender )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UseExtender);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlCoClassGuid )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ BSTR __RPC_FAR *bstrControlCoClassGuid);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LicensedControlCoClassGuid )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ BSTR __RPC_FAR *bstrLicControlCoClassGuid);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlID )( 
            IApcLegacyEvents __RPC_FAR * This,
            /* [in] */ long ProjectItemIndex,
            /* [in] */ long ControlIndex,
            /* [retval][out] */ long __RPC_FAR *pControlID);
        
        END_INTERFACE
    } IApcLegacyEventsVtbl;

    interface IApcLegacyEvents
    {
        CONST_VTBL struct IApcLegacyEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcLegacyEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcLegacyEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcLegacyEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcLegacyEvents_get_ProjectItemCount(This,pCount)	\
    (This)->lpVtbl -> get_ProjectItemCount(This,pCount)

#define IApcLegacyEvents_get_SaveAsLegacy(This,SaveLegacy)	\
    (This)->lpVtbl -> get_SaveAsLegacy(This,SaveLegacy)

#define IApcLegacyEvents_ProjectItemName(This,ProjectItemIndex,pbstrProjectItemName)	\
    (This)->lpVtbl -> ProjectItemName(This,ProjectItemIndex,pbstrProjectItemName)

#define IApcLegacyEvents_ControlCount(This,ProjectItemIndex,pCount)	\
    (This)->lpVtbl -> ControlCount(This,ProjectItemIndex,pCount)

#define IApcLegacyEvents_LicensedControlCount(This,ProjectItemIndex,pCount)	\
    (This)->lpVtbl -> LicensedControlCount(This,ProjectItemIndex,pCount)

#define IApcLegacyEvents_ControlName(This,ProjectItemIndex,ControlIndex,pbstrControlName)	\
    (This)->lpVtbl -> ControlName(This,ProjectItemIndex,ControlIndex,pbstrControlName)

#define IApcLegacyEvents_ClassID(This,ProjectItemIndex,bstrClassID)	\
    (This)->lpVtbl -> ClassID(This,ProjectItemIndex,bstrClassID)

#define IApcLegacyEvents_TypeLibraryInfo(This,ProjectItemIndex,bstrTypeLibraryGuid,MajorVersion,MinorVersion,Lcid)	\
    (This)->lpVtbl -> TypeLibraryInfo(This,ProjectItemIndex,bstrTypeLibraryGuid,MajorVersion,MinorVersion,Lcid)

#define IApcLegacyEvents_UseDefaultExtender(This,ProjectItemIndex,ControlIndex,UseExtender)	\
    (This)->lpVtbl -> UseDefaultExtender(This,ProjectItemIndex,ControlIndex,UseExtender)

#define IApcLegacyEvents_ControlCoClassGuid(This,ProjectItemIndex,ControlIndex,bstrControlCoClassGuid)	\
    (This)->lpVtbl -> ControlCoClassGuid(This,ProjectItemIndex,ControlIndex,bstrControlCoClassGuid)

#define IApcLegacyEvents_LicensedControlCoClassGuid(This,ProjectItemIndex,ControlIndex,bstrLicControlCoClassGuid)	\
    (This)->lpVtbl -> LicensedControlCoClassGuid(This,ProjectItemIndex,ControlIndex,bstrLicControlCoClassGuid)

#define IApcLegacyEvents_ControlID(This,ProjectItemIndex,ControlIndex,pControlID)	\
    (This)->lpVtbl -> ControlID(This,ProjectItemIndex,ControlIndex,pControlID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_get_ProjectItemCount_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcLegacyEvents_get_ProjectItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_get_SaveAsLegacy_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *SaveLegacy);


void __RPC_STUB IApcLegacyEvents_get_SaveAsLegacy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_ProjectItemName_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrProjectItemName);


void __RPC_STUB IApcLegacyEvents_ProjectItemName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_ControlCount_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcLegacyEvents_ControlCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_LicensedControlCount_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IApcLegacyEvents_LicensedControlCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_ControlName_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [in] */ long ControlIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrControlName);


void __RPC_STUB IApcLegacyEvents_ControlName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_ClassID_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [retval][out] */ BSTR __RPC_FAR *bstrClassID);


void __RPC_STUB IApcLegacyEvents_ClassID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_TypeLibraryInfo_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [out][in] */ BSTR __RPC_FAR *bstrTypeLibraryGuid,
    /* [out][in] */ unsigned short __RPC_FAR *MajorVersion,
    /* [out][in] */ unsigned short __RPC_FAR *MinorVersion,
    /* [out][in] */ long __RPC_FAR *Lcid);


void __RPC_STUB IApcLegacyEvents_TypeLibraryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_UseDefaultExtender_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [in] */ long ControlIndex,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UseExtender);


void __RPC_STUB IApcLegacyEvents_UseDefaultExtender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_ControlCoClassGuid_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [in] */ long ControlIndex,
    /* [retval][out] */ BSTR __RPC_FAR *bstrControlCoClassGuid);


void __RPC_STUB IApcLegacyEvents_ControlCoClassGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_LicensedControlCoClassGuid_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [in] */ long ControlIndex,
    /* [retval][out] */ BSTR __RPC_FAR *bstrLicControlCoClassGuid);


void __RPC_STUB IApcLegacyEvents_LicensedControlCoClassGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcLegacyEvents_ControlID_Proxy( 
    IApcLegacyEvents __RPC_FAR * This,
    /* [in] */ long ProjectItemIndex,
    /* [in] */ long ControlIndex,
    /* [retval][out] */ long __RPC_FAR *pControlID);


void __RPC_STUB IApcLegacyEvents_ControlID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcLegacyEvents_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ApcGlobal;

class ApcGlobal;
#endif

#ifndef __ApcEvents_DISPINTERFACE_DEFINED__
#define __ApcEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcEventsVtbl;

    interface ApcEvents
    {
        CONST_VTBL struct ApcEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Apc;

class Apc;
#endif

#ifndef __ApcIdeEvents_DISPINTERFACE_DEFINED__
#define __ApcIdeEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcIdeEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcIdeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcIdeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcIdeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcIdeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcIdeEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcIdeEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcIdeEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcIdeEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcIdeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcIdeEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcIdeEventsVtbl;

    interface ApcIdeEvents
    {
        CONST_VTBL struct ApcIdeEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcIdeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcIdeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcIdeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcIdeEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcIdeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcIdeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcIdeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcIdeEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_IDE;

class IDE;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_PropertiesWindow;

class PropertiesWindow;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Projects;

class Projects;
#endif

#ifndef __ApcProjectEvents_DISPINTERFACE_DEFINED__
#define __ApcProjectEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcProjectEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcProjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcProjectEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcProjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcProjectEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcProjectEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcProjectEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcProjectEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcProjectEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcProjectEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcProjectEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcProjectEventsVtbl;

    interface ApcProjectEvents
    {
        CONST_VTBL struct ApcProjectEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcProjectEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcProjectEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcProjectEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcProjectEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcProjectEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcProjectEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcProjectEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcProjectEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Project;

class Project;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ProjectItems;

class ProjectItems;
#endif

#ifndef __ApcProjectItemEvents_DISPINTERFACE_DEFINED__
#define __ApcProjectItemEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcProjectItemEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcProjectItemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcProjectItemEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcProjectItemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcProjectItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcProjectItemEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcProjectItemEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcProjectItemEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcProjectItemEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcProjectItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcProjectItemEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcProjectItemEventsVtbl;

    interface ApcProjectItemEvents
    {
        CONST_VTBL struct ApcProjectItemEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcProjectItemEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcProjectItemEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcProjectItemEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcProjectItemEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcProjectItemEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcProjectItemEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcProjectItemEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcProjectItemEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ProjectItem;

class ProjectItem;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Controls;

class Controls;
#endif

#ifndef __ApcControlEvents_DISPINTERFACE_DEFINED__
#define __ApcControlEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcControlEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcControlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcControlEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcControlEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcControlEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcControlEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcControlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcControlEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcControlEventsVtbl;

    interface ApcControlEvents
    {
        CONST_VTBL struct ApcControlEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcControlEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Control;

class Control;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Procedures;

class Procedures;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Procedure;

class Procedure;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Categories;

class Categories;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Category;

class Category;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_MiniBitmaps;

class MiniBitmaps;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_MiniBitmap;

class MiniBitmap;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Recorder;

class Recorder;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Scopes;

class Scopes;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Scope;

class Scope;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_MacrosDialog;

class MacrosDialog;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Storage;

class Storage;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Stream;

class Stream;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_RequiredClasses;

class RequiredClasses;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_RequiredClass;

class RequiredClass;
#endif

#ifndef __ApcExtenderDisp_DISPINTERFACE_DEFINED__
#define __ApcExtenderDisp_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcExtenderDisp
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcExtenderDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcExtenderDisp : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcExtenderDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcExtenderDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcExtenderDisp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcExtenderDisp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcExtenderDisp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcExtenderDisp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcExtenderDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcExtenderDisp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcExtenderDispVtbl;

    interface ApcExtenderDisp
    {
        CONST_VTBL struct ApcExtenderDispVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcExtenderDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcExtenderDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcExtenderDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcExtenderDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcExtenderDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcExtenderDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcExtenderDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcExtenderDisp_DISPINTERFACE_DEFINED__ */


#ifndef __ApcExtenderEvents_DISPINTERFACE_DEFINED__
#define __ApcExtenderEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: ApcExtenderEvents
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [hidden][uuid] */ 



EXTERN_C const IID DIID_ApcExtenderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface ApcExtenderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ApcExtenderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ApcExtenderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ApcExtenderEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ApcExtenderEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ApcExtenderEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ApcExtenderEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ApcExtenderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ApcExtenderEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ApcExtenderEventsVtbl;

    interface ApcExtenderEvents
    {
        CONST_VTBL struct ApcExtenderEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ApcExtenderEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ApcExtenderEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ApcExtenderEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ApcExtenderEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ApcExtenderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ApcExtenderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ApcExtenderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ApcExtenderEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ApcExtender;

class ApcExtender;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Instances;

class Instances;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_HostAddIns;

class HostAddIns;
#endif

#ifndef __IApcCollection_INTERFACE_DEFINED__
#define __IApcCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApcCollection
 * at Wed Sep 24 07:45:49 2003
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][nonextensible][oleautomation][uuid] */ 



EXTERN_C const IID IID_IApcCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IApcCollection : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT __RPC_FAR *Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRet) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT __RPC_FAR *Item,
            /* [optional][in] */ VARIANT __RPC_FAR *Key) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Count( 
            /* [retval][out] */ long __RPC_FAR *pi4) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT __RPC_FAR *Index) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApcCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApcCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApcCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApcCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRet);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Item,
            /* [optional][in] */ VARIANT __RPC_FAR *Key);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Count )( 
            IApcCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pi4);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IApcCollection __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Index);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            IApcCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        END_INTERFACE
    } IApcCollectionVtbl;

    interface IApcCollection
    {
        CONST_VTBL struct IApcCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApcCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApcCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApcCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApcCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApcCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApcCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApcCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApcCollection_Item(This,Index,pvarRet)	\
    (This)->lpVtbl -> Item(This,Index,pvarRet)

#define IApcCollection_Add(This,Item,Key)	\
    (This)->lpVtbl -> Add(This,Item,Key)

#define IApcCollection_Count(This,pi4)	\
    (This)->lpVtbl -> Count(This,pi4)

#define IApcCollection_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define IApcCollection__NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> _NewEnum(This,ppUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IApcCollection_Item_Proxy( 
    IApcCollection __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *Index,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarRet);


void __RPC_STUB IApcCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcCollection_Add_Proxy( 
    IApcCollection __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *Item,
    /* [optional][in] */ VARIANT __RPC_FAR *Key);


void __RPC_STUB IApcCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcCollection_Count_Proxy( 
    IApcCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pi4);


void __RPC_STUB IApcCollection_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IApcCollection_Remove_Proxy( 
    IApcCollection __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *Index);


void __RPC_STUB IApcCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IApcCollection__NewEnum_Proxy( 
    IApcCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IApcCollection__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApcCollection_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Collection;

class Collection;
#endif
#endif /* __MSAPC_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
