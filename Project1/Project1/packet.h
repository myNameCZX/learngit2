#pragma once
#include "ace/Message_Block.h"

// 接受客户端的消息 解析成一个完整的事件
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