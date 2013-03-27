// ModelView.cpp : implementation file
//
#include "stdafx.h"


#include "Diagnose.h"
#include "ModelView.h"
#include "macro.h"
#include "DiagnoseDoc.h"
#include "DiagnoseView.h"
#include "TipView.h"
#include "OpenModelDlg.h"
#include "reportshowdlg.h"
#include "reportdefdlg.h"
#include "SelectDataDlg.h"
#include "glint.h"
#include "ZoomLevelDlg.h"

#include "diagnoseclass\\MainDeduce.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMalfuncDeduce&  Deduce()
{
	static CMalfuncDeduce deduce;
	return deduce;
}


int bmpx,bmpy;

/////////////////////////////////////////////////////////////////////////////
// CModelView

IMPLEMENT_DYNCREATE(CModelView, CView)
extern IBaseCom * current_active_com;
extern CModelTree * pModelView;
unsigned long node_id_count = 0;
unsigned long line_id_count = 0;
extern BOOL mousemoving;							//����Ƿ����ƶ�������
extern BOOL mousedown;								//����Ƿ���£�������δ�ͷ�

CMyBmp * pBmp = NULL;
CString BmpPath="";
double xScale = 0.0,
	   yScale = 0.0;

//10.20���
int com_count=9;
const CLSID * CLSIDArray[] = {	&CLSID_MyCom1, &CLSID_MyCom2, &CLSID_MyCom3, &CLSID_MyCom4,
								&CLSID_MyCom5, &CLSID_MyCom6, &CLSID_MyCom11, &CLSID_MyCom12, &CLSID_MyLineCom};
const IID * IIDArray[] = {	&IID_IMyCom1, &IID_IMyCom2, &IID_IMyCom3, &IID_IMyCom4,
							&IID_IMyCom5, &IID_IMyCom6,	&IID_IMyCom11, &IID_IMyCom12, &IID_IMyLineCom};

float m_DefaultPresets[6]={0.35F, 0.5F, 0.7F, 1.0F,1.4F, 2.4F};

//view�ṹ
typedef struct class_view_pointer
{
	CModelView *pModel;
	CDiagnoseView *pDiagnose;
	CModelTree *pTreeView;
	CTipView *pTip;
}class_view_pointer;

class_view_pointer view_pointer;

BOOL finish_add_line = FALSE;
extern MouseAction actionflag;

//fqz
void degrade_to_subtree(Node *pNode, int layer);
void MoveItemToLast(HTREEITEM m_startItem, HTREEITEM pItem);
HTREEITEM NodetoItem(Node *pNode);

static int fullgraph_times=0;

CString DiagnoseResult="";

int Get_Com_ID(Node *node)
{
	CLSID clsid;
	node->GetCom()->GetCLSID((unsigned long)&clsid);
	for (int i=0;i<com_count;i++)
		if (*CLSIDArray[i]==clsid)
			return i;
	return -1;
}

//�õ�ĳ������image��
int get_image_no_of_node(Node *node)
{
	int n=Get_Com_ID(node);
	return 2*(n+1);
}

CModelView::CModelView():downPoint(0,0), upPoint(0,0), movePoint(0,0), lastPoint(0,0)
{
	add_new_line_flag = FALSE;
	m_group_select = FALSE;
	curObject = NULL;
	copyedNode = NULL;
	scrollpos.x = 0;
	scrollpos.y = 0;
	sonNode = parentNode = NULL;
	m_model_scale = 1.0;
	m_GraphInfo.InitGraphInfo();
	//xnf
		oldPercentage=1.0;
	//fqz

	hThread=NULL;
	reason_step_count=0;

	reason_data_field_list.Add("�����");
	reason_data_field_list.Add("�����");
	reason_data_field_list.Add("����");
	reason_data_field_list.Add("�����");
	reason_data_field_list.Add("��������");
	reason_data_field_list.Add("������");

	ReportOutFields.Add("�����");
	ReportOutFields.Add("�����");
	//ReportOutFields.Add("����");
	ReportOutFields.Add("�������");
	ReportOutFields.Add("��������");
	ReportOutFields.Add("�����");
	ReportOutFields.Add("������");

	m_cur_model_name="";
	cur_reason_node_no=0;
	import_data_flag=FALSE;

	HRESULT hr;
	hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����

	//�������ļ�
	CString strFile="user_info.txt";
	CStdioFile file;
	CFileException e;
	CString str;
	int length;
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone,&e);
	while(file.ReadString(str)!=NULL)
	{
		length=str.GetLength();
		if (str.Find("����Դ=")==0)
		{
			m_sqlserver_db.dbsrc=str.Right(length-strlen("����Դ="));
			m_sqlserver_db.dbsrc.TrimLeft();
			m_sqlserver_db.dbsrc.TrimRight();
		}
		else if (str.Find("�û���=")==0)
		{
			m_sqlserver_db.user=str.Right(length-strlen("�û���="));
			m_sqlserver_db.user.TrimLeft();
			m_sqlserver_db.user.TrimRight();
		}
		else if (str.Find("����=")==0)
		{
			m_sqlserver_db.pass=str.Right(length-strlen("����="));
			m_sqlserver_db.pass.TrimLeft();
			m_sqlserver_db.pass.TrimRight();
		}
		else if (str.Find("�����=")==0)   //���õ�ǰ�����
		{
			cur_task_id=atol(str.Right(length-strlen("�����=")));
		}
	}
	file.Close();

	//��֤�û����������Ƿ���ȷ
	try
	{
		CString Datasource;
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=\"\"; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
		hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
		m_pConnection->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		MessageBox("�޷�����sqlserver���ݿ⣬��������û��������������Դ�Ƿ���ȷ","����");///��ʾ������Ϣ
		exit(0);
	}

	if (read_model_array()==FALSE)
	{
		exit(0);
	}
	
//xnf 
	m_bmpGlint=FALSE;
	m_glint=FALSE;
	bmpIndex=1;
	m_glintActive=FALSE;

	hr = ::CoCreateInstance(CLSID_ReasonCom, NULL, CLSCTX_ALL, IID_IReasonCom, (void **)&pReasonCom);
	if ( !SUCCEEDED(hr) )
	{
		MessageBox("����COM����");
		exit (1);
	}

}

CModelView::~CModelView()
{
	if(m_pConnection->State)
		 m_pConnection->Close(); ///����Ѿ�����������ر���
	m_pConnection.Release();
	
	pReasonCom->Release();

	Node * node = NULL;
	Line * line = NULL;
	
	unsigned long count = NodeArray.GetSize();
	unsigned long i;
	for (i=0; i<count; i++ )
	{
		node = NodeArray.GetAt(i);
		delete node;
	}
	NodeArray.RemoveAll();

	count = LineArray.GetSize();
	for (i=0; i<count; i++ )
	{
		line = LineArray.GetAt(i);
		delete line;
	}
	LineArray.RemoveAll();
}


BEGIN_MESSAGE_MAP(CModelView, CView)
	//{{AFX_MSG_MAP(CModelView)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_VSCROLL()
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_SELECTMODEL, OnSelectmodel)
	ON_WM_TIMER()
	ON_COMMAND(ID_DATA_SAVE, OnDataSave)
	ON_UPDATE_COMMAND_UI(ID_DATA_SAVE, OnUpdateDataSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW1, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_REPORTDEFINE, OnUpdateReportdefine)
	ON_UPDATE_COMMAND_UI(ID_REPORTOUT, OnUpdateReportout)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT1, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_ONESTEP, OnOnestep)
	ON_COMMAND(ID_CONTINUE, OnContinue)
	ON_COMMAND(ID_LINE, OnLine)
	ON_UPDATE_COMMAND_UI(ID_ONESTEP, OnUpdateOnestep)
	ON_UPDATE_COMMAND_UI(ID_CONTINUE, OnUpdateContinue)
	ON_UPDATE_COMMAND_UI(ID_LINE, OnUpdateLine)
	ON_COMMAND(ID_AUTOGET, OnAutoget)
	ON_COMMAND(ID_MANGET, OnManget)
	ON_UPDATE_COMMAND_UI(ID_AUTOGET, OnUpdateAutoget)
	ON_UPDATE_COMMAND_UI(ID_MANGET, OnUpdateManget)
	ON_COMMAND(ID_REPORTDEFINE, OnReportdefine)
	ON_COMMAND(ID_REPORTOUT, OnReportout)
	ON_UPDATE_COMMAND_UI(ID_SELECTMODEL, OnUpdateSelectmodel)
	ON_COMMAND(ID_ZOOM_ZOOMIN, OnZoomZoomin)
	ON_COMMAND(ID_ZOOM_ZOOMOUT, OnZoomZoomout)
	ON_COMMAND(ID_FULL_GRAPH, OnFullGraph)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_ZOOMIN, OnUpdateZoomZoomin)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_ZOOMOUT, OnUpdateZoomZoomout)
	ON_UPDATE_COMMAND_UI(ID_FULL_GRAPH, OnUpdateFullGraph)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OTHER, OnUpdateZoomOther)
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_PRINTRESULT, OnPrintresult)
	ON_UPDATE_COMMAND_UI(ID_PRINTRESULT, OnUpdatePrintresult)
	ON_COMMAND(ID_FILE_PRINT1, OnFilePrint1)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW1, OnFilePrintPreview1)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_ZOOM_FIRST, ID_ZOOM_LAST, OnZoom)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ZOOM_FIRST, ID_ZOOM_LAST, OnUpdateZoom)
	ON_COMMAND(ID_ZOOM_OTHER, OnZoomOther)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelView drawing

void CModelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	int count = NodeArray.GetSize();
	int i = 0;
	Node * node = NULL;
	Line * line = NULL;
	BOOL isActive = FALSE;
	for (i=0; i<count; i++)
	{
		node = NodeArray.GetAt(i);
		if ( node->IsDeleted() )
			continue;
		isActive = node->GetActive();
		node->DrawOffset(pDC, 0, scrollpos, m_model_scale, 0, 1, isActive);
	}
	count = LineArray.GetSize();
	for (i=0; i<count; i++)
	{
		line = LineArray.GetAt(i);
		if ( line->IsDeleted() )
			continue;
		isActive = line->GetActive();
		line->DrawOffset(pDC, 0, scrollpos, m_model_scale, 0, 1, isActive);
	}
//xnf ����ģ��ͼ
//POINT point_bmps[11]={(25,69),(25,11),(42,51),(42,0),(112,18),(195,49),
//	(195,15),(304,51),(304,15),(396,51),(396,15)};

	if (!pDC->IsPrinting())
	{
		if(m_cur_model_name!="")
		{
			SetBmpGlint(pDC);
 		}
	}

	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CModelView diagnostics

#ifdef _DEBUG
void CModelView::AssertValid() const
{
	CView::AssertValid();
}

void CModelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModelView message handlers
/*   The following codes were from sijinxin and used to move tree!!!   */
//�ж�parent��son֮���Ƿ������ѭ��
bool IsCircle(Node * parent, Node * son)
{
	Node * node;
	if ( parent->inLine != NULL )
		node = parent->inLine->parentNode;
	else
		return FALSE;

	while ( node != NULL )
	{
		if ( node == son )
			return TRUE;
		else
			if ( node->inLine != NULL )
				node = node->inLine->parentNode;
			else
				return FALSE;
	}

	return FALSE;
}

BOOL FindNextNode(HTREEITEM Item, HTREEITEM& NextItem)
{
	HTREEITEM tempItem;
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctltree = pTreeView->GetTreeCtrl();
	
	if(m_ctltree.ItemHasChildren(Item)==TRUE)//�к���
	{
		NextItem=m_ctltree.GetChildItem(Item);
		return TRUE;
	}
	else
	{
		NextItem=m_ctltree.GetNextSiblingItem(Item);
		if(NextItem!=NULL)//�޺��ӣ����ֵ�
			return TRUE;
		else//�޺��ӣ����ֵ�
		{
			do
			{
				Item=m_ctltree.GetParentItem(Item);
				if(Item==m_ctltree.GetRootItem())
				{
					return FALSE;
				}
				
				tempItem=m_ctltree.GetNextSiblingItem(Item);
				if(tempItem!=NULL)//�и��׵��ֵ�
				{NextItem=tempItem;
				return TRUE;}
			}
			while(tempItem==NULL);//���û�и��׵��ֵܣ�����ѭ��
		}
	}
	return FALSE;
}

//Ҫ��startItem��Item��ֱ�ӻ��߼�ӵĸ��ӹ�ϵ
int GetOffSet(HTREEITEM startItem, HTREEITEM Item)
{
	//0��ʾstartItem��Item��ֱϵ����
	//>0Ϊ��Ӹ���
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	if(Item==m_ctlTree.GetRootItem())
		return -1;
	int i=-1;
	do
	{
		Item=m_ctlTree.GetParentItem(Item);
		i++;
		if(Item==startItem)
			return i;
	}while(Item!=m_ctlTree.GetRootItem());
	return -1;
}

//ע�⣺Ҫ��startItem��Item��ֱ�ӻ��߼�ӵĸ��ӹ�ϵ
//����ΪstartItem��Item��֮�����
int GetOffSetLength(HTREEITEM startItem, HTREEITEM Item)
{
	//ʹ��ǰ�᣺GetOffSet(HTREEITEM startItem, HTREEITEM Item)>=0
	//����ֵn��ʾItemΪstartItem��n������һ���ڵ㣩
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctltree = pTreeView->GetTreeCtrl();
	int i=0;
	do
	{
		i++;
		FindNextNode(startItem,startItem);
		if(Item==startItem)
			return i;
	}while(startItem!=NULL);
	return -1;
}

int Get_No_In_TreeItem(HTREEITEM item, CModelTree *pTreeView)
{
	int i;
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	int itemcount=m_ctlTree.GetCount()-1;
	for (i=0; i<itemcount;i++)
		if (pTreeView->m_Tree.TreeItem[i]==item)
			return i;
	return -1;
}

