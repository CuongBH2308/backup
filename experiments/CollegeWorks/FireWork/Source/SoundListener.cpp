
#include "SoundListener.h"
#include "Sounder.h"

#include "dxhelper.h"
using DXSound::CSoundListener;

CSoundListener* CSoundListener::m_pGlobalSLayer = NULL;

CSoundListener::CSoundListener( HWND hWnd ,int flags )
{

	m_pDSound = NULL;
	m_pPrimary = NULL;

	// �Ƿ�֧��3D
	(flags&DSBCAPS_CTRL3D)?m_b3dsup = true :m_b3dsup = false;

	if( m_pGlobalSLayer ) //����Ѵ���,�򱨴�,ʵ���˵�������
	{
		throw cGameError( "CSoundListener already initialized!" );
	}
	m_pGlobalSLayer = this;

    HRESULT             hr;
    LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

    // ����IDirectSound����
	hr = DirectSoundCreate8( NULL, &m_pDSound, NULL );
    if( FAILED( hr ) )
	{
        throw cGameError( "DirectSoundCreate failed!" );
	}

    // ����Э���㼶Ϊ�� DSSCL_PRIORITY
	hr = m_pDSound->SetCooperativeLevel( hWnd,DSSCL_PRIORITY );
    if( FAILED( hr ) )
	{
        throw cGameError( "SetCooperativeLevel (DS) failed!" );
	}

    // ������������
	sAutoZero<DSBUFFERDESC> dsbd;
    dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER|flags;
    dsbd.dwBufferBytes = 0;
    dsbd.lpwfxFormat   = NULL;
       
	hr = m_pDSound->CreateSoundBuffer( &dsbd, &pDSBPrimary, NULL );
    if( FAILED( hr ) )
	{
        throw cGameError( "CreateSoundBuffer (DS) failed!" );
	}

    // ��������������ʽ�� 22kHz����  16-bit
    WAVEFORMATEX wfx;
    ZeroMemory( &wfx, sizeof(WAVEFORMATEX) ); 
    wfx.wFormatTag      = WAVE_FORMAT_PCM; 
    wfx.nChannels       = 2; 
    wfx.nSamplesPerSec  = 22050; 
    wfx.wBitsPerSample  = 16; 
    wfx.nBlockAlign     = wfx.wBitsPerSample / 8 * wfx.nChannels;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    if( FAILED( hr = pDSBPrimary->SetFormat(&wfx) ) )
	{
       throw cGameError( "SetFormat (DS) failed!" );
	}

	// ���֧��3D��Ч����ѯ3D������ָ��
	if(flags&DSBCAPS_CTRL3D)
	{
		hr = pDSBPrimary->QueryInterface( IID_IDirectSound3DListener, (VOID**)&m_Listener);
		if( FAILED( hr ) )
		{
			throw cGameError( "query DirectSound3DListener failed!" );
		}
	}
    SafeRelease( pDSBPrimary );
}

CSoundListener::~CSoundListener()
{
	SafeRelease(m_Listener);
	SafeRelease( m_pPrimary );
	SafeRelease( m_pDSound );
	m_pGlobalSLayer = NULL;
}



//*********************************************************************************

void CSoundListener::SetPosition(int x,int y, int z)
{
	if(m_b3dsup){
		
		HRESULT hr;
		hr = m_Listener->SetPosition(x,y,z,DS3D_IMMEDIATE);
		
		if( FAILED( hr ) )
		{
			throw cGameError( "SetPosition failed!" );
		}
	}
}


void CSoundListener::SetOrientation(D3DVALUE xFront, D3DVALUE yFront, D3DVALUE zFront, 
									D3DVALUE xTop, 	D3DVALUE yTop, D3DVALUE zTop)
{
	if(m_b3dsup){
		
		HRESULT hr;
		hr = m_Listener->SetOrientation(xFront,yFront,zFront,xTop,yTop,zTop,DS3D_IMMEDIATE);
		
		if( FAILED( hr ) )
		{
			throw cGameError( "SetOrientation failed!" );
		}
	}
}
