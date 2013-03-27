#ifndef _CCamera_H
#define _CCamera_H

#include <d3dx9.h>

namespace d3d
{
	
	class CCamera
	{
	public:
		//AIRCRAFT：能够做任何动作
		//LANDOBJECT：只能做地面上能做的常规动作
		enum CCameraType { LANDOBJECT, AIRCRAFT };
		
		CCamera();
		//pos:相机的初始位置
		CCamera(CCameraType CCameraType,D3DXVECTOR3 pos);
		~CCamera();
		
		//动作
		void strafe(float units); // left/right
		void fly(float units);    // up/down
		void walk(float units);   // forward/backward
		
		void pitch(float angle); // rotate on right vector
		void yaw(float angle);   // rotate on up vector
		void roll(float angle);  // rotate on look vector
	
		

		void getViewMatrix(D3DXMATRIX* V); 
		void setCCameraType(CCameraType CCameraType); 
		void getPosition(D3DXVECTOR3* pos); 
		void setPosition(D3DXVECTOR3* pos); 
		void setPosition(float x,float y,float z); 
		
		void getRight(D3DXVECTOR3* right);
		void getUp(D3DXVECTOR3* up);
		void getLook(D3DXVECTOR3* look);
	protected:
		CCameraType  m_CCameraType;
		D3DXVECTOR3 m_right;
		D3DXVECTOR3 m_up;
		D3DXVECTOR3 m_look;
		D3DXVECTOR3 m_pos;
	};
}
#endif // __CCameraH__