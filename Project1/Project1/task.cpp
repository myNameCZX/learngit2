#include "task.h"
#include "EventHandlerPool.h"
#include "CBuffPacket.h"
#include "define.h"

int ConsumerTask::open(void)
{
	ACE_DEBUG((LM_DEBUG, "open"));
	activate(THR_NEW_LWP, 1);
	return 0;
}

int ConsumerTask::svc()
{
	while (true){

		if (!this->m_qMsg.empty()){

			Packet tPacket = this->m_qMsg.front();

			CBuffPacket* pPacket = new CBuffPacket();
			pPacket->WriteStream(tPacket.m_pBlock->rd_ptr(), tPacket.m_pBlock->length());

			ServerProcessEvent *e = App_EventHandlerPool::instance()->CreateServerEvent(tPacket.m_nEventID);

			e->clear();
			e->SetConnectID(tPacket.m_nConnectID);
			e->SetEventID(tPacket.m_nEventID);
			e->SetPacet(pPacket);

			funHnadler eventHandler = App_EventHandlerPool::instance()->GetHandler(tPacket.m_nEventID);
			eventHandler(e);

			tPacket.m_pBlock->release();
			this->m_qMsg.pop();

			SAFE_DELETE(e);
			SAFE_DELETE(pPacket);
		}

	}
	return 0;
}

void ConsumerTask::AddTTask(ACE_Message_Block * bk)
{
	this->putq(bk);
}

void ConsumerTask::AddTask(Packet &t)
{
	this->m_qMsg.push(t);
}