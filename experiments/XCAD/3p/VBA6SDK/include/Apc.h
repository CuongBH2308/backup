/* --------------------------------------------------------------------------
 * apc.h 
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
#ifndef APCIMPORT_H_INCLUDED
#define APCIMPORT_H_INCLUDED
/*
 * Preprocessor modifiers for this file:
 *
 * define APC_NO_OLE_COLOR if there is a redefinition conflict with OLE_COLOR
 * define APC_FORCE_DEBUG or APC_FORCE_RELEASE to force the #importing of 
 *    DEBUG/RELEASE versions of .dll's.  The default uses _DEBUG as the 
 *    indicator to determine which version to #import.
 */
/////////////////////////////////////////////////////////////////////////////
// Versions

#define APC_VER 640	// APC Version 6.4
#define APC_MAJOR 6
#define APC_MINOR 4

/////////////////////////////////////////////////////////////////////////////
// Import Mode
//
// All modes except APC_IMPORT_MIDL require Visual C++ 5.0 or higher.
// When using Visual C++ 4.2, define APC_IMPORT_MIDL to use the MIDL-generated
// header file
//
// One of the following must be defined to specify the import mode used
// for the header files in the APC wrappers (ApcCpp.h, ApcMfc.h)
//
//    APC_IMPORT_FULL: to use #import with no options
//    APC_IMPORT_NAMED_GUIDS: to use #import with named_guids attribute 
//       this can be defined along with APC_IMPORT_RAW_ONLY
//    APC_IMPORT_RAW_ONLY: to use #import with raw_interfaces_only attribute
//       this can be defined along with APC_IMPORT_NAMED_GUIDS
//
//    APC_IMPORT_MIDL: use ApcMidl.h instead of this file to use type 
//       library header files (default)
//
// if none of the above import modes will work for you, then #import the 
// files yourself and define the APC_RAW, APC_GET, APC_PUT and APC_PUTREF 
// macros, and define APC_IMPORT_CUSTOM.  You are responsible for including 
// the appropriate type library information
//

/////////////////////////////////////////////////////////////////////////////
// Inclusion of this file (apc.h) is appropriate with the following import modes:
//
// APC_IMPORT_FULL
// APC_IMPORT_RAW_ONLY
// APC_IMPORT_NAMED_GUIDS
// APC_IMPORT_RAW_ONLY and APC_IMPORT_NAMED_GUIDS

/////////////////////////////////////////////////////////////////////////////
// Error Conditions

#ifdef APCMIDL_H_INCLUDED
	#error *** Do not include both Apc.h and ApcMidl.h.  See comments above ***
#endif

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

#if (!defined(APC_IMPORT_FULL) && !defined(APC_IMPORT_CUSTOM) && !defined(APC_IMPORT_NAMED_GUIDS) && !defined(APC_IMPORT_RAW_ONLY))
	#pragma message(__FILE__ " : APC warning : no APC_IMPORT_ defined, using default of APC_IMPORT_FULL")
	#define APC_IMPORT_FULL
#endif

#ifdef APC_IMPORT_MIDL
	#error *** include ApcMidl.h instead of Apc.h ***
#endif

#if !defined(APC_IMPORT_MIDL) && (_MSC_VER < 1100)
	#error *** When using Visual C++ 4.2, define APC_IMPORT_MIDL ***
#endif

#ifdef APC_IMPORT_CUSTOM
	#if !(defined(APC_RAW) && defined(APC_GET) && defined(APC_PUT) && defined(APC_PUTREF))
		#pragma message("*** APC_IMPORT_CUSTOM requires that APC_RAW, APC_GET, APC_PUT and APC_PUTREF are all defined ***")
	#endif
	#error *** "apc.h" cannot be used with APC_IMPORT_CUSTOM.  The CUSTOM mode requires a custom header ***
#endif

// win32 includes

#include <comdef.h>
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
	#error APC_RAW, APC_GET, APC_PUT and APC_PUTREF can only be user defined when the import mode is APC_IMPORT_CUSTOM
#endif

#ifdef APC_IMPORT_RAW_ONLY
	#define APC_RAW(name) name
#else
	#define APC_RAW(name) raw_##name
#endif

#define APC_GET(name) get_##name
#define APC_PUT(name) put_##name
#define APC_PUTREF(name) putref_##name

// the APC_BOOL and SID_SApc macros

#define APC_BOOL long
#define SID_SApc APC_IID(IApcX)

// the APC_DIID, APC_IID and APC_CLSID macros

#ifdef APC_IMPORT_NAMED_GUIDS
	#define APC_DIID(name) DIID_##name
	#define APC_DIID_(scope,name) scope::DIID_##name
	#define APC_IID(name) IID_##name
	#define APC_IID_(scope,name) scope::IID_##name
	#define APC_CLSID(name) CLSID_##name
	#define APC_CLSID_(scope,name) scope::CLSID_##name
	#define APC_NAMED_GUIDS named_guids
#else
	#define APC_DIID(name) __uuidof(name)
	#define APC_DIID_(scope,name) __uuidof(scope::name)
	#define APC_IID(name) __uuidof(name)
	#define APC_IID_(scope,name) __uuidof(scope::name)
	#define APC_CLSID(name) __uuidof(name)
	#define APC_CLSID_(scope,name) __uuidof(scope::name)
	#define APC_NAMED_GUIDS
#endif

#ifndef APC_CUSTOM_IMPORT_ATTRIBUTES
	#define APC_CUSTOM_IMPORT_ATTRIBUTES
