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
    HBLoginPacket(char** buffer);

    void DeserializePayload();

    uint32_t GetRand();
    
    uint16_t GetMagic();
    uint16_t GetBoxIdLength();
    uint16_t GetReqDataLength();

    std::string GetBoxId();
    std::string GetReqData();

private:
    uint32_t m_pRand;
    uint16_t m_pMagic;
    uint16_t m_pBoxIdLen;
    std::string m_pBoxId;
    uint16_t m_pReqDataLen;
    std::string m_pReqData;

    char* m_buffer;
};

#endif