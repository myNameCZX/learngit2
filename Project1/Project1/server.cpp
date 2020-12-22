#include "server.h"
#include "task.h"
#include <map>
#include <stdio.h>
#include <iostream>
#include "packet.h"

extern ConsumerTask g_task;

const int Server_svc_handler::DATA_SIZE = 2048;

Server_svc_handler::Server_svc_handler()
{
}

Server_svc_handler::~Server_svc_handler()
{
	m_pRecvMessage->release();
	m_pCurrMessage->release();
}


int Server_svc_handler::open(void* )
{
	ACE_DEBUG((LM_DEBUG, "connect!"));

	ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK); //注册socket上可读事件的处理器，当当前的socket上有可读事件时，就会触发这个handler的handle_input方法

	ACE_INET_Addr m_addrRemote;
	if (this->peer().get_remote_addr(m_addrRemote) != -1){

		ACE_DEBUG((LM_DEBUG, "%s,:%d\n", m_addrRemote.get_host_addr(), m_addrRemote.get_port_number()));
	}

	m_iConnect = App_ServerManager::instance()->AddConnect(this);

	m_pRecvMessage = new ACE_Message_Block(DATA_SIZE/2);
	m_pCurrMessage = new ACE_Message_Block(DATA_SIZE);

	return 0;
}

int Server_svc_handler::handle_input(ACE_HANDLE fd)
{
	// 异常了不做处理
	if (ACE_INVALID_HANDLE == fd
		|| NULL == m_pRecvMessage
		|| NULL == m_pCurrMessage){
		return -1;
	}

	m_pRecvMessage->reset();
	ssize_t cnt = peer().recv(m_pRecvMessage->wr_ptr(), m_pRecvMessage->space());

	if (cnt > 0){
		m_pRecvMessage->wr_ptr(cnt);

		memcpy(m_pCurrMessage->wr_ptr(), m_pRecvMessage->rd_ptr(), cnt);
		m_pCurrMessage->wr_ptr(cnt);

		return Analyze();
	}
	else{
		cout << "NO data received\n" << endl;
		return -1;
	}

	return 0;
}

int Server_svc_handler::Analyze()
{
	if (NULL == m_pCurrMessage) return -1;

	// 判断包的完整性
	uint16_t bodylength = 0;
	memcpy(&bodylength, m_pCurrMessage->rd_ptr() + sizeof(uint16_t), sizeof(uint16_t));
	if (bodylength<4 || bodylength>(100*DATA_SIZE)){
		// 长度异常
		return -1;
	}	

	if (m_pCurrMessage->length() >= bodylength){
		// 包完整

		uint16_t eventID = 0;
		uint16_t bodyLength = 0;
		memcpy(&eventID, m_pCurrMessage->rd_ptr(), sizeof(uint16_t));
		m_pCurrMessage->rd_ptr(sizeof(uint16_t));
		memcpy(&bodyLength, m_pCurrMessage->rd_ptr(), sizeof(uint16_t));
		m_pCurrMessage->rd_ptr(sizeof(uint16_t));
		
		bodyLength -= 4;

		// 包事件
		Packet packet;
		packet.m_nConnectID = m_iConnect;
		packet.m_nEventID = eventID;
		packet.m_pBlock = new ACE_Message_Block(bodyLength);
		if (NULL == packet.m_pBlock){
			return -1;
		}

		memcpy(packet.m_pBlock->wr_ptr(), m_pCurrMessage->rd_ptr(), bodyLength);
		packet.m_pBlock->wr_ptr(bodyLength);

		m_pCurrMessage->rd_ptr(bodyLength);

		// 重置包大小，防止包因为粘包，无限膨胀
		ACE_Message_Block*  p = new ACE_Message_Block(DATA_SIZE + m_pCurrMessage->length());
		if (NULL == p){
			// 异常
			return -1;
		}
		if (m_pCurrMessage->length() > 0){
			memcpy(p->wr_ptr(), m_pCurrMessage->rd_ptr(), m_pCurrMessage->length());
			p->wr_ptr(m_pCurrMessage->length());
		}
		m_pCurrMessage->release();
		m_pCurrMessage = p;

		g_task.AddTask(packet);
	}
	else{
		// 断包
		if ((m_pCurrMessage->length() + m_pCurrMessage->space()) < bodylength){
			m_pCurrMessage->size(bodylength+1);
		}
	}

	return 0;
}

void Server_svc_handler::Send(ACE_Message_Block* pData)
{
	peer().send(pData->rd_ptr(),pData->length());
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

void ServerManager::Send(int nConnectID, ACE_Message_Block* pData)
{
	map<int, Server_svc_handler*>::const_iterator it = m_mConnectManager.find(nConnectID);
	if (it != m_mConnectManager.end()){
		it->second->Send(pData);
	}
}