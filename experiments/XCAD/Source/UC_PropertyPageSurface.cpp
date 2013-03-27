/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "uc_propertypagesurface.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribblend.h"
#include "gr_dlattribtexture.h"
#include "gr_dlsrf.h"
#include "sl_mm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UC_PropertyPageSurface property page

IMPLEMENT_DYNCREATE(UC_PropertyPageSurface, FW_PropertyPage)

UC_PropertyPageSurface::UC_PropertyPageSurface() : FW_PropertyPage(UC_PropertyPageSurface::IDD),
m_pDLSrf(NULL)
{
	//{{AFX_DATA_INIT(UC_PropertyPageSurface)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

UC_PropertyPageSurface::~UC_PropertyPageSurface()
{
}

void UC_PropertyPageSurface::DoDataExchange(CDataExchange* pDX)
{
	FW_PropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UC_PROPERTY_SURFACE_COLOR_R, m_sliderClrR);
	DDX_Control(pDX, IDC_UC_PROPERTY_SURFACE_COLOR_G, m_sliderClrG);
	DDX_Control(pDX, IDC_UC_PROPERTY_SURFACE_COLOR_B, m_sliderClrB);
	DDX_Control(pDX, IDC_UC_PROPERTY_SURFACE_COLOR_A, m_sliderClrA);
	DDX_Control(pDX, IDC_UC_PROPERTY_SURFACE_COLOR,	  m_btnClr);
	DDX_Control(pDX, IDC_UC_PROPERTY_SURFACE_TRANSPARENCY,	  m_btnTransparency);
}

