#include "stdafx.h"
#include "ProxyStub.h"

void ProxyStub::Package(DWORD data, void*& pDataPool)
{
	DWORD* pData = static_cast<DWORD*>(pDataPool);
	*pData = data;

	pDataPool = static_cast<void*>(pData + 1);
}

void ProxyStub::UnPackage(void*& pDataPool, DWORD& data)
{
	DWORD* pData = static_cast<DWORD*>(pDataPool);
	data = *pData;

	pDataPool = static_cast<void*>(pData + 1);
}

void ProxyStub::Package(const tstring& data, void*& pDataPool)
{
	TCHAR* pData = static_cast<TCHAR*>(pDataPool);
	_tcscpy(pData, data.c_str());

	pDataPool = static_cast<void*>(pData + data.length() + 1);

}

void ProxyStub::UnPackage(void*& pDataPool, tstring& data)
{
	TCHAR* pData = static_cast<TCHAR*>(pDataPool);
	data = pData;

	pDataPool = static_cast<void*>(pData + data.length() + 1);

}