#pragma once

#include "ace/Log_Msg.h"
#include "ace/Task.h"
#include "ace/OS.h"
#include "ace/Message_Block.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include "sstream"
#include "packet.h"
#include <queue>
using namespace std;



class ConsumerTask:public ACE_Task<ACE_MT_SYNCH>
{
public:
	virtual int open(void);

	virtual int svc();

	void AddTTask(ACE_Message_Block * bk);

	void AddTask(Packet &t);
private:
	queue<Packet>	m_qMsg;
};