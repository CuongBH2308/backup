#pragma pack(push, 8) 
//---------------------------------------------------------------------------
// Copyright (C) 1995-1998, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// IVBA.H
//---------------------------------------------------------------------------
//
// Contents:
// - Constants, Types, Enums
// - VBA interface definitions
// - VBA APIs
// - VBA Services
// - Controls Programmability
//
//---------------------------------------------------------------------------

#ifndef _IVBA_H
#define _IVBA_H

#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#endif

#include "objext.h"

// forward declares
#ifdef __cplusplus
interface IVba;
interface IVbaProject;
interface IVbaProjItem;
interface IVbaProcs;
interface IVbaProjItemCol;
interface IMsoComponentManager;
interface IOleComponentUIManager;
interface IVbaSite;
interface IVbaCompManagerSite;
interface IVbaProjectSecurity;
#else  // __cplusplus
typedef interface IVba IVba;
typedef interface IVbaProject IVbaProject;
typedef interface IVbaProjItem IVbaProjItem;
typedef interface IVbaProcs IVbaProcs;
typedef interface IVbaProjItemCol IVbaProjItemCol;
typedef interface IMsoComponentManager IMsoComponentManager;
typedef interface IOleComponentUIManager IOleComponentUIManager;
typedef interface IVbaSite IVbaSite;
typedef interface IVbaCompManagerSite IVbaCompManagerSite;
typedef interface IVbaProjectSecurity IVbaProjectSecurity;
#endif  // __cplusplus

///////////////////////////////////////////////////////////////////////////
//
// Constants, Types, Enums
//
///////////////////////////////////////////////////////////////////////////

typedef DWORD VBAMODTYPE;
#define VBAMODTYPE_StdMod	1
#define VBAMODTYPE_ClassMod	2


// Errors
#define VBA_E_NOUSERACTION             0x800A9D15L 
#define VBA_E_NOTOBJECT                0x800A01A8L
#define VBA_E_EXPECTEDFUNCNOTVAR       0x800A88CAL
#define VBA_E_SYNTAX                   0x800A9C70L
#define VBA_E_UNDEFINEDTYPE            0x800A8027L
#define VBA_E_INVALIDPROCNAME          0x800A9C82L
#define VBA_E_UNDEFINEDPROC            0x800A0023L
#define VBA_E_CANTEXECCODEINBREAKMODE  0x800ADF09L
#define VBA_E_MACROSDISABLED           0x800ADF23L
#define VBA_E_MODNAMECONFLICT          0x800A802DL
#define VBA_E_INVALIDSTATE             0x800A8029L
#define VBA_E_UNSUPFORMAT              0x800A8019L
#define VBA_E_ALREADYRECORDING         0x800AC470L
#define VBA_E_PROJECTPROTECTED         0x800AC471L
#define VBA_E_EXCEPTION                0x800AC461L
#define VBA_E_IGNORE                   0x800AC472L
#define VBA_E_RESET                    0x800A9C68L
#define VBA_E_CANTEXITDESIGNMODE       0x800ADF21L
#define VBA_E_CANTCONTINUE             0x800A0011L
#define VBA_E_MODULENOTFOUND           0x800A9C86L
#define VBA_E_PROJECTNOTFOUND          0x800A9C87L
#define VBA_E_COMPERRINHIDDENMODULE    0x800A9D09L      
#define VBA_E_RECORDMODCANTCHANGE      0x800A9D32L
#define VBA_E_COMPILEERROR             0x800A9C64L
#define VBA_E_ILLEGALNAME              0x800AC3D4L
#define VBA_E_FILENOTFOUND             0x800A0035L
#define VBA_E_PATHNOTFOUND             0x800A004CL
#define VBA_E_CLASSNOTREG              0x800A02C9L
#define VBA_E_COULDNTLOADFILE          0x800AC389L

typedef struct {
        UINT uVerMaj;
        UINT uVerMin;
        GUID guidTypelibAppObj;
        GUID guidTypeinfoAppObj;
} VBAAPPOBJDESC;

// Stand-Alone Project information
typedef enum { 
  VBASAPT_NONE= 1, // Renamed from VBASAPT_ADDIN since it is no longer used.
  VBASAPT_MT
}VBASAPROJTYPE;

typedef DWORD VBASAFLAGS;
#define vsaFLAG_CmdLineSupported  1

typedef struct {
        LPCOLESTR	    lpstrHostApp;	// Friendly name of the Host App
        LPCOLESTR	    lpstrRegPath;	// Registry Path for DLL registration
        VBAAPPOBJDESC	    vaodHost;		// Appobj information for this type of project
        VBASAPROJTYPE  vsaptType; //Type (Addin OR MT)
	VBASAFLAGS	    vsaFlags;  //host supports cmdline startup
} VBASAPROJINFO;

// Vba initialization struct
typedef struct {
	UINT	cbSize;		// size of structure for versioning

	DWORD   dwFlags;

	// host interfaces
	IMsoComponentManager *pMsoCompMgr;
	IVbaSite	 *pVbaSite;

	// host info
	LPCOLESTR lpstrName;
	LPCOLESTR lpstrRegKey;	// should be NULL to share settings
	LCID lcidUserInterface;

	// app object stuff
	IUnknown *punkAppObject;

	// more host info
	LPCOLESTR lpstrProjectFileFilter;

        // component manager info
        HWND hwndHost;
        HINSTANCE hinstHost;
        IVbaCompManagerSite *pVbaCompManagerSite;

	// Stand-alone project information
	GUID guidReserved;	// reserved
	UINT		    cSAProjTypes;	 // # of Stand-Alone Project types
        VBASAPROJINFO *rgvsapiProjTypes;

	VBAAPPOBJDESC	    vaodHost;

	// Help file to be used during Digital Signing's VerifyProject and associated conext ID
	LPCOLESTR lpstrDigSigVerifyProjectHelpFile;  
	DWORD     dwDigSigVerifyProjectContextID;    
	
	HINSTANCE  hinstReserved;
} VBAINITINFO;

// For VBAINITINFO::dwFlags: Setting this flag signals to VBA that
// the host wants to use WinHelp files instead of HTMLHelp files.
// for the core VBA Help files
#define VBAINITINFO_UseWinHelp                     0x00000001L

// For VBAINITINFO::dwFlags: Setting this flag will allow designers
//   that support the CATID_VbaDesigner component category to
//   be inserted into a non-standalone project.
//
#define VBAINITINFO_SupportVbaDesigners            0x00000002L

//
// For VBAINITINFO::dwFlags: Setting this flag signals to VBA that
// the host has done the work to support digital signatures.
//
#define VBAINITINFO_EnableDigitalSignatures        0x00000004L

//
// For VBAINITINFO::dwFlags: Setting this flag signals to VBA that
// the host is using a WIDE message loop (default without flag is ANSI)
//
#define VBAINITINFO_MessageLoopWide	           0x00000008L


