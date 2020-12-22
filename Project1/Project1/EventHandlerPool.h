#pragma	once


#include <ace/Acceptor.h>
#include "Event.h"


typedef void(*funHnadler)(ServerProcessEvent *e);

// 创建 消息事件
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
	funHnadler m_arrFunHandler[EventID_MAX];		// 保持根据 事件ID 调用对应处理函数
	fpCreateClass m_arrFunMessage[EventID_MAX];		// 保存根据 事件ID 创建对应的 协议包
};
typedef ACE_Singleton<EventHandlerPool, ACE_Null_Mutex> App_EventHandlerPool;