BEGIN_MESSAGE_MAP(UC_PropertyPageSurface, FW_PropertyPage)
	//{{AFX_MSG_MAP(UC_PropertyPageSurface)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_SURFACE_COLOR_R, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_SURFACE_COLOR_G, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_SURFACE_COLOR_B, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_SURFACE_COLOR_A, OnColorChanged)
	ON_BN_CLICKED(IDC_UC_PROPERTY_SURFACE_TEXTURE_PATH_BROWSER, OnTexturePathBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// UC_PropertyPageSurface message handlers

BOOL UC_PropertyPageSurface::OnInitDialog()
{
	FW_PropertyPage::OnInitDialog();

	SetObj(m_pDLSrf);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void UC_PropertyPageSurface::SetObj(GR_DL* pObj)
{
	if(pObj)
		m_pDLSrf = dynamic_cast<GR_DLSrf*>(pObj);
	if(GetSafeHwnd())
	{
		if(!m_pDLSrf)
			Enable(FALSE);
		else
		{
			Enable(TRUE);
			Update(FALSE);
		}
	}
}

BOOL UC_PropertyPageSurface::OnApply()
{
	if(!m_pDLSrf)
		return FALSE;
	Update();
	m_pDLSrf->Invalidate();
	return TRUE;
}

// Update data according to the setting in the UI
void UC_PropertyPageSurface::Update(BOOL bToData)
{
	const GR_DLAttribPtrVect& vAttrib = m_pDLSrf->GetAttribs();
	for(GR_DLAttribPtrVect::const_iterator it = vAttrib.begin(); it != vAttrib.end(); it++)
	{
		GR_DLAttribColor* pDLAttribColor = dynamic_cast<GR_DLAttribColor*>((*it).GetTarget());
		GR_DLAttribBlend* pDLAttribBlend = dynamic_cast<GR_DLAttribBlend*>((*it).GetTarget());
		if(pDLAttribColor)
			bToData ? pDLAttribColor->SetColor(GetColor()) : SetColor(pDLAttribColor->GetColor());
		else if(pDLAttribBlend)
			bToData ? pDLAttribBlend->SetBlend(GetBlend()) : SetBlend(pDLAttribBlend->GetBlend());
	}
	CString strPath;
	GetDlgItem(IDC_UC_PROPERTY_SURFACE_TEXTURE_PATH)->GetWindowText(strPath);
	if(strPath.GetLength())
	{
		GR_DLAttribTexture* pDLAttribTexture = NULL;
		GR_DLAttrib* pDLAttrib = m_pDLSrf->GetAttrib(typeid(GR_DLAttribTexture)).GetTarget();
		if(!pDLAttrib)
		{
			pDLAttribTexture = new GR_DLAttribTexture(strPath);
			m_pDLSrf->AddAttrib(pDLAttribTexture, true);
		}
		else
		{
			pDLAttribTexture = dynamic_cast<GR_DLAttribTexture*>(pDLAttrib);
			if(pDLAttribTexture)
				pDLAttribTexture->SetTexture(strPath);
		}
	}//"D:\Work\Graphics\XCAD2\res\Crate.bmp"
}

// Set controls upon the color
void UC_PropertyPageSurface::SetColor(const GR_Color& clr)
{
	COLORREF color = RGB(int(clr.GetRed()*255), int(clr.GetGreen()*255), int(clr.GetBlue()*255));
	m_sliderClrR.SetPos(GetRValue(color));
	m_sliderClrG.SetPos(GetGValue(color));
	m_sliderClrB.SetPos(GetBValue(color));
	m_sliderClrA.SetPos(int(clr.GetAlpha()*255));
	m_btnClr.SetColor(color);
}

GR_Color UC_PropertyPageSurface::GetColor() const
{
	GR_Color clr((unsigned char)m_sliderClrR.GetPos(), (unsigned char)m_sliderClrG.GetPos(), (unsigned char)m_sliderClrB.GetPos(), (unsigned char)m_sliderClrA.GetPos());
	return clr;
}

void UC_PropertyPageSurface::OnColorChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLORREF color = RGB(m_sliderClrR.GetPos(), m_sliderClrG.GetPos(), m_sliderClrB.GetPos());
	m_btnClr.SetColor(color);
	*pResult = 0;
}

// Set blend upon the attrib
void UC_PropertyPageSurface::SetBlend(const bool& bBlend)
{
	m_btnTransparency.SetCheck(bBlend ? BST_CHECKED : BST_UNCHECKED);
}

// Get blend upon the controls
bool UC_PropertyPageSurface::GetBlend() const
{
	return ( m_btnTransparency.GetCheck() == BST_CHECKED );
}

void UC_PropertyPageSurface::OnTexturePathBrowser()
{
	//OPENFILENAME ofn;       // common dialog box structure
	//char szFile[260];       // buffer for file name
	//HWND hwnd;              // owner window
	//HANDLE hf;              // file handle

	//// Initialize OPENFILENAME
	//ZeroMemory(&ofn, sizeof(ofn));
	//ofn.lStructSize = sizeof(ofn);
	//ofn.hwndOwner = GetParent()->GetSafeHwnd();
	//ofn.lpstrFile = szFile;
	////
	//// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	//// use the contents of szFile to initialize itself.
	////
	//ofn.lpstrFile[0] = '\0';
	//ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	//ofn.nFilterIndex = 1;
	//ofn.lpstrFileTitle = NULL;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = NULL;
	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//// Display the Open dialog box. 

	//if (GetOpenFileName(&ofn)==TRUE) 
	//	hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
	//	0, (LPSECURITY_ATTRIBUTES) NULL,
	//	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
	//	(HANDLE) NULL);

	CColorDialog d;
	d.DoModal();
	// szFilters is a text string that includes two file name filters:
	// "*.my" for "MyType Files" and "*.*' for "All Files."
	char szFilters[]=
		"MyType Files (*.my)|*.my|All Files (*.*)|*.*||";

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog dlg (TRUE, "my", "*.my",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, GetParent());

	dlg.DoModal();

	//CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap Files (*.bmp)|*.bmp||"), this);
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_UC_PROPERTY_SURFACE_TEXTURE_PATH)->SetWindowText(dlg.GetFileName());
	}
}
