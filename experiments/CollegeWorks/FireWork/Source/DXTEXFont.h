/*
 文件描述：使用CD3DFont为其成员，用D3D纹理写字，高速但字体较少

 */

#ifndef _DXTEXFont_H
#define _DXTEXFont_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d3dfont.h"

#include "IDXFont.h"

namespace d3d
{
	
	class CDXTEXFont : public IDXFont  
	{
	public:
		CDXTEXFont(IDirect3DDevice9* device, DWORD dwHeight = 16,const char* strFontName = "Times New Roman" ,DWORD dwFlags=0L);
		virtual ~CDXTEXFont();
		
	public:
		//在屏幕上写字
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L );
		
		//在屏幕上写帧速
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta);
		
		
	private:
		CD3DFont* m_pTexFont;  // 
	};
}
#endif // _DXTEXFont_H