//
// For VBAINITINFO::dwFlags: Setting this flag signals to VBA that
// the host doesn't want the IDE to be shown.
//
#define VBAINITINFO_DisableIDE                     0x00010000L


typedef enum {
	VBASTEPMODE_None,
	VBASTEPMODE_Into,
	VBASTEPMODE_Over,
} VBASTEPMODE;

// for IVbaSite::Notify
typedef enum {
	VBAHN_ExecuteCodeBegin,
	VBAHN_ExecuteCodeEnd,
        VBAHN_Activate,
        VBAHN_Reset,
        VBAHN_ModalDlgBegin,
        VBAHN_ModalDlgEnd,
	VBAHN_ResetToolbar,
} VBASITENOTIFY;

// for VBAPSN_ProcChanged
typedef struct {
	IVbaProjItem	*pvbaprojitem;
	LPCOLESTR	lpstrObjectName;
	LPCOLESTR	lpstrProcName;
	INVOKEKIND	invokekind;
} VBA_PROC_CHANGE_INFO;

// for IVbaSite::CanEnterBreakMode
typedef enum {
  VBA_BRKREASON_Error,
  VBA_BRKREASON_UserInterrupt,
  VBA_BRKREASON_Breakpoint,
  VBA_BRKREASON_WatchBreak,
  VBA_BRKREASON_HostBreak,
  VBA_BRKREASON_CompileError,
  VBA_BRKREASON_Assert
} VBA_BRKREASON;

// for IVbaSite::CanEnterBreakMode
typedef enum VBA_BRKOPT {
  VBA_BRKOPT_Continue,
  VBA_BRKOPT_Debug,
  VBA_BRKOPT_End,
  VBA_BRKOPT_InterruptError,
  VBA_BRKOPT_ContinueNoReset
} VBA_BRKOPT;

typedef struct {
  VBA_BRKOPT brkopt;
  VBA_BRKREASON brkreason;
} VBA_BRK_INFO;

// for IVbaProjectSite::Notify
typedef enum {
	VBAPSN_AfterProjectReset,
        VBAPSN_Activate,
        VBAPSN_ModalDlgBegin,
        VBAPSN_ModalDlgEnd,
        VBAPSN_SearchReplaceBegin,
        VBAPSN_SearchReplaceEnd,
} VBAPROJSITENOTIFY;

// for IVbaProjItem::GetItemType
typedef enum {
	VBAPIT_StdModule,
	VBAPIT_ClassModule,
	VBAPIT_Designer,
	VBAPIT_DocumentObject,
	VBAPIT_DocumentClass,
	VBAPIT_Other
} VBAPROJITEMTYPE;

typedef enum {
	VBA_PROJ_MODE_Design,
	VBA_PROJ_MODE_Use,
} VBA_PROJECT_MODE;

typedef WORD VBAPROJFLAGS;
#define VBAPROJFLAG_None          0x0000
#define VBAPROJFLAG_Hidden        0x0001
#define VBAPROJFLAG_DisableMacros 0x0002
#define VBAPROJFLAG_DisableSave	  0x0004

typedef enum {
	VBA_PROC_MODE_Wait,
	VBA_PROC_MODE_Run,
	VBA_PROC_MODE_Break
} VBA_PROCESS_MODE;

typedef WORD VBAPROCFLAGS;
#define	VBAPROCFLAG_None	  0x0000
#define	VBAPROCFLAG_Public	  0x0001
#define	VBAPROCFLAG_Private	  0x0002
#define	VBAPROCFLAG_Sub		  0x0004
#define	VBAPROCFLAG_Function	  0x0008
#define	VBAPROCFLAG_NoParameters  0x0010

typedef struct {
	BSTR 		bstrName;
	INVOKEKIND	invokekind;
	VBAPROCFLAGS	vbaprocflags;
	IVbaProjItem	*pVbaProjItem;
} VBAPROC;

typedef enum {
	Protection_None = 0,
	Protection_User = 1,
	Protection_Host = 2,
	Protection_VBA  = 4   // the VBA referred to by the world at large...
	// Note: next one's are 8, 16, 32, etc...
} PROTECTIONSTATE, * LPPROTECTIONSTATE;

typedef WORD VBAIDLEFLAGS;
#define VBAIDLEFLAG_Periodic    0x0001
#define VBAIDLEFLAG_NonPeriodic 0x0002
#define VBAIDLEFLAG_Priority    0x0004

typedef WORD VBAINFOFLAGS;
#define VBAINFOFLAG_ExclusiveBorderSpace 0x0001

typedef enum {
        VBACMSN_LostActivation    = 1,
        VBACMSN_HideBorderTools   = 2,
        VBACMSN_TrackingBegins    = 3,
        VBACMSN_TrackingEnds      = 4
} VBACMSITENOTIFY;

typedef enum {
        VBACOMPSTATE_Modal        = 1,
	// RedrawOff/WarningsOff/Recording are not used in the current version
        VBACOMPSTATE_RedrawOff    = 2,
        VBACOMPSTATE_WarningsOff  = 3,
        VBACOMPSTATE_Recording    = 4
} VBACOMPSTATE;

typedef enum {
        VBALOOPREASON_FocusWait   = 1,
        VBALOOPREASON_DoEvents    = 2,
        VBALOOPREASON_Debug       = 3,
        VBALOOPREASON_ModalForm   = 4
} VBALOOPREASON;

// for IVbaRecorder::BeginAction
#define  VBARECORD_ActionMax     10


// For Digital Signing: Macro Enable, IVba::VerifyProject()
typedef enum {
        VBAMacroEnable_Enable    = 1,
        VBAMacroEnable_Disable   = 2,
        VBAMacroEnable_DontOpen  = 3

}  VBAMACROENABLESTATE;

typedef enum {
        VBASecurityLevel_Undefined  = 0,
	VBASecurityLevel_None       = 1,
	VBASecurityLevel_Medium     = 2,
	VBASecurityLevel_High       = 3

}  VBADIGSIGSECURITYLEVEL;


//
// For VBAINITHOSTADDININFO::dwFlags: Setting this flag signals to VBA to
// disable the host add-ins on startup
//
#define VBAINITHOSTADDININFO_DisableOnStartup        0x00000002L


// For the IVbaHostAddins interface
typedef struct {
  DWORD dwCookie;
  LPOLESTR lpstrRegPath;
  LCID lcidHost;
  DWORD dwFlags;
  BOOL fRemoveFromListOnFailure;
  IDispatch *pdisp;
} VBAINITHOSTADDININFO;


///////////////////////////////////////////////////////////////////////////
//
// Host Interfaces
//  These are the interfaces implemented by the host
//
///////////////////////////////////////////////////////////////////////////

//-------------------
// IVbaSite interface
//-------------------
// {115dd106-2b24-11d2-aa6c-00c04f9901d2}
//DEFINE_GUID(IID_IVbaSite,0x115dd106, 0x2b24, 0x11d2, 0xaa, 0x6c, 0x0, 0xc0, 0x4f, 0x99, 0x01, 0xd2);

