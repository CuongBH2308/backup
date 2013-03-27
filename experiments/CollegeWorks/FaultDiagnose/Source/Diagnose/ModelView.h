#if !defined(AFX_MODELVIEW_H__75FEF2B4_EF29_42AB_B231_E411706706D0__INCLUDED_)
#define AFX_MODELVIEW_H__75FEF2B4_EF29_42AB_B231_E411706706D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelView.h : header file
//
#define ID_ZOOM_FIRST		ID_ZOOM_01
#define ID_ZOOM_LAST		ID_ZOOM_06

#define MODELVIEW_MAX_Y_RANGE	3000
#define MODELVIEW_MAX_X_RANGE	5000
#define MODELVIEW_Y_LINE	50
#define MODELVIEW_X_LINE	30
#define MODELVIEW_Y_PAGE	500
#define MODELVIEW_X_PAGE	300

#define MODEL_SCALE	1.0


#include "openmodeldlg.h"
#include "glint.h"
#include "modeltree.h"
/////////////////////////////////////////////////////////////////////////////
// CDiagRunView view
//fqz
/*   sql_server数据库访问信息*/
#include "modeltree.h"
#include "mainfrm.h"


/*   sql_server数据库访问信息*/
typedef struct class_sqlserver_db
{
	CString dbsrc;	//SQL SERVER 服务器名
	CString dbname;	//默认的数据库名
	CString user;	//用户名
	CString pass;	//密码
}class_sqlserver_db;

/*   推理结果结构    */
class class_reason_result
{
public:
	
	long exec_rule_id;    //规则ID  -1表示无匹配规则
	CString diagnose_type; //诊断类型
	CString antecedent;  //规则内容
	long next_node_no;   //下推结点  -1表示无故障,-2表示有故障,正数表示不能确定,需要下推
};

/*诊断运行数据结构*/
typedef struct class_reason_step
{
	long task_id;				//任务号
	long step_id;				//步骤序号
	long rule_id;				//匹配规则序号
	long node_id;				//诊断结点号
	CString node_name;			//诊断结点名称
	CString comp_name;			//诊断结点所属部件名称
	CString out_node_name;		//输出结点名
	CString rule_content;		//匹配规则内容
}class_reason_step;

/*规则结构不允许随意修改*/
//前件表达式结构：谓词看作操作数，逻辑运算符看作操作数。将前件拆分!
typedef struct class_pred_expression_element
{
	char type;			//type='p'：谓词； type='o'：逻辑运算符
	void *content;		//运算符：如果是运算符则char *，谓词则predicate *
}class_pred_expression_element;
typedef struct class_pred_expression
{
	int element_count;
	class_pred_expression_element *element;
}class_pred_expression;
//规则结构
typedef struct class_rule
{
	long rule_id;						//规则id号
	class_pred_expression antecedent;	//谓词表达式形式的前件
	long goto_node_no;					//后件标示的跳转结点号
}class_rule;


class CModelView : public CView
{
protected:
	CModelView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CModelView)

// Attributes
	friend COpenModelDlg;
