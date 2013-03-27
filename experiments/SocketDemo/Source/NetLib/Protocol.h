#pragma once

#include "ProtocolDef.h"

class Protocol
{
public:
	Protocol(void);
	~Protocol(void);

public:
	PACKET	arithmetics(long a, long b, unsigned short op);
	PACKET	message(const char* msg);
	
	PACKET	reply_arithmetics(const PACKET src, long ret);
	PACKET	reply_message(const PACKET src, const char* msg);
	PACKET	reply_err(const PACKET src, unsigned short err_code);

	static void free_packet(PACKET p);
	
	//	test if a packet available in the buf, if yes, then return the packet length,
	//	otherwise, return 0
	static int test_packet(const unsigned char* buf, int buf_len);

public:
	//	CRC
	static void fix_crc(PACKET p);
	static bool text_crc(const PACKET p);

private:
	PACKET	alloc(unsigned short body_len);

	PACKET	create(unsigned short cmd, void* body, unsigned short body_len);

	PACKET	reply(const PACKET src, void* body, unsigned short body_len);

private:
	inline unsigned long get_next_sn()	{ return m_next_sn++;	}

private:
	static unsigned char calc_crc(const PACKET p);

private:
	unsigned long m_next_sn;
};
