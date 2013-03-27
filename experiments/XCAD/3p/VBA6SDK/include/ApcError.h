//
// ApcError.h
//
// Header file for the APC errors.
//
// This file is part of the Microsoft Applications Programability Control (APC)
// Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
// Information Contained Herein Is Proprietary and Confidential.
//
// --------------------------------------------------------------------------
//
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: APC_E_INVALIDINDEX
//
// MessageText:
//
//  Index not found. The specified index or name does not exist in the collection.
//
#define APC_E_INVALIDINDEX               0x80040500L

//
// MessageId: APC_E_ZOMBIED
//
// MessageText:
//
//  Object is disconnected. The object is no longer valid, but a reference to the object is still being held (most likely by the application).
//
#define APC_E_ZOMBIED                    0x80040501L

//
// MessageId: APC_E_UNEXPECTED
//
// MessageText:
//
//  Unexpected internal error.
//
#define APC_E_UNEXPECTED                 0x80040502L

//
// MessageId: APC_E_OUTOFMEMORY
//
// MessageText:
//
//  Out of memory. This error is returned to indicate that there is not enough memory available to complete the operation.
//
#define APC_E_OUTOFMEMORY                0x80040503L

//
// MessageId: APC_E_OPENFILEFAILED
//
// MessageText:
//
//  File doesn't exist or can't be opened.
//
#define APC_E_OPENFILEFAILED             0x80040504L

//
// MessageId: APC_E_ONLYDOCITEMS
//
// MessageText:
//
//  Method or property valid only for host project items.
//
#define APC_E_ONLYDOCITEMS               0x80040505L

//
// MessageId: APC_E_VBA
//
// MessageText:
//
//  Unknown VBA error; error code = 0x%1!08X!.
//
#define APC_E_VBA                        0x80040506L

//
// MessageId: APC_E_OUTOFSYNC
//
// MessageText:
//
//  Type library information is out of sync with implementation. This occurs most often in VB applications--in which case, you can synchronize this information either by restarting VB or by recreating the executable file.
//
#define APC_E_OUTOFSYNC                  0x80040507L

//
// MessageId: APC_E_INVALIDITEM
//
// MessageText:
//
//  ProjectItems collection contains an unknown or invalid project item.
//
#define APC_E_INVALIDITEM                0x80040508L

//
// MessageId: APC_E_ONLYCODEMODULES
//
// MessageText:
//
//  This method or property is only valid for code modules and host project items.
//
#define APC_E_ONLYCODEMODULES            0x80040509L

//
// MessageId: APC_E_PROJECTLOCKED
//
// MessageText:
//
//  The VBA project is currently referenced by another open VBA project and therefore cannot be closed or destroyed.
//
#define APC_E_PROJECTLOCKED              0x8004050AL

//
// MessageId: APC_E_TYPELIBCHANGED
//
// MessageText:
//
//  The type library of the application doesn't match that used to create this VBA project. For VB applications, make sure that Version Compatibility is set to 'Project Compatibility' and that you have generated an EXE with which you are compatible.
//
#define APC_E_TYPELIBCHANGED             0x8004050BL

//
// MessageId: APC_E_CLASSNOTFOUND
//
// MessageText:
//
//  Unable to find that class in the application's type library.
//
#define APC_E_CLASSNOTFOUND              0x8004050CL

//
// MessageId: APC_E_ONLYSUBROUTINES
//
// MessageText:
//
//  This method or property is only valid for subroutines (that is, methods that don't return values). Functions and property procedures are not supported.
//
#define APC_E_ONLYSUBROUTINES            0x8004050DL

//
// MessageId: APC_E_ALREADYRECORDING
//
// MessageText:
//
//  Cannot start more than one recorder.
//
#define APC_E_ALREADYRECORDING           0x8004050EL

//
// MessageId: APC_E_UNDOEMPTY
//
// MessageText:
//
//  Not enough undo items.
//
#define APC_E_UNDOEMPTY                  0x8004050FL

//
// MessageId: APC_E_NOTEVENT
//
// MessageText:
//
//  This property is only valid for event subroutines defined in host project items.
//
#define APC_E_NOTEVENT                   0x80040510L

//
// MessageId: APC_E_TOOMANYCONTROLS
//
// MessageText:
//
//  Too many controls.
//
#define APC_E_TOOMANYCONTROLS            0x80040511L

//
// MessageId: APC_E_BADOBJ
//
// MessageText:
//
//  Object in parameter %1!d! doesn't support type information or have the correct attributes.
//
#define APC_E_BADOBJ                     0x80040512L

