// IDXFont.cpp: implementation of the IDXFont class.
//
//////////////////////////////////////////////////////////////////////

#include "IDXFont.h"
using d3d::IDXFont;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IDXFont::IDXFont(IDirect3DDevice9* device)
{	
	m_pDevice = device;
}

IDXFont::~IDXFont()
{

}
/*
bool IDXFont::DrawTexts(RECT rect,DWORD dwColor,string strOut)
{
	return true;
}

bool IDXFont::DrawFPS(RECT rect,DWORD dwColor,float timeDelta)
{
	return true;
}
*/