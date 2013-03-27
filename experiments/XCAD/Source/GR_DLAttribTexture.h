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


#pragma once
#include "gr_dlattrib.h"

class GR_DLAttribTexture : public GR_DLAttrib
{
public:
	GR_DLAttribTexture(LPCTSTR lpszFilePath);
	virtual ~GR_DLAttribTexture(void);

	void	SetTexture(LPCTSTR lpszFilePath);
	BYTE*	GetBytes() const;
	int		GetHeight() const;
	int		GetWidth() const;

private:
	BYTE* m_pBytes;
	int m_iHeight;
	int m_iWidth;
};
