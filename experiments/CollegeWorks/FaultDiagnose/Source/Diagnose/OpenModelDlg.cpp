// OpenModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "OpenModelDlg.h"
#include "ModelView.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenModelDlg dialog


COpenModelDlg::COpenModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenModelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenModelDlg)
	m_select_model = _T("");
	//}}AFX_DATA_INIT
}


void COpenModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenModelDlg)
	DDX_Control(pDX, IDC_ModelCombo, m_ModelCombo);
	DDX_CBString(pDX, IDC_ModelCombo, m_select_model);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenModelDlg, CDialog)
	//{{AFX_MSG_MAP(COpenModelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenModelDlg message handlers

void COpenModelDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_ModelCombo.FindStringExact(0,m_select_model)==CB_ERR)
	{
		MessageBox("模型名不在列表范围内","警告");
		return;
	}
	CDialog::OnOK();
}


BOOL COpenModelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelView *pModel = (CModelView *)pFWnd->m_wndSplitter1.GetPane(0,1);
	int count=pModel->ModelArray.GetSize();
	for (int i=0;i<count;i++)
	{
		CString str=pModel->ModelArray.GetAt(i);
		//if (str!=pModel->m_cur_model_name)  //当前模型禁止被重读
		m_ModelCombo.AddString(str);
	}

	UpdateData(FALSE);
	
	m_ModelCombo.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