#endif

// the APC_PTRDECL, APC_PTRSET and APC_PTRREL macros

#ifdef APC_IMPORT_RAW_ONLY
	#define APC_PTRDECL(name)	CComPtr<name>
	#define APC_PTRSET(name,rhs){APC_PTRDECL(name)::operator=(rhs);}
	#define APC_PTRREL(name)	{APC_PTRDECL(name)::Release();}
	#define APC_RAW_INTERFACES_ONLY raw_interfaces_only
#else
	#define APC_PTRDECL(name)	name##Ptr
	#define APC_PTRSET(name,rhs){APC_PTRDECL(name)::operator=(static_cast<name*>(rhs));}
	#define APC_PTRREL(name)	{APC_PTRDECL(name)::operator=(0);}
	#define APC_RAW_INTERFACES_ONLY
#endif

/////////////////////////////////////////////////////////////////////////////
// imports
//
// The following #import directives instruct the compiler to convert the
// type libraries of the specified files into a header file, then include that
// behind the scenes. The files generated are placed into the output directory
// with a .TLH file extension.
//
// The VC5 docs say that for these #imports to work, the directory
// \Program Files\Common Files\Microsoft Shared\VBA\VBA6 must be listed in the 
// compiler's LIB or PATH environment variable. In order to find mso, you must
// also include \Program Files\Common Files\Microsoft Shared\Office10.
/////////////////////////////////////////////////////////////////////////////
// namespace Office--includes CommandBars--see VBAOFF9.HLP

#if defined(APC_FORCE_DEBUG) && defined(APC_FORCE_RELEASE)
	#error *** do not define both APC_FORCE_DEBUG and APC_FORCE_RELEASE
#endif

#if !defined(APC_FORCE_DEBUG) && !defined(APC_FORCE_RELEASE)
	#ifdef _DEBUG
		#define APC_FORCE_DEBUG
	#else
		#define APC_FORCE_RELEASE
	#endif
#endif

#pragma warning(disable : 4146)	// #import creates files with this warning
#ifdef APC_FORCE_DEBUG
	#import "msod.dll" APC_RAW_INTERFACES_ONLY APC_NAMED_GUIDS APC_CUSTOM_IMPORT_ATTRIBUTES
#else
	#import "mso.dll" APC_RAW_INTERFACES_ONLY APC_NAMED_GUIDS APC_CUSTOM_IMPORT_ATTRIBUTES
#endif
#pragma warning(default : 4146)	// set warning back to default

/////////////////////////////////////////////////////////////////////////////
// namespace VBA--the vba runtime--see VBLR6.HLP

namespace VBA 
{
	#ifndef APC_IMPORT_NAMED_GUIDS
		// #import does not produce a guid for the typelib, but we need one
		extern "C" const GUID __declspec(selectany) LIBID_VBA =
			{0x000204EF,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
	#endif
}

/////////////////////////////////////////////////////////////////////////////
// namespace VBIDE--the development environment--see VBOB6.HLP

#import "vbe6ext.olb" APC_RAW_INTERFACES_ONLY APC_NAMED_GUIDS APC_CUSTOM_IMPORT_ATTRIBUTES

/////////////////////////////////////////////////////////////////////////////
// namespace MSAPC--for hosting vba--see VBA6SDK.CHM

namespace MSAPC 
{
	#ifndef APC_IMPORT_NAMED_GUIDS
		// #import does not produce a guid for the typelib, but we need one
		extern "C" const GUID __declspec(selectany) LIBID_APC =
			{0x81b1e710,0xd07d,0x11d0,{0xab,0xab,0xf4,0x51,0xc4,0x00,0x00,0x00}};
	#endif

	#ifndef APC_NO_OLE_COLOR
		typedef DWORD OLE_COLOR;
	#endif

	struct Picture: IPictureDisp {};
	#ifndef APC_IMPORT_RAW_ONLY
		typedef IPictureDispPtr PicturePtr;
	#endif
}

#ifdef GUID
	#error GUID is redefined
#endif
//
// the rename ("GUID", "_GUID") directive is related to a bug
// in #import, as discussed in MSDN Article ID: Q185284
//

#define APCEXCLUDES \
		exclude ("IStream") \
		exclude ("IStorage") \
		exclude ("ISequentialStream") \
		exclude ("IEnumSTATSTG") \
		exclude ("IPersist") \
		exclude ("IPersistStorage") \
		exclude ("_LARGE_INTEGER") \
		exclude ("_ULARGE_INTEGER") \
		exclude ("_FILETIME") \
		exclude ("wireSNB") \
		exclude ("tagRemSNB") \
		exclude ("tagSTATSTG")

#ifdef APC_FORCE_DEBUG
	#import "apc64d.dll" APC_RAW_INTERFACES_ONLY APC_NAMED_GUIDS APC_CUSTOM_IMPORT_ATTRIBUTES \
				rename ("GUID", "_GUID") \
				APCEXCLUDES
#else
	#import "apc64.dll" APC_RAW_INTERFACES_ONLY APC_NAMED_GUIDS APC_CUSTOM_IMPORT_ATTRIBUTES \
				rename ("GUID", "_GUID") \
				APCEXCLUDES
#endif

#undef GUID

/////////////////////////////////////////////////////////////////////////////
// after #including this file, use the statement
// "using namespace MSAPC;" to make the contents 
// of the APC namespace available in the default namespace

#endif //APCIMPORT_H_INCLUDED