//��һ���и��ӹ�ϵ��Tree��������
void MoveItem(HTREEITEM m_startItem, HTREEITEM pItem, HTREEITEM nItem)
{
	//���˾����okee�����е�Ctestview��
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	HTREEITEM Item,nextItem,m_tempParentItem,lItem,m_temppItem;
	int no;

	no=Get_No_In_TreeItem(m_startItem,pTreeView);
	int imageno1,imageno2;
	m_ctlTree.GetItemImage(m_startItem,imageno1,imageno2);
	Item=m_ctlTree.InsertItem(m_ctlTree.GetItemText(m_startItem),imageno1,imageno2,pItem,nItem);
	//fqz: �޸�treeitem
	pTreeView->m_Tree.TreeItem[no]=Item;
	lItem=m_startItem;//m_startItemֵ������ѭ���в���
	nItem=Item;
	pItem=Item;
	m_temppItem=pItem;//m_temppItemֵ����
	while(FindNextNode(lItem,nextItem)!=FALSE)//������һ��Node
	{
		//���nextItem�ĸ��׻��߸��׵ĸ�����m_startItem;
		BOOL isParent=FALSE;
		m_tempParentItem=nextItem;
		//�õ���nextItem�ĸ�����m_startItemλ��
		int indent=GetOffSet(m_startItem,nextItem);
		pItem=m_startItem;
		if(indent>0)//������ڼ�Ӹ��ӹ�ϵ
		{
			pItem=m_temppItem;
			for(int i=1;i<=GetOffSetLength(m_startItem,m_ctlTree.GetParentItem(nextItem));i++)
				FindNextNode(pItem,pItem);
		}
		else if(indent==0)//���m_startItem��nextItem����ֱ�Ӹ��ӹ�ϵ
		{
			pItem=m_temppItem;
		}
		else if(indent==-1)
			break;
		no=Get_No_In_TreeItem(nextItem,pTreeView);
		int imageno1,imageno2;
		m_ctlTree.GetItemImage(nextItem,imageno1,imageno2);
		nItem=m_ctlTree.InsertItem(m_ctlTree.GetItemText(nextItem),imageno1,imageno2,pItem,nItem);
		//fqz: �޸�treeitem
		pTreeView->m_Tree.TreeItem[no]=nItem;
		lItem=nextItem;
	}
	m_ctlTree.DeleteItem(m_startItem);
}


/*            The following codes were added by fqz!!!        */

//���ԣ���ʾ�����Ĳ��
void display_all_nodes_layer()
{
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	int nodecount=pTreeView->m_Tree.NodeArray.GetSize();
	CString str="";
	for (int i=0; i<nodecount; i++)
	{
		Node *pNode=pTreeView->m_Tree.NodeArray.GetAt(i);
		CString name=pNode->GetName();
		CString s;
		s.Format("%s: %d  ",name,pNode->layer);
		str=str+s;
	}
}

int Get_No_In_TreeNodeArray(Node *pNode, CModelTree *pTreeView)
{
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	int nodecount=pTreeView->m_Tree.NodeArray.GetSize();
	for (int i=0; i<nodecount; i++)
	{
		if (pTreeView->m_Tree.NodeArray.GetAt(i)==pNode)
			return i;
	}
	return -1;
}

//���ݽ��Ų���node
Node * CModelView::Get_Node_In_NodeArray(unsigned long node_no)
{
	int nodecount=NodeArray.GetSize();
	for (int i=0; i<nodecount; i++)
	{
		Node *p;
		p=NodeArray.GetAt(i);
		if (p->GetID()==node_no)
			return p;
	}
	return NULL;
}

//���ݽ��ָ�������������treeview�ж�Ӧ��item
HTREEITEM NodetoItem(Node *pNode)
{
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	int k=Get_No_In_TreeNodeArray(pNode, pTreeView);

	if (k!=-1)
		return pTreeView->m_Tree.TreeItem[k];
	else
		return NULL;
}

//��һ���и��ӹ�ϵ��Tree�ƶ����¸��׽���ĩβ
void MoveItemToLast(HTREEITEM m_startItem, HTREEITEM pItem)
{
	HTREEITEM tempItem,nItem;
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();

	nItem=m_ctlTree.GetChildItem(pItem);//�õ���һ���ӽڵ�
	tempItem=nItem;
	while(nItem!=NULL)//��������ӽڵ�
	{
		nItem=tempItem;
		tempItem=m_ctlTree.GetNextSiblingItem(nItem);//�õ���һ���ֵܽڵ�
	}
	MoveItem(m_startItem, pItem, nItem);
}

//��ԭ���Ϊlayer��pNodeΪ�׵�������Ϊһ����
void upgrade_to_tree(Node *pNode, int layer)
{
	pNode->layer=pNode->layer - layer;
	int count = pNode->outLine.GetSize();
	for (int i=0; i<count; i++)
	{
		Line *pLine=pNode->outLine.GetAt(i);
		if (!pLine->IsDeleted())
			upgrade_to_tree(pLine->sonNode, layer);
	}
}

//��pNodeΪ�׵�����Ϊһ���������������layer
void degrade_to_subtree(Node *pNode, int layer)
{
	pNode->layer=pNode->layer + layer;
	int count=pNode->outLine.GetSize();
	for (int i=0; i<count; i++)
	{
		Line *pLine= pNode->outLine.GetAt(i);
		if (!pLine->IsDeleted())
			degrade_to_subtree(pLine->sonNode, layer);
	}
}

void CModelView::clear_nodearray_linearray()
{
	unsigned long count = NodeArray.GetSize();
	unsigned long i;
	for (i=0; i<count; i++ )
	{
		Node *node = NodeArray.GetAt(i);
		free_dataset(node->NodeData);
		delete node;
	}
	NodeArray.RemoveAll();

	count = LineArray.GetSize();
	for (i=0; i<count; i++ )
	{
		Line *line = LineArray.GetAt(i);
		delete line;
	}
	LineArray.RemoveAll();
}

BOOL CModelView::if_connect_model(CString model_name)
{
	_ConnectionPtr m_pConnection0;
	CString Datasource;
	BOOL flag=true;
	m_pConnection0.CreateInstance("ADODB.Connection");///����Connection����
	try
	{
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,model_name,m_sqlserver_db.user,m_sqlserver_db.pass);
		m_pConnection0->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
	}
	catch(_com_error e)///��׽�쳣
	{
		flag=false;
	}
	m_pConnection0.Release();
	return flag;
}

BOOL CModelView::read_model_array()
{
	// TODO: Add your command handler code here

	char sql_cmd[1000];
	CString Datasource;
	HRESULT hr;
	char *modellist_name="ModelList";

	//����ģ���б����ݿ�
	if (!if_connect_model(modellist_name))
	{
		//û��ģ���б����ݿ⣬˵����ǰû���κ�ģ��
		try
		{
			//����ģ���б����ݿ�
			Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=\"\"; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
			hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
			strcpy(sql_cmd,"create database ");
			strcat(sql_cmd,modellist_name);
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(sql_cmd, _variant_t((IDispatch*)m_pConnection, true),adOpenDynamic,adLockOptimistic,adCmdText);
			m_pRecordset.Release();
			m_pConnection->Close();
	
			//����ģ���б����ݿ�
			Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,modellist_name,m_sqlserver_db.user,m_sqlserver_db.pass);
			hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
	
			//������
			strcpy(sql_cmd,"create table MODELLIST_Table(ģ���� varchar(30))");
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(sql_cmd, _variant_t((IDispatch*)m_pConnection, true),adOpenDynamic,adLockOptimistic,adCmdText);
			m_pRecordset.Release();

			m_pConnection->Close();
		}
		catch(_com_error e)///��׽�쳣
		{
			if (m_pRecordset!=NULL)
				m_pRecordset.Release();
			if(m_pConnection->State)
				m_pConnection->Close();
			MessageBox("����ModelList���ݿ�ʧ�ܣ��ÿ��Ѵ��ڻ��û��޴���Ȩ��!","����");///��ʾ������Ϣ
			return false;
		}
	}
	else
	{
		//��ȡģ���б�
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,modellist_name,m_sqlserver_db.user,m_sqlserver_db.pass);
		m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("MODELLIST_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdTable);
		while(!m_pRecordset->EndOfFile)
		{
			ModelArray.Add(vartostr(m_pRecordset->GetCollect("ģ����")));
			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
		m_pConnection->Close();
	}
	
	return true;
}


/*----------------------ADO��ȡ���͵�ת��----------------------*/
CString CModelView::vartostr(const _variant_t &var)
{
	CString strValue;
	
	switch (var.vt)
	{
	case VT_BSTR://�ַ���
	case VT_LPSTR://�ַ���
	case VT_LPWSTR://�ַ���
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://������
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://�޷��Ŷ�����
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://����
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //����
		strValue.Format("%d", var.lVal);
		break;
	case VT_I8: //������
		strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://�޷�������
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //�޷�������
		strValue.Format("%d", var.ulVal);
		break;
	case VT_UI8: //�޷��ų�����
		strValue.Format("%d", var.ulVal);
		break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://������
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://˫������
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //С��
		strValue.Format("%.8f", (double)var);
		break;
	case VT_CY:
		{
			COleCurrency cy = var.cyVal;
			strValue = cy.Format();
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
	case 0x2011:
		strValue = "[BLOB]";
		break;
	case VT_BOOL://������

		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //������
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULLֵ
		strValue = "";
		break;
	case VT_EMPTY://��
		strValue = "";
		break;
	case VT_UNKNOWN://δ֪����
	default:
		strValue = "UN_KNOW";
		break;
	}
	return strValue;
}

_variant_t strtovar(CString value)
{
	_variant_t vt;
	vt.vt = value.IsEmpty() ? VT_NULL : VT_BSTR;
	vt.bstrVal = value.AllocSysString();
	return vt;
}

//ִ��һ��sql���
BOOL CModelView::exec_sql(char *sql_cmd)
{
	try
	{
		return SUCCEEDED(m_pRecordset->Open(sql_cmd, _variant_t((IDispatch*)m_pConnection, true),adOpenDynamic,adLockOptimistic,adCmdText));
	}
	catch (_com_error e)
	{
		TRACE(_T("Warning: �򿪼�¼�������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"), e.ErrorMessage(), __FILE__, __LINE__);
		return FALSE;
	}
}

//һ��model��һ����

//����һ��ģ��
BOOL CModelView::read_one_model(CString model_name)
{
	char sql_cmd[500],buf[10];

	m_sqlserver_db.dbname=model_name;

	CClientDC dc(this);

	try
	{
		CString Datasource;
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
		HRESULT hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
		//����һ���������ִ��е�Provider�����SQL Server������
	}
	catch(_com_error e)///��׽�쳣
	{
		CString Prompt;
		Prompt.Format("�������ݿ�%sʧ�ܣ�����������ݿ��û����Ϳ����Ƿ���ȷ!",model_name);
		MessageBox(Prompt,"����");///��ʾ������Ϣ
		return false;
	}
	
	/*��������*/

	//��MODELSET_Table
	try
	{
		strcpy(sql_cmd, "SELECT * FROM MODELSET_Table where �����=");
		itoa(cur_task_id,buf,10);
		strcat(sql_cmd, buf);
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(sql_cmd,_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		if (!m_pRecordset->EndOfFile)
		{
			BmpPath=vartostr(m_pRecordset->GetCollect("����ͼƬ·��"));
			oldPercentage=atof(vartostr(m_pRecordset->GetCollect("���ű���")));
			xScale=atof(vartostr(m_pRecordset->GetCollect("ͼƬX���ű���")));
			yScale=atof(vartostr(m_pRecordset->GetCollect("ͼƬY���ű���")));
			
			if ( pBmp != NULL )
				delete(pBmp);
			if (BmpPath!="")
				pBmp = new CMyBmp(BmpPath);
			else
				pBmp = NULL;
		}
		else
		{
			oldPercentage=1;
			BmpPath="";
		}
		m_pRecordset.Release();
	}
	catch(_com_error e)///��׽�쳣
	{
		if (m_pRecordset!=NULL)
			m_pRecordset.Release();
		MessageBox("��ȡģ�Ϳ��е�ģ�����Ա�ʧ��!","����");///��ʾ������Ϣ
		return false;
	}

	//������
	try
	{
		strcpy(sql_cmd, "SELECT * FROM NODES_Table where �����=");
		itoa(cur_task_id,buf,10);
		strcat(sql_cmd, buf);
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(sql_cmd,_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		while(!m_pRecordset->EndOfFile)
		{
			long value;
			IBaseCom * pCom = NULL;

			int com_no=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("ͼ����״"))));
			CLSID clsid=*CLSIDArray[com_no];
			IID iid=*IIDArray[com_no];
			
			HRESULT hr=::CoCreateInstance(clsid, NULL, CLSCTX_ALL, iid, (void **)&pCom);
			if ( !SUCCEEDED(hr) )
			{
				MessageBox("init node_com fail");
				return false;
			}
			Node * node = new Node(pCom);
			node->SetActive(FALSE);
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("����"))));
			node_id_count=value+1;
			node->SetID(value);
			//m_pRecordset->GetCollect("�����");
			//node->obj_id=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("�������"))));
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("���"))));
			node->layer=value;
			//m_pRecordset->GetCollect("�������");
			//m_pRecordset->GetCollect("������");
			node->inLine=NULL;
			node->SetName(vartostr(m_pRecordset->GetCollect("�������")));
			//m_pRecordset->GetCollect("�����������");
			node->comment=vartostr(m_pRecordset->GetCollect("�������"));
			
			CPoint pos1, pos2;
			pos1.x=scrollpos.x;
			pos1.y=scrollpos.y;
			pos2.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("X����"))))-scrollpos.x;
			pos2.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("Y����"))))-scrollpos.y;
			node->SetScrPos(pos1);
			node->SetTopLeft(pos2);

			//m_pRecordset->GetCollect("ͼ������");
			//m_pRecordset->GetCollect("ͼ���߿�");
			m_model_scale=atof(vartostr(m_pRecordset->GetCollect("����")));

			GraphInfo * gi = node->GetGraphInfo();
			//m_pRecordset->GetCollect("ͼ����ɫ"))));
			gi->textcolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("������ɫ"))));
			gi->pointsize=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("�ֺ�"))));
			CString lfstr=vartostr(m_pRecordset->GetCollect("����"));
			if (lfstr!="")
			{
				LOGFONT lf;
				sscanf(lfstr,"%ld,%ld,%ld,%ld,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%s",&lf.lfHeight,&lf.lfWidth,&lf.lfEscapement,&lf.lfOrientation,&lf.lfWeight,&lf.lfItalic,&lf.lfUnderline,&lf.lfStrikeOut,&lf.lfCharSet,&lf.lfOutPrecision,&lf.lfClipPrecision,&lf.lfQuality,&lf.lfPitchAndFamily,lf.lfFaceName);
				gi->SetFont(lf);
			}
			//m_pRecordset->GetCollect("�������");
			gi->normal_regioncolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("�����ɫ"))));
			node->SetGraphInfo(gi);

			//��ȡ����Ӧ��������Ϣ
			node->rgnName=vartostr(m_pRecordset->GetCollect("������"));
			node->rgnType=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("��������"))));
			node->point_count=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("�������"))));
			node->Points = new CPoint[node->point_count];
			CString pointlist=vartostr(m_pRecordset->GetCollect("���������"));
			CString singlepoint;
			int pos;
			for (int rgn_point_count=0; rgn_point_count<node->point_count; rgn_point_count++)
			{
				pos=pointlist.Find(";");
				singlepoint=pointlist.Left(pos);
				pointlist=pointlist.Right(pointlist.GetLength()-pos-1);
				sscanf(singlepoint,"(%d,%d)",&node->Points[rgn_point_count].x,&node->Points[rgn_point_count].y);
			}

			//m_pRecordset->GetCollect("��������");
			//m_pRecordset->GetCollect("������־");
			int flag=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("ɾ����־"))));
			if (flag==1)
				node->SetDeleted(true);
			else
				node->SetDeleted(false);

			//node->SetActive(TRUE);
			node->NodeData.data_num=0;
			NodeArray.Add(node);
			if (!node->IsDeleted())
				node->Draw(&dc, pos2, pos1, m_model_scale, gi, 1, node->GetActive());
			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
	}
	catch(_com_error e)///��׽�쳣
	{
		if (m_pRecordset!=NULL)
			m_pRecordset.Release();
		MessageBox("��ȡģ�Ϳ��еĽ���ʧ��!","����");///��ʾ������Ϣ
		return false;
	}
	
	//�����߱�
	try
	{
		CPoint startPoint, endPoint;
		strcpy(sql_cmd, "SELECT * FROM LINE_Table where �����=");
		itoa(cur_task_id,buf,10);
		strcat(sql_cmd, buf);
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(sql_cmd,_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		while(!m_pRecordset->EndOfFile)
		{
			long value;
			Node *parentnode,*sonnode;
			IMyLineCom * pLineCom = NULL;
			HRESULT hr = ::CoCreateInstance(CLSID_MyLineCom, NULL, CLSCTX_ALL, IID_IMyLineCom, (void **)&pLineCom);
			if ( !SUCCEEDED(hr) )
			{
				MessageBox("����Line_COM����");
				return false;
			}
			Line * line = new Line((IBaseCom*)pLineCom);

			line->SetActive(FALSE);

			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("���ߺ�"))));
			line->SetID(value);
			line_id_count=value+1;
			//m_pRecordset->GetCollect("�����");
			//m_pRecordset->GetCollect("�������");
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("������"))));
			parentnode=Get_Node_In_NodeArray(value);
			//m_pRecordset->GetCollect("���������");
			//m_pRecordset->GetCollect("�������");
			//m_pRecordset->GetCollect("�������к�");
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("�ӽ���"))));
			sonnode=Get_Node_In_NodeArray(value);
			//m_pRecordset->GetCollect("�ӽ������");
			//m_pRecordset->GetCollect("�ӽ����");
			//m_pRecordset->GetCollect("�ӽ����к�");
			line->SetName(vartostr(m_pRecordset->GetCollect("��������")));
			//m_pRecordset->GetCollect("������������");
			line->comment=vartostr(m_pRecordset->GetCollect("��������"));
	
			CPoint pos1,pos2;
			pos1.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("�������X"))))-scrollpos.x;
			pos1.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("�������Y"))))-scrollpos.y;
			pos2.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("�����յ�X"))))-scrollpos.x;
			pos2.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("�����յ�Y"))))-scrollpos.y;

			GraphInfo * gi = line->GetGraphInfo();
			gi->normal_penStyle=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("��������"))));
			gi->normal_linewidth=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("���߿��"))));
			gi->normal_linecolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("������ɫ"))));
			gi->active_linecolor = gi->normal_linecolor;
			line->SetGraphInfo(gi);
			//m_pRecordset->GetCollect("��ͷ����");
			//m_pRecordset->GetCollect("������־");
			int flag=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("ɾ����־"))));
			if (flag==1)
				line->SetDeleted(true);
			else
			{
				line->SetDeleted(false);
				line->parentNode = parentnode;
				line->sonNode = sonnode;
				sonnode->inLine=line;
				parentnode->outLine.Add(line);
				line->GetCom()->SetStartPoint((unsigned long)&pos1);
				line->GetCom()->SetEndPoint((unsigned long)&pos2);
				line->Draw(&dc, pos1, scrollpos, m_model_scale, 0, 1, line->GetActive());
			}
			LineArray.Add(line);
			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
	}
	catch(_com_error e)///��׽�쳣
	{
		if (m_pRecordset!=NULL)
			m_pRecordset.Release();
		MessageBox("��ȡģ�Ϳ��е����߱�ʧ��!","����");///��ʾ������Ϣ
		return false;
	}

	return true;
}

