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
#include "uc_propertypagepoint.h"
#include "gr_dlpoint.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribpointsize.h"
#include "gr_dlattribpointsmooth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UC_PropertyPagePoint property page

IMPLEMENT_DYNCREATE(UC_PropertyPagePoint, FW_PropertyPage)

UC_PropertyPagePoint::UC_PropertyPagePoint() : FW_PropertyPage(UC_PropertyPagePoint::IDD),
m_pDLPoint(NULL)
{
	//{{AFX_DATA_INIT(UC_PropertyPagePoint)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

UC_PropertyPagePoint::~UC_PropertyPagePoint()
{
}

void UC_PropertyPagePoint::DoDataExchange(CDataExchange* pDX)
{
	FW_PropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_COLOR_R, m_sliderClrR);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_COLOR_G, m_sliderClrG);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_COLOR_B, m_sliderClrB);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_COLOR_A, m_sliderClrA);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_SIZE,	m_sliderSize);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_COLOR,	m_btnClr);
	DDX_Control(pDX, IDC_UC_PROPERTY_POINT_SMOOTH,	m_btnSmooth);
}


BEGIN_MESSAGE_MAP(UC_PropertyPagePoint, FW_PropertyPage)
	//{{AFX_MSG_MAP(UC_PropertyPagePoint)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_POINT_COLOR_R, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_POINT_COLOR_G, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_POINT_COLOR_B, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_POINT_COLOR_A, OnColorChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// UC_PropertyPagePoint message handlers

BOOL UC_PropertyPagePoint::OnInitDialog()
{
	FW_PropertyPage::OnInitDialog();

	SetObj(m_pDLPoint);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void UC_PropertyPagePoint::SetObj(GR_DL* pObj)
{
	if(pObj)
		m_pDLPoint = dynamic_cast<GR_DLPoint*>(pObj);
	if(GetSafeHwnd())
	{
		if(!m_pDLPoint)
			Enable(FALSE);
		else
		{
			Enable(TRUE);
			Update(FALSE);
		}
	}
}

BOOL UC_PropertyPagePoint::OnApply()
{
	if(!m_pDLPoint)
		return FALSE;
	Update();
	m_pDLPoint->Invalidate();
	return TRUE;
}

// Update data according to the setting in the UI
void UC_PropertyPagePoint::Update(BOOL bToData)
{
	const GR_DLAttribPtrVect& vAttrib = m_pDLPoint->GetAttribs();
	for(GR_DLAttribPtrVect::const_iterator it = vAttrib.begin(); it != vAttrib.end(); it++)
	{
		GR_DLAttribColor* pDLAttribColor				= dynamic_cast<GR_DLAttribColor*>((*it).GetTarget());
		GR_DLAttribPointSize* pDLAttribPointSize		= dynamic_cast<GR_DLAttribPointSize*>((*it).GetTarget());
		GR_DLAttribPointSmooth* pDLAttribPointSmooth	= dynamic_cast<GR_DLAttribPointSmooth*>((*it).GetTarget());
		if(pDLAttribColor)
			bToData ? pDLAttribColor->SetColor(GetColor()) : SetColor(pDLAttribColor->GetColor());
		else if(pDLAttribPointSize)
			bToData ? pDLAttribPointSize->SetSize(GetSize()) : SetSize(pDLAttribPointSize->GetSize());
		else if(pDLAttribPointSmooth)
			bToData ? pDLAttribPointSmooth->SetSmooth(GetSmooth()) : SetSmooth(pDLAttribPointSmooth->GetSmooth());
	}
}

// Set controls upon the color
void UC_PropertyPagePoint::SetColor(const GR_Color& clr)
{
	COLORREF color = RGB(int(clr.GetRed()*255), int(clr.GetGreen()*255), int(clr.GetBlue()*255));
	m_sliderClrR.SetPos(GetRValue(color));
	m_sliderClrG.SetPos(GetGValue(color));
	m_sliderClrB.SetPos(GetBValue(color));
	m_sliderClrA.SetPos(int(clr.GetAlpha()*255));
	m_btnClr.SetColor(color);
}

GR_Color UC_PropertyPagePoint::GetColor() const
{
	GR_Color clr((unsigned char)m_sliderClrR.GetPos(), (unsigned char)m_sliderClrG.GetPos(), (unsigned char)m_sliderClrB.GetPos(), (unsigned char)m_sliderClrA.GetPos());
	return clr;
}

void UC_PropertyPagePoint::OnColorChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLORREF color = RGB(m_sliderClrR.GetPos(), m_sliderClrG.GetPos(), m_sliderClrB.GetPos());
	m_btnClr.SetColor(color);
	*pResult = 0;
}

// Set controls upon the point's size
void UC_PropertyPagePoint::SetSize(const float& fSize)
{
	m_sliderSize.SetPos(int(fSize));
}

// Get point's size upon the controls
float UC_PropertyPagePoint::GetSize() const
{
	return float(m_sliderSize.GetPos());
}

// Set control upon the point's smooth
void UC_PropertyPagePoint::SetSmooth(const bool& bSmooth)
{
	bSmooth ? m_btnSmooth.SetCheck(BST_CHECKED) : m_btnSmooth.SetCheck(BST_UNCHECKED);
}

// Get point's smooth upon the control
bool UC_PropertyPagePoint::GetSmooth() const
{
	return (m_btnSmooth.GetCheck() == BST_CHECKED);
}
