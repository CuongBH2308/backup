/**
* @file DebugWnd.h Debug Window Class, To show error messages history to help debug.
*

*
* @author Baiyan Huang
*
* @date 11/1/2007 [Baiyan Huang] Created
*/
#pragma once
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "Resource.h"
#include "ReportList.h"

namespace DG
{
	/**
	* Show error messages history to help debug and provides several advanced settings.
	*/
	class CDebugWnd : public CDialog
	{
		DECLARE_DYNAMIC(CDebugWnd)

	public:
		CDebugWnd(CWnd* pParent = NULL);
		virtual ~CDebugWnd();

		enum { IDD = IDD_DIALOG_DEBUG };

		BOOL  GetIgnoreAssert();
		BOOL  GetStopOnError();
		BOOL  GetHookSystemAssert();

		void  SetIgnoreAssert(BOOL bYes);
		void  SetStopOnError(BOOL bYes);
		void  SetHookSystemAssert(BOOL bYes);

		/**
		* Append an message to the report list control on the debug window.
		*/
		void Report(const CString& strTime, const CString& strSourceLine, const CString& strMsg);

	protected:
		DECLARE_MESSAGE_MAP()

		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		virtual BOOL OnInitDialog();

		afx_msg void OnClose();
		afx_msg void OnBnClickedButtonClear();
		afx_msg void OnBnClickedCheckHookSystemAssert();
		afx_msg void OnBnClickedButtonOpenLogFile();
		afx_msg void OnNcLButtonDblClk(UINT nHitTest,CPoint point);

	private:
		/**
		* Put the debug window to the right-bottom corner of the screen.
		*/
		void RepositionWindow();

		CReportList m_reportList;
		CButton m_btnIgnoreAssert;
		CButton m_btnStopOnError;
		CButton m_btnHookSystemAssert;
	};
}

#endif