//���浱ǰ����������ݵ���ǰģ�͵�����������ݱ���
BOOL CModelView::save_reason_steps_to_DB()
{
	CString Datasource;
	char sql_cmd[500],buf[10];
	int i;

	//ɾ��ԭ������
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from RESULT_Table where ����ID��=");
	itoa(cur_task_id,buf,10);
	strcat(sql_cmd, buf);
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//������������
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("RESULT_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
	for (i=0;i<reason_step_count;i++)
	{
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("����ID��", _variant_t(reason_step[i].task_id));
		m_pRecordset->PutCollect("�������", _variant_t(reason_step[i].step_id));
		m_pRecordset->PutCollect("����ID��", _variant_t(reason_step[i].rule_id));
		m_pRecordset->PutCollect("����", _variant_t(reason_step[i].node_id));
	}
	if (reason_step_count>0)
		m_pRecordset->Update();
	m_pRecordset.Release();
	return true;
}

//��ģ���Ƿ��Ѿ�����
int CModelView::if_exist_model(CString model_name)
{
	int count=ModelArray.GetSize();
	for (int i=0; i<count; i++)
		if (ModelArray.GetAt(i).CompareNoCase(model_name))
			return i;
	return -1;
}

void CModelView::CreateTree_OnOpen(Node *node, HTREEITEM parent_item, CModelTree *pTreeView, CTreeCtrl& m_ctlTree)
{
	if (node->IsDeleted()) 
		return;
	else
	{
		int treecount = m_ctlTree.GetCount();
		int imageno=get_image_no_of_node(node);
		pTreeView->m_Tree.TreeItem[treecount-1]=m_ctlTree.InsertItem(node->GetName(),imageno,imageno+1,parent_item,TVI_LAST);
		pTreeView->m_Tree.NodeArray.Add(node);
		parent_item=pTreeView->m_Tree.TreeItem[treecount-1];
		int childcount=node->outLine.GetSize();
		for (int i=0;i<childcount;i++)
		{
			Node *son_node=node->outLine.GetAt(i)->sonNode;
			CreateTree_OnOpen(son_node,parent_item,pTreeView,m_ctlTree);
		}
	}
}

void CModelView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nSBCode)
	{
	case SB_LEFT:			//���������
		scrollpos.x = 0;
		break;
		
	case SB_RIGHT:			//�������Ҷ�
		scrollpos.x = MODELVIEW_MAX_X_RANGE;
		break;
		
	case SB_LINELEFT:		//�������һ��
		scrollpos.x = scrollpos.x - MODELVIEW_X_LINE;
		break;
		
	case SB_LINERIGHT:		//���ҹ���һ��
		scrollpos.x = scrollpos.x + MODELVIEW_X_LINE;
		break;
		
	case SB_PAGELEFT:		//�������һҳ
		scrollpos.x = scrollpos.x - MODELVIEW_X_PAGE;
		break;
		
	case SB_PAGERIGHT:		//���ҹ���һҳ
		scrollpos.x = scrollpos.x + MODELVIEW_X_PAGE;
		break;
		
	case SB_THUMBPOSITION:	//�϶���������ĳ��λ��
		scrollpos.x = nPos;
		break;
		
	default:	break;
	}
	//������Զ���Ĺ�����,ҪSetScrollPos(SB_HORZ, currentpos);
	if ( scrollpos.x < 0 )
		scrollpos.x = 0;
	
	if ( scrollpos.x > MODELVIEW_MAX_X_RANGE )
		scrollpos.x = MODELVIEW_MAX_X_RANGE;
	
	SetScrollPos(SB_HORZ, scrollpos.x);
	
	//SetScrollPos(SB_VERT, m_pDoc->s_offset.x);
	UpdateWindow();
	Invalidate();
	
	//CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CModelView::OnLButtonDown(UINT nFlags, CPoint point)
{
	Node * node = NULL;
	ModelObject * pModelObject = NULL,
				* mo = NULL;

	BOOL isPtInRgn = FALSE,
		 IsActive = FALSE;
	CClientDC dc(this);
	CPoint m_point;
	unsigned long count = 0,
				  i = 0;

	//CFileDialog fd(FALSE, "*.txt|*.xml", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"txt File(.txt)|*.txt|xml File(.xml)|*.xml|");
	//fd.DoModal();

	TRACE("downx=%d, downy=%d\n", point.x, point.y);

	actionflag = NOTHING;
	SetCapture();
	mousemoving = FALSE;
	mousedown = TRUE;
	
	count = NodeArray.GetSize();
	for(i=0; i<count; i++)
		NodeArray.GetAt(i)->SetIgnored(FALSE);
	
	count = LineArray.GetSize();
	for(i=0; i<count; i++)
		LineArray.GetAt(i)->SetIgnored(FALSE);
	
	lastPoint.x = downPoint.x = point.x;
	lastPoint.y = downPoint.y = point.y;
	CPoint m_xPoint((int)(point.x/oldPercentage),(int)(point.y/oldPercentage));

	if ( finish_add_line )
	{
		finish_add_line = FALSE;
	}

	if ( add_new_line_flag )
	{
		//......
		count = SelectedObjects.GetSize();
		for (i=0; i<count; i++)
		{
			pModelObject = SelectedObjects.GetAt(i);
			pModelObject->SetActive(FALSE);
			//pModelObject->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 1);
			pModelObject->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 0);
		}
		SelectedObjects.RemoveAll();

		count = NodeArray.GetSize();
		sonNode = NULL;
		parentNode = NULL;
		for ( i=0; i<count; i++ )
		{
			pModelObject = NodeArray.GetAt(i);
			if ( pModelObject->IsDeleted() )
				continue;
			isPtInRgn = pModelObject->PtInRgn(m_xPoint);
			if ( isPtInRgn )
			{
				sonNode = (Node *)pModelObject;
				//curObject = NULL;
				break;
			}
		}
		if ( sonNode == NULL )
		{
			add_new_line_flag = false;
			Invalidate(TRUE);
			CView::OnLButtonDown(nFlags, point);
			return;
		}

		Invalidate(TRUE);
		CView::OnLButtonDown(nFlags, point);
		return;
	}

	count = SelectedObjects.GetSize();
	isPtInRgn = FALSE;
	for (i=0; i<count; i++ )
	{
		pModelObject = SelectedObjects.GetAt(i);

		isPtInRgn = pModelObject->PtInRgn(m_xPoint);
		if ( isPtInRgn )	//�������ĳ�������ڲ�
		{
			curObject = pModelObject;
			switch ( nFlags )
			{
				case MK_LBUTTON + MK_SHIFT:
				case MK_LBUTTON + MK_CONTROL:
								//���ͬʱ����ctrl, ������Ľ���SelectedObjects������ɾ��
								actionflag = CTRL;
								break;
				default:		actionflag = DRAG;
								break;
			}
			break;
		}
	}	//end for �Ѿ�ѡ�еĽ��
		
	//�������һ������ĳ��������
	if ( isPtInRgn )
	{
		Invalidate(TRUE);
		CView::OnLButtonDown(nFlags, point);
		return ;
	}

	//���û�е����κ�һ���Ѿ�ѡ�еĶ����ڲ����ж��Ƿ��������������
	//1���жϽ��
	count = NodeArray.GetSize();
	for (i=0; i<count; i++)
	{
		pModelObject = NodeArray.GetAt(i);
		if ( pModelObject->GetActive() || pModelObject->IsDeleted() )
			continue;

		isPtInRgn = pModelObject->PtInRgn(m_xPoint);
		if ( isPtInRgn )
		{
			curObject = pModelObject;
			switch ( nFlags )
			{
				case MK_LBUTTON + MK_SHIFT:
				case MK_LBUTTON + MK_CONTROL:
								/*
								//����ѡ�еĶ��󼤻�, ����SelectedObjects;
								pModelObject->SetActive(TRUE);
								//pModelObject->DrawOffset(&dc, NULL, scrollpos, m_model_scale, 0, 1, 1);
								SelectedObjects.Add(pModelObject);
								*/
								actionflag = CTRL;
								break;
				default:		count = SelectedObjects.GetSize();
								ModelObject * mo;
								for (i=0; i<count; i++)
								{
									mo = SelectedObjects.GetAt(i);
									mo->SetActive(FALSE);
									//mo->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 0);
								}
								SelectedObjects.RemoveAll();
								SelectedObjects.Add(pModelObject);
								pModelObject->SetActive(TRUE);
								//pModelObject->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 1);
								actionflag = NODE;
								break;
			}
			break;
		}
	}	//end for 

	if ( isPtInRgn )
	{
		Invalidate(TRUE);
		CView::OnLButtonDown(nFlags, point);
		return ;
	}
	
	//2���ж�����
	count = LineArray.GetSize();
	for (i=0; i<count; i++)
	{
		pModelObject = LineArray.GetAt(i);
		if ( pModelObject->GetActive() || pModelObject->IsDeleted() )
			continue;
		isPtInRgn = pModelObject->PtInRgn(m_xPoint);
		if ( isPtInRgn )
		{
			//MessageBox("on it");
			curObject = pModelObject;
			switch ( nFlags )
			{
				case MK_LBUTTON + MK_SHIFT:
				case MK_LBUTTON + MK_CONTROL:
								//����ѡ�еĶ��󼤻�, ����SelectedObjects;
								/*
								pModelObject->SetActive(TRUE);
								//pModelObject->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 1);
								SelectedObjects.Add(pModelObject);
								*/
								actionflag = CTRL;
								break;
				default:		count = SelectedObjects.GetSize();
								for (i=0; i<count; i++)
								{
									mo = SelectedObjects.GetAt(i);
									mo->SetActive(FALSE);
									//mo->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 0);
								}
								SelectedObjects.RemoveAll();
								SelectedObjects.Add(pModelObject);
								pModelObject->SetActive(TRUE);
								//pModelObject->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 1);
								actionflag = LINE;
								break;
			}
			break;
		}
	}

	if ( isPtInRgn )
	{
		Invalidate(TRUE);
		CView::OnLButtonDown(nFlags, point);
		return ;
	}

	//Ҳû�����κ�������
	curObject = NULL;
	switch ( nFlags )
	{
		case MK_LBUTTON + MK_SHIFT:
		case MK_LBUTTON + MK_CONTROL:
						//������Ҫ��ѡ
						actionflag = CLIP;
						break;
		default:		count = SelectedObjects.GetSize();
						for (i=0; i<count; i++)
						{
							mo = SelectedObjects.GetAt(i);
							mo->SetActive(FALSE);
							//mo->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 0);
						}
						
						SelectedObjects.RemoveAll();
						actionflag = CLIP;
	}

	Invalidate(TRUE);
}

