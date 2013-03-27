#pragma once
#include <map>
#include <string>

typedef void (*FuncType)(void* );

class IPCInvoker
{
public:

	static bool ClientInvoke(char* szIndex);
	static bool ServerDispatch();


	static void ExitServer(void* pPara);

	static bool m_bExit;

	static std::map<std::string, FuncType>& DispatchMap();
};



// Register
class FuncRegister
{
public:
	FuncRegister(const std::string& strIndex, FuncType pFunc);
};

#define REGISTER_FUNC(func) \
	static FuncRegister register_##func(std::string(#func), func);