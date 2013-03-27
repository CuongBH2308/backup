// DiagRunView.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "DiagRunView.h"
#include "ComTreeView.h"
#include "OpenModelDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagRunView

IMPLEMENT_DYNCREATE(CDiagRunView, CScrollView)

extern IBaseCom * current_active_com;
extern CModelTree * pModelView;
unsigned long node_id_count = 0;
unsigned long line_id_count = 0;
extern BOOL mousemoving;							//鼠标是否在移动过程中
extern BOOL mousedown;								//鼠标是否点下，并且尚未释放

//10.20添加
int com_count=3;
const CLSID * CLSIDArray[] = {&CLSID_MyCom1, &CLSID_MyCom2, &CLSID_MyLineCom};
const IID * IIDArray[] = {&IID_IMyCom1, &IID_IMyCom2, &IID_IMyLineCom};

int Get_Com_ID(Node *node)
{
	CLSID clsid;
	node->GetCom()->GetCLSID((unsigned long)&clsid);
	for (int i=0;i<com_count;i++)
		if (*CLSIDArray[i]==clsid)
			return i;
	return -1;
}

//fqz
void degrade_to_subtree(Node *pNode, int layer);
void MoveItemToLast(HTREEITEM m_startItem, HTREEITEM pItem);
HTREEITEM NodetoItem(Node *pNode);
//声明删除保留区
DeleteArea ModelDeleteArea;

CDiagRunView::CDiagRunView():downPoint(0,0), upPoint(0,0), movePoint(0,0), lastPoint(0,0)
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

	//fqz
	m_cur_model_name="";
	ModelDeleteArea.data_flag=0;
	AfxOleInit();///初始化COM库
	HRESULT hr;
	hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
	if(!SUCCEEDED(hr))
	{
		AfxMessageBox("创建m_pConnection失败!");
	}

//	m_sqlserver_db.dbsrc="127.0.0.1";
//	m_sqlserver_db.user="fqz";
//	m_sqlserver_db.pass="windblow";
	m_sqlserver_db.dbsrc="windblow";
	m_sqlserver_db.user="fqz";
	m_sqlserver_db.pass="windblow";
	read_model_array();
scrollpos.x=2500;
scrollpos.y=1500;

}

CDiagRunView::~CDiagRunView()
{
	//fqz
	m_pConnection.Release();
}


