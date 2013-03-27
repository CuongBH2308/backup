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
#include "fw_sliderctrlcolor.h"

IMPLEMENT_DYNAMIC(FW_SliderCtrlColor, FW_SliderCtrl)
FW_SliderCtrlColor::FW_SliderCtrlColor(void)
{
}

FW_SliderCtrlColor::~FW_SliderCtrlColor(void)
{
}

BEGIN_MESSAGE_MAP(FW_SliderCtrlColor, FW_SliderCtrl)
	//{{AFX_MSG_MAP(FW_SliderCtrlColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// virtual 
void FW_SliderCtrlColor::PreSubclassWindow()
{
	FW_SliderCtrl::PreSubclassWindow();
	SetRange(0,255);
	ClearTics();
}

float FW_SliderCtrlColor::GetValueFloat() const
{
	return float(GetValueByte()) / 255.0f;
}

BYTE FW_SliderCtrlColor::GetValueByte() const
{
	return GetPos();
}