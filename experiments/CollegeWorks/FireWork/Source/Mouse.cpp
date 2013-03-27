#include "InputManager.h"
#include "Mouse.h"

using DXInput::CMouse;
using DXInput::IMouseReceiver;

CMouse::CMouse(  HWND hWnd, bool bExclusive )
{
	m_pTarget = NULL;

	m_pDevice = NULL;

	HRESULT hr;

	//创建鼠标设备
	hr = Input()->GetDInput()->CreateDevice( GUID_SysMouse, &m_pDevice, NULL );
	if( FAILED( hr ))
	{
		throw cGameError("[CMouse::Init]: Couldn't create the device!\n");
	}

	//设置数据格式
	hr = m_pDevice->SetDataFormat(&c_dfDIMouse);
 	if( FAILED( hr ))
	{
		SafeRelease( m_pDevice );
		throw cGameError("[CMouse::Init]: SetDataFormat failed\n");
	}

	//设置协调层级：分两种情况
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



	//鼠标初始状态
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
 
	//刷新并获取新状态
    hr = m_pDevice->Poll(); 
	hr = m_pDevice->GetDeviceState( sizeof(DIMOUSESTATE), (void*)&currState );

	//若失败，重新来一次
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

	//如果存在鼠标消息接收者，消息处理
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
			// 鼠标左键按下
			m_pTarget->MouseButtonDown( 0 );
		}
		if( currState.rgbButtons[1] & 0x80 )
		{
			// 鼠标右键按下
			m_pTarget->MouseButtonDown( 1 );
		}
		if( currState.rgbButtons[2] & 0x80 )
		{
			// 鼠标滚轴按下
			m_pTarget->MouseButtonDown( 2 );
		}
		if( !(currState.rgbButtons[0] & 0x80) && (m_lastState.rgbButtons[0] & 0x80) )
		{
			// 鼠标左键UP
			m_pTarget->MouseButtonUp( 0 );
		}
		if( !(currState.rgbButtons[1] & 0x80) && (m_lastState.rgbButtons[1] & 0x80) )
		{
			// 鼠标右键UP
			m_pTarget->MouseButtonUp( 1 );
		}
		if( !(currState.rgbButtons[2] & 0x80) && (m_lastState.rgbButtons[2] & 0x80) )
		{
			// 鼠标滚轴UP
			m_pTarget->MouseButtonUp( 2 );
		}

	}
	m_lastState = currState;
	return resAllGood;
}


//获得该设备
eResult CMouse::Acquire()
{
	HRESULT hr = m_pDevice->Acquire();
	if( FAILED(hr) )
	{
		return resFailed;
	}
	return resAllGood;
}

//释放该设备
void CMouse::UnAcquire()
{
	m_pDevice->Unacquire();
}
