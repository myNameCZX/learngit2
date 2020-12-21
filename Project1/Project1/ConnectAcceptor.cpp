#include "ConnectAcceptor.h"

int ConnectAcceptor::make_svc_handler(Server_svc_handler*& sh)
{
	ACE_DEBUG((LM_ERROR, "[ConnectAcceptor::make_svc_handler]Connect is more MaxHandlerCoun.\n"));
	sh = new Server_svc_handler();
	sh->reactor(this->reactor());

	return 0;
}
