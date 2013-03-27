/*
 �ļ�����������Ϸ�ļ������������������������Ϸ�߼�
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

extern std::vector<CTerrain*>       g_pTerrain;//����

// ȫ�ֱ���

bool g_bFullScreen = false;                                 //�Ƿ�ȫ��
int g_Width  = 800;                                         //��Ļ��
int g_Height = 600;                                         //��Ļ��
char g_MapPicName[MAX_FILENAME_LEN];                        //��ǰʾ��ͼ��
std::string  g_RoomFile("courtyard.wld");                   //����һ�ŷ����ͼ���ı��ļ�
std::string  g_TerrainFile("courtyard\\hby.raw");           //�������ε�ͼ���ļ�
std::string  g_BackMusicFile("Resource\\firework.wav");     //�����������ֵ������ļ�
std::string  g_FireWorkBmp("Resource\\flare.bmp");        //�̻����ӵ�ͼ
std::string  g_FireGunDds("Resource\\flare_alpha.dds");   //�ӵ���ͼ
std::map<string,string> g_mapfilenames;                  //��ͼ���ƺͶ�Ӧ�ļ���
////////////////�ؼ����//////////////////////////////////////////////////////////
HWND g_RdFullScreen;
HWND g_RdNoFullScreen;
HWND g_CmboxFenBianLv;
HWND g_LbMapNames;
HWND g_PcMaps;
HWND g_BtEnter;
HWND g_BtExit;

//////////////////////////////////////////////////////////////////////////
IDirect3DDevice9* g_Device = NULL;                            //�豸����ӿ�


CCourtyard* g_pcy = NULL;                                   //��ʾһ������

IDXFont* g_pDxFont = NULL;                                   //D3D���ʶ���
IDXFont* g_pDxFont1 = NULL; 

CPSystem* g_pFirework = NULL;

CPSystem* g_Gun = NULL;                                     //�Զ������̻�

//CTerrain *g_pTerrain = NULL;

std::vector<C3DSounder*> g_p3DExpSounds;                      //��ը���������
CSounder* g_pbackSound = NULL;

std::list<CFirework*> g_FireWorkList;                          //���û��Լ�������̻�



D3DXVECTOR3 g_pos(0,1,0);                                     //��ҵĳ�ʼλ��
CViewer TheViewer(CCamera::LANDOBJECT,g_pos);                 //�ۿ��ߣ����




// ��ʼ��������Դ
bool Setup(HINSTANCE hInstance,HWND hwnd)
{
	
	
	srand((unsigned int)time(0));


	//��ʼ������
	CSoundListener::Create(hwnd,DSBCAPS_CTRL3D);
	
	g_pbackSound = new CSounder(const_cast<char*>(g_BackMusicFile.c_str()));
	
	if(g_pbackSound == NULL)
		MessageBox(hwnd,"������������ʧ�ܣ�","����",MB_OK);

	if(g_pbackSound!=NULL)
		g_pbackSound->Play(true);

	//���ر�ը��
	char soundfilename[9];
	for(int i = 1; i<4; i++)
	{
		sprintf(soundfilename,"Resource\\exp%d.wav",i);
		C3DSounder* pSound3d = new C3DSounder(soundfilename);
		pSound3d->SetPosition(0.0f, 80.0f, 100.0f);
		pSound3d->SetDistance(0,5);
		g_p3DExpSounds.push_back(pSound3d);
	}

	//��ʼ��DINPUT����������Ӧ�Ľ�����
	CInputManager::Create(hInstance,hwnd,false,true,true,true);
	Input()->GetKeyboard()->SetReceiver(&TheViewer);
	Input()->GetMouse()->SetReceiver(&TheViewer);
	Input()->GetJoyStick()->SetReceiver(&TheViewer);
	
	ShowCursor(false);

	
	//�����̶����̻�
	D3DXVECTOR3 origin(0.0f, 80.0f, 100.0f);          //�̻𱬷���
	g_pFirework = new d3d::CFirework(&origin, 6000);   //���Ӹ���
	g_pFirework->init(g_Device, const_cast<char*>(g_FireWorkBmp.c_str()));           //�������㻺��������

	//�����̻���ǹ
	g_Gun = new d3d::CParticleFireworkGun( &TheViewer );
	g_Gun->init(g_Device, const_cast<char*>(g_FireGunDds.c_str()));


	//����ͥԺ�����䣩
	cFile file;
	file.Open(g_RoomFile.c_str());
	g_pcy = new CCourtyard(file);


	//����3D��mesh ����
	g_pDxFont = new CDXTEXFont(g_Device);
	g_pDxFont1 = new CDXMESHFont(g_Device);


	//��������
/*	D3DXVECTOR3 p(-20,-5,-12);                            //�������Ͻǵĵ�
	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);         //����ƽ�й�
	g_pTerrain = new CTerrain(g_Device, g_TerrainFile.c_str(),p, 8, 8, 1, 0.1f);
	g_pTerrain->genTexture(&lightDirection);              ////������������ÿ��λ�õĸ߶�����������ɫ��������ɫ��
	*/

	
	//����ͶӰ����
	D3DXMATRIX proj;                                       //ͶӰ����
	D3DXMatrixPerspectiveFovLH(
			&proj,                             
			D3DX_PI / 4.0f,                                 // 45  fovY
			(float)g_Width / (float)g_Height,                //Aspect
			1.0f,                                            //zn
			5000.0f);                                        //zf

	g_Device->SetTransform(D3DTS_PROJECTION, &proj);

	//���ò���������������
	TheViewer.SetMouseSensitivity(0.3)	;
	TheViewer.SetJSSensitivity(0.004);

	d3dbase::DrawBasicScene(g_pcy,g_Device, 1.0f);  //�ػ��������

	

	
	
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

