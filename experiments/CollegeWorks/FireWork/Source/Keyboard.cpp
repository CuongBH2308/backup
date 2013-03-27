#include <stack>
#include "Keyboard.h"
#include "InputManager.h"

using namespace std;
using DXInput::CKeyboard;
using DXInput::IKeyboardReceiver;

CKeyboard::CKeyboard( HWND hWnd )
{
	m_pTarget = NULL;

	m_pDevice = NULL;
	
	HRESULT hr;

	//得到DINPUT对象指针
	LPDIRECTINPUT8 pDI = Input()->GetDInput();

	//创建键盘设备
	hr = Input()->GetDInput()->CreateDevice( GUID_SysKeyboard, &m_pDevice, NULL );
    if( FAILED(hr) )
    { 
        throw cGameError("Keyboard could not be created\n");
    } 
 
	//设置数据格式
    hr = m_pDevice->SetDataFormat(&c_dfDIKeyboard); 
    if( FAILED(hr) )
    { 
		SafeRelease( m_pDevice );
        throw cGameError("Keyboard could not be created\n");
    } 
 
    //设置协调层级
    hr = m_pDevice->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
    if( FAILED(hr) )
    { 
		SafeRelease( m_pDevice );
        throw cGameError("Keyboard coop level could not be changed\n");
    } 

	// 初始化键盘状态
	memset( m_keyState, 0, 256*sizeof(bool) );	
}

CKeyboard::~CKeyboard()
{
	if( m_pDevice )
	{
		m_pDevice->Unacquire();
		SafeRelease( m_pDevice );
	}
}



void CKeyboard::SetReceiver( IKeyboardReceiver* pTarget )
{
	m_pTarget = pTarget;
}


//检测key是否按下

bool CKeyboard::Poll( int key )
{
	if( m_keyState[key] & 0x80 )
		return true;
	return false;
}

//处理键盘事件
eResult CKeyboard::Update()
{
	char     newState[256]; 
    HRESULT  hr; 
 
	//刷新并获取新状态
    hr = m_pDevice->Poll(); 
    hr = m_pDevice->GetDeviceState(sizeof(newState),(LPVOID)&newState); 

    if( FAILED(hr) )
    { 
		//重新获取设备再试
		hr = m_pDevice->Acquire();
		if( FAILED( hr ) )
		{
			return resFailed;
		}

	    hr = m_pDevice->Poll(); 
	    hr = m_pDevice->GetDeviceState(sizeof(newState),(LPVOID)&newState); 
		if( FAILED( hr ) )
		{
			return resFailed;
		}
    } 


	//如果存在鼠标消息接收者，消息处理
	if( m_pTarget )
	{
		int i;
		for( i=0; i< 256; i++ ) //　检测每个键
		{
			//前后两次键状态不一样
			if( m_keyState[i] != newState[i] )
			{
				if( !(newState[i] & 0x80) )
				{
					// 是UP
					m_pTarget->KeyUp( i );
				}
				else
				{
					//是按下，这在下面处理
				}
			}

			//更新键盘状态
			m_keyState[i] = newState[i];

			//检测　i　是否按下
			if( Poll( i ) )
			{
				m_pTarget->KeyDown( i );
			}
		}
	}
	else
	{
		//更新键盘状态
		memcpy( m_keyState, newState, 256 );
	}
 
	return resAllGood;
}