#undef  INTERFACE
#define INTERFACE  IVbaSite
DECLARE_INTERFACE_(IVbaSite, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaSite methods ***
	STDMETHOD(GetOwnerWindow)(THIS_ HWND *phwnd) PURE;
	STDMETHOD(Notify)(THIS_ VBASITENOTIFY vbahnotify) PURE;
	
	STDMETHOD(FindFile)(THIS_ LPCOLESTR lpstrFileName, BSTR *pbstrFullPath) PURE;
	STDMETHOD(GetMiniBitmap)(THIS_ REFGUID rgguid, HBITMAP *phbmp, COLORREF *pcrMask) PURE;

        STDMETHOD(CanEnterBreakMode)(THIS_ VBA_BRK_INFO *pbrkinfo) PURE;
        STDMETHOD(SetStepMode)(THIS_ VBASTEPMODE vbastepmode) PURE;
        STDMETHOD(ShowHide)(THIS_ BOOL fVisible) PURE;

        STDMETHOD(InstanceCreated)(THIS_ IUnknown *punkInstance) PURE;

	STDMETHOD(HostCheckReference)(THIS_ BOOL fSave, REFGUID rgguid,
				      UINT *puVerMaj, UINT *puVerMin) PURE;

        STDMETHOD(GetIEVersion)(THIS_  LONG *plMajVer, LONG *plMinVer, BOOL * pfCanInstall) PURE;
        STDMETHOD(UseIEFeature)(THIS_  LONG  lMajVer,  LONG  lMinVer,  HWND hwndOwner) PURE;

	STDMETHOD(ShowHelp)(THIS_ HWND hwnd, LPCOLESTR szHelp, UINT wCmd, DWORD dwHelpContext, BOOL fWinHelp) PURE;

	STDMETHOD(OpenProject)(THIS_ HWND hwndOwner, IVbaProject *pVbaRefProj,
                                     LPCOLESTR lpstrFileName, IVbaProject **ppVbaProj) PURE;

};


//---------------
// IVbaSite2 interface
//---------------

// {E6806260-6C85-11d3-8D61-00C04FB17665}
//DEFINE_GUID(IID_IVbaSite2, 0xe6806260, 0x6c85, 0x11d3, 0x8d, 0x61, 0x0, 0xc0, 0x4f, 0xb1, 0x76, 0x65);

#undef  INTERFACE
#define INTERFACE  IVbaSite2
DECLARE_INTERFACE_(IVbaSite2, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaSite2 methods ****
	STDMETHOD(FindFileWithVersion)(THIS_ LPCOLESTR lpstrFileName, BSTR *pbstrFullPath, 
	      WORD wMajor, WORD wMinor, LCID lcid) PURE;
};

//---------------
// IVbaSite3 interface
//---------------
// {AC7D567E-2A6F-11d4-B6B2-00C04FB17665}
//DEFINE_GUID(IID_IVbaSite3, 0xac7d567e, 0x2a6f, 0x11d4, 0xb6, 0xb2, 0x0, 0xc0, 0x4f, 0xb1, 0x76, 0x65);

#undef  INTERFACE
#define INTERFACE  IVbaSite3
DECLARE_INTERFACE_(IVbaSite3, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaSite3 methods ****
	STDMETHOD(FindFileWithVersion)(THIS_ LPCOLESTR lpstrFileName, BSTR *pbstrFullPath, 
	      WORD wMajor, WORD wMinor, LCID lcid, LPCOLESTR lpstrProjName) PURE;
};

//--------------------------
// IVbaProjectSite interface
//--------------------------


// {1B30B6B8-E44B-11d1-9915-00A0C9702442}
//DEFINE_GUID(IID_IVbaProjectSite, 0x1b30b6b8, 0xe44b, 0x11d1, 0x99, 0x15, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

#undef  INTERFACE
#define INTERFACE  IVbaProjectSite
DECLARE_INTERFACE_(IVbaProjectSite, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaProjectSite methods *** 
	STDMETHOD(GetOwnerWindow)(THIS_ HWND *phwnd) PURE;
	STDMETHOD(Notify)(THIS_ VBAPROJSITENOTIFY vbapsn) PURE;
	STDMETHOD(GetObjectOfName)(THIS_ LPCOLESTR lpstrName, IDocumentSite **ppDocSite) PURE;
	STDMETHOD(LockProjectOwner)(THIS_ BOOL fLock, BOOL fLastUnlockCloses) PURE;
	STDMETHOD(RequestSave)(THIS_ HWND hwndOwner) PURE;

        STDMETHOD(ReleaseModule)(THIS_ IVbaProjItem *pVbaProjItem) PURE;
        STDMETHOD(ModuleChanged)(THIS_ IVbaProjItem *pVbaProjItem) PURE;

        STDMETHOD(DeletingProjItem)(THIS_ IVbaProjItem *pVbaProjItem) PURE;

        STDMETHOD(ModeChange)(THIS_ VBA_PROJECT_MODE pvbaprojmode) PURE;
        STDMETHOD(ProcChanged)(THIS_ VBA_PROC_CHANGE_INFO *pvbapcinfo) PURE;

        STDMETHOD(ReleaseInstances)(THIS_ IVbaProjItem *pVbaProjItem) PURE;

        STDMETHOD(ProjItemCreated)(THIS_ IVbaProjItem *pVbaProjItem) PURE;

        STDMETHOD(GetMiniBitmapGuid)(THIS_ IVbaProjItem *pVbaProjItem, GUID *pguidMiniBitmap) PURE;

	STDMETHOD(GetSignature)(THIS_  void **ppvSignature, DWORD * pcbSign) PURE;
	STDMETHOD(PutSignature)(THIS_  void  *pvSignature,  DWORD   cbSign)  PURE;

        STDMETHOD(NameChanged)(THIS_ IVbaProjItem *pVbaProjItem, LPCOLESTR lpstrOldName) PURE;
        STDMETHOD(ModuleDirtyChanged)(THIS_ IVbaProjItem *pVbaProjItem, BOOL fDirty) PURE;

        STDMETHOD(CreateDocClassInstance)(THIS_ IVbaProjItem *pVbaProjItem, CLSID clsidDocClass,
                                          IUnknown *punkOuter, BOOL fIsPredeclared,
                                          IUnknown **ppunkInstance) PURE; 
};


//------------------------------
// IVbaCompManagerSite interface
//------------------------------
// {B3205671-FE45-11cf-8D08-00A0C90F2732}
//DEFINE_GUID(IID_IVbaCompManagerSite, 0xb3205671, 0xfe45, 0x11cf, 0x8d, 0x8, 0x0, 0xa0, 0xc9, 0xf, 0x27, 0x32);

