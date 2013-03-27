#pragma once

// CNetListener command target

class CNetListener : public CAsyncSocket
{
public:
	CNetListener();
	virtual ~CNetListener();

protected:
	virtual void OnAccept(int nErrorCode);
};
