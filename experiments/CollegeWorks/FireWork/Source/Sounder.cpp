
#include "Sounder.h"

#include "dxhelper.h"

using DXSound::CSounder;
using DXSound::CWaveSoundRead;
using std::map;

map< CWaveSoundRead*, int > CSounder::m_waveMap;

void CSounder::SetVolume(int lVolume)
{
	m_pBuffer->SetVolume(lVolume);
}

CSounder::CSounder()
{
}

CSounder::CSounder(char* filename )
{
	m_pWaveSoundRead = NULL;
	m_pBuffer = NULL;

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
}

CSounder::CSounder( CSounder& in )
{
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;
	//初始化，创建缓冲区
	Init();
	
	//填充数据
	Fill();
}

CSounder& CSounder::operator=( const CSounder &in )
{
	/**
	 * 销毁原数据
	 */
	int count = --m_waveMap[ m_pWaveSoundRead ];
	if( !count )
	{
		delete m_pWaveSoundRead;
	}
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
	
	return *this;
}


CSounder::~CSounder()
{
	int count = m_waveMap[ m_pWaveSoundRead ];
	if( count == 1 )
	{
		delete m_pWaveSoundRead;
	}
	else
	{
		m_waveMap[ m_pWaveSoundRead ] = count - 1;
	}
		
	SafeRelease( m_pBuffer );
}

void CSounder::Init()
{
    //初始化DSBUFFERDESC
	sAutoZero<DSBUFFERDESC> dsbd;
    dsbd.dwFlags       = DSBCAPS_STATIC|DSBCAPS_CTRLVOLUME;//|DSBCAPS_CTRL3D;
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

	// 升级到新的接口版本
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


void CSounder::Restore()
{
    HRESULT hr;

    if( NULL == m_pBuffer )
	{
		return;
	}

    DWORD dwStatus;
    if( FAILED( hr = m_pBuffer->GetStatus( &dwStatus ) ) )
	{
		throw cGameError( "couldn't get buffer status" );
	}

    if( dwStatus & DSBSTATUS_BUFFERLOST )
    {
		//如果应用程序刚开始，可能我们还不能控制DirectSound
		//这时我们就不断重复修复，直到成功为止
        do 
        {
            hr = m_pBuffer->Restore();
            if( hr == DSERR_BUFFERLOST )
                Sleep( 10 );
        }
        while( hr = m_pBuffer->Restore() );

		//缓冲区已修复，可以加载数据了
        Fill();
    }
}


void CSounder::Fill()
{
    HRESULT hr; 
    uchar*   pbWavData; // 指向实际wav数据的指针
    uint    cbWavSize; // 数据大小
    void*   pbData  = NULL;
    void*   pbData2 = NULL;
    ulong   dwLength;
    ulong   dwLength2;

	// wav文件的大小
    uint nWaveFileSize = m_pWaveSoundRead->m_ckIn.cksize;

    //为此wav文件分配足够的空间
    pbWavData = new uchar[ nWaveFileSize ];

	//分配失败
    if( NULL == pbWavData )
	{
	    delete [] pbWavData;
        throw cGameError("Out of memory!");
	}

	//读数据到pbWavData中去
	hr = m_pWaveSoundRead->Read( 
		nWaveFileSize, 
        pbWavData, 
        &cbWavSize );
    if( FAILED( hr ) )           
	{
	    delete [] pbWavData;
        throw cGameError("m_pWaveSoundRead->Read failed");
	}

    //到文件头
    m_pWaveSoundRead->Reset();

    //锁住缓冲区以拷贝数据
	hr = m_pBuffer->Lock( 
		0, m_bufferSize, &pbData, &dwLength, 
        &pbData2, &dwLength2, 0L );
    if( FAILED( hr ) )
	{
	    delete [] pbWavData;
        throw cGameError("m_pBuffer->Lock failed");
	}

    memcpy( pbData, pbWavData, m_bufferSize );

	//拷贝完毕，解锁
    m_pBuffer->Unlock( pbData, m_bufferSize, NULL, 0 );

    //使用完pbWavData，释放它
    delete [] pbWavData;
}


bool CSounder::IsPlaying()
{
    DWORD dwStatus = 0;

    m_pBuffer->GetStatus( &dwStatus );

    if( dwStatus & DSBSTATUS_PLAYING )
        return true;
    else 
        return false;
}


void CSounder::Play( bool bLoop )
{
	HRESULT hr;
    if( NULL == m_pBuffer )
        return;

    // 如果缓冲区丢失了，修复它
    Restore();

    // 播放
    DWORD dwLooped = bLoop ? DSBPLAY_LOOPING : 0L;
    if( FAILED( hr = m_pBuffer->Play( 0, 0, dwLooped ) ) )
	{
		throw cGameError("m_pBuffer->Play failed");
	}
}

void CSounder::Stop()
{
	HRESULT hr;
    if( NULL == m_pBuffer )
        return;

	if(!IsPlaying())
		return;
   
    if( FAILED( hr = m_pBuffer->Stop()) )
	{
		throw cGameError("m_pBuffer->Stop failed");
	}
	
}