#include "d3dBase.h"
#include "Sounder.h"
#include "resource.h"
#include "math3D\mathD3D.h"
#include "terrain.h"

using d3d::CTerrain;
std::vector<CTerrain*>       g_pTerrain;//地形

extern const int MAX_FILENAME_LEN = 30;
char g_FileDir[MAX_FILENAME_LEN];
bool g_useTextures = true;
//FVF
const DWORD d3dbase::Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

//创建主窗口
bool d3dbase::CreateD3DWindow(HINSTANCE hInstance,HWND& hwnd,int width, int height)
{
	//设置窗口类
	WNDCLASS wc;
	
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)d3dbase::WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "D3D9Window";
	
	//注册窗口类
	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
	
	//创建窗口
	hwnd = ::CreateWindow("D3D9Window", "游戏窗口", 
		WS_EX_TOPMOST,
		0, 0, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/); 
	
	if( !hwnd )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}
	
	
	
	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

}

//初始化D3D窗口
bool d3dbase::InitD3D(
	HWND  hwnd,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{
	
	HRESULT hr = 0;

	// Step 1: 创建IDirect3D9对象
	IDirect3D9* d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2:检查并设置硬件顶点处理功能.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3: 填充D3DPRESENT_PARAMETERS结构，设置D3D窗口初始状态
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = width;
	d3dpp.BackBufferHeight           = height;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hwnd;
	d3dpp.Windowed                   = windowed;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 4:创建D3D设备
	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		hwnd,               // window associated with device
		vp,                 // vertex processing
	    &d3dpp,             // present parameters
	    device);            // return created device

	if( FAILED(hr) )
	{
		// 使用16位深度缓存再重新创建一次
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		if( FAILED(hr) )
		{
			d3d9->Release(); // 释放d3d9对象　
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // 释放d3d9对象
	
	return true;
}

int d3dbase::EnterMsgLoop( bool (*ptr_display)(float timeDelta) ) //函数指针显示场景
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static float lastTime = (float)timeGetTime(); 

	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
        {	
			//没有消息时绘制场景
			float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;

			ptr_display(timeDelta);

			lastTime = currTime;
        }
    }
    return msg.wParam;
}

//平行光
D3DLIGHT9 d3dbase::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

//点光源
D3DLIGHT9 d3dbase::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

//聚光灯
D3DLIGHT9 d3dbase::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.5f;
	light.Phi          = 0.7f;

	return light;
}

//材质
D3DMATERIAL9 d3dbase::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}

d3dbase::BoundingBox::BoundingBox()
{
	// 无穷大、小
	_min.x = d3dbase::INFINITY;
	_min.y = d3dbase::INFINITY;
	_min.z = d3dbase::INFINITY;

	_max.x = -d3dbase::INFINITY;
	_max.y = -d3dbase::INFINITY;
	_max.z = -d3dbase::INFINITY;
}

bool d3dbase::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if( p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z )
	{
		return true;
	}
	else
	{
		return false;
	}
}

d3dbase::BoundingSphere::BoundingSphere()
{
	_radius = 0.0f;
}

//解析出一个文件名的文件目录来
bool d3dbase::GetFileDir(const char *filepath)
{
	char tmpfilepath[MAX_FILENAME_LEN];
	strcpy(tmpfilepath,filepath);
	for(int i = strlen(tmpfilepath); i>=0; i--)
	{
		if(filepath[i] == '\\')//用转义字符
		{
			tmpfilepath[i] = '\0';
			strcpy(g_FileDir,tmpfilepath);
			strcat(g_FileDir,"\\");//在程序中，用\\表示\，转义字符
			return true;
		}
	}

	return false;

}

bool d3dbase::LoadXFileMesh(ID3DXMesh**                     pMesh,
							std::string strFilename,IDirect3DDevice9* Device,
					        std::vector<D3DMATERIAL9>& Mtrls, std::vector<IDirect3DTexture9*>& Textures)