//
// MessageId: APC_E_SUBORFUNCEXPECTED
//
// MessageText:
//
//  Expecting Sub or Function (the specified name was not found).
//
#define APC_E_SUBORFUNCEXPECTED          0x80040513L

//
// MessageId: APC_E_CANTCOPYTYPELIB
//
// MessageText:
//
//  Unable to copy host type library. The host type library most likely contains unsupported constructs.
//
#define APC_E_CANTCOPYTYPELIB            0x80040514L

//
// MessageId: APC_E_NOSCOPES
//
// MessageText:
//
//  The Scopes collection is empty; you need to populate the Scopes collection before showing the Macros dialog box or using CallMacro.
//
#define APC_E_NOSCOPES                   0x80040515L

//
// MessageId: APC_E_NOPERMISSION
//
// MessageText:
//
//  Permission denied (or access denied).
//
#define APC_E_NOPERMISSION               0x80040516L

//
// MessageId: APC_E_TOOMANYOPENFILES
//
// MessageText:
//
//  Too many files open.
//
#define APC_E_TOOMANYOPENFILES           0x80040517L

//
// MessageId: APC_E_FILEALREADYEXISTS
//
// MessageText:
//
//  File already exists.
//
#define APC_E_FILEALREADYEXISTS          0x80040518L

//
// MessageId: APC_E_OUTOFDISKSPACE
//
// MessageText:
//
//  Out of disk space.
//
#define APC_E_OUTOFDISKSPACE             0x80040519L

//
// MessageId: APC_E_ONLYFORINMEMORY
//
// MessageText:
//
//  This property is only valid for root in-memory storage objects.
//
#define APC_E_ONLYFORINMEMORY            0x8004051AL

//
// MessageId: APC_E_CANTACCESSARRAY
//
// MessageText:
//
//  Can't access the storage array.
//
#define APC_E_CANTACCESSARRAY            0x8004051BL

//
// MessageId: APC_E_NOREADORLOCKSTORAGE
//
// MessageText:
//
//  Invalid flag or attempt to create storage in read-only or locked mode.
//
#define APC_E_NOREADORLOCKSTORAGE        0x8004051CL

//
// MessageId: APC_E_INVALIDFILENAME
//
// MessageText:
//
//  Invalid filename.
//
#define APC_E_INVALIDFILENAME            0x8004051DL

//
// MessageId: APC_E_INVALIDINMEMORYSTG
//
// MessageText:
//
//  This property is not valid for root in-memory storage objects.
//
#define APC_E_INVALIDINMEMORYSTG         0x8004051EL

//
// MessageId: APC_E_UNKNOWN
//
// MessageText:
//
//  Unknown error; error code = 0x%1!08X!.
//
#define APC_E_UNKNOWN                    0x8004051FL

//
// MessageId: APC_E_INVALIDARG
//
// MessageText:
//
//  One or more arguments are invalid.
//
#define APC_E_INVALIDARG                 0x80040520L

//
// MessageId: APC_E_INVALIDARG_SPECIFIC
//
// MessageText:
//
//  Argument %1!d! is invalid.
//
#define APC_E_INVALIDARG_SPECIFIC        0x80040521L

//
// MessageId: APC_E_BADPARMCOUNT
//
// MessageText:
//
//  Bad parameter count.
//
#define APC_E_BADPARMCOUNT               0x80040522L

//
// MessageId: APC_E_BADVARTYPE
//
// MessageText:
//
//  Bad parameter type.
//
#define APC_E_BADVARTYPE                 0x80040523L

//
// MessageId: APC_E_OVERFLOW
//
// MessageText:
//
//  Out of present range.
//
#define APC_E_OVERFLOW                   0x80040524L

//
// MessageId: APC_E_TYPEMISMATCH
//
// MessageText:
//
//  Type mismatch.
//
#define APC_E_TYPEMISMATCH               0x80040525L

//
// MessageId: APC_E_PARMNOTOPTIONAL
//
// MessageText:
//
//  Parameter not optional.
//
#define APC_E_PARMNOTOPTIONAL            0x80040526L

//
// MessageId: APC_E_UNKNOWNLCID
//
// MessageText:
//
//  Unknown language.
//
#define APC_E_UNKNOWNLCID                0x80040527L

//
// MessageId: APC_E_CONNECTION_TERMINATED
//
// MessageText:
//
//  Connection terminated with remote host.
//
#define APC_E_CONNECTION_TERMINATED      0x80040528L

//
// MessageId: APC_E_CALL_REJECTED
//
// MessageText:
//
//  Call rejected by callee.
//
#define APC_E_CALL_REJECTED              0x80040529L

