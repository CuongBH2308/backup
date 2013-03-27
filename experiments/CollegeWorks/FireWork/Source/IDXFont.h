/*
 �ļ����������ʵĻ��࣬������������Ļ��д�֣�����FPS
 �������������࣬�ֱ����ڲ�ͬ����;
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
		////����Ļ��д��
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L) = 0;

		////����Ļ��д֡��
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta) = 0;
		
	protected:
		IDirect3DDevice9* m_pDevice;  //for creating fonts
		float    m_fps;               //֡��  frame/second
		
	};
}
#endif // _IDXFont_H
