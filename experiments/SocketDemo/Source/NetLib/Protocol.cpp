#include "StdAfx.h"
#include "Protocol.h"

Protocol::Protocol(void)
	: m_next_sn(1)
{
}

Protocol::~Protocol(void)
{
}

PACKET Protocol::arithmetics(long a, long b, unsigned short op)
{
	ARITHMETICS_BODY body = { a, b };
	return create(op, &body, sizeof(body));
}

PACKET Protocol::message(const char *msg)
{
	MESSAGE* p = (MESSAGE*)msg;
	return create(CMD_AUTO, p, ::strlen(msg) + 1);
}

PACKET Protocol::reply_arithmetics(const PACKET src, long ret)
{
	ARITHMETICS_REPLY_BODY body = { ret };
	return reply(src, &body, sizeof(body));
}

PACKET Protocol::reply_message(const PACKET src, const char *msg)
{
	MESSAGE* p = (MESSAGE*)msg;
	return reply(src, p, ::strlen(msg) + 1);
}

PACKET Protocol::reply_err(const PACKET src, unsigned short err_code)
{
	PACKET p = alloc(0);
	p->cmd = CMD_REPLY;
	p->status = err_code;
	p->sn = src->sn;
	fix_crc(p);
	return p;
}

PACKET Protocol::alloc(unsigned short body_len)
{
	PACKET p = (PACKET)new unsigned char[sizeof(HEADER) + body_len];
	p->len = sizeof(HEADER) + body_len;
	return p;
}

PACKET Protocol::create(unsigned short cmd, void *body, unsigned short body_len)
{
	PACKET p = alloc(body_len);
	p->cmd = cmd;
	p->status = ERR_OK;
	p->sn = get_next_sn();
	//	body
	if (body_len > 0)	::memcpy(p->body, body, body_len);
	//	crc
	fix_crc(p);
	return p;
}

PACKET Protocol::reply(const PACKET src, void *body, unsigned short body_len)
{
	PACKET p = alloc(body_len);
	p->cmd = CMD_REPLY;
	p->status = ERR_OK;
	p->sn = src->sn;
	//	copy body
	if (body_len > 0)	::memcpy(p->body, body, body_len);
	//	crc
	fix_crc(p);
	return p;
}

//static
void Protocol::free_packet(PACKET p)
{
	delete [](unsigned char*)p;
}

//static
int Protocol::test_packet(const unsigned char* buf, int buf_len)
{
	//	at least, the packet's length must >= header length
	if (buf_len < sizeof(HEADER))	return 0;
	PACKET p = (PACKET)buf;
	if (p->len <= buf_len)	return p->len;
	return 0;
}

//static
void Protocol::fix_crc(PACKET p)
{
	p->crc = 0;
	p->crc = calc_crc(p);
}

//static
bool Protocol::text_crc(const PACKET p)
{
	unsigned char crc = calc_crc(p);
	unsigned char t = p->crc << 1;
	return crc == t;
}

//static
unsigned char Protocol::calc_crc(const PACKET p)
{
	unsigned char crc = 0;

	const char* stm = (const char*)p;
	unsigned short i = 0;
	while (i < p->len) crc += stm[i++];
	
	return crc;
}