#undef  INTERFACE
#define INTERFACE  IVbaCompManagerSite
DECLARE_INTERFACE_(IVbaCompManagerSite, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaCompManagerSite methods ***
        STDMETHOD(Notify)(VBACMSITENOTIFY vbacmsn) PURE;
        STDMETHOD(EnterState)(THIS_ VBACOMPSTATE vbacompstate, BOOL fEnter) PURE;
        STDMETHOD(PushMessageLoop)(THIS_ VBALOOPREASON vbaloopreason, BOOL *pfAborted) PURE;
        STDMETHOD(ContinueIdle)(THIS_ BOOL *pfContinue) PURE;
        STDMETHOD(DoIdle)(THIS) PURE;
};

//----------------------------
// IVbaMallocSpySite interface
//----------------------------
// {BCBCD7E0-B464-11cf-9F76-00AA00BDCC9A}
//DEFINE_GUID(IID_IVbaMallocSpySite, 0xbcbcd7e0, 0xb464, 0x11cf, 0x9f, 0x76, 0x0, 0xaa, 0x0, 0xbd, 0xcc, 0x9a);

#undef  INTERFACE
#define INTERFACE  IVbaMallocSpySite
DECLARE_INTERFACE_(IVbaMallocSpySite, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaMallocSpySite methods ***
	STDMETHOD(BeginMarkAsIgnorable)(THIS) PURE;
        STDMETHOD(EndMarkAsIgnorable)(THIS) PURE;
};



///////////////////////////////////////////////////////////////////////////
//
// VBA Interfaces
//
///////////////////////////////////////////////////////////////////////////

//----------------------
// IVbaProject interface
//----------------------
// {CD9B1AC5-FAA3-11d1-9922-00A0C9702442}
//DEFINE_GUID(IID_IVbaProject, 0xcd9b1ac5, 0xfaa3, 0x11d1, 0x99, 0x22, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

#undef  INTERFACE
#define INTERFACE  IVbaProject
DECLARE_INTERFACE_(IVbaProject, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaProject attributes ***
	STDMETHOD(GetName)(THIS_ BSTR *pbstrName) PURE;
	STDMETHOD(SetName)(THIS_ LPCOLESTR lpstrName) PURE;

	STDMETHOD(IsDirty)(THIS_ BOOL *pfDirty) PURE;
	STDMETHOD(SetDirty)(THIS_ BOOL fDirty) PURE;

	// Macro manipulation
        STDMETHOD(GetVbaProcs)(THIS_ IVbaProcs **ppVbaProcs) PURE;

	// Executing a single line of code.
	STDMETHOD(ParseLine)(THIS_ LPCOLESTR lpstrLine) PURE;
	STDMETHOD(ExecuteLine)(THIS_ LPCOLESTR lpstrLine) PURE;

	// *** Project methods ***
	STDMETHOD(GetVbaObject)(THIS_ IVba **ppvba) PURE;

	STDMETHOD(GetMode)(THIS_ VBA_PROJECT_MODE *pmode) PURE;
	STDMETHOD(SetMode)(THIS_ VBA_PROJECT_MODE mode) PURE;

	STDMETHOD(GetProjItemCol)(THIS_ IVbaProjItemCol **ppVbaProjItemCol) PURE;

	STDMETHOD(LoadComplete)(THIS) PURE;

	STDMETHOD(SetFileName)(THIS_ LPCOLESTR lpstrPath) PURE;
	STDMETHOD(GetFileName)(THIS_ BSTR *pbstrPath) PURE;
	STDMETHOD(Compile)(THIS) PURE;

	STDMETHOD(Close)(THIS) PURE;
	STDMETHOD(GetExtensibilityObject)(THIS_ IDispatch ** ppDispatch) PURE;
	STDMETHOD(Protect)(THIS_ BOOL fProtect) PURE;
	STDMETHOD(GetProtectionState)(THIS_ LPPROTECTIONSTATE lpProtectionState) PURE;
	STDMETHOD(SetDisplayName)(THIS_ LPCOLESTR lpstrDisplayName) PURE;

        STDMETHOD(AddTypeLibRef)(THIS_ GUID guidTypeLib, UINT uVerMaj, UINT uVerMin) PURE;
        STDMETHOD(LockForViewing)(THIS_ LPCOLESTR lpstrPassword, BOOL fLock) PURE;
        STDMETHOD(IsCompiled)(THIS_ BOOL *pfCompiled) PURE;

	STDMETHOD(SetDelayProtectionState)(THIS_ BOOL   fDelayProtection) PURE;
	STDMETHOD(GetDelayProtectionState)(THIS_ BOOL* pfDelayProtection) PURE;

	STDMETHOD(SignProject)( THIS_ IStorage * pStg) PURE;
        STDMETHOD(SetLoadFromText)(THIS) PURE;
        STDMETHOD(DidLoadFromText)(THIS_ BOOL * pfDidLoadFromText) PURE;
	  
};

//------------------------------------
// IVbaProjectSecurity interface
//------------------------------------
// {A7870464-A8B9-4b0d-88D1-CD3B5C03CC15}
//DEFINE_GUID(IID_IVbaProjectSecurity, 0xa7870464, 0xa8b9, 0x4b0d, 0x88, 0xd1, 0xcd, 0x3b, 0x5c, 0x3, 0xcc, 0x15);

#undef INTERFACE
#define INTERFACE IVbaProjectSecurity
DECLARE_INTERFACE_(IVbaProjectSecurity, IUnknown)
{
        BEGIN_INTERFACE
        // *** IUnknown methods ****
        STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
        STDMETHOD_(ULONG, AddRef)(THIS) PURE;
        STDMETHOD_(ULONG, Release)(THIS) PURE;
        
        //*** IVbaProjectSecurity methods ****
        STDMETHOD(SetFormsSFILevel)(THIS_ DWORD dwLevel) PURE;
        STDMETHOD(GetFormsSFILevel)(THIS_ DWORD* pdwLevel) PURE;
};




//------------------------------------
// IVbaProjItemCol interface
//------------------------------------
// {CD9B1AC6-FAA3-11d1-9922-00A0C9702442}
//DEFINE_GUID(IID_IVbaProjItemCol, 0xcd9b1ac6, 0xfaa3, 0x11d1, 0x99, 0x22, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