{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer  = 0;//adj info of the mesh
	ID3DXBuffer* mtrlBuffer = 0;//material info of the mesh
	
	
	DWORD        numMtrls   = 0;//此模型中包括的材质、纹理的个数
	
	hr = D3DXLoadMeshFromX( 
		   
		strFilename.c_str(),
		
		D3DXMESH_MANAGED,
		
		Device,
		
		&adjBuffer,
		
		&mtrlBuffer,  //此模型的材质、纹理由它返回
		
		
		0,
		
		&numMtrls,
		
		pMesh);

	//调试语句
	if(D3DERR_INVALIDCALL== hr)
	{
		int j = 0;
	}
	if(E_OUTOFMEMORY == hr)
	{
		int h = 1;
	}
	

	if(FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
		return false;
	}
	
	//
	//由mtrlBuffer得到材质和纹理
	//
	
	if( mtrlBuffer != NULL && numMtrls != 0 )
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer(); //void*　－－＞D3DXMATERIAL*
		for(int i = 0; i < numMtrls; i++)
		{
			//MatD3D加载时没有设置ambient分量，在这里设置为与Diffuse分量相同
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			
			// 存储材质集
			Mtrls.push_back( mtrls[i].MatD3D );
			
			//检查第i个材质是否有相应的纹理图
			if( mtrls[i].pTextureFilename != 0 )
			{
				// 有的话从相应文件加载
				if(GetFileDir(const_cast<char*>(strFilename.c_str())))
					strcat(g_FileDir,mtrls[i].pTextureFilename);
				else
					strcpy(g_FileDir,mtrls[i].pTextureFilename);

				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					Device,
					g_FileDir,
					&tex);
				
				// 并存储
				Textures.push_back( tex );
			}
			else
			{
				// 否则就为　NULL
				Textures.push_back( 0 );
			}
		}
	}
	d3dbase::Release<ID3DXBuffer*>(mtrlBuffer); //  已经从mtrlBuffer解析完纹理与材质，释放mtrlBuffer
	
	//根据邻接矩阵优化模型
	hr = (*pMesh)->OptimizeInplace(		
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT  |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0);
	
	d3dbase::Release<ID3DXBuffer*>(adjBuffer); // 释放adjBuffer
	
	if(FAILED(hr))
	{
		::MessageBox(0, "OptimizeInplace() - FAILED", 0, 0);
		return false;
	}

	return true;
	
	
}

