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
extern BOOL mousemoving;							//����Ƿ����ƶ�������
extern BOOL mousedown;								//����Ƿ���£�������δ�ͷ�

//10.20���
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
//����ɾ��������
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
	AfxOleInit();///��ʼ��COM��
	HRESULT hr;
	hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
	if(!SUCCEEDED(hr))
	{
		AfxMessageBox("����m_pConnectionʧ��!");
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
	Item=m_ctlTree.InsertItem(m_ctlTree.GetItemText(m_startItem),0,1,pItem,nItem);
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
		nItem=m_ctlTree.InsertItem(m_ctlTree.GetItemText(nextItem),0,1,pItem,nItem);
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

//���ݽ��Ų���node
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

/*----------------------ADO��ȡ���͵�ת��----------------------*/
CString vartostr(const _variant_t &var)
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
BOOL CDiagRunView::exec_sql(char *sql_cmd)
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
BOOL CDiagRunView::read_one_model(CString model_name)
{
	m_sqlserver_db.dbname=CString(model_name);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CString Datasource;
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
	HRESULT hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
	//����һ���������ִ��е�Provider�����SQL Server������
	
	/*��������*/
/*
	//������������Ա�
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("OBJECT_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
		while(!m_pRecordset->adoEOF)
		{
			m_pRecordset->GetCollect("�������");
			m_pRecordset->GetCollect("�����");
			m_pRecordset->GetCollect("�����");
			m_pRecordset->GetCollect("��������");
			m_pRecordset->GetCollect("��������");

			//?=vartostr();

			m_pRecordset->MoveNext();
		}
		m_pRecordset.Release();
	}
	catch(_com_error e)///��׽�쳣
	{
		AfxMessageBox("��ȡ����������Ա�ʧ��!");///��ʾ������Ϣ
	}
*/
	//������
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open("NODES_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
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
			//m_pRecordset->GetCollect("�������");
			value=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("���"))));
			node->layer=value;
			//m_pRecordset->GetCollect("�������");
			//m_pRecordset->GetCollect("������");
			node->inLine=NULL;
			node->SetName(vartostr(m_pRecordset->GetCollect("�������")));
			//m_pRecordset->GetCollect("�����������");
			node->comment=vartostr(m_pRecordset->GetCollect("�������"));
			CPoint pos1, pos2;
			/*
			pos1.x=0;
			pos1.y=0;
			pos2.x=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("X����"))));
			pos2.y=atol(LPCTSTR(vartostr(m_pRecordset->GetCollect("Y����"))));
			node->SetScrPos(pos1);		
			node->SetTopLeft(pos2);
			*/

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
			//m_pRecordset->GetCollect("����");
			//m_pRecordset->GetCollect("�ֺ�");
			//m_pRecordset->GetCollect("������ɫ");
			//m_pRecordset->GetCollect("�������");
			gi->normal_regioncolor=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("�����ɫ"))));
			node->SetGraphInfo(gi);
			//m_pRecordset->GetCollect("��������");
			//m_pRecordset->GetCollect("������־");
			int flag=atoi(LPCTSTR(vartostr(m_pRecordset->GetCollect("ɾ����־"))));
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
	catch(_com_error e)///��׽�쳣
	{
		AfxMessageBox("��ȡ����ʧ��!");///��ʾ������Ϣ
	}
	
	//�����߱�
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
		AfxMessageBox("��ȡ���߱�ʧ��!");///��ʾ������Ϣ
	}

	if(m_pConnection->State)
		 m_pConnection->Close(); ///����Ѿ�����������ر���
	return true;
}