#undef  INTERFACE
#define INTERFACE  IVbaProjItemCol
DECLARE_INTERFACE_(IVbaProjItemCol, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** Project Item manipulation methods ***
	STDMETHOD(GetProjItemCount)(THIS_ UINT *pucItems) PURE;
	STDMETHOD(GetProjItem)(THIS_ UINT uiItem, IVbaProjItem **ppVbaProjItem) PURE;
	STDMETHOD(GetProjItemOfName)(THIS_ LPCOLESTR lpstrName, IVbaProjItem **ppVbaProjItem) PURE;
	STDMETHOD(IsValidProjItemName)(THIS_ LPCOLESTR lpstrName, BOOL *pIsValid) PURE;
	STDMETHOD(DeleteProjItem)(THIS_ LPCOLESTR lpstrName) PURE;
	STDMETHOD(CopyProjItem)(THIS_ IVbaProjItem *pVbaProjItemToCopy,
				      LPCOLESTR lpstrNameNew,
				      IDocumentSite      *pDocSite,
				      IVbaProjItem	 *pVbaPITemplateDoc,
				      IVbaProjItem **ppVbaProjItemNew) PURE;

	// *** Project Item creation methods ***
	STDMETHOD(CreateDocumentProjItem)(THIS_ LPCOLESTR 	  lpstrName,
						IDocumentSite    *pDocSite,
						IVbaProjItem	 *pVbaPITemplateDoc,
						IVbaProjItem     **ppVbaProjItem) PURE;
        
	STDMETHOD(CreateModuleProjItem)(THIS_ LPCOLESTR lpstrName, 
					      VBAMODTYPE vbamodtype, 
					      IVbaProjItem **ppVbaProjItem) PURE;

        STDMETHOD(CreateDocClassProjItem)(THIS_ LPCOLESTR 	  lpstrName,
						IDocumentSite    *pDocSite,
						IVbaProjItem     **ppVbaProjItem) PURE;

        STDMETHOD(CreateDesignerProjItem)(THIS_ LPCOLESTR 	  lpstrName,
						CLSID             clsidDesigner,
						IVbaProjItem     **ppVbaProjItem) PURE;
};


//--------------------------
// IVbaProjItem interface
//--------------------------
// {CD9B1AC7-FAA3-11d1-9922-00A0C9702442}
//DEFINE_GUID(IID_IVbaProjItem, 0xcd9b1ac7, 0xfaa3, 0x11d1, 0x99, 0x22, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

#undef  INTERFACE
#define INTERFACE  IVbaProjItem
DECLARE_INTERFACE_(IVbaProjItem, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaProjItem methods ***
	STDMETHOD(GetContainingProject)(THIS_ IVbaProject **ppvbaproj) PURE;

	STDMETHOD(GetName)(THIS_ BSTR *pbstrName) PURE;
	STDMETHOD(SetName)(THIS_ LPCOLESTR lpstrName) PURE;
	
	STDMETHOD(IsDirty)(THIS_ BOOL *pIsDirty) PURE;

	STDMETHOD(GetItemType)(THIS_ VBAPROJITEMTYPE *ppit) PURE;

	STDMETHOD(SetDocumentTemplate)(THIS_ IVbaProjItem *pVbaPITemplateDoc) PURE;

	STDMETHOD(GetVbaProcs)(THIS_ IVbaProcs **ppvbaprocs) PURE;

	STDMETHOD(InsertTextIntoModule)(THIS_ LPCOLESTR lpstrFileName) PURE;
	STDMETHOD(SetDisplayName)(THIS_ LPCOLESTR lpstrDisplayName) PURE;

	STDMETHOD(SetExtension)(THIS_ IUnknown *punkExt) PURE;

	STDMETHOD(CreateItemInstance)(THIS_ BOOL fSetPredeclaredId, IUnknown *punkOuter, 
                                            IUnknown **ppunkPrivate) PURE;

        STDMETHOD(GetPredeclaredId)(THIS_ IUnknown **ppunkInstance) PURE;
        STDMETHOD(ResetPredeclaredId)(THIS) PURE;

        STDMETHOD(LoadDocClass)(THIS) PURE;
        STDMETHOD(Compile)(THIS) PURE;
	STDMETHOD(SetDocClassBase)(THIS_ ITypeInfo *ptinfoBaseClass) PURE;
};



//------------------------
// IVbaProcs interface
//------------------------

// 41833fb0-4548-11ce-89da-00fa00687610
//DEFINE_GUID(IID_IVbaProcs, 0x41833fb0, 0x4548, 0x11ce, 0x89, 0xda, 0x00, 0xfa, 0x00, 0x68, 0x76, 0x10);

#undef  INTERFACE
#define INTERFACE  IVbaProcs
DECLARE_INTERFACE_(IVbaProcs, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaProcs methods ***
	STDMETHOD(GetProcs)(THIS_ VBAPROCFLAGS vbaprocflags, 
				  DWORD dwInvokeKinds, 
				  BOOL fSortByName, 
				  UINT *pucProcs, 
				  VBAPROC **pprgproc) PURE;
	STDMETHOD(FreeProcs)(THIS_ UINT ucProcs, VBAPROC *prgproc) PURE;

	STDMETHOD(EditProc)(THIS_ LPCOLESTR lpstrProcName, INVOKEKIND invokekind) PURE;
	STDMETHOD(DeleteProc)(THIS_ LPCOLESTR lpstrProcName, INVOKEKIND invokekind) PURE;
	STDMETHOD(SetProcInfo)(THIS_ LPCOLESTR lpstrProcName, 
			   LPCOLESTR  szDescription,
			   LPCOLESTR szInfo) PURE;
	STDMETHOD(GetProcInfo)(THIS_ LPCOLESTR lpstrProcName, 
			   BSTR  *pbstrDescription,
			   BSTR  *pbstrInfo) PURE;

	// Binding/Calling code
	STDMETHOD(CallMacro)(THIS_ LPCOLESTR lpstrMacroName) PURE;
	STDMETHOD(BindProcDisp)(THIS_ LPCOLESTR lpstrProcName, 
				  DWORD dwInvokeKinds,
				  BOOL fBindToPrivate,
				  IDispatch **ppdisp,
				  DISPID *pdispid,
				  INVOKEKIND *pinvokekind) PURE;
	STDMETHOD(DoesProcExist)(THIS_ LPCOLESTR lpstrObjName,
				 LPCOLESTR lpstrProcName,
				 BOOL *pfExists,  // TRUE if the sub exists
				 BOOL *pfEmpty) PURE; // TRUE if there is no code inside
};

//--------------------------
// IVbaRecorder interface
//--------------------------

// 41833fb0-4548-11ce-89da-00fa00688b10
//DEFINE_GUID(IID_IVbaRecorder, 0x41833fb0, 0x4548, 0x11ce, 0x89, 0xda, 0x00, 0xfa, 0x00, 0x68, 0x8b, 0x10);

