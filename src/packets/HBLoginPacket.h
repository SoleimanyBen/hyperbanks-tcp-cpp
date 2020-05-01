#ifndef HBLOGINPACKET_HEADER
#define HBLOGINPACKET_HEADER

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../enums/EPacketType.h"
#include "../packets/HBPackets.h"
#include "../packets/HBLoginPacket.h"

class HBLoginPacket : public HBPackets
{
public:
    HBLoginPacket(boost::shared_ptr<HBSession> session, char* buffer);

    struct LoginPacket : public HBPackets::PacketHeader
    {
        uint32_t m_pRand;
        uint16_t m_pMagic;
        uint16_t m_pBoxIdLen;
        std::string m_pBoxId;
    } loginPacket;

private:

    char* m_buffer;
};

#endif