BEGIN_MESSAGE_MAP(CDiagRunView, CScrollView)
	//{{AFX_MSG_MAP(CDiagRunView)
	ON_COMMAND(ID_SELECTMODEL, OnSelectmodel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagRunView drawing

/////////////////////////////////////////////////////////////////////////////
// CDiagRunView diagnostics

#ifdef _DEBUG
void CDiagRunView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDiagRunView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiagRunView message handlers
/*   The following codes were from sijinxin and used to move tree!!!   */

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
	Item=m_ctlTree.InsertItem(m_ctlTree.GetItemText(m_startItem),0,1,pItem,nItem);
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
		nItem=m_ctlTree.InsertItem(m_ctlTree.GetItemText(nextItem),0,1,pItem,nItem);
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
	AfxMessageBox(str);
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
Node * CDiagRunView::Get_Node_In_NodeArray(unsigned long node_no)
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

void CDiagRunView::clear_nodearray_linearray()
{
	unsigned long count = NodeArray.GetSize();
	unsigned long i;
	for (i=0; i<count; i++ )
	{
		Node *node = NodeArray.GetAt(i);
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

void CDiagRunView::read_model_array()
{
	// TODO: Add your command handler code here
	CString str;
	CStdioFile file;
	CFileException e;
	if (file.Open("model_list.txt",CFile::modeRead|CFile::shareDenyNone,&e))
	{
		str="";
		while(file.ReadString(str)!=NULL)
		{
			ModelArray.Add(str);
			str="";
		}
		file.Close();
	}
}

void CDiagRunView::write_model_array()
{
	// TODO: Add your command handler code here
	CStdioFile file;
	CFileException e;
	file.Open("model_list.txt",CFile::modeReadWrite|CFile::modeCreate|CFile::shareDenyNone,&e);
	int count=ModelArray.GetSize();
	if (count>0)
	{
		for (int i=0; i<count-1; i++)
			file.WriteString(ModelArray.GetAt(i)+"\n");
		file.WriteString(ModelArray.GetAt(count-1));
	}
	file.Close();
}

/*----------------------ADO读取类型的转换----------------------*/
CString vartostr(const _variant_t &var)
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
BOOL CDiagRunView::exec_sql(char *sql_cmd)
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
BOOL CDiagRunView::read_one_model(CString model_name)
{
	m_sqlserver_db.dbname=CString(model_name);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CString Datasource;
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
	HRESULT hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	//上面一句中连接字串中的Provider是针对SQL Server环境的
	
	/*读入数据*/
/*
	//读被测对象属性表
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("OBJECT_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
		while(!m_pRecordset->adoEOF)
		{
			m_pRecordset->GetCollect("对象序号");
			m_pRecordset->GetCollect("对象号");
			m_pRecordset->GetCollect("任务号");
			m_pRecordset->GetCollect("对象名称");
			m_pRecordset->GetCollect("对象描述");

			//?=vartostr();

			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
	}
	catch(_com_error e)///捕捉异常
	{
		AfxMessageBox("读取被测对象属性表失败!");///显示错误信息
	}
*/
	//读结点表
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("NODES_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
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
			//m_pRecordset->GetCollect("对象序号");
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("层号"))));
			node->layer=value;
			//m_pRecordset->GetCollect("层中序号");
			//m_pRecordset->GetCollect("父结点号");
			node->inLine=NULL;
			node->SetName(vartostr(m_pRecordset->GetCollect("结点名称")));
			//m_pRecordset->GetCollect("结点中文名称");
			node->comment=vartostr(m_pRecordset->GetCollect("结点描述"));
			CPoint pos1, pos2;
			/*
			pos1.x=0;
			pos1.y=0;
			pos2.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("X坐标"))));
			pos2.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("Y坐标"))));
			node->SetScrPos(pos1);		
			node->SetTopLeft(pos2);
			*/

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
			//m_pRecordset->GetCollect("字体");
			//m_pRecordset->GetCollect("字号");
			//m_pRecordset->GetCollect("字体颜色");
			//m_pRecordset->GetCollect("填充类型");
			gi->normal_regioncolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("填充颜色"))));
			node->SetGraphInfo(gi);
			//m_pRecordset->GetCollect("正在运行");
			//m_pRecordset->GetCollect("分析标志");
			int flag=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("删除标志"))));
			if (flag==1)
				node->SetDeleted(true);
			else
				node->SetDeleted(false);

			//node->SetActive(TRUE);
			NodeArray.Add(node);
			if (!node->IsDeleted())
				node->Draw(&dc, pos2, pos1, m_model_scale, &m_GraphInfo, 1, node->GetActive());
			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
	}
	catch(_com_error e)///捕捉异常
	{
		AfxMessageBox("读取结点表失败!");///显示错误信息
	}
	
	//读连线表
	try
	{
		CPoint startPoint, endPoint;
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("LINE_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
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
		AfxMessageBox("读取连线表失败!");///显示错误信息
	}

	if(m_pConnection->State)
		 m_pConnection->Close(); ///如果已经打开了连接则关闭它
	return true;
}

