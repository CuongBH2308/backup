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
#include "pt_document.h"

// PT_Document
IMPLEMENT_DYNCREATE(PT_Document, FW_Document)

PT_Document::PT_Document()
{
}

PT_Document::~PT_Document()
{
}

BEGIN_MESSAGE_MAP(PT_Document, FW_Document)
END_MESSAGE_MAP()

// virtual 
BOOL PT_Document::OnNewDocument()
{
	BOOL bOK = FW_Document::OnNewDocument();
	if(bOK)
	{

	}

	return bOK;
}

//virtual
BOOL PT_Document::OnOpenDocument(LPCSTR lpszDoc)
{
	BOOL bOK = FW_Document::OnOpenDocument(lpszDoc);

	return bOK;
}

//virtual 
BOOL PT_Document::OnSaveDocument(LPCSTR lpszDoc)
{
	BOOL bOK = FW_Document::OnSaveDocument(lpszDoc);

	return bOK;
}

// virtual 
void PT_Document::OnCloseDocument()
{
	FW_Document::OnCloseDocument();
}