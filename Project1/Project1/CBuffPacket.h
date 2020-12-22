#pragma once

#include "ace/Message_Block.h"
#include <string>

using namespace  std;

class CBuffPacket
{
public:
	CBuffPacket();
	~CBuffPacket();


	bool WriteStream(const char* pData, int length);
	bool ReadStream(char*& pData, int& length);

	//∂¡»°
	CBuffPacket& operator >> (unsigned char& u1Data);
	CBuffPacket& operator >> (unsigned short& u2Data);
	CBuffPacket& operator >> (unsigned int& u4Data);

	CBuffPacket& operator >> (short &n2Data);
	CBuffPacket& operator >> (int &n4Data);


	CBuffPacket& operator >> (string& str);
	CBuffPacket& operator >> (bool& bData);

	// –¥»Î
	CBuffPacket& operator << (unsigned char u1Data);
	CBuffPacket& operator << (unsigned short u2Data);
	CBuffPacket& operator << (unsigned int u4Data);
	CBuffPacket& operator << (int u4Data);

	CBuffPacket& operator << (const string &str);

	CBuffPacket& operator << (bool bData);



public:
	ACE_Message_Block* GetBlock();
private:
	ACE_Message_Block	*m_pBlock;
};