// Viewer.h: interface for the CViewer class.
/*
 ������Ϸ��ҵ��࣬�̳���CCamera,IJoyStickReceiver,IMouseReceiver,IKeyboardReceiver
 ��Ҫ���������Ϸ����ҵ��ӽǣ��˶�������Ӧ�û�������Ϣ
 */

#if !defined(AFX_VIEWER_H__4374D59C_90C2_41AE_9620_21DA9EB0414C__INCLUDED_)
#define AFX_VIEWER_H__4374D59C_90C2_41AE_9620_21DA9EB0414C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "JoyStick.h"
using namespace DXInput;

class CViewer : 
	public IKeyboardReceiver, 
	public IMouseReceiver, 
	public IJoyStickReceiver,
	public d3d::CCamera  
{
public:
	CViewer();
	CViewer(CCameraType CCameraType,D3DXVECTOR3 pos);
	virtual ~CViewer();

	//moose interface
public:
	virtual void MouseMoved( int dx, int dy );
	virtual void MouseButtonUp( int button );
	virtual void MouseButtonDown( int button );

	
	//keyboard interface
	virtual void KeyUp( int key );
	virtual void KeyDown( int key );


	//joystick interface
	virtual void JoyStickAxisMoved( int dx,int dy );
	virtual void JoyStickButtonUp( int button );
	virtual void JoyStickButtonDown( int button );



public:
	void SetTimeDelta(float timedelta)
	{
		m_fTimeDelta = timedelta;

	}

	void SetMouseSensitivity(float mousesensitivity )
	{
		m_mousesensitivity = mousesensitivity;
		
	}
	void SetJSSensitivity(float jssensitivity )
	{
		m_jssensitivity = jssensitivity;
		
	}
private:
	float m_fTimeDelta;
	float m_mousesensitivity;
	float m_jssensitivity;
};

#endif // !defined(AFX_VIEWER_H__4374D59C_90C2_41AE_9620_21DA9EB0414C__INCLUDED_)
