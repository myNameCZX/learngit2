#pragma once


#include "CBuffPacket.h"

enum EventID_
{
	LoginEveintID = 1,	// µÇÈëÊÂ¼þ


	EventID_MAX,
};



class ServerProcessEvent
{
public:
	ServerProcessEvent();

	void SetEventID(unsigned short eventID);
	unsigned short GetEventID();

	void SetConnectID(int nConnectID);
	int GetConnectID();

	virtual void SetPacet(CBuffPacket *pBuffPacket){};
	virtual	CBuffPacket* WritePacket();
	virtual void clear(){};

	virtual void send();
protected:
	unsigned short m_u2EventID;
	int		m_nConnectID;
};


class LoginEvent :public ServerProcessEvent
{
public:
	LoginEvent(){};
	virtual void SetPacet(CBuffPacket *pBuffPacket);
	virtual	CBuffPacket* WritePacket();
	virtual void clear();

	string m_sName;
};