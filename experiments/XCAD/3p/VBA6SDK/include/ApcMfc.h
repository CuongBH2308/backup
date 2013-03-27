/* --------------------------------------------------------------------------
 * apcMfc.h 
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
#ifndef APCMFC_H_INCLUDED			// protect against multiple inclusions
#define APCMFC_H_INCLUDED
/*
 * Use this file for MFC applications.
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
 * define APC_NO_OLECLIENTITEM to remove the container support 
 *        class
 * define APC_HINT_UPDATE_OLEITEM to use UpdateAllViews hint other
 *        than 0x00FFFFFF
 */
/* --------------------------------------------------------------------------
 * APC/MFC template library
 * --------------------------------------------------------------------------
 */

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef __ATLBASE_H__
	#error include <atlbase.h> before including this file
#endif

#ifndef __ATLCOM_H__
	#error include <atlcom.h> before including this file
#endif

/////////////////////////////////////////////////////////////////////////////

#include "apcCpp.h"

#ifndef MEMID_Index
	#define MEMID_Index           (-804)
#endif

#ifndef MEMID_Name
	#define MEMID_Name            (0x80010000)  // as defined by controls spec.
#endif

#ifndef MEMID_Parent
	#define MEMID_Parent          (0x80010008)  // as defined by controls spec.
#endif

#ifndef MEMID_Delete
	#define MEMID_Delete          (-801)        // new dispid assigned.
#endif

#ifndef MEMID_Object
	#define MEMID_Object          (-802)        // new dispid assigned
#endif

/////////////////////////////////////////////////////////////////////////////

namespace MSAPC 
{

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// globals

// see apcImpl.cpp

extern IApc* g_pApcHost;

void AFXAPI ApcOleTermOrFreeLib(BOOL bTerm, BOOL bJustRevoke);
const AFX_INTERFACEMAP_ENTRY* ApcGetEntryFromIID(const void* iid, const AFX_INTERFACEMAP* pMap);
LPUNKNOWN ApcGetPtrFromEntry(const void* pThis, const AFX_INTERFACEMAP_ENTRY* pEntry);

#ifndef _UNICODE
//these things are to work around an MFC bug.
extern HHOOK g_hHookOldCbtFilter;
extern WNDPROC g_wndprocOld;
LRESULT CALLBACK ApcActivationWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ApcCBTWindowsHook(int code, WPARAM wParam, LPARAM lParam);
#endif
/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcApplication - base class for your application class

template <class T, class AppBase = CWinApp>
class CApcApplication : 
	public AppBase, 
	public CApcHost<T>
{
public:
	CApcApplication()
	{
	}

	BOOL OnIdle(LONG lCount)
	{
		// MFC uses lCount==-1 for forcing UpdateUI
		if (lCount < 0)
			return AppBase::OnIdle(lCount);

		BOOL fVbaNotDone = FALSE;
		ApcHost.OnIdle(&fVbaNotDone, lCount != 1, lCount > 0, lCount > 0);

		BOOL fMfcNotDone = AppBase::OnIdle(lCount);

		if (lCount > 10 && fVbaNotDone)
		{
			MsgWaitForMultipleObjects(0, NULL, FALSE, 100, QS_ALLINPUT);
		}

		return fVbaNotDone || fMfcNotDone;
	}

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		// VBA SPECIFIC: Let the VBA Component Manager attempt
		//               to consume the message.  If it does,
		//               remove the message from the loop and
		//               continue processing.  Otherwise, let
		//               the MFC attempt to process the message.
		if (ApcHost.GetApcCompManager()) 
		{
			APC_BOOL fConsumed = FALSE;

			ApcHost.GetApcCompManager()->APC_RAW(PreTranslateMessage)(&m_msgCur, &fConsumed);

			if (fConsumed) 
			{
				// message processed by the Component Manager
				// continue processing, skipping MFC pump
				return TRUE;
			}
		}

		// VBA SPECIFIC: If the VBA Component Manager didn't process
		//               the message, and the host is not active, then
		//               translate and dispatch the message to component.
		if (!ApcHost.m_fHostIsActiveComponent) 
		{
			// Remove message and process it for component
			TranslateMessage(&m_msgCur);
			DispatchMessage(&m_msgCur);
			return TRUE;
		}

		return AppBase::PreTranslateMessage(pMsg);
	}

	HRESULT ApcHost_DoIdle(BOOL* pfContinue)
	{
		AFX_MANAGE_STATE(m_pModuleState);

		return CApcHost<T>::ApcHost_DoIdle(pfContinue);
	}

	HRESULT ApcHost_PushMessageLoop(AxMessageLoopReason LoopReason, BOOL* pfAborted)
	{
		AFX_MANAGE_STATE(m_pModuleState);

		return CApcHost<T>::ApcHost_PushMessageLoop(LoopReason, pfAborted);
	}

	void ApcHost_OnMessageLoop(AxMessageLoopReason loopreason, BOOL* pfAborted, int* pnExitCode, BOOL fPushedByHost)
	{
        APC_BOOL fContinue;

		T* pT = static_cast<T*>(this);

		// for tracking the idle time state
		BOOL bIdle = TRUE;
		LONG lIdleCount = 0;

		// VBA SPECIFIC: Keep track of the number of times we've been entered
		ApcHost.m_cMsgLoop++;

		if (fPushedByHost && 0 == ApcHost.m_cFirstMsgLoop)
		{
			_ASSERTE(pnExitCode); // first message loop should want an exit code
			ApcHost.m_cFirstMsgLoop = ApcHost.m_cMsgLoop;
		}

		// acquire and dispatch messages until a WM_QUIT message is received.
		for (;;)
		{
			// VBA SPECIFIC: Check to see if VBA Component Manager wants
			//               to stop message processing
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

			// phase1: check to see if we can do idle work
			if (!::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
			{
				// Do OnIdle processing. There are two cases here:
				//
				//	1. OnIdleMessage told us that OnIdle should be called. In this case,
				//	we perform MFC's OnIdle processing as normal (incrementing the count
				//	appropriately). When no more OnIdle's are required, we then put
				//	ourselves to sleep until another message arrives.
				//
				//	2. When no other message is in the queue and OnIdleMessage told us
				//	there was no OnIdle work to be done, then simply go to sleep until
				//	another message comes in. (Note: This rarely occurs, but if it does,
				//	we need to be ready; otherwise, we hog the CPU forever.)

				// make sure there are still no messages in the queue (in case
				// OnWaitForMessage did something unexpected)
				if (!::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE)) 
				{
					if (bIdle) 
					{
						// IsIdleMessage told us that OnIdle processing was required
						if (!OnIdle(lIdleCount++)) 
						{
							// no more OnIdle is required
							bIdle = FALSE;	// assume "no idle" state

							if (ApcHost.GetApcCompManager())
								ApcHost.GetApcCompManager()->APC_RAW(WaitForMessage)();

							WaitMessage();	// sleep until a messages arrives
						}
					}
					else 
					{
						// no OnIdle's are necessary; sleep until message arrives

						if (ApcHost.GetApcCompManager())
							ApcHost.GetApcCompManager()->APC_RAW(WaitForMessage)();

						WaitMessage();
					}
				}
			}
			else 
			{
				
				// pump message, but quit on WM_QUIT
				if (!PumpMessage()) 
				{
					break;
				}

				// reset "no idle" state after pumping "normal" message
				if (IsIdleMessage(&m_msgCur)) {
					// MFC told us we need to do OnIdle processing -- so set boolean
					// so that we do this above. Otherwise, we'll go into a "wait" without
					// having done OnIdle processing.
					lIdleCount = 0;	// reset according to OnIdle rules of MFC
					bIdle = TRUE;
				}
			}
		}

		if (fPushedByHost && ApcHost.m_cMsgLoop == ApcHost.m_cFirstMsgLoop)
			ApcHost.m_cFirstMsgLoop = 0;

        ApcHost.m_cMsgLoop--;

		if (ApcHost.m_cMsgLoop == ApcHost.m_cFirstMsgLoop)
			ApcNotifyV(("ApcHost_OnStackUnwound"), pT->ApcHost_OnStackUnwound());
	}

	// ApcHost_OnCreate - called by ApcHost.Create
	HRESULT ApcHost_OnCreate()
	{
		HRESULT hr = CApcHost<T>::ApcHost_OnCreate();

		g_pApcHost = ApcHost;

		return hr;
	}

