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
#include "fw_sliderctrlcolor.h"
#include "fw_buttoncolor.h"
#include "gr_color.h"
#include "resource.h"

class GR_DL;
class GR_DLPoint;
class UC_PropertyPagePoint : public FW_PropertyPage
{
	DECLARE_DYNCREATE(UC_PropertyPagePoint)

	// Construction
public:
	UC_PropertyPagePoint();
	~UC_PropertyPagePoint();

	void SetObj(GR_DL* pObj);

	// Apply the setting
	virtual BOOL OnApply();

	// Dialog Data
	//{{AFX_DATA(UC_PropertyPagePoint)
	enum { IDD = IDD_UC_PROPERTY_POINT };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(UC_PropertyPagePoint)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(UC_PropertyPagePoint)
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

	// Set controls upon the point's size
	void SetSize(const float& fSize);

	// Get point's size upon the controls
	float GetSize() const;

	// Set control upon the point's smooth
	void SetSmooth(const bool& bSmooth);

	// Get point's smooth upon the control
	bool GetSmooth() const;

	GR_DLPoint* m_pDLPoint;
	FW_SliderCtrlColor	m_sliderClrR;
	FW_SliderCtrlColor	m_sliderClrG;
	FW_SliderCtrlColor	m_sliderClrB;
	FW_SliderCtrlColor	m_sliderClrA;
	FW_SliderCtrlColor	m_sliderSize;
	FW_ButtonColor		m_btnClr;
	FW_Button			m_btnSmooth;
};