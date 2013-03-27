#pragma once

#include "ProtocolDef.h"

class CDataSocket;

//	interface class
class IDataEvent
{
public:
	virtual void on_packet(CDataSocket* from, const PACKET p) = 0;
};

// CDataSocket command target

class CDataSocket : public CAsyncSocket
{
public:
	CDataSocket(IDataEvent* pEventSink);
	virtual ~CDataSocket();

public:
	void	send_packet(PACKET p);

protected:
	void	try_receive();
	void	check_packets();

protected:
	virtual void OnReceive(int nErrorCode);

private:
	unsigned char	m_buf[1024];
	int		m_buf_len;

private:
	IDataEvent*	m_pEventSink;
};

