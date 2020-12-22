#include "Event.h"
#include "server.h"
#include "define.h"

ServerProcessEvent::ServerProcessEvent()
{
}

void ServerProcessEvent::SetEventID(unsigned short eventID)
{
	this->m_u2EventID = eventID;
}

unsigned short ServerProcessEvent::GetEventID()
{
	return m_u2EventID;
}

void ServerProcessEvent::SetConnectID(int nConnectID)
{
	this->m_nConnectID = nConnectID;
}
int ServerProcessEvent::GetConnectID()
{
	return m_nConnectID;
}

CBuffPacket* ServerProcessEvent::WritePacket()
{
	return 0;
}

void ServerProcessEvent::send()
{
	CBuffPacket*p = this->WritePacket();
	App_ServerManager::instance()->Send(m_nConnectID, p->GetBlock());
	SAFE_DELETE(p);
}

void LoginEvent::SetPacet(CBuffPacket *pBuffPacket)
{
	(*pBuffPacket) >> m_sName;
}

void LoginEvent::clear()
{
	this->m_sName.clear();
}

CBuffPacket* LoginEvent::WritePacket()
{
	CBuffPacket*p = new CBuffPacket();
	(*p) << m_sName;

	return p;
}