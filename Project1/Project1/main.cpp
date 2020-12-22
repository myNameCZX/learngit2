#include <iostream>
#include <ace/INET_Addr.h> 
#include <ace/SOCK_Stream.h>  
#include <ace/SOCK_Acceptor.h> 
#include <ace/Acceptor.h>
#include <ace/Svc_Handler.h>
#include "server.h"
#include "task.h"
#include "ConnectAcceptor.h"
#include "EventHandlerPool.h"

using namespace std;

ConsumerTask g_task;


int main(int argc, char* argv[])
{
	ACE_DEBUG((LM_DEBUG, "Test server running...\n"));
	const int PORT_NUM = 12345;
	ACE_INET_Addr addr(PORT_NUM);
	// ��ÿ���ͻ������ӳɹ�������һ��Server_svc_handler ����,������.open(),ÿ���յ���Ϣ����handle_input
	//ServerAcceptor acceptor(addr, ACE_Reactor::instance());

	// ע����Ϣ
	App_EventHandlerPool::instance()->Init();

	ConnectAcceptor accep;
	accep.open(addr, ACE_Reactor::instance());
	//accep.start(addr);

	g_task.open();

	App_ServerManager::instance()->open();

	//ACE_Thread_Manager::instance()->wait();
	ACE_Reactor::instance()->owner(ACE_OS::thr_self());
	ACE_Reactor::instance()->run_reactor_event_loop();
	//ACE_Reactor::run_event_loop(); //��һֱ��ͣ�ļ���ע����¼���
	return 0;
}