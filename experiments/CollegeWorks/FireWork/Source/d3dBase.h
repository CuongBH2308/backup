#ifndef _d3dBase_H
#define _d3dBase_H

#include <d3dx9.h>
#include <string>
#include <vector>
#include <limits>

#include "file.h"
#include "Courtyard.h"

//DWORD -- > D3DXCOLOR
#define  DWTOD3DXCOLOR(dwcolor)   D3DCOLOR_XRGB((dwcolor)>>16,(dwcolor)>>8,(dwcolor))

const int MaxObject = 10;
const int MaxTexPerObj = 15;
const int MaxTerrain = 5;

namespace d3dbase
{

	
	/////////////////����/////////////////////////////////////////////////////////
	//��������
	bool CreateD3DWindow(HINSTANCE hInstance,HWND& hwnd,int width, int height);  // [in] Application instance.

	//��ʼ��D3D
	bool InitD3D(
		HWND hwnd,                  //[in] MainWindow
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType,     // [in] HAL or REF
		IDirect3DDevice9** device);// [out]The created device.

	//��Ϣѭ��
	int EnterMsgLoop( 
		bool (*ptr_display)(float timeDelta));

	//������Ϣ������
	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);


	//
	// ��������COM����
	//
	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}
	
	//�ͷ�ָ��
	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}
	
	//������
	bool DrawBasicScene(CCourtyard* pcy,IDirect3DDevice9* device, float scale);

	//����ģ��
	bool LoadXFileMesh(ID3DXMesh**                      Mesh,
		               std::string                     strFilename,//in:Xfile������
		               IDirect3DDevice9*               Device,//��ǰ�豸
		               std::vector<D3DMATERIAL9>&       Mtrls,   //out:���ز��ʼ�
	                   std::vector<IDirect3DTexture9*>& Textures);//out����������

	
	// �õ�[lowBound,highBound]֮��������
	float GetRandomFloat(float lowBound, float highBound);
	
	
	//�õ�min �͡�max֮����������
	void GetRandomVector(
		D3DXVECTOR3* out,
		D3DXVECTOR3* min,
		D3DXVECTOR3* max);
	
	//float --> DWORD
	DWORD FtoDw(float f);
	
	//��ֵ(���ڵ���ϵͳ��)
	float Lerp(float a, float b, float t);

	//����������ʽ�ĵƹ�ĺ���
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

	//��ʼ�����ʵĺ���
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	

	//������һ���ļ������ļ�Ŀ¼��
	bool GetFileDir(const  char *filepath);


	///////����///////////////////////////////////////////////////////////////////

	// ��ɫ
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	const D3DXCOLOR BEACH_SAND( D3DCOLOR_XRGB(255, 249, 157) );
	const D3DXCOLOR DESERT_SAND( D3DCOLOR_XRGB(250, 205, 135) );
	
	const D3DXCOLOR LIGHTGREEN( D3DCOLOR_XRGB( 60, 184, 120) );
	const D3DXCOLOR  PUREGREEN( D3DCOLOR_XRGB(  0, 166,  81) );
	const D3DXCOLOR  DARKGREEN( D3DCOLOR_XRGB(  0, 114,  54) );
	
	const D3DXCOLOR LIGHT_YELLOW_GREEN( D3DCOLOR_XRGB(124, 197, 118) );
	const D3DXCOLOR  PURE_YELLOW_GREEN( D3DCOLOR_XRGB( 57, 181,  74) );
	const D3DXCOLOR  DARK_YELLOW_GREEN( D3DCOLOR_XRGB( 25, 123,  48) );
	
	const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
	const D3DXCOLOR DARKBROWN( D3DCOLOR_XRGB(115, 100,  87));

	//����
	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);

    //���޴�
	const float INFINITY = FLT_MAX;

	//����С����������������
	//const float EPSILON  = 0.001f;
	
	
	//////�ṹ////////////////////////////////////////////////////////////////////

	//�߽��
	struct BoundingBox
	{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
	};

	//�߽���
	struct BoundingSphere
	{
		BoundingSphere();

		D3DXVECTOR3 _center;
		float       _radius;
	};	

	
	//�����ʽ
	struct Vertex
	{
		Vertex(){}
		Vertex(float x, float y, float z, 
			float nx, float ny, float nz,
			float u, float v)
		{
			_x  = x;  _y  = y;  _z  = z;
			_nx = nx; _ny = ny; _nz = nz;
			_u  = u;  _v  = v;
		}
		float _x, _y, _z;
		float _nx, _ny, _nz;
		float _u, _v;

		static const DWORD FVF;
	};



}

#endif // __d3dBaseH__