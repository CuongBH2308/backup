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
#include "fw_commandlineinfo.h"

void SetErrorInfo(UINT uiStringID)
{
	CComPtr<ICreateErrorInfo> spCEI;
	CComQIPtr<IErrorInfo, &IID_IErrorInfo> spEI;
	CString strError;

	strError.LoadString(uiStringID);
	if(!strError.IsEmpty())
	{
		CreateErrorInfo(&spCEI);
		spCEI->SetDescription(strError.AllocSysString());
		spEI = spCEI;
		SetErrorInfo(0, spEI);
	}
}

// This method is used to parse out extra command line parameters that 
// we are expecting for this sample. These parameters are to allow flexibility 
// in the sample. Typical hosts would not specify these values in this manner.
// The possibilities are:
//
// /winhelp		
// /vbalang=XXXX
//
// /winhelp indicates that VBA should use winhelp instead of the
// default HTML help. Typically a host will use ONLY one help style,
// 
// /vbalang is used to specify which language of VBA the sample uses
// the XXXX should be replaced by a four digit decimal language specifier, e.g:
// /vbalang=1031
// for German VBA. The default is English.

void FW_CommandLineInfo::ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast)
{
	CString strParam(lpszParam);

	if(bFlag)
	{
		if(!strParam.CompareNoCase("winhelp"))
		{
			m_bWinHelp = TRUE;
		}
		else 
		{
			CString left, right;
			left = strParam.Left(8);
			if(!left.CompareNoCase("vbalang="))
			{
				right = strParam.Right(4);
				int lcid = _ttoi(right);
				if( lcid > 1000 )
					m_lcid = (LCID)lcid;
			}
		}
	}

	CCommandLineInfo::ParseParam(lpszParam, bFlag, bLast);
}