public:
	//fqz

	IReasonCom *pReasonCom;
	CRect CurModelGraphRect;
	
	DWORD dwThreadId;
	HANDLE hThread;

	BOOL import_data_flag;

	BOOL if_connect_model(CString model_name);
	CRect CalModelGraphRect();
	void load_all_nodes_data(CString curdatast);
	void free_dataset(class_dataset dataset);
	static LRESULT reason_one_thread(LPVOID pParam);
	static LRESULT continue_reason_thread(LPVOID pParam);
	CString vartostr(const _variant_t &var);

	CStringArray ReportOutFields;        //输出报表定义的字段列表
	CStringArray reason_data_field_list; //推理的所有字段列表

	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	class_sqlserver_db m_sqlserver_db;
	CString m_cur_model_name;
	CStringArray ModelArray;			//模型数组
	long cur_reason_node_no;
	Node *cur_reason_node;
	long cur_task_id; //当前任务号
	
	long reason_step_count;
	class_reason_step reason_step[30000];

	void ShowData();
	void ReasonAll();
	void ReasonOnestep();
	void ContinueReason();
	void ReportOut();

	//根据指定输出的字段列表，以文件方式输出，返回报表内容
	CString ReportOut_by_File();

	//根据指定输出的字段列表，以XML方式输出，返回报表内容
	CString ReportOut_by_XML();

	//记录当前步骤的推理内容
	void SaveCurReasonStep(class_reason_result reason_result, Node *curNode);

	class_reason_result reason_one_node(int node_no);
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
	BOOL read_model_array();
	void CreateTree_OnOpen(Node *node, HTREEITEM parent_item, CModelTree *pTreeView, CTreeCtrl& m_ctlTree);
	int if_exist_model(CString model_name);
	BOOL exec_sql(char *sql_cmd);
	BOOL read_one_model(CString model_name);
	BOOL save_reason_steps_to_DB();
	void StopCurGlint();  //fqz

// Operations
public:
	void SetGlint(Node *pNode);
	static void DrawR(CDC &memDC, PRNINFO PrnInfo);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CModelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CModelView)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCancelMode();
	afx_msg void OnSelectmodel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDataSave();
	afx_msg void OnUpdateDataSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateReportdefine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateReportout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnOnestep();
	afx_msg void OnContinue();
	afx_msg void OnLine();
	afx_msg void OnUpdateOnestep(CCmdUI* pCmdUI);
	afx_msg void OnUpdateContinue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnAutoget();
	afx_msg void OnManget();
	afx_msg void OnUpdateAutoget(CCmdUI* pCmdUI);
	afx_msg void OnUpdateManget(CCmdUI* pCmdUI);
	afx_msg void OnReportdefine();
	afx_msg void OnReportout();
	afx_msg void OnUpdateSelectmodel(CCmdUI* pCmdUI);
	afx_msg void OnZoomZoomin();
	afx_msg void OnZoomZoomout();
	afx_msg void OnFullGraph();
	afx_msg void OnUpdateZoomZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomZoomout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFullGraph(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomOther(CCmdUI* pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPrintresult();
	afx_msg void OnUpdatePrintresult(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint1();
	afx_msg void OnFilePrintPreview1();
	//}}AFX_MSG
	afx_msg void OnZoom(UINT nID);
	afx_msg void OnUpdateZoom(CCmdUI *pCmdUI);
	afx_msg void OnZoomOther();
	DECLARE_MESSAGE_MAP()

//xnf zoom
	float oldPercentage; //保留原比例.
	int GetPresetZoom();
		
//xnf 闪

private:
	BOOL m_glint;
	Node *m_pNode;
	CGlint m_cGlint;
public:
	void EndNodeg(Node *p);
	void SetNodeRect(CDC *pDC, CRect rect, BOOL bFlag);
	CString GetMyDirectory();
	void SetBmpGlint(CDC *pDC);
	void SetBmpIndx(int index){ bmpIndex=index;}
	void ShowBim(CDC *pDC,CPoint & point, float fscale=1);
	void BeginGlint() { m_glint=TRUE;m_glintActive=TRUE;}
	void EndGlint(); 

	//闪烁图像
	BOOL m_bmpGlint;
	BOOL m_bmpChange;
	BOOL m_glintActive;
	int  bmpIndex;
	void bmpBeginGlint(){ m_bmpGlint=TRUE;m_bmpChange=TRUE;}
	void bmpEndGlint() { m_bmpGlint=FALSE; m_bmpChange=FALSE;CClientDC dc(this); SetBmpGlint(&dc);Invalidate();}
//xnf print work;
	//zoom in and out variables
//	float oldPercentage;
	int numberOfPages;
	int numCol;
	int oldMap;
	int numRow;
	double ratio_x,	ratio_y;
	int reportResult;// 报告结果输出。
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELVIEW_H__75FEF2B4_EF29_42AB_B231_E411706706D0__INCLUDED_)
