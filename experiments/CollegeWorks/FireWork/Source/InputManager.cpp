#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"

using DXInput::CInputManager;

CInputManager* CInputManager::m_pGlobalILayer = NULL;

//创建管理对象，及其相应的事件处理类（鼠标，键盘，手柄）
CInputManager::CInputManager( 
	HINSTANCE hInst, 
	HWND hWnd, 
	bool bExclusive, 
	bool bUseKeyboard, 
	bool bUseMouse ,
	bool bUseJoystick)
{


	m_pKeyboard = NULL;
	m_pMouse = NULL;
	m_pJoystick = NULL;

	if( m_pGlobalILayer )
	{
		throw cGameError("CInputManager already initialized!\n");
	}
	m_pGlobalILayer = this;

	HRESULT hr;

	/**
	 * Create the DI8 object
	 */

	hr = DirectInput8Create( hInst, DIRECTINPUT_VERSION, 
						IID_IDirectInput8, (void**)&m_pDI, NULL );
    if( FAILED(hr) )
	{
		throw cGameError("DirectInput8 object could not be created\n"); 
	}

	try 
	{
		if( bUseKeyboard )
		{
			m_pKeyboard = new CKeyboard( hWnd );
		}
		if( bUseMouse )
		{
			m_pMouse = new CMouse( hWnd, bExclusive );
		}
		if( bUseJoystick )
		{
			m_pJoystick = new CJoyStick( hWnd, bExclusive );
		}
	}
	catch( ... )
	{
		SafeRelease( m_pDI );
		throw;
	}

}


CInputManager::~CInputManager()
{
	if( m_pDI )
	{
		if( m_pKeyboard )
		{
			delete m_pKeyboard; // this does all the de-init.
		}

		if( m_pMouse )
		{
			delete m_pMouse; // this does all the de-init.
		}

		if( m_pJoystick )
		{
			delete m_pJoystick; // this does all the de-init.
		}


		SafeRelease( m_pDI );
	}
	m_pGlobalILayer = NULL;
}

//处理所有的事件
void CInputManager::UpdateDevices()
{
	if( m_pKeyboard )
	{
		m_pKeyboard->Update();
	}
	if( m_pMouse )
	{
		m_pMouse->Update();
	}
	if( m_pJoystick )
	{
		m_pJoystick->Update();
	}
}


void CInputManager::SetFocus()
{
	if( m_pKeyboard )
	{
		m_pKeyboard->ClearTable();
	}
	if( m_pMouse )
	{
		m_pMouse->Acquire();
	}
	if( m_pJoystick )
	{
		m_pJoystick->Acquire();
	}
}


void CInputManager::KillFocus()
{
	if( m_pKeyboard )
	{
		m_pKeyboard->ClearTable();
	}
	if( m_pMouse )
	{
		m_pMouse->UnAcquire();
	}
	if( m_pJoystick )
	{
		m_pJoystick->UnAcquire();
	}
}