void CModelView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if ( !mousedown )
	{
		CView::OnLButtonUp(nFlags, point);
		return ;
	}

	TRACE("upx=%d, upy=%d\n", point.x, point.y);

	CClientDC dc(this);
	ModelObject * pModelObject = NULL,
				* mo = NULL;
	//Node * node = NULL;
	//Line * line = NULL;
	BOOL isPtInRgn = FALSE;
	CPoint topcenter(0,0),
		   bottomcenter(0,0);
	BOOL isActive = FALSE;
			
	ReleaseCapture();
	mousedown = FALSE;
	mousemoving = FALSE;

	unsigned long count = 0,
				  i = 0;

	HRESULT hr;
	CMainFrame * pFWnd = NULL;
	CModelTree * pTreeView = NULL;
	CTreeCtrl * pTreeCtrl = NULL;
	CDiagnoseView *pDiagnose=NULL;

	int treecount = 0;
	CPoint m_xPoint((int)(point.x/oldPercentage),(int)(point.y/oldPercentage));
	if ( add_new_line_flag )
	{
		//......
		add_new_line_flag = FALSE;
		count = NodeArray.GetSize();
		parentNode = NULL;
		for ( i=0; i<count; i++ )
		{
			pModelObject = NodeArray.GetAt(i);
			if ( pModelObject->IsDeleted() )
				continue;
			isPtInRgn = pModelObject->PtInRgn(m_xPoint);
			if ( isPtInRgn )
			{
				parentNode = (Node *)pModelObject;
				//curObject = NULL;
				break;
			}
		}
		if ( parentNode == NULL || parentNode == sonNode || sonNode == NULL )
		{
			Invalidate(TRUE);
			CView::OnLButtonDown(nFlags, point);
			return;
		}
		
		if ( IsCircle(parentNode,sonNode) )
		{
			MessageBox("�������ӽ�㲻�ܳ���ѭ��", "����");
			Invalidate(TRUE);
			CView::OnLButtonDown(nFlags, point);
			return;
		}

		//����parentNode ��sonNode����ز���
		IMyLineCom * pLineCom = NULL;

		hr = ::CoCreateInstance(CLSID_MyLineCom, NULL, CLSCTX_ALL, IID_IMyLineCom, (void **)&pLineCom);
		if ( !SUCCEEDED(hr) )
		{
			MessageBox("����COM����");
			return ;
		}

		Line * newLine = new Line((IBaseCom*)pLineCom);
		Line * pLine = NULL;

		if ( sonNode->inLine != NULL )
		{
			int cc = LineArray.GetSize();
			int ii = 0;
			for(ii=0; ii<cc; ii++ )
			{
				pLine = LineArray.GetAt(ii);
				if ( sonNode->inLine==pLine )
				{
					LineArray.RemoveAt(ii);
					break;
				}
			}
			cc = sonNode->inLine->parentNode->outLine.GetSize();
			for(ii=0; ii<cc; ii++ )
			{
				pLine = sonNode->inLine->parentNode->outLine.GetAt(ii);
				if ( sonNode->inLine == pLine )
				{
					sonNode->inLine->parentNode->outLine.RemoveAt(ii);
					break;
				}
			}

			delete(sonNode->inLine);
		}
		sonNode->inLine = newLine;
		newLine->parentNode = parentNode;
		newLine->sonNode = sonNode;
		parentNode->outLine.Add(newLine);

		newLine->SetID(line_id_count);
		CString t;
		t.Format("%ud", line_id_count);
		newLine->SetName(t);
		newLine->comment = "LINE";
		line_id_count++;

		//��������
		CPoint startPoint,
			   endPoint;

		parentNode->GetBottomCenter(startPoint);
		sonNode->GetTopCenter(endPoint);
		pLineCom->SetStartPoint((unsigned long)&startPoint);
		pLineCom->SetEndPoint((unsigned long)&endPoint);

		newLine->Draw(&dc, 0, scrollpos, m_model_scale, NULL, 1, 1);

		//����ǰ������Ϊ�����ѡ��
		if ( curObject != NULL )
		{
			curObject->SetActive(FALSE);
			curObject->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, 0);
			curObject = NULL;
		}
		curObject = newLine;
		LineArray.Add(newLine);
		SelectedObjects.Add(newLine);

		add_new_line_flag = FALSE;
		actionflag = NOTHING;

		finish_add_line = TRUE;

		//AddLayerNum(sonNode);
		//����Сǿ�Ĵ���
		//10.15
		//.....
		//fqz
		/*����TreeItem[]
		CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
		CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
		CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
		for (i=0;i<m_ctlTree.GetCount()-1;i++)
			MessageBox(m_ctlTree.GetItemText(pTreeView->m_Tree.TreeItem[i]));
		*/

		degrade_to_subtree(sonNode, parentNode->layer+1-sonNode->layer);
		//����treeview: ��sonNodeΪ��������ΪparentNode������
		MoveItemToLast(NodetoItem(sonNode),NodetoItem(parentNode));

		Invalidate(TRUE);
		CView::OnLButtonUp(nFlags, point);
		return ;
	}

	count = NodeArray.GetSize();
	for(i=0; i<count; i++)
		NodeArray.GetAt(i)->SetIgnored(FALSE);
	
	count = LineArray.GetSize();
	for(i=0; i<count; i++)
		LineArray.GetAt(i)->SetIgnored(FALSE);

	mousemoving = FALSE;

	upPoint.x = point.x;
	upPoint.y = point.y;
	CRect curRect(downPoint, upPoint);

	//dc.DrawDragRect(CRect(0,0,0,0),	CSize(0,0), r, CSize(1,1));
//xnf
	CPoint offset((int)((upPoint.x-downPoint.x)/oldPercentage), (int)((upPoint.y-downPoint.y)/oldPercentage));	//λ��
	CPoint topleft, 
		   bottomright;
	Line * pLine = NULL;
	Node * pNode = NULL;
	CPoint newpoint;
	int cc, ii;

	//CMenu * menu;

	switch ( actionflag )
 	{
		case NOTHING://�޶���
					break;
		case NODE:	//�����㣬�ڵ�ǰλ���ػ���
					if ( curObject == NULL )
						break;
					
					curObject->OffsetRgn(offset);
					
					pNode = (Node *)curObject;
					pNode->GetBottomCenter(bottomcenter);
					pNode->GetTopCenter(topcenter);
					if ( pNode->inLine != NULL )
						pNode->inLine->SetEndPoint(topcenter);
					
					count = pNode->outLine.GetSize();
					for ( i=0; i<count; i++ )
					{
						pLine = pNode->outLine.GetAt(i);
						pLine->SetStartPoint(bottomcenter);
					}
						
					//�Ҳ���ѡ����Ӧitem
					pFWnd = (CMainFrame *)AfxGetMainWnd();
					pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
					pDiagnose = (CDiagnoseView *)pFWnd->m_wndSplitter1.GetPane(0,0);

					pTreeCtrl = &pTreeView->GetTreeCtrl();
					pTreeCtrl->SelectItem(NodetoItem(pNode));

					//�޸�diagnoseview
					pDiagnose->m_nodename=pNode->GetName();
					pDiagnose->m_compname=pNode->rgnName;
					pDiagnose->UpdateData(false);
					
					break;

		case LINE:	//��������
					break;

		case CLIP:	//��ѡ
					isPtInRgn = FALSE;
					topleft.x = downPoint.x<upPoint.x ? downPoint.x : upPoint.x;
					topleft.y = downPoint.y<upPoint.y ? downPoint.y : upPoint.y;
					bottomright.x = downPoint.x>upPoint.x ? downPoint.x : upPoint.x;
					bottomright.y = downPoint.y>upPoint.y ? downPoint.y : upPoint.y;
					curRect.SetRect(topleft, bottomright);

					//�ж���Щ���������У�����active��־ȡ"��"
					SelectedObjects.RemoveAll();
					count = NodeArray.GetSize();
					for(i=0; i<count; i++)
					{
						pModelObject = NodeArray.GetAt(i);
						if ( pModelObject->IsDeleted() )
							continue;
						isPtInRgn = pModelObject->InOtherRect(curRect,oldPercentage);
						if ( isPtInRgn )
						{
							pModelObject->SetActive(TRUE);
							SelectedObjects.Add(pModelObject);
						}
						else
							pModelObject->SetActive(FALSE);
					}

					count = LineArray.GetSize();
					for(i=0; i<count; i++)
					{
						pModelObject = LineArray.GetAt(i);
						if ( pModelObject->IsDeleted() )
							continue;
						isPtInRgn = pModelObject->InOtherRect(curRect,oldPercentage);
						if ( isPtInRgn )
						{
							pModelObject->SetActive(TRUE);
							SelectedObjects.Add(pModelObject);
						}
						else
							pModelObject->SetActive(FALSE);
					}
					/*
					count = SelectedObjects.GetSize();
					if ( count >= 1 )
						curObject = SelectedObjects.GetAt(count-1);
					else
						curObject = NULL;
					*/
					break;
					
		case MOVE:
		case DRAG:	//ѡ��һ��������Ϸ�
					//��ѡ�н�㼰������������¼������꣬����ͼ
					count = SelectedObjects.GetSize();
					for (i=0; i<count; i++)
					{
						pModelObject = SelectedObjects.GetAt(i);
						if ( pModelObject->IsKindOf(RUNTIME_CLASS(Node)) )
						{
							pNode = (Node *)pModelObject;
							pNode->OffsetRgn(offset);
							//pNode->DrawOffset(&dc, offset, scrollpos, m_model_scale, 0, 1, 1);
							
							if ( pNode->inLine != NULL )
							{
								pNode->GetTopCenter(topcenter);
								pNode->inLine->SetEndPoint(topcenter);
							}
							
							cc = pNode->outLine.GetSize();
							pNode->GetBottomCenter(bottomcenter);
							for ( ii=0; ii<cc; ii++ )
							{
								pLine = pNode->outLine.GetAt(ii);
								pLine->SetStartPoint(bottomcenter);
							}
						}
						/*�������϶�����
						else
						{
							pLine = (Line *)pModelObject;
							pLine->pCom->Draw((unsigned long)&dc, 0, (unsigned long)&scrollpos, 1, 0, 1, 1);
							pLine->pCom->OffsetRgn((unsigned long)&offset);
						}
						*/
					}

					break;
					
		//case MOVE:	//һ�����λ���ƶ��������е�node������NODE�ķ�ʽ���д���

		//case SHIFT://shift�����
		case CTRL:	//ctrl�����
					//......
					//removeѡ�еĽ��
					if ( curObject != NULL )
					{
						count = SelectedObjects.GetSize();
						for (i=0; i<count; i++)
						{
							if ( curObject == SelectedObjects.GetAt(i) )
							{
								curObject->SetActive(FALSE);
								SelectedObjects.RemoveAt(i);
								curObject = NULL;
								break;
							}
						}
						if ( i == count )
						{
							curObject->SetActive(TRUE);
							SelectedObjects.Add(curObject);
						}

					}
					break;
		case COPY:	//MessageBox("����ѡ�ж���");
					break;

		default:	break;
	}

	actionflag = NOTHING;

	Invalidate(TRUE);
	//UpdateWindow();
}

