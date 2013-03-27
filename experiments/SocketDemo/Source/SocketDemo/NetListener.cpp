// NetListener.cpp : implementation file
//

#include "stdafx.h"
#include "SocketDemo.h"
#include "NetListener.h"
#include "DataSocket.h"
#include "Server.h"

// CNetListener

CNetListener::CNetListener()
{
}

CNetListener::~CNetListener()
{
}


// CNetListener member functions
void CNetListener::OnAccept(int nErrorCode)
{
	CDataSocket* sock = new CDataSocket(&Server::get());		//	TODO: we should delete this object when the socket is closed
	Accept(*sock);
}
