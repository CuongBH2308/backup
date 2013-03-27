#pragma once

#include "DataSocket.h"
#include "../NetLib/Protocol.h"

class Server : public IDataEvent
{
private:
	Server(void);
	~Server(void);

public:
	static Server& get();

public:
	virtual void on_packet(CDataSocket* from, const PACKET p);

private:
	long calc(unsigned short alrithm, const ARITHMETICS_BODY* p);

private:
	Protocol m_protocol;
};
