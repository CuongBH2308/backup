/*
 �ļ���������������¼�
 */
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <memory.h>
#include <dinput.h>
#include "dxhelper.h"

//class CInputManager;


namespace DXInput
{
//ʵ�ִ˽ӿڵ��������Խ��ռ�����Ϣ������
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
		
		// ����Ƿ��м�������
		bool Poll( int key );
		
		//���ý��ռ�����Ϣ�Ķ���
		void SetReceiver( IKeyboardReceiver* pTarget );
		
		//��������¼�
		eResult Update();

	protected:
		
		LPDIRECTINPUTDEVICE8	m_pDevice;	//�����豸
		
		char					m_keyState[256];//����״̬
		
		IKeyboardReceiver*		m_pTarget;   //���ռ�����Ϣ�Ķ���
		
	};
}
#endif //_KEYBOARD_H
