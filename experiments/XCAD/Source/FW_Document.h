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


#pragma once
#include "xcad.h"
#include "afxole.h"

interface IFWDocument;
class DR_Fragment;
class FW_DocumentData;
class FW_Request;
class GR_DLNode;
class XCAD_EXPORT FW_Document : public CApcDocument<FW_Document,COleServerDoc/*COleDocument*/>, public CApcProjectItem<FW_Document>
{
	DECLARE_DYNCREATE(FW_Document)
public:
	FW_Document();
	virtual ~FW_Document();

	// Get m_spIFWDocument;
	CComPtr<IFWDocument> GetInterface();

	// Set m_spIFWDocument to NULL
	void ResetInterface();

	virtual void Serialize(CArchive& ar);
	virtual HRESULT ApcProject_Save();
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCSTR);
	virtual BOOL OnSaveDocument(LPCSTR);
	virtual void OnCloseDocument();
	virtual HRESULT ExecuteRequest(FW_Request* pReq);


	virtual void LoadFromStorage();
	virtual void SaveToStorage(CObject* pObject = NULL);

	// Get m_bActive
	BOOL GetActive() const;

	// Initialize data
	void InitData();

	// Get root node
	GR_DLNode* GetDLNode() const;

	// Get fragment
	DR_Fragment* GetFragment() const;

protected:
	virtual COleServerItem* OnGetEmbeddedItem();

	afx_msg void OnToolsMacroMacros();
	DECLARE_MESSAGE_MAP()
	
private:
	// Interface to access this document
	CComPtr<IFWDocument> m_spIFWDocument;

	// Document data
	FW_DocumentData* m_pDocData;
};