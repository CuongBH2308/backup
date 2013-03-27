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
#include "mh_collect.h"

class GR_DLCrv;
class GR_DLNodeSketch2D;
class S2_CrvNurbsCmd : public FW_Cmd
{
public:
	S2_CrvNurbsCmd(void);
    virtual ~S2_CrvNurbsCmd(void);

	static S2_CrvNurbsCmd* GetCmd();

	// If the button in the command bar is clicked, then this function will be called
	virtual BOOL OnExecute();

	// Terminate the command. Such as when ESC is pressed
	virtual BOOL OnTerminate();

	// MouseMove message
	virtual void OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonUp message
	virtual void OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);

	// RButtonUp message
	virtual void OnRButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);
private:
	DECLARE_MESSAGE_MAP()

	// The active sketch node
	GR_DLNodeSketch2D*	m_pDLNodeSketch2D;

	// The line segment for preview
	GR_DLCrv*			m_pDLCrvPreview;

	// Order of the curve
	size_t				m_nOrder;

	// Control points
	MH_CVVect			m_vCV;
};
