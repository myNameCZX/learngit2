
#pragma once
#include <iostream>
#include <ace/INET_Addr.h> 
#include <ace/SOCK_Stream.h>  
#include <ace/SOCK_Acceptor.h> 
#include <ace/Acceptor.h>
#include <ace/Svc_Handler.h>
#include <ace/ace.h>
#include "server.h"

using namespace std;


class Server_svc_handler;
class ConnectAcceptor : public ACE_Acceptor<Server_svc_handler, ACE_SOCK_ACCEPTOR>
{
public:

	virtual int make_svc_handler(Server_svc_handler*& sh);

	//int open2(ACE_INET_Addr& local_addr,ACE_Reactor* reactor);


	//int start(const ACE_INET_Addr& addr);
};