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

	//��ѯ�õ���3D����ָ�롡m_Buffer3D
	if( FAILED(m_pBuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&m_buff3D)))
	{
		throw cGameError("couldn't query DirectSound3DBuffer!");

	}

}


C3DSounder::C3DSounder(C3DSounder& in)
{
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;
	//��ʼ��������������
	Init();
    //�������
	Fill();

	//��ѯ�õ���3D����ָ�롡m_Buffer3D
	if( FAILED(m_pBuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&m_buff3D)))
	{
		throw cGameError("couldn't query DirectSound3DBuffer!");
		
	}
	
}


C3DSounder& C3DSounder::operator = ( const C3DSounder &in )
{
	/**
	 * ����ԭ����
	 */
	int count = --m_waveMap[ m_pWaveSoundRead ];
	if( !count )
	{
		delete m_pWaveSoundRead;
	}
	
	SafeRelease( m_buff3D );
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

	//��ѯ�õ���3D����ָ�롡m_Buffer3D
	if( FAILED(m_pBuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&m_buff3D)))
	{
		throw cGameError("couldn't query DirectSound3DBuffer!");
		
	}
	
	return *this;
}

C3DSounder::~C3DSounder()
{
	
	SafeRelease( m_buff3D );


	//�������е��������Ѿ��ڻ��������
	
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
//�ض��� ��ʼ������,ʹ��������3D���ƹ���
void C3DSounder::Init()
{
	//��ʼ��DSBUFFERDESC
	sAutoZero<DSBUFFERDESC> dsbd;
    dsbd.dwFlags       = DSBCAPS_STATIC|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRL3D;
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

	//�������µĽӿڰ汾
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

	Min<1?Min = 1:Min; //��С����С��1

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