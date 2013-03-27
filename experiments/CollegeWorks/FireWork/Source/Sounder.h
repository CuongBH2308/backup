/*
 文件描述：播放普通WAV音乐	
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
		
		void SetVolume(int lVolume);   //调整音量
		
		void Restore();                // 修复缓冲区
		
		void Fill();                   //加载音乐数据到缓冲区
		
		bool IsPlaying();
		
		
	protected:
		
		CSounder();   //用在子类中，需要默认的构造函数
		
		
		virtual void Init();// 创建缓冲区
		
	protected:
		CWaveSoundRead*     m_pWaveSoundRead; //从wave文件读数据
		LPDIRECTSOUNDBUFFER8	m_pBuffer;    //次缓冲区
		
		int					m_bufferSize;
		
		//不同的CSounder对象如果使用同一个WAVE文件，我们只需加载它一次
		static std::map< CWaveSoundRead*, int > m_waveMap;
		
	};
	
}

#endif //_SOUND_H
