#include "stdafx.h"
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "ReportList.h"
#include "DebugMacros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace DG;

#pragma region IDEHandler
#if _MSC_VER >= 1300     // VC++ 7 or more

#include <initguid.h>
#pragma warning( disable : 4278 )
#pragma warning( disable : 4146 )
#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("8.0") lcid("0") raw_interfaces_only named_guids
#pragma warning( default : 4146 )
#pragma warning( default : 4278 )

/**
 * This is a EnumWindowsProc function to activate the running visual studio window.
 * @remarks Here we use windows text to find the visual studio window, which is only available for English version.
 */
BOOL CALLBACK ActivateVisualStudio(HWND hWnd, LPARAM lParam)
{
	TCHAR szBuffer[1000];
	LPTSTR szWindowCaption = szBuffer;
	::GetWindowText(hWnd, szWindowCaption, 1000);
	CString strWindowCaption = szWindowCaption;
	int nPos = strWindowCaption.Find(_T("- Microsoft Visual Studio"));
	if(nPos == -1)  return TRUE;
	else
	{
		if(-1 == strWindowCaption.Find(_T("Running")) && 
			-1 == strWindowCaption.Find(_T("Debugging")))
		{
			return TRUE;
		}
		else
		{
			::BringWindowToTop(hWnd);
			::ShowWindow(hWnd, SW_MAXIMIZE);
			return FALSE;
		}
	}
}

namespace VC7IdeHandler {
	static bool initialize()
	{
		return true;
	}

	static void uninitialize( bool initialized )
	{
	}

	/**
	 * Go to the source code of the specified source file and line in visual studio and highlight it.
	 * @remarks We assume there is only one Visual Studio instance, or else we can't ensure that 
	 * the source file will be opened in the running visual studio.
	 */
	static void goToLineInSourceCode( CString fileName, int line )
	{
		// Activate the running visual studio first
		EnumWindows(ActivateVisualStudio, NULL);

		USES_CONVERSION;

		CComPtr< IRunningObjectTable > pIRunningObjectTable;
		HRESULT hr = ::GetRunningObjectTable( 0, &pIRunningObjectTable );

		CComPtr< IEnumMoniker > pIEnumMoniker;
		hr = pIRunningObjectTable->EnumRunning( &pIEnumMoniker );

		CComPtr< EnvDTE::_DTE > pIEnvDTE;
		while ( true )
		{
			ULONG celtFetched;
			CComPtr< IMoniker > pIMoniker;
			if ( S_OK != pIEnumMoniker->Next( 1, &pIMoniker, &celtFetched ) )
				break;

			CComPtr< IBindCtx > pIBindCtx; 
			hr = ::CreateBindCtx( NULL, &pIBindCtx ); 

			LPOLESTR pszDisplayName;
			pIMoniker->GetDisplayName( pIBindCtx, NULL, &pszDisplayName );

			TRACE( "Moniker %s\n", W2A( pszDisplayName ) );

			CString strDisplayName( pszDisplayName );
			CComPtr< IMalloc > pIMalloc;
			::CoGetMalloc( 1, &pIMalloc );
			pIMalloc->Free( pszDisplayName );

			if ( strDisplayName.Right( 4 ) == _T(".sln") 
				|| strDisplayName.Find( _T("VisualStudio.DTE") ) >= 0 )
			{
				CComPtr< IUnknown > pIUnknown;
				pIRunningObjectTable->GetObject( pIMoniker, &pIUnknown );
				pIUnknown->QueryInterface( &pIEnvDTE );
				if( pIEnvDTE.p )
					break;
			}
		}

		if ( pIEnvDTE.p )
		{
			CComPtr< EnvDTE::Documents > pIDocuments;
			HRESULT result = pIEnvDTE->get_Documents( &pIDocuments );
			if ( !SUCCEEDED( result ) )
				return;

			DGASSERT( pIDocuments.p );

			CComPtr< EnvDTE::Document > pIDocument;
			CComBSTR bstrFileName( fileName );
			CComVariant type=_T("Text");
			CComVariant read=_T("False");
			result = pIDocuments->Open( bstrFileName, 
				type.bstrVal,
				read.bVal, 
				&pIDocument );
			if ( !SUCCEEDED( result ) )
				return;

			DGASSERT( pIDocument.p );

			CComPtr< IDispatch > pIDispatch;
			result = pIDocument->get_Selection( &pIDispatch );
			if ( !SUCCEEDED( result ) )
				return;

			CComPtr< EnvDTE::TextSelection > pITextSelection;
			pIDispatch->QueryInterface( &pITextSelection );

			DGASSERT( pITextSelection.p );

			result = pITextSelection->GotoLine( line, TRUE );
			if ( !SUCCEEDED( result ) )
				return;

		}
	}

} // namespace VC7IdeHandler

