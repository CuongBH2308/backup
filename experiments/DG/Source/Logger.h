/**
* @file Logger.h Debug Provides a class CLogger.
*

*
* @author Baiyan Huang
*
* @date Date [Baiyan Huang] Created
*/
#pragma once
#include "BuildOption.h"
#ifdef ENABLE_REPORT

namespace DG
{
	/**
	* A simple file manipulate class, used to log error messages.
	*/
	class CLogger
	{
	public:
		CLogger(const CString& strFileName);
		~CLogger(void);

		/**
		* Log the message to log file.
		*/
		void Log(const CString& strMsg);

	private:
		CStdioFile m_file;         ///< The file handle.
		CString m_strFileName;     ///< The current log file name.
	};
}
#endif