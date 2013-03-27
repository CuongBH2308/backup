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
/*   sql_server���ݿ������Ϣ*/
#include "modeltree.h"
#include "mainfrm.h"


/*   sql_server���ݿ������Ϣ*/
typedef struct class_sqlserver_db
{
	CString dbsrc;	//SQL SERVER ��������
	CString dbname;	//Ĭ�ϵ����ݿ���
	CString user;	//�û���
	CString pass;	//����
}class_sqlserver_db;

/*   �������ṹ    */
class class_reason_result
{
public:
	
	long exec_rule_id;    //����ID  -1��ʾ��ƥ�����
	CString diagnose_type; //�������
	CString antecedent;  //��������
	long next_node_no;   //���ƽ��  -1��ʾ�޹���,-2��ʾ�й���,������ʾ����ȷ��,��Ҫ����
};

/*����������ݽṹ*/
typedef struct class_reason_step
{
	long task_id;				//�����
	long step_id;				//�������
	long rule_id;				//ƥ��������
	long node_id;				//��Ͻ���
	CString node_name;			//��Ͻ������
	CString comp_name;			//��Ͻ��������������
	CString out_node_name;		//��������
	CString rule_content;		//ƥ���������
}class_reason_step;

/*����ṹ�����������޸�*/
//ǰ�����ʽ�ṹ��ν�ʿ������������߼��������������������ǰ�����!
typedef struct class_pred_expression_element
{
	char type;			//type='p'��ν�ʣ� type='o'���߼������
	void *content;		//�������������������char *��ν����predicate *
}class_pred_expression_element;
typedef struct class_pred_expression
{
	int element_count;
	class_pred_expression_element *element;
}class_pred_expression;
//����ṹ
typedef struct class_rule
{
	long rule_id;						//����id��
	class_pred_expression antecedent;	//ν�ʱ��ʽ��ʽ��ǰ��
	long goto_node_no;					//�����ʾ����ת����
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

	CStringArray ReportOutFields;        //�����������ֶ��б�
	CStringArray reason_data_field_list; //����������ֶ��б�

	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	class_sqlserver_db m_sqlserver_db;
	CString m_cur_model_name;
	CStringArray ModelArray;			//ģ������
	long cur_reason_node_no;
	Node *cur_reason_node;
	long cur_task_id; //��ǰ�����
	
	long reason_step_count;
	class_reason_step reason_step[30000];

	void ShowData();
	void ReasonAll();
	void ReasonOnestep();
	void ContinueReason();
	void ReportOut();

	//����ָ��������ֶ��б����ļ���ʽ��������ر�������
	CString ReportOut_by_File();

	//����ָ��������ֶ��б���XML��ʽ��������ر�������
	CString ReportOut_by_XML();

	//��¼��ǰ�������������
	void SaveCurReasonStep(class_reason_result reason_result, Node *curNode);

	class_reason_result reason_one_node(int node_no);
	Node * Get_Node_In_NodeArray(unsigned long node_no);
	CPoint scrollpos;
	GraphInfo m_GraphInfo;

	CPoint downPoint;							//������ʱ�ĵ�
	CPoint upPoint;								//�ͷ����ʱ�ĵ�
	CPoint movePoint;							//�ƶ����ĵ�
	CPoint lastPoint;							//��һ�εĵ�

	double m_model_scale;						//���ű���

	BOOL add_new_line_flag;						//�Ƿ�Ҫ�������
	BOOL m_group_select;						//�Ƿ��Ѿ�ѡ��һ����

	ModelObject * curObject;								//��ǰ�����еĶ���
	Node * copyedNode;
	Node * sonNode;
	Node * parentNode;
	CTypedPtrArray <CPtrArray, Node*> NodeArray;			//�������
	CTypedPtrArray <CPtrArray, Line*> LineArray;			//��������
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
	float oldPercentage; //����ԭ����.
	int GetPresetZoom();
		
//xnf ��

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

	//��˸ͼ��
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
	int reportResult;// �����������
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELVIEW_H__75FEF2B4_EF29_42AB_B231_E411706706D0__INCLUDED_)
