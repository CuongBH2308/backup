// DXTEXFont.cpp: implementation of the CDXTEXFont class.
//
//////////////////////////////////////////////////////////////////////

#include "DXTEXFont.h"
using d3d::IDXFont;
using d3d::CDXTEXFont;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//D3DFONT_BOLD,
//D3DFONT_ITALIC, D3DFONT_ZENABLE
CDXTEXFont::CDXTEXFont(IDirect3DDevice9* device,DWORD dwHeight /* = 16 */,const char* strFontName /* = "Times New Roman"  */,DWORD dwFlags/* =0L */)
:IDXFont(device),m_pTexFont(NULL)
{
	m_pTexFont = new CD3DFont(strFontName,dwHeight,dwFlags);
	
	if(m_pTexFont)
	{
		m_pTexFont->InitDeviceObjects( m_pDevice );
		m_pTexFont->RestoreDeviceObjects();
		
	}
	else
	{
		throw cGameError("create textrue font failed");
	}
	
}

CDXTEXFont::~CDXTEXFont()
{
	m_pTexFont->InvalidateDeviceObjects();
	m_pTexFont->DeleteDeviceObjects();
	d3dbase::Delete<CD3DFont*>(m_pTexFont);
}

bool CDXTEXFont::DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags/* =0L  */)
{
	HRESULT hr;
	hr = m_pTexFont->DrawText((FLOAT)rect.left,(FLOAT)rect.top,dwColor,strOut.c_str(),dwFlags);
	if(FAILED(hr))
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

bool CDXTEXFont::DrawFPS(RECT rect,DWORD dwColor,float timeDelta)
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0;
	static char  fpsString[9] = "0.000000";
	if( m_pTexFont != NULL)
	{
		frameCnt++;
		
		timeElapsed += timeDelta;
		
		if(timeElapsed >= 1.0f)
		{
			m_fps = (float)frameCnt / timeElapsed;
			sprintf(fpsString, "%f", m_fps);
			fpsString[8] = '\0'; // mark end of string
			
			char *p = fpsString;
			timeElapsed = 0.0f;
			frameCnt    = 0;
		}
		
		DrawTexts(rect,dwColor,fpsString);	
	}
	return true;
}