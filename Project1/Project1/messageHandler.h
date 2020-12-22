#pragma  once

#include <ace/Acceptor.h>
#include "Event.h"

class messageHandler
{
public:
	static void OnLoginEvent(ServerProcessEvent* e);
};