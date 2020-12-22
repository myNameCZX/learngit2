#pragma	once


#include <ace/Acceptor.h>
#include "Event.h"


typedef void(*funHnadler)(ServerProcessEvent *e);

// ���� ��Ϣ�¼�
typedef ServerProcessEvent* (*fpCreateClass)();


//==============================================================
template<class T>
class CreateServerProcessEvent
{
public:
	static ServerProcessEvent* Create();

protected:
private:
};

template<class T>
ServerProcessEvent* CreateServerProcessEvent<T>::Create()
{
	return (ServerProcessEvent*)(new T());
}
//==========================================================

class EventHandlerPool
{
public:
	EventHandlerPool();

	void RegEventHandler(unsigned short eventID, funHnadler fp, fpCreateClass fun);
	funHnadler GetHandler(unsigned short eventID);

	ServerProcessEvent* CreateServerEvent(unsigned short eventID);
	void Init();
private:
	funHnadler m_arrFunHandler[EventID_MAX];		// ���ָ��� �¼�ID ���ö�Ӧ������
	fpCreateClass m_arrFunMessage[EventID_MAX];		// ������� �¼�ID ������Ӧ�� Э���
};
typedef ACE_Singleton<EventHandlerPool, ACE_Null_Mutex> App_EventHandlerPool;