//传入pcy为NULL表示释放资源
bool d3dbase::DrawBasicScene(CCourtyard* pcy,IDirect3DDevice9* device, float scale)	
{
	//定义需要用到的指针、变量
	static std::vector<sLitVertex> v;                                  //每个平面的最多顶点数
	static std::vector<IDirect3DTexture9*>      tex;                //平面的纹理


	static  ID3DXMesh*      pMesh[MaxObject];                        //模型
	static std::vector<D3DMATERIAL9>       Mtrls[MaxTexPerObj];      //组成模型的材质
	static std::vector<IDirect3DTexture9*> Textures[MaxTexPerObj];    //组成模型的纹理


	int i,j;
	static bool bfirst = true;

	static int nPolys = 0;      //平面数
	static int nObjs = 0;        //模型物体数
	static int nTerrain = 0; //地形数
	

	if( pcy == NULL&&bfirst == true)
	{
		return false;
	}

	//当传入参数pcy的值为NULL时，释放资源
	if(pcy == NULL && bfirst == false)
	{
		int i;

		//释放平面纹理
		for(i = 0; i<nPolys; i++)
		{
			Release<IDirect3DTexture9*>(tex[i]);
		}
		//释放模型
		for(i = 0; i<nObjs; i++)
		{
			Release<ID3DXMesh*>(pMesh[i]);
		}
		//释放地形
		for(i = 0; i<nTerrain; i++)
		{
			Delete<CTerrain*>(g_pTerrain[i]);
		}
		return false;
	}
	
	//如果使用纹理，设置混合方式	
	if( g_useTextures )
	{
		device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		device->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	}
	
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);                   //产生单位矩阵
	device->SetTransform(D3DTS_WORLD, &I);    //设置世界坐标,调整作用
	

	nPolys = pcy->m_polyList.size();      //平面数
	nObjs = pcy->m_objList.size();        //模型物体数
	nTerrain = pcy->m_TerrainList.size(); //地形数

	
	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);         //创建平行光，创建地形时使用
	
   	//第一次运行：加载纹理图，模型，创建地形
	if(bfirst)
	{
		
		const char * ch;
		HRESULT hr;

		//若使用纹理，加载纹理图
		if(g_useTextures){
			IDirect3DTexture9* temttex = NULL;
			for( i=0; i<nPolys; i++ )
			{
				hr = D3DXCreateTextureFromFile(  //从文件创建纹理  tex
					device,
					ch = pcy->m_polyList[i].m_texfile.c_str(),
					&temttex);

				tex.push_back(temttex);

				if(FAILED(hr))
				{
					throw cGameError("create texture failed");
				}
				
			}
		}


		//加载模型
		for( i=0; i<nObjs; i++ )
		{
			
			if(LoadXFileMesh(&pMesh[i],pcy->m_objList[i].m_meshfile,device,Mtrls[i],Textures[i]) == false)
			{
				throw cGameError("create mesh failed");

			}

		}
	

		//创建、加载地形
		for( i=0; i<nTerrain; i++ )
		{
			CTerrain *pTer = NULL;
			D3DXVECTOR3 p(pcy->m_TerrainList[i].m_pos.x,pcy->m_TerrainList[i].m_pos.y,pcy->m_TerrainList[i].m_pos.z);
			pTer = new CTerrain(device,pcy->m_TerrainList[i].m_terrainfile,p,
				pcy->m_TerrainList[i].m_numVertsPerRow,pcy->m_TerrainList[i].m_numVertsPerCol,
				pcy->m_TerrainList[i].m_cellSpacing,pcy->m_TerrainList[i].m_heightScale);
			
			pTer->genTexture(&lightDirection);              ////创建纹理并根据每个位置的高度来设置其颜色（纹理颜色）

			g_pTerrain.push_back(pTer);
			
		}

		bfirst = false;
	}

	//设置绘画状态

	//使用镜面反射
	device->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	//自动法向量归一化
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	//开始画图
	//渲染平面
	for( i=0; i<nPolys; i++ )
	{
		
		
		
		if(g_useTextures)
		{
			device->SetTexture( 0, tex[i]);
			device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		}
		
		int nVerts = pcy->m_polyList[i].m_nVerts;

		sLitVertex tempv;
		v.clear();
		for( j=0; j<nVerts; j++ )
		{
			tempv = sLitVertex(
				pcy->m_ptList[ pcy->m_polyList[i].m_vList[j].m_ind ],
				pcy->m_polyList[i].m_vList[j].m_col,
				0,
				pcy->m_polyList[i].m_vList[j].m_u,
				pcy->m_polyList[i].m_vList[j].m_v );

			v.push_back(tempv);
		}
		

		// 指定自定义的FVF
		//device->SetVertexShader( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 );
		device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 );
	
		//以三角扇形的格画出平面
		device->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,//三角扇形
			pcy->m_polyList[i].m_nVerts - 2,//三角形个数
			(void*)&v[0],
			sizeof( sLitVertex ) );// 
		
	}

	//渲染模型
	for(i = 0;i<nObjs; i++)
	{
		D3DXMATRIX World,World1;

		//平移
		point3 p = pcy->m_objList[i].m_pos;
		D3DXMatrixTranslation(&World, p.x,p.y,p.z);

		//旋转
		float angle = pcy->m_objList[i].m_angle;
		D3DXMatrixRotationY(&World1,angle);

		//复合变换
		D3DXMatrixMultiply(&World,&World1,&World);
	
		//设置世界矩阵
		device->SetTransform(D3DTS_WORLD, &World);
	
		for(j = 0; j < Mtrls[i].size(); j++)
		{
			
			
			device->SetMaterial( &Mtrls[i][j] );
			device->SetTexture(0, Textures[i][j]);
			pMesh[i]->DrawSubset(j);
		}
	}


	//渲染地形
	for( i=0; i<nTerrain; i++ )
	{
		g_pTerrain[i]->draw(&I,false);
	
	}
	return true;
}



float d3dbase::GetRandomFloat(float lowBound, float highBound)
{
	if( lowBound >= highBound ) // 不合法输入
		return lowBound;

	// 得到一个[0, 1] 之间的float数
	float f = (rand() % 10000) * 0.0001f; 

	// 　返回 [lowBound, highBound] 之间的float 数
	return (f * (highBound - lowBound)) + lowBound; 
}

void d3dbase::GetRandomVector(
	  D3DXVECTOR3* out,
	  D3DXVECTOR3* min,
	  D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

DWORD d3dbase::FtoDw(float f)
{
	return *((DWORD*)&f);
}


float d3dbase::Lerp(float a, float b, float t)
{
	return a - (a*t) + (b*t);
}





