void CModelView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( !mousedown )
	{
		CView::OnMouseMove(nFlags, point);
		return ;
	}
	
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CSize size(1,1);

	CRgn rgn,
		 outRgn;
	rgn.CreateRectRgn(0,0,5,5);
	outRgn.CreateRectRgn(0,0,5,5);

	static CRect lastNodeRect,	//for case NODE
				 curNodeRect;
	static CRect outRect,		//for case Drag
				 lastDragRect,
				 curDragRect;
	static CRect lastMoveRect,	//for case MOVE
				 curMoveRect;
	static CRect lastClipRect,	//for case CLIP
				 curClipRect;

	CPoint topleft,			//��clipʱ�����ö˵���
		   bottomright;

	BOOL first_combine = true;

	ModelObject * pModelObject = NULL ;
	unsigned long count = 0,
				  i = 0;

	BOOL isInRgn = FALSE,
		 isInRgn2 = FALSE;
	BOOL isActive = FALSE;

	movePoint.x = point.x;
	movePoint.y = point.y;

	bool find_node_flag = false;

	if ( add_new_line_flag )
	{
		//����
		CPen * pen = new CPen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen * syspen = dc.SelectObject(pen);

		if ( lastPoint != point )
		{
			//TRACE("invalidate\n");
			Invalidate(TRUE);
		}

		dc.MoveTo(downPoint);
		//dc.LineTo(lastPoint);
		//dc.MoveTo(downPoint);
		dc.LineTo(point);

		lastPoint.x = point.x;
		lastPoint.y = point.y;

		dc.SelectObject(syspen);
		delete pen;
		CView::OnMouseMove(nFlags, point);
		return ;
	}

	add_new_line_flag = false;
	TRACE("movex=%d, movey=%d\n", point.x, point.y);
	CRect lastR,CurR;
	switch ( actionflag )
	{
		case NOTHING:	//�޶���
					break;
		case NODE:	//�ƶ������㣬ȡ�������ԭͼ����������Ͻǵ�λ�ƣ�
					if ( !mousemoving )
					{
						if ( curObject == NULL )
						{
							MessageBox("actionflagΪ�ƶ���㣬��curObjectΪ��", "����");
							lastPoint.x = point.x;
							lastPoint.y = point.y;
							CView::OnMouseMove(nFlags, point);
							return ;
						}
						//ȡ��com�ı�Ե����
						curObject->GetCom()->GetRgn((unsigned long)&rgn);
						rgn.GetRgnBox(&lastNodeRect);
						//lastNodeRect=CRect(lastNodeRect.left,lastNodeRect.top,lastNodeRect.right,lastNodeRect.bottom);
						lastNodeRect.SetRect((int)(lastNodeRect.left*oldPercentage),(int)(lastNodeRect.top*oldPercentage),
										(int)(lastNodeRect.right*oldPercentage),(int)(lastNodeRect.bottom*oldPercentage));
						//�����ƶ������λ��
						curNodeRect.SetRect(lastNodeRect.TopLeft(), lastNodeRect.BottomRight());
						curNodeRect.OffsetRect(movePoint.x-lastPoint.x, movePoint.y-lastPoint.y);
						//dc.DrawDragRect(curNodeRect, size, lastNodeRect, size);//xnfp
						mousemoving = TRUE;
					}
					else
					{
						//���ϴεĽ����ʼ��lastRect
						lastNodeRect.SetRect(curNodeRect.TopLeft(), curNodeRect.BottomRight());
						curNodeRect.OffsetRect(movePoint.x-lastPoint.x, movePoint.y-lastPoint.y);
					//	dc.DrawDragRect(curNodeRect, size, lastNodeRect, size);xnf change
					//	lastR.SetRect((int)(lastNodeRect.left*oldPercentage),(int)(lastNodeRect.top*oldPercentage),
					//					(int)(lastNodeRect.right*oldPercentage),(int)(lastNodeRect.bottom*oldPercentage));
					//	CurR.SetRect((int)(curNodeRect.left*oldPercentage),(int)(curNodeRect.top*oldPercentage),
					//				(int)(curNodeRect.right*oldPercentage),(int)(curNodeRect.bottom*oldPercentage));

						dc.DrawDragRect(curNodeRect, size, lastNodeRect, size);
					}
					break;
					
		case LINE:	//�������ߣ���ʱ�������ƶ�����
					break;

		case MOVE:
		case DRAG:	//�Ϸţ����������ϽǺ������½ǣ���һ������
					actionflag = MOVE;
					if ( !mousemoving )
					{
						count = SelectedObjects.GetSize();
						for (i=0; i<count; i++)
						{
							pModelObject = SelectedObjects.GetAt(i);
							if ( pModelObject->IsDeleted() )
								continue;
							if ( !pModelObject->IsKindOf(RUNTIME_CLASS(Node)) )
								continue;

							//����ȡ�õ�����
							if ( first_combine )
							{
								//outRgn.DeleteObject();
								pModelObject->GetCom()->GetRgn((unsigned long)&outRgn);
								first_combine = false;
							}
							else
							{
								pModelObject->GetCom()->GetRgn((unsigned long)&rgn);
								outRgn.CombineRgn(&rgn, &outRgn, RGN_OR);
							}
						}
						outRgn.GetRgnBox(&outRect);
						outRect.SetRect((int)(outRect.left*oldPercentage),(int)(outRect.top*oldPercentage),(int)(outRect.right*oldPercentage),(int)(outRect.bottom*oldPercentage));//
						lastMoveRect.SetRect(outRect.TopLeft(), outRect.BottomRight());
						curMoveRect.SetRect(outRect.TopLeft(), outRect.BottomRight());

						//curMoveRect.OffsetRect(movePoint.x-downPoint.x, movePoint.y-downPoint.y);
						//TRACE("x1=%d, y1=%d; x2=%d, y2=%d\n", lastMoveRect.left, lastMoveRect.top, curMoveRect.left, curMoveRect.top);
						//dc.DrawDragRect(curMoveRect, size, lastMoveRect, size);
						mousemoving = TRUE;
					}
					else
					{
						count = SelectedObjects.GetSize();
						find_node_flag = false;
						for ( i=0; i<count; i++ )
						{
							if ( !SelectedObjects.GetAt(i)->IsKindOf(RUNTIME_CLASS(Node)) )
								continue;
							else
								find_node_flag = true;
						}

						if ( find_node_flag )
						{
							//���ϴεĽ����ʼ��lastRect
							lastMoveRect.SetRect(curMoveRect.TopLeft(), curMoveRect.BottomRight());
							curMoveRect.OffsetRect(movePoint.x-lastPoint.x, movePoint.y-lastPoint.y);
							TRACE("x1=%d, y1=%d; x2=%d, y2=%d\n", lastMoveRect.left, lastMoveRect.top, curMoveRect.left, curMoveRect.top);
							lastR.SetRect((int)(lastMoveRect.left),(int)(lastMoveRect.top),
										(int)(lastMoveRect.right),(int)(lastMoveRect.bottom));
							CurR.SetRect((int)(curMoveRect.left),(int)(curMoveRect.top),
									(int)(curMoveRect.right),(int)(curMoveRect.bottom));
//							
							dc.DrawDragRect(CurR, size, lastR, size);
						}
					}
					break;

		case NEW:	//�½����
					break;
		case CTRL:	//ctrl�����
					if ( movePoint != downPoint || movePoint != lastPoint )
					{
						curObject->SetActive(TRUE);
						SelectedObjects.Add(curObject);
						actionflag = COPY;
					}
					break;
		case CLIP:	//drewdragcret,������ɿ���������SelectedObjects����ʹЧ�ʸ�һЩ
					isInRgn2 = isInRgn = FALSE;
					//if ( downPoint.x == lastPoint.x || downPoint.y == lastPoint.y )
					//	break;
					topleft.x = downPoint.x<lastPoint.x ? downPoint.x : lastPoint.x;
					topleft.y = downPoint.y<lastPoint.y ? downPoint.y : lastPoint.y;
					bottomright.x = downPoint.x>lastPoint.x ? downPoint.x : lastPoint.x;
					bottomright.y = downPoint.y>lastPoint.y ? downPoint.y : lastPoint.y;
					lastClipRect.SetRect(topleft, bottomright);

					//if ( downPoint.x == movePoint.x || downPoint.y == movePoint.y )
					//	break;
					topleft.x = downPoint.x<movePoint.x ? downPoint.x : movePoint.x;
					topleft.y = downPoint.y<movePoint.y ? downPoint.y : movePoint.y;
					bottomright.x = downPoint.x>movePoint.x ? downPoint.x : movePoint.x;
					bottomright.y = downPoint.y>movePoint.y ? downPoint.y : movePoint.y;
					curClipRect.SetRect(topleft, bottomright);

					//TRACE("downx=%d, downy=%d, movex=%d, movey=%d\n", downPoint.x, downPoint.y, movePoint.x, movePoint.y);

					dc.DrawDragRect(curClipRect, size, lastClipRect, size);
					outRgn.DeleteObject();
					outRgn.CreateRectRgn(curClipRect.left,curClipRect.top,curClipRect.right, curClipRect.bottom);
					//�ж���Щ���������У�����active��־ȡ"��"
					count = NodeArray.GetSize();
					for(i=0; i<count; i++)
					{
						pModelObject = NodeArray.GetAt(i);
						if ( pModelObject->IsDeleted() )
							continue;
						isInRgn = pModelObject->InOtherRect(lastClipRect,oldPercentage);
						isInRgn2 = pModelObject->InOtherRect(curClipRect,oldPercentage);
						if ( isInRgn != isInRgn2 )	//�����ѡǰ������״̬�����ı�
						{
							isActive = pModelObject->GetActive();
							isActive = !isActive;
							pModelObject->SetActive(isActive);
						}
					}

					count = LineArray.GetSize();
					for(i=0; i<count; i++)
					{
						pModelObject = LineArray.GetAt(i);
						if ( pModelObject->IsDeleted() )
							continue;
						isInRgn = pModelObject->InOtherRect(lastClipRect,oldPercentage);
						isInRgn2 = pModelObject->InOtherRect(curClipRect,oldPercentage);
						
						if ( isInRgn != isInRgn2 )	//�����ѡǰ������״̬�����ı�
						{
							isActive = pModelObject->GetActive();
							isActive = !isActive;
							pModelObject->SetActive(isActive);
						}
					}
					break;
		//default :	MessageBox("�������궯������", "����");
	}

	lastPoint.x = point.x;
	lastPoint.y = point.y;
}

void CModelView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CDiagnoseView *pDiagnose = (CDiagnoseView *)pFWnd->m_wndSplitter1.GetPane(0,0);
	pDiagnose->UpdateData(false);
	CView::OnRButtonUp(nFlags, point);
}

void CModelView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	switch ( nSBCode)
	{
	case SB_TOP:			//����������
		scrollpos.y = 0;
		break;
		
	case SB_BOTTOM:			//�������ײ�
		scrollpos.y = MODELVIEW_MAX_Y_RANGE;
		break;
		
	case SB_LINEUP:			//������������ϵİ���,����һ��
		scrollpos.y = scrollpos.y - MODELVIEW_Y_LINE;
		break;
		
	case SB_LINEDOWN:		//������������µİ���,����һ��
		scrollpos.y = scrollpos.y + MODELVIEW_Y_LINE;
		break;
		
	case SB_PAGEUP:			//����������ϲ��հ�,����һҳ
		scrollpos.y = scrollpos.y - MODELVIEW_Y_PAGE;
		break;
		
	case SB_PAGEDOWN:		//����������²��հ�,����һҳ
		scrollpos.y = scrollpos.y + MODELVIEW_Y_PAGE;
		break;
		
	case SB_THUMBPOSITION:	//�϶���������ĳ��λ��(������nPos��)
		scrollpos.y = nPos;
		break;
		
	default:	break;
	}
	//������Զ���Ĺ�����,ҪSetScrollPos(SB_VERT, currentpos)
	if ( scrollpos.y < 0 )
		scrollpos.y = 0;
	
	if ( scrollpos.y > MODELVIEW_MAX_Y_RANGE )
		scrollpos.y = MODELVIEW_MAX_Y_RANGE;
	
	SetScrollPos(SB_VERT, scrollpos.y);
	
	//SetScrollPos(SB_HORZ, m_pDoc->s_offset.y);
	
	UpdateWindow();
	Invalidate();
		
//	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CModelView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CModelView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	SetScrollRange(SB_VERT, 0, MODELVIEW_MAX_Y_RANGE, TRUE);
	SetScrollRange(SB_HORZ, 0, MODELVIEW_MAX_X_RANGE, TRUE);
	scrollpos.x = 0;
	scrollpos.y = 0;
	SetScrollPos(SB_VERT, scrollpos.x, TRUE);
	SetScrollPos(SB_HORZ, scrollpos.y, TRUE);
	

	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));
	pFrm->SetActiveView(pView); //�����	
	SetTimer(0,150,NULL);
}

void CModelView::OnSelectmodel() 
{
	// TODO: Add your command handler code here

	if (m_cur_model_name!="")
		StopCurGlint();

	COpenModelDlg dlg;
	if (dlg.DoModal()==IDCANCEL)
		return;

	m_cur_model_name=dlg.m_select_model;
	clear_nodearray_linearray();
	
	if(m_pConnection->State)
		 m_pConnection->Close(); //����Ѿ�����������ر���
	read_one_model(m_cur_model_name);

	cur_reason_node_no=0;
	SelectedObjects.RemoveAll();
	curObject = NULL;
	import_data_flag=FALSE;

	//�޸��ұߵ���
	CMainFrame *pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree *pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	pTreeView->m_Tree.NodeArray.RemoveAll();
	m_ctlTree.DeleteItem(pTreeView->m_Tree.root);
	pTreeView->m_Tree.root = m_ctlTree.InsertItem(_T("VIRTUAL ROOT"),0,1, 0, TVI_ROOT);
	int count=NodeArray.GetSize();
	Node *pNode;
	for (int i=0;i<count;i++)
	{
		pNode=NodeArray.GetAt(i);
		if (pNode->inLine==NULL)
			CreateTree_OnOpen(pNode,pTreeView->m_Tree.root,pTreeView,m_ctlTree);
	}
	pTreeView->ExpandAll(m_ctlTree.GetRootItem());

	//������ǰ��ͼ������Ӧģ�ͽ����
	CurModelGraphRect=CalModelGraphRect();
	int x1 = CurModelGraphRect.left,
		y1 = CurModelGraphRect.top,
		x2 = CurModelGraphRect.right,
		y2 = CurModelGraphRect.bottom;

	CString str;

	if (count>0)
	{
		CPoint pos(CurModelGraphRect.left+scrollpos.x,CurModelGraphRect.top+scrollpos.y);
		
		//draw ����ͼ
		bmpx=CurModelGraphRect.left+scrollpos.x;
		bmpy=CurModelGraphRect.bottom+scrollpos.y+(int)(20*oldPercentage);
		
		scrollpos = pos;
		SetScrollPos(SB_VERT, pos.y, TRUE);
		SetScrollPos(SB_HORZ, pos.x, TRUE);
		
		fullgraph_times=0;
		OnFullGraph();
	}
	
	cur_reason_node_no=0;
	reason_step_count=0; //��գ���������
	CTipView *pTip = (CTipView *)pFWnd->m_wndSplitter3.GetPane(1,0);
	pTip->ClearTipData();

	DiagnoseResult="";
	Invalidate(true);
}

//���㵱ǰģ�ͽ��ͼ����Χ����
CRect CModelView::CalModelGraphRect() 
{
	int minleft=30000,mintop=30000,maxright=-30000,maxbottom=-30000;
	CPoint topleft, bottomright;
	int i;
	int count=NodeArray.GetSize();
	Node *pNode;
	CRect result;
	CRgn rgn;
	rgn.CreateRectRgn(0,0,5,5);
	
	for (i=0; i<count;i++)
	{
		pNode=NodeArray.GetAt(i);
		
		pNode->GetCom()->GetRgn((unsigned long)&rgn);
		rgn.GetRgnBox(&result);
		topleft = result.TopLeft();
		bottomright = result.BottomRight();

		if (topleft.x<minleft)
			minleft=topleft.x;
		if (topleft.y<mintop)
			mintop=topleft.y;
		if (bottomright.x>maxright)
			maxright=bottomright.x;
		if (bottomright.y>maxbottom)
			maxbottom=bottomright.y;
	}
	if (count>0)
		result.SetRect(minleft-20,mintop-20,maxright,maxbottom);	
	else
		result.SetRect(0,0,0,0);

	return result;
}

void CModelView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CClientDC dc(this);
	OnPrepareDC(&dc);
	if (m_cGlint.IsActiveGlint())
	{

		CRgn rgn;
		rgn.CreateRectRgn(0,0,10,10);
		CRect crectValue(100,100,200,200);
		m_glintActive=!m_glintActive;
		m_cGlint.m_glintNode->GetCom()->GetRgn((unsigned long)&rgn);
		rgn.GetRgnBox(&crectValue);
		TRACE("x=%d, y=%d\n", crectValue.left, crectValue.top);
		TRACE("x=%d, y=%d\n", crectValue.right, crectValue.bottom);
		crectValue.InflateRect(5, 5);
		TRACE("x=%d, y=%d\n", crectValue.left, crectValue.top);
		TRACE("x=%d, y=%d\n", crectValue.right, crectValue.bottom);
		SetNodeRect(&dc,crectValue,m_glintActive);
		
	}
	if (m_cGlint.IsActiveBmp())
	{
		//wht SetBmpGlint(&dc,m_cGlint.m_bmpIndex,m_bmpChange);
		CRgn rgn;
		CBrush brush(RGB(255, 255, 255));
		CPoint * realPoints = NULL;
		realPoints = new CPoint[m_cGlint.m_glintNode->point_count];
		for (int i=0; i<m_cGlint.m_glintNode->point_count; i++ )
		{
			realPoints[i].x = (int)( m_cGlint.m_glintNode->Points[i].x / xScale ) + bmpx-scrollpos.x;
			realPoints[i].y = (int)( m_cGlint.m_glintNode->Points[i].y / yScale ) + bmpy-scrollpos.y;
		}
		
		switch ( m_cGlint.m_glintNode->rgnType )
		{
			case 0: rgn.CreatePolygonRgn(realPoints, m_cGlint.m_glintNode->point_count, ALTERNATE);
					dc.FillRgn(&rgn, &brush);
					break;
			case 1: rgn.CreatePolygonRgn(realPoints, m_cGlint.m_glintNode->point_count, ALTERNATE);
					dc.FillRgn(&rgn, &brush);
					break;
			case 2: rgn.CreateEllipticRgnIndirect(CRect(realPoints[0], realPoints[1]));
					dc.FillRgn(&rgn, &brush);
					break;
		}
		m_bmpChange=!m_bmpChange;
		delete []realPoints;
	}	

	CView::OnTimer(nIDEvent);
}

void CModelView::EndNodeg(Node *p)
{
		CClientDC dc(this);	
		CRgn rgn;
		OnPrepareDC(&dc);
		rgn.CreateRectRgn(0,0,10,10);
		CRect crectValue(100,100,200,200);
		p->GetCom()->GetRgn((unsigned long)&rgn);
		rgn.GetRgnBox(&crectValue);
		crectValue.InflateRect(5, 5);
	
		if(m_glintActive)
			SetNodeRect(&dc,crectValue,m_glintActive);
		m_glintActive=FALSE;
	//	p->
}