#undef  INTERFACE
#define INTERFACE  IVbaRecorder
DECLARE_INTERFACE_(IVbaRecorder, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaRecordMacro methods ***
	STDMETHOD(RecordStart)(THIS_ IVbaProject *pVbaProj, IVbaProjItem *pVbaProjItem, LPCOLESTR bstrMacroName) PURE;
	STDMETHOD(GetRecordMarkLocation)(THIS_ IVbaProject **ppVbaProj,
					       IVbaProjItem **pVbaProjItem) PURE;
	STDMETHOD(RecordEnd)(THIS) PURE;
	STDMETHOD(RecordCancel)(THIS) PURE;

	STDMETHOD(RecordLine)(THIS_ LPCOLESTR lpstr) PURE;
	STDMETHOD(BeginAction)(THIS_ UINT uActionId) PURE;
	STDMETHOD(EraseAction)(THIS_ UINT uActionId) PURE;

	STDMETHOD(IsValidIdentifier)(THIS_ LPCOLESTR lpstrIdent) PURE;
	STDMETHOD(GetKeyWord)(THIS_ UINT kwid, BSTR *pbstrKeyword) PURE;

        STDMETHOD(RecordGetMacroName)(THIS_ BSTR *pbstrMacroName) PURE;
};

//--------------------------
// IVbaCompManager interface
//--------------------------

// {15B31E51-FE47-11cf-8D08-00A0C90F2732}
//DEFINE_GUID(IID_IVbaCompManager, 0x15b31e51, 0xfe47, 0x11cf, 0x8d, 0x8, 0x0, 0xa0, 0xc9, 0xf, 0x27, 0x32);

#undef  INTERFACE
#define INTERFACE  IVbaCompManager
DECLARE_INTERFACE_(IVbaCompManager, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaCompManager methods ***
        STDMETHOD(SetHostInfo)(THIS_ VBAINFOFLAGS vbainfoflags) PURE;

        STDMETHOD(OnHostActivate)(THIS) PURE;
        STDMETHOD(OnWaitForMessage)(THIS) PURE;

        STDMETHOD(OnHostEnterState)(THIS_ VBACOMPSTATE vbacompstate, BOOL fEnter) PURE;
        STDMETHOD(InState)(THIS_ VBACOMPSTATE vbacompstate, BOOL *pfInState) PURE;

        STDMETHOD(DoIdle)(THIS_ VBAIDLEFLAGS vbaidleflags, BOOL *pfContinue) PURE; 
        STDMETHOD(ContinueMessageLoop)(THIS_ BOOL fPushedByHost, BOOL *pfContinue) PURE;

        STDMETHOD(PreTranslateMessage)(THIS_ struct tagMSG *pMsg, BOOL *pfConsumed) PURE;

        STDMETHOD(InitiateReset)(THIS) PURE;
};


//---------------
// IVba interface
//---------------

// {CD9B1AC8-FAA3-11d1-9922-00A0C9702442}
//DEFINE_GUID(IID_IVba, 0xcd9b1ac8, 0xfaa3, 0x11d1, 0x99, 0x22, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

// {CD9B1AC9-FAA3-11d1-9922-00A0C9702442}
//DEFINE_GUID(CLSID_IVba, 0xcd9b1ac9, 0xfaa3, 0x11d1, 0x99, 0x22, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

#undef  INTERFACE
#define INTERFACE  IVba
DECLARE_INTERFACE_(IVba, IUnknown)
{
	BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVba methods ****
	STDMETHOD(GetVersionInfo)(THIS_ UINT *puVerMaj, UINT *puVerMin, UINT *puVerRef, BOOL *pfDebug) PURE;

        STDMETHOD(CreateProject)(THIS_ VBAPROJFLAGS vbaprojflags,
                                       IVbaProjectSite *pProjSite, IVbaProject **ppProj) PURE;

	STDMETHOD(ShowError)(THIS_ HRESULT hres) PURE;

	STDMETHOD(SetStepMode)(THIS_ VBASTEPMODE vbasm) PURE;

	STDMETHOD(GetMode)(THIS_ VBA_PROCESS_MODE *pmode) PURE;

	STDMETHOD(GetRecorder)(THIS_ IVbaRecorder **ppVbaRec) PURE;

	STDMETHOD(IsExecutingWatchExpression)(THIS_ BOOL *pfExecWatch) PURE;
	STDMETHOD(GetExecutingProject)(THIS_ IVbaProject **ppVbaProj) PURE;
	STDMETHOD(GetExtensibilityObject)(THIS_ IDispatch ** ppDispatch) PURE;

	STDMETHOD(Reset)(THIS) PURE;
        STDMETHOD(CreateExtension)(THIS_
                   /* [in]  */ IUnknown *punkOuter,
                   /* [in]  */ IUnknown *punkBase,
                   /* [in]  */ IUnknown *punkExtender,
                   /* [out] */ IUnknown **ppunkExtension) PURE;

        STDMETHOD(NotifyUserInterrupt)(THIS_ DWORD dwReserved) PURE;
        STDMETHOD(GetCompManager)(THIS_ IVbaCompManager **ppVbaCompManager) PURE;

        STDMETHOD(GetExecutingInstance)(THIS_ IUnknown **ppunkInstance) PURE;
        STDMETHOD(BuildErrorInfo)(THIS_ HRESULT hres, IErrorInfo **pperrinfo) PURE;
	

        STDMETHOD(QueryTerminate)(THIS_ BOOL *pfCanTerminate) PURE;
	
        STDMETHOD(VerifyProject)(THIS_
				 /* in  */ IStorage               * pStg,
				 /* in  */ void                   * pvSignature,
				 /* out */ VBAMACROENABLESTATE    * pdsMacroState,
				 /* in  */ VBADIGSIGSECURITYLEVEL   uiSecurityLevel,
				 /* in  */ LPCOLESTR                lpcszFileName,
				 /* out */ BOOL                   * pfLoadFromText) PURE;	 		

	STDMETHOD(DlgSetSecurityLevel)(THIS_
				 /*  in/out */ VBADIGSIGSECURITYLEVEL * pSecurityLevel,
				 /* reserved*/ LPVOID                   lpReserved) PURE;
                                 
        STDMETHOD(SupportDesigner)(THIS_ CLSID clsidDesigner, BOOL fSupport) PURE;

        STDMETHOD(PreTerminate)(THIS) PURE;
        STDMETHOD(UpgradeStorage)(THIS_ USHORT  usVerDelta) PURE;
};


//-------------------------
// IVbaHostAddins interface
//-------------------------
 
// {9E7BE5EB-C1DA-11d1-AA7E-00C04FC2F1BF}
//DEFINE_GUID(IID_IVbaHostAddins, 0x9e7be5eb, 0xc1da, 0x11d1, 0xaa, 0x7e, 0x0, 0xc0, 0x4f, 0xc2, 0xf1, 0xbf);

#undef  INTERFACE
#define INTERFACE  IVbaHostAddins
DECLARE_INTERFACE_(IVbaHostAddins, IUnknown)
{
        BEGIN_INTERFACE
	// *** IUnknown methods ****
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	// *** IVbaHostAddins methods ****
	STDMETHOD(GetAddIns)(THIS_ IDispatch **ppdispAddins) PURE;
	STDMETHOD(OnHostStartupComplete)(THIS) PURE;
	STDMETHOD(OnHostBeginShutdown)(THIS) PURE;
	STDMETHOD(ShowAddInsDialog)(THIS_ HWND hparentwin) PURE;
	STDMETHOD(LoadHostAddins)(THIS) PURE;
};


