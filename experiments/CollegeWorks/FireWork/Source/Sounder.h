/*
 �ļ�������������ͨWAV����	
 */
#ifndef _SOUND_H
#define _SOUND_H

#include <map>

#include "SoundListener.h"
#include "Wavread.h"

namespace DXSound{
	
	class CSounder  
	{
	public:
		CSounder( char* filename );
		
		CSounder( CSounder& in );     //copy constructor
		
		CSounder& operator=( const CSounder &in );
		
		virtual ~CSounder();
		
		
	public:
		
		void Play( bool bLoop = false );
		
		void Stop();
		
		void SetVolume(int lVolume);   //��������
		
		void Restore();                // �޸�������
		
		void Fill();                   //�����������ݵ�������
		
		bool IsPlaying();
		
		
	protected:
		
		CSounder();   //���������У���ҪĬ�ϵĹ��캯��
		
		
		virtual void Init();// ����������
		
	protected:
		CWaveSoundRead*     m_pWaveSoundRead; //��wave�ļ�������
		LPDIRECTSOUNDBUFFER8	m_pBuffer;    //�λ�����
		
		int					m_bufferSize;
		
		//��ͬ��CSounder�������ʹ��ͬһ��WAVE�ļ�������ֻ�������һ��
		static std::map< CWaveSoundRead*, int > m_waveMap;
		
	};
	
}

#endif //_SOUND_H