	// ApcHost_OnDestroy - called by ApcHost.Destroy
	void ApcHost_OnDestroy()
	{
		ApcHost.OnDestroy();

		g_pApcHost = NULL;
	}

public:
	virtual int Run()
	{
#ifndef _UNICODE
		// this code works around an MFC with MSO10 bug
		// on UNICODE systems, so
		// only do this if we are on a UNICODE capable platform

		BOOL bIsUnicode = FALSE;

		OSVERSIONINFO osvi;
		memset(&osvi, 0, sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		GetVersionEx(&osvi);

		if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
			bIsUnicode = TRUE;


		if(bIsUnicode)
		  //set up our windows hook to work around MFC bug
		  g_hHookOldCbtFilter = SetWindowsHookEx(WH_CBT, (HOOKPROC)ApcCBTWindowsHook, NULL, GetCurrentThreadId());
#endif
		// use the VBA Component Manager MessageLoop() 
		ApcHost.MessageLoop(); 
#ifndef _UNICODE
		if(bIsUnicode)
			//unhook the hook
			UnhookWindowsHookEx(g_hHookOldCbtFilter);
#endif
		return ExitInstance();
	}

	virtual int ExitInstance()
	{
		ApcHost.Destroy();
		return AppBase::ExitInstance();
	}

#ifdef _UNICODE

#ifndef WM_KICKIDLE
#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#endif // WMKICKIDLE

	// Override MFC's implementation of CWinThread::PumpMessage
	// to allow for calling the ANSI APIs for ANSI receiving windows
	virtual BOOL PumpMessage()
	{
		ASSERT_VALID(this);
		BOOL fReturn;
		BOOL fUnicodeWindowMsg;
		MSG msg;

		// first check whether the receiving window is ANSI or UNICODE
		fReturn = ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
		fUnicodeWindowMsg = fReturn && IsWindowUnicode(msg.hwnd);

		if (fUnicodeWindowMsg)
		{
			fReturn = ::GetMessageW(&m_msgCur, NULL, NULL, NULL);
		}
		else
		{
			fReturn = ::GetMessageA(&m_msgCur, NULL, NULL, NULL);
		}

		if (!fReturn)
		{
	#ifdef _DEBUG
			if (afxTraceFlags & traceAppMsg)
				TRACE0("CWinThread::PumpMessage - Received WM_QUIT.\n");
			m_nDisablePumpCount++; // application must die
				// Note: prevents calling message loop things in 'ExitInstance'
				// will never be decremented
	#endif
			return FALSE;
		}

	#ifdef _DEBUG
		if (m_nDisablePumpCount != 0)
		{
			TRACE0("Error: CWinThread::PumpMessage called when not permitted.\n");
			ASSERT(FALSE);
		}
	#endif

		// process this message
		if (m_msgCur.message != WM_KICKIDLE && !PreTranslateMessage(&m_msgCur))
		{
			::TranslateMessage(&m_msgCur);
			fUnicodeWindowMsg ? ::DispatchMessageW(&m_msgCur) : ::DispatchMessageA(&m_msgCur);
		}

		return TRUE;
	}
#endif // _UNICODE

#if _MFC_VER >= 0x0700
	// message pump for Run
	MSG m_msgCur;                   // current message
#endif


	BOOL ApcOleInit()
	{
		// do MFC's init of ole
		if (!AfxOleInit())
			return FALSE;

		// set our own shutdown handler
		// this must be done after calling AfxOleInit
		//ASSERT(m_lpfnOleTermOrFreeLib == AfxOleTermOrFreeLib);
		m_lpfnOleTermOrFreeLib = ApcOleTermOrFreeLib;

		return TRUE;
	}

	//{{AFX_MSG(CApcApplication)
	afx_msg void OnVbaIde()
	{
		if (ApcHost)
		{
			CComPtr<IApcIde> spIDE;
			HRESULT hr = ApcHost->APC_GET(Ide)(&spIDE);
			ASSERT(SUCCEEDED(hr));
			if (spIDE)
			{
				hr = spIDE->APC_PUT(Visible)(VARIANT_TRUE);
				ASSERT(SUCCEEDED(hr));
			}
		}
	}

	afx_msg void OnUpdateVbaIde(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(ApcHost != NULL);
	}

	afx_msg void OnVbaPropertiesWindow()
	{
		if (ApcHost)
		{
			CComPtr<IApcPropertiesWindow> spPropertiesWindow;
			HRESULT hr = ApcHost->APC_GET(PropertiesWindow)(&spPropertiesWindow);
			ASSERT(SUCCEEDED(hr));

			if (spPropertiesWindow)
			{
				HRESULT hr = spPropertiesWindow->APC_PUT(Visible)(VARIANT_TRUE);
				ASSERT(SUCCEEDED(hr));
			}
		}
	}

	//}}AFX_MSG

};

//
// Helper class for CApcDocument to reduce code bloat
//
class CApcAmbientProperties
{
public:
	CApcAmbientProperties()
	{
		// ambient properties
		m_pOleFont = NULL;
		m_crFore = (COLORREF) -1;
		m_crBack = (COLORREF) -1;
	}

	/*
	DISPID_AMBIENT_BACKCOLOR			(-701)
	DISPID_AMBIENT_DISPLAYNAME			(-702)
	DISPID_AMBIENT_FONT					(-703)
	DISPID_AMBIENT_FORECOLOR			(-704)
	DISPID_AMBIENT_LOCALEID				(-705)
	DISPID_AMBIENT_MESSAGEREFLECT		(-706)
	DISPID_AMBIENT_SCALEUNITS			(-707)
	DISPID_AMBIENT_TEXTALIGN			(-708)
	DISPID_AMBIENT_USERMODE				(-709)
	DISPID_AMBIENT_UIDEAD				(-710)
	DISPID_AMBIENT_SHOWGRABHANDLES		(-711)
	DISPID_AMBIENT_SHOWHATCHING			(-712)
	DISPID_AMBIENT_DISPLAYASDEFAULT		(-713)
	DISPID_AMBIENT_SUPPORTSMNEMONICS	(-714)
	DISPID_AMBIENT_AUTOCLIP				(-715)
	DISPID_AMBIENT_APPEARANCE			(-716)
	*/

	BOOL GetAmbientProp( CWnd* pWnd, DISPID dispid, VARIANT* pvarResult)
	{
		switch (dispid)
		{
			case DISPID_AMBIENT_AUTOCLIP:
			case DISPID_AMBIENT_MESSAGEREFLECT:
				V_VT(pvarResult) = VT_BOOL;
				V_BOOL(pvarResult) = (VARIANT_BOOL)-1;
				return TRUE;

			case DISPID_AMBIENT_SUPPORTSMNEMONICS:
			case DISPID_AMBIENT_SHOWGRABHANDLES:
			case DISPID_AMBIENT_SHOWHATCHING:
			case DISPID_AMBIENT_UIDEAD:
				V_VT(pvarResult) = VT_BOOL;
				V_BOOL(pvarResult) = 0;
				return TRUE;

			case DISPID_AMBIENT_APPEARANCE:     // ambient appearance is 3D
				V_VT(pvarResult) = VT_I2;
				V_I2(pvarResult) = 1;
				return TRUE;

			case DISPID_AMBIENT_BACKCOLOR:
			case DISPID_AMBIENT_FORECOLOR:
				if (m_crBack == (COLORREF)-1)   // ambient colors not initialized
				{			
					CWindowDC dc(pWnd);
					pWnd->SendMessage(WM_CTLCOLORSTATIC, (WPARAM)dc.m_hDC, (LPARAM)pWnd->m_hWnd);
					m_crBack = dc.GetBkColor();
					m_crFore = dc.GetTextColor();
				}

				V_VT(pvarResult) = VT_COLOR;
				V_I4(pvarResult) = (dispid == DISPID_AMBIENT_BACKCOLOR) ? m_crBack : m_crFore;
				return TRUE;

			case DISPID_AMBIENT_FONT:
				if (m_pOleFont == NULL)         // ambient font not initialized
					CreateOleFont(pWnd->GetFont(), pWnd);

				ASSERT(m_pOleFont != NULL);
				if (m_pOleFont == NULL)         // failed to create font
					return FALSE;

				V_VT(pvarResult) = VT_FONT;
				m_pOleFont->AddRef();
				V_DISPATCH(pvarResult) = m_pOleFont;
				return TRUE;

			case DISPID_AMBIENT_DISPLAYASDEFAULT:
				V_VT(pvarResult) = VT_BOOL;
				V_BOOL(pvarResult) = 0; // (VARIANT_BOOL)(pSite->IsDefaultButton() ? -1 : 0);
				return TRUE;

			case DISPID_AMBIENT_LOCALEID:
				V_VT(pvarResult) = VT_I4;
				V_I4(pvarResult) = GetThreadLocale();
				return TRUE;

			case DISPID_AMBIENT_SCALEUNITS:
			{
				CString str;
				str.LoadString(AFX_IDS_OCC_SCALEUNITS_PIXELS);
				V_VT(pvarResult) = VT_BSTR;
				V_BSTR(pvarResult) = str.AllocSysString();
				return TRUE;
			}
		}

		return FALSE;
	}

protected:
	/////////////////////////////////////////////////////////////////////////////
	// ambient properties support for OLE Controls

	COLORREF m_crBack;
	COLORREF m_crFore;
	LPFONTDISP m_pOleFont;

