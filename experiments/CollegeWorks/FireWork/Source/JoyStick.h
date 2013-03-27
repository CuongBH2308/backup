/*
 �ļ������������ֱ��¼�
 */
#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <dinput.h>
#include "dxhelper.h"

// �������ǿ���ת�������Χ
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

// ������Ч��ΧΪ20%
#define JOYDEAD 200


// ���Ƶ�95%ʱ���ǵ���Ϊ100%
#define JOYSAT  950


namespace DXInput
{
//ʵ�ִ˽ӿڵ��������Խ����ֱ���Ϣ������
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
		
	//���ý����ֱ���Ϣ�Ķ���
		void SetReceiver( IJoyStickReceiver* pTarget );
		
		//�����ֱ��¼�
		eResult Update();
		
		//����ֱ��豸
		eResult Acquire();
		
		void UnAcquire();
		
		//�ص������������о������ӵ��ֱ��豸����//�о��ֱ������ҵ�һ������ɡ�
		static BOOL CALLBACK  EnumDevicesProc(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
		
	protected:

		//�����ֱ������һЩ��������
		bool InitJoystick();

	protected:
		LPDIRECTINPUTDEVICE8	m_pDevice;	//��ʾ�ֱ�
		
		DIJOYSTATE2   m_lastdijs;				// �ϴ��ֱ�״̬
		
		IJoyStickReceiver*		m_pTarget;   ////�����ֱ���Ϣ�Ķ���
		
		
	};
}

#endif // _JOYSTICK_H
