/* --------------------------------------------------------------------------
 * apcMidl.h 
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
#ifndef APCMIDL_H_INCLUDED
#define APCMIDL_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// Versions

#define APC_VER 640	// APC Version 6.3
#define APC_MAJOR 6
#define APC_MINOR 4

/////////////////////////////////////////////////////////////////////////////
// Import Mode
//
// All modes except APC_IMPORT_MIDL require Visual C++ 5.0 or higher.
// When using Visual C++ 4.2, define APC_IMPORT_MIDL to use the MIDL-generated
// header file.
//
// One of the following must be defined to specify the import mode used
// for the header files in the APC wrappers (ApcCpp.h, ApcMfc.h)
//
//    APC_IMPORT_MIDL: to use type library header files (default)
//       APC_IMPORT_NAMED_GUIDS will be defined automatically
//       APC_IMPORT_RAW_ONLY will be defined automatically
//
//    For the following modes, include "apc.h" instead of this file
//    APC_IMPORT_FULL: to use #import with no options
//    APC_IMPORT_NAMED_GUIDS: to use #import with named_guids attribute 
//       this can be defined along with APC_IMPORT_RAW_ONLY
//    APC_IMPORT_RAW_ONLY: to use #import with raw_interfaces_only attribute
//       this can be defined along with APC_IMPORT_NAMED_GUIDS
//
// if none of the above import modes will work for you, then #import the 
// files yourself and define the APC_RAW, APC_GET, APC_PUT and APC_PUTREF 
// macros, and define APC_IMPORT_CUSTOM.  You are responsible for including 
// the appropriate type library information
//

/////////////////////////////////////////////////////////////////////////////
// Inclusion of this file (ApcMidl.h) is appropriate with the following import modes:
//
// APC_IMPORT_MIDL (default)

/////////////////////////////////////////////////////////////////////////////
// Error Conditions

#ifdef APC_IMPORT_MODE
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

#ifdef APCIMPORT_H_INCLUDED
	#error *** Do not include both Apc.h and ApcMidl.h.  See comments above ***
#endif

#if (defined(APC_IMPORT_FULL) || defined(APC_IMPORT_NAMED_GUIDS) || defined(APC_IMPORT_RAW_ONLY))
	#error *** include Apc.h instead of ApcMidl.h when defining these import modes ***
#endif

#ifndef APC_IMPORT_MIDL
	#pragma message(__FILE__ " : APC warning : APC_IMPORT_MIDL not defined, using default")
	#define APC_IMPORT_MIDL
#endif

#ifdef APC_IMPORT_CUSTOM
	#if !(defined(APC_RAW) && defined(APC_GET) && defined(APC_PUT) && defined(APC_PUTREF))
		#pragma message("APC_IMPORT_CUSTOM requires that APC_RAW, APC_GET, APC_PUT and APC_PUTREF are all defined")
	#endif
	#error *** APC_IMPORT_MIDL cannot be used with APC_IMPORT_CUSTOM ***
#endif

// ALWAYS defined for the MIDL import mode
#define APC_IMPORT_NAMED_GUIDS
#define APC_IMPORT_RAW_ONLY

// win32 includes

#include <ole2.h>
#include <servprov.h>
#include <olectl.h> // IProvideDynamicClassInfo requires IProvideClassInfo 

// vba sdk includes

#include <vbaguids.h>
#include <objext.h>
#include <vba.h>

/////////////////////////////////////////////////////////////////////////////
// The APC_RAW, APC_GET, APC_PUT and APC_PUTREF macros are used to internally 
// in the Apc header files adjust the Apc headers for whatever prefixes are 
// hard-coded into the client code.

#if defined(APC_RAW) || defined(APC_GET) || defined(APC_PUT) || defined(APC_PUTREF)
	#error APC_RAW, APC_GET, APC_PUT and APC_PUTREF can only be user defined when APC_IMPORT_MODE is APC_IMPORT_CUSTOM
#endif

#define APC_RAW(name) name
#define APC_GET(name) get_##name
#define APC_PUT(name) put_##name
#define APC_PUTREF(name) putref_##name

// the APC_BOOL and SID_SApc macros

#define APC_BOOL BOOL

// the APC_DIID, APC_IID and APC_CLSID macros

#define APC_DIID(name) DIID_##name
#define APC_DIID_(scope,name) scope::DIID_##name
#define APC_IID(name) IID_##name
#define APC_IID_(scope,name) scope::IID_##name
#define APC_CLSID(name) CLSID_##name
#define APC_CLSID_(scope,name) scope::CLSID_##name
#define APC_NAMED_GUIDS named_guids

// the APC_PTRDECL, APC_PTRSET and APC_PTRREL macros

#define APC_PTRDECL(name)	CComPtr<name>
#define APC_PTRSET(name,rhs){APC_PTRDECL(name)::operator=(rhs);}
#define APC_PTRREL(name)	{APC_PTRDECL(name)::Release();}
#define APC_RAW_INTERFACES_ONLY raw_interfaces_only

/////////////////////////////////////////////////////////////////////////////
// includes
//

/////////////////////////////////////////////////////////////////////////////
// namespace Office--includes CommandBars--see VBAOFF9.HLP

namespace Office 
{
    #include <msotl.h>
}

/////////////////////////////////////////////////////////////////////////////
// namespace VBA--the vba runtime--see VBLR6.HLP

#include <rpc.h>
#include <rpcndr.h>
#include <objidl.h>
#include <oleidl.h>

#define CLSID_DEFINED	// prevent MIDL-generated files from redefining CLSID in different namespaces

/////////////////////////////////////////////////////////////////////////////
// namespace VBIDE--the development environment--see VBOB6.HLP

namespace VBIDE 
{
	using Office::CommandBars;
	#include <vbaext.h>
}

/////////////////////////////////////////////////////////////////////////////
// namespace MSForms--the forms package--see FM20.HLP

// forms package not included in MIDL mode

/////////////////////////////////////////////////////////////////////////////
// namespace MSAPC--for hosting vba--see VBA6SDK.CHM

namespace MSAPC 
{
	using VBIDE::VBE;
	using VBIDE::VBProject;
	using VBIDE::_VBProjects;
	using VBIDE::_VBComponent;
	using VBIDE::_VBComponents;
	using ::tagMSG;

	#include <apcTLB.h>
}

/////////////////////////////////////////////////////////////////////////////
// after #including this file, use the statement
// "using namespace MSAPC;" to make the contents 
// of the APC namespace available in the default namespace

#endif //APCMIDL_H_INCLUDED