//
// MessageId: APC_E_BUSY
//
// MessageText:
//
//  Callee is busy or unavailable.
//
#define APC_E_BUSY                       0x8004052AL

//
// MessageId: APC_E_CALLFAILED
//
// MessageText:
//
//  Remote procedure call failed.
//
#define APC_E_CALLFAILED                 0x8004052BL

//
// MessageId: APC_E_EXCEPTION
//
// MessageText:
//
//  Exception occurred.
//
#define APC_E_EXCEPTION                  0x8004052CL

//
// MessageId: APC_E_NOCOLLECTION
//
// MessageText:
//
//  Unable to create VBA collection (Collection class not registered).
//
#define APC_E_NOCOLLECTION               0x8004052DL

//
// MessageId: APC_E_CANT_CREATE_PROJECTITEMS_COLLECTION
//
// MessageText:
//
//  Unable to populate the ProjectItems collection.
//
#define APC_E_CANT_CREATE_PROJECTITEMS_COLLECTION 0x8004052EL

//
// MessageId: APC_E_CANT_CREATE_APC_DATA_STREAM
//
// MessageText:
//
//  Unable to create private APC data stream.
//
#define APC_E_CANT_CREATE_APC_DATA_STREAM 0x8004052FL

//
// MessageId: APC_E_CANT_CREATE_PROJITEM_DATA_STREAM
//
// MessageText:
//
//  Unable to create private host project items data stream.
//
#define APC_E_CANT_CREATE_PROJITEM_DATA_STREAM 0x80040530L

//
// MessageId: APC_E_CANT_CREATE_VBA_STREAM
//
// MessageText:
//
//  Unable to create VBA stream.
//
#define APC_E_CANT_CREATE_VBA_STREAM     0x80040531L

//
// MessageId: APC_E_COULDNOTACCESSSTREAM
//
// MessageText:
//
//  Unable to access stream.
//
#define APC_E_COULDNOTACCESSSTREAM       0x80040532L

//
// MessageId: APC_E_DISKERROR
//
// MessageText:
//
//  Disk error.
//
#define APC_E_DISKERROR                  0x80040533L

//
// MessageId: APC_E_INVALIDSEEKPOS
//
// MessageText:
//
//  Invalid seek position.
//
#define APC_E_INVALIDSEEKPOS             0x80040534L

//
// MessageId: APC_E_REVERTED
//
// MessageText:
//
//  The Storage or Stream object is invalid due to a prior rollback operation in the transaction tree.
//
#define APC_E_REVERTED                   0x80040535L

//
// MessageId: APC_E_UNKNOWNPROPERTYNAME
//
// MessageText:
//
//  Specified property name does not exist.
//
#define APC_E_UNKNOWNPROPERTYNAME        0x80040536L

//
// MessageId: APC_E_HOSTCONTROLALREADYSET
//
// MessageText:
//
//  Host control already set.
//
#define APC_E_HOSTCONTROLALREADYSET      0x80040537L

//
// MessageId: APC_E_EXTENDERALREADYSET
//
// MessageText:
//
//  The extender has already been set for this control.
//
#define APC_E_EXTENDERALREADYSET         0x80040538L

//
// MessageId: APC_E_NOTATTACHED
//
// MessageText:
//
//  The VBA project has been saved, but SaveCompleted has not been called. (Or the VBA project has not yet been attached to an IStorage by calling InitNew or Load.)
//
#define APC_E_NOTATTACHED                0x80040539L

//
// MessageId: APC_E_INVALIDFILEFILTER
//
// MessageText:
//
//  Invalid file filter.
//
#define APC_E_INVALIDFILEFILTER          0x8004053AL

//
// MessageId: APC_E_SHAREVIOLATION
//
// MessageText:
//
//  A share violation has occurred.
//
#define APC_E_SHAREVIOLATION             0x8004053BL

//
// MessageId: APC_E_NOTCURRENT
//
// MessageText:
//
//  The storage has been changed since the last commit.
//
#define APC_E_NOTCURRENT                 0x8004053CL

//
// MessageId: APC_E_UNDEFINEDPROC
//
// MessageText:
//
//  Undefined Sub or Function.
//
#define APC_E_UNDEFINEDPROC              0x8004053DL

//
// MessageId: APC_E_INVALIDPROCNAME
//
// MessageText:
//
//  Procedure not found or invalid name.
//
#define APC_E_INVALIDPROCNAME            0x8004053EL

//
// MessageId: APC_E_CANTEXITDESIGNMODE
//
// MessageText:
//
//  Can't exit Design mode.
//
#define APC_E_CANTEXITDESIGNMODE         0x8004053FL