	void CreateOleFont(CFont* pFont, CWnd *pWnd)
	{
		USES_CONVERSION;

		CFont fontSys;
		if ((pFont == NULL) || (pFont->m_hObject == NULL))
		{
			// no font was provided, so use the system font
			if (fontSys.CreateStockObject(DEFAULT_GUI_FONT) ||
				fontSys.CreateStockObject(SYSTEM_FONT))
			{
				pFont = &fontSys;
			}
			else
			{
				m_pOleFont = NULL;
				return;
			}
		}

		LOGFONT logfont;
		pFont->GetLogFont(&logfont);

		FONTDESC fd;
		fd.cbSizeofstruct = sizeof(FONTDESC);
		fd.lpstrName = T2OLE(logfont.lfFaceName);
		fd.sWeight = (short)logfont.lfWeight;
		fd.sCharset = logfont.lfCharSet;
		fd.fItalic = logfont.lfItalic;
		fd.fUnderline = logfont.lfUnderline;
		fd.fStrikethrough = logfont.lfStrikeOut;

		long lfHeight = logfont.lfHeight;
		if (lfHeight < 0)
			lfHeight = -lfHeight;

		CWindowDC dc(pWnd);
		int ppi = dc.GetDeviceCaps(LOGPIXELSY);
		fd.cySize.Lo = lfHeight * 720000 / ppi;
		fd.cySize.Hi = 0;

		if (m_pOleFont != NULL) 
			m_pOleFont->Release();
		m_pOleFont = NULL;
		if (FAILED(OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&m_pOleFont)))
			m_pOleFont = NULL;
	}
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcOleServerDocInterfaceMap - base class for your document class

class CApcOleServerDocInterfaceMap
{
	const AFX_INTERFACEMAP& m_thisMap;
	const AFX_INTERFACEMAP& m_baseMap;
	const AFX_INTERFACEMAP_ENTRY* m_pPSEntry;

public:
	CApcOleServerDocInterfaceMap(const AFX_INTERFACEMAP& thisMap, const AFX_INTERFACEMAP& baseMap)
	:
		m_thisMap(thisMap),
		m_baseMap(baseMap),
		m_pPSEntry(ApcGetEntryFromIID(&IID_IPersistStorage, &baseMap))
	{
	}

	IPersistStorage* GetPersistStorage(const void* pThis) const
	{
		return (IPersistStorage*) ApcGetPtrFromEntry(pThis, m_pPSEntry);
	}

	operator AFX_DATA const AFX_INTERFACEMAP &() const
	{
		return m_pPSEntry ? m_thisMap : m_baseMap;
	}

