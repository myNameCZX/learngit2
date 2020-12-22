#include "CBuffPacket.h"

CBuffPacket::CBuffPacket()
{
	m_pBlock = new ACE_Message_Block(1024);
}

CBuffPacket::~CBuffPacket()
{
	m_pBlock->release();
	m_pBlock = 0;
}

bool CBuffPacket::WriteStream(const char* pData, int length)
{
	memcpy(m_pBlock->wr_ptr(),pData, length);
	m_pBlock->wr_ptr(length);

	return true;
}

bool CBuffPacket::ReadStream(char*& pData, int& length)
{
	memcpy(pData, m_pBlock->rd_ptr(), length);
	m_pBlock->rd_ptr(length);

	return true;
}

CBuffPacket& CBuffPacket::operator >> (unsigned char& u1Data)
{
	memcpy(&u1Data, m_pBlock->rd_ptr(), sizeof(u1Data));
	m_pBlock->rd_ptr(sizeof(u1Data));

	return *this;
}
CBuffPacket& CBuffPacket::operator >> (unsigned short& u2Data)
{
	memcpy(&u2Data, m_pBlock->rd_ptr(), sizeof(u2Data));
	m_pBlock->rd_ptr(sizeof(u2Data));

	return *this;
}
CBuffPacket& CBuffPacket::operator >> (unsigned int& u4Data)
{
	memcpy(&u4Data, m_pBlock->rd_ptr(), sizeof(u4Data));
	m_pBlock->rd_ptr(sizeof(u4Data));

	return *this;
}

CBuffPacket& CBuffPacket::operator >> (short &n2Data)
{
	memcpy(&n2Data, m_pBlock->rd_ptr(), sizeof(n2Data));
	m_pBlock->rd_ptr(sizeof(n2Data));

	return *this;
}
CBuffPacket& CBuffPacket::operator >> (int &n4Data)
{
	memcpy(&n4Data, m_pBlock->rd_ptr(), sizeof(n4Data));
	m_pBlock->rd_ptr(sizeof(n4Data));

	return *this;
}


CBuffPacket& CBuffPacket::operator >> (string& str)
{
	unsigned short	u2Size = 0;
	memcpy(&u2Size, m_pBlock->rd_ptr(), sizeof(u2Size));
	m_pBlock->rd_ptr(sizeof(u2Size));
	str = string(m_pBlock->rd_ptr(), u2Size);
	m_pBlock->rd_ptr(u2Size);

	return *this;
}
CBuffPacket& CBuffPacket::operator >> (bool& bData)
{
	memcpy(&bData, m_pBlock->rd_ptr(), sizeof(bData));
	m_pBlock->rd_ptr(sizeof(bData));

	return *this;
}

// –¥»Î
CBuffPacket& CBuffPacket::operator << (unsigned char u1Data)
{
	memcpy(m_pBlock->wr_ptr(), &u1Data, sizeof(u1Data));
	m_pBlock->wr_ptr(sizeof(u1Data));

	return *this;
}
CBuffPacket& CBuffPacket::operator << (unsigned short u2Data)
{
	memcpy(m_pBlock->wr_ptr(), &u2Data, sizeof(u2Data));
	m_pBlock->wr_ptr(sizeof(u2Data));
	return *this;
}
CBuffPacket& CBuffPacket::operator << (unsigned int u4Data)
{
	memcpy(m_pBlock->wr_ptr(), &u4Data, sizeof(u4Data));
	m_pBlock->wr_ptr(sizeof(u4Data));
	return *this;
}

CBuffPacket& CBuffPacket::operator << (int u4Data)
{
	memcpy(m_pBlock->wr_ptr(), &u4Data, sizeof(u4Data));
	m_pBlock->wr_ptr(sizeof(u4Data));
	return *this;
}

CBuffPacket& CBuffPacket::operator << (const string &str)
{
	unsigned short u2Size = str.length();
	memcpy(m_pBlock->wr_ptr(), &u2Size, sizeof(u2Size));
	m_pBlock->wr_ptr(sizeof(u2Size));

	memcpy(m_pBlock->wr_ptr(), str.c_str(), str.length());
	m_pBlock->wr_ptr(str.length());
	return *this;
}

CBuffPacket& CBuffPacket::operator << (bool bData)
{
	memcpy(m_pBlock->wr_ptr(), &bData, sizeof(bData));
	m_pBlock->wr_ptr(sizeof(bData));
	return *this;
}

ACE_Message_Block* CBuffPacket::GetBlock()
{
	return m_pBlock;
}