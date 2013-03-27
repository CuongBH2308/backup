// DiagnoseDoc.cpp : implementation of the CDiagnoseDoc class
//

#include "stdafx.h"
#include "Diagnose.h"

#include "DiagnoseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseDoc

IMPLEMENT_DYNCREATE(CDiagnoseDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiagnoseDoc, CDocument)
	//{{AFX_MSG_MAP(CDiagnoseDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseDoc construction/destruction

CDiagnoseDoc::CDiagnoseDoc()
{
	// TODO: add one-time construction code here

}

CDiagnoseDoc::~CDiagnoseDoc()
{
}

BOOL CDiagnoseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDiagnoseDoc serialization

void CDiagnoseDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseDoc diagnostics

#ifdef _DEBUG
void CDiagnoseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiagnoseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseDoc commands