	AFX_DATA const AFX_INTERFACEMAP* operator&() const
	{
		return m_pPSEntry ? &m_thisMap : &m_baseMap;
	}
};

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcDocument - base class for your document class

BOOL ApcGetEmbedded(COleServerDoc* pThis);
BOOL ApcGetEmbedded(CDocument* pThis);

template <class T, class DocBase = COleServerDoc>
class CApcDocument :
	public DocBase,
	public CApcProject<T>
{
public:
	CApcDocument()
	{
		m_fApcRemember = TRUE;
		m_fApcAmbientDesignMode = TRUE;
		m_fApcAutoLoad = TRUE;
		m_fApcAutoCreate = TRUE;
		m_axProjectFlag = axProjectNormal;
		EnableCompoundFile(TRUE);
	}

        CApcDocument(OLECHAR* pStgName) : CApcProject<T>(pStgName)
	{
		m_fApcRemember = TRUE;
		m_fApcAmbientDesignMode = TRUE;
		m_fApcAutoLoad = TRUE;
		m_fApcAutoCreate = TRUE;
		m_axProjectFlag = axProjectNormal;
		EnableCompoundFile(TRUE);
	}

	virtual BOOL OnNewDocument()
	{
		ApcEntryHR(CApcDocument::OnNewDocument);

		//
		// VBA requires a storage for a project.  Typically, in MFC,
		// a storage is not created for a new document until the document
		// is saved.  This code forces the creation of a storage using MFC's 
		// own mechanism, though you could just as well create a temporary 
		// one yourself.
		//
		BOOL bSaveEmbedded = m_bEmbedded;
		m_bEmbedded	= FALSE; // force creation of a stg

		BOOL fGood = DocBase::OnNewDocument();
		m_bEmbedded	= bSaveEmbedded;
		if (!fGood)
			return FALSE;

		ASSERT(m_lpRootStg); // should have a stg now

		if (m_fApcAutoCreate)
		{
			ASSERT(g_pApcHost); // did you call ApcHost.Create in your application class?

			hr = ApcProject.Create(g_pApcHost, m_axProjectFlag, NULL);
			ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
			{
				ApcProject.Close();
				return FALSE;
			}

			hr = ApcProject.InitNew(m_lpRootStg);
			ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
			{
				ApcProject.Close();
				return FALSE;
			}
		}

		return TRUE;
	}

	void PreCloseFrame(CFrameWnd* pFrame)
	{
		COleClientItem* pItem;
		
		POSITION pos = GetStartPosition();
		while(pos)
		{
			pItem = (COleClientItem*) GetNextItem(pos);
			if (pItem != NULL)
			{
				if (pItem->IsInPlaceActive())
				{
					pItem->Deactivate();
				}
			}
		}
		
		DocBase::PreCloseFrame(pFrame);
	}

	void DeleteContents()
	{
		ApcProject.Close();

		DocBase::DeleteContents();
	}

	BOOL IsModified()
	{
		if (ApcProject.IsDirty() == S_OK)
			return TRUE;

		return DocBase::IsModified();
	}

	HRESULT ApcLoad()
	{
		ApcEntryHR(CApcDocument::ApcLoad);

		ASSERT(g_pApcHost); // did you call ApcHost.Create in your application class?

		if (S_FALSE == ApcProject.Exists(m_lpRootStg))
			ApcReturnHR(APC_E_NO_VBA_PROJECT);
		ApcCallHR(ApcProject.Open(g_pApcHost, m_axProjectFlag));
		ApcCallHR(ApcProject.Load(m_lpRootStg));
		ApcCallHR(ApcProject.FinishLoading());

		ApcReturnHR(S_OK);
	}

public:

	BOOL m_fApcRemember;
	BOOL m_fApcAmbientDesignMode;
	AxProjectFlag m_axProjectFlag;
	CApcAmbientProperties m_ambientProperties;
	
	void LoadFromStorage()
	{
		ASSERT(m_lpRootStg != NULL);

		// open Contents stream
		COleStreamFile file;
		CFileException fe;
		if (!file.OpenStream(m_lpRootStg, _T("Contents"),
				CFile::modeRead|CFile::shareExclusive, &fe) &&
			!file.CreateStream(m_lpRootStg, _T("Contents"),
				CFile::modeRead|CFile::shareExclusive|CFile::modeCreate, &fe))
		{
			if (fe.m_cause == CFileException::fileNotFound)
				AfxThrowArchiveException(CArchiveException::badSchema);
			else
				AfxThrowFileException(fe.m_cause, fe.m_lOsError);
		}

		// load it with CArchive (loads from Contents stream)
		CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
		loadArchive.m_pDocument = this;
		loadArchive.m_bForceFlat = FALSE;

		TRY
		{
			BOOL fConvert = (S_FALSE == ApcProject.Exists(m_lpRootStg)) && m_fApcAutoCreate;

			if (fConvert)
			{
				HRESULT hr;

				ASSERT(g_pApcHost); // did you call ApcHost.Create in your application class?

				hr = ApcProject.Create(g_pApcHost, m_axProjectFlag);
				if (FAILED(hr))
					AfxThrowOleException(hr);

				hr = ApcProject.InitNew(m_lpRootStg);
				if (FAILED(hr))
					AfxThrowOleException(hr);
			}

			if (file.GetLength() != 0)
			{
				Serialize(loadArchive);     // load main contents
			}

			if (S_OK == ApcProject.Exists(m_lpRootStg) && m_fApcAutoLoad)
			{
				HRESULT hr = ApcLoad();
				if (FAILED(hr))
					AfxThrowOleException(hr);
			}

			loadArchive.Close();
			file.Close();
		}
		CATCH_ALL(e)
		{
			file.Abort();   // will not throw an exception
			DeleteContents();   // removed failed contents
			loadArchive.Abort();
			THROW_LAST();
		}
		END_CATCH_ALL
	}

	void ApcEnableAutoLoad(BOOL fAutoLoad)
	{
		m_fApcAutoLoad = fAutoLoad;
	}

	void ApcEnableAutoCreate(BOOL fAutoCreate)
	{
		m_fApcAutoCreate = fAutoCreate;
	}

	void ApcSetProjectFlag(AxProjectFlag tProjectFlag)
	{
		m_axProjectFlag = tProjectFlag;
	}

	void SaveToStorage(CObject* pObject)
	{
		ASSERT(m_lpRootStg != NULL);

		// create Contents stream
		COleStreamFile file;
		CFileException fe;
		if (!file.CreateStream(m_lpRootStg, _T("Contents"),
				CFile::modeReadWrite|CFile::shareExclusive|CFile::modeCreate, &fe))
		{
			if (fe.m_cause == CFileException::fileNotFound)
				AfxThrowArchiveException(CArchiveException::badSchema);
			else
				AfxThrowFileException(fe.m_cause, fe.m_lOsError);
		}

		// save to Contents stream
		CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
		saveArchive.m_pDocument = this;
		saveArchive.m_bForceFlat = FALSE;
		BOOL fNeedSaveCompleted = FALSE;

		TRY
		{
			// save the contents
			if (pObject != NULL)
			{
				pObject->Serialize(saveArchive);
			}
			else
			{
				BOOL fSaveProject = !!ApcProject;

				if (fSaveProject)
				{
					m_fApcRemember = m_bRemember && !m_bSameAsLoad;

					HRESULT hr = ApcProject.Save(m_lpRootStg, m_bSameAsLoad);
					fNeedSaveCompleted = !ApcGetEmbedded(this);
					if (FAILED(hr))
						AfxThrowOleException(hr);
				}

				Serialize(saveArchive);

				if (fSaveProject)
				{
					fNeedSaveCompleted = FALSE;
					HRESULT hr = ApcProject.SaveCompleted(m_fApcRemember ? m_lpRootStg : NULL);
					ASSERT(SUCCEEDED(hr));
				}
			}
			saveArchive.Close();
			file.Close();

			// commit the root storage
			SCODE sc = m_lpRootStg->Commit(STGC_ONLYIFCURRENT);
			if (sc != S_OK)
				AfxThrowOleException(sc);
		}
		CATCH_ALL(e)
		{
			if (fNeedSaveCompleted)
			{
				HRESULT hr = ApcProject.SaveCompleted(NULL);
				ASSERT(SUCCEEDED(hr));
			}

			file.Abort();   // will not throw an exception
			CommitItems(FALSE); // abort save in progress
			saveArchive.Abort();
			THROW_LAST();
		}
		END_CATCH_ALL
	}

private:
	BOOL m_fApcAutoLoad;
	BOOL m_fApcAutoCreate;

public:
	//
	// Command and Update Command handlers available for use by your derived classes:
	//    ON_COMMAND(ID_VBA_MODE, (CApcDocument<CYourDoc, COleServerDoc>::OnVbaMode))
	//    ON_UPDATE_COMMAND_UI(ID_VBA_MODE, (CApcDocument<CYourDoc, COleServerDoc>::OnUpdateVbaMode))
	//
	afx_msg void OnVbaMode()
	{
		ASSERT(ApcProject);
		if (ApcProject)
		{
			AxProjectMode mode = axModeDesign;
			if (SUCCEEDED(ApcProject->APC_GET(Mode)(&mode)))
			{
				ApcProject->APC_PUT(Mode)(axModeDesign == mode ? axModeRun : axModeDesign);
				BroadcastAmbientPropertyChange(DISPID_AMBIENT_USERMODE);
				UpdateAllViews(NULL);
			}
		}
	}

	afx_msg void OnUpdateVbaMode(CCmdUI* pCmdUI)
	{
		if (ApcProject)
		{
			AxProjectMode mode = axModeDesign;
			ApcProject->APC_GET(Mode)(&mode);
			pCmdUI->SetCheck(axModeDesign == mode);
		}
	}

	afx_msg void OnVbaAmbientMode()
	{
		m_fApcAmbientDesignMode = !m_fApcAmbientDesignMode;
		BroadcastAmbientPropertyChange(DISPID_AMBIENT_USERMODE);
		UpdateAllViews(NULL);
	}

	afx_msg void OnUpdateVbaAmbientMode(CCmdUI* pCmdUI)
	{
		pCmdUI->SetCheck(!m_fApcAmbientDesignMode);
	}

	void BroadcastAmbientPropertyChange(DISPID dispid)
	{
		IOleControl* iOleControl;

		POSITION pos = GetStartPosition();
		while (pos)
		{
			COleClientItem* pOCX = GetNextClientItem(pos);
			if (pOCX)
			{
				iOleControl = NULL;
				ASSERT(pOCX->m_lpObject);
				pOCX->m_lpObject->QueryInterface(IID_IOleControl, (LPVOID*)&iOleControl);
				if (iOleControl)
				{
					iOleControl->OnAmbientPropertyChange(dispid);
					iOleControl->Release();
				}
			}
		}
	}

	BOOL GetAmbientProp( DISPID dispid, VARIANT* pvarResult)
	{
		POSITION pos = GetFirstViewPosition();
		CView* pView = GetNextView(pos);

		if (dispid == DISPID_AMBIENT_USERMODE)
		{
			//---
			if (ApcProject)
			{
				AxProjectMode mode = axModeDesign;
				if (SUCCEEDED(ApcProject->APC_GET(Mode)(&mode)))
				{
					V_VT(pvarResult) = VT_BOOL;
					V_BOOL(pvarResult) = ( mode == axModeDesign ) && !m_fApcAmbientDesignMode ? 0 : (VARIANT_BOOL) -1;
					return TRUE;
				}
			}
			else
			{
				V_VT(pvarResult) = VT_BOOL;
				V_BOOL(pvarResult) = !m_fApcAmbientDesignMode ? 0 : (VARIANT_BOOL) -1;
				return TRUE;
			}
		}

		//
		// Some using MFC might implement the 
		// same operation.  Figure this wrapper a representative example.
		//
		return m_ambientProperties.GetAmbientProp(pView, dispid, pvarResult);
	}
};

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcOleServerDoc - base class for your embedded document class

void ApcOnSaveEmbedded(COleServerDoc* pThis, LPSTORAGE pStgSave);
void ApcOnSaveEmbedded(CDocument* pThis, LPSTORAGE pStgSave);
void ApcNotifySaved(COleServerDoc* pThis);
void ApcNotifySaved(CDocument* pThis);

template <class T, class DocBase = CApcDocument>
class CApcOleServerDoc :
	public DocBase
{
private:
	typedef CApcOleServerDoc<T, DocBase> ThisClass;
	IPersistStorage* m_pBasePS;

	static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[];
	static AFX_DATA const AFX_INTERFACEMAP interfaceMapData;
protected:
	static AFX_DATA const CApcOleServerDocInterfaceMap interfaceMap; 

#ifdef _AFXDLL
	static const AFX_INTERFACEMAP* PASCAL _GetBaseInterfaceMap() {
		return &DocBase::interfaceMap; }
#endif
	virtual const AFX_INTERFACEMAP* GetInterfaceMap() const {
		return &ThisClass::interfaceMap; }
public:
	CApcOleServerDoc()
	{
		m_fApcRemember = TRUE;
		m_fApcAmbientDesignMode = TRUE;
		m_fApcAutoLoad = TRUE;
		m_fApcAutoCreate = TRUE;
		m_axProjectFlag = axProjectNormal;
		EnableCompoundFile(TRUE);
		m_pBasePS = interfaceMap.GetPersistStorage(this);
	}

    CApcOleServerDoc(OLECHAR* pStgName) : CApcProject<T>(pStgName)
	{
		m_fApcRemember = TRUE;
		m_fApcAmbientDesignMode = TRUE;
		m_fApcAutoLoad = TRUE;
		m_fApcAutoCreate = TRUE;
		m_axProjectFlag = axProjectNormal;
		EnableCompoundFile(TRUE);
		m_pBasePS = interfaceMap.GetPersistStorage(this);
	}

	virtual BOOL OnNewDocument()
	{
		ApcEntryHR(CApcOleServerDoc::OnNewDocument);

		ASSERT(m_bCompoundFile); // did you call EnableCompoundFile in constructor?
		ASSERT(g_pApcHost); // did you call VaoHost.Create in your application class?

		BOOL fGood = COleServerDoc::OnNewDocument();
		if (!fGood)
			return FALSE;

		ASSERT(m_lpRootStg || m_bEmbedded);

		// if we're created or loaded in-place, then MFC's calls to OnNewDocument are
		// a little strange.
		//
		// at the COM level, the client CoCreates the document object, QI's for 
		// IPersistStorage then calls either IPersistStorage::InitNew or 
		// IPersistStorage::Load.
		//
		// when the document is CoCreated, MFC always calls OnNewDocument
		//
		// later, when there is a call to IPersistStorage::InitNew or 
		// IPersistStorage::Load, MFC calls DeleteContents then OnNewDocument or
		// OnOpenDocument(NULL).
		//
		// we handle this by ignoring the first call to OnNewDocument when
		// running in-place.
		//
		// if you want to make your app safe to run in-place, you can perform
		// the same test in your OnNewDocument function
		if (!m_lpRootStg)
			return TRUE; // running in-place; must ignore first call to OnNewDocument

		// if we got this far, then there is an IStorage and we will init VBA

		if (m_fApcAutoCreate)
		{
			ASSERT(g_pApcHost); // did you call ApcHost.Create in your application class?
			
			hr = ApcProject.Create(g_pApcHost, m_axProjectFlag, NULL);
			ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
			{
				ApcProject.Close();
				return FALSE;
			}

			hr = ApcProject.InitNew(m_lpRootStg);
			ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
			{
				ApcProject.Close();
				return FALSE;
			}
		}

		return TRUE;
	}


	class XPersistStorage : public IPersistStorage
	{
	public:
		STDMETHODIMP QueryInterface(
			REFIID iid, LPVOID* ppvObj)
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->ExternalQueryInterface(&iid, ppvObj);
		}

		STDMETHODIMP_(ULONG) AddRef()
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->ExternalAddRef();
		}