//�洢һ�����е�ģ��
BOOL CDiagRunView::save_one_model(CString model_name)
{
	CString Datasource;
	HRESULT hr;
	char sql_cmd[500];
	int i;
	int updated;

	m_sqlserver_db.dbname=model_name;
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
	
	//1. ����OBJECT_Table
/*
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from OBJECT_Table");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//��������
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open("OBJECT_Table",_variant_t((IDispatch*)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdTable);
	m_pRecordset->AddNew();
	m_pRecordset->PutCollect("�����", _variant_t(long(2)));
	m_pRecordset->PutCollect("�����", _variant_t(long(2)));
	m_pRecordset->PutCollect("��������", _variant_t(""));
	m_pRecordset->PutCollect("��������", _variant_t(""));
	//�������� ��������
	
	m_pRecordset->Update();
	m_pRecordset.Release();
*/

	//2. ����NODES_Table
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from NODES_Table");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//��������
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
			m_pRecordset->PutCollect("����", _variant_t(long(pNode->GetID())));
			//m_pRecordset->PutCollect("�����", _variant_t(long(2)));
			//m_pRecordset->PutCollect("�������", _variant_t(long(2)));
			m_pRecordset->PutCollect("���", _variant_t(long(pNode->layer)));
			//m_pRecordset->PutCollect("�������", _variant_t(long(2)));
			if (pNode->inLine==NULL)
				m_pRecordset->PutCollect("������", _variant_t(long(-1)));
			else
				m_pRecordset->PutCollect("������", _variant_t(long(pNode->inLine->parentNode->GetID())));
			m_pRecordset->PutCollect("�������", _variant_t(pNode->GetName()));
			//m_pRecordset->PutCollect("�����������", _variant_t(pNode->GetName()));
			m_pRecordset->PutCollect("�������", _variant_t(pNode->comment));
			m_pRecordset->PutCollect("X����", _variant_t(long(pNode->GetTopLeft().x + pNode->GetScrPos().x)));
			m_pRecordset->PutCollect("Y����", _variant_t(long(pNode->GetTopLeft().y + pNode->GetScrPos().y)));
			m_pRecordset->PutCollect("ͼ����״", _variant_t(short(Get_Com_ID(pNode))));
			//m_pRecordset->PutCollect("ͼ������", _variant_t(short(1)));
			//m_pRecordset->PutCollect("ͼ���߿�", _variant_t(short(1)));
			m_pRecordset->PutCollect("����", _variant_t(m_model_scale));
			//m_pRecordset->PutCollect("ͼ����ɫ", _variant_t(short(1)));
			//m_pRecordset->PutCollect("����", _variant_t(short(1)));
			//m_pRecordset->PutCollect("�ֺ�", _variant_t(short(1)));
			//m_pRecordset->PutCollect("������ɫ", _variant_t(short(1)));
			//m_pRecordset->PutCollect("�������", _variant_t(short(1)));
			//m_pRecordset->PutCollect("�����ɫ", _variant_t(short(1)));
			//m_pRecordset->PutCollect("��������", _variant_t(short(1)));
			//m_pRecordset->PutCollect("������־", _variant_t(short(1)));
			m_pRecordset->PutCollect("ɾ����־",_variant_t(short(0)));
		}
	}
	if (updated==1)
		m_pRecordset->Update();
	m_pRecordset.Release();


	//3. ����LINE_Table
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"delete from LINE_Table");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	//��������
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
			m_pRecordset->PutCollect("���ߺ�", _variant_t(long(pLine->GetID())));
			//m_pRecordset->PutCollect("�����", _variant_t(long(2)));
			//m_pRecordset->PutCollect("�������", _variant_t(long(2)));
			m_pRecordset->PutCollect("������", _variant_t(long(pLine->parentNode->GetID())));
			//m_pRecordset->PutCollect("���������", _variant_t(short(1)));
			m_pRecordset->PutCollect("�������", _variant_t(long(pLine->parentNode->layer)));
			//m_pRecordset->PutCollect("�������к�", _variant_t(long(2)));
			m_pRecordset->PutCollect("�ӽ���", _variant_t(long(pLine->sonNode->GetID())));
			//m_pRecordset->PutCollect("�ӽ������", _variant_t(short(1)));
			m_pRecordset->PutCollect("�ӽ����", _variant_t(long(pLine->sonNode->layer)));
			//m_pRecordset->PutCollect("�ӽ����к�", _variant_t(long(2)));
			m_pRecordset->PutCollect("��������", _variant_t(pLine->GetName()));
			//m_pRecordset->PutCollect("������������", _variant_t(pLine->GetName()));
			m_pRecordset->PutCollect("��������", _variant_t(pLine->comment));

			pLine->parentNode->GetCom()->GetBottomCenter((unsigned long)&tempPoint);
			m_pRecordset->PutCollect("�������X", _variant_t(long(tempPoint.x+pLine->parentNode->GetScrPos().x)));
			m_pRecordset->PutCollect("�������Y", _variant_t(long(tempPoint.y+pLine->parentNode->GetScrPos().y)));
			pLine->sonNode->GetCom()->GetTopCenter((unsigned long)&tempPoint);
			m_pRecordset->PutCollect("�����յ�X", _variant_t(long(tempPoint.x+pLine->sonNode->GetScrPos().x)));
			m_pRecordset->PutCollect("�����յ�Y", _variant_t(long(tempPoint.y+pLine->sonNode->GetScrPos().y)));

			m_pRecordset->PutCollect("��������", _variant_t(short(pLine->GetGraphInfo()->normal_penStyle)));
			m_pRecordset->PutCollect("���߿��", _variant_t(short(pLine->GetGraphInfo()->normal_linewidth)));
			m_pRecordset->PutCollect("������ɫ", _variant_t(short(pLine->GetGraphInfo()->normal_linecolor)));
			//m_pRecordset->PutCollect("��ͷ����", _variant_t(short(1)));
			//m_pRecordset->PutCollect("������־", _variant_t(short(1)));
			m_pRecordset->PutCollect("ɾ����־",_variant_t(short(0)));
		}
	}
	if (updated==1)
		m_pRecordset->Update();
	m_pRecordset.Release();

	if(m_pConnection->State)
		m_pConnection->Close();
	return true;
}