//
// MessageId: APC_E_HOSTPROJITEM_NOEVENT
//
// MessageText:
//
//  Host project items must have at least one event.
//
#define APC_E_HOSTPROJITEM_NOEVENT       0x80040540L

//
// MessageId: APC_E_CONTROL_NOEVENT
//
// MessageText:
//
//  Controls must have a coclass (in VB, controls must have at least one event).
//
#define APC_E_CONTROL_NOEVENT            0x80040541L

//
// MessageId: APC_E_EXTENDER_NOEVENT
//
// MessageText:
//
//  Extenders must have a coclass (in VB, extenders must have at least one event).
//
#define APC_E_EXTENDER_NOEVENT           0x80040542L

//
// MessageId: APC_E_PROJ_STG_ALREADYINITIALIZED
//
// MessageText:
//
//  The project storage has already been initialized.
//
#define APC_E_PROJ_STG_ALREADYINITIALIZED 0x80040543L

//
// MessageId: APC_E_MODNAMECONFLICT
//
// MessageText:
//
//  The specified module name conflicts with an existing module name.
//
#define APC_E_MODNAMECONFLICT            0x80040544L

//
// MessageId: APC_E_INVALID_IDENT_STRING
//
// MessageText:
//
//  Not a legal object name: '%1!S!' 
//
#define APC_E_INVALID_IDENT_STRING       0x80040545L

//
// MessageId: APC_E_HOSTCONTROLNOTSET
//
// MessageText:
//
//  The HostControl property has not been set
//
#define APC_E_HOSTCONTROLNOTSET          0x80040546L

//
// MessageId: APC_E_EXTENDERNOTSET
//
// MessageText:
//
//  The Extender property has not been set
//
#define APC_E_EXTENDERNOTSET             0x80040547L

//
// MessageId: APC_E_CANT_CREATE_TEMP_DIR
//
// MessageText:
//
//  Unable to create the application's temporary directory (used for the storage of .EXT and other temporary files).
//
#define APC_E_CANT_CREATE_TEMP_DIR       0x80040548L

//
// MessageId: APC_E_OBJECTNOTSET
//
// MessageText:
//
//  The object has not been set.
//
#define APC_E_OBJECTNOTSET               0x80040549L

//
// MessageId: APC_E_CORRUPTSTORAGE
//
// MessageText:
//
//  The storage file contains corrupt data.
//
#define APC_E_CORRUPTSTORAGE             0x8004054AL

//
// MessageId: APC_E_COULD_NOT_REMOVE_OBJ
//
// MessageText:
//
//  Unable to remove object from the collection.
//
#define APC_E_COULD_NOT_REMOVE_OBJ       0x8004054BL

//
// MessageId: APC_E_COULD_NOT_ADD_OBJ
//
// MessageText:
//
//  Unable to add object to the collection.
//
#define APC_E_COULD_NOT_ADD_OBJ          0x8004054CL

//
// MessageId: APC_E_COULD_NOT_CREATE_CODEMODULE
//
// MessageText:
//
//  Unable to create CodeModule.
//
#define APC_E_COULD_NOT_CREATE_CODEMODULE 0x8004054DL

//
// MessageId: APC_E_COULD_NOT_CREATE_CLASSMODULE
//
// MessageText:
//
//  Unable to create ClassModule.
//
#define APC_E_COULD_NOT_CREATE_CLASSMODULE 0x8004054EL

//
// MessageId: APC_E_CANT_CREATE_PROJITEM
//
// MessageText:
//
//  Unable to create host project item.
//
#define APC_E_CANT_CREATE_PROJITEM       0x8004054FL

//
// MessageId: APC_E_CANT_ACCESS_TYPELIB
//
// MessageText:
//
//  Unable to open or read the type library.
//
#define APC_E_CANT_ACCESS_TYPELIB        0x80040550L

//
// MessageId: APC_E_NO_VBA_PROJECT
//
// MessageText:
//
//  There is no VBA project associated with this object.
//
#define APC_E_NO_VBA_PROJECT             0x80040551L

//
// MessageId: APC_E_COMPILEERROR
//
// MessageText:
//
//  VBA encountered an error while compiling.
//
#define APC_E_COMPILEERROR               0x80040552L

//
// MessageId: APC_E_TOO_MANY_HOSTS
//
// MessageText:
//
//  Only one Apc object can be created per process.
//
#define APC_E_TOO_MANY_HOSTS             0x80040553L