		STDMETHODIMP_(ULONG) Release()
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->ExternalRelease();
		}

		#ifndef _AFX_NO_NESTED_DERIVATION
			size_t m_nOffset;
			XPersistStorage()
			{ 
				m_nOffset = offsetof(ThisClass, m_xPersistStorage); 
			}
		#endif

		STDMETHODIMP GetClassID(LPCLSID lpClassID)
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->m_pBasePS->GetClassID(lpClassID);
		}

		STDMETHODIMP IsDirty()
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->m_pBasePS->IsDirty();
		}

		STDMETHODIMP InitNew(LPSTORAGE pStg)
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->m_pBasePS->InitNew(pStg);
		}

		STDMETHODIMP Load(LPSTORAGE pStg)
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			return pThis->m_pBasePS->Load(pStg);
		}

		STDMETHODIMP Save(LPSTORAGE pStgSave, BOOL fSameAsLoad)
		{
			METHOD_PROLOGUE_EX_(ThisClass, PersistStorage)
			ASSERT_VALID(pThis);

			SCODE sc = S_OK;
			TRY
			{
				// delegate through the document
				ASSERT(pThis->m_bRemember);
				pThis->m_bRemember = FALSE;
				pThis->m_bSameAsLoad = fSameAsLoad;
				ApcOnSaveEmbedded(pThis, pStgSave);

				// clear dirty flag since save to same storage successful
				if (fSameAsLoad)
				{
					pThis->SetModifiedFlag(FALSE);

					// notify clients that object has been saved
					ApcNotifySaved(pThis);
				}
			}
			CATCH_ALL(e)
			{
				sc = COleException::Process(e);
				e->Delete();
			}
			END_CATCH_ALL

			// restore default state
			pThis->m_bRemember = TRUE;

			ASSERT_VALID(pThis);
			return sc;
		}

		STDMETHODIMP SaveCompleted(LPSTORAGE pStgSaved)
		{
			METHOD_PROLOGUE_EX(ThisClass, PersistStorage)
			HRESULT hr1=pThis->ApcProject.SaveCompleted(pStgSaved);
			HRESULT hr2=pThis->m_pBasePS->SaveCompleted(pStgSaved);
			if (FAILED(hr1))
				return hr1;
			if (FAILED(hr2))
				return hr2;
			return NOERROR;
		}

		STDMETHODIMP HandsOffStorage()
		{
			METHOD_PROLOGUE_EX(ThisClass, PersistStorage)
			HRESULT hr1=pThis->ApcProject.HandsOffStorage();
			HRESULT hr2=pThis->m_pBasePS->HandsOffStorage();
			if (FAILED(hr1))
				return hr1;
			if (FAILED(hr2))
				return hr2;
			return NOERROR;
		}
	
	} m_xPersistStorage;
	friend class XPersistStorage;

private:
	BOOL m_fApcAutoLoad;
	BOOL m_fApcAutoCreate;

};

#ifdef _AFXDLL
	template <class T, class DocBase>
	const AFX_DATADEF AFX_INTERFACEMAP CApcOleServerDoc<T,DocBase>::interfaceMapData =
		{ &ThisClass::_GetBaseInterfaceMap, &ThisClass::_interfaceEntries[0], };

#else
	template <class T, class DocBase>
	const AFX_DATADEF AFX_INTERFACEMAP CApcOleServerDoc<T,DocBase>::interfaceMapData =
		{ &DocBase::interfaceMap, &ThisClass::_interfaceEntries[0], };
#endif

template <class T, class DocBase>
const AFX_DATADEF AFX_INTERFACEMAP_ENTRY CApcOleServerDoc<T,DocBase>::_interfaceEntries[] =
{
	{ &IID_IPersistStorage, offsetof(ThisClass, m_xPersistStorage) },
	{ NULL, (size_t)-1 }
};

template <class T, class DocBase>
const CApcOleServerDocInterfaceMap CApcOleServerDoc<T,DocBase>::interfaceMap = CApcOleServerDocInterfaceMap(
	CApcOleServerDoc<T,DocBase>::interfaceMapData, DocBase::interfaceMap);


/////////////////////////////////////////////////////////////////////////////

void ApcSerializeGUID(CArchive& ar, GUID& guid);

//
// MFC WORKAROUND access functions (defined in apcImpl.cpp)
//
BOOL ApcGetSameAsLoad(COleDocument* pDoc);
DVTARGETDEVICE* ApcGetTargetDevice(COleDocument* pDoc);


#ifndef APC_NO_OLECLIENTITEM

//#include <afxpriv2.h>

/////////////////////////////////////////////////////////////////////////////
//*public: safe to use in client code.
// CApcOleClientItem - base class for your OleClient class

#ifndef APC_HINT_UPDATE_OLEITEM
	#define APC_HINT_UPDATE_OLEITEM 0x00FFFFFF
#endif

//
// CApcOleClientItem
//

#ifdef _DEBUG

	#define APC_STDMETHOD(theClass, localClass, retVal) \
		METHOD_PROLOGUE(theClass, localClass) \
		ASSERT_VALID(pThis); \
		return retVal;

#else

	#define APC_STDMETHOD(theClass, localClass, retVal) \
		return retVal;

#endif

#define APC_STDREFCOUNT(theClass, localClass) \
 		STDMETHOD_(ULONG, AddRef)() \
		{ \
			METHOD_PROLOGUE(theClass, localClass) \
			return (ULONG) pThis->ExternalAddRef(); \
		} \
		STDMETHOD_(ULONG, Release)() \
		{ \
			METHOD_PROLOGUE(theClass, localClass) \
			return (ULONG) pThis->ExternalRelease(); \
		}

#define APC_STDQI(theClass, localClass) \
		STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj) \
		{ \
			METHOD_PROLOGUE(theClass, localClass) \
			return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj); \
		}

