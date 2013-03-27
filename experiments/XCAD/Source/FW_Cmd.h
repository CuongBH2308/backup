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
#include "xcad.h"

interface IFWCmd;
class FW_Document;
class FW_View;
class XCAD_EXPORT FW_Cmd : public CCmdTarget
{
	DECLARE_DYNAMIC(FW_Cmd)
public:
	// Once a command is new up, it will be added into FW_Cmds that will 
	// manage the life cycle of this command
	FW_Cmd(UINT nDisplayName,
		UINT nTooltip,
		UINT nImages,
		const CString& strInternalName,
		const int& iCmdId = -1);

	// Once a command is new up, it will be added into FW_Cmds that will 
	// manage the life cycle of this command
	FW_Cmd(const CString& strDisplayName,
		const CString& strTooltip,
		CImageList& imageList,
		const CString& strInternalName,
		const int& iCmdId = -1);

	virtual ~FW_Cmd(void);

	// Get m_spIFWCmd;
	CComPtr<IFWCmd> GetInterface();

	// Set m_spIFWCmd to NULL
	void ResetInterface();

	// helper
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );

	// If the button in the command bar is clicked, then this function will be called
	virtual BOOL OnExecute();

	// Terminate the command. Such as when ESC is pressed
	virtual BOOL OnTerminate();

	// Enable/Disable Check/Uncheck the button
	virtual BOOL OnUpdateCmdUI(CCmdUI* pCmdUI);

	// MouseMove message
	virtual void OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonDown message
	virtual void OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point);

	// LButtonUp message
	virtual void OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);

	// RButtonDown message
	virtual void OnRButtonDown(CWnd* pWnd, UINT nFlags, CPoint point);

	// RButtonUp message
	virtual void OnRButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);

	// KeyDown message
	virtual void OnKeyDown(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags);

	// KeyUp message
	virtual void OnKeyUp(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags);

	void SetDisplayName(const CString& strDisplayName);
	CString GetDisplayName();

	void SetTooltip(const CString& strTooltip);
	CString GetTooltip();

	void SetInternalName(const CString& strInternalName);
	CString GetInternalName() const;

	void SetCmdId(const int& iCmdId);
	int GetCmdId() const;

	void SetState(const UINT& nState);
	UINT GetState() const;

	void SetImages(CImageList& imageList);
	CImageList* GetImages();

	void SetActive(bool bActive);
	bool GetActive() const;

	FW_View*	 GetView() const;
	FW_Document* GetDocument() const;
private:
	CComPtr<IFWCmd> m_spIFWCmd;

	CString		m_strDisplayName;
	CString		m_strTooltip;
	CString		m_strInternalName;
	int			m_iCmdId;
	UINT		m_nState;
	CImageList	m_imageList;

	CString		m_strStatusPrev;
	bool		m_bActive;
	FW_View*	m_pView;
	FW_Document*m_pDoc;
	DECLARE_MESSAGE_MAP()
};