//������ʾ
bool Display(float timeDelta)
{
	if( g_Device )
	{

		// �ر�culling���������ܿ���3���͵�������
		g_Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		
		// ��ZBUFFER
		//Device->SetRenderState( D3DRS_ZENABLE, TRUE );
		
		//ʹ�ö�����ɫ��Ⱦ�������������
		g_Device->SetRenderState( D3DRS_LIGHTING, FALSE );
	
		TheViewer.SetTimeDelta(timeDelta);   //����ˢ�¼��ʱ��

		Input()->UpdateDevices();            //��������DINPUT�¼�

		//����3D��Ч
		D3DXVECTOR3 pos,up,look;

		TheViewer.getPosition(&pos);           //��õ�ǰλ��

		TheViewer.getLook(&look);
		TheViewer.getUp(&up);

		Sound()->SetPosition(pos);            //��ΪListener,����λ��
		Sound()->SetOrientation(look,up);     //���ó���

		


	   /////////////////�߶ȵ���/////////////////////////////////////////////////////////
	   
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
			//����λ�û�ø߶�
			static float height = 0.0f;
			pos.y = pos.y-height; //�õ��ϴεĸ߶ȣ�������סshiftʱ�ı仯��
			height= g_pTerrain[i]->getHeight( pos.x, pos.z );
			
			//���ݸ߶ȵ�����ҵ�λ��
			pos.y = pos.y+height; // 
			TheViewer.setPosition(&pos);
			if(interrain == false)
				interrain = true;
		}
		else
		{
			
			if(interrain == true)                //����մӵ����˳���������ȡλ��
			{
				
				TheViewer.getPosition(&pos);
				pos.y = g_pos.y;             //����ӱ�Ե���µĻ�����߶�Ӧ��Ϊ����߶�
				interrain = false;
			}
			TheViewer.setPosition(&pos);
			
		}
		
		
		
		//////////////////////////////////////////////////////////////////////////
		


		//�����ӽǱ任����
		D3DXMATRIX V;
		TheViewer.getViewMatrix(&V); //CCameraͨ������Ӱ�쳡���Ļ��ƻ!!!
		g_Device->SetTransform(D3DTS_VIEW, &V);




		//////////���������̻�////////////////////////////////////////////////////////////////
		
		g_pFirework->update(timeDelta);   //�ı��̻�ÿ�����ӵ�״̬

		std::list<CFirework*>::iterator iter1,iter2;

		bool ballalive = false;
		while(!ballalive)//ȥ�����в����ڵ��̻�ȼ�����ˣ�
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
		


		/////////�����ķ�����̻�/////////////////////////////////////////////////////////////////
		
		std::list<Attribute> originlist;
		originlist = g_Gun->Getupdate(timeDelta);

		std::list<Attribute>::iterator iter;
		for(iter = originlist.begin();iter!=originlist.end();iter++)
		{
			CFirework* exp;
			D3DXVECTOR3 origin = iter->m_position; //�̻𱬷���
			exp = new d3d::CFirework(&origin, 6000); //���Ӹ���
			exp->init(g_Device, const_cast<char*>(g_FireWorkBmp.c_str())); //�������㻺��������
			g_FireWorkList.push_back(exp);

			//������������
			static int i = 0;
			//g_p3DExpSounds[i]->Stop();
			i = (i+1)%3;
			g_p3DExpSounds[i]->Play();
		}

        //////////////////////////////////////////////////////////////////////////


		//�̶�����̻������
		if( g_pFirework->isDead() ) //�Ƿ��������Ӷ��Ѿ�����
		{
			g_pFirework->reset();  //ȫ�����óɳ�ʼ״̬

			static int i = 0;

		    g_p3DExpSounds[i]->Play();
			
			i = (i+1)%3;
				
		}



		
		//  ��ʼ���Ƴ���
		g_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

		g_Device->BeginScene();
        //////////////////////////////////////////////////////////////////////////
        
	
		
		D3DXMATRIX I;
		D3DXMatrixIdentity(&I); //������λ����

	    d3dbase::DrawBasicScene(g_pcy,g_Device, 1.0f);  //�ػ��������

		g_Device->SetTransform(D3DTS_WORLD, &I);
	

		//g_pTerrain->draw(&I,false);

		g_Gun->render();         // �����̻�

		g_pFirework->render();  //���������̻𶥵�
		for(iter1 = g_FireWorkList.begin();iter1!=g_FireWorkList.end();iter1++)
		{
			(*iter1)->render();
		}
		

		//��󻭵�����ǰ��
		RECT rect = {10,10,10,100},rect1 = {0,6,10,0};

        g_pDxFont->DrawFPS(rect,0xffff0000,timeDelta);   //����֡��
		g_pDxFont1->DrawTexts(rect1,0xffffffff,"Welcome to 3D world!");


		//////////////////////////////////////////////////////////////////////////
		
		g_Device->EndScene();
		
		g_Device->Present(0, 0, 0, 0);
		
	}
	return true;
}






