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
extern BOOL mousemoving;							//鼠标是否在移动过程中
extern BOOL mousedown;								//鼠标是否点下，并且尚未释放

CMyBmp * pBmp = NULL;
CString BmpPath="";
double xScale = 0.0,
	   yScale = 0.0;

//10.20添加
int com_count=9;
const CLSID * CLSIDArray[] = {	&CLSID_MyCom1, &CLSID_MyCom2, &CLSID_MyCom3, &CLSID_MyCom4,
								&CLSID_MyCom5, &CLSID_MyCom6, &CLSID_MyCom11, &CLSID_MyCom12, &CLSID_MyLineCom};
const IID * IIDArray[] = {	&IID_IMyCom1, &IID_IMyCom2, &IID_IMyCom3, &IID_IMyCom4,
							&IID_IMyCom5, &IID_IMyCom6,	&IID_IMyCom11, &IID_IMyCom12, &IID_IMyLineCom};

float m_DefaultPresets[6]={0.35F, 0.5F, 0.7F, 1.0F,1.4F, 2.4F};

//view结构
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

//得到某个结点的image号
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

	reason_data_field_list.Add("任务号");
	reason_data_field_list.Add("步骤号");
	reason_data_field_list.Add("结点号");
	reason_data_field_list.Add("规则号");
	reason_data_field_list.Add("规则内容");
	reason_data_field_list.Add("输出结点");

	ReportOutFields.Add("步骤号");
	ReportOutFields.Add("任务号");
	//ReportOutFields.Add("结点号");
	ReportOutFields.Add("结点名称");
	ReportOutFields.Add("部件名称");
	ReportOutFields.Add("规则号");
	ReportOutFields.Add("输出结点");

	m_cur_model_name="";
	cur_reason_node_no=0;
	import_data_flag=FALSE;

	HRESULT hr;
	hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象

	//读输入文件
	CString strFile="user_info.txt";
	CStdioFile file;
	CFileException e;
	CString str;
	int length;
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone,&e);
	while(file.ReadString(str)!=NULL)
	{
		length=str.GetLength();
		if (str.Find("数据源=")==0)
		{
			m_sqlserver_db.dbsrc=str.Right(length-strlen("数据源="));
			m_sqlserver_db.dbsrc.TrimLeft();
			m_sqlserver_db.dbsrc.TrimRight();
		}
		else if (str.Find("用户名=")==0)
		{
			m_sqlserver_db.user=str.Right(length-strlen("用户名="));
			m_sqlserver_db.user.TrimLeft();
			m_sqlserver_db.user.TrimRight();
		}
		else if (str.Find("密码=")==0)
		{
			m_sqlserver_db.pass=str.Right(length-strlen("密码="));
			m_sqlserver_db.pass.TrimLeft();
			m_sqlserver_db.pass.TrimRight();
		}
		else if (str.Find("任务号=")==0)   //设置当前任务号
		{
			cur_task_id=atol(str.Right(length-strlen("任务号=")));
		}
	}
	file.Close();

	//验证用户名、密码是否正确
	try
	{
		CString Datasource;
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=\"\"; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
		hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
		m_pConnection->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		MessageBox("无法连接sqlserver数据库，请检查你的用户名、密码和数据源是否正确","错误");///显示错误信息
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
		MessageBox("创建COM错误");
		exit (1);
	}

}

CModelView::~CModelView()
{
	if(m_pConnection->State)
		 m_pConnection->Close(); ///如果已经打开了连接则关闭它
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
//xnf 导弹模拟图
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
//判断parent和son之间是否出现了循环
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
	
	if(m_ctltree.ItemHasChildren(Item)==TRUE)//有孩子
	{
		NextItem=m_ctltree.GetChildItem(Item);
		return TRUE;
	}
	else
	{
		NextItem=m_ctltree.GetNextSiblingItem(Item);
		if(NextItem!=NULL)//无孩子，有兄弟
			return TRUE;
		else//无孩子，无兄弟
		{
			do
			{
				Item=m_ctltree.GetParentItem(Item);
				if(Item==m_ctltree.GetRootItem())
				{
					return FALSE;
				}
				
				tempItem=m_ctltree.GetNextSiblingItem(Item);
				if(tempItem!=NULL)//有父亲的兄弟
				{NextItem=tempItem;
				return TRUE;}
			}
			while(tempItem==NULL);//如果没有父亲的兄弟，继续循环
		}
	}
	return FALSE;
}

