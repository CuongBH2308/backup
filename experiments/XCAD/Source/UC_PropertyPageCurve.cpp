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
#include "uc_propertypagecurve.h"
#include "gr_dlcrv.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribcurvewidth.h"
#include "gr_dlattribcurvestipple.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UC_PropertyPageCurve property page

IMPLEMENT_DYNCREATE(UC_PropertyPageCurve, FW_PropertyPage)

UC_PropertyPageCurve::UC_PropertyPageCurve() : FW_PropertyPage(UC_PropertyPageCurve::IDD),
m_pDLCrv(NULL)
{
	//{{AFX_DATA_INIT(UC_PropertyPageCurve)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

UC_PropertyPageCurve::~UC_PropertyPageCurve()
{
}

void UC_PropertyPageCurve::DoDataExchange(CDataExchange* pDX)
{
	FW_PropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_COLOR_R, m_sliderClrR);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_COLOR_G, m_sliderClrG);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_COLOR_B, m_sliderClrB);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_COLOR_A, m_sliderClrA);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_COLOR,	m_btnClr);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_WEIGHT,	m_sliderWidth);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_STIPPLE_FACTOR,	m_sliderFactor);
	DDX_Control(pDX, IDC_UC_PROPERTY_CURVE_STIPPLE_PATTERN,	m_editPattern);
}


BEGIN_MESSAGE_MAP(UC_PropertyPageCurve, FW_PropertyPage)
	//{{AFX_MSG_MAP(UC_PropertyPageCurve)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_CURVE_COLOR_R, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_CURVE_COLOR_G, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_CURVE_COLOR_B, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_PROPERTY_CURVE_COLOR_A, OnColorChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// UC_PropertyPageCurve message handlers

BOOL UC_PropertyPageCurve::OnInitDialog()
{
	FW_PropertyPage::OnInitDialog();

	SetObj(m_pDLCrv);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void UC_PropertyPageCurve::SetObj(GR_DL* pObj)
{
	if(pObj)
		m_pDLCrv= dynamic_cast<GR_DLCrv*>(pObj);
	if(GetSafeHwnd())
	{
		if(!m_pDLCrv)
			Enable(FALSE);
		else
		{
			Enable(TRUE);
			Update(FALSE);
		}
	}
}

BOOL UC_PropertyPageCurve::OnApply()
{
	if(!m_pDLCrv)
		return FALSE;
	Update();
	m_pDLCrv->Invalidate();
	return TRUE;
}

// Update data according to the setting in the UI
void UC_PropertyPageCurve::Update(BOOL bToData)
{
	const GR_DLAttribPtrVect& vAttrib = m_pDLCrv->GetAttribs();
	for(GR_DLAttribPtrVect::const_iterator it = vAttrib.begin(); it != vAttrib.end(); it++)
	{
		GR_DLAttribColor* pDLAttribColor = dynamic_cast<GR_DLAttribColor*>((*it).GetTarget());
		GR_DLAttribCurveWidth* pDLAttribCurveWidth = dynamic_cast<GR_DLAttribCurveWidth*>((*it).GetTarget());
		GR_DLAttribCurveStipple* pDLAttribCurveStipple = dynamic_cast<GR_DLAttribCurveStipple*>((*it).GetTarget());
		if(pDLAttribColor)
			bToData ? pDLAttribColor->SetColor(GetColor()) : SetColor(pDLAttribColor->GetColor());
		else if(pDLAttribCurveWidth)
			bToData ? pDLAttribCurveWidth->SetWidth(GetWidth()) : SetWidth(pDLAttribCurveWidth->GetWidth());
		else if(pDLAttribCurveStipple)
		{
			int iFactor;
			unsigned short pattern;
			if(bToData)
			{
				GetStipple(iFactor, pattern);
				pDLAttribCurveStipple->Set(iFactor, pattern);
			}
			else
			{
				pDLAttribCurveStipple->Get(iFactor, pattern);
				SetStipple(iFactor, pattern);
			}
		}
	}
}

// Set controls upon the color
void UC_PropertyPageCurve::SetColor(const GR_Color& clr)
{
	COLORREF color = RGB(int(clr.GetRed()*255), int(clr.GetGreen()*255), int(clr.GetBlue()*255));
	m_sliderClrR.SetPos(GetRValue(color));
	m_sliderClrG.SetPos(GetGValue(color));
	m_sliderClrB.SetPos(GetBValue(color));
	m_sliderClrA.SetPos(int(clr.GetAlpha()*255));
	m_btnClr.SetColor(color);
}

GR_Color UC_PropertyPageCurve::GetColor() const
{
	GR_Color clr((unsigned char)m_sliderClrR.GetPos(), (unsigned char)m_sliderClrG.GetPos(), (unsigned char)m_sliderClrB.GetPos(), (unsigned char)m_sliderClrA.GetPos());
	return clr;
}

void UC_PropertyPageCurve::OnColorChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLORREF color = RGB(m_sliderClrR.GetPos(), m_sliderClrG.GetPos(), m_sliderClrB.GetPos());
	m_btnClr.SetColor(color);
	*pResult = 0;
}

// Set Width
void UC_PropertyPageCurve::SetWidth(const float& fWidth)
{
	m_sliderWidth.SetPos(int(fWidth));
}

// Get Width
float UC_PropertyPageCurve::GetWidth() const
{
	return float(m_sliderWidth.GetPos());
}

// Set stipple
void UC_PropertyPageCurve::SetStipple(const int& iFactor, const unsigned short& pattern)
{
	m_sliderFactor.SetPos(iFactor);
	CString str;
	str.Format(_T("%d"), pattern);
	m_editPattern.SetWindowText(str);
}

// Get stipple
void UC_PropertyPageCurve::GetStipple(int& iFactor, unsigned short& pattern) const
{
	iFactor = m_sliderFactor.GetPos();
	CString str;
	m_editPattern.GetWindowText(str);
	pattern = _ttoi(str);
}