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
#include "xcad.h"
#include "fw_cmd.h"
#include "fw_document.h"
#include "fw_mdiframewnd.h"
#include "uc_renderlightdlg.h"
#include "uc_renderlightreq.h"


IMPLEMENT_DYNAMIC(UC_RenderLightDlg, FW_Dialog)
UC_RenderLightDlg::UC_RenderLightDlg(FW_Cmd* pCmd, CWnd* pParent /*=NULL*/)
: FW_Dialog(UC_RenderLightDlg::IDD, pParent),
m_pCmd(pCmd)
{
	Create(UC_RenderLightDlg::IDD, pParent);
}

UC_RenderLightDlg::~UC_RenderLightDlg()
{
}

void UC_RenderLightDlg::DoDataExchange(CDataExchange* pDX)
{
	FW_Dialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_R,	m_sliderAmbientClrR);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_G,	m_sliderAmbientClrG);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_B,	m_sliderAmbientClrB);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_A,	m_sliderAmbientClrA);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR,		m_btnAmbientClr);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_AMBIENT,			m_checkAmbientClr);

	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_R,	m_sliderDiffuseClrR);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_G,	m_sliderDiffuseClrG);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_B,	m_sliderDiffuseClrB);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_A,	m_sliderDiffuseClrA);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR,		m_btnDiffuseClr);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIFFUSE,			m_checkDiffuseClr);

	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_R,	m_sliderSpecularClrR);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_G,	m_sliderSpecularClrG);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_B,	m_sliderSpecularClrB);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_A,	m_sliderSpecularClrA);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR,	m_btnSpecularClr);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_SPECULAR,			m_checkSpecularClr);

	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_POSITION_X,		m_editPosX);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_POSITION_Y,		m_editPosY);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_POSITION_Z,		m_editPosZ);

	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIRECTION_X,		m_editDirX);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIRECTION_Y,		m_editDirY);
	DDX_Control(pDX, IDC_UC_RENDER_LIGHT_DIRECTION_Z,		m_editDirZ);
}


BEGIN_MESSAGE_MAP(UC_RenderLightDlg, FW_Dialog)
	//{{AFX_MSG_MAP(UC_RenderLightDlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_R, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_G, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_B, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_AMBIENT_COLOR_A, OnColorChanged)

	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_R, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_G, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_B, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_DIFFUSE_COLOR_A, OnColorChanged)

	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_R, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_G, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_B, OnColorChanged)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_UC_RENDER_LIGHT_SPECULAR_COLOR_A, OnColorChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL UC_RenderLightDlg::OnInitDialog()
{
	FW_Dialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// virtual 
void UC_RenderLightDlg::OnOK()
{
	// Apply the setting
	OnApply();

	ASSERT(m_pCmd);
	// UC_RenderLightCmd::OnTerminate will destroy the window
	m_pCmd->OnTerminate();
}

// virtual 
void UC_RenderLightDlg::OnCancel()
{
	ASSERT(m_pCmd);
	// UC_RenderLightCmd::OnTerminate will destroy the window
	m_pCmd->OnTerminate();
}

void UC_RenderLightDlg::OnApply()
{
	float pos[4];
	m_editPosX.GetValue(pos[0]);
	m_editPosY.GetValue(pos[1]);
	m_editPosZ.GetValue(pos[2]);
	pos[3] = 1.0f;

	GR_DLAttribLight::Ambient ambient;
	GR_DLAttribLight::Diffuse diffuse;
	GR_DLAttribLight::Specular specular;
	if(m_checkAmbientClr.GetCheck() == BST_CHECKED)
		ambient = GR_DLAttribLight::Ambient(m_sliderAmbientClrR.GetValueFloat(), 
					m_sliderAmbientClrG.GetValueFloat(),
					m_sliderAmbientClrB.GetValueFloat(),
					m_sliderAmbientClrA.GetValueFloat());
	if(m_checkDiffuseClr.GetCheck() == BST_CHECKED)
		diffuse = GR_DLAttribLight::Diffuse(m_sliderDiffuseClrR.GetValueFloat(), 
					m_sliderDiffuseClrG.GetValueFloat(),
					m_sliderDiffuseClrB.GetValueFloat(),
					m_sliderDiffuseClrA.GetValueFloat());
	if(m_checkSpecularClr.GetCheck() == BST_CHECKED)
		specular = GR_DLAttribLight::Specular(m_sliderSpecularClrR.GetValueFloat(), 
					m_sliderSpecularClrG.GetValueFloat(),
					m_sliderSpecularClrB.GetValueFloat(),
					m_sliderSpecularClrA.GetValueFloat());
					

	UC_RenderLightReq req(FW_MDIFrameWnd::GetActiveDoc(),
		ambient, diffuse, specular,GR_DLAttribLight::Position(pos[0], pos[1], pos[2], pos[3]));

	FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);

	FW_MDIFrameWnd::GetMDIFrameWnd()->UpdateActiveView();
}

// virtual 
void UC_RenderLightDlg::PostNcDestroy()
{
	delete this;
}

void UC_RenderLightDlg::OnColorChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	COLORREF color = RGB(m_sliderAmbientClrR.GetPos(), m_sliderAmbientClrG.GetPos(), m_sliderAmbientClrB.GetPos());
	m_btnAmbientClr.SetColor(color);

	color = RGB(m_sliderDiffuseClrR.GetPos(), m_sliderDiffuseClrG.GetPos(), m_sliderDiffuseClrB.GetPos());
	m_btnDiffuseClr.SetColor(color);

	color = RGB(m_sliderSpecularClrR.GetPos(), m_sliderSpecularClrG.GetPos(), m_sliderSpecularClrB.GetPos());
	m_btnSpecularClr.SetColor(color);
	*pResult = 0;
}