//��ģ���Ƿ��Ѿ�����
int CDiagRunView::if_exist_model(CString model_name)
{
	int count=ModelArray.GetSize();
	for (int i=0; i<count; i++)
		if (ModelArray.GetAt(i).CompareNoCase(model_name))
			return i;
	return -1;
}

//����һ��ģ��
BOOL CDiagRunView::create_one_model(CString model_name)
{
	char sql_cmd[500];
	CString Datasource;
	HRESULT hr;

	m_sqlserver_db.dbname=model_name;
	
	//����һ�����ݿ�
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=GPES; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create database ");
	strcat(sql_cmd,model_name);
	exec_sql(sql_cmd);
	m_pRecordset.Release();
	m_pConnection->Close();

	//���Ӹ�ģ�����ݿ�
	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=%s; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.dbname,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
	
	//������ģ���ڵĸ���
	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table OBJECT_Table(������ int identity primary key, ����� int, ����� int, �������� varchar(50), �������� varchar(200))");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table NODES_Table(������ int identity primary key, ���� int, ����� int, ������� int, ��� int, ������� int, ������ int, ������� varchar(50), ����������� varchar(50), ������� varchar(100), X���� int, Y���� int, ͼ����״ smallint, ͼ������ smallint, ͼ���߿� smallint, ���� float, ͼ����ɫ smallint, ���� smallint, �ֺ� smallint, ������ɫ smallint, ������� smallint, �����ɫ smallint, �������� smallint, ������־ smallint, ɾ����־ smallint)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table LINE_Table(������� int identity primary key, ���ߺ� int, ����� int, ������� int, ������ int, ��������� smallint, ������� int, �������к� int, �ӽ��� int, �ӽ������ smallint, �ӽ���� int, �ӽ����к� int, �������� varchar(50), ������������ varchar(50), �������� varchar(100), �������X int, �������Y int, �����յ�X int, �����յ�Y int, �������� smallint, ���߿�� smallint, ������ɫ smallint, ��ͷ���� smallint, ������־ smallint, ɾ����־ smallint)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table DATA_Table(��������ID�� int identity primary key, ���� int, ������������ varchar(50), �������ݱ�׼ֵ float)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pRecordset.CreateInstance("ADODB.Recordset");
	strcpy(sql_cmd,"create table RULE_Table(����ID�� int identity primary key, ������� int, ���� int, ����� int, ������� int, ������ varchar(40), �������� varchar(200), ������� int, ������� varchar(100), ���Ŷ� float)");
	exec_sql(sql_cmd);
	m_pRecordset.Release();

	m_pConnection->Close();
	return true;
}

//ɾ��һ��ģ��
BOOL CDiagRunView::delete_one_model(CString model_name)
{
	char sql_cmd[500];
	CString Datasource;
	HRESULT hr;
	
	//���ͷ�, ɾ����
	m_pConnection.Release();
	hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����

	Datasource.Format("Provider=SQLOLEDB.1; Data Source=%s; Initial Catalog=GPES; User ID=%s; PWD=%s", m_sqlserver_db.dbsrc,m_sqlserver_db.user,m_sqlserver_db.pass);
	hr = m_pConnection->Open(_bstr_t(LPCTSTR(Datasource)),"","",-1);///�������ݿ�
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
//xnf ��Ӵ���
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
