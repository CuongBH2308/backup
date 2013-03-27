// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyCalculator.h"
#include "CalculatorDlg.h"

#include<iostream>
#include "CalculatorLib/LogicWordAnalyser.h"
#include "CalculatorLib/LogicSyntaxAnalyser.h"
#include "CalculatorLib/LogicPriorityTable.h"
#include "CalculatorLib/Calculator.h"
#include "CalculatorLib/ArithWordAnalyser.h"
#include "CalculatorLib/ArithSyntaxAnalyser.h"
#include "CalculatorLib/ArithPriorityTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent),m_bModify(false)
{
	//{{AFX_DATA_INIT(CCalculatorDlg)
	m_CalType = -1;
	m_strExp = _T("!(5>3)|6>3&6>7");
	m_strResult = _T("");
	m_VarName = _T("");
	m_dVarValue = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculatorDlg)
	DDX_Control(pDX, IDC_LIST_VARS, m_VarsList);
	DDX_Radio(pDX, IDC_RADIO_TYPE1, m_CalType);
	DDX_Text(pDX, IDC_EDITEXP, m_strExp);
	DDX_Text(pDX, IDC_EDITRESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_VARNAME, m_VarName);
	DDX_Text(pDX, IDC_EDIT_VARVALUE, m_dVarValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONCAL, OnButtoncal)
	ON_BN_CLICKED(IDC_RADIO_TYPE1, OnRadioType1)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, OnRadioType2)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BTNSETUPVAR, OnBtnsetupvar)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, OnButtonSubmit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_LBN_SELCHANGE(IDC_LIST_VARS, OnSelchangeListVars)
	ON_LBN_DBLCLK(IDC_LIST_VARS, OnDblclkListVars)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	GetWindowRect(&m_rclarge);
	
	CWnd* pWndLandmark=GetDlgItem(IDC_SPLIT);
	ASSERT(pWndLandmark);
	pWndLandmark->GetWindowRect(&m_rcsmall);

	SetWindowPos(NULL,0,0,m_rcsmall.right,m_rcsmall.bottom,
		SWP_NOMOVE|SWP_NOZORDER);
	
	m_CalType = 0;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


bool CCalculatorDlg::IsAlpha(char ch){
	if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z'))
		return true;
	return false;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalculatorDlg::OnButtoncal() 
{
	UpdateData(TRUE);

	
	if(m_CalType == 0){

		CLogicWordAnalyser lwa;//("U>0",c);
		CLogicSyntaxAnalyser lsa;
		CLogicPriorityTable lpt;
		
		//CCalculator cl(lwa,lsa,lpt,m_strExp.GetBuffer(0));

		m_Cal.SetExpression(m_strExp.GetBuffer(0));
		m_Cal.SetAnalyser(lwa,lsa,lpt);
		bool bResult;
		int Ret = m_Cal.Calculate(bResult);
		if( Ret == SUCCESSED){
			
			if(bResult) m_strResult = "true";
			else        m_strResult = "false";
		}
		else if(Ret == WORD_ERR){
			AfxMessageBox("词法错误!!!");
		}
		else if(Ret == SYNTAX_ERR){
			AfxMessageBox("语法错误!!!");
		}
		else if(Ret == NO_VALUE){
			AfxMessageBox("变量没有值!!!");
		}


	}

	if(m_CalType == 1){
		CArithWordAnalyser awa;//("U>0",c);
		CArithSyntaxAnalyser asa;
		CArithPriorityTable apt;
		//CCalculator ca(awa,asa,apt,m_strExp.GetBuffer(0));
		m_Cal.SetExpression(m_strExp.GetBuffer(0));
		m_Cal.SetAnalyser(awa,asa,apt);
		double dResult;

		int Ret = m_Cal.Calculate(dResult);

		if( Ret == SUCCESSED){
			
			m_strResult.Format("%f",dResult);
		}
		else if(Ret == WORD_ERR){
			AfxMessageBox("词法错误!!!");
		}
		else if(Ret == SYNTAX_ERR){
			AfxMessageBox("语法错误!!!");
		}
		else if(Ret == NO_VALUE){
			AfxMessageBox("变量没有值!!!");
		}
		
		
	}

	UpdateData(FALSE);
	
}

void CCalculatorDlg::OnRadioType1() 
{

	if(m_CalType == 1){
		m_strExp = "";
		m_strResult = "";
		m_CalType = 0;
		UpdateData(FALSE);
	}
	
}

void CCalculatorDlg::OnRadioType2() 
{
	if(m_CalType == 0){
		m_strExp = "";
		m_strResult = "";
		m_CalType = 1;
		UpdateData(FALSE);
	}
	
}

void CCalculatorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == VK_ESCAPE )
		PostQuitMessage(0);
	
	if(nChar == VK_RETURN)
		OnButtoncal() ;

		
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCalculatorDlg::OnBtnsetupvar() 
{
	static bool bShow = false;
	
	if(bShow == false){
		SetWindowPos(NULL,0,0,m_rclarge.Width(),m_rclarge.Height(),
			SWP_NOMOVE|SWP_NOZORDER);

		SetDlgItemText(IDC_BTNSETUPVAR,"<<变量设置");
		
		bShow = true;
	}
	
	else{
		SetWindowPos(NULL,0,0,m_rcsmall.right,m_rcsmall.bottom,
			SWP_NOMOVE|SWP_NOZORDER);

		SetDlgItemText(IDC_BTNSETUPVAR,"变量设置>>");
		bShow = false;
	}
	// TODO: Add your control notification handler code here
	
}

