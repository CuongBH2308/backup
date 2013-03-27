// 3DSounder.cpp: implementation of the C3DSounder class.
//
//////////////////////////////////////////////////////////////////////

#include "3DSounder.h"
#include "dxhelper.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using DXSound::C3DSounder;
using DXSound::CWaveSoundRead;

C3DSounder::C3DSounder(char* filename)
{
	m_pWaveSoundRead = NULL;
	m_pBuffer = NULL;
	m_buff3D = NULL;
	
    // 创建一个CWaveSoundRead并记录
    m_pWaveSoundRead = new CWaveSoundRead();
	m_waveMap[ m_pWaveSoundRead ] = 1;
	
    // 加载WAVE文件数据
    if( FAILED( m_pWaveSoundRead->Open( filename ) ) )
    {
        throw cGameError("couldn't open file!");
    }
	
	//初始化，创建缓冲区
	Init();

	//填充数据
	Fill();

	//查询得到　3D缓冲指针　m_Buffer3D
	if( FAILED(m_pBuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&m_buff3D)))
	{
		throw cGameError("couldn't query DirectSound3DBuffer!");

	}

}


C3DSounder::C3DSounder(C3DSounder& in)
{
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;
	//初始化，创建缓冲区
	Init();
    //填充数据
	Fill();

	//查询得到　3D缓冲指针　m_Buffer3D
	if( FAILED(m_pBuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&m_buff3D)))
	{
		throw cGameError("couldn't query DirectSound3DBuffer!");
		
	}
	
}


C3DSounder& C3DSounder::operator = ( const C3DSounder &in )
{
	/**
	 * 销毁原数据
	 */
	int count = --m_waveMap[ m_pWaveSoundRead ];
	if( !count )
	{
		delete m_pWaveSoundRead;
	}
	
	SafeRelease( m_buff3D );
	SafeRelease( m_pBuffer );


	/**
	 * 拷贝新数据
	 */
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;

	//初始化，创建缓冲区
	Init();

	//填充数据
	Fill();

	//查询得到　3D缓冲指针　m_Buffer3D
	if( FAILED(m_pBuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&m_buff3D)))
	{
		throw cGameError("couldn't query DirectSound3DBuffer!");
		
	}
	
	return *this;
}

C3DSounder::~C3DSounder()
{
	
	SafeRelease( m_buff3D );


	//下面所有的清理工作已经在基类中完成
	
	/*	int count = m_waveMap[ m_pWaveSoundRead ];
	if( count == 1 )
	{
		delete m_pWaveSoundRead;
	}
	else
	{
		m_waveMap[ m_pWaveSoundRead ] = count - 1;
	}
	
    */

	
   //	SafeRelease( m_pBuffer );
	

}


//******************************************************************************
//重定义 初始化函数,使缓冲区有3D控制功能
void C3DSounder::Init()
{
	//初始化DSBUFFERDESC
	sAutoZero<DSBUFFERDESC> dsbd;
    dsbd.dwFlags       = DSBCAPS_STATIC|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRL3D;
    dsbd.dwBufferBytes = m_pWaveSoundRead->m_ckIn.cksize;
    dsbd.lpwfxFormat   = m_pWaveSoundRead->m_pwfx;

    HRESULT hr; 

	// 临时DirectSoundBuffer接口指针
	LPDIRECTSOUNDBUFFER pTempBuffer = 0;

	// 创建缓冲区　　只能为单声道
	hr = Sound()->GetDSound()->CreateSoundBuffer( &dsbd, &pTempBuffer, NULL );//　只能为单声道
	
    if( FAILED( hr ) )
    {
        throw cGameError("CreateSoundBuffer failed!");
    }

	//升级到新的接口版本
	pTempBuffer->QueryInterface( IID_IDirectSoundBuffer8, (void**)&m_pBuffer );
	if( FAILED( hr ) )
    {
        throw cGameError("SoundBuffer query to 8 failed!");
    }
	
	//释放临时的老接口版本
	pTempBuffer->Release();

    //记录下缓冲区大小
    m_bufferSize = dsbd.dwBufferBytes;
}


//////////////////////////////////////////////////////////////////////////


void C3DSounder::SetDistance(float Min,float Max)
{
	if(Min>Max)
	{
		float tmp;
		tmp = Min;
		Min = Max;
		Max = tmp;
	}

	Min<1?Min = 1:Min; //最小不能小于1

	 HRESULT hr; 

	 hr = m_buff3D->SetMinDistance(Min,DS3D_IMMEDIATE);
	 if(FAILED(hr))
	 {
          throw cGameError("SetMinDistance failed!");
	 }

	 hr = m_buff3D->SetMaxDistance(Max,DS3D_IMMEDIATE);
	 if(FAILED(hr))
	 {
		 throw cGameError("SetMaxDistance failed!");
	 }


}


void C3DSounder::SetPosition(int x,int y,int z)
{
	HRESULT hr;
	hr = m_buff3D->SetPosition(x,y,z,DS3D_IMMEDIATE);
	if(FAILED(hr))
	{
		throw cGameError("SetPosition failed!");
	}
}