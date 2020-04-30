#include "HBPackets.h"
#include <iostream>


HBPackets::HBPackets(char** buffer)
{
    buffer = buffer;

    DeserializeHeader();
}

void HBPackets::DeserializeHeader()
{
    m_pLength = buffer[0] + buffer[1];
    m_pCommand = buffer[2];
    m_pVersion = buffer[3];
    m_pCheckVersion = buffer[4];
    m_pToken = buffer[5];

    DeserializePayload();
}

uint16_t HBPackets::GetLength()
{
    return m_pLength;
}

uint8_t HBPackets::GetCommand()
{
    return m_pCommand;
}

uint8_t HBPackets::GetVersion()
{
    return m_pVersion;
}

uint8_t HBPackets::GetCheckVersion()
{
    return m_pCheckVersion;
}

template<class T>
void HBPackets::ParsePacket(const char packet[], T& obj)
{
    size_t typeSize = sizeof(obj);
}
