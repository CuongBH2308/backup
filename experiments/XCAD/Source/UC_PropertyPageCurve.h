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


#pragma once
#include "fw_propertypage.h"
#include "resource.h"
#include "fw_sliderctrlcolor.h"
#include "fw_buttoncolor.h"
#include "fw_edit.h"

class GR_DL;
class GR_DLCrv;
class GR_Color;
class UC_PropertyPageCurve : public FW_PropertyPage
{
	DECLARE_DYNCREATE(UC_PropertyPageCurve)

	// Construction
public:
	UC_PropertyPageCurve();
	~UC_PropertyPageCurve();

	void SetObj(GR_DL* pObj);

	// Apply the setting
	virtual BOOL OnApply();
    
	// Dialog Data
	//{{AFX_DATA(UC_PropertyPageCurve)
	enum { IDD = IDD_UC_PROPERTY_CURVE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(UC_PropertyPageCurve)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(UC_PropertyPageCurve)
	virtual BOOL OnInitDialog();
	afx_msg void OnColorChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// Update data according to the setting in the UI
	void Update(BOOL bToData = TRUE);

	// Set controls upon the color
	void SetColor(const GR_Color& clr);

	// Get color upon the controls
	GR_Color GetColor() const;

	// Set Width
	void SetWidth(const float& fWidth);

	// Get Width
	float GetWidth() const;

	// Set stipple
	void SetStipple(const int& iFactor, const unsigned short& pattern);

	// Get stipple
	void GetStipple(int& iFactor, unsigned short& pattern) const;

	GR_DLCrv* m_pDLCrv;
	FW_SliderCtrlColor	m_sliderClrR;
	FW_SliderCtrlColor	m_sliderClrG;
	FW_SliderCtrlColor	m_sliderClrB;
	FW_SliderCtrlColor	m_sliderClrA;
	FW_SliderCtrlColor	m_sliderWidth;
	FW_ButtonColor		m_btnClr;
	FW_SliderCtrlColor	m_sliderFactor;
	FW_Edit				m_editPattern;
};