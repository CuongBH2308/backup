// DiagnoseDoc.h : interface of the CDiagnoseDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGNOSEDOC_H__3D2EF5D5_7B61_4DB2_A0BE_77C3029926B4__INCLUDED_)
#define AFX_DIAGNOSEDOC_H__3D2EF5D5_7B61_4DB2_A0BE_77C3029926B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiagnoseDoc : public CDocument
{
protected: // create from serialization only
	CDiagnoseDoc();
	DECLARE_DYNCREATE(CDiagnoseDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagnoseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiagnoseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiagnoseDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGNOSEDOC_H__3D2EF5D5_7B61_4DB2_A0BE_77C3029926B4__INCLUDED_)