//要求startItem和Item有直接或者间接的父子关系
int GetOffSet(HTREEITEM startItem, HTREEITEM Item)
{
	//0表示startItem是Item的直系父亲
	//>0为间接父亲
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

//注意：要求startItem和Item有直接或者间接的父子关系
//返回为startItem和Item的之间距离
int GetOffSetLength(HTREEITEM startItem, HTREEITEM Item)
{
	//使用前提：GetOffSet(HTREEITEM startItem, HTREEITEM Item)>=0
	//返回值n表示Item为startItem第n个（下一个节点）
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

//把一段有父子关系的Tree部分移走
void MoveItem(HTREEITEM m_startItem, HTREEITEM pItem, HTREEITEM nItem)
{
	//详见司晋新okee程序中的Ctestview类
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
	HTREEITEM Item,nextItem,m_tempParentItem,lItem,m_temppItem;
	int no;

	no=Get_No_In_TreeItem(m_startItem,pTreeView);
	int imageno1,imageno2;
	m_ctlTree.GetItemImage(m_startItem,imageno1,imageno2);
	Item=m_ctlTree.InsertItem(m_ctlTree.GetItemText(m_startItem),imageno1,imageno2,pItem,nItem);
	//fqz: 修改treeitem
	pTreeView->m_Tree.TreeItem[no]=Item;
	lItem=m_startItem;//m_startItem值在以下循环中不变
	nItem=Item;
	pItem=Item;
	m_temppItem=pItem;//m_temppItem值不变
	while(FindNextNode(lItem,nextItem)!=FALSE)//查找下一个Node
	{
		//如果nextItem的父亲或者父亲的父亲是m_startItem;
		BOOL isParent=FALSE;
		m_tempParentItem=nextItem;
		//得到在nextItem的父亲在m_startItem位置
		int indent=GetOffSet(m_startItem,nextItem);
		pItem=m_startItem;
		if(indent>0)//如果存在间接父子关系
		{
			pItem=m_temppItem;
			for(int i=1;i<=GetOffSetLength(m_startItem,m_ctlTree.GetParentItem(nextItem));i++)
				FindNextNode(pItem,pItem);
		}
		else if(indent==0)//如果m_startItem和nextItem存在直接父子关系
		{
			pItem=m_temppItem;
		}
		else if(indent==-1)
			break;
		no=Get_No_In_TreeItem(nextItem,pTreeView);
		int imageno1,imageno2;
		m_ctlTree.GetItemImage(nextItem,imageno1,imageno2);
		nItem=m_ctlTree.InsertItem(m_ctlTree.GetItemText(nextItem),imageno1,imageno2,pItem,nItem);
		//fqz: 修改treeitem
		pTreeView->m_Tree.TreeItem[no]=nItem;
		lItem=nextItem;
	}
	m_ctlTree.DeleteItem(m_startItem);
}


/*            The following codes were added by fqz!!!        */

//测试：显示各结点的层号
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

//根据结点号查找node
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

//根据结点指针查找其在整个treeview中对应的item
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

//把一段有父子关系的Tree移动到新父亲结点的末尾
void MoveItemToLast(HTREEITEM m_startItem, HTREEITEM pItem)
{
	HTREEITEM tempItem,nItem;
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
	CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();

	nItem=m_ctlTree.GetChildItem(pItem);//得到第一个子节点
	tempItem=nItem;
	while(nItem!=NULL)//如果存在子节点
	{
		nItem=tempItem;
		tempItem=m_ctlTree.GetNextSiblingItem(nItem);//得到下一个兄弟节点
	}
	MoveItem(m_startItem, pItem, nItem);
}

//将原层号为layer的pNode为首的子树变为一棵树
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

//将pNode为首的树变为一棵子树，层号提升layer
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
	m_pConnection0.CreateInstance("ADODB.Connection");///创建Connection对象
	try
	{
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,model_name,m_sqlserver_db.user,m_sqlserver_db.pass);
		m_pConnection0->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	}
	catch(_com_error e)///捕捉异常
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

	//连接模型列表数据库
	if (!if_connect_model(modellist_name))
	{
		//没有模型列表数据库，说明当前没有任何模型
		try
		{
			//创建模型列表数据库
			Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=\"\"; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
			hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
			strcpy(sql_cmd,"create database ");
			strcat(sql_cmd,modellist_name);
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(sql_cmd, _variant_t((IDispatch*)m_pConnection, true),adOpenDynamic,adLockOptimistic,adCmdText);
			m_pRecordset.Release();
			m_pConnection->Close();
	
			//连接模型列表数据库
			Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,modellist_name,m_sqlserver_db.user,m_sqlserver_db.pass);
			hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	
			//创建表
			strcpy(sql_cmd,"create table MODELLIST_Table(模型名 varchar(30))");
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(sql_cmd, _variant_t((IDispatch*)m_pConnection, true),adOpenDynamic,adLockOptimistic,adCmdText);
			m_pRecordset.Release();

			m_pConnection->Close();
		}
		catch(_com_error e)///捕捉异常
		{
			if (m_pRecordset!=NULL)
				m_pRecordset.Release();
			if(m_pConnection->State)
				m_pConnection->Close();
			MessageBox("创建ModelList数据库失败，该库已存在或用户无创建权限!","错误");///显示错误信息
			return false;
		}
	}
	else
	{
		//读取模型列表
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,modellist_name,m_sqlserver_db.user,m_sqlserver_db.pass);
		m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("MODELLIST_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdTable);
		while(!m_pRecordset->EndOfFile)
		{
			ModelArray.Add(vartostr(m_pRecordset->GetCollect("模型名")));
			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
		m_pConnection->Close();
	}
	
	return true;
}


