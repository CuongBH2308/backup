/**
* @file ReportList.h Implement the report list class which is used in debug window.
* Double-click on report item will open the source line in Visual studio.
*

*
* @author Baiyan Huang
*
* @date 7/28/2008 [Baiyan Huang] Refactor this class from CDebugWnd and add the functionalities to jump to source
*                                line when double clicked on a list item.
*/
#pragma once
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include <afxcmn.h>  // MFC support for Windows Common Controls

namespace DG
{

	/**
	* A list control class used in debug window to report errors.
	*/
	class CReportList : public CListCtrl
	{
		DECLARE_DYNAMIC(CReportList)

	public:
		CReportList();
		virtual ~CReportList();

	public:
		/**
		* Initialize the report list control. such as set control styles, create columns.
		*/
		void Initialize();

		/**
		* Append a report item to the list.
		*/
		void AppendReport(const CString& strTime, const CString& strSourceLine, const CString& strMsg);

		/**
		* Clear the reports.
		*/
		void ClearReports();

	protected:
		DECLARE_MESSAGE_MAP()

		/**
		* Double-click on a specific row to jump to the source line in Visual Studio.
		*/
		void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);


	private:
		int m_nSourceLineSubItem; ///< Mark the sub item number of "source line" column.
	};
}
#endif
