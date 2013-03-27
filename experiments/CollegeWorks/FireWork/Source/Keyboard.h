/*
 文件描述：处理键盘事件
 */
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <memory.h>
#include <dinput.h>
#include "dxhelper.h"

//class CInputManager;


namespace DXInput
{
//实现此接口的类对象可以接收键盘消息并处理
	struct IKeyboardReceiver
	{
		virtual void KeyUp( int key ){};
		virtual void KeyDown( int key ){};
	};
	
	
	class CKeyboard  
	{
	
	public:
		
		void ClearTable()
		{
			memset( m_keyState, 0, sizeof(char)*256 );
		}
		
		CKeyboard( HWND hWnd );
		~CKeyboard();
		
		// 检测是否有键被按下
		bool Poll( int key );
		
		//设置接收键盘消息的对象
		void SetReceiver( IKeyboardReceiver* pTarget );
		
		//处理键盘事件
		eResult Update();

	protected:
		
		LPDIRECTINPUTDEVICE8	m_pDevice;	//键盘设备
		
		char					m_keyState[256];//键盘状态
		
		IKeyboardReceiver*		m_pTarget;   //接收键盘消息的对象
		
	};
}
#endif //_KEYBOARD_H