/*----------------------ADO读取类型的转换----------------------*/
CString CModelView::vartostr(const _variant_t &var)
{
	CString strValue;
	
	switch (var.vt)
	{
	case VT_BSTR://字符串
	case VT_LPSTR://字符串
	case VT_LPWSTR://字符串
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://短整型
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://无符号短整型
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://整型
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //整型
		strValue.Format("%d", var.lVal);
		break;
	case VT_I8: //长整型
		strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://无符号整型
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //无符号整型
		strValue.Format("%d", var.ulVal);
		break;
	case VT_UI8: //无符号长整型
		strValue.Format("%d", var.ulVal);
		break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://浮点型
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://双精度型
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //小数
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
	case VT_BOOL://布尔型

		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //日期型
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULL值
		strValue = "";
		break;
	case VT_EMPTY://空
		strValue = "";
		break;
	case VT_UNKNOWN://未知类型
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

//执行一条sql语句
BOOL CModelView::exec_sql(char *sql_cmd)
{
	try
	{
		return SUCCEEDED(m_pRecordset->Open(sql_cmd, _variant_t((IDispatch*)m_pConnection, true),adOpenDynamic,adLockOptimistic,adCmdText));
	}
	catch (_com_error e)
	{
		TRACE(_T("Warning: 打开记录集发生异常. 错误信息: %s; 文件: %s; 行: %d\n"), e.ErrorMessage(), __FILE__, __LINE__);
		return FALSE;
	}
}

//一个model是一个库

//读入一个模型
BOOL CModelView::read_one_model(CString model_name)
{
	char sql_cmd[500],buf[10];

	m_sqlserver_db.dbname=model_name;

	CClientDC dc(this);

	try
	{
		CString Datasource;
		Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
		HRESULT hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
		//上面一句中连接字串中的Provider是针对SQL Server环境的
	}
	catch(_com_error e)///捕捉异常
	{
		CString Prompt;
		Prompt.Format("连接数据库%s失败，请检测你的数据库用户名和口令是否正确!",model_name);
		MessageBox(Prompt,"错误");///显示错误信息
		return false;
	}
	
	/*读入数据*/

	//读MODELSET_Table
	try
	{
		strcpy(sql_cmd, "SELECT * FROM MODELSET_Table where 任务号=");
		itoa(cur_task_id,buf,10);
		strcat(sql_cmd, buf);
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(sql_cmd,_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		if (!m_pRecordset->EndOfFile)
		{
			BmpPath=vartostr(m_pRecordset->GetCollect("部件图片路径"));
			oldPercentage=atof(vartostr(m_pRecordset->GetCollect("缩放比例")));
			xScale=atof(vartostr(m_pRecordset->GetCollect("图片X缩放比例")));
			yScale=atof(vartostr(m_pRecordset->GetCollect("图片Y缩放比例")));
			
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
	catch(_com_error e)///捕捉异常
	{
		if (m_pRecordset!=NULL)
			m_pRecordset.Release();
		MessageBox("读取模型库中的模型属性表失败!","错误");///显示错误信息
		return false;
	}

	//读结点表
	try
	{
		strcpy(sql_cmd, "SELECT * FROM NODES_Table where 任务号=");
		itoa(cur_task_id,buf,10);
		strcat(sql_cmd, buf);
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open(sql_cmd,_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		while(!m_pRecordset->EndOfFile)
		{
			long value;
			IBaseCom * pCom = NULL;

			int com_no=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("图形形状"))));
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
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("结点号"))));
			node_id_count=value+1;
			node->SetID(value);
			//m_pRecordset->GetCollect("任务号");
			//node->obj_id=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("对象序号"))));
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("层号"))));
			node->layer=value;
			//m_pRecordset->GetCollect("层中序号");
			//m_pRecordset->GetCollect("父结点号");
			node->inLine=NULL;
			node->SetName(vartostr(m_pRecordset->GetCollect("结点名称")));
			//m_pRecordset->GetCollect("结点中文名称");
			node->comment=vartostr(m_pRecordset->GetCollect("结点描述"));
			
			CPoint pos1, pos2;
			pos1.x=scrollpos.x;
			pos1.y=scrollpos.y;
			pos2.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("X坐标"))))-scrollpos.x;
			pos2.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("Y坐标"))))-scrollpos.y;
			node->SetScrPos(pos1);
			node->SetTopLeft(pos2);

			//m_pRecordset->GetCollect("图形线型");
			//m_pRecordset->GetCollect("图形线宽");
			m_model_scale=atof(vartostr(m_pRecordset->GetCollect("比例")));

			GraphInfo * gi = node->GetGraphInfo();
			//m_pRecordset->GetCollect("图形颜色"))));
			gi->textcolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("字体颜色"))));
			gi->pointsize=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("字号"))));
			CString lfstr=vartostr(m_pRecordset->GetCollect("字体"));
			if (lfstr!="")
			{
				LOGFONT lf;
				sscanf(lfstr,"%ld,%ld,%ld,%ld,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%s",&lf.lfHeight,&lf.lfWidth,&lf.lfEscapement,&lf.lfOrientation,&lf.lfWeight,&lf.lfItalic,&lf.lfUnderline,&lf.lfStrikeOut,&lf.lfCharSet,&lf.lfOutPrecision,&lf.lfClipPrecision,&lf.lfQuality,&lf.lfPitchAndFamily,lf.lfFaceName);
				gi->SetFont(lf);
			}
			//m_pRecordset->GetCollect("填充类型");
			gi->normal_regioncolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("填充颜色"))));
			node->SetGraphInfo(gi);

			//获取结点对应的区域信息
			node->rgnName=vartostr(m_pRecordset->GetCollect("区域名"));
			node->rgnType=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("区域类型"))));
			node->point_count=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("区域点数"))));
			node->Points = new CPoint[node->point_count];
			CString pointlist=vartostr(m_pRecordset->GetCollect("区域点数组"));
			CString singlepoint;
			int pos;
			for (int rgn_point_count=0; rgn_point_count<node->point_count; rgn_point_count++)
			{
				pos=pointlist.Find(";");
				singlepoint=pointlist.Left(pos);
				pointlist=pointlist.Right(pointlist.GetLength()-pos-1);
				sscanf(singlepoint,"(%d,%d)",&node->Points[rgn_point_count].x,&node->Points[rgn_point_count].y);
			}

			//m_pRecordset->GetCollect("正在运行");
			//m_pRecordset->GetCollect("分析标志");
			int flag=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("删除标志"))));
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
	catch(_com_error e)///捕捉异常
	{
		if (m_pRecordset!=NULL)
			m_pRecordset.Release();
		MessageBox("读取模型库中的结点表失败!","错误");///显示错误信息
		return false;
	}
	
	//读连线表
	try
	{
		CPoint startPoint, endPoint;
		strcpy(sql_cmd, "SELECT * FROM LINE_Table where 任务号=");
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
				MessageBox("创建Line_COM错误");
				return false;
			}
			Line * line = new Line((IBaseCom*)pLineCom);

			line->SetActive(FALSE);

			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线号"))));
			line->SetID(value);
			line_id_count=value+1;
			//m_pRecordset->GetCollect("任务号");
			//m_pRecordset->GetCollect("对象序号");
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("父结点号"))));
			parentnode=Get_Node_In_NodeArray(value);
			//m_pRecordset->GetCollect("父结点类型");
			//m_pRecordset->GetCollect("父结点层号");
			//m_pRecordset->GetCollect("父结点层中号");
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("子结点号"))));
			sonnode=Get_Node_In_NodeArray(value);
			//m_pRecordset->GetCollect("子结点类型");
			//m_pRecordset->GetCollect("子结点层号");
			//m_pRecordset->GetCollect("子结点层中号");
			line->SetName(vartostr(m_pRecordset->GetCollect("连线名称")));
			//m_pRecordset->GetCollect("连线中文名称");
			line->comment=vartostr(m_pRecordset->GetCollect("连线描述"));
	
			CPoint pos1,pos2;
			pos1.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线起点X"))))-scrollpos.x;
			pos1.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线起点Y"))))-scrollpos.y;
			pos2.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线终点X"))))-scrollpos.x;
			pos2.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线终点Y"))))-scrollpos.y;

			GraphInfo * gi = line->GetGraphInfo();
			gi->normal_penStyle=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线类型"))));
			gi->normal_linewidth=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线宽度"))));
			gi->normal_linecolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("连线颜色"))));
			gi->active_linecolor = gi->normal_linecolor;
			line->SetGraphInfo(gi);
			//m_pRecordset->GetCollect("箭头类型");
			//m_pRecordset->GetCollect("分析标志");
			int flag=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("删除标志"))));
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
	catch(_com_error e)///捕捉异常
	{
		if (m_pRecordset!=NULL)
			m_pRecordset.Release();
		MessageBox("读取模型库中的连线表失败!","错误");///显示错误信息
		return false;
	}

	return true;
}

