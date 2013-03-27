// DataSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SocketDemo.h"
#include "DataSocket.h"
#include "../NetLib/Protocol.h"


// CDataSocket

CDataSocket::CDataSocket(IDataEvent* pEventSink)
	: m_buf_len(0)
	, m_pEventSink(pEventSink)
{
}

CDataSocket::~CDataSocket()
{
}

void CDataSocket::send_packet(PACKET p)
{
	Send(p, p->len);	//	TODO: we should check the return value to determine whether the packet is wholely sent, or just partial is sent
}

// CDataSocket member functions
void CDataSocket::OnReceive(int nErrorCode)
{
	try_receive();
}

void CDataSocket::try_receive()
{
	int n = Receive(m_buf + m_buf_len, 1024 - m_buf_len);
	if (n > 0)
	{
		m_buf_len += n;
		//	check if any available packets in the queue
		check_packets();
	}
}

void CDataSocket::check_packets()
{
	int off = 0;
	int n = 0;
	while (n = Protocol::test_packet(m_buf + off, m_buf_len - off) > 0)
	{
		m_pEventSink->on_packet(this, (const PACKET)(m_buf + off));
		off += n;
	}
}
