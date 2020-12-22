#include "EventHandlerPool.h"
#include "messageHandler.h"

EventHandlerPool::EventHandlerPool()
{
}

void EventHandlerPool::RegEventHandler(unsigned short eventID, funHnadler fp, fpCreateClass fun)
{
	m_arrFunHandler[eventID] = fp;
	m_arrFunMessage[eventID] = fun;
}

funHnadler EventHandlerPool::GetHandler(unsigned short eventID)
{
	if (eventID >= EventID_MAX){
		
		return 0;
	}
	return m_arrFunHandler[eventID];
}

ServerProcessEvent* EventHandlerPool::CreateServerEvent(unsigned short eventID)
{
	// 相当于调用  CreateServerProcessEvent<LoginEvent>::Create()
	return m_arrFunMessage[eventID]();
}

void EventHandlerPool::Init()
{
	RegEventHandler(LoginEveintID, messageHandler::OnLoginEvent, CreateServerProcessEvent<LoginEvent>::Create);
}