#include "stdafx.h"
#include "CallSynchronizer.h"

TCHAR* CallSynchronizer::m_strCallEvent = _T("GUID_Call_Event");
TCHAR* CallSynchronizer::m_strReturnEvent = _T("GUID_Return_Event"); 

bool CallSynchronizer::Call()
{
	HANDLE hCallEvent = ::CreateEvent(NULL, FALSE, FALSE, m_strCallEvent);
	assert(hCallEvent);

	DWORD dwErr = ::GetLastError();
	assert(ERROR_ALREADY_EXISTS == dwErr && "Check if Server is started!!!");

	bool bRet = false;
	if(hCallEvent) bRet = !!::SetEvent(hCallEvent);

	return bRet;
}

bool CallSynchronizer::Return()
{
	HANDLE hReturnEvent = ::CreateEvent(NULL, FALSE, FALSE, m_strReturnEvent);
	assert(hReturnEvent);

	bool bRet = false;
	if(hReturnEvent) bRet = !!::SetEvent(hReturnEvent);

	return bRet;
}

bool CallSynchronizer::IsCalled()
{
	HANDLE hCallEvent = ::CreateEvent(NULL, FALSE, FALSE, m_strCallEvent);
	assert(hCallEvent);

	DWORD dwErr = ::WaitForSingleObject(hCallEvent, INFINITE);
	assert(WAIT_OBJECT_0 == dwErr);

	return WAIT_OBJECT_0 == dwErr;
}


bool CallSynchronizer::IsReturned()
{
	HANDLE hReturnEvent = ::CreateEvent(NULL, FALSE, FALSE, m_strReturnEvent);
	assert(hReturnEvent);

	DWORD dwErr = ::WaitForSingleObject(hReturnEvent, INFINITE);
	assert(WAIT_OBJECT_0 == dwErr);

	return WAIT_OBJECT_0 == dwErr;
}
