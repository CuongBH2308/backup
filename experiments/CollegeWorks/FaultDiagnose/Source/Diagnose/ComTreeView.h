#if !defined(AFX_COMTREEVIEW_H__6D97EDF9_266E_4E92_A915_EDA22CBA74C6__INCLUDED_)
#define AFX_COMTREEVIEW_H__6D97EDF9_266E_4E92_A915_EDA22CBA74C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComTreeView view

class CComTreeView : public CTreeView
{
protected:
	CComTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CComTreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComTreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CComTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CComTreeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMTREEVIEW_H__6D97EDF9_266E_4E92_A915_EDA22CBA74C6__INCLUDED_)
