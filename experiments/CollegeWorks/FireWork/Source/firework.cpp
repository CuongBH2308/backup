/*
 文件描述：主游戏文件，程序从这里启动，负责游戏逻辑
 */
#include "d3dBase.h"
#include "PSystem.h"
#include "Camera.h"
#include <cstdlib>
#include <ctime>
#include "Sounder.h"
#include "3DSounder.h"
#include "Sounders.h"
#include "Viewer.h"
#include "InputManager.h"
#include "Courtyard.h"
#include "DXGDIFont.h"
#include "DXTEXFont.h"
#include "DXMESHFont.h"
#include "terrain.h"

#include "resource.h"
using namespace d3d;
using d3dbase::CCourtyard;
using namespace DXSound;

const int MAX_FBL_LEN = 10;
const int MAX_FILENAME_LEN = 30;
const int SHOWPCHEIGHT = 160;
const int SHOWPC_WIDTH = 160;

extern std::vector<CTerrain*>       g_pTerrain;//地形

// 全局变量

bool g_bFullScreen = false;                                 //是否全屏
int g_Width  = 800;                                         //屏幕宽
int g_Height = 600;                                         //屏幕高
char g_MapPicName[MAX_FILENAME_LEN];                        //当前示例图名
std::string  g_RoomFile("courtyard.wld");                   //描述一张房间地图的文本文件
std::string  g_TerrainFile("courtyard\\hby.raw");           //描述地形的图象文件
std::string  g_BackMusicFile("Resource\\firework.wav");     //描述背景音乐的声音文件
std::string  g_FireWorkBmp("Resource\\flare.bmp");        //烟火粒子的图
std::string  g_FireGunDds("Resource\\flare_alpha.dds");   //子弹的图
std::map<string,string> g_mapfilenames;                  //地图名称和对应文件名
////////////////控件句柄//////////////////////////////////////////////////////////
HWND g_RdFullScreen;
HWND g_RdNoFullScreen;
HWND g_CmboxFenBianLv;
HWND g_LbMapNames;
HWND g_PcMaps;
HWND g_BtEnter;
HWND g_BtExit;

//////////////////////////////////////////////////////////////////////////
IDirect3DDevice9* g_Device = NULL;                            //设备对象接口


CCourtyard* g_pcy = NULL;                                   //表示一个房间

IDXFont* g_pDxFont = NULL;                                   //D3D画笔对象
IDXFont* g_pDxFont1 = NULL; 

CPSystem* g_pFirework = NULL;

CPSystem* g_Gun = NULL;                                     //自动发射烟火

//CTerrain *g_pTerrain = NULL;

std::vector<C3DSounder*> g_p3DExpSounds;                      //爆炸声（多个）
CSounder* g_pbackSound = NULL;

std::list<CFirework*> g_FireWorkList;                          //由用户自己发射的烟火



D3DXVECTOR3 g_pos(0,1,0);                                     //玩家的初始位置
CViewer TheViewer(CCamera::LANDOBJECT,g_pos);                 //观看者：玩家




// 初始化所有资源
bool Setup(HINSTANCE hInstance,HWND hwnd)
{
	
	
	srand((unsigned int)time(0));


	//初始化声音
	CSoundListener::Create(hwnd,DSBCAPS_CTRL3D);
	
	g_pbackSound = new CSounder(const_cast<char*>(g_BackMusicFile.c_str()));
	
	if(g_pbackSound == NULL)
		MessageBox(hwnd,"创建背景音乐失败！","错误",MB_OK);

	if(g_pbackSound!=NULL)
		g_pbackSound->Play(true);

	//加载爆炸声
	char soundfilename[9];
	for(int i = 1; i<4; i++)
	{
		sprintf(soundfilename,"Resource\\exp%d.wav",i);
		C3DSounder* pSound3d = new C3DSounder(soundfilename);
		pSound3d->SetPosition(0.0f, 80.0f, 100.0f);
		pSound3d->SetDistance(0,5);
		g_p3DExpSounds.push_back(pSound3d);
	}

	//初始化DINPUT，并设置相应的接收者
	CInputManager::Create(hInstance,hwnd,false,true,true,true);
	Input()->GetKeyboard()->SetReceiver(&TheViewer);
	Input()->GetMouse()->SetReceiver(&TheViewer);
	Input()->GetJoyStick()->SetReceiver(&TheViewer);
	
	ShowCursor(false);

	
	//创建固定点烟火
	D3DXVECTOR3 origin(0.0f, 80.0f, 100.0f);          //烟火爆发点
	g_pFirework = new d3d::CFirework(&origin, 6000);   //粒子个数
	g_pFirework->init(g_Device, const_cast<char*>(g_FireWorkBmp.c_str()));           //创建顶点缓冲与纹理

	//创建烟火发射枪
	g_Gun = new d3d::CParticleFireworkGun( &TheViewer );
	g_Gun->init(g_Device, const_cast<char*>(g_FireGunDds.c_str()));


	//创建庭院（房间）
	cFile file;
	file.Open(g_RoomFile.c_str());
	g_pcy = new CCourtyard(file);


	//创建3D　mesh 画笔
	g_pDxFont = new CDXTEXFont(g_Device);
	g_pDxFont1 = new CDXMESHFont(g_Device);


	//创建地形
/*	D3DXVECTOR3 p(-20,-5,-12);                            //地形左上角的点
	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);         //创建平行光
	g_pTerrain = new CTerrain(g_Device, g_TerrainFile.c_str(),p, 8, 8, 1, 0.1f);
	g_pTerrain->genTexture(&lightDirection);              ////创建纹理并根据每个位置的高度来设置其颜色（纹理颜色）
	*/

	
	//设置投影矩阵
	D3DXMATRIX proj;                                       //投影矩阵
	D3DXMatrixPerspectiveFovLH(
			&proj,                             
			D3DX_PI / 4.0f,                                 // 45  fovY
			(float)g_Width / (float)g_Height,                //Aspect
			1.0f,                                            //zn
			5000.0f);                                        //zf

	g_Device->SetTransform(D3DTS_PROJECTION, &proj);

	//设置操作器件的灵敏度
	TheViewer.SetMouseSensitivity(0.3)	;
	TheViewer.SetJSSensitivity(0.004);

	d3dbase::DrawBasicScene(g_pcy,g_Device, 1.0f);  //重绘基本场景

	

	
	
	return true;
}

