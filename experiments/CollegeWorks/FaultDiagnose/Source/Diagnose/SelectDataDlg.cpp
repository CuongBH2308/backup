// SelectDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "SelectDataDlg.h"
#include "mainfrm.h"
#include "modelview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDataDlg dialog


CSelectDataDlg::CSelectDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDataDlg)
	m_select_time = _T("");
	//}}AFX_DATA_INIT
}


void CSelectDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDataDlg)
	DDX_Control(pDX, IDC_DataCombo, m_DataCombo);
	DDX_CBString(pDX, IDC_DataCombo, m_select_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDataDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDataDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDataDlg message handlers

CString Datastr[10000];

BOOL CSelectDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame * pFrm = (CMainFrame *)AfxGetMainWnd();
	CModelView *pView = (CModelView *)(pFrm->m_wndSplitter1.GetPane(0,1));

	try
	{
		_RecordsetPtr m_pRecordset1;
		m_pRecordset1.CreateInstance("ADODB.Recordset");
		m_pRecordset1->Open("DATATEST_Table",_variant_t((IDispatch*)pView->m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdTable);
		int n=0;
		while(!m_pRecordset1->EndOfFile)
		{
			m_DataCombo.AddString(pView->vartostr(m_pRecordset1->GetCollect("时间")));
			Datastr[n++]=pView->vartostr(m_pRecordset1->GetCollect("数据"));
			m_pRecordset1->MoveNext();
		}
		m_DataCombo.SetCurSel(0);
		m_pRecordset1.Release();
	}

	catch(_com_error e)///捕捉异常
	{
		MessageBox("读取DATATEST_Table失败!","错误");///显示错误信息
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDataDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int no;
	no=m_DataCombo.FindStringExact(0,m_select_time);
	if (no==CB_ERR)
	{
		MessageBox("时间不在列表范围内","警告");
		return;
	}
	m_select_data=Datastr[no];
	CDialog::OnOK();
}
