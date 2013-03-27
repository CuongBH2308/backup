/*
 文件描述：处理手柄事件
 */
#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <dinput.h>
#include "dxhelper.h"

// 设置我们可以转动的最大范围
#define JOYMAX    1000
#define JOYMIN   -1000
/*				Y

  ^
  |
  |
  X	-10,00 <---*---> +10,00
  |
  |
  \/
*/

// 设置无效范围为20%
#define JOYDEAD 200


// 当移到95%时我们当作为100%
#define JOYSAT  950


namespace DXInput
{
//实现此接口的类对象可以接收手柄消息并处理
	struct IJoyStickReceiver
	{
		virtual void JoyStickAxisMoved( int dx,int dy ){};
		
		//virtual void JoyStickZAxisDown( int dz ){};
		
		virtual void JoyStickButtonUp( int button ){};
		virtual void JoyStickButtonDown( int button ){};
	};
	


	class CJoyStick  
	{
	
	public:
		CJoyStick(HWND hwnd,bool bExclusive);
		virtual ~CJoyStick();
		
	public:
		
	//设置接收手柄消息的对象
		void SetReceiver( IJoyStickReceiver* pTarget );
		
		//处理手柄事件
		eResult Update();
		
		//获得手柄设备
		eResult Acquire();
		
		void UnAcquire();
		
		//回调函数：用来列举相连接的手柄设备　　//列举手柄对象，找到一个就完成　
		static BOOL CALLBACK  EnumDevicesProc(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
		
	protected:

		//设置手柄对象的一些基本属性
		bool InitJoystick();

	protected:
		LPDIRECTINPUTDEVICE8	m_pDevice;	//表示手柄
		
		DIJOYSTATE2   m_lastdijs;				// 上次手柄状态
		
		IJoyStickReceiver*		m_pTarget;   ////接收手柄消息的对象
		
		
	};
}

#endif // _JOYSTICK_H
