#if !defined(AFX_MODELTREE_H__BD7612F7_6CD3_4563_97D9_4B65B4290F3D__INCLUDED_)
#define AFX_MODELTREE_H__BD7612F7_6CD3_4563_97D9_4B65B4290F3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModelTree view
class Tree
{
public:
	HTREEITEM root;
	HTREEITEM TreeItem[MAXTREE];
	CTypedPtrArray <CPtrArray, Node*> NodeArray;	//结点数组
	Tree(){}
	~Tree(){}
};

class CModelTree : public CTreeView
{
protected:
	CModelTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CModelTree)

// Attributes
public:
	CTreeCtrl * m_TreeView;
	Tree m_Tree;
	CImageList* m_pImageList;

// Operations
public:
	int Get_No_In_TreeItem(HTREEITEM item, int itemcount);
	void ExpandAll(HTREEITEM root_item);
	void AddBitmap(UINT nIDResource);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelTree)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CModelTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CModelTree)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELTREE_H__BD7612F7_6CD3_4563_97D9_4B65B4290F3D__INCLUDED_)
