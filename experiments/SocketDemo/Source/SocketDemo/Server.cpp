#include "StdAfx.h"
#include "Server.h"
#include "../NetLib/ProtocolDef.h"

#pragma comment(lib, "../Debug/NetLib.lib")

Server::Server(void)
{
}

Server::~Server(void)
{
}

//static
Server& Server::get()
{
	static Server theServer;
	return theServer;
}

void Server::on_packet(CDataSocket *from, const PACKET p)
{
	PACKET ret = NULL;

	if (!Protocol::text_crc(p))
	{	//	bad format
		ret = m_protocol.reply_err(p, ERR_FORMAT);
	}
	else
	{
		switch (p->cmd)
		{
		case CMD_ADD:
		case CMD_SUB:
		case CMD_MUL:
		case CMD_DIV:
			//	body must be valid
			if (p->len < sizeof(HEADER) + sizeof(ARITHMETICS_BODY))
			{	//	bad format
				ret = m_protocol.reply_err(p, ERR_FORMAT);
			}
			else
			{
				//	body
				ARITHMETICS_BODY* body = (ARITHMETICS_BODY*)p->body;
				long m = calc(p->cmd, body);
				ret = m_protocol.reply_arithmetics(p, m);
			}
			break;

		case CMD_AUTO:
			ret = m_protocol.reply_message(p, (const char*)(p->body));
			break;

		default:
			ret = m_protocol.reply_err(p, ERR_CMD);
		}
	}
	if (ret != NULL)
	{
		from->send_packet(ret);
		m_protocol.free_packet(ret);
	}
}

long Server::calc(unsigned short alrithm, const ARITHMETICS_BODY *p)
{
	long ret = 0;

	switch (alrithm)
	{
	case CMD_ADD:
		ret = p->a + p->b;
		break;
		
	case CMD_SUB:
		ret = p->a - p->b;
		break;

	case CMD_MUL:
		ret = p->a * p->b;
		break;

	case CMD_DIV:
		ret = p->a / p->b;
		break;
	}

	return ret;
}
