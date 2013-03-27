// DXGDIFont.cpp: implementation of the CDXGDIFont class.
//
//////////////////////////////////////////////////////////////////////

#include "DXGDIFont.h"
#include "d3dbase.h"
using d3d::CDXGDIFont;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDXGDIFont::CDXGDIFont(IDirect3DDevice9* device,const  LOGFONT *pLogFont /* = NULL */)
:IDXFont(device)
{
	LOGFONT lf;
	if(pLogFont == NULL)//È¡Ä¬ÈÏ×ÖÌå
	{
		ZeroMemory(&lf, sizeof(LOGFONT));
		
		lf.lfHeight         = 25;    // in logical units
		lf.lfWidth          = 12;    // in logical units
		lf.lfEscapement     = 0;        
		lf.lfOrientation    = 0;     
		lf.lfWeight         = 500;   // boldness, range 0(light) - 1000(bold)
		lf.lfItalic         = false;   
		lf.lfUnderline      = false;    
		lf.lfStrikeOut      = false;    
		lf.lfCharSet        = DEFAULT_CHARSET;
		lf.lfOutPrecision   = 0;              
		lf.lfClipPrecision  = 0;          
		lf.lfQuality        = 0;           
		lf.lfPitchAndFamily = 0;           
		strcpy(lf.lfFaceName, "Times New Roman"); // font style
	}
	else
	{
		lf = *pLogFont;
	}
	if(FAILED(D3DXCreateFontIndirect(m_pDevice, &lf, &m_pGdiFont)))
	{
		::MessageBox(0, "D3DXCreateFontIndirect() - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
	
}

CDXGDIFont::~CDXGDIFont()
{
	d3dbase::Release<ID3DXFont*>(m_pGdiFont);

}


bool CDXGDIFont::DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags/* =0L  */)
{
	
	int iresult = m_pGdiFont->DrawText(
		strOut.c_str(), 
		-1,               // size of string or -1 indicates null terminating string
		&rect,            // rectangle text is to be formatted to in windows coords
		dwFlags, // draw in the top left corner of the viewport
		dwColor);  
	if(iresult == 0)
	{
		return false;
	}

	else 
		return true;
	
}

bool CDXGDIFont::DrawFPS(RECT rect,DWORD dwColor,float timeDelta)
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0;
	static char  fpsString[9] = {0};
	if( m_pGdiFont )
	{
		frameCnt++;
		
		timeElapsed += timeDelta;
		
		if(timeElapsed >= 1.0f)
		{
			m_fps = (float)frameCnt / timeElapsed;
			sprintf(fpsString, "%f", m_fps);
			fpsString[8] = '\0'; // mark end of string
			
			
			timeElapsed = 0.0f;
			frameCnt    = 0;
		}
		
		DrawTexts(rect,dwColor,fpsString);	
	}
	return true;
}