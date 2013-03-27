/*
 �ļ���������Ϊ�����ߣ���������3D�ͷ�3D����
 */
#ifndef _SOUNDLISTENER_H
#define _SOUNDLISTENER_H

#include <dsound.h>
#include <d3dx9.h>

namespace DXSound{
	
	//����������������Ĭ�����ԣ���
	const int DSBCAPS_NOTHING = 0x00000000;
	
	class CSounder;
	
	//ֻ��һ��CSoundListener,Ҳ����ֻ��һ��LPDIRECTSOUND8��LPDIRECTSOUNDBUFFER8
	class CSoundListener  
	{
		
	public:
		virtual ~CSoundListener();
		
		//�õ�CSoundListener����
		static CSoundListener* GetSound()
		{ 
			return m_pGlobalSLayer; 
		}
		
		
		//�õ�LPDIRECTSOUND8 ����
		LPDIRECTSOUND8 GetDSound()
		{
			return m_pDSound;
		}
		
		
		//����Ψһ��CSoundListener ����
		static void Create( HWND hWnd ,int flags = DSBCAPS_NOTHING)
		{
			new CSoundListener( hWnd, flags);
		}
		
		
		//���������ߵ�λ��
		void SetPosition(int x,int y, int z);
		
		void SetPosition(D3DXVECTOR3 pos)
		{
			SetPosition(pos.x,pos.y,pos.z);
			
		}
		
		
		//���������ߵĳ���
		void SetOrientation(D3DVALUE xFront, D3DVALUE yFront, D3DVALUE zFront, 
			D3DVALUE xTop, 	D3DVALUE yTop, D3DVALUE zTop);
		
		void SetOrientation(D3DVECTOR Front,D3DVECTOR Top)
		{
			SetOrientation(Front.x,Front.y,Front.z,Top.x,Top.y,Top.z);
		}
		
		
	protected:
		CSoundListener( HWND hWnd ,int flags);
		
		
	protected:
		
		LPDIRECTSOUND8			m_pDSound;
		
		LPDIRECTSOUNDBUFFER8	m_pPrimary; // primary mixer
		
		LPDIRECTSOUND3DLISTENER8 m_Listener; //������
		
		bool m_b3dsup;   //�Ƿ�֧��3d��Ч
		
		static CSoundListener* m_pGlobalSLayer;
		
		
		
		
	};
	
	
	inline CSoundListener* Sound()
	{
		return CSoundListener::GetSound();
	}
	
}
#endif //_SOUNDLISTENER_H