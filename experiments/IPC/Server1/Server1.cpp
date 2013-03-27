// Server1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server1.h"
#include "../IPCCommon/Invoker.h"
#include "../IPCCommon/IPCStrategy.h"
#include "../IPCCommon/ProxyStub.h"
#include <cassert>
#include <psapi.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef std::basic_string<TCHAR> tstring;


// The one and only application object

CWinApp theApp;

using namespace std;

void ExitServer(void* pPara)
{
	IPCInvoker::ExitServer(pPara);
}

REGISTER_FUNC(ExitServer);


tstring GetProcessModules(DWORD dwPID)
{
	HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
	assert(hProcess);
	if(!hProcess) return _T("");

	HMODULE hMods[1024];
	DWORD cbNeeded;
	tstring strModules;
	if( ::EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (size_t i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
		{
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.
			if (::GetModuleFileNameEx( hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				strModules.append(szModName);
				strModules.append(_T("\n"));
			}
		}
	}

	return strModules;

}

void GetProcessModules(void* pPara)
{
	// unpackage input
	DWORD pid;
	ProxyStub::UnPackage(pPara, pid);

	tstring strModules = GetProcessModules(pid);

	// package output
	void* pOutput = IPCStrategyFactory::GetActiveIPCStrategy()->GetOutputData();
	ProxyStub::Package(strModules, pOutput);
}


REGISTER_FUNC(GetProcessModules);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		IPCInvoker::ServerDispatch();
		//SECURITY_ATTRIBUTES sa;
		//sa.nLength = sizeof(SECURITY_ATTRIBUTES );
		//sa.lpSecurityDescriptor = NULL;
		//sa.bInheritHandle = TRUE;

		//HANDLE hSendingEvent = CreateEvent(&sa, FALSE, FALSE, Event_Function_Call); // auto reset events with non-signaled state as default
		//HANDLE hSendingMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, Index_Size, Mapping_Function_Index);


		//bool bRunning = true;
		//while(bRunning)
		//{
		//	::WaitForSingleObject(hSendingEvent, INFINITE);

		//	LPVOID pData = ::MapViewOfFile(hSendingMap, FILE_MAP_READ, 0, 0, Index_Size);
		//	DWORD* piData = reinterpret_cast<DWORD*>(pData);

		//	if(*piData == 4)
		//	{
		//		_tprintf(_T("Execute Function 4"));

		//		HANDLE hRetrivingMap = ::OpenFileMapping(FILE_MAP_WRITE, FALSE, Mapping_Function_Output);
		//		LPVOID pData = ::MapViewOfFile(hRetrivingMap, FILE_MAP_WRITE, 0, 0, Data_Size);

		//		//::EnumProcessModules(HANDLE, )

		//		CString strValue = _T("Hello, World!!!");
		//		TCHAR* szValue = strValue.GetBuffer();
		//		_tprintf(szValue);

		//		::memcpy(pData, szValue, (strValue.GetLength() + 1) * sizeof(TCHAR));

		//		HANDLE hRetrievingEvent = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, Event_Function_Return);
		//		if(hRetrievingEvent) ::SetEvent(hRetrievingEvent);

		//	}
		//}
	}

	return nRetCode;
}
