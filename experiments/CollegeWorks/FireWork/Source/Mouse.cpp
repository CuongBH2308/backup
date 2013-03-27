#include "InputManager.h"
#include "Mouse.h"

using DXInput::CMouse;
using DXInput::IMouseReceiver;

CMouse::CMouse(  HWND hWnd, bool bExclusive )
{
	m_pTarget = NULL;

	m_pDevice = NULL;

	HRESULT hr;

	//��������豸
	hr = Input()->GetDInput()->CreateDevice( GUID_SysMouse, &m_pDevice, NULL );
	if( FAILED( hr ))
	{
		throw cGameError("[CMouse::Init]: Couldn't create the device!\n");
	}

	//�������ݸ�ʽ
	hr = m_pDevice->SetDataFormat(&c_dfDIMouse);
 	if( FAILED( hr ))
	{
		SafeRelease( m_pDevice );
		throw cGameError("[CMouse::Init]: SetDataFormat failed\n");
	}

	//����Э���㼶�����������
	if( bExclusive )
	{
		hr = m_pDevice->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND );
	}
	else
	{
		hr = m_pDevice->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	if( FAILED( hr ))
	{
		SafeRelease( m_pDevice );
		throw cGameError("[CMouse::Init]: SetCooperativeLevel failed\n");
	}



	//����ʼ״̬
	m_lastState.lX = 0;
	m_lastState.lY = 0;
	m_lastState.lZ = 0;
	m_lastState.rgbButtons[0] = 0;
	m_lastState.rgbButtons[1] = 0;
	m_lastState.rgbButtons[2] = 0;
	m_lastState.rgbButtons[3] = 0;
}

CMouse::~CMouse()
{
	if( m_pDevice )
	{
		m_pDevice->Unacquire();
		SafeRelease( m_pDevice );
	}
}


void CMouse::SetReceiver( IMouseReceiver* pTarget )
{
	m_pTarget = pTarget;
}


eResult CMouse::Update()
{
	DIMOUSESTATE currState;
    HRESULT  hr; 
 
	//ˢ�²���ȡ��״̬
    hr = m_pDevice->Poll(); 
	hr = m_pDevice->GetDeviceState( sizeof(DIMOUSESTATE), (void*)&currState );

	//��ʧ�ܣ�������һ��
    if( FAILED(hr) )
    { 
		hr = m_pDevice->Acquire();
		if( FAILED( hr ) )
		{
			return resFailed;
		}

	    hr = m_pDevice->Poll(); 
	    hr = m_pDevice->GetDeviceState( sizeof(DIMOUSESTATE),(void*)&currState ); 
		if( FAILED( hr ) )
		{
			return resFailed;
		}
    } 

	//������������Ϣ�����ߣ���Ϣ����
	if( m_pTarget )
	{
		int dx = currState.lX;
		int dy = currState.lY;
		if( dx || dy )
		{
			m_pTarget->MouseMoved( dx, dy );
		}
		if( currState.rgbButtons[0] & 0x80 )
		{
			// ����������
			m_pTarget->MouseButtonDown( 0 );
		}
		if( currState.rgbButtons[1] & 0x80 )
		{
			// ����Ҽ�����
			m_pTarget->MouseButtonDown( 1 );
		}
		if( currState.rgbButtons[2] & 0x80 )
		{
			// �����ᰴ��
			m_pTarget->MouseButtonDown( 2 );
		}
		if( !(currState.rgbButtons[0] & 0x80) && (m_lastState.rgbButtons[0] & 0x80) )
		{
			// ������UP
			m_pTarget->MouseButtonUp( 0 );
		}
		if( !(currState.rgbButtons[1] & 0x80) && (m_lastState.rgbButtons[1] & 0x80) )
		{
			// ����Ҽ�UP
			m_pTarget->MouseButtonUp( 1 );
		}
		if( !(currState.rgbButtons[2] & 0x80) && (m_lastState.rgbButtons[2] & 0x80) )
		{
			// ������UP
			m_pTarget->MouseButtonUp( 2 );
		}

	}
	m_lastState = currState;
	return resAllGood;
}


//��ø��豸
eResult CMouse::Acquire()
{
	HRESULT hr = m_pDevice->Acquire();
	if( FAILED(hr) )
	{
		return resFailed;
	}
	return resAllGood;
}

//�ͷŸ��豸
void CMouse::UnAcquire()
{
	m_pDevice->Unacquire();
}
