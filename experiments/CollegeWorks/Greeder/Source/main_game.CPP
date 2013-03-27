// T3D Game Console, creates a game console application

// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <winuser.h>
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>

//#include "resource.h"

#include <ddraw.h>  // directX includes
#include <dsound.h>
#include <dmksctrl.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmusicf.h>
#include <dinput.h>
#include "T3DLIB1.h" // game library includes
#include "T3DLIB2.h"
#include "T3DLIB3.h"
#include "Snake.h"
#include "resource.h"

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define WINDOW_BPP      16
#define WINDOWED        1
#define MAX_NUM         10


// MACROS /////////////////////////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define INDEXTOCOORX(index)    (index*BODYSIZE+ XBEGIN+BODYSIZE/2)
#define INDEXTOCOORY(index)   (index*BODYSIZE + BODYSIZE/2)

// GLOBALS ////////////////////////////////////////////////
HWND      main_window_handle = NULL; // globally track main window
HINSTANCE main_instance      = NULL; // globally track hinstance

char       g_szClassName[80] = "WINCLASS"; //注册窗口时用的窗口类名

char buffer[80];                     // general printing buffer
bool g_bExclusive;
char *szTitle = "贪吃蛇";


//////////////////////////////////////////////////////////////////////////
CSnake Snake;

void ShowSnake();
char* ShowLastError();
void   phase(int num);
void OutPutInfo(char *filename,char *strinfo);
DWORD WINAPI ThreadShowFood(LPVOID lpStartupParam);
DWORD WINAPI ThreadGetInput(LPVOID lpStartupParam);

bool bRun;
bool EndThread = false;

int dieindex;
int eatindex;
int backindex;

int  digit[MAX_NUM];

typedef struct
{
	
	HANDLE 		    hEvent ;
	Point           food;
//	BOOL   			bContinue ;
}
PARAMS, *PPARAMS ;

PARAMS  Par,Par1;
//char *ch="dfdf";

/*
//*******************************************************************************************
void CreateMainWindow();
void DestroyMainWindow();

  RECT CalculateWindowRect(HWND hWindow, SIZE szDesiredClient);
  
	RECT AdjustMainWindow(bool bExclusive, int nScreenWidth, int nScreenHeight);
	void SwitchMode(bool bExclusive, int nWidth, int nHeight, int nBPP);
	//*******************************************************************************************
*/
// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
							UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context
	char buffer[80];        // used to print strings
	
	RECT rect;
	// what is the message 
	switch(msg)
	{	

	case WM_COMMAND:
            switch( LOWORD(wparam) )
            {
                case ID_LEVEL1:
					Snake.SetLevel(1);
					break;
				case ID_LEVEL2:
					Snake.SetLevel(2);
					break;
				case ID_LEVEL3:
					Snake.SetLevel(3);
					break;
				case ID_LEVEL4:
					Snake.SetLevel(4);
					break;
				case ID_LEVEL5:
					Snake.SetLevel(5);
					break;
				case ID_LEVEL6:
					Snake.SetLevel(6);
					break;
				case ID_LEVEL7:
					Snake.SetLevel(7);
					break;
				case ID_LEVEL8:
					Snake.SetLevel(8);
					break;
				case ID_LEVEL9:
					Snake.SetLevel(9);
					break;
					
				case ID_RESTART:
					if(bRun == false){
						
						Snake.Reset();
						EndThread = false;
						sound_fx[backindex].dsbuffer->Play(0,0,1);
						CreateThread(NULL,0,ThreadShowFood,&Par,0,0);
						bRun = true;
					}
					break;
				case ID_EXIT:
					PostQuitMessage(0);
					break;
					
                    // Prevent potential crashes when the monitor powers down
			}
			break;
			
	case WM_CREATE: 
        {
			// do initialization stuff here
			// return success
			return(0);
		} break;
	case WM_KEYUP:
		if(wparam == VK_F4){
			bRun = false;
			SwitchMode(!g_bExclusive,800,600,16);
			
			//DDraw_Fill_Surface(lpddsback,100);
			//	DDraw_Flip2();
			
			
			
			LoadBitmapFile(lpddsoff[0],0,0,"bg_bmp.bmp");
			
			LoadBitmapFile(lpddsoff[1],0,0,"snake_head.bmp");
			LoadBitmapFile(lpddsoff[1],0,20,"snake_body.bmp");
			LoadBitmapFile(lpddsoff[1],0,40,"snake_tail.bmp");
			
			LoadBitmapFile(lpddsoff[2],0,0,"food1.bmp");
			LoadBitmapFile(lpddsoff[2],0,20,"food2.bmp");
			LoadBitmapFile(lpddsoff[2],0,40,"food3.bmp");
			
            lpddsback->Blt(NULL,lpddsoff[0],NULL,NULL,NULL);
			DDraw_Flip2();
			
			bRun = true;
			
		}
		else if(wparam == VK_SPACE){
			static int num = 0;
			if((++num)%2==1) bRun = false;
			else bRun = true;
		}

		else if(wparam == VK_F1){
			if(bRun == false){
			
			Snake.Reset();
			EndThread = false;
			sound_fx[backindex].dsbuffer->Play(0,0,1);
			CreateThread(NULL,0,ThreadShowFood,&Par,0,0);
			bRun = true;
			}
		}
		
		else if(wparam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		
		break;
		
	case WM_PAINT: 
		{
			// simply validate the window 
			hdc = BeginPaint(hwnd,&ps);	 
			
			// end painting
			EndPaint(hwnd,&ps);
			
			// return success
			return(0);
		} break;
		
	case WM_CLOSE:
		EndThread = true;
		PostQuitMessage(0);
		break;
		
	case WM_DESTROY: 
		{
			
			// kill the application, this sends a WM_QUIT message 
			//PostQuitMessage(0);
			
			// return success
			return(0);
		} break;
		
	default:break;
		
    } // end switch
	
	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));
	
} // end WinProc