//存储一个已有的模型
BOOL CDiagRunView::save_one_model(CString model_name)
{
	CString Datasource;
	HRESULT hr;
	char sql_cmd[500];
	int i;
	int updated;

	m_sqlserver_db.dbname=model_name;
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	
	//1. 处理OBJECT_Table
/*
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from OBJECT_Table");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//插入数据
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("OBJECT_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
	m_pRecordset->AddNew();
	m_pRecordset->PutCollect("对象号", _variant_t(long(2)));
	m_pRecordset->PutCollect("任务号", _variant_t(long(2)));
	m_pRecordset->PutCollect("对象名称", _variant_t(""));
	m_pRecordset->PutCollect("对象描述", _variant_t(""));
	//对象名称 对象描述
	
	m_pRecordset->Update();
	m_pRecordset.Release();
*/

	//2. 处理NODES_Table
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from NODES_Table");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//插入数据
	updated=0;
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("NODES_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
	int count=NodeArray.GetSize();
	for (i=0;i<count;i++)
	{
		Node *pNode=NodeArray.GetAt(i);
		if (!pNode->IsDeleted())
		{
			m_pRecordset->AddNew();
			updated=1;
			m_pRecordset->PutCollect("结点号", _variant_t(long(pNode->GetID())));
			//m_pRecordset->PutCollect("任务号", _variant_t(long(2)));
			//m_pRecordset->PutCollect("对象序号", _variant_t(long(2)));
			m_pRecordset->PutCollect("层号", _variant_t(long(pNode->layer)));
			//m_pRecordset->PutCollect("层中序号", _variant_t(long(2)));
			if (pNode->inLine==NULL)
				m_pRecordset->PutCollect("父结点号", _variant_t(long(-1)));
			else
				m_pRecordset->PutCollect("父结点号", _variant_t(long(pNode->inLine->parentNode->GetID())));
			m_pRecordset->PutCollect("结点名称", _variant_t(pNode->GetName()));
			//m_pRecordset->PutCollect("结点中文名称", _variant_t(pNode->GetName()));
			m_pRecordset->PutCollect("结点描述", _variant_t(pNode->comment));
			m_pRecordset->PutCollect("X坐标", _variant_t(long(pNode->GetTopLeft().x + pNode->GetScrPos().x)));
			m_pRecordset->PutCollect("Y坐标", _variant_t(long(pNode->GetTopLeft().y + pNode->GetScrPos().y)));
			m_pRecordset->PutCollect("图形形状", _variant_t(short(Get_Com_ID(pNode))));
			//m_pRecordset->PutCollect("图形线型", _variant_t(short(1)));
			//m_pRecordset->PutCollect("图形线宽", _variant_t(short(1)));
			m_pRecordset->PutCollect("比例", _variant_t(m_model_scale));
			//m_pRecordset->PutCollect("图形颜色", _variant_t(short(1)));
			//m_pRecordset->PutCollect("字体", _variant_t(short(1)));
			//m_pRecordset->PutCollect("字号", _variant_t(short(1)));
			//m_pRecordset->PutCollect("字体颜色", _variant_t(short(1)));
			//m_pRecordset->PutCollect("填充类型", _variant_t(short(1)));
			//m_pRecordset->PutCollect("填充颜色", _variant_t(short(1)));
			//m_pRecordset->PutCollect("正在运行", _variant_t(short(1)));
			//m_pRecordset->PutCollect("分析标志", _variant_t(short(1)));
			m_pRecordset->PutCollect("删除标志",_variant_t(short(0)));
		}
	}
	if (updated==1)
		m_pRecordset->Update();
	m_pRecordset.Release();


	//3. 处理LINE_Table
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from LINE_Table");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//插入数据
	updated=0;
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("LINE_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
	count=LineArray.GetSize();
	CPoint tempPoint;
	for (i=0;i<count;i++)
	{
		Line *pLine=LineArray.GetAt(i);
		if (!pLine->IsDeleted())
		{
			m_pRecordset->AddNew();
			updated=1;
			m_pRecordset->PutCollect("连线号", _variant_t(long(pLine->GetID())));
			//m_pRecordset->PutCollect("任务号", _variant_t(long(2)));
			//m_pRecordset->PutCollect("对象序号", _variant_t(long(2)));
			m_pRecordset->PutCollect("父结点号", _variant_t(long(pLine->parentNode->GetID())));
			//m_pRecordset->PutCollect("父结点类型", _variant_t(short(1)));
			m_pRecordset->PutCollect("父结点层号", _variant_t(long(pLine->parentNode->layer)));
			//m_pRecordset->PutCollect("父结点层中号", _variant_t(long(2)));
			m_pRecordset->PutCollect("子结点号", _variant_t(long(pLine->sonNode->GetID())));
			//m_pRecordset->PutCollect("子结点类型", _variant_t(short(1)));
			m_pRecordset->PutCollect("子结点层号", _variant_t(long(pLine->sonNode->layer)));
			//m_pRecordset->PutCollect("子结点层中号", _variant_t(long(2)));
			m_pRecordset->PutCollect("连线名称", _variant_t(pLine->GetName()));
			//m_pRecordset->PutCollect("连线中文名称", _variant_t(pLine->GetName()));
			m_pRecordset->PutCollect("连线描述", _variant_t(pLine->comment));

			pLine->parentNode->GetCom()->GetBottomCenter((unsigned long)&tempPoint);
			m_pRecordset->PutCollect("连线起点X", _variant_t(long(tempPoint.x+pLine->parentNode->GetScrPos().x)));
			m_pRecordset->PutCollect("连线起点Y", _variant_t(long(tempPoint.y+pLine->parentNode->GetScrPos().y)));
			pLine->sonNode->GetCom()->GetTopCenter((unsigned long)&tempPoint);
			m_pRecordset->PutCollect("连线终点X", _variant_t(long(tempPoint.x+pLine->sonNode->GetScrPos().x)));
			m_pRecordset->PutCollect("连线终点Y", _variant_t(long(tempPoint.y+pLine->sonNode->GetScrPos().y)));

			m_pRecordset->PutCollect("连线类型", _variant_t(short(pLine->GetGraphInfo()->normal_penStyle)));
			m_pRecordset->PutCollect("连线宽度", _variant_t(short(pLine->GetGraphInfo()->normal_linewidth)));
			m_pRecordset->PutCollect("连线颜色", _variant_t(short(pLine->GetGraphInfo()->normal_linecolor)));
			//m_pRecordset->PutCollect("箭头类型", _variant_t(short(1)));
			//m_pRecordset->PutCollect("分析标志", _variant_t(short(1)));
			m_pRecordset->PutCollect("删除标志",_variant_t(short(0)));
		}
	}
	if (updated==1)
		m_pRecordset->Update();
	m_pRecordset.Release();

	if(m_pConnection->State)
		m_pConnection->Close();
	return true;
}

//该模型是否已经存在
int CDiagRunView::if_exist_model(CString model_name)
{
	int count=ModelArray.GetSize();
	for (int i=0; i<count; i++)
		if (ModelArray.GetAt(i).CompareNoCase(model_name))
			return i;
	return -1;
}

//创建一个模型
BOOL CDiagRunView::create_one_model(CString model_name)
{
	char sql_cmd[500];
	CString Datasource;
	HRESULT hr;

	m_sqlserver_db.dbname=model_name;
	
	//创建一个数据库
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=GPES; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create database ");
	strcat(sql_cmd,model_name);
	exec_sql(sql_cmd);
	m_pRecordset.Release();
	m_pConnection->Close();

	//连接该模型数据库
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	
	//创建该模型内的各表
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table OBJECT_Table(结点序号 int identity primary key, 对象号 int, 任务号 int, 对象名称 varchar(50), 对象描述 varchar(200))");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table NODES_Table(结点序号 int identity primary key, 结点号 int, 任务号 int, 对象序号 int, 层号 int, 层中序号 int, 父结点号 int, 结点名称 varchar(50), 结点中文名称 varchar(50), 结点描述 varchar(100), X坐标 int, Y坐标 int, 图形形状 smallint, 图形线型 smallint, 图形线宽 smallint, 比例 float, 图形颜色 smallint, 字体 smallint, 字号 smallint, 字体颜色 smallint, 填充类型 smallint, 填充颜色 smallint, 正在运行 smallint, 分析标志 smallint, 删除标志 smallint)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table LINE_Table(连线序号 int identity primary key, 连线号 int, 任务号 int, 对象序号 int, 父结点号 int, 父结点类型 smallint, 父结点层号 int, 父结点层中号 int, 子结点号 int, 子结点类型 smallint, 子结点层号 int, 子结点层中号 int, 连线名称 varchar(50), 连线中文名称 varchar(50), 连线描述 varchar(100), 连线起点X int, 连线起点Y int, 连线终点X int, 连线终点Y int, 连线类型 smallint, 连线宽度 smallint, 连线颜色 smallint, 箭头类型 smallint, 分析标志 smallint, 删除标志 smallint)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table DATA_Table(征兆数据ID号 int identity primary key, 结点号 int, 征兆数据描述 varchar(50), 征兆数据标准值 float)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table RULE_Table(规则ID号 int identity primary key, 规则序号 int, 结点号 int, 任务号 int, 对象序号 int, 规则名 varchar(40), 规则内容 varchar(200), 规则输出 int, 结果描述 varchar(100), 可信度 float)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pConnection->Close();
	return true;
}

//删除一个模型
BOOL CDiagRunView::delete_one_model(CString model_name)
{
	char sql_cmd[500];
	CString Datasource;
	HRESULT hr;
	
	//不释放, 删不掉
	m_pConnection.Release();
	hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象

	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=GPES; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///连接数据库
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"drop database ");
	strcat(sql_cmd,model_name);
	exec_sql(sql_cmd);
	m_pRecordset.Release();
	m_pConnection->Close();
	return true;
}

void CDiagRunView::CreateTree_OnOpen(Node *node, HTREEITEM parent_item, CModelTree *pTreeView, CTreeCtrl& m_ctlTree)
{
	if (node->IsDeleted()) 
		return;
	else
	{
		int treecount = m_ctlTree.GetCount();
		pTreeView->m_Tree.TreeItem[treecount-1]=m_ctlTree.InsertItem(node->GetName(),0,1,parent_item,TVI_LAST);
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

void CDiagRunView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

//	COpenModelDlg dlg;
//	if (dlg.DoModal()==IDCANCEL)
//		return;
//	CreateGraph(dlg.SelectItemText);

	CScrollView::OnPrepareDC(pDC, pInfo);
}

void CDiagRunView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 5000;
	SetScrollSizes(MM_TEXT, sizeTotal);
	


}
//xnf 添加代码
void CDiagRunView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	CClientDC dc(this);
	//dc.SetROP2(R2_NOTXORPEN);
/*	dc.SetBkMode(TRANSPARENT);
	
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
		node->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, isActive);
	}
	count = LineArray.GetSize();
	for (i=0; i<count; i++)
	{
		line = LineArray.GetAt(i);
		if ( line->IsDeleted() )
			continue;
		isActive = line->GetActive();
		line->DrawOffset(&dc, 0, scrollpos, m_model_scale, 0, 1, isActive);
	}
	// TODO: add draw code here*/
}
//xnf
void CDiagRunView::CreateGraph(CString NodeName)
{
	m_cur_model_name=NodeName;
	clear_nodearray_linearray();
	read_one_model(m_cur_model_name);
	SelectedObjects.RemoveAll();
	curObject = NULL;
	ModelDeleteArea.data_flag=0;
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
	//	if (pNode->inLine==NULL)
//			CreateTree_OnOpen(pNode,pTreeView->m_Tree.root,pTreeView,m_ctlTree);
	}
//	delete pNode;
}

void CDiagRunView::OnSelectmodel() 
{
	// TODO: Add your command handler code here
	COpenModelDlg dlg;
	if (dlg.DoModal()==IDCANCEL)
		return;
	CreateGraph(dlg.SelectItemText);
}