void CModelView::SetNodeRect(CDC *pDC, CRect rect, BOOL bFlag)
{
	int oldR=pDC->SetROP2(R2_XORPEN );
	CPen * pen;
	pen = new CPen(PS_SOLID, 1, RGB(255, 255,255));
/*	if (bFlag)
		 pen = new CPen(PS_SOLID, 1, RGB(255, 255,255));
	else
		 pen = new CPen(PS_SOLID, 1, RGB(0, 0,0));*/
	CPen * oldpen = pDC->SelectObject(pen);
	pDC->MoveTo(rect.left,rect.top );
	pDC->LineTo(rect.right,rect.top);
	pDC->LineTo(rect.right,rect.bottom );
	pDC->LineTo(rect.left,rect.bottom );
	pDC->LineTo(rect.left,rect.top );
	pDC->SelectObject(oldpen);
	delete pen;
}

void CModelView::SetGlint(Node *pNode)
{
	m_pNode=pNode;
	//��ʱ����
	CClientDC dc(this);
	
	pNode->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1,m_glintActive );
	CRgn rgn;
	rgn.CreateRectRgn(0,0,5,5);
	pNode->GetCom()->GetRgn((unsigned long)&rgn);
	CRect rect;
	rgn.GetRgnBox(rect);
	rect.InflateRect(5, 5);
	InvalidateRect(rect);
}
void CModelView::EndGlint() 
{
	m_glint=FALSE;
	m_glintActive=FALSE; 
	CClientDC dc(this);
	m_pNode->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1,FALSE );
	m_pNode=NULL;
	Invalidate();
}

void CModelView::ShowBim(CDC * pDC,CPoint &point,float fscale)
{
	CDC m_dcMem;
	CPaintDC m_sdc(this);

	m_dcMem.CreateCompatibleDC(&m_sdc);
	CBitmap * poldbmp = m_dcMem.SelectObject(&pBmp->m_cbitmap);

	pDC->BitBlt(point.x,point.y,(int)(pBmp->bitmap.bmWidth*fscale),(int)(pBmp->bitmap.bmHeight*fscale), 
	            &m_dcMem, 0, 0, SRCCOPY);

	
	m_dcMem.SelectObject(poldbmp);
	m_dcMem.DeleteDC();
	
}

void CModelView::SetBmpGlint(CDC *pDC)
{
	//CPoint point(point_bmps[11-index].x+bmpx-scrollpos.x,point_bmps[11-index].y+bmpy-scrollpos.y);
	if (pBmp==NULL)
		return;
	CPoint point(bmpx-scrollpos.x,bmpy-scrollpos.y);
	ShowBim(pDC,point,1.0);
}

BOOL CModelView::OnPreparePrinting(CPrintInfo* pInfo) 
{

	if (reportResult==1)
	{
	
		pInfo->SetMaxPage(1); //������ҳ��
		return DoPreparePrinting(pInfo);;
	}
	
	CDC dc;
	if (!AfxGetApp()->CreatePrinterDC(dc))
	{
		MessageBox("�������ô�ӡ,������Ĭ�ϼ����","����");
		return FALSE;
	}
	// ������Ļ��С��ֽ�ŵĴ�С�Լ���ӡҳ����
	dc.SaveDC();
	//�����ӵĴ�С����mm��ʾ��
	CPoint point((int)((MODELVIEW_MAX_X_RANGE/96)*25.4),(int)((MODELVIEW_MAX_Y_RANGE/96)*25.4));
//	int oldMap;
	numberOfPages=0;
	int xLogPix	= dc.GetDeviceCaps(HORZSIZE); //�õ�ֽ�ŵĴ�С
	int yLogPix	= dc.GetDeviceCaps(VERTSIZE);

	numCol=(int)((point.x+xLogPix-1)/xLogPix); //��������������
	numRow=(int)((point.y+yLogPix-1)/yLogPix);

	numberOfPages=numRow*numCol; // �ܵ�ҳ����
	
	pInfo->SetMaxPage(numberOfPages); //������ҳ��
 
	dc.DeleteDC();           
//	return bRet; 
	return DoPreparePrinting(pInfo);
}
void CModelView::OnFilePrint1() 
{
	// TODO: Add your command handler code here
	reportResult=0;
	CView::OnFilePrint();
}

void CModelView::OnFilePrintPreview1() 
{
	// TODO: Add your command handler code here
	reportResult=0;
	CView::OnFilePrintPreview();
}

void CModelView::OnPrintresult() 
{
	// TODO: Add your command handler code here

	//xnf print
	reportResult=1;
	CView::OnFilePrintPreview();
}
void CModelView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	
	if (reportResult==1)
	{
	
		CString head="��Ͻ���";		//ͷ
		CString text;					//����
		CString tail="�����ˣ�";		//����
		CTime time;
		CString timestr;
		time=CTime::GetCurrentTime();
		timestr = time.Format("%Y��%m��%d��%H:%M");
		pInfo->SetMaxPage(1); //������ҳ��




		//��ӡ��ǰҳ��
		LOGFONT lf1;
		::ZeroMemory(& lf1, sizeof(LOGFONT));
		_tcscpy(lf1.lfFaceName, _T("xxx"));
		lf1.lfHeight = 210;
		lf1.lfWeight = FW_BOLD;
		strcpy(lf1.lfFaceName, "Arial");
		CFont font;
		font.CreateFontIndirect(& lf1);
		CFont * pOldFont = (CFont *) pDC->SelectObject(& font);
		int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX); //Number of pixels per logical inch along the display width.
		int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
		int width,heigth;
		int xwidh = pDC->GetDeviceCaps(HORZSIZE); //�õ�ҳ���Сmm
		int xheigth = pDC->GetDeviceCaps(VERTSIZE);
		width = (int)(xwidh/25.4*xLogPixPerInch);
		heigth= (int)(xheigth/25.4*yLogPixPerInch);
		//setting of the text printed
		int oldMapMode=pDC->SetMapMode(MM_TEXT);
		pDC->TextOut((int)(width/2-460),600, head); //��ӡ����
		lf1.lfWeight = FW_NORMAL;
		lf1.lfHeight = 120;
		font.DeleteObject();
		font.CreateFontIndirect(& lf1);
		pDC->SelectObject(&font);
		//fqz
		text.Format("         %s��������%s��ģ��%s��������ϲ��ԡ�",timestr,m_sqlserver_db.user,m_cur_model_name);
		pDC->TextOut(180,1200, text); //��ӡ���ݣ�
		text.Format("         ���Խ��ۣ�%s",DiagnoseResult);
		pDC->TextOut(180,1400, text); //��ӡ���ݣ�


		
		lf1.lfWeight = FW_BOLD;
		lf1.lfHeight = 150;
		font.DeleteObject();		
		font.CreateFontIndirect(& lf1);
		pDC->SelectObject(&font);
		
		pDC->TextOut((int)(width-1500),heigth-1500, tail); //��ӡ
		pDC->SetMapMode(oldMapMode);
		if (pOldFont) pDC->SelectObject(pOldFont);
		return;	
	}	
	CString str;
	CPoint point;
	CString	text ;
	CSize	csText ;
	//��ӡ��ǰҳ��
	text.Format("PAGE %1d of %1d", pInfo->m_nCurPage, pInfo->GetMaxPage()) ;
	csText = pDC->GetTextExtent(text) ;
	LOGFONT lf1;
	//LOGFONT logFont; make the page mark
	::ZeroMemory(& lf1, sizeof(LOGFONT));
	_tcscpy(lf1.lfFaceName, _T("xxx"));
	lf1.lfHeight = 50;
	lf1.lfWeight = FW_BOLD;

	CFont font;
	font.CreateFontIndirect(& lf1);
	CFont * pOldFont = (CFont *) pDC->SelectObject(& font);

	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX); //Number of pixels per logical inch along the display width.
	int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);

	int width,heigth;
	int xwidh = pDC->GetDeviceCaps(HORZSIZE); //�õ�ҳ���Сmm
	int xheigth = pDC->GetDeviceCaps(VERTSIZE);
	width = (int)(xwidh/25.4*xLogPixPerInch);
	heigth= (int)(xheigth/25.4*yLogPixPerInch);
	//setting of the text printed
	int oldMapMode=pDC->SetMapMode(MM_TEXT);
	pDC->TextOut((int)(width-300),10, text); //��ӡҳü
	pDC->SetMapMode(oldMapMode);
	if (pOldFont) pDC->SelectObject(pOldFont);

	
	CSize size1=CSize(50,30);
	pDC->SetWindowExt(size1);
	//�õ��豸������߼�����ı���
	long xExt = (long)size1.cx * xLogPixPerInch/96;
	long yExt = (long)size1.cy * yLogPixPerInch/96;
	pDC->SetViewportExt((int)xExt,(int)yExt);


	int xorg,yorg;
	int x1,y1;
	x1=(int)((pInfo->m_nCurPage-1)%numCol); //���㶥�����������λ��
	y1=(int)((pInfo->m_nCurPage-1)/numCol); //���㶥�����������λ��
	xorg=(int)(x1*xwidh/25.4*96-scrollpos.x);
	yorg=(int)(y1*xheigth/25.4*96-scrollpos.y);
	pDC->SetWindowOrg(xorg,yorg);            //���ô�������
//	pDC->SetViewportOrg(0,0);            //���ô�������
	OnDraw(pDC);
	

}
void CModelView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{

	pDC->SetMapMode(MM_ANISOTROPIC);
	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
	ratio_x = (double) xLogPixPerInch / 96;
	ratio_y = (double) yLogPixPerInch / 96;
	pDC->SetWindowExt(MODELVIEW_MAX_X_RANGE,MODELVIEW_MAX_Y_RANGE);
	pDC->SetViewportExt( (int)(MODELVIEW_MAX_X_RANGE*ratio_x*oldPercentage),
		                 (int)(MODELVIEW_MAX_Y_RANGE*ratio_y*oldPercentage));
	// TODO: Add your specialized code here and/or call the base class

}

CString CModelView::GetMyDirectory()
{
	TCHAR sFilename[_MAX_PATH];
	TCHAR sDrive[_MAX_DRIVE];
	TCHAR sDir[_MAX_DIR];
	TCHAR sFname[_MAX_FNAME];
	TCHAR sExt[_MAX_EXT];
	GetModuleFileName(AfxGetInstanceHandle(), sFilename, _MAX_PATH);
	_tsplitpath(sFilename, sDrive, sDir, sFname, sExt);

	CString rVal(CString(sDrive) + CString(sDir));
	if (rVal.Right(1) != _T('\\'))
	rVal += _T("\\"); 

	return rVal;
} 




