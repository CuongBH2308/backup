/*
 文件描述：处理鼠标事件
 */
#ifndef _MOUSE_H
#define _MOUSE_H

#include <dinput.h>
#include "dxhelper.h"

namespace DXInput
{
	
    //实现此接口的类对象可以接收鼠标消息并处理
	struct IMouseReceiver
	{
		virtual void MouseMoved( int dx, int dy ){};
		virtual void MouseButtonUp( int button ){};
		virtual void MouseButtonDown( int button ){};
		//virtual void MouseButtonClick( int button ){};
	};
	
	

	
	class CMouse  
	{
		
	public:
		
		CMouse( HWND hWnd, bool bExclusive );
		~CMouse();
		
		//设置接收鼠标消息的对象
		void SetReceiver( IMouseReceiver* pTarget );
		
		//处理鼠标事件
		eResult Update();
		
		eResult Acquire();
		
		void UnAcquire();
		
	protected:
		LPDIRECTINPUTDEVICE8	m_pDevice;    //表示鼠标
		
		DIMOUSESTATE			m_lastState;  //表示上次的鼠标状态
		
		IMouseReceiver*			m_pTarget;  //接收鼠标消息的对象
		
	};
}
#endif // _MOUSE_H
