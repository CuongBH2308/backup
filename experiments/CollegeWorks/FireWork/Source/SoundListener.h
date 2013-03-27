/*
 文件描述：作为倾听者，可以是听3D和非3D声音
 */
#ifndef _SOUNDLISTENER_H
#define _SOUNDLISTENER_H

#include <dsound.h>
#include <d3dx9.h>

namespace DXSound{
	
	//创建的主缓冲区的默认特性：无
	const int DSBCAPS_NOTHING = 0x00000000;
	
	class CSounder;
	
	//只有一个CSoundListener,也就是只有一个LPDIRECTSOUND8和LPDIRECTSOUNDBUFFER8
	class CSoundListener  
	{
		
	public:
		virtual ~CSoundListener();
		
		//得到CSoundListener对象
		static CSoundListener* GetSound()
		{ 
			return m_pGlobalSLayer; 
		}
		
		
		//得到LPDIRECTSOUND8 对象
		LPDIRECTSOUND8 GetDSound()
		{
			return m_pDSound;
		}
		
		
		//创建唯一的CSoundListener 对象
		static void Create( HWND hWnd ,int flags = DSBCAPS_NOTHING)
		{
			new CSoundListener( hWnd, flags);
		}
		
		
		//设置倾听者的位置
		void SetPosition(int x,int y, int z);
		
		void SetPosition(D3DXVECTOR3 pos)
		{
			SetPosition(pos.x,pos.y,pos.z);
			
		}
		
		
		//设置倾听者的朝向
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
		
		LPDIRECTSOUND3DLISTENER8 m_Listener; //倾听者
		
		bool m_b3dsup;   //是否支持3d音效
		
		static CSoundListener* m_pGlobalSLayer;
		
		
		
		
	};
	
	
	inline CSoundListener* Sound()
	{
		return CSoundListener::GetSound();
	}
	
}
#endif //_SOUNDLISTENER_H