/*----------------------ADO��ȡ���͵�ת��----------------------*/
CString vartoCstr(const _variant_t &var)
{
	CString strValue;
	
	switch (var.vt)
	{
	case VT_BSTR://�ַ���
	case VT_LPSTR://�ַ���
	case VT_LPWSTR://�ַ���
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://������
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://�޷��Ŷ�����
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://����
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //����
		strValue.Format("%d", var.lVal);
		break;
	case VT_I8: //������
		strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://�޷�������
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //�޷�������
		strValue.Format("%d", var.ulVal);
		break;
	case VT_UI8: //�޷��ų�����
		strValue.Format("%d", var.ulVal);
		break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://������
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://˫������
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //С��
		strValue.Format("%.8f", (double)var);
		break;
	case VT_CY:
		{
			COleCurrency cy = var.cyVal;
			strValue = cy.Format();
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
	case 0x2011:
		strValue = "[BLOB]";
		break;
	case VT_BOOL://������

		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //������
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULLֵ
		strValue = "";
		break;
	case VT_EMPTY://��
		strValue = "";
		break;
	case VT_UNKNOWN://δ֪����
	default:
		strValue = "UN_KNOW";
		break;
	}
	return strValue;
}

char *vartochar(const _variant_t &var)
{
	CString strValue;
	char *result;

	switch (var.vt)
	{
	case VT_BSTR://�ַ���
	case VT_LPSTR://�ַ���
	case VT_LPWSTR://�ַ���
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://������
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://�޷��Ŷ�����
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://����
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //����
		strValue.Format("%d", var.lVal);
		break;
	case VT_I8: //������
		strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://�޷�������
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //�޷�������
		strValue.Format("%d", var.ulVal);
		break;
	case VT_UI8: //�޷��ų�����
		strValue.Format("%d", var.ulVal);
		break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://������
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://˫������
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //С��
		strValue.Format("%.8f", (double)var);
		break;
	case VT_CY:
		{
			COleCurrency cy = var.cyVal;
			strValue = cy.Format();
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
	case 0x2011:
		strValue = "[BLOB]";
		break;
	case VT_BOOL://������

		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //������
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULLֵ
		strValue = "";
		break;
	case VT_EMPTY://��
		strValue = "";
		break;
	case VT_UNKNOWN://δ֪����
	default:
		strValue = "UN_KNOW";
		break;
	}
	int length=strValue.GetLength();
	result=(char *)malloc(length+1);
	strcpy(result,strValue.GetBuffer(length));
	return result;
}

/*----------------------���ݽӿ�----------------------*/

//ע��: ����1��ӻ�ɾ�����, ����2��ӻ�ɾ�����ݽ��ʱ, ����ֵ�͵���֮����

//����: ���뵱ǰģ�����н�������
//���ݱ��е�curdata�ǵ�ǰģ�͵�����ֵ��: �����ŵ����Ĵ�������
void CModelView::load_all_nodes_data(CString curdatastr)
{
	_RecordsetPtr m_pRecordset;
	_variant_t type;
	ADO_LONGPTR record_count;
	char sql_cmd[200],buf[10];
	char *substr;
	int i;
	int node_count=NodeArray.GetSize();

	int length=curdatastr.GetLength();
	char *str=(char *)malloc(length+1);
	strcpy(str,curdatastr.GetBuffer(length));
	int pos=0;

	//��������ԭ�е���������
	for (i=0; i<node_count; i++ )
	{
		Node *node = NodeArray.GetAt(i);
		free_dataset(node->NodeData);
	}
	//NodeArrayҲ�ǰ����������,���Դ����������ֵ�Ĵ���
	for (i=0;i<node_count;i++)
	{
		Node *node=NodeArray.GetAt(i);
		itoa(node->GetID(),buf,10);
		strcpy(sql_cmd, "SELECT * FROM DATA_Table where ����=");
		strcat(sql_cmd, buf);
		strcat(sql_cmd, " and �����=");
		itoa(cur_task_id,buf,10);
		strcat(sql_cmd, buf);
		try
		{
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(sql_cmd,_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			HRESULT _hr = m_pRecordset->get_RecordCount(&record_count);
			node->NodeData.data_num=record_count;
			if (node->NodeData.data_num>0)
			{
				node->NodeData.datalist=(class_data *)malloc(sizeof(class_data)*node->NodeData.data_num);
				node->NodeData.data_num=0;
				while(!m_pRecordset->EndOfFile)
				{
					type = m_pRecordset->GetCollect("����������");
					node->NodeData.datalist[node->NodeData.data_num].type=vartochar(type);
					
					substr = get_str_from_str(str,pos," ",0);
					pos=pos+strlen(substr)+strlen(" ");
					node->NodeData.datalist[node->NodeData.data_num].value=atof(substr);
					free(substr);

					node->NodeData.data_num++;

					m_pRecordset->MoveNext();
				}
			}
			m_pRecordset.Release();
		}

		catch(_com_error e)///��׽�쳣
		{
			MessageBox("��ȡ���ݿ�ʧ��!","����");///��ʾ������Ϣ
		}
	}
	free(str);
}

//���ݽӿڣ���ȡĳ���������ݣ���dataset�ṹ�洢
class_dataset get_node_data(int node_no,CModelView *pModel)
{
	Node *node=pModel->Get_Node_In_NodeArray(node_no);
	return node->NodeData;
}

//�ͷ�dataset��ռ�ռ�
void CModelView::free_dataset(class_dataset dataset)
{
	int i;
	for (i=0;i<dataset.data_num;i++)
		free(dataset.datalist[i].type);
	if (dataset.data_num>0)
		free(dataset.datalist);
	dataset.data_num=0;
}

/*----------------------����������----------------------*/

//ĳ������ڵ�����������ת����һ�����š�����޷���ת�κν�㣬�򷵻�-1
class_reason_result CModelView::reason_one_node(int node_no)
{
//
	class_reason_result result;

	//ģ���������
	Sleep(2000L);
	result.next_node_no=-1; 
	result.exec_rule_id=-1;	//-1��ʾûƥ�䵽�κι���
	
	int ruleid,outnodeid;
	CString strrule;
	
	result.diagnose_type = "��������";
	if(Deduce().RegDeduce1Node(node_no,ruleid,strrule,outnodeid) == false)
	{
		result.diagnose_type = "ģ������";
		Deduce().BlurDeduce1Node(node_no,ruleid,strrule,outnodeid);
	}

	result.next_node_no= outnodeid; 
	result.exec_rule_id = ruleid;
	result.antecedent = strrule;

/*	class_reason_result result;
	int antecedent_result;
	int i;
	class_dataset dataset;
	class_rule r;
	
	
	//ģ���������
	Sleep(2000L);

	result.next_node_no=-1; 
	result.exec_rule_id=-1;	//-1��ʾûƥ�䵽�κι���

	dataset=get_node_data(node_no,this);
	if (dataset.data_num==0)//������?
		return result;

	//�����ý���ڸ�����һ�����������̷���
	_RecordsetPtr m_pRecordset;
	_variant_t rule_id,antecedent,goto_node_no;
	CString sql_cmd;
	char *substr;

	CString rule_table_name[2]={"CORRECTRULE_Table","WRONGRULE_Table"};

	for (i=0;i<2;i++)
	{
		sql_cmd.Format("SELECT * FROM %s where ����=%ld and �����=%ld",rule_table_name[i],node_no,cur_task_id);
		try
		{
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(LPCTSTR(sql_cmd),_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			while(!m_pRecordset->EndOfFile)
			{
				//��ȡ��ǰ����r
				rule_id = m_pRecordset->GetCollect("����ID��");
				antecedent = m_pRecordset->GetCollect("��������");
				goto_node_no = m_pRecordset->GetCollect("�������");
				
				substr=vartochar(rule_id);
				r.rule_id=atol(substr);
				free(substr);
				substr=vartochar(antecedent);
				//r.antecedent=str_to_antecedent(substr);
				
				pReasonCom->str_to_antecedent((unsigned long)substr,(unsigned long)&r.antecedent);
				free(substr);
				substr=vartochar(goto_node_no);
				r.goto_node_no=atoi(substr);
				free(substr);
				
				//����ǰ����r
				//ǰ����ĳν�ʲ��ɽ⣬������˵���ù���Ͳ��ɽ⣬����Ҫ�������ϵ
				//  �� ����ǰ��=С��(��ѹ,3.2)|����(����,2.1)
				//	 dataset={��ѹ=2}
				//	 datasetȱ�ٵ���������ֵ�����ù���ǰ����Ȼ�ǳ�����
				
				if (r.goto_node_no>=0 && Get_Node_In_NodeArray(r.goto_node_no)==NULL)
				{	//����ģʱ�ý�㱻ɾ����,�������ڣ���Ч��
					pReasonCom->free_rule((unsigned long)&r);
					m_pRecordset->MoveNext();
					continue;
				}
				pReasonCom->calculate_pred_expression((unsigned long)&r.antecedent,(unsigned long)&dataset, (unsigned long)&antecedent_result);
				if (antecedent_result==0)
				{
					pReasonCom->free_rule((unsigned long)&r);
					m_pRecordset->MoveNext();
					continue;
				}
				else
				{
					//���ǰ��Ϊ�棬���¼�����ʾ��㣬�˳�
					result.next_node_no=r.goto_node_no;
					result.exec_rule_id=r.rule_id;
					result.antecedent=vartoCstr(antecedent);
					pReasonCom->free_rule((unsigned long)&r);
					//ƥ������ʹ��Ƶ��+1
					long freq=atol(LPCTSTR(vartoCstr(m_pRecordset->GetCollect("ʹ��Ƶ��"))));
					m_pRecordset->PutCollect("ʹ��Ƶ��",_variant_t(long(freq+1)));
					m_pRecordset->Update();
					break;
				}
			}
			m_pRecordset.Release();
		}

		catch(_com_error e)///��׽�쳣
		{
			CString str;
			str.Format("��ȡ%sʧ��!",rule_table_name[i]);
			MessageBox(str,"����");///��ʾ������Ϣ
			return result;
		}
		if (result.exec_rule_id!=-1)
			break;
	}*/

	return result;
}

//ֹͣ��ǰ��˸�Ľ��Ͳ���
void CModelView::StopCurGlint()
{
	if (m_cGlint.IsActiveGlint())
	{
		Node *glintnode=m_cGlint.m_glintNode;
		m_cGlint.EndNode();
		EndNodeg(glintnode);
	}
	if (m_cGlint.IsActiveBmp())
	{
		int glintbmp=m_cGlint.m_bmpIndex;
		CClientDC dc(this);
		m_cGlint.EndBmp();
		//SetBmpGlint(&dc,glintbmp,FALSE);
	}
}

//��¼��ǰ�������������
void CModelView::SaveCurReasonStep(class_reason_result reason_result, Node *curNode)
{
	//��¼��ǰ���в���
	CString out_node_name;

	if (reason_result.exec_rule_id==-1)
	{
		out_node_name="��";
		reason_result.antecedent="��";
	}
	else
	{
		if (reason_result.next_node_no==-1)
			out_node_name="����";
		else if (reason_result.next_node_no==-2)
			out_node_name="����";
		else
			out_node_name=Get_Node_In_NodeArray(reason_result.next_node_no)->GetName();
	}
	
	reason_step[reason_step_count].task_id=cur_task_id;
	reason_step[reason_step_count].step_id=reason_step_count+1;
	reason_step[reason_step_count].rule_id=reason_result.exec_rule_id;
	reason_step[reason_step_count].node_id=cur_reason_node_no;
	reason_step[reason_step_count].node_name=curNode->GetName();
	reason_step[reason_step_count].comp_name=curNode->rgnName;
	reason_step[reason_step_count].out_node_name=out_node_name;
	reason_step[reason_step_count].rule_content=reason_result.antecedent;
	reason_step_count++;

	//��ʾ��׷��
	TipShowData curdata;
	curdata.step_id = reason_step_count;
	curdata.run_node_name = Get_Node_In_NodeArray(cur_reason_node_no)->GetName();
	curdata.diagnose_type = reason_result.diagnose_type;
	curdata.match_rule_id = reason_result.exec_rule_id;
	curdata.out_node_name = out_node_name;
	curdata.rule_content = reason_result.antecedent;
	curdata.diagnose_result = DiagnoseResult;
	view_pointer.pTip->DisplayItem(curdata);
}

//���������߳�
LRESULT CModelView::reason_one_thread(LPVOID pParam)
{
	//view_pointer.pDiagnose->m_nodename="test";
	//view_pointer.pModel->SendMessage(WM_RBUTTONUP);

	CString Prompt;
	class_reason_result reason_result;

	CModelView *pModel=view_pointer.pModel;
	
	//��ʼ��˸��ǰҪ����Ľ��
	pModel->m_cGlint.BeginNode(pModel->cur_reason_node);
	pModel->m_cGlint.BeginBmp(1);
	pModel->Invalidate();

	//�Ƴ����
	reason_result=pModel->reason_one_node(pModel->cur_reason_node_no);

	//�������ֹͣ��˸
	pModel->StopCurGlint();

	if (reason_result.exec_rule_id!=-1)
	{
		if (reason_result.next_node_no==-1)
		{
			Prompt.Format("%s����, ��Ϲ��̽���, û�з��ֹ���",pModel->cur_reason_node->GetName());
			DiagnoseResult="һ������";
		}
		else if (reason_result.next_node_no==-2)
		{
			Prompt.Format("%s���ֹ���, ��Ϲ��̽���",pModel->cur_reason_node->GetName());
			DiagnoseResult=pModel->cur_reason_node->rgnName+"���ֹ���";
		}
		else
		{
			Node *node=pModel->Get_Node_In_NodeArray(reason_result.next_node_no);
			Prompt.Format("%s�����й���, ��������",node->GetName());
			DiagnoseResult=node->rgnName+"�����й��ϣ��д����";
		}
	}
	else
	{
		Prompt.Format("%s����ƥ�����, ��Ϲ��̽���",pModel->cur_reason_node->GetName());
		DiagnoseResult.Format("%s����ƥ�����",pModel->cur_reason_node->GetName());
	}
	pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);//�洢���貢׷����ʾ��
	AfxMessageBox(Prompt);
	pModel->cur_reason_node_no=reason_result.next_node_no;//��ǰ���ı�
	pModel->hThread=NULL; //�߳̽���
	return 0L;
}

//�ಽ�����߳�
LRESULT CModelView::continue_reason_thread(LPVOID pParam)
{
	CString Prompt;
	class_reason_result reason_result;
	CModelView *pModel=view_pointer.pModel;
	CTreeCtrl * pTreeCtrl = &view_pointer.pTreeView->GetTreeCtrl();

	while (pModel->cur_reason_node_no>=0 && pModel->cur_reason_node!=NULL)
	{
		pTreeCtrl->SelectItem(view_pointer.pTreeView->m_Tree.TreeItem[Get_No_In_TreeNodeArray(pModel->cur_reason_node, view_pointer.pTreeView)]);

		view_pointer.pDiagnose->m_nodename=pModel->cur_reason_node->GetName();
		view_pointer.pDiagnose->m_compname=pModel->cur_reason_node->rgnName;
		view_pointer.pModel->SendMessage(WM_RBUTTONUP);

		//��ʼ��˸��ǰҪ����Ľ��
		pModel->m_cGlint.BeginNode(pModel->cur_reason_node);
		pModel->m_cGlint.BeginBmp(1);
		pModel->Invalidate();

		reason_result=pModel->reason_one_node(pModel->cur_reason_node_no);
		
		//ֹͣ��˸
		pModel->StopCurGlint();

		if (reason_result.exec_rule_id!=-1)
		{
			if (reason_result.next_node_no==-1)
			{
				DiagnoseResult="һ������";
				pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);
				Prompt.Format("%s����, ��Ϲ��̽���, û�з��ֹ���",pModel->cur_reason_node->GetName());
				AfxMessageBox(Prompt);
			}
			else if (reason_result.next_node_no==-2)
			{
				DiagnoseResult=pModel->cur_reason_node->rgnName+"���ֹ���";
				pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);
				Prompt.Format("%s���ֹ���, ��Ϲ��̽���",pModel->cur_reason_node->GetName());
				AfxMessageBox(Prompt);
			}
			else
			{
				DiagnoseResult=pModel->Get_Node_In_NodeArray(reason_result.next_node_no)->rgnName+"�����й��ϣ��д����";
				pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);
			}
		}
		else
		{
			DiagnoseResult.Format("%s����ƥ�����",pModel->cur_reason_node->GetName());
			pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);//��ʾ��ʾ������
			Prompt.Format("%s����ƥ�����, ��Ϲ��̽���",pModel->cur_reason_node->GetName());
			AfxMessageBox(Prompt);
		}
		pModel->cur_reason_node_no=reason_result.next_node_no;
		pModel->cur_reason_node=pModel->Get_Node_In_NodeArray(pModel->cur_reason_node_no);
	}
	pModel->hThread=NULL;
	return 0L;
}

void CModelView::ReasonOnestep()
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("����ѡ��һ��ģ��!","��ʾ");
		return;
	}
	if (import_data_flag==FALSE)
	{
		MessageBox("���ȵ�������������","��ʾ");
		return;
	}

	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CTipView *pTip = (CTipView *)pFWnd->m_wndSplitter3.GetPane(1,0);
	CModelTree *pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl * pTreeCtrl = &pTreeView->GetTreeCtrl();
	CDiagnoseView *pDiagnose = (CDiagnoseView *)pFWnd->m_wndSplitter1.GetPane(0,0);
	view_pointer.pDiagnose=pDiagnose;
	view_pointer.pModel=this;
	view_pointer.pTip=pTip;
	view_pointer.pTreeView=pTreeView;

	CString Prompt;

	//����û�ѡ����һ����㣬��Ӹý�㿪ʼ�����������һ�������㿪ʼ
	if (curObject!=NULL && curObject->IsKindOf(RUNTIME_CLASS(Node)))
	{
		cur_reason_node=(Node *)curObject;
		cur_reason_node_no=cur_reason_node->GetID();
		cur_reason_node->SetActive(false);
		SelectedObjects.RemoveAll();
		curObject=NULL;
		Invalidate();
		reason_step_count=0; //�����ǰ���������
		pTip->ClearTipData();
	}
	else
	{
		if (cur_reason_node_no<0)
		{
			MessageBox("��Ϲ����Ѿ���������������ϣ��������С��뵥�����ԣ�����ѡ����!","��ʾ");
			return;
		}
		else
		{
			if ((cur_reason_node=Get_Node_In_NodeArray(cur_reason_node_no))==NULL)
			{
				CString prompt;
				prompt.Format("�����ڽ��%d",cur_reason_node_no);
				MessageBox(prompt,"��ʾ");
				return;
			}
		}
	}

	pTreeCtrl->SelectItem(NodetoItem(cur_reason_node));
	pDiagnose->m_nodename=cur_reason_node->GetName();
	pDiagnose->m_compname=cur_reason_node->rgnName;
	pDiagnose->UpdateData(false);

	hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)reason_one_thread,NULL,0,&dwThreadId);
	if(hThread==NULL)
		AfxMessageBox("���������߳�ʧ��!");
}

