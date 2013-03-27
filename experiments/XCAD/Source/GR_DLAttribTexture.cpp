/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "gr_dlattribtexture.h"
#include <windows.h>
#include <glaux.h>
#include <gl\gl.h>
#include <gl\glu.h>

GR_DLAttribTexture::GR_DLAttribTexture(LPCTSTR lpszFilePath)
:m_pBytes(NULL)
{
	SetTexture(lpszFilePath);
}

GR_DLAttribTexture::~GR_DLAttribTexture(void)
{
	if(m_pBytes)
		::free(m_pBytes);
}

void GR_DLAttribTexture::SetTexture(LPCTSTR lpszFilePath)
{
	if(m_pBytes)
		::free(m_pBytes);

	AUX_RGBImageRec* pRGBImageRec = auxDIBImageLoad(lpszFilePath);
	m_iWidth	= pRGBImageRec->sizeX;
	m_iHeight	= pRGBImageRec->sizeY;
	m_pBytes	= pRGBImageRec->data;
}

BYTE* GR_DLAttribTexture::GetBytes() const
{
	return m_pBytes;
}

int GR_DLAttribTexture::GetHeight() const
{
	return m_iHeight;
}

int GR_DLAttribTexture::GetWidth() const
{
	return m_iWidth;
}