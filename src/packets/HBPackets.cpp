#include "HBPackets.h"


HBPackets::HBPackets(char buffer[])
{
    m_buffer = buffer;
}

void HBPackets::DeserializeHeader()
{
    m_pLength = m_buffer[1];
}