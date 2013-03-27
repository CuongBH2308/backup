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

class GR_DLNodeSketch2D;
class UC_TestCrvNurbsCmd : public FW_Cmd
{
public:
	UC_TestCrvNurbsCmd(void);
	virtual ~UC_TestCrvNurbsCmd(void);

	static UC_TestCrvNurbsCmd* GetCmd();

	// If the button in the command bar is clicked, then this function will be called
	virtual BOOL OnExecute();

	// LButtonUp message
	virtual void OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);

private:
	DECLARE_MESSAGE_MAP()

	// The active sketch node
	GR_DLNodeSketch2D*	m_pDLNodeSketch2D;
};