void Cleanup()
{


	int soundnum = g_p3DExpSounds.size();
	for(int i = 0; i<soundnum; i++)
	{
		d3dbase::Delete<C3DSounder*>( g_p3DExpSounds[i] );
	}

	d3dbase::Delete<d3d::CPSystem*>( g_pFirework );

	d3dbase::Delete<d3d::CPSystem*>( g_Gun );

	d3dbase::Delete<d3dbase::CCourtyard*>( g_pcy );

	d3dbase::DrawBasicScene(NULL,g_Device,1.0);

//	d3dbase::Delete<d3d::CTerrain*>( g_pTerrain );


}

//场景显示
bool Display(float timeDelta)
{
	if( g_Device )
	{

		// 关闭culling，让我们能看到3角型的正反面
		g_Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		
		// 打开ZBUFFER
		//Device->SetRenderState( D3DRS_ZENABLE, TRUE );
		
		//使用顶点颜色渲染，必须禁掉光照
		g_Device->SetRenderState( D3DRS_LIGHTING, FALSE );
	
		TheViewer.SetTimeDelta(timeDelta);   //设置刷新间隔时间

		Input()->UpdateDevices();            //处理所有DINPUT事件

		//产生3D音效
		D3DXVECTOR3 pos,up,look;

		TheViewer.getPosition(&pos);           //获得当前位置

		TheViewer.getLook(&look);
		TheViewer.getUp(&up);

		Sound()->SetPosition(pos);            //作为Listener,设置位置
		Sound()->SetOrientation(look,up);     //设置朝向

		


	   /////////////////高度调整/////////////////////////////////////////////////////////
	   
		int i;
		bool flag = false;
		for(i = 0; i<g_pTerrain.size(); i++)
		{
			if(g_pTerrain[i]->IsInside(pos))
			{
				flag = true;
				break;
			}
		}
		
		static bool interrain = false;
		if(flag == true)
		{
			//根据位置获得高度
			static float height = 0.0f;
			pos.y = pos.y-height; //得到上次的高度（包括按住shift时的变化）
			height= g_pTerrain[i]->getHeight( pos.x, pos.z );
			
			//根据高度调整玩家的位置
			pos.y = pos.y+height; // 
			TheViewer.setPosition(&pos);
			if(interrain == false)
				interrain = true;
		}
		else
		{
			
			if(interrain == true)                //如果刚从地形退出来，重新取位置
			{
				
				TheViewer.getPosition(&pos);
				pos.y = g_pos.y;             //如果从边缘跳下的话，其高度应该为地面高度
				interrain = false;
			}
			TheViewer.setPosition(&pos);
			
		}
		
		
		
		//////////////////////////////////////////////////////////////////////////
		


		//设置视角变换矩阵
		D3DXMATRIX V;
		TheViewer.getViewMatrix(&V); //CCamera通过此来影响场景的绘制活动!!!
		g_Device->SetTransform(D3DTS_VIEW, &V);




		//////////更新所有烟火////////////////////////////////////////////////////////////////
		
		g_pFirework->update(timeDelta);   //改变烟火每个粒子的状态

		std::list<CFirework*>::iterator iter1,iter2;

		bool ballalive = false;
		while(!ballalive)//去掉所有不存在的烟火（燃烧完了）
		{
			if(g_FireWorkList.empty()) ballalive = true;
			for(iter1 = g_FireWorkList.begin();iter1!=g_FireWorkList.end();iter1++)
			{
				if((*iter1)->isDead())
				{
					
					ballalive = false;
					delete (*iter1);
					g_FireWorkList.erase(iter1);
					break;
					
				}

				ballalive = true;
			}
		}
		

		for(iter1 = g_FireWorkList.begin();iter1!=g_FireWorkList.end();iter1++)
		{
		
			    (*iter1)->update(timeDelta);
		}
		//////////////////////////////////////////////////////////////////////////
		


		/////////新增的发射的烟火/////////////////////////////////////////////////////////////////
		
		std::list<Attribute> originlist;
		originlist = g_Gun->Getupdate(timeDelta);

		std::list<Attribute>::iterator iter;
		for(iter = originlist.begin();iter!=originlist.end();iter++)
		{
			CFirework* exp;
			D3DXVECTOR3 origin = iter->m_position; //烟火爆发点
			exp = new d3d::CFirework(&origin, 6000); //粒子个数
			exp->init(g_Device, const_cast<char*>(g_FireWorkBmp.c_str())); //创建顶点缓冲与纹理
			g_FireWorkList.push_back(exp);

			//轮流播放声音
			static int i = 0;
			//g_p3DExpSounds[i]->Stop();
			i = (i+1)%3;
			g_p3DExpSounds[i]->Play();
		}

        //////////////////////////////////////////////////////////////////////////


		//固定点的烟火的重生
		if( g_pFirework->isDead() ) //是否所有粒子都已经死了
		{
			g_pFirework->reset();  //全部设置成初始状态

			static int i = 0;

		    g_p3DExpSounds[i]->Play();
			
			i = (i+1)%3;
				
		}



		
		//  开始绘制场景
		g_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

		g_Device->BeginScene();
        //////////////////////////////////////////////////////////////////////////
        
	
		
		D3DXMATRIX I;
		D3DXMatrixIdentity(&I); //产生单位矩阵

	    d3dbase::DrawBasicScene(g_pcy,g_Device, 1.0f);  //重绘基本场景

		g_Device->SetTransform(D3DTS_WORLD, &I);
	

		//g_pTerrain->draw(&I,false);

		g_Gun->render();         // 绘制烟火弹

		g_pFirework->render();  //逐批绘制烟火顶点
		for(iter1 = g_FireWorkList.begin();iter1!=g_FireWorkList.end();iter1++)
		{
			(*iter1)->render();
		}
		

		//最后画的在最前面
		RECT rect = {10,10,10,100},rect1 = {0,6,10,0};

        g_pDxFont->DrawFPS(rect,0xffff0000,timeDelta);   //画出帧速
		g_pDxFont1->DrawTexts(rect1,0xffffffff,"Welcome to 3D world!");


		//////////////////////////////////////////////////////////////////////////
		
		g_Device->EndScene();
		
		g_Device->Present(0, 0, 0, 0);
		
	}
	return true;
}






