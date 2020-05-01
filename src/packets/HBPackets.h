#ifndef HBPACKETS_HEADER
#define HBPACKETS_HEADER

#include <stdint.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include "../server/HBSession.h"

#pragma pack(1)

class HBPackets
{
public:
    HBPackets(boost::shared_ptr<HBSession> session, char* buffer);

    void ResponsePacket();

    template<class T>
    void SendResponsePacket(T& obj);

    template<class T>
    void ParseBytesToStruct(T& obj, char* buffer);

    template<class T>
    char* ParseStructToBytes(T obj, size_t packetSize);

    std::string ParseStringFromBytes(char* bytes, size_t offset, size_t size);

    struct PacketHeader
    {
        uint16_t m_pLength;
        uint8_t m_pCommand;
        uint8_t m_pVersion;
        uint8_t m_pCheckSum;
        uint8_t m_pToken;
    };

private:
    // p = packet
    boost::shared_ptr<HBSession> m_session;

};

#endif