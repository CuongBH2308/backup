/*
 �ļ�������ʹ��LPD3DXFONTΪ���Ա����GDIʵ�֣�����������ٶȽ���
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
		//����Ļ��д��
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L );

		//����Ļ��д֡��
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta);
		
		
	private:
		LPD3DXFONT m_pGdiFont; // return the created font
	};
}

#endif // _DXGDIFont_H
