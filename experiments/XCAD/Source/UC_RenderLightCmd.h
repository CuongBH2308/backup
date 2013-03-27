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

class UC_RenderLightDlg;
class UC_RenderLightCmd : public FW_Cmd
{
public:
	UC_RenderLightCmd(void);
	virtual ~UC_RenderLightCmd(void);

	static UC_RenderLightCmd* GetCmd();

	// If the button in the command bar is clicked, then this function will be called
	virtual BOOL OnExecute();

	// Some other command is activated, so this command will be terminated
	virtual BOOL OnTerminate();

	// MouseMove message
	virtual void OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonDown message
	virtual void OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonUp message
	virtual void OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);

private:
	UC_RenderLightDlg*	m_pRenderLightDlg;

	DECLARE_MESSAGE_MAP()
};
