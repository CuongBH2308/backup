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
#include <map>

class MH_Point3;
class GR_DL;
class GR_DLNode;
class UC_Sketch2DCmd : public FW_Cmd
{
public:
	UC_Sketch2DCmd(void);
	virtual ~UC_Sketch2DCmd(void);

	static UC_Sketch2DCmd* GetCmd();

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
	
	std::map<GR_DL*, MH_Point3>		m_mDL;
	std::map<GR_DLNode*, MH_Point3> m_mDLNode;
};
