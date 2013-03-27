#pragma once

class CallSynchronizer
{
public:
	static bool Call();
	static bool Return();

	static bool IsCalled();
	static bool IsReturned();

private:
	static TCHAR* m_strCallEvent;
	static TCHAR* m_strReturnEvent; 
};