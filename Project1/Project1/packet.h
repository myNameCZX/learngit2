#pragma once
#include "ace/Message_Block.h"

// ���ܿͻ��˵���Ϣ ������һ���������¼�
struct Packet
{
	int		m_nConnectID;
	int		m_nEventID;
	ACE_Message_Block	*m_pBlock;

	Packet() :
		m_nConnectID(0),
		m_nEventID(0)
	{
		m_pBlock = NULL;
	}
};