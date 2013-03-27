/**
* @file DebugManager.h Provide a Debug Manager class which can report assert, error message to a debug window, 
* and trace to a log file.
*

*
* @author Baiyan Huang
*
* @date Date [Baiyan Huang] Created
*/
#pragma once
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "Singleton.h"

namespace DG
{
	class CDebugWnd;
	class CLogger;

	/**
	* This class reponsible for report assert, error message to a debug window, and trace to a log file
	* @remarks We need to destroy the debug window at a specific time, so we need to use SingletonPtr
	*/
	class  CDebugManager : public FW::SingletonPtr<CDebugManager>
	{
	public:
		friend class FW::SingletonPtr<CDebugManager>;

		/**
		* Debug option when we encounter with an assert window.
		*/
		enum Option     
		{
			kBreakInto,     ///< Debug into the source code.
			kIgnore         ///< Just ignore the assert and continue execution.
		};

	public:
		/**
		* Native Assert callback
		*/
		static int NativeAssert( int nReportType, char *szMessage, int *pnReturnValue );

		/**
		* Custom Assert
		*/
		Option CustomAssert(const CString& strError, const CString& strFileName, int nLineNum);

		/**
		* Report error
		*/
		Option CustomError(const CString& strError, const CString& strFileName, int nLineNum);

		/**
		* Report a message
		*/
		void ReportMsg(const CString& strMsg, const CString& strFileName, int nLineNum);

	public:
		CLogger* GetLogger(){return m_pLogger;}

		CDebugWnd* GetDebugWnd() {return m_pDebugWnd;}

		/**
		* Open the log file
		*/
		void OpenLogFile();

		/**
		* Hook system assert or not
		*/
		void ToggleSystemAssert();

	protected:
		CDebugManager(void);
		~CDebugManager(void);

	private:
		CLogger* m_pLogger;                      ///< CLogger object to report msg to log file.

		CDebugWnd* m_pDebugWnd;                  ///< CDebugWnd object to report msg to debug window.

		CString m_strLogPath;                    ///< The log file path.

		CString m_strFullLogFileName;            ///< The full log file name.

	};
}
#endif