///////////////////////对话框操作///////////////////////////////////////////////////

//加入分辩率
void AddFenBianlv(char* fenbianlv)
{
	SendMessage( g_CmboxFenBianLv, CB_ADDSTRING, 0, (long)fenbianlv);
}


//加入地图名
void AddMapName(char* mapname)
{
	SendMessage( g_LbMapNames, LB_ADDSTRING, 0, (long)mapname);
}

//由地图名得到地图例图名
void GetMapPicName(char* mapname)
{
	//得到当前世界文件名
	g_RoomFile = mapname;
	int i = 0;
	for(i = 0; i<strlen(mapname); i++)
	{
		if(mapname[i] == '.')
			break;
	}

	mapname[i] = '\0';
	
	char *slash = "\\";  //注意，这里要用双斜杠
    char *postfix = ".bmp";
	
	// 得到当前例图文件名
	strcpy(g_MapPicName,mapname);
	strcat(g_MapPicName,slash);
	strcat(g_MapPicName,mapname);
	strcat(g_MapPicName,postfix);

	
}

//获得分辩率
bool GetFenBianLv(char * fenbianlv)
{
	char* pwidth = NULL, *pheight = NULL;
	int i;
	for(i = 0; i <strlen(fenbianlv); i++)
	{
		if(fenbianlv[i] == 'X')
		{
			fenbianlv[i] = '\0';
			pwidth = fenbianlv;
			pheight = fenbianlv + i + 1;
		}
			
	}
	if(pwidth!=NULL&&pheight!=NULL)
	{
		g_Width = atoi(pwidth);
		g_Height = atoi(pheight);
		return true;
	}

	return false;
}