//保存当前诊断运行内容到当前模型的诊断运行数据表中
BOOL CModelView::save_reason_steps_to_DB()
{
	CString Datasource;
	char sql_cmd[500],buf[10];
	int i;

	//删除原有内容
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from RESULT_Table where 任务ID号=");
	itoa(cur_task_id,buf,10);
	strcat(sql_cmd, buf);
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//保存现有内容
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("RESULT_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
	for (i=0;i<reason_step_count;i++)
	{
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("任务ID号", _variant_t(reason_step[i].task_id));
		m_pRecordset->PutCollect("步骤序号", _variant_t(reason_step[i].step_id));
		m_pRecordset->PutCollect("规则ID号", _variant_t(reason_step[i].rule_id));
		m_pRecordset->PutCollect("结点号", _variant_t(reason_step[i].node_id));
	}
	if (reason_step_count>0)
		m_pRecordset->Update();
	m_pRecordset.Release();
	return true;
}

//该模型是否已经存在
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
	case SB_LEFT:			//滚动到左端
		scrollpos.x = 0;
		break;
		
	case SB_RIGHT:			//滚动到右端
		scrollpos.x = MODELVIEW_MAX_X_RANGE;
		break;
		
	case SB_LINELEFT:		//向左滚动一行
		scrollpos.x = scrollpos.x - MODELVIEW_X_LINE;
		break;
		
	case SB_LINERIGHT:		//向右滚动一行
		scrollpos.x = scrollpos.x + MODELVIEW_X_LINE;
		break;
		
	case SB_PAGELEFT:		//向左滚动一页
		scrollpos.x = scrollpos.x - MODELVIEW_X_PAGE;
		break;
		
	case SB_PAGERIGHT:		//向右滚动一页
		scrollpos.x = scrollpos.x + MODELVIEW_X_PAGE;
		break;
		
	case SB_THUMBPOSITION:	//拖动滚动条到某个位置
		scrollpos.x = nPos;
		break;
		
	default:	break;
	}
	//如果是自定义的滚动条,要SetScrollPos(SB_HORZ, currentpos);
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
		if ( isPtInRgn )	//如果点在某个对象内部
		{
			curObject = pModelObject;
			switch ( nFlags )
			{
				case MK_LBUTTON + MK_SHIFT:
				case MK_LBUTTON + MK_CONTROL:
								//如果同时按下ctrl, 将激活的结点从SelectedObjects数组中删除
								actionflag = CTRL;
								break;
				default:		actionflag = DRAG;
								break;
			}
			break;
		}
	}	//end for 已经选中的结点
		
	//如果点在一组对象的某个区域内
	if ( isPtInRgn )
	{
		Invalidate(TRUE);
		CView::OnLButtonDown(nFlags, point);
		return ;
	}

	//如果没有点在任何一个已经选中的对象内部，判断是否点在其他对象中
	//1：判断结点
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
								//将新选中的对象激活, 加入SelectedObjects;
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
	
	//2：判断连线
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
								//将新选中的对象激活, 加入SelectedObjects;
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

	//也没有在任何连线上
	curObject = NULL;
	switch ( nFlags )
	{
		case MK_LBUTTON + MK_SHIFT:
		case MK_LBUTTON + MK_CONTROL:
						//可能是要框选
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
			MessageBox("父结点和子结点不能出现循环", "错误");
			Invalidate(TRUE);
			CView::OnLButtonDown(nFlags, point);
			return;
		}

		//设置parentNode 和sonNode的相关参数
		IMyLineCom * pLineCom = NULL;

		hr = ::CoCreateInstance(CLSID_MyLineCom, NULL, CLSCTX_ALL, IID_IMyLineCom, (void **)&pLineCom);
		if ( !SUCCEEDED(hr) )
		{
			MessageBox("创建COM错误");
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

		//画出连线
		CPoint startPoint,
			   endPoint;

		parentNode->GetBottomCenter(startPoint);
		sonNode->GetTopCenter(endPoint);
		pLineCom->SetStartPoint((unsigned long)&startPoint);
		pLineCom->SetEndPoint((unsigned long)&endPoint);

		newLine->Draw(&dc, 0, scrollpos, m_model_scale, NULL, 1, 1);

		//将当前连线设为激活的选项
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
		//加入小强的代码
		//10.15
		//.....
		//fqz
		/*测试TreeItem[]
		CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
		CModelTree * pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
		CTreeCtrl& m_ctlTree = pTreeView->GetTreeCtrl();
		for (i=0;i<m_ctlTree.GetCount()-1;i++)
			MessageBox(m_ctlTree.GetItemText(pTreeView->m_Tree.TreeItem[i]));
		*/

		degrade_to_subtree(sonNode, parentNode->layer+1-sonNode->layer);
		//更新treeview: 将sonNode为根的树作为parentNode的子树
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
	CPoint offset((int)((upPoint.x-downPoint.x)/oldPercentage), (int)((upPoint.y-downPoint.y)/oldPercentage));	//位移
	CPoint topleft, 
		   bottomright;
	Line * pLine = NULL;
	Node * pNode = NULL;
	CPoint newpoint;
	int cc, ii;

	//CMenu * menu;

	switch ( actionflag )
 	{
		case NOTHING://无动作
					break;
		case NODE:	//激活结点，在当前位置重绘结点
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
						
					//右侧树选中相应item
					pFWnd = (CMainFrame *)AfxGetMainWnd();
					pTreeView = (CModelTree *)pFWnd->m_wndSplitter1.GetPane(0,2);
					pDiagnose = (CDiagnoseView *)pFWnd->m_wndSplitter1.GetPane(0,0);

					pTreeCtrl = &pTreeView->GetTreeCtrl();
					pTreeCtrl->SelectItem(NodetoItem(pNode));

					//修改diagnoseview
					pDiagnose->m_nodename=pNode->GetName();
					pDiagnose->m_compname=pNode->rgnName;
					pDiagnose->UpdateData(false);
					
					break;

		case LINE:	//激活连线
					break;

		case CLIP:	//框选
					isPtInRgn = FALSE;
					topleft.x = downPoint.x<upPoint.x ? downPoint.x : upPoint.x;
					topleft.y = downPoint.y<upPoint.y ? downPoint.y : upPoint.y;
					bottomright.x = downPoint.x>upPoint.x ? downPoint.x : upPoint.x;
					bottomright.y = downPoint.y>upPoint.y ? downPoint.y : upPoint.y;
					curRect.SetRect(topleft, bottomright);

					//判断哪些对象在其中，将其active标志取"非"
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
		case DRAG:	//选中一组结点进行拖放
					//对选中结点及其相关连线重新计算坐标，并画图
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
						/*不允许拖动连线
						else
						{
							pLine = (Line *)pModelObject;
							pLine->pCom->Draw((unsigned long)&dc, 0, (unsigned long)&scrollpos, 1, 0, 1, 1);
							pLine->pCom->OffsetRgn((unsigned long)&offset);
						}
						*/
					}

					break;
					
		//case MOVE:	//一组对象位置移动，将其中的node都按照NODE的方式进行处理

		//case SHIFT://shift＋左键
		case CTRL:	//ctrl＋左键
					//......
					//remove选中的结点
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
		case COPY:	//MessageBox("复制选中对象");
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

	CPoint topleft,			//在clip时，设置端点用
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
		//画线
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
		case NOTHING:	//无动作
					break;
		case NODE:	//移动激活结点，取得鼠标在原图中相对于左上角的位移，
					if ( !mousemoving )
					{
						if ( curObject == NULL )
						{
							MessageBox("actionflag为移动结点，但curObject为空", "错误");
							lastPoint.x = point.x;
							lastPoint.y = point.y;
							CView::OnMouseMove(nFlags, point);
							return ;
						}
						//取得com的边缘矩形
						curObject->GetCom()->GetRgn((unsigned long)&rgn);
						rgn.GetRgnBox(&lastNodeRect);
						//lastNodeRect=CRect(lastNodeRect.left,lastNodeRect.top,lastNodeRect.right,lastNodeRect.bottom);
						lastNodeRect.SetRect((int)(lastNodeRect.left*oldPercentage),(int)(lastNodeRect.top*oldPercentage),
										(int)(lastNodeRect.right*oldPercentage),(int)(lastNodeRect.bottom*oldPercentage));
						//设置移动后矩形位置
						curNodeRect.SetRect(lastNodeRect.TopLeft(), lastNodeRect.BottomRight());
						curNodeRect.OffsetRect(movePoint.x-lastPoint.x, movePoint.y-lastPoint.y);
						//dc.DrawDragRect(curNodeRect, size, lastNodeRect, size);//xnfp
						mousemoving = TRUE;
					}
					else
					{
						//用上次的结果初始化lastRect
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
					
		case LINE:	//激活连线，暂时不允许移动连线
					break;

		case MOVE:
		case DRAG:	//拖放，计算最左上角和最右下角，画一个矩形
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

							//计算取得的坐标
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
							//用上次的结果初始化lastRect
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

		case NEW:	//新建结点
					break;
		case CTRL:	//ctrl＋左键
					if ( movePoint != downPoint || movePoint != lastPoint )
					{
						curObject->SetActive(TRUE);
						SelectedObjects.Add(curObject);
						actionflag = COPY;
					}
					break;
		case CLIP:	//drewdragcret,当鼠标松开后再设置SelectedObjects，会使效率高一些
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
					//判断哪些对象在其中，将其active标志取"非"
					count = NodeArray.GetSize();
					for(i=0; i<count; i++)
					{
						pModelObject = NodeArray.GetAt(i);
						if ( pModelObject->IsDeleted() )
							continue;
						isInRgn = pModelObject->InOtherRect(lastClipRect,oldPercentage);
						isInRgn2 = pModelObject->InOtherRect(curClipRect,oldPercentage);
						if ( isInRgn != isInRgn2 )	//如果框选前后两个状态发生改变
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
						
						if ( isInRgn != isInRgn2 )	//如果框选前后两个状态发生改变
						{
							isActive = pModelObject->GetActive();
							isActive = !isActive;
							pModelObject->SetActive(isActive);
						}
					}
					break;
		//default :	MessageBox("错误的鼠标动作参数", "错误");
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
	case SB_TOP:			//滚动到顶部
		scrollpos.y = 0;
		break;
		
	case SB_BOTTOM:			//滚动到底部
		scrollpos.y = MODELVIEW_MAX_Y_RANGE;
		break;
		
	case SB_LINEUP:			//点击滚动条向上的按键,滚动一行
		scrollpos.y = scrollpos.y - MODELVIEW_Y_LINE;
		break;
		
	case SB_LINEDOWN:		//点击滚动条向下的按键,滚动一行
		scrollpos.y = scrollpos.y + MODELVIEW_Y_LINE;
		break;
		
	case SB_PAGEUP:			//点击滚动条上部空白,滚动一页
		scrollpos.y = scrollpos.y - MODELVIEW_Y_PAGE;
		break;
		
	case SB_PAGEDOWN:		//点击滚动条下部空白,滚动一页
		scrollpos.y = scrollpos.y + MODELVIEW_Y_PAGE;
		break;
		
	case SB_THUMBPOSITION:	//拖动滚动条到某个位置(保存在nPos中)
		scrollpos.y = nPos;
		break;
		
	default:	break;
	}
	//如果是自定义的滚动条,要SetScrollPos(SB_VERT, currentpos)
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
	pFrm->SetActiveView(pView); //激活窗口	
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
		 m_pConnection->Close(); //如果已经打开了连接则关闭它
	read_one_model(m_cur_model_name);

	cur_reason_node_no=0;
	SelectedObjects.RemoveAll();
	curObject = NULL;
	import_data_flag=FALSE;

	//修改右边的树
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

	//调整当前视图，以适应模型结点树
	CurModelGraphRect=CalModelGraphRect();
	int x1 = CurModelGraphRect.left,
		y1 = CurModelGraphRect.top,
		x2 = CurModelGraphRect.right,
		y2 = CurModelGraphRect.bottom;

	CString str;

	if (count>0)
	{
		CPoint pos(CurModelGraphRect.left+scrollpos.x,CurModelGraphRect.top+scrollpos.y);
		
		//draw 部件图
		bmpx=CurModelGraphRect.left+scrollpos.x;
		bmpy=CurModelGraphRect.bottom+scrollpos.y+(int)(20*oldPercentage);
		
		scrollpos = pos;
		SetScrollPos(SB_VERT, pos.y, TRUE);
		SetScrollPos(SB_HORZ, pos.x, TRUE);
		
		fullgraph_times=0;
		OnFullGraph();
	}
	
	cur_reason_node_no=0;
	reason_step_count=0; //清空，重新推理
	CTipView *pTip = (CTipView *)pFWnd->m_wndSplitter3.GetPane(1,0);
	pTip->ClearTipData();

	DiagnoseResult="";
	Invalidate(true);
}

