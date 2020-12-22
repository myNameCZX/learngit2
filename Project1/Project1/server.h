#pragma once

#include <iostream>
#include <ace/INET_Addr.h> 
#include <ace/SOCK_Stream.h>  
#include <ace/SOCK_Acceptor.h> 
#include <ace/Acceptor.h>
#include <ace/Svc_Handler.h>

#include<map>

using namespace std;

class Server_svc_handler : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:
	Server_svc_handler();
	~Server_svc_handler();

	int open(void* );

	int handle_input(ACE_HANDLE);

	int Analyze();

	void Send(ACE_Message_Block* pData);
public:
	static const int DATA_SIZE;
	int m_iConnect;

	ACE_Message_Block*         m_pCurrMessage;                 //读出来的数据保持
	ACE_Message_Block*         m_pRecvMessage;                 //读时候的临时对象
};


class ServerManager : public ACE_Task<ACE_MT_SYNCH>
{
public:
	virtual int open(void* args = 0);
	virtual int svc(void);

	int AddConnect(Server_svc_handler* p);

	void Send(int nConnectID, ACE_Message_Block* pData);
private:
	map<int, Server_svc_handler*> m_mConnectManager;

	int m_iConnect;
};

typedef ACE_Singleton<ServerManager, ACE_Null_Mutex> App_ServerManager;