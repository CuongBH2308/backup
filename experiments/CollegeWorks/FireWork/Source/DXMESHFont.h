/*
 文件描述：使用ID3DXMesh为成员，创建MESH作为3D字体，字体多样且有3D效果
 */

#ifndef _DXMESHFont_H
#define _DXMESHFont_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDXFont.h"

namespace d3d
{
	class CDXMESHFont : public IDXFont  
	{
	public:
		CDXMESHFont(IDirect3DDevice9* device, const  LOGFONT *pLogFont = NULL);
		virtual ~CDXMESHFont();

	public:
		//在屏幕上写字
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L );
		
		//在屏幕上写帧速
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta);
		
		
	private:
		ID3DXMesh* m_pMeshFont;//表示字的模型

		HDC m_hdc; 
		HFONT m_hFont;
		HFONT m_hFontOld;
		
	};
}
#endif //_DXMESHFont_H