//
// MessageId: APC_E_PROJECT_ITEM_COUNT_MISMATCH
//
// MessageText:
//
//  Unable to open the VBA project. The number of host project items does not match those in the VBA project.
//
#define APC_E_PROJECT_ITEM_COUNT_MISMATCH 0x80040554L

//
// MessageId: APC_E_PROJECT_ITEM_MISMATCH
//
// MessageText:
//
//  Unable to open the VBA project. The names of the host project items do not match those in the VBA project.
//
#define APC_E_PROJECT_ITEM_MISMATCH      0x80040555L

//
// MessageId: APC_E_INVALID_PROJECT_ITEM
//
// MessageText:
//
//  Invalid host project item was passed in the collection.
//
#define APC_E_INVALID_PROJECT_ITEM       0x80040556L

//
// MessageId: APC_E_CANT_READ_APC_DATA
//
// MessageText:
//
//  Unable to read VBA project data.
//
#define APC_E_CANT_READ_APC_DATA         0x80040557L

//
// MessageId: APC_E_INCORRECT_VERSION
//
// MessageText:
//
//  The version of this VBA project file cannot be read by this version of APC.
//
#define APC_E_INCORRECT_VERSION          0x80040558L

//
// MessageId: APC_E_INVALID_PICTURE
//
// MessageText:
//
//  Invalid picture.
//
#define APC_E_INVALID_PICTURE            0x80040559L

//
// MessageId: APC_E_EXCEEDED_HOST_COUNT
//
// MessageText:
//
//  VBA has been initialized too many times in this process. You must restart your application.
//
#define APC_E_EXCEEDED_HOST_COUNT        0x8004055AL

//
// MessageId: APC_E_BAD_VBA_INSTALLATION
//
// MessageText:
//
//  One of the VBA components is missing or corrupt. You must reinstall VBA.
//
#define APC_E_BAD_VBA_INSTALLATION       0x8004055BL

//
// MessageId: APC_E_EXPIRED
//
// MessageText:
//
//  Your VBA license key has expired.
//
#define APC_E_EXPIRED                    0x8004055CL

//
// MessageId: APC_E_INCORRECT_VBA_VERSION
//
// MessageText:
//
//  Wrong version of VBA.
//
#define APC_E_INCORRECT_VBA_VERSION      0x8004055DL

//
// MessageId: APC_E_CLASS_NOT_FOUND
//
// MessageText:
//
//  Unable to find that Extender class in the application's type library, or that Extender class did not define at least one event.
//
#define APC_E_CLASS_NOT_FOUND            0x8004055EL

//
// MessageId: APC_E_CANT_FIRE_EVENT
//
// MessageText:
//
//  Unable to fire event.
//
#define APC_E_CANT_FIRE_EVENT            0x8004055FL

//
// MessageId: APC_E_PROJECT_ALREADY_EXISTS
//
// MessageText:
//
//  There is already an existing project with the specified name.
//
#define APC_E_PROJECT_ALREADY_EXISTS     0x80040560L

//
// MessageId: APC_E_USER_INTERRUPT
//
// MessageText:
//
//  User interrupt.
//
#define APC_E_USER_INTERRUPT             0x80040561L

//
// MessageId: APC_E_INVALID_APP_OBJ
//
// MessageText:
//
//  Invalid Application object.
//
#define APC_E_INVALID_APP_OBJ            0x80040562L

//
// MessageId: APC_E_STORAGE_NOPERMISSION
//
// MessageText:
//
//  Invalid storage file or permission denied.
//
#define APC_E_STORAGE_NOPERMISSION       0x80040563L

//
// MessageId: APC_E_MINIBITMAP_CANT_BE_CHANGED
//
// MessageText:
//
//  Can't change Picture property once displayed in the VBA IDE. The Picture property should only be changed once during initialization of the Apc object.
//
#define APC_E_MINIBITMAP_CANT_BE_CHANGED 0x80040564L

//
// MessageId: APC_E_CANTSAVE
//
// MessageText:
//
//  Can't save the storage file.
//
#define APC_E_CANTSAVE                   0x80040565L

//
// MessageId: APC_E_APP_OBJECT_REQUIRED
//
// MessageText:
//
//  You must specify an Application object when running from within Visual Basic.
//
#define APC_E_APP_OBJECT_REQUIRED        0x80040566L

//
// MessageId: APC_E_NO_COMP_MANAGER
//
// MessageText:
//
//  This function is only available to non-VB applications (that is, applications that have called IApc::put_MessageLoopSite).
//
#define APC_E_NO_COMP_MANAGER            0x80040567L

//
// MessageId: APC_E_NOT_A_FORM
//
// MessageText:
//
//  The specified parameter is not a valid UserForm.
//
#define APC_E_NOT_A_FORM                 0x80040568L

