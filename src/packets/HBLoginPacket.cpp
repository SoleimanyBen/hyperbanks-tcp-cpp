#include "HBLoginPacket.h"

HBLoginPacket::HBLoginPacket(char buffer[]) : HBPackets(buffer)
{

}

void HBLoginPacket::DeserializePayload()
{
    m_pRand = buffer[6] + buffer[7] + buffer[8] + buffer[9];
    m_pMagic = buffer[10];
    m_pBoxIdLen = buffer[11];

    std::stringstream stream;

    // 16 bytes
    stream << buffer[17];
    stream << buffer[18];
    stream << buffer[19];
    stream << buffer[20];
    stream << buffer[21];
    stream << buffer[22];
    stream << buffer[23];
    stream << buffer[24];
    stream << buffer[25];
    stream << buffer[26];
    stream << buffer[27];
    stream << buffer[28];
    stream << buffer[29];
    stream << buffer[30];
    stream << buffer[31];
    stream << buffer[32];

    m_pBoxId = stream.str();

    m_pReqDataLen = buffer[33] + buffer[34];
}

std::string HBLoginPacket::GetBoxId()
{
    return m_pBoxId;
}