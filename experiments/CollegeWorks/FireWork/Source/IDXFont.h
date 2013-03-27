/*
 文件描述：画笔的基类，可以用来在屏幕上写字，计算FPS
 从它派生三个类，分别用于不同的用途
 */

#ifndef _IDXFont_H
#define _IDXFont_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<string>
#include <d3dx9.h>
#include "dxhelper.h"
#include "d3dbase.h"
using std::string;
using namespace d3dbase;

namespace d3d
{
	
	class IDXFont  
	{
	public:
		IDXFont(IDirect3DDevice9* device);
		virtual ~IDXFont();
		
	public:
		////在屏幕上写字
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L) = 0;

		////在屏幕上写帧速
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta) = 0;
		
	protected:
		IDirect3DDevice9* m_pDevice;  //for creating fonts
		float    m_fps;               //帧速  frame/second
		
	};
}
#endif // _IDXFont_H
