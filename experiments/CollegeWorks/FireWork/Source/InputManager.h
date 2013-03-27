/*
 文件描述：统一管理三种输入设备
 */
#ifndef _INPUTLAYER_H
#define _INPUTLAYER_H

#include <dinput.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "JoyStick.h"

namespace DXInput
{
	class CInputManager
	{	
		
	public:
		
		virtual ~CInputManager();
		
		CKeyboard* GetKeyboard()
		{
			return m_pKeyboard;
		}
		
		CMouse* GetMouse()
		{
			return m_pMouse;
		}
		
		CJoyStick* GetJoyStick()
		{
			return m_pJoystick;
		}
		
		//处理三种设备的所有事件
		void UpdateDevices();
		
		static CInputManager* GetInput()
		{
			return m_pGlobalILayer;
		}
		
		LPDIRECTINPUT8 GetDInput()
		{
			return m_pDI; 
		}
		
		void SetFocus(); // 得到三种设备的控制权
		void KillFocus(); // 释放。。。。。
		
		//创建管理对象
		static void Create( 
			HINSTANCE hInst, 
			HWND hWnd, 
			bool bExclusive, 
			bool bUseKeyboard = true, 
			bool bUseMouse = true ,
			bool bUseJoystick = true )
		{
			new CInputManager( 
				hInst, 
				hWnd, 
				bExclusive, 
				bUseKeyboard, 
				bUseMouse,
				bUseJoystick);
		}

	protected:

		CKeyboard*		m_pKeyboard;
		CMouse*			m_pMouse;
		CJoyStick*      m_pJoystick;
		
		//  DI8 对象
		LPDIRECTINPUT8	m_pDI;
		
		static CInputManager* m_pGlobalILayer;
		
		CInputManager( 
			HINSTANCE hInst, 
			HWND hWnd, 
			bool bExclusive, 
			bool bUseKeyboard = true, 
			bool bUseMouse = true ,
			bool bUseJoystick = true );
	};


	
	
	inline CInputManager* Input()
	{
		return CInputManager::GetInput();
	}
	
}

#endif //_INPUTLAYER_H
