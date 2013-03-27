/*
 文件描述：使用LPD3DXFONT为其成员，用GDI实现，字体多样但速度较慢
 */

#ifndef _DXGDIFont_H
#define _DXGDIFont_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDXFont.h"
namespace d3d
{
	
	class CDXGDIFont : public IDXFont  
	{
	public:                                 // // LOGFONT structure describing the font
		CDXGDIFont(IDirect3DDevice9* device, const  LOGFONT *pLogFont = NULL);
		virtual ~CDXGDIFont();
	public:
		//在屏幕上写字
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L );

		//在屏幕上写帧速
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta);
		
		
	private:
		LPD3DXFONT m_pGdiFont; // return the created font
	};
}

#endif // _DXGDIFont_H
