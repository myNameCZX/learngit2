#include "EventHandlerPool.h"
#include "messageHandler.h"

#include <iostream>
#include "Event.h"

using namespace std;
void messageHandler::OnLoginEvent(ServerProcessEvent* e)
{
	LoginEvent*et =	dynamic_cast<LoginEvent*>(e);

	if (nullptr != et){

		cout << "name=" << et->m_sName << endl;




		// ����һ����Ϣ��xx
		et->m_sName;
		et->send();
	}
}