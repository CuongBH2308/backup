/*
  �ļ��������̳���CSounder��������3D��Ч��3D��Ч����
 */

#ifndef _3DSounder_H
#define _3DSounder_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sounder.h"

namespace DXSound{
	class C3DSounder : public CSounder  
	{
	public:
		
		C3DSounder(char* filename);
		
		C3DSounder( C3DSounder& in );//copy constructor
		
		//C3DSounder( CSounder& in );//copy constructor,create a 3D sounder from a non3d sounder
		
		C3DSounder& operator=( const C3DSounder &in );
		
		virtual ~C3DSounder();
		
	public:
		//���ÿɱ������������С���롡
		void SetDistance(float Min,float Max);
		
		//���÷�����λ��
		void SetPosition(int x,int y,int z);
		void SetPosition(D3DXVECTOR3 pos){SetPosition(pos.x,pos.y,pos.z);}
		
	protected:

		//����3D������
		virtual void Init();
		
	protected:
		LPDIRECTSOUND3DBUFFER m_buff3D; //3D buffer
		
	};
	
}
#endif // _3DSounder_H
