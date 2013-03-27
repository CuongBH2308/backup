// JoyStick.cpp: implementation of the CJoyStick class.
//
//////////////////////////////////////////////////////////////////////

#include "JoyStick.h"
#include "InputManager.h"

using DXInput::CJoyStick;
using DXInput::IJoyStickReceiver;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CJoyStick::CJoyStick(HWND hwnd,bool bExclusive)
{

	m_pTarget = NULL;
	

	
	m_pDevice = NULL;

	HRESULT         hr; 
	

	//�����ֱ������о�
	hr = Input()->GetDInput()->EnumDevices(DI8DEVCLASS_GAMECTRL ,EnumDevicesProc,
		                                   this,DIEDFL_ATTACHEDONLY);  //ͨ��thisָ�봫�ݡ�m_pDevice
	if(FAILED(hr))
	{
		throw cGameError("EnumDevices failed");
	}

	if(m_pDevice == NULL)
	{
		return;
	}


	//���������豸�����ʽΪ���ֱ�
	hr = m_pDevice->SetDataFormat(&c_dfDIJoystick2);
	
	if(FAILED(hr))
	{
		throw cGameError("SetDataFormat failed");
	}


	//���������豸Э���㼶
	if(bExclusive)
		hr = m_pDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE|DISCL_BACKGROUND );
	else
		hr = m_pDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	if(FAILED(hr))
	{
		throw cGameError("SetCooperativeLevel failed");
	}
	

	////�����ֱ������һЩ��������
	InitJoystick();

	// ��ʼ���ֱ�״̬
	memset(&m_lastdijs,0,sizeof(DIJOYSTATE2));



}

CJoyStick::~CJoyStick()
{
	if( m_pDevice )
	{
		m_pDevice->Unacquire();
		SafeRelease( m_pDevice );
	}

}


//////////////////////////////////////////////////////////////////////////
//�о��ֱ������ҵ�һ�������
BOOL CJoyStick::EnumDevicesProc(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	CJoyStick* pjs = (CJoyStick*) pvRef;
	HRESULT hr;
	hr = Input()->GetDInput()->CreateDevice(lpddi->guidInstance,&pjs->m_pDevice, NULL );

	if(hr != DI_OK)  
	{
		return DIENUM_CONTINUE;
	}

	else
		return DIENUM_STOP;
}




bool CJoyStick::InitJoystick()
{
   
    // ����: range, deadzone, saturation
	
    DIPROPRANGE diprg; 
	
    diprg.diph.dwSize       = sizeof( diprg ); 
    diprg.diph.dwHeaderSize = sizeof( diprg.diph ); 
    diprg.diph.dwObj        = 0; 
    diprg.diph.dwHow        = DIPH_DEVICE;

	//range
	diprg.lMax              = JOYMAX;
	diprg.lMin              = JOYMIN;
	
    if ( FAILED( m_pDevice->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
        return FALSE; 
	
    //deadzone.
    DIPROPDWORD dipdw;
	
    dipdw.diph.dwSize       = sizeof( dipdw ); 
    dipdw.diph.dwHeaderSize = sizeof( dipdw.diph ); 
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = JOYDEAD;
	
    if ( FAILED( m_pDevice->SetProperty( DIPROP_DEADZONE, &dipdw.diph ) ) )
        return FALSE;
	
    //saturation.
    dipdw.dwData            = JOYSAT;
    if ( FAILED( m_pDevice->SetProperty( DIPROP_SATURATION, &dipdw.diph ) ) )
        return FALSE;
	
    
    return TRUE;
}


void CJoyStick::SetReceiver(IJoyStickReceiver* pTarget )
{
	m_pTarget = pTarget;
}


eResult CJoyStick::Update()
{

	DIJOYSTATE2   curdijs;
	HRESULT hr;

	

	if(!m_pDevice)
		return resFalse;

	hr = m_pDevice->Poll();   //���ҡ��
	hr = m_pDevice->GetDeviceState( sizeof( DIJOYSTATE2 ), &curdijs );

	if( FAILED(hr) )
    { 
		hr = m_pDevice->Acquire();
		if( FAILED( hr ) )
		{
			return resFailed;
		}
		
		hr = m_pDevice->Poll(); 
		hr = m_pDevice->GetDeviceState( sizeof( DIJOYSTATE2 ), &curdijs );
		if( FAILED( hr ) )
		{
			return resFailed;
		}
    } 
	if(FAILED(hr))
	{
		return resFailed;
	}
	

	if(m_pTarget)
	{
		
		int dx = curdijs.lX;
		int dy = curdijs.lY;
		int dz = curdijs.lZ;
		
		if(dx||dy)
		{
			m_pTarget->JoyStickAxisMoved(dx,dy);
		}
		
		
		for(int i=0;i<sizeof(curdijs.rgbButtons);i++)
		{
			if(curdijs.rgbButtons[i]&0x80)
			{
				m_pTarget->JoyStickButtonDown(i);
			}
			
			else if(m_lastdijs.rgbButtons[i]&0x80)
			{
				m_pTarget->JoyStickButtonUp(i);
			}
		}
	}
	m_lastdijs= curdijs;
	return resAllGood;

	
}

// ����ֱ�����
eResult CJoyStick::Acquire()
{
	if(!m_pDevice)
		return resFailed;
		
	HRESULT hr = m_pDevice->Acquire();
	if( FAILED(hr) )
	{
		return resFailed;
	}
	return resAllGood;
}


void CJoyStick::UnAcquire()
{
	if(m_pDevice)
	{
		m_pDevice->Unacquire();
	}
}