///////////////////////////////////////////////////////////

int Game_Main(void *parms = NULL, int num_parms = 0)
{
    // this is the main loop of the game, do all your processing
    // here
    //DDraw_Flip2();
    // for now test if user is hitting ESC and send WM_CLOSE
    if (KEYDOWN(VK_ESCAPE)){
        
        // Screen_Transitions(SCREEN_WHITENESS,NULL,0);
        SendMessage(main_window_handle,WM_CLOSE,0,0);
		  }
	// start the timing clock

	if(Snake.IsDead() == true){
		bRun = false;
		sound_fx[dieindex].dsbuffer->Play(0,0,0);
		sound_fx[backindex].dsbuffer->Stop();
		EndThread = true;
		return 0;
	}
	Start_Clock();
	DInput_Read_Keyboard();
	
	Direction dir = Snake.GetDirection() ;
	if(keyboard_state[DIK_UP] & 0X80)
		dir = UP;
	else if(keyboard_state[DIK_DOWN] & 0X80)
		dir = DOWN;
	else if(keyboard_state[DIK_LEFT] & 0X80)
		dir = LEFT;
	else if(keyboard_state[DIK_RIGHT] & 0X80)
		dir = RIGHT;
	else if(keyboard_state[DIK_SPACE] & 0X80)
		dir = PAUSE;
	
	Snake.SetDirection(dir);
	
	Snake.move(Par.food);

	sound_fx[backindex].buff3D->SetPosition(Par.food.x/10.0,Par.food.y/10.0,0.0f,DS3D_IMMEDIATE);

	Point pCur = Snake.GetHead();
	
	Listener->SetPosition(pCur.x/10.0,pCur.y/10.0,0.0f,DS3D_IMMEDIATE);
	
	ShowSnake();

	//if(threadexit == true){
	//	CreateThread(NULL,0,ThreadProcedure,&Par,0,0);
		
//	}
	
	
	
	
	Wait_Clock(30+(9-Snake.GetLevel())*10);
    return(1);
    
} // end Game_Main

////////////////////////////////////////////////////////////