//
// MessageId: APC_E_NO_UI
//
// MessageText:
//
//  No UI is allowed. The host application does not support the proper message loop integration interfaces (that is, IVbaCompManagerSite or IApcSite).
//
#define APC_E_NO_UI                      0x80040569L

//
// MessageId: APC_E_STILL_LOADING_CONTROLS
//
// MessageText:
//
//  The controls on a host project item are not in the running state; you must call FinishedLoadingControls.
//
#define APC_E_STILL_LOADING_CONTROLS     0x8004056AL

//
// MessageId: APC_E_MACRO_NAME_CONFLICT
//
// MessageText:
//
//  The specified macro name already exists in the code module or host project item. Macro names must be unique.
//
#define APC_E_MACRO_NAME_CONFLICT        0x8004056BL

//
// MessageId: APC_E_BROKEN_REFERENCE
//
// MessageText:
//
//  This VBA project contains a broken reference.
//
#define APC_E_BROKEN_REFERENCE           0x8004056CL

//
// MessageId: APC_E_FILENOTFOUND
//
// MessageText:
//
//  The system cannot find the file specified.
//
#define APC_E_FILENOTFOUND               0x8004056DL

//
// MessageId: APC_E_NO_VBA_PROJECTITEM
//
// MessageText:
//
//  There is no VBA project item associated with this object.
//
#define APC_E_NO_VBA_PROJECTITEM         0x8004056EL

//
// MessageId: APC_E_CONTROLNOTREGISTERED
//
// MessageText:
//
//  The specified CLSID is not a properly registered licensed control.
//
#define APC_E_CONTROLNOTREGISTERED       0x8004056FL

//
// MessageId: APC_E_BADLICENSEDCONTROL
//
// MessageText:
//
//  The specified control is not a registered licensed control.
//
#define APC_E_BADLICENSEDCONTROL         0x80040570L

//
// MessageId: APC_E_CANTREGISTERCONTROL
//
// MessageText:
//
//  Unable to register the specified licensed control.
//
#define APC_E_CANTREGISTERCONTROL        0x80040571L

//
// MessageId: APC_E_CANTREADREGISTRY
//
// MessageText:
//
//  Error reading registration database.
//
#define APC_E_CANTREADREGISTRY           0x80040572L

//
// MessageId: APC_E_NOAGGREGATION
//
// MessageText:
//
//  The specified licensed control cannot be created as part of an aggregate.
//
#define APC_E_NOAGGREGATION              0x80040573L

//
// MessageId: APC_E_INVALIDCLASSID
//
// MessageText:
//
//  The specified CLSID is not valid.
//
#define APC_E_INVALIDCLASSID             0x80040574L

//
// MessageId: APC_E_EXTCLASSNOTREGISTERED
//
// MessageText:
//
//  Extender class not registered via RegisterExtenderClass().
//
#define APC_E_EXTCLASSNOTREGISTERED      0x80040575L

//
// MessageId: APC_E_STREAM_OR_STORAGE_ALREADYEXISTS
//
// MessageText:
//
//  Specified stream or storage already exists.
//
#define APC_E_STREAM_OR_STORAGE_ALREADYEXISTS 0x80040576L

//
// MessageId: APC_E_NOTIMPLEMENTED
//
// MessageText:
//
//  Not implemented.
//
#define APC_E_NOTIMPLEMENTED             0x80040577L

//
// MessageId: APC_E_PROJECT_IS_PROTECTED
//
// MessageText:
//
//  Operation failed; this project is protected.
//
#define APC_E_PROJECT_IS_PROTECTED       0x80040578L

//
// MessageId: APC_E_NOT_IN_DESIGN_MODE
//
// MessageText:
//
//  VBA is unable to execute code because the project is in Design mode.
//
#define APC_E_NOT_IN_DESIGN_MODE         0x80040579L

//
// MessageId: APC_E_MACROS_ARE_DISABLED
//
// MessageText:
//
//  VBA is unable to execute code because the project was opened with macros disabled.
//
#define APC_E_MACROS_ARE_DISABLED        0x8004057AL

//
// MessageId: APC_E_NO_CONTROL_TYPELIBRARY_GUID
//
// MessageText:
//
//  Can't create control type library. Before controls can be created or loaded, a control type library GUID must be established by setting the ControlLibraryGuid property.
//
#define APC_E_NO_CONTROL_TYPELIBRARY_GUID 0x8004057BL

//
// MessageId: APC_E_USERFORM_NOT_SUPPORTED
//
// MessageText:
//
//  This property or method does not support UserForms.
//
#define APC_E_USERFORM_NOT_SUPPORTED     0x8004057CL

