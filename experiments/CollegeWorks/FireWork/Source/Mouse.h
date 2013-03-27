/*
 �ļ���������������¼�
 */
#ifndef _MOUSE_H
#define _MOUSE_H

#include <dinput.h>
#include "dxhelper.h"

namespace DXInput
{
	
    //ʵ�ִ˽ӿڵ��������Խ��������Ϣ������
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
		
		//���ý��������Ϣ�Ķ���
		void SetReceiver( IMouseReceiver* pTarget );
		
		//��������¼�
		eResult Update();
		
		eResult Acquire();
		
		void UnAcquire();
		
	protected:
		LPDIRECTINPUTDEVICE8	m_pDevice;    //��ʾ���
		
		DIMOUSESTATE			m_lastState;  //��ʾ�ϴε����״̬
		
		IMouseReceiver*			m_pTarget;  //���������Ϣ�Ķ���
		
	};
}
#endif // _MOUSE_H
