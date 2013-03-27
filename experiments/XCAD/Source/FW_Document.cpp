/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "fw_document.h"
#include "fw_documentdata.h"
#include "fw_cmd.h"
#include "fw_cmds.h"
#include "fw_cmdmanager.h"
#include "fw_mdiframewnd.h"
#include "fw_oleserveritem.h"
#include "fw_request.h"
#include "fw_winapp.h"
#include "sl_mm.h"
#include "SL_Storage.h"
// FW_Document
IMPLEMENT_DYNCREATE(FW_Document, CDocument)

FW_Document::FW_Document()
:m_spIFWDocument(NULL),
m_pDocData(NULL)
{
	ApcEnableAutoCreate(TRUE);
	ApcEnableAutoLoad(TRUE);
	EnableCompoundFile();

	GetInterface();
}

FW_Document::~FW_Document()
{
	if(m_spIFWDocument)
		m_spIFWDocument = NULL;

	if(m_pDocData)
		DEL_OBJ(m_pDocData);
}

BEGIN_MESSAGE_MAP(FW_Document, CDocument)
	//{{AFX_MSG_MAP(FW_Document)
	ON_COMMAND(ID_TOOLS_MACRO_MACROS, OnToolsMacroMacros)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// virtual
COleServerItem* FW_Document::OnGetEmbeddedItem()
{
	FW_OleServerItem* pItem = new FW_OleServerItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

// Get m_spFWDocument;
CComPtr<IFWDocument> FW_Document::GetInterface()
{
	if(!m_spIFWDocument)
	{
		HRESULT hr = m_spIFWDocument.CoCreateInstance(CLSID_FWDocument,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
		if(SUCCEEDED(hr))
			m_spIFWDocument->SetPrimary((unsigned char*)this);
	}

	return m_spIFWDocument;
}

// Set m_spIFWDocument to NULL
void FW_Document::ResetInterface()
{
	if(m_spIFWDocument)
		m_spIFWDocument.p = NULL;
}

// Whether this document is active
BOOL FW_Document::GetActive() const
{
	if(FW_MDIFrameWnd::GetActiveDoc() == this)
		return TRUE;

	return FALSE;
}

// Initialize data
void FW_Document::InitData()
{
	if(!m_pDocData)
	{
		m_pDocData = NEW_OBJ2(FW_DocumentData)(this);
		m_pDocData->Init();
	}
}

// Get root node
GR_DLNode* FW_Document::GetDLNode() const
{
	ASSERT(m_pDocData);
	return m_pDocData->GetDLNode();
}

// Get fragment
DR_Fragment* FW_Document::GetFragment() const
{
	ASSERT(m_pDocData);
	return m_pDocData->GetFragment();
}

void FW_Document::Serialize(CArchive& ar)
{
	//	((CView*)m_viewList.GetHead())->SerializeRaw(ar);
}

HRESULT FW_Document::ApcProject_Save()
{
	OnFileSave();
	return NOERROR;
}

BOOL FW_Document::OnNewDocument() 
{
	// After this step, ApcProject should be created
	if(!CApcDocument<FW_Document, COleServerDoc/*COleDocument*/>::OnNewDocument())
		return FALSE;

	if (!ApcProject) 
		return FALSE;

	HRESULT hr = ApcProject->put_DisplayName(CComBSTR(GetTitle()));
	if(FAILED(hr))
		return FALSE;

	//// Initial document data
	InitData();
	
	// Set modified
	SetModifiedFlag(FALSE);

	// Update views
	UpdateAllViews(NULL);

	return TRUE;
}

BOOL FW_Document::OnOpenDocument(LPCSTR lpszDoc)
{
	if(!CApcDocument<FW_Document, COleServerDoc/*COleDocument*/>::OnOpenDocument(lpszDoc))
		return FALSE;

	if (!ApcProject) 
		return FALSE;

	ApcProject->put_DisplayName(CComBSTR(lpszDoc));

	return TRUE;


}


void FW_Document::LoadFromStorage()
{
	CApcDocument<FW_Document, COleServerDoc/*COleDocument*/>::LoadFromStorage();
}

void FW_Document::SaveToStorage(CObject* pObject/* = NULL*/)
{

	m_pDocData->GetStorage()->Save();

	HRESULT hr = m_pDocData->GetStorage()->GetPtr()->CopyTo(0, NULL, NULL, m_lpRootStg);
	ASSERT(SUCCEEDED(hr));

	CApcDocument<FW_Document, COleServerDoc/*COleDocument*/>::SaveToStorage(pObject);
}


BOOL FW_Document::OnSaveDocument(LPCSTR lpszDoc)
{
	if (!CApcDocument<FW_Document, COleServerDoc/*COleDocument*/>::OnSaveDocument(lpszDoc))
		return FALSE;

	if (!ApcProject)
		return FALSE;

	ApcProject->put_DisplayName(CComBSTR(lpszDoc));

	return TRUE;
}

void FW_Document::OnCloseDocument()
{
	FW_WinApp* pApp = FW_WinApp::GetWinApp();

	if (ApcProject && !pApp->GetCloseFrame()) 
	{
		// Only this document will be closed.
		VARIANT_BOOL bLocked=VARIANT_FALSE;
		ApcProject->get_Locked(&bLocked);
		if (bLocked==VARIANT_TRUE) 
			return;
	}

	FW_Cmd* pCmd = pApp->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnTerminate();

	//pApp->RemoveFromCollection(this);
	CApcDocument<FW_Document, COleServerDoc/*COleDocument*/>::OnCloseDocument();
}

void FW_Document::OnToolsMacroMacros() 
{
	FW_WinApp *pApp = FW_WinApp::GetWinApp();
	CComPtr<IApc> pApc;
	CComPtr<IApcScopes> pScopes;
	CComPtr<IApcMacrosDialog> pMacrosDialog;

	// Make sure the ApcHost is existing
	if (!pApp->ApcHost) 
		return;

	pApc = pApp->ApcHost.GetApcHost();
	if (!pApc)
		return;

	// To show macros dialog, we must create a scopes collection.
	// You can create a scopes project off of the Apc host or off of a project.
	pApc->APC_RAW(CreateScopes)(VARIANT_TRUE, &pScopes);
	if (pScopes == NULL)
		return;

	// Get macros dialog object from scopes collection and set its properties
	pScopes->APC_GET(MacrosDialog)(&pMacrosDialog);
	if (pMacrosDialog == NULL)
		return;

	CString strTitle;
	strTitle.LoadString(IDS_MACROSDLG_TITLE);
	pMacrosDialog->APC_PUT(DialogTitle)(strTitle.AllocSysString());
	pMacrosDialog->APC_PUT(StartUpPosition)(axPositionCenterOwner);
	pMacrosDialog->APC_RAW(Show)();	
}

// virtual 
HRESULT FW_Document::ExecuteRequest(FW_Request* pReq)
{
	return pReq->Execute();
}