int Game_Init(void *parms = NULL, int num_parms = 0)
{
	// this is called once after the initial window is created and
	// before the main event loop is entered, do all your initialization
	// here

	phase(12381234);
	DDraw_Init(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_BPP,WINDOWED);
	g_bExclusive = false;
	//DDraw_Init(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_BPP);
	//	g_bExclusive = true;
	
	
	bRun = true;
	
	LoadBitmapFile(lpddsoff[0],160,0,"BACK.bmp");
	LoadBitmapFile(lpddsoff[0],0,0,"left.bmp");
	LoadBitmapFile(lpddsoff[0],160,480,"down.bmp");

	
	LoadBitmapFile(lpddsoff[1],0,0,"snake_head.bmp");
	LoadBitmapFile(lpddsoff[1],0,20,"snake_body.bmp");
	LoadBitmapFile(lpddsoff[1],0,40,"snake_tail.bmp");

	char ch[6];//load digit map   (0,60)点开始的一排13X23
	for (int i = 0;i<10;i++)
	{
          sprintf(ch,"%d.bmp",i);
		  LoadBitmapFile(lpddsoff[1],(i)*13,60,ch);
	}
	
	LoadBitmapFile(lpddsoff[2],0,0,"food1.bmp");
	LoadBitmapFile(lpddsoff[2],0,20,"food2.bmp");
	LoadBitmapFile(lpddsoff[2],0,40,"food3.bmp");

	/*if(lpddclipper)
	lpddclipper->Release();

	RECT  rc = {160,0,800,480};
	lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&rc);
	*/
	//DDraw_Fill_Surface(lpddsback,0);
	
	//	RECT clip_rect = {XBEGIN,WINDOW_WIDTH,YBEGIN,WINDOW_HEIGHT-120};
	//    DDraw_Attach_Clipper(lpddsprimary,1,&clip_rect);
	
	// initialize directinput
	DInput_Init();
	
	// acquire the keyboard 
	DInput_Init_Keyboard();
	
	// initialize directsound and directmusic
	DSound_Init();

	DSound_CreatePriSur(DSBCAPS_CTRL3D);

	dieindex = DSound_Load_WAV("DIE_BEEP.WAV");
	eatindex = DSound_Load_WAV("EAT_BEEP.WAV");
	backindex = DSound_Load_WAV("BG_MIC1.wav",DSBCAPS_CTRLDEFAULT|DSBCAPS_CTRL3D);

	sound_fx[backindex].dsbuffer->Play(0,0,1);
	sound_fx[backindex].dsbuffer->QueryInterface(IID_IDirectSound3DBuffer,(VOID**)&sound_fx[backindex].buff3D);	

	Listener->SetOrientation(0.0,0.0,0.0,0.0,0.0,-1.0,DS3D_IMMEDIATE);

	D3DVALUE pflMaxDistance,pflMinDistance; 
	pflMaxDistance = 100.0f;
	sound_fx[backindex].buff3D->SetMaxDistance(pflMaxDistance,DS3D_IMMEDIATE);








	sound_fx[backindex].buff3D->GetMaxDistance(&pflMaxDistance);

	sound_fx[backindex].buff3D->GetMinDistance(&pflMinDistance);




	D3DVECTOR  pvOrientFront;
   D3DVECTOR  pvOrientTop ;
	 Listener->GetOrientation(&pvOrientFront, &pvOrientTop );
	 



	//蛇的初始化
	
	ShowSnake();
	
	
	
	// hide the mouse
	if (!WINDOWED)
		ShowCursor(FALSE);
	
	// seed random number generator
	srand(Start_Clock());
	
	do{
	Par.food.x = rand()%32;
	Par.food.y = rand()%24;
	}while(Snake.CheckFoodCollision(Par.food));
	
	Par.hEvent = CreateEvent (NULL, FALSE, FALSE, NULL) ;
    
//	SetEvent(Par.hEvent);
    CreateThread(NULL,0,ThreadShowFood,&Par,0,0);
	
	//CreateThread(NULL,0,ThreadGetInput,&Par,0,0);
	// return success
	return(1);
} // end Game_Init

/////////////////////////////////////////////////////////////

int Game_Shutdown(void *parms = NULL, int num_parms = 0)
{
	// this is called after the game is exited and the main event
	// loop while is exited, do all you cleanup and shutdown here
	
    DDraw_Shutdown();
	DInput_Shutdown();
	DSound_Shutdown();
	
	if(lpddsoff[0])
		lpddsoff[0]->Release();
	if(lpddsoff[1])
		lpddsoff[1]->Release();
	
	if(lpddsoff[2])
		lpddsoff[2]->Release();
	
	
	// return success or failure or your own return code here
	return(1);
	
} // end Game_Shutdown

// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR lpcmdline,
				   int ncmdshow)
{
	
	WNDCLASSEX winclass; // this will hold the class we create
	HWND	   hwnd;	 // generic window handle
	MSG		   msg;		 // generic message
	HDC        hdc;      // graphics device context
	
	// first fill in the window class stucture
	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.lpszMenuName	= LPCSTR(IDR_MENU1);
	winclass.lpszClassName	= g_szClassName;
	winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
	
	// save hinstance in global
	main_instance = hinstance;
	
	// register the window class
	if (!RegisterClassEx(&winclass))
		return(0);
	
	
	
	// create the window
	if (!(hwnd = CreateWindowEx(NULL,                  // extended style
		g_szClassName,     // class
		szTitle, // title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		20,20,	  // initial x,y
		WINDOW_WIDTH,WINDOW_HEIGHT,  // initial width, height
		NULL,	  // handle to parent 
		NULL,	  // handle to menu
		hinstance,// instance of this application
		NULL)))	// extra creation parms
		return(0);
	
	
	
	
	
	// save main window handle
	main_window_handle = hwnd;
	
	RECT dest_rect;
	GetClientRect(main_window_handle, &dest_rect); 
	GetWindowRect(main_window_handle, &dest_rect); 
	POINT P = {0,0};
	ClientToScreen(hwnd,&P);
	
	
	RECT rcNewWindowRect;
	SIZE szDesiredClient;
	szDesiredClient.cx = WINDOW_WIDTH;
	szDesiredClient.cy = WINDOW_HEIGHT;
    rcNewWindowRect = CalculateWindowRect(hwnd,szDesiredClient);
	
	MoveWindow(main_window_handle, rcNewWindowRect.left, rcNewWindowRect.top, 
		(rcNewWindowRect.right - rcNewWindowRect.left),
		(rcNewWindowRect.bottom - rcNewWindowRect.top), true);
	WindowCenterlize(hwnd);
	// initialize game here
	Game_Init();
	
	
	// enter main event loop
	while(TRUE)
	{
		// test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;
			
			// translate any accelerator keys
			TranslateMessage(&msg);
			
			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		
		if(bRun)// main game processing goes here
			Game_Main();
		
	} // end while
	
	// closedown game here
	Game_Shutdown();
	
	// return to Windows like this
	return(msg.wParam);
	
} // end WinMain




void ShowSnake(){
	
	int i,j,k;
	Point p;
	HDC hdc;
	int count = Snake.GetCount();
	RECT rectdes={160,0,800,480};
	
	if(DD_OK!=lpddsback->Blt(NULL,lpddsoff[0],NULL,DDBLT_WAIT|DDBLT_KEYSRC,NULL))
		
		//	lpddsback->Blt(NULL,lpddsoff[0],NULL,NULL,NULL);
		//	DDraw_Fill_Surface(lpddsback,0);
		MessageBox(NULL,"error","",MB_OK);
///////////////////载入信息//////////////////////////////////////////////////////
	phase(Snake.GetLevel());
	for ( i = 1,j = MAX_NUM-digit[0];i<=digit[0];i++,j++) {
		
		RECT rectsrc = {(digit[j])*13,60,(digit[j]+1)*13,60+23};
		RECT rectdes = { 5+13*(i-1),155,5+13*i,155+23};
		
		if(DD_OK!=lpddsback->Blt(&rectdes,lpddsoff[1],&rectsrc,DDBLT_WAIT|DDBLT_KEYSRC,NULL))
			MessageBox(NULL,"error","",MB_OK);
		}
		

	phase(Snake.GetScore());
	for ( i = 1,j = MAX_NUM-digit[0];i<=digit[0];i++,j++) {
		
		RECT rectsrc = {(digit[j])*13,60,(digit[j]+1)*13,60+23};
		RECT rectdes = { 5+13*(i-1),265,5+13*i,265+23};
		
		if(DD_OK!=lpddsback->Blt(&rectdes,lpddsoff[1],&rectsrc,DDBLT_WAIT|DDBLT_KEYSRC,NULL))
			MessageBox(NULL,"error111","",MB_OK);
		}


	phase(Snake.GetLength());
	for ( i = 1,j = MAX_NUM-digit[0];i<=digit[0];i++,j++) {
		
		RECT rectsrc = {(digit[j])*13,60,(digit[j]+1)*13,60+23};
		RECT rectdes = { 5+13*(i-1),375,5+13*i,375+23};
		
		if(DD_OK!=lpddsback->Blt(&rectdes,lpddsoff[1],&rectsrc,DDBLT_WAIT|DDBLT_KEYSRC,NULL))
			MessageBox(NULL,"error111","",MB_OK);
	}
	
	lpddsback->GetDC(&hdc);

	char str[10];
	switch(Snake.GetDirection()){
	case UP:strcpy(str,"UP");break;
	case DOWN:strcpy(str,"DOWN");break;
	case LEFT:strcpy(str,"LEFT");break;
	case RIGHT:strcpy(str,"RIGHT");break;
	default :break;
	}
	
	TextOut(hdc,300,14+480,str,strlen(str));
	sprintf(str,"( %d,%d)", Par.food.x,Par.food.y);
	TextOut(hdc,610,14+480,str,strlen(str));
	lpddsback->ReleaseDC(hdc);
	
	//////////////////////////////////////////////////////////////////////////////////////	
	//载入蛇尾
	p = Snake.GetPointCoor(0);
	RECT rectsource1 = {0,40,20,60};
	RECT rectdes1 = {p.x-BODYSIZE/2,p.y-BODYSIZE/2,p.x+BODYSIZE/2,p.y+BODYSIZE/2};
	if(DD_OK!=lpddsback->Blt(&rectdes1,lpddsoff[1],&rectsource1,DDBLT_WAIT|DDBLT_KEYSRC,NULL))
		OutPutInfo("erro55r.txt",ShowLastError());
	//载入蛇头
	p = Snake.GetPointCoor(count-1);
	RECT rectsource2 = {0,0,20,20};
	RECT rectdes2 = {p.x-BODYSIZE/2,p.y-BODYSIZE/2,p.x+BODYSIZE/2,p.y+BODYSIZE/2};
	lpddsback->Blt(&rectdes2,lpddsoff[1],&rectsource2,DDBLT_WAIT|DDBLT_KEYSRC,NULL);
	
	//载入所有蛇身
	p = Snake.GetPointCoor(1);
	RECT rectsource3 = {0,20,20,40};
	RECT rectdes3 = {p.x-BODYSIZE/2,p.y-BODYSIZE/2,p.x+BODYSIZE/2,p.y+BODYSIZE/2};
	lpddsback->Blt(&rectdes3,lpddsoff[1],&rectsource3,DDBLT_WAIT|DDBLT_KEYSRC,NULL);
	
	for(k = 2;k<count-1;k++){
		p = Snake.GetPointCoor(k);
		//RECT rect = {p.x-BODYSIZE/2,p.y-BODYSIZE/2,p.x+BODYSIZE/2,p.y+BODYSIZE/2};
		//lpddsback->BltFast(p.x-BODYSIZE/2,p.y-BODYSIZE/2,lpddsback,&rect,DDBLTFAST_WAIT);
		//LoadBitmapFile(lpddsback,p.x-BODYSIZE/2,p.y-BODYSIZE/2,"snake_body.bmp");
		RECT rectdes = {p.x-BODYSIZE/2,p.y-BODYSIZE/2,p.x+BODYSIZE/2,p.y+BODYSIZE/2};
		lpddsback->Blt(&rectdes,lpddsoff[1],&rectsource3,DDBLT_WAIT|DDBLT_KEYSRC,NULL);
	}
	
	DDraw_Flip2();
	
}





