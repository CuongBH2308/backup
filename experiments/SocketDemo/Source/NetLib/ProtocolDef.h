#pragma once

//	COMMANDS
#define CMD_ADD		'+'
#define CMD_SUB		'-'
#define CMD_MUL		'*'
#define CMD_DIV		'/'
#define CMD_AUTO	0x0011
#define CMD_REPLY	0x8000

//	ERROR CODES
#define ERR_OK		0x0000
#define ERR_FORMAT	0x8001
#define ERR_DIV0	0x8002
#define ERR_CMD		0x8003
#define ERR_UNKNOWN	0xffff

#pragma pack(push, 1)			//	Byte align

//	HEADER
typedef struct
{
	unsigned short	len;		//	length
	unsigned short	cmd;		//	command
	unsigned short	status;		//	status (error code)
	unsigned long	sn;			//	serial number
	unsigned char	crc;		//	crc
}HEADER;

typedef struct tagPacket : HEADER
{
	unsigned char	body[1];	//	body goes here
}*PACKET;

//	BODIES
typedef struct
{
	long	a;
	long	b;
}ARITHMETICS_BODY;

typedef struct
{
	char str[1];				//	ending with '\0'
}MESSAGE;

typedef struct
{
	long	m;
}ARITHMETICS_REPLY_BODY;

#pragma pack(pop)				//	Restore the align mode