//
// MessageId: APC_E_DUPLICATE_DOCUMENT_OBJECT_SPECIFIED
//
// MessageText:
//
//  Duplicate document object specified.
//
#define APC_E_DUPLICATE_DOCUMENT_OBJECT_SPECIFIED 0x8004057DL

//
// MessageId: APC_E_INVALID_PROPERTY_TYPE
//
// MessageText:
//
//  This method does not support Property Let, Property Get, or Property Set routines.
//
#define APC_E_INVALID_PROPERTY_TYPE      0x8004057EL

//
// MessageId: APC_E_INVALIDVARIANT_OR_INVALIDSEEKPOS
//
// MessageText:
//
//  The stream contains corrupt data, or the current seek position is invalid.
//
#define APC_E_INVALIDVARIANT_OR_INVALIDSEEKPOS 0x8004057FL

//
// MessageId: APC_E_HOSTOBJECT_REQUIRED
//
// MessageText:
//
//  Host object required for project items of this type.
//
#define APC_E_HOSTOBJECT_REQUIRED        0x80040580L

//
// MessageId: APC_E_INVALID_HOSTOBJECT
//
// MessageText:
//
//  Host object not required for project items of this type.
//
#define APC_E_INVALID_HOSTOBJECT         0x80040581L

//
// MessageId: APC_E_HOST_ALREADYINITIALIZED
//
// MessageText:
//
//  The host object has already been initialized.
//
#define APC_E_HOST_ALREADYINITIALIZED    0x80040582L

//
// MessageId: APC_E_EVENTSINK_ALREADYINITIALIZED
//
// MessageText:
//
//  The event sink has already been initialized.
//
#define APC_E_EVENTSINK_ALREADYINITIALIZED 0x80040583L

//
// MessageId: APC_E_EVENTSINK_INVALID
//
// MessageText:
//
//  The event sink has already been uninitialized or was not set.
//
#define APC_E_EVENTSINK_INVALID          0x80040584L

//
// MessageId: APC_E_EVENTSINK_INVALIDCOOKIE
//
// MessageText:
//
//  The cookie supplied to uninitialize the event sink is invalid.
//
#define APC_E_EVENTSINK_INVALIDCOOKIE    0x80040585L

//
// MessageId: APC_E_VBAMACROENABLE_DONTOPEN
//
// MessageText:
//
//  The user does not want to open a project because it contains macros.
//
#define APC_E_VBAMACROENABLE_DONTOPEN    0x80040586L

//
// MessageId: APC_E_CONTROL_LIBRARY_ALREADY_MADE
//
// MessageText:
//
//  Unable to set this property -- the control type library has already been created.
//
#define APC_E_CONTROL_LIBRARY_ALREADY_MADE 0x80040587L

//
// MessageId: APC_E_FAILED_VBASIGNPROJECT
//
// MessageText:
//
//  Unable to sign project.  Signature will not be saved.
//
#define APC_E_FAILED_VBASIGNPROJECT      0x80040588L

//
// MessageId: APC_E_INVALID_USERPASSWORD
//
// MessageText:
//
//  User password is incorrect.  LockForViewing state is unchanged.
//
#define APC_E_INVALID_USERPASSWORD       0x80040589L

//
// MessageId: APC_E_ONLYDOCCLASSES
//
// MessageText:
//
//  Method or property valid only for document class project items.
//
#define APC_E_ONLYDOCCLASSES             0x8004058AL

//
// MessageId: APC_E_HOSTADDINS_ALREADYINITIALIZED
//
// MessageText:
//
//  The HostAddIns object has already been initialized.
//
#define APC_E_HOSTADDINS_ALREADYINITIALIZED 0x8004058BL

//
// MessageId: APC_E_HOSTADDINSINIT_NOREGISTRYPATH
//
// MessageText:
//
//  The HostAddIns initialization requires registry path for addins.
//
#define APC_E_HOSTADDINSINIT_NOREGISTRYPATH 0x8004058CL

//
// MessageId: APC_E_HOSTADDINSINIT_NOLICENSEKEY
//
// MessageText:
//
//  The HostAddIns initialization requires valid license key.
//
#define APC_E_HOSTADDINSINIT_NOLICENSEKEY 0x8004058DL

//
// MessageId: APC_E_HOSTADDINSINIT_NOHOSTOBJECT
//
// MessageText:
//
//  The HostAddIns initialization requires host object with IDispatch.
//
#define APC_E_HOSTADDINSINIT_NOHOSTOBJECT 0x8004058EL