//计算当前模型结点图的外围区域
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
	//暂时保留
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
	
		pInfo->SetMaxPage(1); //设置总页数
		return DoPreparePrinting(pInfo);;
	}
	
	CDC dc;
	if (!AfxGetApp()->CreatePrinterDC(dc))
	{
		MessageBox("不能设置打印,请设置默认计算机","错误");
		return FALSE;
	}
	// 计算屏幕大小与纸张的大小以及打印页数。
	dc.SaveDC();
	//计算视的大小（用mm表示）
	CPoint point((int)((MODELVIEW_MAX_X_RANGE/96)*25.4),(int)((MODELVIEW_MAX_Y_RANGE/96)*25.4));
//	int oldMap;
	numberOfPages=0;
	int xLogPix	= dc.GetDeviceCaps(HORZSIZE); //得到纸张的大小
	int yLogPix	= dc.GetDeviceCaps(VERTSIZE);

	numCol=(int)((point.x+xLogPix-1)/xLogPix); //计算行数和列数
	numRow=(int)((point.y+yLogPix-1)/yLogPix);

	numberOfPages=numRow*numCol; // 总的页数。
	
	pInfo->SetMaxPage(numberOfPages); //设置总页数
 
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
	
		CString head="诊断结论";		//头
		CString text;					//正文
		CString tail="操作人：";		//署名
		CTime time;
		CString timestr;
		time=CTime::GetCurrentTime();
		timestr = time.Format("%Y年%m月%d日%H:%M");
		pInfo->SetMaxPage(1); //设置总页数




		//打印当前页数
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
		int xwidh = pDC->GetDeviceCaps(HORZSIZE); //得到页面大小mm
		int xheigth = pDC->GetDeviceCaps(VERTSIZE);
		width = (int)(xwidh/25.4*xLogPixPerInch);
		heigth= (int)(xheigth/25.4*yLogPixPerInch);
		//setting of the text printed
		int oldMapMode=pDC->SetMapMode(MM_TEXT);
		pDC->TextOut((int)(width/2-460),600, head); //打印标题
		lf1.lfWeight = FW_NORMAL;
		lf1.lfHeight = 120;
		font.DeleteObject();
		font.CreateFontIndirect(& lf1);
		pDC->SelectObject(&font);
		//fqz
		text.Format("         %s，操作人%s对模型%s进行了诊断测试。",timestr,m_sqlserver_db.user,m_cur_model_name);
		pDC->TextOut(180,1200, text); //打印内容；
		text.Format("         测试结论：%s",DiagnoseResult);
		pDC->TextOut(180,1400, text); //打印内容；


		
		lf1.lfWeight = FW_BOLD;
		lf1.lfHeight = 150;
		font.DeleteObject();		
		font.CreateFontIndirect(& lf1);
		pDC->SelectObject(&font);
		
		pDC->TextOut((int)(width-1500),heigth-1500, tail); //打印
		pDC->SetMapMode(oldMapMode);
		if (pOldFont) pDC->SelectObject(pOldFont);
		return;	
	}	
	CString str;
	CPoint point;
	CString	text ;
	CSize	csText ;
	//打印当前页数
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
	int xwidh = pDC->GetDeviceCaps(HORZSIZE); //得到页面大小mm
	int xheigth = pDC->GetDeviceCaps(VERTSIZE);
	width = (int)(xwidh/25.4*xLogPixPerInch);
	heigth= (int)(xheigth/25.4*yLogPixPerInch);
	//setting of the text printed
	int oldMapMode=pDC->SetMapMode(MM_TEXT);
	pDC->TextOut((int)(width-300),10, text); //打印页眉
	pDC->SetMapMode(oldMapMode);
	if (pOldFont) pDC->SelectObject(pOldFont);

	
	CSize size1=CSize(50,30);
	pDC->SetWindowExt(size1);
	//得到设备坐标和逻辑坐标的比例
	long xExt = (long)size1.cx * xLogPixPerInch/96;
	long yExt = (long)size1.cy * yLogPixPerInch/96;
	pDC->SetViewportExt((int)xExt,(int)yExt);


	int xorg,yorg;
	int x1,y1;
	x1=(int)((pInfo->m_nCurPage-1)%numCol); //计算顶点列坐标相对位置
	y1=(int)((pInfo->m_nCurPage-1)/numCol); //计算顶点行坐标相对位置
	xorg=(int)(x1*xwidh/25.4*96-scrollpos.x);
	yorg=(int)(y1*xheigth/25.4*96-scrollpos.y);
	pDC->SetWindowOrg(xorg,yorg);            //设置窗口坐标
