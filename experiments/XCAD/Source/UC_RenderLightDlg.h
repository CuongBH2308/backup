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
#include "fw_dialog.h"
#include "fw_buttoncolor.h"
#include "fw_editpos.h"
#include "fw_sliderctrlcolor.h"
#include "resource.h"

class FW_Cmd;
class UC_RenderLightDlg : public FW_Dialog
{
	DECLARE_DYNAMIC(UC_RenderLightDlg)

public:
	UC_RenderLightDlg(FW_Cmd* pCmd, CWnd* pParent = NULL);
	virtual ~UC_RenderLightDlg();

	enum { IDD = IDD_UC_RENDER_LIGHT };

	virtual void OnOK();
	virtual void OnCancel();
	virtual void OnApply();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnColorChanged(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
private:
	FW_Cmd*	m_pCmd;

	FW_SliderCtrlColor	m_sliderAmbientClrR;
	FW_SliderCtrlColor	m_sliderAmbientClrG;
	FW_SliderCtrlColor	m_sliderAmbientClrB;
	FW_SliderCtrlColor	m_sliderAmbientClrA;
	FW_ButtonColor		m_btnAmbientClr;
	FW_Button			m_checkAmbientClr;

	FW_SliderCtrlColor	m_sliderDiffuseClrR;
	FW_SliderCtrlColor	m_sliderDiffuseClrG;
	FW_SliderCtrlColor	m_sliderDiffuseClrB;
	FW_SliderCtrlColor	m_sliderDiffuseClrA;
	FW_ButtonColor		m_btnDiffuseClr;
	FW_Button			m_checkDiffuseClr;

	FW_SliderCtrlColor	m_sliderSpecularClrR;
	FW_SliderCtrlColor	m_sliderSpecularClrG;
	FW_SliderCtrlColor	m_sliderSpecularClrB;
	FW_SliderCtrlColor	m_sliderSpecularClrA;
	FW_ButtonColor		m_btnSpecularClr;
	FW_Button			m_checkSpecularClr;

	FW_EditPos			m_editPosX;
	FW_EditPos			m_editPosY;
	FW_EditPos			m_editPosZ;

	FW_EditPos			m_editDirX;
	FW_EditPos			m_editDirY;
	FW_EditPos			m_editDirZ;

};
