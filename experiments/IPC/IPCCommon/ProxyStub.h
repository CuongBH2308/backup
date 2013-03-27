#pragma once
#include <string>

typedef std::basic_string<TCHAR> tstring;

class ProxyStub
{
public:
	static void Package(DWORD data, void*& pDataPool);
	static void UnPackage(void*& pDataPool, DWORD& data);

	static void Package(const tstring& data, void*& pDataPool);
	static void UnPackage(void*& pDataPool, tstring& data);
};