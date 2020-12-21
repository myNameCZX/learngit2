#include "server.h"
#include "task.h"
#include <map>
#include <stdio.h>
#include <iostream>
extern ConsumerTask g_task;

const int Server_svc_handler::DATA_SIZE = 64;

Server_svc_handler::Server_svc_handler()
{
	data = new char[DATA_SIZE];
}

int Server_svc_handler::open(void* )
{
	ACE_DEBUG((LM_DEBUG, "connect!"));
	char* msg = "client connected sucessfully in server";
	ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK); //注册socket上可读事件的处理器，当当前的socket上有可读事件时，就会触发这个handler的handle_input方法
	peer().send(msg, strlen(msg));

	ACE_INET_Addr m_addrRemote;
	if (this->peer().get_remote_addr(m_addrRemote) != -1){

		ACE_DEBUG((LM_DEBUG, "%s,:%d\n", m_addrRemote.get_host_addr(), m_addrRemote.get_port_number()));
	}

	
	m_iConnect = App_ServerManager::instance()->AddConnect(this);

	m_pCurrMessage = new ACE_Message_Block(DATA_SIZE);
	ACE_DEBUG((LM_INFO, " msg=%s\n", m_pCurrMessage->rd_ptr()));
	return 0;
}


string ByteStream2String(char  *pByteStream, size_t iStreamLen)
{
	std::string sRet = "";
	char curr_byte[3];
	
	for (size_t idx = 0; idx < iStreamLen; ++idx)
	{
	    memset(curr_byte, 0, 3);
		sprintf_s(curr_byte, "%02hhX", pByteStream[idx]);

		sRet += curr_byte;
	    sRet += " ";
	 }
	
	return sRet;
}

int Server_svc_handler::handle_input(ACE_HANDLE fd)
{

	// 异常了不做处理
	if (ACE_INVALID_HANDLE == fd) return 0;

	memset(data, 0, DATA_SIZE);
	m_pCurrMessage = new ACE_Message_Block(DATA_SIZE);
	int nRecvSize = m_pCurrMessage->size() - m_pCurrMessage->length();	// m_pCurrMessage 该对象剩余的空间

	ssize_t cnt = peer().recv(m_pCurrMessage->wr_ptr(), nRecvSize);
	if (cnt <= 0){
		cout << "NO data received" << endl;
	}
	else{
		ACE_DEBUG((LM_INFO, "begin msg=%s\n", m_pCurrMessage->rd_ptr()));
		m_pCurrMessage->wr_ptr(cnt); // 空间占用
		
		uint16_t eventID = 0;
		uint16_t bodylength = 0;
		memcpy(&eventID, m_pCurrMessage->rd_ptr(), sizeof(uint16_t));
		m_pCurrMessage->rd_ptr(sizeof(uint16_t));

		memcpy(&bodylength, m_pCurrMessage->rd_ptr(), sizeof(uint16_t));
		m_pCurrMessage->rd_ptr(sizeof(uint16_t));

		uint16_t stringSize = 0;
		memcpy(&stringSize, m_pCurrMessage->rd_ptr(), sizeof(uint16_t));
		m_pCurrMessage->rd_ptr(sizeof(uint16_t));

		char p[1024] = "\0";
		memset(p, 0, 1023);
		memcpy(&p, m_pCurrMessage->rd_ptr(), stringSize);
		string str((char*)m_pCurrMessage->rd_ptr(), stringSize);

		//memcpy(p, pData + 3 * sizeof(uint16_t), stringSize); 
		//string ff = ByteStream2String(p, stringSize);
		cout << "p=" << str << endl;
		//ACE_DEBUG((LM_INFO, "%d, recvSize=%d， msg=%s, length=%d,eventid=%d\n", fd, cnt, m_pCurrMessage->rd_ptr(), (int)m_u2PacketCommandID, (int)eventID));

		ACE_Message_Block* mb = new ACE_Message_Block(DATA_SIZE);
		//mb->copy(data);
		//g_task.AddTTask(mb);
	}

	return 0;
}

int ServerManager::open(void* args)
{
	m_iConnect = 0;
	activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED | THR_SUSPENDED, 1);
	return 0;
}


int ServerManager::svc(void)
{

	return 0;
}

int  ServerManager::AddConnect(Server_svc_handler* p)
{
	++m_iConnect;

	this->m_mConnectManager.insert(make_pair(m_iConnect, p));
	return m_iConnect;
}