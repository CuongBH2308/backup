// Viewer.cpp: implementation of the CViewer class.
//
//////////////////////////////////////////////////////////////////////

#include "Viewer.h"
#include "SoundListener.h"
#include "d3dBase.h"
#include "PSystem.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern d3d::CPSystem* g_Gun;
static bool bbegin = true;

CViewer::CViewer()
{

}

CViewer::CViewer(CCameraType CCameraType,D3DXVECTOR3 pos)
:CCamera(CCameraType,pos),m_fTimeDelta(0.01),
m_mousesensitivity(1.0),m_jssensitivity(1.0)
{
	
}

CViewer::~CViewer()
{
	
}


//////////////////////////////////////////////////////////////////////////

void CViewer::KeyDown(int key )
{
	//D3DXVECTOR3 pos,pos2;
	switch(key) {
	case DIK_W:
		walk(8.0f * m_fTimeDelta);
		break;
	case DIK_A:
		strafe(-8.0f * m_fTimeDelta);
		break;
	case DIK_S:
		walk(-8.0f * m_fTimeDelta);
		break;
	case DIK_D:
		strafe(8.0f * m_fTimeDelta);
		break;



	case DIK_UP:
		pitch(-2.0f * m_fTimeDelta);
		break;
	case DIK_LEFT:
		yaw(-2.0f * m_fTimeDelta);
		break;
	case DIK_DOWN:
		pitch(2.0f * m_fTimeDelta);
		break;
	case DIK_RIGHT:
		yaw(2.0f * m_fTimeDelta);
		break;
	case DIK_LSHIFT:
		if(bbegin)
		{
			m_pos.y-=2;
			bbegin = false;
		}
		break;
		
	case DIK_NEXT:
		m_pos.y-=0.5;
		break;
	case DIK_PRIOR:
		m_pos.y+=0.5;
		break;
			

	default:break;
	}

	
}

void CViewer::KeyUp(int key )
{
	switch(key) {
	case DIK_LSHIFT:
		m_pos.y+=2;
		bbegin = true;
		break;
	default:break;
	}
}








//////////////////////////////////////////////////////////////////////////


void CViewer::MouseButtonDown(int button )
{
	
}

void CViewer::MouseButtonUp(int button )
{
	if(button == 0)
	{
		g_Gun->addParticle();
	}
}

void CViewer::MouseMoved(int dx, int dy )
{
	yaw(m_mousesensitivity*dx*m_fTimeDelta);
	pitch(m_mousesensitivity*dy*m_fTimeDelta);
	
}












//////////////////////////////////////////////////////////////////////////



void CViewer::JoyStickAxisMoved(int dx,int dy )
{
	yaw(m_jssensitivity*dx*m_fTimeDelta);
	pitch(m_jssensitivity*dy*m_fTimeDelta);
}

void CViewer::JoyStickButtonDown(int button )
{
	


}

void CViewer::JoyStickButtonUp(int button )
{
	
	
	



}
