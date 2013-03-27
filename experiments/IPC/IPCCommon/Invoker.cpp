#include "stdafx.h"
#include "Invoker.h"
#include "IPCStrategy.h"
#include "CallSynchronizer.h"

using namespace std;

bool IPCInvoker::m_bExit = false;

std::map<std::string, FuncType>& IPCInvoker::DispatchMap()
{
	static std::map<std::string, FuncType> m_mapDispatch;
	return m_mapDispatch;
}

bool IPCInvoker::ClientInvoke(char* szIndex)
{
	// Set index to indicate which function to call
	void* pIndex = IPCStrategyFactory::GetActiveIPCStrategy()->GetIndexData();
	char* szShareIndex = static_cast<char*>(pIndex);
	strcpy(szShareIndex, szIndex);

	// Start to call the function in Server process
	CallSynchronizer::Call();

	// Wait until server finished
	bool bSucceeded = CallSynchronizer::IsReturned();
	assert(bSucceeded);

	// returned data already store in OutputData
	return bSucceeded;

}

bool IPCInvoker::ServerDispatch()
{
	m_bExit = false;
	while(!m_bExit)
	{
		// Client is calling
		if(CallSynchronizer::IsCalled())
		{
			// Get the function index
			void* pIndex = IPCStrategyFactory::GetActiveIPCStrategy()->GetIndexData();
			char* szShareIndex = static_cast<char*>(pIndex);
			string strIndex = szShareIndex;


			// Dispatch the call
			std::map<string, FuncType>::iterator it = DispatchMap().find(strIndex);
			assert(it != DispatchMap().end());

			if(it != DispatchMap().end())
			{
				void* pPara = IPCStrategyFactory::GetActiveIPCStrategy()->GetInputData();
				it->second(pPara);
			}

			CallSynchronizer::Return();
		}
	}

	return true;
}

void IPCInvoker::ExitServer(void* pPara)
{
	m_bExit = true;
}


FuncRegister::FuncRegister(const string& strIndex, FuncType pFunc)
{
	// assert not exist.
	IPCInvoker::DispatchMap()[strIndex] = pFunc;
}

