// DXMESHFont.cpp: implementation of the CDXMESHFont class.
//
//////////////////////////////////////////////////////////////////////

#include "DXMESHFont.h"
using d3d::IDXFont;
using d3d::CDXMESHFont;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDXMESHFont::CDXMESHFont(IDirect3DDevice9* device, const LOGFONT *pLogFont /* = NULL */)
:IDXFont(device),m_pMeshFont(NULL)
{
	// Get a handle to a device context.
	//
	m_hdc = CreateCompatibleDC( 0 );
	
	//
	// Describe the font we want.
	//
	
    LOGFONT lf;
	if(pLogFont == NULL)//取默认字体
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

	m_hFont = CreateFontIndirect(&lf);
    m_hFontOld = (HFONT)SelectObject(m_hdc, m_hFont); 
}

CDXMESHFont::~CDXMESHFont()
{
	d3dbase::Delete<ID3DXMesh*>(m_pMeshFont);
	//
	// Restore the old font and free the acquired HDC.
	//
    SelectObject(m_hdc, m_hFontOld);
    DeleteObject( m_hFont );
    DeleteDC( m_hdc );
}

bool CDXMESHFont::DrawTexts(RECT rect,DWORD dwColor,string strOut,DWORD dwFlags/* =0L  */)
{
	HRESULT hr;
	static string strLast = "";

	if(strLast!=strOut)//前后字不同，重新创建字模型,否则跳过，大大提高了速度
	{	
		d3dbase::Delete<ID3DXMesh*>(m_pMeshFont);
		hr = D3DXCreateText(m_pDevice, m_hdc, strOut.c_str(), 0.001f, 0.4f, &m_pMeshFont, 0, 0);
		if(FAILED(hr))
		{
			return false;
		}
		strLast = strOut;
	}
	
	
	D3DXVECTOR3 dir(0.0f, -0.5f, 1.0f);
	D3DXCOLOR col = DWTOD3DXCOLOR(dwColor);
	D3DLIGHT9 light = d3dbase::InitDirectionalLight(&dir, &col);

	//D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	D3DMATERIAL9 fontmtrl = d3dbase::YELLOW_MTRL;
	m_pDevice->SetMaterial(&fontmtrl);

/*	m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
	
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	m_pDevice->SetMaterial(&d3dbase::WHITE_MTRL);
	*/
	m_pDevice->SetLight(0, &light);
	m_pDevice->LightEnable(0, true);
	D3DXMATRIX World;
	// 用rect的三个分量来表示其三维位置
	D3DXMatrixTranslation(&World, rect.left, rect.top, rect.right);

	m_pDevice->SetTransform(D3DTS_WORLD, &World);
	
	hr = m_pMeshFont->DrawSubset(0);
//	m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	if(FAILED(hr))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CDXMESHFont::DrawFPS(RECT rect,DWORD dwColor,float timeDelta)
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0;
	static char  fpsString[9] = "0.000000";
	//	if( m_pMeshFont )
	//	{
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
	//	}
	return true;
}