void OutPutInfo(char *filename,char *strinfo){
	ofstream output_file;
	output_file.open(filename);
	output_file<<strinfo;
	output_file.close();
}

char* ShowLastError(){
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
	return (char*)lpMsgBuf;
}


DWORD WINAPI ThreadShowFood(LPVOID lpStartupParam){
	volatile 		PPARAMS pparams ;
	
	pparams = (PPARAMS) lpStartupParam ;

	int x = INDEXTOCOORX(pparams->food.x);
	int y = INDEXTOCOORY(pparams->food.y);
	//ch = "hby";
	
	//	MessageBox(NULL,ch,"",MB_OK);
	
	while (TRUE)
	{
		//WaitForSingleObject (pparams->hEvent, INFINITE) ;

		if(EndThread == true){
			break;
		}
		
		int bottom=20,top=0;
		for(int i = 0;i<3;i++,bottom+=20,top+=20){
			RECT rectsource = {0,top,20,bottom};
			RECT rectdes = {x-BODYSIZE/2,y-BODYSIZE/2,x+BODYSIZE/2,y+BODYSIZE/2};
            lpddsback->Blt(&rectdes,lpddsoff[0],&rectdes,DDBLT_WAIT|DDBLT_KEYSRC,NULL);
			lpddsback->Blt(&rectdes,lpddsoff[2],&rectsource,DDBLT_WAIT|DDBLT_KEYSRC,NULL);
			//为何不能直接贴到lpddsprimary上
			DDraw_Flip2();
			Sleep(10);	
		}
		if(!Snake.IsFoodExist()){
			//产生新的食物,不与蛇身重复
			sound_fx[eatindex].dsbuffer->Play(0,0,0);
			do{
				Par.food.x = rand()%32;
				Par.food.y = rand()%24;
			}while(Snake.CheckFoodCollision(Par.food));
			
			x = INDEXTOCOORX(Par.food.x);
			y = INDEXTOCOORY(Par.food.y);
			
			Snake.Setfood();
			
		}
		
		
		
	}//while
	return 0;
}



DWORD WINAPI ThreadGetInput(LPVOID lpStartupParam){
	while(true){
		DInput_Read_Keyboard();
	}
	return 0;
}


void   phase(int num){
	int i;
	for (i = 0;i<MAX_NUM;i++){
		digit[i] = 0;
	}
	digit[0] = 1;
	i = MAX_NUM - 1;
	digit[i] = 0;
	
	while(num!=0){
		digit[i--] = num%10;
		digit[0]++;
		num = num/10;	
	}
	if(digit[0] != 1){
		digit[0]-=1;
	}
}