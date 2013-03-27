#if !defined(AFX_DIAGRUNVIEW_H__D53C2187_792C_4C17_9FDD_9369EDCC9F18__INCLUDED_)
#define AFX_DIAGRUNVIEW_H__D53C2187_792C_4C17_9FDD_9369EDCC9F18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiagRunView.h : header file
//
#define MODELVIEW_MAX_Y_RANGE	1000
#define MODELVIEW_MAX_X_RANGE	1000
#define MODELVIEW_Y_LINE	50
#define MODELVIEW_X_LINE	30
#define MODELVIEW_Y_PAGE	500
#define MODELVIEW_X_PAGE	300

/////////////////////////////////////////////////////////////////////////////
// CDiagRunView view
//fqz
/*   sql_server数据库访问信息*/
#include "modeltree.h"
#include "mainfrm.h"

typedef struct class_sqlserver_db
{
	CString dbsrc;	//SQL SERVER 服务器名
	CString dbname;	//默认的数据库名
	CString user;	//用户名
	CString pass;	//密码
}class_sqlserver_db;

class CDiagRunView : public CScrollView
{
protected:
	CDiagRunView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDiagRunView)

// Attributes
public:
	//fqz
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	class_sqlserver_db m_sqlserver_db;
	CString m_cur_model_name;
	CStringArray ModelArray;			//模型数组

	Node * Get_Node_In_NodeArray(unsigned long node_no);
	CPoint scrollpos;
	GraphInfo m_GraphInfo;

	CPoint downPoint;							//鼠标点下时的点
	CPoint upPoint;								//释放鼠标时的点
	CPoint movePoint;							//移动鼠标的点
	CPoint lastPoint;							//上一次的点

	double m_model_scale;						//缩放比例

	BOOL add_new_line_flag;						//是否要添加连线
	BOOL m_group_select;						//是否已经选中一组结点

	ModelObject * curObject;								//当前鼠标点中的对象
	Node * copyedNode;
	Node * sonNode;
	Node * parentNode;
	CTypedPtrArray <CPtrArray, Node*> NodeArray;			//结点数组
	CTypedPtrArray <CPtrArray, Line*> LineArray;			//连线数组
	CTypedPtrArray <CPtrArray, ModelObject*> SelectedObjects;


// Operations
public:
	void CreateGraph(CString NodeName);
	//fqz function
	void clear_nodearray_linearray();
	void read_model_array();
	void write_model_array();
	void CreateTree_OnOpen(Node *node, HTREEITEM parent_item, CModelTree *pTreeView, CTreeCtrl& m_ctlTree);
	int if_exist_model(CString model_name);
	BOOL exec_sql(char *sql_cmd);
	BOOL read_one_model(CString model_name);
	BOOL save_one_model(CString model_name);
	BOOL create_one_model(CString model_name);
	BOOL delete_one_model(CString model_name);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagRunView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDiagRunView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDiagRunView)
	afx_msg void OnSelectmodel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGRUNVIEW_H__D53C2187_792C_4C17_9FDD_9369EDCC9F18__INCLUDED_)
