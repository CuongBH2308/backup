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
#include "fw_editpos.h"

FW_EditPos::FW_EditPos(void)
{
}

FW_EditPos::~FW_EditPos(void)
{
}

// Is the string in the edit is valid
// virtual 
BOOL FW_EditPos::IsValid() const
{
	CString str;
	GetWindowText(str);
	TCHAR* lpszText = str.GetBuffer(0);
    	ASSERT(lpszText != NULL);
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	TCHAR chFirst = lpszText[0];
	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	if (d == 0.0 && chFirst != _T('0'))
		return FALSE;   // could not convert
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	if (*lpszText != _T('\0'))
		return FALSE;   // not terminated properly

	return TRUE;
}

BOOL FW_EditPos::GetValue(float& value) const
{
	CString str;
	GetWindowText(str);
	TCHAR* lpszText = str.GetBuffer(0);
	ASSERT(lpszText != NULL);
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	TCHAR chFirst = lpszText[0];
	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	if (d == 0.0 && chFirst != _T('0'))
		return FALSE;   // could not convert
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	if (*lpszText != _T('\0'))
		return FALSE;   // not terminated properly

	value = float(d);
	return TRUE;
}