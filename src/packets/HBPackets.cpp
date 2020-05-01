#include "HBPackets.h"


HBPackets::HBPackets(boost::shared_ptr<HBSession> session, char* buffer) : m_session(session)
{
    std::cout << "Current command number" << std::endl;
}

template<class T>
void HBPackets::SendResponsePacket(T& obj)
{
    char* bytes = ParseStructToBytes<T>(obj);

    m_session->SendPacket(bytes);
}

template<class T>
void HBPackets::ParseBytesToStruct(T& obj, char* buffer)
{
    memcpy(&obj, &buffer[0], sizeof(T));
}

template<class T>
char* HBPackets::ParseStructToBytes(T obj, size_t packetSize)
{
    return char* bytes = reinterpret_cast<char*>(obj);
}

std::string HBPackets::ParseStringFromBytes(char* bytes, size_t offset, size_t size)
{
    char* charString = new char[size];

    for (int i = 0; i < size; i++)
    {
        charString[i] = bytes[offset + i];
    }

    std::string newString(charString);
    
    return newString;
}