#include "Camera.h"
using d3d::CCamera;


CCamera::CCamera()
{
	m_CCameraType = AIRCRAFT;

	m_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

CCamera::CCamera(CCameraType CCameraType,D3DXVECTOR3 pos)
{
	m_CCameraType = CCameraType;

	m_pos   = pos;
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

CCamera::~CCamera()
{

}

void CCamera::getPosition(D3DXVECTOR3* pos)
{
	*pos = m_pos;
}

void CCamera::setPosition(float x,float y,float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void CCamera::setPosition(D3DXVECTOR3* pos)
{
	m_pos = *pos;
}

void CCamera::getRight(D3DXVECTOR3* right)
{
	*right = m_right;
}

void CCamera::getUp(D3DXVECTOR3* up)
{
	*up = m_up;
}

void CCamera::getLook(D3DXVECTOR3* look)
{
	*look = m_look;
}

//前后走
void CCamera::walk(float units)
{
	if( m_CCameraType == LANDOBJECT )
		m_pos += D3DXVECTOR3(m_look.x, 0.0f, m_look.z) * units;

	if( m_CCameraType == AIRCRAFT )
		m_pos += m_look * units;
}

//左右走
void CCamera::strafe(float units)
{
	if( m_CCameraType == LANDOBJECT )
		m_pos += D3DXVECTOR3(m_right.x, 0.0f, m_right.z) * units;

	if( m_CCameraType == AIRCRAFT )
		m_pos += m_right * units;
}

//上升
void CCamera::fly(float units)
{
	if( m_CCameraType == AIRCRAFT )
		m_pos += m_up * units;
}

//俯仰转
void CCamera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &m_right,	angle);

	D3DXVec3TransformCoord(&m_up,&m_up, &T);
	D3DXVec3TransformCoord(&m_look,&m_look, &T);
}

//左右转
void CCamera::yaw(float angle)
{
	D3DXMATRIX T;

	if( m_CCameraType == LANDOBJECT )
		D3DXMatrixRotationY(&T, angle);

	if( m_CCameraType == AIRCRAFT )
		D3DXMatrixRotationAxis(&T, &m_up, angle);

	D3DXVec3TransformCoord(&m_right,&m_right, &T);
	D3DXVec3TransformCoord(&m_look,&m_look, &T);
}

//横着转
void CCamera::roll(float angle)
{
	if( m_CCameraType == AIRCRAFT )
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &m_look,	angle);

		D3DXVec3TransformCoord(&m_right,&m_right, &T);
		D3DXVec3TransformCoord(&m_up,&m_up, &T);
	}
}

void CCamera::getViewMatrix(D3DXMATRIX* V)
{
	D3DXVec3Normalize(&m_look, &m_look);

	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);

	float x = -D3DXVec3Dot(&m_right, &m_pos);
	float y = -D3DXVec3Dot(&m_up, &m_pos);
	float z = -D3DXVec3Dot(&m_look, &m_pos);

	(*V)(0,0) = m_right.x; (*V)(0, 1) = m_up.x; (*V)(0, 2) = m_look.x; (*V)(0, 3) = 0.0f;
	(*V)(1,0) = m_right.y; (*V)(1, 1) = m_up.y; (*V)(1, 2) = m_look.y; (*V)(1, 3) = 0.0f;
	(*V)(2,0) = m_right.z; (*V)(2, 1) = m_up.z; (*V)(2, 2) = m_look.z; (*V)(2, 3) = 0.0f;
	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}

void CCamera::setCCameraType(CCameraType CCameraType)
{
	m_CCameraType = CCameraType;
}