///////////////////////////////////////////////////////////////////////////
//
// VBA APIs
//
///////////////////////////////////////////////////////////////////////////

STDAPI VbaInitialize(DWORD dwCookie,
                     VBAINITINFO *pVbaInitInfo,
		     IVba **ppVba);

STDAPI VbaTerminate(IVba *pVba);

STDAPI VbaInitializeHostAddins(VBAINITHOSTADDININFO *pInitAddinInfo,
			       IVbaHostAddins **ppHostAddins);

///////////////////////////////////////////////////////////////////////////
//
// VBA implements the following standard services (see objext.h):
//   SLicensedClassManager
//   SCreateExtendedTypeLib
//   SCodeNavigate
//   STrackSelection
//   SLocalRegistry
//
// VBA implements these custom services (see below):
//   SVbaMainUI
//   SVbaPropertyBrowserUI
//   SVbaFormat
//   SVbaFiles
//
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//  VBA Component Categories
//-------------------------------------------------------------------------

// {77B01B3B-C495-11d1-9903-00A0C9702442}
//DEFINE_GUID(CATID_VbaDesigner, 0x77b01b3b, 0xc495, 0x11d1, 0x99, 0x3, 0x0, 0xa0, 0xc9, 0x70, 0x24, 0x42);

//-------------------------------------------------------------------------
//  SVba*UI Services
//    These services allows he host to control the VBA UI.
//
//  interfaces implemented:
//    IUIElement
//-------------------------------------------------------------------------

// 759d0501-d979-11ce-84ec-00aa00614f3e
//DEFINE_GUID(SID_SVbaMainUI, 0x759d0501, 0xd979, 0x11ce, 0x84, 0xec, 0x00, 0xaa, 0x00, 0x61, 0x4f, 0x3e);

// 759d0502-d979-11ce-84ec-00aa00614f3e
//DEFINE_GUID(SID_SVbaPropertyBrowserUI, 0x759d0502, 0xd979, 0x11ce, 0x84, 0xec, 0x00, 0xaa, 0x00, 0x61, 0x4f, 0x3e);

//-------------------------------------------------------------------------
//  SVbaFormat Service.
//    This service VARIANT formatting routines equivalent to the 
//    Basic Format$ intrinsic. Can be used to implement IGetVbaObjects
//    on controls sites
//
//  interfaces implemented:
//    IVbaFormat
//    IVbaFormat2
//-------------------------------------------------------------------------
//DEFINE_GUID(IID_IVbaFormat, 0x9849FD60L, 0x3768, 0x101B, 0x8D, 0x72, 0xAE, 0x61, 0x64, 0xFF, 0xE3, 0xCF);
#define SID_SVbaFormat IID_IVbaFormat

#undef  INTERFACE
#define INTERFACE IVbaFormat
DECLARE_INTERFACE_(IVbaFormat, IUnknown)
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef) (THIS) PURE;
    STDMETHOD_(ULONG, Release) (THIS) PURE;

    // *** IVbaFormat methods ***
    STDMETHOD(Format)(THIS_ LPVARIANT lpVarData, 
			        LPCOLESTR szFormat,
                                LPVOID    lpBuffer, 
                                USHORT    cbBuffer, 
                                LCID      lcid,
                                USHORT    sFirstDayOfWeek,
                                USHORT    sFirstWeekOfYear,
                                USHORT    *pcbResult) PURE;
};

//-------------------------------------------------------------------------
//  SVbaFiles Service.
//    This service provides file access to files opened in Basic code. Can
//  be used to implement IGetVbaObjects on controls sites
//
//  interfaces implemented:
//    IVbaFiles
//-------------------------------------------------------------------------
//DEFINE_GUID(IID_IVbaFiles, 0xB53BA860L, 0x3768, 0x101B, 0x8D, 0x72, 0x00, 0xDD, 0x01, 0x0E, 0xDF, 0xAA);
#define SID_SVbaFiles IID_IVbaFiles

#undef  INTERFACE
#define INTERFACE  IVbaFiles
DECLARE_INTERFACE_(IVbaFiles, IUnknown)
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef) (THIS) PURE;
    STDMETHOD_(ULONG, Release) (THIS) PURE;

    // *** IVbaFiles methods ***
    STDMETHOD(Read)(THIS_ USHORT usFileNo, LPVOID lpBuffer, UINT cb) PURE;
    STDMETHOD(Write)(THIS_ USHORT usFileNo, LPVOID lpBuffer, UINT cb) PURE;
    STDMETHOD(Seek)(THIS_ USHORT usFileNo, LONG lOffset, LONG *plPos) PURE;
    STDMETHOD(SeekRel)(THIS_ USHORT usFileNo, LONG lOffset, LONG *plPos) PURE;
};


//-------------------------------------------------------------------------
// SVbaHostMsoTFCUser Service
//   This is a service provided by the host application.  VBA calls for
//   it through IMsoComponentHost::QueryService to get a pointer to
//   the host's IMsoTFCUser object.
//-------------------------------------------------------------------------
//DEFINE_GUID(SID_IVbaHostMsoTFCUser, 0x9F4F4140L, 0x5838, 0x11CF, 0x87, 0x78, 0x00, 0xAA, 0x00, 0xB9, 0x31, 0x85);


///////////////////////////////////////////////////////////////////////////
//
// Control Programmability Interfaces
//
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//  IGetVBAObject Interface
//    This interface is implemented by the control container's control site
//  to enable it to hand out IVbaFormat[2] and IVbaFiles interfaces to controls
//
//-------------------------------------------------------------------------
//DEFINE_GUID(IID_IGetVBAObject, 0x91733A60L, 0x3F4C, 0x101B, 0xA3, 0xF6, 0x00, 0xAA, 0x00, 0x34, 0xE4, 0xE9);
#undef INTERFACE
#define INTERFACE IGetVBAObject
DECLARE_INTERFACE_(IGetVBAObject,IUnknown)
{
    BEGIN_INTERFACE
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IGetVBAObject methods ***
    STDMETHOD(GetObject)(THIS_ REFIID riid, void FAR* FAR* ppvObj, DWORD dwReserved) PURE;
};



//--- EOF -------------------------------------------------------------------
//---------------------------------------------------------------------------
// Copyright (C) 1991-1998, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------

#ifdef __cplusplus
  interface IOleControlSite;
  interface IPropertyNotifySink;
#else
  typedef interface IOleControlSite IOleControlSite;
  typedef interface IPropertyNotifySink IPropertyNotifySink;
#endif

#define DWCTRLCOOKIE_Nil      0xffffffff
#define EXTENDER_MemidLow    0x80010000
#define EXTENDER_MemidHigh   0x8001ffff

