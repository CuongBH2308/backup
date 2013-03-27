/*
 �ļ�������ʹ��ID3DXMeshΪ��Ա������MESH��Ϊ3D���壬�����������3DЧ��
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
		//����Ļ��д��
		virtual bool DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags=0L );
		
		//����Ļ��д֡��
		virtual bool DrawFPS(RECT rect,DWORD dwColor,float timeDelta);
		
		
	private:
		ID3DXMesh* m_pMeshFont;//��ʾ�ֵ�ģ��

		HDC m_hdc; 
		HFONT m_hFont;
		HFONT m_hFontOld;
		
	};
}
#endif //_DXMESHFont_H
