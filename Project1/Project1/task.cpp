#include "task.h"

int ConsumerTask::open(void)
{
	ACE_DEBUG((LM_DEBUG, "open"));
	activate(THR_NEW_LWP, 1);
	return 0;
}

int ConsumerTask::svc()
{
	do
	{
		ACE_Message_Block* msg = NULL;
		if (!this->msg_queue()->is_empty())
		{
			this->getq(msg);
			ACE_DEBUG((LM_DEBUG, "%s\n", msg->rd_ptr()));

			int a = atoi(msg->rd_ptr());
			if (1 == a){
				
			}

			msg->release();
		}
	} while (true);
	return 0;
}

void ConsumerTask::AddTTask(ACE_Message_Block * bk)
{
	this->putq(bk);
}