//-------------------------------------------------------------------------
//  Macros for inserting default members to the build in Controls.
//
//-------------------------------------------------------------------------
#define MEMID_Name            (0x80010000)  // as defined by controls spec.
#define MEMID_Parent          (0x80010008)  // as defined by controls spec.
#define MEMID_Delete          (-801)        // new dispid assigned.
#define MEMID_Object          (-802)        // new dispid assigned

#define STD_EXTENDER_METHODS                                       \
        [propget, id(MEMID_Name)] BSTR * Name();                  \
        [propput, id(MEMID_Name)] void Name([in] BSTR bstrName);  \
        [propget, id(MEMID_Object)] IDispatch * Object();          \
        [id(MEMID_Delete)] void Delete();                \



//-------------------------------------------------------------------------
//  IControlDesign
//
//-------------------------------------------------------------------------
//DEFINE_GUID( IID_IControlDesign, 0x5bd18670, 0xe2fa, 0x11ce, 0x82, 0x29, 0x00, 0xaa, 0x00, 0x44, 0x40, 0xd0 );
#define SID_SControlDesign IID_IControlDesign

#undef  INTERFACE
#define INTERFACE IControlDesign
DECLARE_INTERFACE_(IControlDesign, IUnknown)
{
    BEGIN_INTERFACE
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IControlDesign methods
    STDMETHOD(DefineControl)(THIS_ 
			     DWORD dwflags,      
			     ITypeInfo *ptinfo,  
			     DWORD dwCtlCookie,
                             LPCOLESTR szName) PURE;
			      
    STDMETHOD(UndefineControl)(THIS_ 
                               DWORD flags,
                               DWORD dwCtlCookie) PURE;

    STDMETHOD(HideControl)(THIS_ 
			   DWORD dwCtlCookie,
			   BOOL fHide) PURE;
};

//-------------------------------------------------------------------------
//  IControlRT
//
//-------------------------------------------------------------------------
//DEFINE_GUID( IID_IControlRT, 0x3402ea80, 0xe2fa, 0x11ce, 0x82, 0x29, 0x00, 0xaa, 0x00, 0x44, 0x40, 0xd0 );

#undef  INTERFACE
#define INTERFACE IControlRT
DECLARE_INTERFACE_(IControlRT, IUnknown)
{
    BEGIN_INTERFACE
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IControlRT methods
    STDMETHOD(ForceControlCreation)(THIS_ 
			     DWORD dwflags,      
			     DWORD dwCtlCookie) PURE;
			      

};


//-------------------------------------------------------------------------
//  IControlContainer
//
//-------------------------------------------------------------------------
//DEFINE_GUID( IID_IControlContainer, 0xbc863490, 0xe675, 0x11ce, 0x82, 0x29, 0x00, 0xaa, 0x00, 0x44, 0x40, 0xd0 );

#undef  INTERFACE
#define INTERFACE IControlContainer
DECLARE_INTERFACE_(IControlContainer, IUnknown)
{
    BEGIN_INTERFACE
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IControlDesign methods
    STDMETHOD(Init)(THIS_ 
		    IControlRT *pctrlRT) PURE;

    STDMETHOD(GetControlParts)(THIS_ 
                               DWORD dwflags,                
                               DWORD dwCtlCookie,            
                               IUnknown *punkOuter,          
                               DWORD    *pdwRTCookie,
                               IUnknown **ppunkExtender,     
                               IUnknown **ppunkprivControl,  
                               IOleControlSite **ppocs) PURE;     


    STDMETHOD(CopyControlParts)(THIS_ 
                                DWORD dwflags,               
                                DWORD dwCtlCookieTemplate,   
                                IUnknown *punkOuter,         
                                DWORD *pdwCltCookie,         
                                DWORD *pdwRTCookie,         
                                IUnknown **ppunkExtender,    
                                IUnknown **ppunkprivControl, 
                                IOleControlSite **ppocs) PURE;    



    STDMETHOD(SetExtenderEventSink)(THIS_ 
                                    DWORD dwCtlCookie,      
                                    IUnknown *punkSink,
                                    IPropertyNotifySink *ppropns) PURE;

		 
};

//-------------------------------------------------------------------------
//  IProvideControls
//
//-------------------------------------------------------------------------
//DEFINE_GUID( IID_IProvideControls, 0x3676f490, 0xe2fa, 0x11ce, 0x82, 0x29, 0x00, 0xaa, 0x00, 0x44, 0x40, 0xd0 );

#undef  INTERFACE
#define INTERFACE IProvideControls
DECLARE_INTERFACE_(IProvideControls, IUnknown)
{
    BEGIN_INTERFACE
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IProvideControls methods
    STDMETHOD(GetControls)(THIS_ 
			   DWORD cControls,      
			   DWORD rgCtrlPropCookie[],  
			   IUnknown *rgpunk[]) PURE;

    STDMETHOD(SetSink)(THIS_ 
	    	       DWORD *pdwCookie,      
		       IDispatch *pdispSink) PURE;

};

//-------------------------------------------------------------------------
//  IControlInfo
//
//-------------------------------------------------------------------------
#undef  INTERFACE
#define INTERFACE IControlInfo
DECLARE_INTERFACE_(IControlInfo, IUnknown)
{
    BEGIN_INTERFACE
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IControlInfo methods
    STDMETHOD(SetName)(THIS_ BSTR bstrName) PURE;
    STDMETHOD(GetName)(THIS_ BSTR *pbstrName) PURE;                                
    STDMETHOD(GetParent)(THIS_ IControlContainer **ppctrlcont) PURE;                                
    STDMETHOD(GetTypeInfo)( THIS_
                            UINT itinfo,
                            LCID lcid,
                            ITypeInfo FAR* FAR* pptinfo ) PURE;
};

//-------------------------------------------------------------------------
//  IFreezeEvents
//
//-------------------------------------------------------------------------

// {F27BE360-1B98-11cf-84FC-00AA00A71DCB}
//DEFINE_GUID(IID_IFreezeEvents, 0xf27be360, 0x1b98, 0x11cf, 0x84, 0xfc, 0x0, 0xaa, 0x0, 0xa7, 0x1d, 0xcb);
#define SID_SFreezeEvents IID_IFreezeEvents

#undef  INTERFACE
#define INTERFACE IFreezeEvents
DECLARE_INTERFACE_(IFreezeEvents, IUnknown)
{
    BEGIN_INTERFACE
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IFreezeEvents methods
    STDMETHOD(FreezeEvents)(THIS_ BOOL fFreeze) PURE;
};




#if FV_EVENT
//-------------------------------------------------------------------------
//  IEvent
//
//-------------------------------------------------------------------------
// 3dbd2ff0-73b2-11cf-b4a2-00aa00bf9e22
//DEFINE_GUID(IID_IEvent, 0x3dbd2ff0, 0x73b2, 0x11cf, 0xb4, 0xa2, 0x00, 0xaa, 0x00, 0xbf, 0x9e, 0x22);
#endif
#endif 
#pragma pack(pop) 
