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
#include "fw_cmd.h"

class GR_DL;
class UC_WorkplaneCmd :	public FW_Cmd
{
public:
	UC_WorkplaneCmd(void);
	virtual ~UC_WorkplaneCmd(void);

	static UC_WorkplaneCmd* GetCmd();

	// If the button in the command bar is clicked, then this function will be called
	virtual BOOL OnExecute();

	// MouseMove message
	virtual void OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonDown message
	virtual void OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonUp message
	virtual void OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);

private:
	DECLARE_MESSAGE_MAP()

	// Is the GR_DL valid as an input to generate the sketch 2d
	bool IsValid(GR_DL*	pDL) const;

	// 1. 3 points
	// 2. 1 point and 1 line
	// 3. 1 face
	GR_DL*	m_pDL[3];
};
