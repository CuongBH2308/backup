// ReportShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diagnose.h"
#include "ReportShowDlg.h"
#include "mainfrm.h"
#include "modelview.h"
#include "PreParent.h"	
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportShowDlg dialog

static int fieldnum;
extern CString DiagnoseResult;

CReportShowDlg::CReportShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportShowDlg)
	//}}AFX_DATA_INIT
}


void CReportShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportShowDlg)
	DDX_Control(pDX, IDC_REPORTLIST, m_reportlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportShowDlg, CDialog)
	//{{AFX_MSG_MAP(CReportShowDlg)
	ON_BN_CLICKED(IDSAVEREPORT, OnSavereport)
	ON_BN_CLICKED(IDPRINTREPORT, OnPrintreport)
	ON_BN_CLICKED(IDC_PRIVIEW, OnPriview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportShowDlg message handlers


BOOL CReportShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame *pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelView *pModel = (CModelView *)pFWnd->m_wndSplitter1.GetPane(0,1);
	
	m_reportlist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int i,j,nItem=0;
	fieldnum=pModel->ReportOutFields.GetSize();
	CString fieldname;
	int collen;
	for (i=0;i<fieldnum;i++)
	{
		fieldname=pModel->ReportOutFields.GetAt(i);
		if (fieldname=="�������" || fieldname=="��������" || fieldname=="������")
			collen=130;
		else
			collen=80;
		m_reportlist.InsertColumn(nItem++, fieldname, LVCFMT_LEFT, collen);
	}

	//�����¼
	CString value;
	for (i=0;i<pModel->reason_step_count;i++)
	{
		value.Format("%ld",pModel->reason_step[i].step_id);
		nItem = m_reportlist.InsertItem(0xFFFFFF, value);
		int nSub = 1;
		for (j=1;j<fieldnum;j++)
		{
			fieldname=pModel->ReportOutFields.GetAt(j);
			if (fieldname=="�����")
				value.Format("%ld",pModel->reason_step[i].task_id);
			//else if (fieldname=="����")
			//	value.Format("%ld",pModel->reason_step[i].node_id);
			else if (fieldname=="�������")
				value=pModel->reason_step[i].node_name;
			else if (fieldname=="��������")
				value=pModel->reason_step[i].comp_name;
			else if (fieldname=="�����")
				value.Format("%ld",pModel->reason_step[i].rule_id);
			else if (fieldname=="������")
				value=pModel->reason_step[i].out_node_name;
			m_reportlist.SetItem(nItem, nSub++, 1, value, NULL, 0, 0, 0);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportShowDlg::OnSavereport()
{
	// TODO: Add your control notification handler code here
	CString report;
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CModelView *pModel = (CModelView *)pFWnd->m_wndSplitter1.GetPane(0,1);
	CString filename;

	CFileDialog fd(FALSE, "*.txt|*.xml", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"txt File(.txt)|*.txt|xml File(.xml)|*.xml|");
	if ( fd.DoModal() == IDOK )
		filename = fd.GetPathName();
	else
		return;
	
	CStdioFile file;
	CFileException e;
	file.Open(filename,CFile::modeReadWrite|CFile::modeCreate|CFile::shareDenyNone,&e);
	if (filename.Find(".txt")!=-1)
		report=pModel->ReportOut_by_File();
	else if (filename.Find(".xml")!=-1)
		report=pModel->ReportOut_by_XML();

	file.WriteString(report);
	file.Close();
}
void CReportShowDlg::OnPriview() 
{
	// TODO: Add your control notification handler code here
	if(m_reportlist.GetItemCount()<= 0)
		return;
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_reportlist.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_reportlist.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawInfo, PrnInfo);
	DlgPreView.DoModal();
		
}
void CReportShowDlg::OnPrintreport() 
{
	// TODO: Add your control notification handler code here
	if(m_reportlist.GetItemCount()<= 0)
		return;
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_reportlist.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = TRUE;
	PrnInfo.nCurPage = 1;

	PrnInfo.nMaxLine = m_reportlist.GetItemCount();
	PrnInfo.nCountPage=(m_reportlist.GetItemCount()+29)/30;
	CPreParent DlgPreView;
//	DlgPreView.SetCallBackFun(DrawInfo, PrnInfo);
	CDC memDC;
	
	CPrintInfo printInfo;
	if( AfxGetApp()->GetPrinterDeviceDefaults(&printInfo.m_pPD->m_pd) )
	{
		HDC hDC = printInfo.m_pPD->m_pd.hDC;
		if (hDC == NULL)
			hDC = printInfo.m_pPD->CreatePrinterDC();
		if(hDC !=NULL)
		{
			memDC.Attach(hDC);
		}
		else 
		{
			AfxMessageBox("Can not find printer. Please check installed/default printers.");
			return;
		}
	}

	DrawInfo(memDC, PrnInfo);

}
void CReportShowDlg::DrawInfo(CDC &memDC, PRNINFO PrnInfo)
{
	if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//��ǰҳ
	BOOL IsPrint = PrnInfo.IsPrint;		//�Ƿ��ӡ
	int nMaxPage = PrnInfo.nCountPage;	//���ҳ��
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("��������:%Y-%m-%d");
	csLFinality=csLFinality+"����Ͻ��ۣ�"+DiagnoseResult;
	csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);

	TCHAR szTitle[] = TEXT(" ��Ϲ��̱���");

	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, *oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//ϸ������
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//�ֱ�
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

 	int xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	int yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

	DOUBLE xPix = (DOUBLE)xP*10/254;	//ÿ mm ��ȵ�����
	DOUBLE yPix = (DOUBLE)yP*10/254;	//ÿ mm �߶ȵ�����
	DOUBLE fAdd = 7*yPix;		//ÿ�������
	
	DOUBLE nTop = 25*yPix;		//��һҳ������
	int	  iStart = 0;			//�ӵڼ��п�ʼ��ȡ
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 20*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-20);	//������
	LVCOLUMN lvc;
	char text[30];
	lvc.mask = LVCF_TEXT|LVCF_SUBITEM;
	lvc.pszText = text;
	lvc.cchTextMax = 30;
	HWND hWndHeader = ListView_GetHeader(hList);
    //����У��еĸ���

    int nColCount=fieldnum;
	
	CRect rcH,r;
	DOUBLE xAdd;

    int nLineCount = ListView_GetItemCount(hList);

	//ListView_GetColumn(hList,1, &lvc);
	
	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//������ӡ����
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//��ʼ�ĵ���ӡ
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "���ӵ���ӡ��ʧ��!", "����", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 25*yPix;		//��һҳ������
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("��������:%Y-%m-%d");
				csLFinality=csLFinality+"����Ͻ��ۣ�"+DiagnoseResult;

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//��ʼҳ
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("��ӡʧ��!"), "����", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//��ӡ
					//����
					oldfont = memDC.SelectObject(&TitleFont);
					int nItem = B5_OTHERLINE;
					if(nCurPage == 1)
					{
						nItem = B5_ONELINE;
						rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
						memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					//ϸ��
 					memDC.SelectObject(&DetailFont);
					rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
					//�Ϻ���
					
					memDC.MoveTo(rc.left, rc.top);
					memDC.LineTo(rc.right, rc.top);
//xnf				
					xAdd= rc.Width()/(nColCount);
					int col = 0;
					for(col=0; col<nColCount;col++)
					{
						rt1.SetRect(nLeft+col*xAdd, nTop, nLeft+(col+1)*xAdd, nTop+fAdd);	
						ListView_GetColumn(hList,col, &lvc);
						memDC.DrawText(lvc.pszText, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
					}	
					for(col=0; col<nColCount;col++)
					{
						rt1.SetRect(nLeft+col*rcH.Width(), nTop, nLeft+(col+1)*xAdd, nTop+fAdd);	
						memDC.MoveTo(rt1.right, rt1.top);
						memDC.LineTo(rt1.right, rt1.bottom);

					}	
					memDC.MoveTo(rc.left, rt1.bottom);
					memDC.LineTo(rc.right, rt1.bottom);
					for( col=0; col<nColCount;col++)
					{
						rt1.SetRect(nLeft+col*xAdd, nTop, nLeft+(col+1)*xAdd, nTop+fAdd);	
						memDC.MoveTo(rt1.right, rt1.top);
						memDC.LineTo(rt1.right, rt1.bottom);

					}	
					int nCountItem = ListView_GetItemCount(hList);
					CHAR szID[30]={0};
					memDC.MoveTo(rc.left, rc.bottom);
					memDC.LineTo(rc.right, rc.bottom);
					for(int i=0;i<nItem; i++)
					{
						for ( col=0; col<nColCount;col++)
						{
							ListView_GetItemText(hList, i+iStart, col, szID, 30);
							rt1.SetRect(nLeft+col*xAdd, nTop+(i+1)*fAdd, nLeft+(col+1)*xAdd, nTop+(i+2)*fAdd);	
							memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							memDC.MoveTo(rt1.right, rt1.top);
							memDC.LineTo(rt1.right, rt1.bottom);
						}
								
						//�º���
						memDC.MoveTo(rc.left, rt1.bottom);
						memDC.LineTo(rc.right, rt1.bottom);
						
						rc.top += fAdd;
						rc.bottom += fAdd;
						rt1.top = rc.top;
						rt1.bottom = rc.bottom;
					
						if((i+iStart+1)>=nCountItem)
							break;
 					}
					//��β
					memDC.MoveTo(rc.left, nTop);
					memDC.LineTo(rc.left, rc.bottom);
					//memDC.MoveTo(rc.right, nTop);
					//memDC.LineTo(rc.right, rc.bottom);
					CRect csR;
					csR.SetRect(nLeft, nTop+nItem*fAdd, nLeft+nColCount*xAdd, nTop+(nItem+1)*fAdd);	
					memDC.DrawText(csLFinality, &csR, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText(csRFinality, &csR, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
					memDC.EndPage();
					memDC.SelectObject(oldfont);
				}
			}
			memDC.EndDoc();
		}
	}
	else
	{
		//��ӡԤ��
		
		//�߿���
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	
		//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);
		xAdd= rc.Width()/(nColCount);
		int col=0;
		for(col=0; col<nColCount;col++)
		{
			rt1.SetRect(nLeft+col*xAdd, nTop, nLeft+(col+1)*xAdd, nTop+fAdd);	
			ListView_GetColumn(hList,col, &lvc);
			memDC.DrawText(lvc.pszText, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
		}	
		for( col=0; col<nColCount;col++)
		{
			rt1.SetRect(nLeft+col*xAdd, nTop, nLeft+(col+1)*xAdd, nTop+fAdd);	
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);

		}	
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);
		for( col=0; col<nColCount;col++)
		{
			rt1.SetRect(nLeft+col*xAdd, nTop, nLeft+(col+1)*xAdd, nTop+fAdd);	
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);

		}	
		int nCountItem = ListView_GetItemCount(hList);
		CHAR szID[30]={0};
		memDC.MoveTo(rc.left, rc.bottom);
		memDC.LineTo(rc.right, rc.bottom);
		for(int i=0;i<nItem; i++)
		{
			for ( col=0; col<nColCount;col++)
			{
				ListView_GetItemText(hList, i+iStart, col, szID, 30);
				rt1.SetRect(nLeft+col*xAdd, nTop+(i+1)*fAdd, nLeft+(col+1)*xAdd, nTop+(i+2)*fAdd);	
				memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				memDC.MoveTo(rt1.right, rt1.top);
				memDC.LineTo(rt1.right, rt1.bottom);
			}
					
			//�º���
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
		
			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β
		memDC.MoveTo(rc.left, nTop);
		memDC.LineTo(rc.left, rc.bottom);
		//memDC.MoveTo(rc.right, nTop);
		//memDC.LineTo(rc.right, rc.bottom);
		CRect csR;
		csR.SetRect(nLeft, nTop+(nItem+1)*fAdd, nLeft+nColCount*xAdd, nTop+(nItem+2)*fAdd);	
		memDC.DrawText(csLFinality, &csR, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText(csRFinality, &csR, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);

		memDC.SelectObject(oldfont);
		memDC.SelectObject(hPenOld);
	}
	TitleFont.DeleteObject();
	DetailFont.DeleteObject();
	cPen.DeleteObject();
}
