// ReportDefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "ReportDefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDefDlg dialog


CReportDefDlg::CReportDefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportDefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportDefDlg)
	m_outnode = FALSE;
	m_rule_id = FALSE;
	m_task_id = FALSE;
	m_node_name = FALSE;
	m_comp_name = FALSE;
	//}}AFX_DATA_INIT
}


void CReportDefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDefDlg)
	DDX_Check(pDX, IDC_CHECK_OUTNODE, m_outnode);
	DDX_Check(pDX, IDC_CHECK_RULE_ID, m_rule_id);
	DDX_Check(pDX, IDC_CHECK_TASK_ID, m_task_id);
	DDX_Check(pDX, IDC_CHECK_NODE_NAME, m_node_name);
	DDX_Check(pDX, IDC_CHECK_COMP_NAME, m_comp_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDefDlg, CDialog)
	//{{AFX_MSG_MAP(CReportDefDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDefDlg message handlers
