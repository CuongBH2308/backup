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
#include "fw_sliderctrl.h"

class FW_SliderCtrlColor : public FW_SliderCtrl
{
	DECLARE_DYNAMIC(FW_SliderCtrlColor)

public:
	FW_SliderCtrlColor(void);
	virtual ~FW_SliderCtrlColor(void);

	float	GetValueFloat() const;
	BYTE	GetValueByte() const;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void	PreSubclassWindow() ;
};
