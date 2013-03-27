// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"
#include "../IPCCommon/Invoker.h"
#include "../IPCCommon/ProxyStub.h"
#include "../IPCCommon/IPCStrategy.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

typedef basic_string<TCHAR> tstring;

// Function Wrappers
void ExitServer()
{
	IPCInvoker::ClientInvoke("ExitServer");
}

tstring GetProcessModules(DWORD dwPID)
{
	// set input
	void* pInputData = IPCStrategyFactory::GetActiveIPCStrategy()->GetInputData();
	ProxyStub::Package(dwPID, pInputData);

	IPCInvoker::ClientInvoke("GetProcessModules");

	// get output
	void* pOutputData = IPCStrategyFactory::GetActiveIPCStrategy()->GetOutputData();
	tstring strModules;
	ProxyStub::UnPackage(pOutputData, strModules);

	return strModules;
}

//
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
		DWORD pid = 1712;
		tstring strModules = GetProcessModules(pid);

		_tprintf(_T("%s"), strModules.c_str());

		ExitServer();

		//// Can't open filemapping created in a 64bit process.
		//HANDLE hSendingMap = ::OpenFileMapping(FILE_MAP_WRITE, FALSE, Mapping_Function_Index);
		//DWORD dwErr = ::GetLastError();
		//LPVOID pIndex = ::MapViewOfFile(hSendingMap, FILE_MAP_WRITE, 0, 0, Index_Size);

		//// 
		//HANDLE hRetrivingMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, Data_Size, Mapping_Function_Output);
		//LPVOID pData = ::MapViewOfFile(hRetrivingMap, FILE_MAP_READ, 0, 0, Data_Size);

		//HANDLE hRetrievingEvent = CreateEvent(NULL, FALSE, FALSE, Event_Function_Return); // auto reset events with non-signaled state as default

		//DWORD* piIndex = reinterpret_cast<DWORD*>(pIndex);

		//*piIndex = 4;

		//HANDLE hSendingEvent = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, Event_Function_Call);
		//if(hSendingEvent) ::SetEvent(hSendingEvent);

		//::WaitForSingleObject(hRetrievingEvent, INFINITE);
		//TCHAR* szValue = (TCHAR*)pData;
		//_tprintf(szValue);

	}

	return nRetCode;
}