void CCalculatorDlg::OnButtonSubmit() 
{
	UpdateData(TRUE);

	if(m_bModify == false){  //添加

		if(m_VarName.GetLength() == 0){
			AfxMessageBox("变量名不能为空!!!");
			return ;
		}
		
		if(m_Cal.AddVariable(m_VarName.GetBuffer(0),m_dVarValue) == false){
			AfxMessageBox("变量已存在或变量名非法!!!");
			return ;
		}
		
		CString str1,str2;
		str1.Format("%8.4f",m_dVarValue);
		
		str2.Format("%-20s",m_VarName.GetBuffer(0));

	//_Cal.AddVariable(m_VarName.GetBuffer(0),m_dVarValue);

		m_VarsList.AddString(str2+str1);
	}

	else{

		CString str,str1,str2;

		m_bModify = false; 
		
		int index = m_VarsList.GetCurSel();	
		if(index == LB_ERR) return;
		
		m_VarsList.GetText(index,str);
		
		str1 = str.Left(20);//变量名最长为20
		
		str1.TrimRight();

		if(str1 == m_VarName){  //没有改变变量名
			m_VarsList.DeleteString(index);
			m_Cal.SetVarValue(m_VarName.GetBuffer(0),m_dVarValue);

			str1.Format("%8.4f",m_dVarValue);
			
			str2.Format("%-20s",m_VarName.GetBuffer(0));
			
			//m_VarsList.AddString(str2+str1);
			m_VarsList.InsertString(index,str2+str1);

		}

		else{                                                //改变变量名
			
			str1.TrimRight();

			str2 =str1;
			
			
			if(m_VarName.GetLength() == 0){
				AfxMessageBox("变量名不能为空!!!");
				return ;
			}
			
			for(int i = 0;i<m_VarName.GetLength();i++){
				if(!IsAlpha(m_VarName[i])){
					AfxMessageBox("变量名非法!!!");
				    return ;
				}
					
			}



			m_Cal.DeleteVar(str2.GetBuffer(0));	
			m_VarsList.DeleteString(index);

		


		
		    m_Cal.AddVariable(m_VarName.GetBuffer(0),m_dVarValue);
			str1.Format("%8.4f",m_dVarValue);
			
			str2.Format("%-20s",m_VarName.GetBuffer(0));
			
			m_VarsList.AddString(str2+str1);
		}

		

		
	}
	
           	
}

void CCalculatorDlg::OnButtonDelete() 
{
	m_bModify = false;
	CString str,str1;
    int index = m_VarsList.GetCurSel();	
	if(index == LB_ERR) return;
	m_VarsList.GetText(index,str);
	str1 = str.Left(20);//变量名最长为20
	str1.TrimRight();
//	AfxMessageBox(str1);

	m_Cal.DeleteVar(str1.GetBuffer(0)); //从变量表中删除
	
	m_VarsList.DeleteString(index);//从列表中删除

	


}

void CCalculatorDlg::OnButtonModify() 
{

	m_bModify = true;

	CString str,str1,str2;

	int index = m_VarsList.GetCurSel();	

	if(index == LB_ERR){
		m_bModify = false;
		return;
	}

	m_VarsList.GetText(index,str);

	str1 = str.Left(20);//变量名最长为20

	str1.TrimRight();

	m_VarName = str1;

	str2 = str.Right(str.GetLength()-20);
	str2.TrimLeft();
	//AfxMessageBox(str2);
	
	m_dVarValue = atof(str2.GetBuffer(0));
	
//	m_Cal.DeleteVar(str1.GetBuffer(0)); //从变量表中删除
	
//	m_VarsList.DeleteString(index);//从列表中删除


	UpdateData(FALSE);
}

void CCalculatorDlg::OnSelchangeListVars() 
{

	m_bModify = false;
	
}

void CCalculatorDlg::OnDblclkListVars() 
{
	OnButtonModify() ;
	
	
}

BOOL CCalculatorDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	
		
	return CDialog::PreCreateWindow(cs);
}

int CCalculatorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString WindowText = "多功能表达式计算";
	SetWindowText((LPCTSTR)WindowText);//m_WindowText可以是一个CString类的变量。 	// TODO: Add your specialized creation code here
	
	return 0;
}
