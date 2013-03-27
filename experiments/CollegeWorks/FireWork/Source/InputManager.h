/*
 �ļ�������ͳһ�������������豸
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
		
		//���������豸�������¼�
		void UpdateDevices();
		
		static CInputManager* GetInput()
		{
			return m_pGlobalILayer;
		}
		
		LPDIRECTINPUT8 GetDInput()
		{
			return m_pDI; 
		}
		
		void SetFocus(); // �õ������豸�Ŀ���Ȩ
		void KillFocus(); // �ͷš���������
		
		//�����������
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
		
		//  DI8 ����
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