//
// MessageId: APC_E_HOSTADDINSINIT_NOAPCOBJECT
//
// MessageText:
//
//  The HostAddIns initialization requires host object with IDispatch. Attempt to use APC's Application Object failed.
//
#define APC_E_HOSTADDINSINIT_NOAPCOBJECT 0x8004058FL

//
// MessageId: APC_E_HOSTADDINSPUT_INVALID_REGISTRYPATH
//
// MessageText:
//
//  The registry path is invalid and will not be assigned to HostAddIns object.
//
#define APC_E_HOSTADDINSPUT_INVALID_REGISTRYPATH 0x80040590L

//
// MessageId: APC_E_BACKCOLOR_CANT_BE_CHANGED
//
// MessageText:
//
//  Can't change BackColor property once displayed in the VBA IDE. The BackColor property should only be changed once during initialization of the Apc object.
//
#define APC_E_BACKCOLOR_CANT_BE_CHANGED  0x80040591L

//
// MessageId: APC_E_CONTROL_MARKED_FOR_DELETE
//
// MessageText:
//
//  The control was marked for delete during load, this error should have been expected.
//
#define APC_E_CONTROL_MARKED_FOR_DELETE  0x80040592L

//
// MessageId: APC_E_HOSTADDINSINIT_FAILED
//
// MessageText:
//
//  Initialization of HostAddIns failed.
//
#define APC_E_HOSTADDINSINIT_FAILED      0x80040593L

//
// MessageId: APC_E_SHOWADDINSDIALOG_FAILED
//
// MessageText:
//
//  Must initialize VBA IDE before calling ShowAddinsDialog.
//
#define APC_E_SHOWADDINSDIALOG_FAILED    0x80040594L

//
// MessageId: APC_E_NOTRECORDING
//
// MessageText:
//
//  This method or property may only be accessed during recording.
//
#define APC_E_NOTRECORDING               0x80040595L

//
// MessageId: APC_E_ROUNDTRIP_STREAM_NOT_FOUND
//
// MessageText:
//
//  Roundtrip stream not found in stream list.
//
#define APC_E_ROUNDTRIP_STREAM_NOT_FOUND 0x80040596L

//
// MessageId: APC_E_ROUNDTRIP_STORAGE_NOT_FOUND
//
// MessageText:
//
//  Roundtrip storage not found in storage list.
//
#define APC_E_ROUNDTRIP_STORAGE_NOT_FOUND 0x80040597L

//
// MessageId: APC_E_ROUNDTRIP_STORAGE_NOT_INITIALIZED
//
// MessageText:
//
//  Roundtrip storage has no IStorage assigned.
//
#define APC_E_ROUNDTRIP_STORAGE_NOT_INITIALIZED 0x80040598L

//
// MessageId: APC_E_INVALID_LICENSE_KEY
//
// MessageText:
//
//  VBA Initialization failed due to an invalid License Key.
//
#define APC_E_INVALID_LICENSE_KEY        0x80040599L

//
// MessageId: APC_E_CANT_RUN_IN_BREAK_MODE
//
// MessageText:
//
//  Unable to execute VBA code while in break mode.
//
#define APC_E_CANT_RUN_IN_BREAK_MODE     0x8004059AL

//
// MessageId: APC_E_DIGITAL_SIGNING_DISABLED
//
// MessageText:
//
//  Method or property requires that Digital Signatures be enabled.
//
#define APC_E_DIGITAL_SIGNING_DISABLED   0x8004059BL

//
// MessageId: APC_E_ACTIONCANCELLED
//
// MessageText:
//
//  Action was cancelled by the user.
//
#define APC_E_ACTIONCANCELLED            0x8004059CL

//
// MessageId: APC_E_COLLECTION_ADD_DUPLICATEKEY
//
// MessageText:
//
//  This key is already associated with an element of this collection.
//
#define APC_E_COLLECTION_ADD_DUPLICATEKEY 0x8004059DL

//
// MessageId: APC_E_COLLECTION_ITEMS_NOT_IDISPATCH
//
// MessageText:
//
//  _NewEnum requires Collection items that support IDispatch.
//
#define APC_E_COLLECTION_ITEMS_NOT_IDISPATCH 0x8004059EL

//
// MessageId: APC_S_SIGNFAILED
//
// MessageText:
//
//  Unable to digitally sign the VBA project.
//
#define APC_S_SIGNFAILED                 0x4004059FL

//
// MessageId: APC_E_LAST_ERROR
//
// MessageText:
//
//  
//
#define APC_E_LAST_ERROR                 0x800405A0L