#define APC_BEGIN_INTERFACE_PART(localClass, baseClass) \
		class X##localClass : public baseClass \
		{ \
		public:


#define	IMPLTYPE_FDEFAULTSOURCE	(IMPLTYPEFLAG_FSOURCE | IMPLTYPEFLAG_FDEFAULT)
#define	IMPLTYPE_MASK (0x1 | 0x2 | 0x4 | 0x8)

template <class T, class BaseClass = COleClientItem>
class CApcOleClientItem : 
	public BaseClass,
	public CApcControl<T>
{
public:
	typedef CApcOleClientItem<T> _CApcOleClientItem;
	typedef BaseClass _CApcOleClientItemBaseClass;

	CApcOleClientItem(COleDocument* pContainerDoc) : _CApcOleClientItemBaseClass(pContainerDoc)
	{
		m_clsid = IID_NULL;
		m_iidEvents = IID_NULL;
		m_rect = CRect(10, 10, 210, 210);
		m_extent = m_rect.Size();
		m_extentIcon = CSize(0,0);
		m_bFreeze = FALSE;
		m_bSerializing = FALSE;
		m_dwMiscStatus = 0;

		//
		// ConnectionPoint members
		//
		m_pEventConnectionPoint = NULL;
		m_nEventCookie = 0;
			
		m_pBindConnectionPoint = NULL;
		m_nBindCookie = 0;
	}

	~CApcOleClientItem()
	{
		if (ApcControl)
			ApcControl.Detach();

		if (m_pEventConnectionPoint || m_pBindConnectionPoint)
			Release();

		if (m_pBindConnectionPoint != NULL)
		{
			m_pBindConnectionPoint->Release();
			m_pBindConnectionPoint = NULL;
		}

		//---ASSERT(m_pProjItem == NULL);
	}

	//
	// ApcControl base class helper
	//
	HRESULT ApcFireEvent(DISPID dispid = 1, DISPPARAMS* pDispParams = NULL, VARIANT* pVarResult = NULL)
	{
		ApcEntryHR(CApcOleClientItem::FireEvent);

		if (m_iidEvents != IID_NULL)
		{
			//
			// fire on composite control
			//
			if (ApcControl)
			{
				CComPtr<IDispatch> spCC;
				ApcCallHR(ApcControl->APC_GET(CompositeControl)(&spCC));
				if (spCC)
				{
					ApcCallHR(MSAPC::ApcFireEvent(spCC, m_iidEvents, dispid, pDispParams, pVarResult));
				}
			}
		}

		ApcReturnHR(S_OK);
	}

	//
	// ApcControl overrides
	//
	HRESULT ApcControl_OnDefine(IApcProjectItem* pProjectItem, IDispatch* pHostControl, AxControlFlag controlFlag, IDispatch* pExtender)
	{
		ApcEntryHR(CApcOleClientItem::OnDefine);

		//
		// Give Client Item BASE a notification
		//
		ApcCallHR(CApcControl<T>::ApcControl_OnDefine(pProjectItem, pHostControl, controlFlag, pExtender));

		ASSERT(m_dwItemNumber);

		ApcReturnHR(hr);
	}

	HRESULT ApcControl_OnUndefine()
	{
		ApcEntryHR(CApcOleClientItem::OnUndefine);

		//
		// Give Client Item BASE a notification
		//
		ApcCallHR(CApcControl<T>::ApcControl_OnUndefine());

		ApcReturnHR(hr);
	}

	//
	// ApcItem overrides
	//
	IApcRegControls* ApcOleItem_GetApcProjItemRegControls()
	{
		T* pT = static_cast<T*>(this);
		ASSERT(pT->GetDocument());
		return pT->GetDocument()->ApcProjectItem.GetApcRegControls();
	}

	HRESULT ApcOleItem_CreateExtender(IUnknown** ppExtender)
	{
		return S_OK; // not required
	}

	HRESULT ApcOleItem_OnGetAmbientProp(DISPID dispid, VARIANT* pvarResult)
	{
		return S_OK; // not required
	}

protected:
    virtual void Release(OLECLOSE dwCloseOption = OLECLOSE_NOSAVE)
	{
		if (ApcControl)
			ApcControl.Detach();

		UINT nSt = GetItemState();
		if ((nSt == activeUIState) || (nSt == activeState) || (nSt == openState)) 
			Close(OLECLOSE_NOSAVE);

		// if we are connected to the events connection point
		if (m_pEventConnectionPoint != NULL)
		{
			// unadvise and release
			m_pEventConnectionPoint->Unadvise(m_nEventCookie);
			m_pEventConnectionPoint->Release();
			m_pEventConnectionPoint = NULL;
		}

		// if we are connected to the property change notification conn pt
		if (m_pBindConnectionPoint != NULL)
		{
			// unadvise and release
			m_pBindConnectionPoint->Unadvise(m_nBindCookie);
			m_pBindConnectionPoint->Release();
			m_pBindConnectionPoint = NULL;
		}

		_CApcOleClientItemBaseClass::Release(dwCloseOption);
	}

// Attributes
public:
	virtual CLSID* GetClassID()
	{ 
		return &m_clsid; 
	}
	virtual IID* GetEventsIID()
	{ 
		return &m_iidEvents; 
	}
	virtual const CRect& GetItemRect()
	{ 
		return m_rect; 
	}

// APC Extensions for control support
public:
	virtual void Invalidate()
	{
		GetDocument()->UpdateAllViews(NULL, APC_HINT_UPDATE_OLEITEM, this);
	}

	virtual void Move(CRect& rc)
	{
		// invalidate old rect
		Invalidate();

		// Save the new position and set the extent
		CRect oldRect = m_rect;
		m_rect = rc;
		m_extent = m_rect.Size();

		if (oldRect.Size() != rc.Size())
		{
			CSize size = m_extent;
			CClientDC dc(NULL);
			dc.DPtoHIMETRIC(&size);
			SetExtent(size);
		}

		// update item rect when in-place active
		if (IsInPlaceActive()) 
		{
			SetItemRects();
		}
		
		// invalidate new rect
		Invalidate();
	}

	virtual void SetRect(CRect& rc)
	{
		SetSize(rc.Size());
	}

	virtual void SetSize(CSize size)
	{
		DVASPECT dv = GetDrawAspect();
		if (dv == DVASPECT_ICON) 
		{
			m_extentIcon = size;
		}
		else 
		{
			m_extent = size;
		}
	}

	virtual void SetFreezeState(BOOL bFreeze)
	{
		m_bFreeze = bFreeze;

		// Inform the control whether the container is ignoring or accepting
		// events from the control.
		IOleControl* pIOleControl = NULL;

		if (m_lpObject != NULL)
		{
			HRESULT hr = m_lpObject->QueryInterface(IID_IOleControl, (LPVOID*)&pIOleControl);

			if (SUCCEEDED(hr)) 
			{
				pIOleControl->FreezeEvents(bFreeze);
				pIOleControl->Release();
			}
		}

	}

	virtual BOOL UpdateExtent()
	{
		CSize size;

		if (GetExtent(&size)) 
		{
			// OLE returns the extent in HIMETRIC units -- we need pixels
			CClientDC dc(NULL);
			dc.HIMETRICtoDP(&size);

			// only invalidate if it has actually changed
			if (size != m_rect.Size()) 
			{
				// invalidate old, update, invalidate new
				Invalidate();

				m_rect.bottom = m_rect.top + size.cy;
				m_rect.right = m_rect.left + size.cx;
				m_extent = m_rect.Size();

				Invalidate();

				// mark document as modified
				GetDocument()->SetModifiedFlag(TRUE);
			}         
			return TRUE;
		}

		return FALSE;
	}

	virtual BOOL UpdateExtentFromServer()
	{
		CSize size;

		// get size in pixels
		if (!GetExtent(&size)) 
		{
			return FALSE;       // blank
		}

		if (size == m_extent) 
		{
			return FALSE;
		}

		// if new object (i.e. m_extent is empty) setup position
		if (m_extent == CSize(0,0))
		{
			m_rect.right	= m_rect.left + MulDiv(size.cx,10,254);
			m_rect.bottom = m_rect.top - MulDiv(size.cy,10,254);
		}
		else
		{
			if (!IsInPlaceActive() && size != m_extent)
			{
				// data changed and not inplace, so scale up rect as well
				m_rect.right = m_rect.left +
					MulDiv(m_rect.Width(),size.cx, m_extent.cx);
				m_rect.bottom = m_rect.top +
					MulDiv(m_rect.Height(),size.cy, m_extent.cy);
			}
		}

		m_extent = size;

		Invalidate();

		return TRUE;
	}

	void DeactivateUI()
	{
	   if (IsOleControl())
		  return;

	   _CApcOleClientItemBaseClass::DeactivateUI();
	}

	BOOL IsOleControl()
	{
		if (m_lpObject != NULL) 
		{
			IOleControl* pIOleControl;

			HRESULT hr = m_lpObject->QueryInterface(IID_IOleControl, (LPVOID*)& pIOleControl);
			if (SUCCEEDED(hr)) 
			{
				pIOleControl->Release();
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL IsUIActive() const
	{
		return (GetItemState() == activeUIState);
	}
	BOOL IsInsideOut() const
	{
		return (m_dwMiscStatus & OLEMISC_INSIDEOUT);
	}
	DWORD HitTest(CPoint point)
	{
		if (!GetItemRect().PtInRect(point))
			return HITRESULT_OUTSIDE;

		CComPtr<IViewObjectEx> spViewObjectEx;
		HRESULT hr = m_lpObject->QueryInterface(IID_IViewObjectEx, (void**) &spViewObjectEx.p);
		if (SUCCEEDED(hr))
		{
			DWORD dwHitResult;
			hr = spViewObjectEx->QueryHitPoint(DVASPECT_CONTENT, &GetItemRect(), point, 0, &dwHitResult);
			if (SUCCEEDED(hr))
				return dwHitResult;
		}
		
		return HITRESULT_HIT;
	}

protected:
	// APC control extension support
	CLSID m_clsid;
	IID m_iidEvents;
	BOOL m_bFreeze;
	BOOL m_bSerializing;
	DWORD m_dwMiscStatus;

	// Drawing support
	CRect m_rect;
	CSize m_extent;
	CSize m_extentIcon;

	// Connection Points
	void InitEvents()
	{
		ASSERT_VALID(this);
		ASSERT(m_lpObject != NULL);

		//
		//  Use the control's class info to obtain its default events interface (m_iidEvents)
		//
		
		// QI IProvideClassInfo
		LPPROVIDECLASSINFO lpProvide = NULL;
		if (SUCCEEDED(m_lpObject->QueryInterface(IID_IProvideClassInfo, (LPVOID*) &lpProvide)))
		{
			ASSERT(lpProvide != NULL);
 
			// QI ITypeInfo
			LPTYPEINFO lpClassInfo = NULL;
			if (SUCCEEDED(lpProvide->GetClassInfo(&lpClassInfo)))
			{
				ASSERT(lpClassInfo != NULL);

				// get the Type Attribute from ITypeInfo
				LPTYPEATTR lpTypeClass;
				if (SUCCEEDED(lpClassInfo->GetTypeAttr(&lpTypeClass)))
				{
					UINT nCount;
					int iFlags;
					HREFTYPE hRefType;

					// make sure it was for the control's coclass
					ASSERT(lpTypeClass != NULL);
					ASSERT(lpTypeClass->typekind == TKIND_COCLASS);
 
					//
					//  Search for typeinfo of the default events interface.
					//

					// for each of the implemented parts of the interface
					for (nCount = 0; nCount < lpTypeClass->cImplTypes; nCount++)
					{
						// see if its the default source (the events dispatch interface)
						if (SUCCEEDED(lpClassInfo->GetImplTypeFlags(nCount, &iFlags)) && ((iFlags & IMPLTYPE_MASK) == IMPLTYPE_FDEFAULTSOURCE))
						{
							LPTYPEINFO lpTypeInfo = NULL;
                        
							// if it is then get its refernece type and its ITypeInfo
							if (SUCCEEDED(lpClassInfo->GetRefTypeOfImplType(nCount, &hRefType)) &&
								SUCCEEDED(lpClassInfo->GetRefTypeInfo(hRefType, &lpTypeInfo)))
							{
								ASSERT(lpTypeInfo != NULL);

								LPTYPEATTR lpType = NULL;

								// if we have a valid ITypeInfo and we can retrieve its type attributes
								if (lpTypeInfo != NULL && SUCCEEDED(lpTypeInfo->GetTypeAttr(&lpType)))
								{
									//
									// store the GUID, it's the IID for the events interface
									//
									m_iidEvents = lpType->guid;

									// release the type attribute and return
									lpTypeInfo->ReleaseTypeAttr(lpType);
									lpType = NULL;
								}
									
								// Release and bail
								lpTypeInfo->Release();
								lpTypeInfo = NULL;
							}                     
							break;
						}
					}          
					lpClassInfo->ReleaseTypeAttr(lpTypeClass);
					lpTypeClass = NULL;
				}                     
				lpClassInfo->Release();
				lpClassInfo = NULL;
			}          
			lpProvide->Release();
		}

		//
		//  Wire the control to our event handlers
		//

		// QI IConnectionPointContainer
		LPCONNECTIONPOINTCONTAINER lpContainer;
		if (SUCCEEDED(m_lpObject->QueryInterface(IID_IConnectionPointContainer, (LPVOID FAR*)&lpContainer)))
		{
			ASSERT(lpContainer != NULL);

			// request the connection point for the events IID
			if (SUCCEEDED(lpContainer->FindConnectionPoint(m_iidEvents, &m_pEventConnectionPoint)))
			{
				ASSERT(m_pEventConnectionPoint != NULL);
				if (m_pEventConnectionPoint != NULL) 
				{
					// advise the connection point, so we receive event notifications
					m_pEventConnectionPoint->Advise(&m_xEventSink, &m_nEventCookie);
				}
			}

			// request the connection point for the property notification sink 
			if (SUCCEEDED(lpContainer->FindConnectionPoint(IID_IPropertyNotifySink, &m_pBindConnectionPoint)))
			{
				ASSERT(m_pBindConnectionPoint != NULL);
				if (m_pBindConnectionPoint != NULL) 
				{
					// advise the connection point, so we receive property change notifications
					m_pBindConnectionPoint->Advise(&m_xPropertyNotifySink, &m_nBindCookie);
				}
			}

			// we are done with the connection point container
			lpContainer->Release();
		}
	}

	LPCONNECTIONPOINT m_pEventConnectionPoint;
	DWORD m_nEventCookie;
	LPCONNECTIONPOINT m_pBindConnectionPoint;
	DWORD m_nBindCookie;

// Operations
public:
	//
	// WORKAROUND:  A bug in MFC's COleClientItem::Draw implementation requires
	// this block copy of the function, which correctly passes NULL for the 8th
	// parameter to IViewObject::Draw (lprcWBounds) when not drawing a metafile
	//
	BOOL Draw(CDC* pDC, LPCRECT lpBounds, DVASPECT nDrawAspect = (DVASPECT)-1)
	{
		ASSERT_VALID(this);
		ASSERT(AfxIsValidAddress(lpBounds, sizeof(RECT), FALSE));
		ASSERT_VALID(pDC);

		if (m_lpObject == NULL || m_lpViewObject == NULL)
			return FALSE;   // partially created COleClientItem object

		// use current draw aspect if aspect is -1 (default)
		if (nDrawAspect == -1)
			nDrawAspect = m_nDrawAspect;

		// convert RECT lpBounds to RECTL rclBounds
		RECTL rclBounds;
		rclBounds.left = lpBounds->left;
		rclBounds.top = lpBounds->top;
		rclBounds.right = lpBounds->right;
		rclBounds.bottom = lpBounds->bottom;

		// get RECTL describing window extents and origin
		RECTL rclWBounds;
		CPoint ptOrg = pDC->GetWindowOrg();
		CSize sizeExt = pDC->GetWindowExt();
		rclWBounds.left = ptOrg.x;
		rclWBounds.top = ptOrg.y;
		rclWBounds.right = sizeExt.cx;
		rclWBounds.bottom = sizeExt.cy;

		// WORKAROUND >>>
		LPRECTL rclWBoundsParam = NULL;
		// <<< WORKAROUND

		// get target device to use for draw
		COleDocument* pDoc = GetDocument();
		const DVTARGETDEVICE* ptd = NULL;
		HDC hdcTarget = NULL;
		// WORKAROUND >>>
		if (pDC->IsPrinting() && ApcGetTargetDevice(pDoc) != NULL)
		// <<< WORKAROUND
		{
			ptd = ApcGetTargetDevice(pDoc);
			hdcTarget = pDC->m_hAttribDC;
			// WORKAROUND >>>
			rclWBoundsParam = &rclWBounds;
			// <<< WORKAROUND
		}

		// attempt draw with target device
		SCODE sc = m_lpViewObject->Draw(nDrawAspect, -1, NULL,
			(DVTARGETDEVICE*) ptd, hdcTarget, pDC->m_hDC,
			&rclBounds, &rclWBounds, NULL, 0);
		if (ptd != NULL && sc == OLE_E_BLANK)
		{
			// attempt draw without target device
			// WORKAROUND >>>
			sc = m_lpViewObject->Draw(nDrawAspect, -1, NULL,
				NULL, NULL, pDC->m_hDC,
				&rclBounds, rclWBoundsParam, NULL, 0);
			// <<< WORKAROUND
		}

		if (sc != S_OK && sc == OLE_E_BLANK)
			return FALSE;   // return FALSE if the object is blank

		CheckGeneral(sc);   // otherwise, may throw exception on error
		return TRUE;
	}
	//{{AFX_VIRTUAL(CApcOleClientItem)
public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam)
	{
		ASSERT_VALID(this);

		_CApcOleClientItemBaseClass::OnChange(wNotification, dwParam);

		switch (wNotification)
		{
			case OLE_CHANGED:
				UpdateExtent();
				Invalidate();
				break;

			case OLE_CHANGED_ASPECT:
			case OLE_CHANGED_STATE:
				Invalidate();
				break;
		}
	}
	virtual void OnActivate()
	{
		_CApcOleClientItemBaseClass::OnActivate();
	}

protected:
	virtual void OnGetItemPosition(CRect& rPosition)
	{
		ASSERT_VALID(this);

		if (m_rect.Size() == CSize(0,0)) 
		{
			UpdateExtentFromServer();
		}

		// Return m_rect, which is in document coordinates
		rPosition = m_rect;
	}

	virtual void OnDeactivateUI(BOOL bUndoable)
	{
		_CApcOleClientItemBaseClass::OnDeactivateUI(bUndoable);

		// Close an in-place active item whenever it removes the user
		//  interface.  The action here should match as closely as possible
		//  to the handling of the escape key in the view.
		if (!IsOleControl()) 
		{
			Deactivate();
		}
	}

	virtual BOOL OnChangeItemPosition(const CRect& rectPos)
	{
		ASSERT_VALID(this);

		// During in-place activation CApcOleClientItem::OnChangeItemPosition
		//  is called by the server to change the position of the in-place
		//  window.  Usually, this is a result of the data in the server
		//  document changing such that the extent has changed or as a result
		//  of in-place resizing.
		//
		// The default here is to call the base class, which will call
		//  COleClientItem::SetItemRects to move the item
		//  to the new position.

		if (!_CApcOleClientItemBaseClass::OnChangeItemPosition(rectPos))
			return FALSE;

		// Update the position stored in the item
		Invalidate();
		m_rect = rectPos;
		Invalidate();

		// Treat any change in position as a modification of the document.
		GetDocument()->SetModifiedFlag(TRUE);

		return TRUE;
	}

	//}}AFX_VIRTUAL

// Advanced overridables
protected:

	virtual BOOL FinishCreate(SCODE sc)
	{
		// chain to base clase
		BOOL bCreated = _CApcOleClientItemBaseClass::FinishCreate(sc);

		// if base class finished successfully
		if (bCreated)
		{
			_CApcOleClientItemBaseClass::GetClassID(&m_clsid);

			// Note we don't explicitly handle freezing events here, if we wished to,
			// we would grab the OLE object and inform it that its events are frozen.

			InitEvents(); //InitControlInfo InitBindInfo

			m_lpObject->GetMiscStatus(DVASPECT_CONTENT, &m_dwMiscStatus);

			if (!m_bSerializing) 
			{
				// Force links to be updated for the embedded item.
				UpdateLink();

				// Update the extent of the newly created item.
				UpdateExtent();
			}
		}

		return bCreated;
	}

	virtual void Serialize(CArchive& ar)
	{
		ASSERT_VALID(this);

		m_bSerializing = TRUE;

		if (ar.IsStoring())
		{
			//
			// WORKAROUND: MFC is not calling the initial OleSave if the IPersistStorage
			// is not dirty.  This results in an error further downstrean when
			// IPersistStorage::SaveCompleted is called. <OLECLI1.cpp>
			//

			// save dirty object
			// determine destination storage
			COleDocument* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			ASSERT(m_lpStorage != NULL);
			LPPERSISTSTORAGE lpPersistStorage = NULL;
			HRESULT hr = m_lpObject->QueryInterface(IID_IPersistStorage, (void**) &lpPersistStorage);
			ASSERT(FAILED(hr) || lpPersistStorage != NULL);

			if (SUCCEEDED(hr) && ((ApcGetSameAsLoad(pDoc) && lpPersistStorage->IsDirty() == S_FALSE) && (!ar.m_bForceFlat)))
			{
				// call OleSave now and IPersistStorage::SaveCompleted later
				hr = ::OleSave(lpPersistStorage, m_lpStorage, TRUE);
				if (FAILED(hr)) {
					AfxThrowOleException(hr);
				}
			}

			lpPersistStorage->Release();
		}
		
		// Call base class first to read in COleClientItem data.
		// Since this sets up the m_pDocument pointer returned from
		//  CApcOleClientItem::GetDocument, it is a good idea to call
		//  the base class Serialize first.
		_CApcOleClientItemBaseClass::Serialize(ar);

		BOOL bRegistered = FALSE;
		DWORD nID = -1;

		// now store/retrieve data specific to CApcOleClientItem
		if (ar.IsStoring())
		{
			if (ApcControl)
			{
				bRegistered = TRUE;
				nID = ApcControl.ID(); //ApcControl->APC_GET(ID)(&nID);
			}

			ar << bRegistered;
			ar << nID;

			// Save the class information for the object
			ApcSerializeGUID(ar, m_clsid);
			ApcSerializeGUID(ar, m_iidEvents);

			// Save the position and extent
			ar << m_rect;
			ar << m_extent;
			ar << m_bFreeze;
			BOOL bSelected = FALSE;
			ar << bSelected;
		}
		else
		{
			ar >> bRegistered;
			ar >> nID;

			// Restore the class information for the object
			ApcSerializeGUID(ar, m_clsid);
			ApcSerializeGUID(ar, m_iidEvents);

			// Restore the position and extent
			ar >> m_rect;
			ar >> m_extent;
			ar >> m_bFreeze;
			BOOL bSelected;
			ar >> bSelected;
			ASSERT(bSelected == FALSE);
		}
		m_bSerializing = FALSE;

		// now register the control
		if ((!ar.IsStoring()) && bRegistered)
		{
			HRESULT hr;
			T* pT = static_cast<T*>(this);

			CComPtr<IDispatch> spExtender;
			hr = pT->ApcOleItem_CreateExtender((IUnknown**) &spExtender);
			ASSERT(SUCCEEDED(hr));

			IApcRegControls* ireg;
			ireg = pT->ApcOleItem_GetApcProjItemRegControls();

			CComQIPtr<IDispatch, &IID_IDispatch> spPrimary(m_lpObject);

			ASSERT(nID != -1);
			hr = ApcControl.Register(ireg, nID, spPrimary, spExtender);
			ASSERT(SUCCEEDED(hr));
		}
	}

	virtual HRESULT OnChanged(DISPID dispid)
	{
		return S_OK;
	}

	virtual HRESULT OnRequestEdit(DISPID dispid)
	{
		return S_OK;
	}

protected:
	LPUNKNOWN GetInterfaceHook(const void* piid)
	{
		//
		//  If requested IID is same as the one we looked up in the registry
		//  (see InitControlInfo), return pointer to our event handler code.
		//
		if (*(IID FAR*)piid == m_iidEvents)
			return &m_xEventSink;

		else if (*(IID FAR*)piid == IID_IOleControlSite)
			return &m_xOleControlSite;

		else if (*(IID FAR*)piid == IID_IPropertyNotifySink)
			return &m_xPropertyNotifySink;

		else if (*(IID FAR*)piid == IID_IDispatch)
			return &m_xAmbientProps;
	
		return NULL;
	}

	/////////////////////////////////////////////////////////////////////////////
	// CApcOleClientItem::XOleControlSite

	APC_BEGIN_INTERFACE_PART(OleControlSite, IOleControlSite)
		INIT_INTERFACE_PART(CApcOleClientItem, OleControlSite)
		APC_STDREFCOUNT(CApcOleClientItem, OleControlSite)
		APC_STDQI(CApcOleClientItem, OleControlSite)
		STDMETHOD(OnControlInfoChanged)()
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, E_NOTIMPL);
		}
		STDMETHOD(LockInPlaceActive)(BOOL fLock)
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, E_NOTIMPL);
		}
		STDMETHOD(GetExtendedControl)(LPDISPATCH* ppDisp)
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, E_NOTIMPL);
		}
		STDMETHOD(TransformCoords)(POINTL* lpptlHimetric, POINTF* lpptfContainer, DWORD flags)
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, E_NOTIMPL);
		}
		STDMETHOD(TranslateAccelerator)(LPMSG lpMsg, DWORD grfModifiers)
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, E_NOTIMPL);
		}
		STDMETHOD(OnFocus)(BOOL bGotFocus)
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, S_OK);
		}
		STDMETHOD(ShowPropertyFrame)()
		{
			APC_STDMETHOD(CApcOleClientItem, OleControlSite, E_NOTIMPL);
		}
	END_INTERFACE_PART(OleControlSite)

	/////////////////////////////////////////////////////////////////////////////
	// CApcOleClientItem::XAmbientProps

	APC_BEGIN_INTERFACE_PART(AmbientProps, IDispatch)
		INIT_INTERFACE_PART(CApcOleClientItem, AmbientProps)
		APC_STDREFCOUNT(CApcOleClientItem, AmbientProps)
		APC_STDQI(CApcOleClientItem, AmbientProps)
		STDMETHOD(GetTypeInfoCount)(unsigned int* ptinfo)
		{
			METHOD_PROLOGUE(CApcOleClientItem, AmbientProps)
			ASSERT_VALID(pThis);
			*ptinfo = 0;
			return S_OK;
		}
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**)
		{
			METHOD_PROLOGUE(CApcOleClientItem, AmbientProps)
			ASSERT_VALID(pThis);
			return ResultFromScode(E_NOTIMPL);
		}
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int cNames, LCID, DISPID* rgdispid)
		{
			METHOD_PROLOGUE(CApcOleClientItem, AmbientProps)
			ASSERT_VALID(pThis);

			UINT nIdx = 0;

			// we don't support mnemnoics, it isn't required
			while (nIdx < cNames) 
			{ 
				rgdispid[nIdx] = DISPID_UNKNOWN;
				nIdx++;
			}
			return S_OK;
		}
		STDMETHOD(Invoke)(DISPID dispid, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr)
		{
			UNUSED(wFlags);
			UNUSED(pDispParams);
			UNUSED(pexcepinfo);
			UNUSED(puArgErr);

			METHOD_PROLOGUE(CApcOleClientItem, AmbientProps)
			ASSERT(wFlags & DISPATCH_PROPERTYGET);
			ASSERT(pDispParams->cArgs == 0);
			ASSERT_VALID(pThis);
			
			// set default result to member not found
			HRESULT hr = ResultFromScode (DISP_E_MEMBERNOTFOUND);

			//
			// this test will mature when firing extender events
			//
			if (wFlags == DISPATCH_METHOD)
				return hr;

			T* pT = static_cast<T*>(pThis);
			if (pT->ApcOleItem_OnGetAmbientProp(dispid, pvarResult) == S_OK)
				hr = S_OK;

			return hr;
		}
	END_INTERFACE_PART(AmbientProps)

	/////////////////////////////////////////////////////////////////////////////
	// CApcOleClientItem::XPropertyNotifySink

	APC_BEGIN_INTERFACE_PART(PropertyNotifySink, IPropertyNotifySink)
		INIT_INTERFACE_PART(CApcOleClientItem, PropertyNotifySink)
		APC_STDREFCOUNT(CApcOleClientItem, PropertyNotifySink)
		STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj)
		{
			METHOD_PROLOGUE(CApcOleClientItem, PropertyNotifySink)

			if (IsEqualIID(iid, IID_IUnknown) || 
				IsEqualIID(iid, IID_IPropertyNotifySink))
			{
				*ppvObj = this;
				AddRef();
				return S_OK;
			}
			else
			{
				return E_NOINTERFACE;
			}
		}
		STDMETHOD(OnChanged)(DISPID dispid)
		{
			METHOD_PROLOGUE(CApcOleClientItem, PropertyNotifySink)
			HRESULT hr = pThis->OnChanged(dispid);
			return hr;
		}
		STDMETHOD(OnRequestEdit)(DISPID dispid)
		{
			// Currently we only support Optimistic binding ala VB4
			// In this model, requests always succeed
			METHOD_PROLOGUE(CApcOleClientItem, PropertyNotifySink)
			HRESULT hr = pThis->OnRequestEdit(dispid);
			return hr;
		}
	END_INTERFACE_PART(PropertyNotifySink)

	/////////////////////////////////////////////////////////////////////////////
	// CApcOleClientItem::XEventSink

	APC_BEGIN_INTERFACE_PART(EventSink, IDispatch)
		INIT_INTERFACE_PART(CApcOleClientItem, EventSink)
		APC_STDREFCOUNT(CApcOleClientItem, EventSink)
		STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj)
		{
			METHOD_PROLOGUE(CApcOleClientItem, EventSink)

			if (IsEqualIID(iid, IID_IUnknown) ||
				IsEqualIID(iid, IID_IDispatch) ||
				IsEqualIID(iid, pThis->m_iidEvents))
			{
				*ppvObj = this;
				AddRef();
				return S_OK;
			}
			else
			{
				return E_NOINTERFACE;
			}
		}
		STDMETHOD(GetTypeInfoCount)(unsigned int*)
		{
			APC_STDMETHOD(CApcOleClientItem, EventSink, E_NOTIMPL);
		}
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**)
		{
			APC_STDMETHOD(CApcOleClientItem, EventSink, E_NOTIMPL);
		}
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*)
		{
			APC_STDMETHOD(CApcOleClientItem, EventSink, E_NOTIMPL);
		}
		STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*, VARIANT*, EXCEPINFO*, unsigned int*)
		{
			APC_STDMETHOD(CApcOleClientItem, EventSink, E_NOTIMPL);
		}
	END_INTERFACE_PART(EventSink)

	#ifdef _DEBUG

		virtual void AssertValid() const
		{
			_CApcOleClientItemBaseClass::AssertValid();
		}

		virtual void Dump(CDumpContext& dc) const
		{
			_CApcOleClientItemBaseClass::Dump(dc);
		}

	#endif
};

#endif // APC_NO_OLECLIENTITEM

} // namespace MSAPC

#endif