//	pDC->SetViewportOrg(0,0);            //设置窗口坐标
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




/*----------------------ADO读取类型的转换----------------------*/
CString vartoCstr(const _variant_t &var)
{
	CString strValue;
	
	switch (var.vt)
	{
	case VT_BSTR://字符串
	case VT_LPSTR://字符串
	case VT_LPWSTR://字符串
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://短整型
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://无符号短整型
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://整型
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //整型
		strValue.Format("%d", var.lVal);
		break;
	case VT_I8: //长整型
		strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://无符号整型
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //无符号整型
		strValue.Format("%d", var.ulVal);
		break;
	case VT_UI8: //无符号长整型
		strValue.Format("%d", var.ulVal);
		break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://浮点型
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://双精度型
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //小数
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
	case VT_BOOL://布尔型

		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //日期型
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULL值
		strValue = "";
		break;
	case VT_EMPTY://空
		strValue = "";
		break;
	case VT_UNKNOWN://未知类型
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
	case VT_BSTR://字符串
	case VT_LPSTR://字符串
	case VT_LPWSTR://字符串
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://短整型
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://无符号短整型
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://整型
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //整型
		strValue.Format("%d", var.lVal);
		break;
	case VT_I8: //长整型
		strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://无符号整型
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //无符号整型
		strValue.Format("%d", var.ulVal);
		break;
	case VT_UI8: //无符号长整型
		strValue.Format("%d", var.ulVal);
		break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://浮点型
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://双精度型
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //小数
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
	case VT_BOOL://布尔型

		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //日期型
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULL值
		strValue = "";
		break;
	case VT_EMPTY://空
		strValue = "";
		break;
	case VT_UNKNOWN://未知类型
	default:
		strValue = "UN_KNOW";
		break;
	}
	int length=strValue.GetLength();
	result=(char *)malloc(length+1);
	strcpy(result,strValue.GetBuffer(length));
	return result;
}

/*----------------------数据接口----------------------*/

//注意: 界面1添加或删除结点, 界面2添加或删除数据结点时, 数据值就得随之调整

//功能: 导入当前模型所有结点的数据
//数据表中的curdata是当前模型的数据值串: 按结点号递增的次序排列
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

	//清除各结点原有的数据序列
	for (i=0; i<node_count; i++ )
	{
		Node *node = NodeArray.GetAt(i);
		free_dataset(node->NodeData);
	}
	//NodeArray也是按结点号排序的,所以次序符合数据值的次序
	for (i=0;i<node_count;i++)
	{
		Node *node=NodeArray.GetAt(i);
		itoa(node->GetID(),buf,10);
		strcpy(sql_cmd, "SELECT * FROM DATA_Table where 结点号=");
		strcat(sql_cmd, buf);
		strcat(sql_cmd, " and 任务号=");
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
					type = m_pRecordset->GetCollect("征兆数据名");
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

		catch(_com_error e)///捕捉异常
		{
			MessageBox("读取数据库失败!","错误");///显示错误信息
		}
	}
	free(str);
}

//数据接口：读取某个结点的数据，以dataset结构存储
class_dataset get_node_data(int node_no,CModelView *pModel)
{
	Node *node=pModel->Get_Node_In_NodeArray(node_no);
	return node->NodeData;
}

//释放dataset所占空间
void CModelView::free_dataset(class_dataset dataset)
{
	int i;
	for (i=0;i<dataset.data_num;i++)
		free(dataset.datalist[i].type);
	if (dataset.data_num>0)
		free(dataset.datalist);
	dataset.data_num=0;
}

/*----------------------推理主函数----------------------*/