namespace IDEHandler = VC7IdeHandler;

#else
#error Unsupported VC++ version.
#endif

#pragma endregion

#pragma region CSourceLine
/**
 * Stands for source code file name and line number.
 */
class CSourceLine
{
public:
	CSourceLine(LPCTSTR szFileName, int nLineNum):m_strFileName(szFileName), m_nLineNum(nLineNum){}
	CSourceLine(LPCTSTR szSourceLine);

	/**
	 * Jump to the source line.
	 */
	bool GoTo();

private:
	CString m_strFileName;
	int     m_nLineNum;
};

CSourceLine::CSourceLine(LPCTSTR szSourceLine)
{
	// Parse the source line string to get source file name and line number.
	// SourceLine: z:\commonlayer\test\itstestproject-mfc\itstestmfc\mfctestcmd.cpp(32)

	// Source file
	CString strSourceLine = szSourceLine;
	int nPos = strSourceLine.ReverseFind(_T('('));
	m_strFileName = strSourceLine.Left(nPos);

	// Line number
	CString strLineNum = strSourceLine.Mid(nPos+1, strSourceLine.GetLength()- nPos - 2);
	m_nLineNum = _tstoi(strLineNum);
}
bool CSourceLine::GoTo()
{
	IDEHandler::goToLineInSourceCode(m_strFileName, m_nLineNum);
	return true;
}

#pragma endregion

#pragma region CReportList
// CReportList
BEGIN_MESSAGE_MAP(CReportList, CListCtrl)
	//{{AFX_MSG_MAP(MsDevCallerListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CReportList, CListCtrl)

CReportList::CReportList()
{

}

CReportList::~CReportList()
{
}

void CReportList::Initialize()
{
	// Set control styles.
	ModifyStyle(0, LVS_REPORT);
	SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// insert 3 columns with specified length.
	CRect rect;
	this->GetClientRect(&rect);
	int nColInterval = rect.Width()/9;
	this->InsertColumn(0, _T("Time"), LVCFMT_LEFT, nColInterval * 2);
	this->InsertColumn(2, _T("Source Line"), LVCFMT_LEFT, nColInterval * 3);
	this->InsertColumn(4, _T("Message"), LVCFMT_LEFT, rect.Width() - nColInterval * 5);

	// The index of "Source Line" sub item
	m_nSourceLineSubItem = 1;
}

void CReportList::AppendReport(const CString& strTime, const CString& strSourceLine, const CString& strMsg)
{
	LVITEM lvi;

	// Item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = this->GetItemCount();

	// SubItem: Time
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strTime);
	this->InsertItem(&lvi);

	// SubItem: SourceLine
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strSourceLine);
	this->SetItem(&lvi);

	// SubItem: Msg
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strMsg);
	this->SetItem(&lvi);

	// Scroll the list box to the end
	this->EnsureVisible(lvi.iItem, FALSE);
}
void CReportList::ClearReports()
{
	this->DeleteAllItems();
}

void CReportList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Get index of selected item
	POSITION pos = GetFirstSelectedItemPosition();
	int hotItem = GetNextSelectedItem(pos);

	// Get the SubItem: SourceLine
	CString strSourceLine = GetItemText( hotItem, m_nSourceLineSubItem);

	// Go to the source line.
	CSourceLine srcLine(strSourceLine);
	srcLine.GoTo();

	*pResult = 0;
}
#pragma endregion

#endif