///////////////////////�Ի������///////////////////////////////////////////////////

//����ֱ���
void AddFenBianlv(char* fenbianlv)
{
	SendMessage( g_CmboxFenBianLv, CB_ADDSTRING, 0, (long)fenbianlv);
}


//�����ͼ��
void AddMapName(char* mapname)
{
	SendMessage( g_LbMapNames, LB_ADDSTRING, 0, (long)mapname);
}

//�ɵ�ͼ���õ���ͼ��ͼ��
void GetMapPicName(char* mapname)
{
	//�õ���ǰ�����ļ���
	g_RoomFile = mapname;
	int i = 0;
	for(i = 0; i<strlen(mapname); i++)
	{
		if(mapname[i] == '.')
			break;
	}

	mapname[i] = '\0';
	
	char *slash = "\\";  //ע�⣬����Ҫ��˫б��
    char *postfix = ".bmp";
	
	// �õ���ǰ��ͼ�ļ���
	strcpy(g_MapPicName,mapname);
	strcat(g_MapPicName,slash);
	strcat(g_MapPicName,mapname);
	strcat(g_MapPicName,postfix);

	
}

//��÷ֱ���
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

		g_mapfilenames["���������"] =  "courtyard.wld";
		g_mapfilenames["а��ĵ���"] =  "world.wld";
		AddMapName("���������");
		AddMapName("а��ĵ���");
		SendMessage(g_LbMapNames, LB_SETCURSEL, 0, 0);
		
		CheckRadioButton(hDlg,IDC_RD_FULLSCREEN,IDC_RD_NOFULLSCREEN,IDC_RD_NOFULLSCREEN);

		hBitmap	=  (HBITMAP)::LoadImage(NULL, "courtyard\\courtyard.bmp",IMAGE_BITMAP,SHOWPC_WIDTH,SHOWPCHEIGHT,LR_LOADFROMFILE);
		SendMessage(g_PcMaps, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap); 
	
		return TRUE;
	
		
		
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_ENTER:
			//��÷ֱ���
			index = SendMessage( g_CmboxFenBianLv, CB_GETCURSEL, 0, 0);
			SendMessage( g_CmboxFenBianLv, CB_GETLBTEXT, index, (long)fenbianlv);
			GetFenBianLv(fenbianlv);

			//��ñ�ʾ������ļ���
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
		g_Width, g_Height, !g_bFullScreen, D3DDEVTYPE_HAL, &g_Device))  //��ʼ��D3D
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
	//
	if(!Setup(hinstance,hwnd))  //��ʼ������ϵͳ,�������㻺��������,������������,����ͶӰ����
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

