//某个结点内的推理，返回跳转的下一个结点号。如果无法跳转任何结点，则返回-1
class_reason_result CModelView::reason_one_node(int node_no)
{
//
	class_reason_result result;

	//模拟推理很慢
	Sleep(2000L);
	result.next_node_no=-1; 
	result.exec_rule_id=-1;	//-1表示没匹配到任何规则
	
	int ruleid,outnodeid;
	CString strrule;
	
	result.diagnose_type = "规则推理";
	if(Deduce().RegDeduce1Node(node_no,ruleid,strrule,outnodeid) == false)
	{
		result.diagnose_type = "模糊推理";
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
	
	
	//模拟推理很慢
	Sleep(2000L);

	result.next_node_no=-1; 
	result.exec_rule_id=-1;	//-1表示没匹配到任何规则

	dataset=get_node_data(node_no,this);
	if (dataset.data_num==0)//无数据?
		return result;

	//遍历该结点内各规则，一旦成立，立刻返回
	_RecordsetPtr m_pRecordset;
	_variant_t rule_id,antecedent,goto_node_no;
	CString sql_cmd;
	char *substr;

	CString rule_table_name[2]={"CORRECTRULE_Table","WRONGRULE_Table"};

	for (i=0;i<2;i++)
	{
		sql_cmd.Format("SELECT * FROM %s where 结点号=%ld and 任务号=%ld",rule_table_name[i],node_no,cur_task_id);
		try
		{
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open(LPCTSTR(sql_cmd),_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			while(!m_pRecordset->EndOfFile)
			{
				//读取当前规则r
				rule_id = m_pRecordset->GetCollect("规则ID号");
				antecedent = m_pRecordset->GetCollect("规则内容");
				goto_node_no = m_pRecordset->GetCollect("规则输出");
				
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
				
				//处理当前规则r
				//前件中某谓词不可解，并不能说明该规则就不可解，还需要看运算关系
				//  如 规则前件=小于(电压,3.2)|大于(电流,2.1)
				//	 dataset={电压=2}
				//	 dataset缺少电流的数据值，但该规则前件依然是成立的
				
				if (r.goto_node_no>=0 && Get_Node_In_NodeArray(r.goto_node_no)==NULL)
				{	//对象建模时该结点被删除了,但规则还在，无效！
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
					//如果前件为真，则记录后件所示结点，退出
					result.next_node_no=r.goto_node_no;
					result.exec_rule_id=r.rule_id;
					result.antecedent=vartoCstr(antecedent);
					pReasonCom->free_rule((unsigned long)&r);
					//匹配规则的使用频度+1
					long freq=atol(LPCTSTR(vartoCstr(m_pRecordset->GetCollect("使用频度"))));
					m_pRecordset->PutCollect("使用频度",_variant_t(long(freq+1)));
					m_pRecordset->Update();
					break;
				}
			}
			m_pRecordset.Release();
		}

		catch(_com_error e)///捕捉异常
		{
			CString str;
			str.Format("读取%s失败!",rule_table_name[i]);
			MessageBox(str,"错误");///显示错误信息
			return result;
		}
		if (result.exec_rule_id!=-1)
			break;
	}*/

	return result;
}

//停止当前闪烁的结点和部件
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

//记录当前步骤的推理内容
void CModelView::SaveCurReasonStep(class_reason_result reason_result, Node *curNode)
{
	//记录当前运行步骤
	CString out_node_name;

	if (reason_result.exec_rule_id==-1)
	{
		out_node_name="空";
		reason_result.antecedent="空";
	}
	else
	{
		if (reason_result.next_node_no==-1)
			out_node_name="正常";
		else if (reason_result.next_node_no==-2)
			out_node_name="故障";
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

	//提示区追加
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

//单步推理线程
LRESULT CModelView::reason_one_thread(LPVOID pParam)
{
	//view_pointer.pDiagnose->m_nodename="test";
	//view_pointer.pModel->SendMessage(WM_RBUTTONUP);

	CString Prompt;
	class_reason_result reason_result;

	CModelView *pModel=view_pointer.pModel;
	
	//开始闪烁当前要推理的结点
	pModel->m_cGlint.BeginNode(pModel->cur_reason_node);
	pModel->m_cGlint.BeginBmp(1);
	pModel->Invalidate();

	//推出结果
	reason_result=pModel->reason_one_node(pModel->cur_reason_node_no);

	//推理完后，停止闪烁
	pModel->StopCurGlint();

	if (reason_result.exec_rule_id!=-1)
	{
		if (reason_result.next_node_no==-1)
		{
			Prompt.Format("%s正常, 诊断过程结束, 没有发现故障",pModel->cur_reason_node->GetName());
			DiagnoseResult="一切正常";
		}
		else if (reason_result.next_node_no==-2)
		{
			Prompt.Format("%s发现故障, 诊断过程结束",pModel->cur_reason_node->GetName());
			DiagnoseResult=pModel->cur_reason_node->rgnName+"发现故障";
		}
		else
		{
			Node *node=pModel->Get_Node_In_NodeArray(reason_result.next_node_no);
			Prompt.Format("%s可能有故障, 请继续诊断",node->GetName());
			DiagnoseResult=node->rgnName+"可能有故障，有待诊断";
		}
	}
	else
	{
		Prompt.Format("%s中无匹配规则, 诊断过程结束",pModel->cur_reason_node->GetName());
		DiagnoseResult.Format("%s中无匹配规则",pModel->cur_reason_node->GetName());
	}
	pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);//存储步骤并追加提示区
	AfxMessageBox(Prompt);
	pModel->cur_reason_node_no=reason_result.next_node_no;//当前结点改变
	pModel->hThread=NULL; //线程结束
	return 0L;
}

//多步推理线程
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

		//开始闪烁当前要推理的结点
		pModel->m_cGlint.BeginNode(pModel->cur_reason_node);
		pModel->m_cGlint.BeginBmp(1);
		pModel->Invalidate();

		reason_result=pModel->reason_one_node(pModel->cur_reason_node_no);
		
		//停止闪烁
		pModel->StopCurGlint();

		if (reason_result.exec_rule_id!=-1)
		{
			if (reason_result.next_node_no==-1)
			{
				DiagnoseResult="一切正常";
				pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);
				Prompt.Format("%s正常, 诊断过程结束, 没有发现故障",pModel->cur_reason_node->GetName());
				AfxMessageBox(Prompt);
			}
			else if (reason_result.next_node_no==-2)
			{
				DiagnoseResult=pModel->cur_reason_node->rgnName+"发现故障";
				pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);
				Prompt.Format("%s发现故障, 诊断过程结束",pModel->cur_reason_node->GetName());
				AfxMessageBox(Prompt);
			}
			else
			{
				DiagnoseResult=pModel->Get_Node_In_NodeArray(reason_result.next_node_no)->rgnName+"可能有故障，有待诊断";
				pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);
			}
		}
		else
		{
			DiagnoseResult.Format("%s中无匹配规则",pModel->cur_reason_node->GetName());
			pModel->SaveCurReasonStep(reason_result,pModel->cur_reason_node);//显示提示区内容
			Prompt.Format("%s中无匹配规则, 诊断过程结束",pModel->cur_reason_node->GetName());
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
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("请先选择一个模型!","提示");
		return;
	}
	if (import_data_flag==FALSE)
	{
		MessageBox("请先导入数据再推理","提示");
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

	//如果用户选择了一个结点，则从该结点开始推理，否则从上一步推理结点开始
	if (curObject!=NULL && curObject->IsKindOf(RUNTIME_CLASS(Node)))
	{
		cur_reason_node=(Node *)curObject;
		cur_reason_node_no=cur_reason_node->GetID();
		cur_reason_node->SetActive(false);
		SelectedObjects.RemoveAll();
		curObject=NULL;
		Invalidate();
		reason_step_count=0; //清空以前的推理过程
		pTip->ClearTipData();
	}
	else
	{
		if (cur_reason_node_no<0)
		{
			MessageBox("诊断过程已经结束。想重新诊断，请点击运行。想单步调试，请先选择结点!","提示");
			return;
		}
		else
		{
			if ((cur_reason_node=Get_Node_In_NodeArray(cur_reason_node_no))==NULL)
			{
				CString prompt;
				prompt.Format("不存在结点%d",cur_reason_node_no);
				MessageBox(prompt,"提示");
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
		AfxMessageBox("创建推理线程失败!");
}

void CModelView::ContinueReason() 
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("请先选择一个模型!","提示");
		return;
	}
	if (import_data_flag==FALSE)
	{
		MessageBox("请先导入数据再推理","提示");
		return;
	}

	//从上一步推理结点开始
	if (cur_reason_node_no<0)
	{
		MessageBox("诊断过程已经结束。想重新诊断，请点击运行；想单步调试，请先选择结点!","注意");
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
		AfxMessageBox("创建推理线程失败!");
}

void CModelView::ReasonAll() 
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("请先选择一个模型!","提示");
		return;
	}
	if (import_data_flag==FALSE)
	{
		MessageBox("请先导入数据再推理","提示");
		return;
	}

	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CTipView *pTip = (CTipView *)pFWnd->m_wndSplitter3.GetPane(1,0);
	pTip->ClearTipData();

	//用户要选中一个结点开始推理
	if (curObject!=NULL && curObject->IsKindOf(RUNTIME_CLASS(Node)))
	{
		cur_reason_node=(Node *)curObject;
		cur_reason_node_no=cur_reason_node->GetID();
		cur_reason_node->SetActive(false);
		SelectedObjects.RemoveAll();
		curObject=NULL;
		Invalidate();
		reason_step_count=0; //清空以前的推理过程
		pTip->ClearTipData();
		ContinueReason();
	}
	else
		MessageBox("请先选中你要开始推理的结点","提示");
	
}