void CModelView::ContinueReason() 
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("����ѡ��һ��ģ��!","��ʾ");
		return;
	}
	if (import_data_flag==FALSE)
	{
		MessageBox("���ȵ�������������","��ʾ");
		return;
	}

	//����һ�������㿪ʼ
	if (cur_reason_node_no<0)
	{
		MessageBox("��Ϲ����Ѿ���������������ϣ��������У��뵥�����ԣ�����ѡ����!","ע��");
		return;
	}
	else
		cur_reason_node=Get_Node_In_NodeArray(cur_reason_node_no);
	
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CDiagnoseView *pDiagnose = (CDiagnoseView *)pFWnd->m_wndSplitter1.GetPane(0,0);
	CTipView *pTip = (CTipView *)pFWnd->m_wndSplitter3.GetPane(1,0);
	CModelTree *pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	view_pointer.pDiagnose=pDiagnose;
	view_pointer.pModel=this;
	view_pointer.pTip=pTip;
	view_pointer.pTreeView=pTreeView;

	hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)continue_reason_thread,NULL,0,&dwThreadId);
	if(hThread==NULL)
		AfxMessageBox("���������߳�ʧ��!");
}

void CModelView::ReasonAll() 
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("����ѡ��һ��ģ��!","��ʾ");
		return;
	}
	if (import_data_flag==FALSE)
	{
		MessageBox("���ȵ�������������","��ʾ");
		return;
	}

	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CTipView *pTip = (CTipView *)pFWnd->m_wndSplitter3.GetPane(1,0);
	pTip->ClearTipData();

	//�û�Ҫѡ��һ����㿪ʼ����
	if (curObject!=NULL && curObject->IsKindOf(RUNTIME_CLASS(Node)))
	{
		cur_reason_node=(Node *)curObject;
		cur_reason_node_no=cur_reason_node->GetID();
		cur_reason_node->SetActive(false);
		SelectedObjects.RemoveAll();
		curObject=NULL;
		Invalidate();
		reason_step_count=0; //�����ǰ���������
		pTip->ClearTipData();
		ContinueReason();
	}
	else
		MessageBox("����ѡ����Ҫ��ʼ����Ľ��","��ʾ");
	
}

void CModelView::OnDataSave() 
{
	// TODO: Add your command handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	if (reason_step_count==0)
		MessageBox("��ǰ��������Ϊ�գ�ûʲô�ɱ����!","��ʾ");
	else	
	{
		save_reason_steps_to_DB();
		MessageBox("������̳ɹ����浽����������ݱ���","�ɹ�");
	}
}

//����ָ��������ֶ��б����ļ���ʽ��������ر�������
CString CModelView::ReportOut_by_File()
{
	CString report,currecord,fieldname,value;
	int i,j;

	int reportfieldcount=ReportOutFields.GetSize();
	for (i=0;i<reason_step_count;i++)
	{
		currecord="";
		for (j=0;j<reportfieldcount;j++)
		{
			fieldname=ReportOutFields.GetAt(j);
			if (fieldname=="�����")
				value.Format("%ld",reason_step[i].task_id);
			else if (fieldname=="�����")
				value.Format("%ld",reason_step[i].step_id);
			//else if (fieldname=="����")
			//	value.Format("%ld",reason_step[i].node_id);
			else if (fieldname=="�������")
				value=reason_step[i].node_name;
			else if (fieldname=="��������")
				value=reason_step[i].comp_name;
			else if (fieldname=="�����")
				value.Format("%ld",reason_step[i].rule_id);
			else if (fieldname=="������")
				value=reason_step[i].out_node_name;
			currecord=currecord+fieldname+"="+value+"\n";
		}
		if (report!="")
			report=report+"\n";
		report=report+currecord;
	}
	report=report+"\n"+"��Ͻ��ۣ�"+DiagnoseResult;
	return report;
}

//����ָ��������ֶ��б���XML��ʽ��������ر�������
CString CModelView::ReportOut_by_XML()
{
	CString report,currecord,fieldname,value;
	int i,j;

	report="<?xml version=\"1.0\" encoding=\"GB2312\" ?>\n";
	report=report+"\t<������>\n";
	int reportfieldcount=ReportOutFields.GetSize();
	for (i=0;i<reason_step_count;i++)
	{
		currecord="\t\t<����>\n";
		for (j=0;j<reportfieldcount;j++)
		{
			fieldname=ReportOutFields.GetAt(j);
			if (fieldname=="�����")
				value.Format("%ld",reason_step[i].task_id);
			else if (fieldname=="�����")
				value.Format("%ld",reason_step[i].step_id);
			//else if (fieldname=="����")
			//	value.Format("%ld",reason_step[i].node_id);
			else if (fieldname=="�������")
				value=reason_step[i].node_name;
			else if (fieldname=="��������")
				value=reason_step[i].comp_name;
			else if (fieldname=="�����")
				value.Format("%ld",reason_step[i].rule_id);
			else if (fieldname=="������")
				value=reason_step[i].out_node_name;
			currecord=currecord+"\t\t\t"+"<"+fieldname+">"+value+"</"+fieldname+">"+"\n";
		}
		currecord=currecord+"\t\t</����>\n";
		report=report+currecord;
	}
	report=report+"\t</������>";
	return report;
}

void CModelView::ReportOut() 
{
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}

	// TODO: Add your control notification handler code here
	CString report;
	if (m_cur_model_name=="")
	{
		MessageBox("����ѡ��һ��ģ��!","��ʾ");
		return;
	}
	
	CReportShowDlg dlg;
	dlg.DoModal();
}

void CModelView::OnReportdefine() 
{
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}

	// TODO: Add your command handler code here
	CReportDefDlg dlg;
	int i;
	CString fieldname;
	int reportfieldcount=ReportOutFields.GetSize();
	for (i=0;i<reportfieldcount;i++)
	{
		fieldname=ReportOutFields.GetAt(i);
		if (fieldname=="�����")
			dlg.m_task_id=TRUE;
		//else if (fieldname=="����")
		//	dlg.m_node_id=TRUE;
		else if (fieldname=="�������")
			dlg.m_node_name=TRUE;
		else if (fieldname=="��������")
			dlg.m_comp_name=TRUE;
		else if (fieldname=="�����")
			dlg.m_rule_id=TRUE;
		else if (fieldname=="������")
			dlg.m_outnode=TRUE;
	}
	if (dlg.DoModal()==IDCANCEL)
		return;

	ReportOutFields.RemoveAll();
	ReportOutFields.Add("�����");
	if (dlg.m_task_id==TRUE)
		ReportOutFields.Add("�����");
	//if (dlg.m_node_id==TRUE)
		//ReportOutFields.Add("����");
	if (dlg.m_node_name==TRUE)
		ReportOutFields.Add("�������");
	if (dlg.m_comp_name==TRUE)
		ReportOutFields.Add("��������");
	if (dlg.m_rule_id==TRUE)
		ReportOutFields.Add("�����");
	if (dlg.m_outnode==TRUE)
		ReportOutFields.Add("������");
}

void CModelView::ShowData() 
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("����ѡ��һ��ģ��!","��ʾ");
		return;
	}
	CSelectDataDlg dlg;
	if ( dlg.DoModal() == IDCANCEL )
		return;

	//load_all_nodes_data(dlg.m_select_data);
	Deduce().GetRecordSet(dlg.m_select_data);
	import_data_flag=TRUE;
	MessageBox("���ݵ���ɹ���");
}




void CModelView::OnReportout() 
{
	// TODO: Add your command handler code here
	ReportOut();
}

void CModelView::OnOnestep() 
{
	// TODO: Add your command handler code here
	ReasonOnestep();
}

void CModelView::OnContinue() 
{
	// TODO: Add your command handler code here
	ContinueReason();
}

void CModelView::OnLine() 
{
	// TODO: Add your command handler code here
	ReasonAll();
}


void CModelView::OnAutoget() 
{
	// TODO: Add your command handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	MessageBox("�����Զ���ȡ");
}

void CModelView::OnManget() 
{
	// TODO: Add your command handler code here
	if(hThread)
	{
		MessageBox("��ǰ�������ڽ��У����Ժ�����!","����");
		return;
	}
	MessageBox("�����ֹ���ȡ");
}

void CModelView::OnUpdateDataSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateReportdefine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateReportout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

void CModelView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}


void CModelView::OnUpdateOnestep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

void CModelView::OnUpdateContinue(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}


void CModelView::OnUpdateAutoget(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

void CModelView::OnUpdateManget(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdateSelectmodel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CModelView::OnUpdatePrintresult(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread || DiagnoseResult=="")
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

//xnf zoom
void CModelView::OnZoom(UINT nID)
{
	oldPercentage=m_DefaultPresets[nID - ID_ZOOM_FIRST];
	Invalidate();
}
void CModelView::OnUpdateZoom(CCmdUI *pCmdUI)
{
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(pCmdUI->m_nID - ID_ZOOM_FIRST == (UINT) GetPresetZoom());
	}
}

int CModelView::GetPresetZoom()
{
	for(int i=0;i<6;i++)
	{
		if(m_DefaultPresets[i]==oldPercentage)
		     return i;
	}
	return -1;
}

void CModelView::OnZoomOther() 
{
	// TODO: Add your command handler code here
	CZoomLevelDlg dlg;
	dlg.m_ZoomPercentage = (int)(100.0f * oldPercentage);

	if (dlg.DoModal() == IDOK)
	{
		oldPercentage=dlg.m_ZoomPercentage / 100.0f;
		Invalidate();
	}	
}

void CModelView::OnZoomZoomin() 
{
	// TODO: Add your command handler code here
	oldPercentage=oldPercentage*0.9;
	Invalidate();
}

void CModelView::OnZoomZoomout() 
{
	// TODO: Add your command handler code here
	oldPercentage=oldPercentage*1.1;
	Invalidate();
}

void CModelView::OnFullGraph()
{
	// TODO: Add your command handler code here
	CRect rectClient;
	GetClientRect(&rectClient);
	float vRate, hRate;
	CRect r=CalModelGraphRect();
	CClientDC dc(this);
	OnPrepareDC(&dc);

	double width,height;
	if (pBmp==NULL)
	{
		width=r.Width();
		height=r.Height();
	}
	else
	{
		width=r.Width()<pBmp->bitmap.bmWidth?pBmp->bitmap.bmWidth:r.Width();
		height=r.Height()+pBmp->bitmap.bmHeight+(int)(20*oldPercentage);  //����bmp��height
	}
	hRate = width/rectClient.Width();
	vRate = height/rectClient.Height();

	if(hRate<vRate)
		hRate=vRate;
	oldPercentage=1.0/hRate;
	
	if (fullgraph_times!=0)
	{
		CPoint pos(r.left+scrollpos.x,r.top+scrollpos.y);
		scrollpos = pos;
		SetScrollPos(SB_VERT, pos.y, TRUE);
		SetScrollPos(SB_HORZ, pos.x, TRUE);
	}
	else
		fullgraph_times++;

	Invalidate();
}

void CModelView::OnUpdateZoomZoomin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

void CModelView::OnUpdateZoomZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

void CModelView::OnUpdateFullGraph(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

void CModelView::OnUpdateZoomOther(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_cur_model_name=="" || hThread)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);	
}

BOOL CModelView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
	if ( zDelta < 0 )
		scrollpos.y += MODELVIEW_Y_LINE;
	else
		if ( zDelta > 0 )
			scrollpos.y -= MODELVIEW_Y_LINE;

	if ( scrollpos.y < 0 )
		scrollpos.y = 0;

	if ( scrollpos.y > MODELVIEW_MAX_Y_RANGE )
		scrollpos.y = MODELVIEW_MAX_Y_RANGE;

	SetScrollPos(SB_VERT, scrollpos.y, TRUE);
	
	//modified = true;
	Invalidate(TRUE);	

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CModelView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	//#define VK_LEFT           0x25
	//#define VK_UP             0x26
	//#define VK_RIGHT          0x27
	//#define VK_DOWN           0x28
	//#define VK_LSHIFT         0xA0
	//#define VK_RSHIFT         0xA1
	//#define VK_LCONTROL       0xA2
	//#define VK_RCONTROL       0xA3
	//#define VK_PRIOR          0x21
	//#define VK_NEXT           0x22
	/*
	�����ƶ��������ķ���
	switch ( nChar )
	{
		case VK_LEFT: scrollpos.x -= MODELVIEW_X_LINE;
					break;
		case VK_UP: scrollpos.y -= MODELVIEW_Y_LINE;
					break;
		case VK_RIGHT: scrollpos.x += MODELVIEW_X_LINE;
					break;
		case VK_DOWN: scrollpos.y += MODELVIEW_Y_LINE;
					break;
	}

	SetScrollPos(SB_VERT, scrollpos.y, TRUE);
	SetScrollPos(SB_HORZ, scrollpos.x, TRUE);
	*/

	//�ƶ��������
	CClientDC dc(this);
	OnPrepareDC(&dc);
	int count = 0,
		i = 0;
	ModelObject * pModelOjbect = NULL;
	CPoint offset(0,0);
	BOOL flag = FALSE;

	switch ( nChar )
	{
		case VK_LEFT: flag = TRUE;
					offset.x -= 5;	//MODELVIEW_X_LINE;
					break;
		case VK_UP: flag = TRUE;
					offset.y -= 5;	//MODELVIEW_Y_LINE;
					break;
		case VK_RIGHT: flag = TRUE;
					offset.x += 5;	//MODELVIEW_X_LINE;
					break;
		case VK_DOWN: flag = TRUE;
					offset.y += 5;	//MODELVIEW_Y_LINE;
					break;
		case VK_PRIOR: scrollpos.y -= MODELVIEW_Y_LINE;
						break;
		case VK_NEXT: scrollpos.y += MODELVIEW_Y_LINE;
						break;
		default : return ;
	}

	//modified = true;
	
	if ( !flag )
	{
		if ( scrollpos.y < 0 )
			scrollpos.y = 0;

		if ( scrollpos.y > MODELVIEW_MAX_Y_RANGE )
			scrollpos.y = MODELVIEW_MAX_Y_RANGE;
		
		SetScrollPos(SB_VERT, scrollpos.y, TRUE);
		SetScrollPos(SB_HORZ, scrollpos.x, TRUE);
		Invalidate(TRUE);
		return ;
	}

	count = SelectedObjects.GetSize();
	Line * pLine = NULL;
	int cc = 0,
		ii = 0;
	CPoint topcenter, bottomcenter;
	for (i=0; i<count; i++)
	{
		pModelOjbect = SelectedObjects.GetAt(i);
		if ( !pModelOjbect->IsKindOf(RUNTIME_CLASS(Node)) )
			continue;
		pModelOjbect->DrawOffset(&dc, offset, scrollpos, m_model_scale, NULL, 1, 1);

		if ( ((Node *)pModelOjbect)->inLine != NULL )
		{
			((Node *)pModelOjbect)->GetTopCenter(topcenter);
			((Node *)pModelOjbect)->inLine->SetEndPoint(topcenter);
		}
		
		cc = ((Node *)pModelOjbect)->outLine.GetSize();
		((Node *)pModelOjbect)->GetBottomCenter(bottomcenter);
		for ( ii=0; ii<cc; ii++ )
		{
			pLine = ((Node *)pModelOjbect)->outLine.GetAt(ii);
			pLine->SetStartPoint(bottomcenter);
		}
	}

	Invalidate(TRUE);
}