//
LRESULT CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int index = 0;
	char fenbianlv[MAX_FBL_LEN];
	char filename[MAX_FILENAME_LEN];
	HBITMAP hBitmap;

	switch (message)
	{
	case WM_INITDIALOG:
	
		g_RdFullScreen = GetDlgItem( hDlg, IDC_RD_FULLSCREEN );
		g_RdNoFullScreen = GetDlgItem( hDlg, IDC_RD_NOFULLSCREEN  );
		g_CmboxFenBianLv = GetDlgItem( hDlg, IDC_COMBO_FENBIANLV  );
		g_PcMaps = GetDlgItem( hDlg, IDC_MAPS  );
		g_LbMapNames = GetDlgItem( hDlg, IDC_LIST_MAPNAMES );
		

		AddFenBianlv("1024X768");
		AddFenBianlv("800X600");
		AddFenBianlv("640X480");
		SendMessage( g_CmboxFenBianLv, CB_SETCURSEL, 0, 0);

		g_mapfilenames["美丽的天空"] =  "courtyard.wld";
		g_mapfilenames["邪恶的地狱"] =  "world.wld";
		AddMapName("美丽的天空");
		AddMapName("邪恶的地狱");
		SendMessage(g_LbMapNames, LB_SETCURSEL, 0, 0);
		
		CheckRadioButton(hDlg,IDC_RD_FULLSCREEN,IDC_RD_NOFULLSCREEN,IDC_RD_NOFULLSCREEN);

		hBitmap	=  (HBITMAP)::LoadImage(NULL, "courtyard\\courtyard.bmp",IMAGE_BITMAP,SHOWPC_WIDTH,SHOWPCHEIGHT,LR_LOADFROMFILE);
		SendMessage(g_PcMaps, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap); 
	
		return TRUE;
	
		
		
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_ENTER:
			//获得分辩率
			index = SendMessage( g_CmboxFenBianLv, CB_GETCURSEL, 0, 0);
			SendMessage( g_CmboxFenBianLv, CB_GETLBTEXT, index, (long)fenbianlv);
			GetFenBianLv(fenbianlv);

			//获得表示世界的文件名
			index = SendMessage( g_LbMapNames, LB_GETCURSEL, 0, 0);
			SendMessage( g_LbMapNames, LB_GETTEXT, index, (long)filename);

			EndDialog(hDlg, LOWORD(wParam));
			//return TRUE;
			break;

		case IDC_BUTTON_EXIT:		
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		
		case IDC_RD_FULLSCREEN:
			g_bFullScreen = true;
			break;

		case IDC_RD_NOFULLSCREEN:
			g_bFullScreen = false;
			break;
			
		case IDC_LIST_MAPNAMES:
//	case LBN_SELCHANGE:
			if(g_LbMapNames == (HWND) lParam && LBN_SELCHANGE == HIWORD(wParam) )
			{
				index = SendMessage( g_LbMapNames, LB_GETCURSEL, 0, 0);
				if(index == LB_ERR) 
					break;
				SendMessage( g_LbMapNames, LB_GETTEXT, index, (long)filename);
				strcpy(filename,g_mapfilenames[filename].c_str());
                GetMapPicName(filename);
				hBitmap	=  (HBITMAP)::LoadImage(NULL, g_MapPicName,IMAGE_BITMAP,SHOWPC_WIDTH,SHOWPCHEIGHT,LR_LOADFROMFILE);
				SendMessage(g_PcMaps, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap); 
				break;
			}
			break;
			
			
		default:
			break;
		
		}
		default:
			break;
	}


    return FALSE;
}
//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{

	

	if(IDC_BUTTON_EXIT == DialogBox(hinstance, (LPCTSTR)IDD_DIALOG_SETUP, NULL, (DLGPROC)DialogProc))
		return 0;

	HWND hwnd;
	if(!d3dbase::CreateD3DWindow(hinstance,hwnd,g_Width,g_Height))
	{
		::MessageBox(0, "CreateD3DWindow - FAILED", 0, 0);
		return 0;
	}
	
	if(!d3dbase::InitD3D(hwnd,
		g_Width, g_Height, !g_bFullScreen, D3DDEVTYPE_HAL, &g_Device))  //初始化D3D
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
	//
	if(!Setup(hinstance,hwnd))  //初始化粒子系统,创建顶点缓冲与纹理,创建基本场景,设置投影矩阵
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}
		


	

	d3dbase::EnterMsgLoop( Display );

	Cleanup();
	
	g_Device->Release();
	

	return 0;
}



//
// WndProc
//
LRESULT CALLBACK d3dbase::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

















