// ZoomLevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "ZoomLevelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomLevelDlg dialog


CZoomLevelDlg::CZoomLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomLevelDlg)
	m_ZoomPercentage = 100;
	
	//}}AFX_DATA_INIT
}


void CZoomLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomLevelDlg)
	DDX_Control(pDX, IDC_ZOOMSPIN, m_ZoomSpin);
	DDX_Text(pDX, IDC_ZOOMEDIT, m_ZoomPercentage);
	DDV_MinMaxInt(pDX, m_ZoomPercentage, 1, 2000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomLevelDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomLevelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomLevelDlg message handlers

BOOL CZoomLevelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ZoomSpin.SetRange(1, 2000);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
