#include "stdafx.h"
#include "IPCStrategy.h"

class IPCFileMappingStrategy: public IPCStrategy
{
public:
	virtual void* GetIndexData()
	{
		HANDLE hIndex = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, Index_Size, m_strIndexFileMapping);
		LPVOID pData = ::MapViewOfFile(hIndex, FILE_MAP_ALL_ACCESS, 0, 0, Index_Size);
		return pData;
	}

	virtual void* GetInputData()
	{
		HANDLE hInput = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, Input_Size, m_strInputFileMapping);
		LPVOID pData = ::MapViewOfFile(hInput, FILE_MAP_ALL_ACCESS, 0, 0, Input_Size);
		return pData;
	}

	virtual void* GetOutputData()
	{
		HANDLE hOutput = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, Output_Size, m_strOutputFileMapping);
		LPVOID pData = ::MapViewOfFile(hOutput, FILE_MAP_ALL_ACCESS, 0, 0, Output_Size);
		return pData;
	}

private:
	static const DWORD Index_Size = 256;
	static const DWORD Input_Size = 16 * 1024 * 1024;
	static const DWORD Output_Size = 16 * 1024 * 1024;

	static TCHAR* m_strIndexFileMapping;
	static TCHAR* m_strInputFileMapping;
	static TCHAR* m_strOutputFileMapping;
};

TCHAR* IPCFileMappingStrategy::m_strIndexFileMapping = _T("GUID_Index_FileMapping");
TCHAR* IPCFileMappingStrategy::m_strInputFileMapping = _T("GUID_Input_FileMapping");
TCHAR* IPCFileMappingStrategy::m_strOutputFileMapping = _T("GUID_Output_FileMapping");


IPCStrategy* IPCStrategyFactory::IPCStrategies[kIPCTypeCount] = {NULL};

IPCStrategy* IPCStrategyFactory::GetIPCStrategy(IPCTypeEnum eIPCType)
{
	if(IPCStrategies[eIPCType] == NULL)
	{
		IPCStrategy* pStrategy = NULL;
		switch (eIPCType)
		{
		case kFileMappingType: 
			pStrategy = new IPCFileMappingStrategy;
			break;

		default:
			assert(false);
		}

		IPCStrategies[eIPCType] = pStrategy;
	}

	return IPCStrategies[eIPCType];
}

IPCStrategy* IPCStrategyFactory::GetActiveIPCStrategy()
{
	return IPCStrategyFactory::GetIPCStrategy(kFileMappingType);
}