void CModelView::OnDataSave() 
{
	// TODO: Add your command handler code here
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	if (reason_step_count==0)
		MessageBox("当前推理数据为空，没什么可保存的!","提示");
	else	
	{
		save_reason_steps_to_DB();
		MessageBox("推理过程成功保存到诊断运行数据表中","成功");
	}
}

//根据指定输出的字段列表，以文件方式输出，返回报表内容
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
			if (fieldname=="任务号")
				value.Format("%ld",reason_step[i].task_id);
			else if (fieldname=="步骤号")
				value.Format("%ld",reason_step[i].step_id);
			//else if (fieldname=="结点号")
			//	value.Format("%ld",reason_step[i].node_id);
			else if (fieldname=="结点名称")
				value=reason_step[i].node_name;
			else if (fieldname=="部件名称")
				value=reason_step[i].comp_name;
			else if (fieldname=="规则号")
				value.Format("%ld",reason_step[i].rule_id);
			else if (fieldname=="输出结点")
				value=reason_step[i].out_node_name;
			currecord=currecord+fieldname+"="+value+"\n";
		}
		if (report!="")
			report=report+"\n";
		report=report+currecord;
	}
	report=report+"\n"+"诊断结论："+DiagnoseResult;
	return report;
}

//根据指定输出的字段列表，以XML方式输出，返回报表内容
CString CModelView::ReportOut_by_XML()
{
	CString report,currecord,fieldname,value;
	int i,j;

	report="<?xml version=\"1.0\" encoding=\"GB2312\" ?>\n";
	report=report+"\t<任务组>\n";
	int reportfieldcount=ReportOutFields.GetSize();
	for (i=0;i<reason_step_count;i++)
	{
		currecord="\t\t<任务>\n";
		for (j=0;j<reportfieldcount;j++)
		{
			fieldname=ReportOutFields.GetAt(j);
			if (fieldname=="任务号")
				value.Format("%ld",reason_step[i].task_id);
			else if (fieldname=="步骤号")
				value.Format("%ld",reason_step[i].step_id);
			//else if (fieldname=="结点号")
			//	value.Format("%ld",reason_step[i].node_id);
			else if (fieldname=="结点名称")
				value=reason_step[i].node_name;
			else if (fieldname=="部件名称")
				value=reason_step[i].comp_name;
			else if (fieldname=="规则号")
				value.Format("%ld",reason_step[i].rule_id);
			else if (fieldname=="输出结点")
				value=reason_step[i].out_node_name;
			currecord=currecord+"\t\t\t"+"<"+fieldname+">"+value+"</"+fieldname+">"+"\n";
		}
		currecord=currecord+"\t\t</任务>\n";
		report=report+currecord;
	}
	report=report+"\t</任务组>";
	return report;
}

void CModelView::ReportOut() 
{
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}

	// TODO: Add your control notification handler code here
	CString report;
	if (m_cur_model_name=="")
	{
		MessageBox("请先选择一个模型!","提示");
		return;
	}
	
	CReportShowDlg dlg;
	dlg.DoModal();
}

void CModelView::OnReportdefine() 
{
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
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
		if (fieldname=="任务号")
			dlg.m_task_id=TRUE;
		//else if (fieldname=="结点号")
		//	dlg.m_node_id=TRUE;
		else if (fieldname=="结点名称")
			dlg.m_node_name=TRUE;
		else if (fieldname=="部件名称")
			dlg.m_comp_name=TRUE;
		else if (fieldname=="规则号")
			dlg.m_rule_id=TRUE;
		else if (fieldname=="输出结点")
			dlg.m_outnode=TRUE;
	}
	if (dlg.DoModal()==IDCANCEL)
		return;

	ReportOutFields.RemoveAll();
	ReportOutFields.Add("步骤号");
	if (dlg.m_task_id==TRUE)
		ReportOutFields.Add("任务号");
	//if (dlg.m_node_id==TRUE)
		//ReportOutFields.Add("结点号");
	if (dlg.m_node_name==TRUE)
		ReportOutFields.Add("结点名称");
	if (dlg.m_comp_name==TRUE)
		ReportOutFields.Add("部件名称");
	if (dlg.m_rule_id==TRUE)
		ReportOutFields.Add("规则号");
	if (dlg.m_outnode==TRUE)
		ReportOutFields.Add("输出结点");
}

void CModelView::ShowData() 
{
	// TODO: Add your control notification handler code here
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	if (m_cur_model_name=="")
	{
		MessageBox("请先选择一个模型!","提示");
		return;
	}
	CSelectDataDlg dlg;
	if ( dlg.DoModal() == IDCANCEL )
		return;

	//load_all_nodes_data(dlg.m_select_data);
	Deduce().GetRecordSet(dlg.m_select_data);
	import_data_flag=TRUE;
	MessageBox("数据导入成功！");
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
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	MessageBox("数据自动获取");
}

void CModelView::OnManget() 
{
	// TODO: Add your command handler code here
	if(hThread)
	{
		MessageBox("当前推理活动正在进行，请稍后再试!","警告");
		return;
	}
	MessageBox("数据手工获取");
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
		height=r.Height()+pBmp->bitmap.bmHeight+(int)(20*oldPercentage);  //加上bmp的height
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
	这是移动滚动条的方法
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

	//移动结点坐标
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

