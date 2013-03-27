/*
 �ļ�������ʹ��CD3DFontΪ���Ա����D3D����д�֣����ٵ��������

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
		//����Ļ��д��
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L );
		
		//����Ļ��д֡��
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta);
		
		
	private:
		CD3DFont* m_pTexFont;  // 
	};
}
#endif // _DXTEXFont_H
