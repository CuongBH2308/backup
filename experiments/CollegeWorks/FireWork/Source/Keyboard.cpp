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

	//�õ�DINPUT����ָ��
	LPDIRECTINPUT8 pDI = Input()->GetDInput();

	//���������豸
	hr = Input()->GetDInput()->CreateDevice( GUID_SysKeyboard, &m_pDevice, NULL );
    if( FAILED(hr) )
    { 
        throw cGameError("Keyboard could not be created\n");
    } 
 
	//�������ݸ�ʽ
    hr = m_pDevice->SetDataFormat(&c_dfDIKeyboard); 
    if( FAILED(hr) )
    { 
		SafeRelease( m_pDevice );
        throw cGameError("Keyboard could not be created\n");
    } 
 
    //����Э���㼶
    hr = m_pDevice->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
    if( FAILED(hr) )
    { 
		SafeRelease( m_pDevice );
        throw cGameError("Keyboard coop level could not be changed\n");
    } 

	// ��ʼ������״̬
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


//���key�Ƿ���

bool CKeyboard::Poll( int key )
{
	if( m_keyState[key] & 0x80 )
		return true;
	return false;
}

//��������¼�
eResult CKeyboard::Update()
{
	char     newState[256]; 
    HRESULT  hr; 
 
	//ˢ�²���ȡ��״̬
    hr = m_pDevice->Poll(); 
    hr = m_pDevice->GetDeviceState(sizeof(newState),(LPVOID)&newState); 

    if( FAILED(hr) )
    { 
		//���»�ȡ�豸����
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


	//������������Ϣ�����ߣ���Ϣ����
	if( m_pTarget )
	{
		int i;
		for( i=0; i< 256; i++ ) //�����ÿ����
		{
			//ǰ�����μ�״̬��һ��
			if( m_keyState[i] != newState[i] )
			{
				if( !(newState[i] & 0x80) )
				{
					// ��UP
					m_pTarget->KeyUp( i );
				}
				else
				{
					//�ǰ��£��������洦��
				}
			}

			//���¼���״̬
			m_keyState[i] = newState[i];

			//��⡡i���Ƿ���
			if( Poll( i ) )
			{
				m_pTarget->KeyDown( i );
			}
		}
	}
	else
	{
		//���¼���״̬
		memcpy( m_keyState, newState, 256 );
	}
 
	return resAllGood;
}


