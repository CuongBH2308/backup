
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

    // ����һ��CWaveSoundRead����¼
    m_pWaveSoundRead = new CWaveSoundRead();
	m_waveMap[ m_pWaveSoundRead ] = 1;

    // ����WAVE�ļ�����
    if( FAILED( m_pWaveSoundRead->Open( filename ) ) )
    {
        throw cGameError("couldn't open file!");
    }

	//��ʼ��������������
	Init();

	//�������
	Fill();
}

CSounder::CSounder( CSounder& in )
{
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;
	//��ʼ��������������
	Init();
	
	//�������
	Fill();
}

CSounder& CSounder::operator=( const CSounder &in )
{
	/**
	 * ����ԭ����
	 */
	int count = --m_waveMap[ m_pWaveSoundRead ];
	if( !count )
	{
		delete m_pWaveSoundRead;
	}
	SafeRelease( m_pBuffer );

	/**
	 * ����������
	 */
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;

	//��ʼ��������������
	Init();
	
	//�������
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
    //��ʼ��DSBUFFERDESC
	sAutoZero<DSBUFFERDESC> dsbd;
    dsbd.dwFlags       = DSBCAPS_STATIC|DSBCAPS_CTRLVOLUME;//|DSBCAPS_CTRL3D;
    dsbd.dwBufferBytes = m_pWaveSoundRead->m_ckIn.cksize;
    dsbd.lpwfxFormat   = m_pWaveSoundRead->m_pwfx;

    HRESULT hr; 

	// ��ʱDirectSoundBuffer�ӿ�ָ��
	LPDIRECTSOUNDBUFFER pTempBuffer = 0;

	// ��������������ֻ��Ϊ������
	hr = Sound()->GetDSound()->CreateSoundBuffer( &dsbd, &pTempBuffer, NULL );//��ֻ��Ϊ������
	
    if( FAILED( hr ) )
    {
        throw cGameError("CreateSoundBuffer failed!");
    }

	// �������µĽӿڰ汾
	pTempBuffer->QueryInterface( IID_IDirectSoundBuffer8, (void**)&m_pBuffer );
	if( FAILED( hr ) )
    {
        throw cGameError("SoundBuffer query to 8 failed!");
    }
	
	//�ͷ���ʱ���Ͻӿڰ汾
	pTempBuffer->Release();

	//��¼�»�������С
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
		//���Ӧ�ó���տ�ʼ���������ǻ����ܿ���DirectSound
		//��ʱ���ǾͲ����ظ��޸���ֱ���ɹ�Ϊֹ
        do 
        {
            hr = m_pBuffer->Restore();
            if( hr == DSERR_BUFFERLOST )
                Sleep( 10 );
        }
        while( hr = m_pBuffer->Restore() );

		//���������޸������Լ���������
        Fill();
    }
}


void CSounder::Fill()
{
    HRESULT hr; 
    uchar*   pbWavData; // ָ��ʵ��wav���ݵ�ָ��
    uint    cbWavSize; // ���ݴ�С
    void*   pbData  = NULL;
    void*   pbData2 = NULL;
    ulong   dwLength;
    ulong   dwLength2;

	// wav�ļ��Ĵ�С
    uint nWaveFileSize = m_pWaveSoundRead->m_ckIn.cksize;

    //Ϊ��wav�ļ������㹻�Ŀռ�
    pbWavData = new uchar[ nWaveFileSize ];

	//����ʧ��
    if( NULL == pbWavData )
	{
	    delete [] pbWavData;
        throw cGameError("Out of memory!");
	}

	//�����ݵ�pbWavData��ȥ
	hr = m_pWaveSoundRead->Read( 
		nWaveFileSize, 
        pbWavData, 
        &cbWavSize );
    if( FAILED( hr ) )           
	{
	    delete [] pbWavData;
        throw cGameError("m_pWaveSoundRead->Read failed");
	}

    //���ļ�ͷ
    m_pWaveSoundRead->Reset();

    //��ס�������Կ�������
	hr = m_pBuffer->Lock( 
		0, m_bufferSize, &pbData, &dwLength, 
        &pbData2, &dwLength2, 0L );
    if( FAILED( hr ) )
	{
	    delete [] pbWavData;
        throw cGameError("m_pBuffer->Lock failed");
	}

    memcpy( pbData, pbWavData, m_bufferSize );

	//������ϣ�����
    m_pBuffer->Unlock( pbData, m_bufferSize, NULL, 0 );

    //ʹ����pbWavData���ͷ���
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

    // �����������ʧ�ˣ��޸���
    Restore();

    // ����
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