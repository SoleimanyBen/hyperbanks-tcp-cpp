#ifndef HBSESSION_HEADER
#define HBSESSION_HEADER

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/endian/conversion.hpp>
#include "../enums/EPacketType.h"
#include "../packets/HBPackets.h"
#include "../packets/HBLoginPacket.h"
#include "../utils/Utils.h"

#define MAX_BYTE_LENGTH 1024

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))



class HBSession : public boost::enable_shared_from_this<HBSession>
{
public:
    HBSession(boost::asio::io_service& ioService);

    boost::asio::ip::tcp::socket& GetSocket();

    void ListenForPacket();

    void HandleRead(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transfered);
    void HandleWrite(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transferred);

    void SendPacket(char* bytes);
    
    void DeserializePacket(EPacketType& type, size_t transferred_bytes);

    bool VerifyPacket(size_t packetLength);
    EPacketType GetPacketType();

    void OnLogin(int transferred_bytes);

    
    void hexdump(void *ptr, int buflen) {
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;
    for (i=0; i<buflen; i+=16) {
        printf("%06x: ", i);
        for (j=0; j<16; j++) 
        if (i+j < buflen)
            printf("%02x ", buf[i+j]);
        else
            printf("   ");
        printf(" ");
        for (j=0; j<16; j++) 
        if (i+j < buflen)
            printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
        printf("\n");
    }
    }

    struct LoginStruct 
    {
        uint16_t size;
        uint8_t cmd;
        uint8_t version;
        uint8_t checkSum;
        uint32_t token;
        uint32_t rand;
        uint16_t magic;
        uint16_t boxIdLength;
        std::string boxId;
    } loginStruct;
    
private:
    boost::asio::ip::tcp::socket m_socket;

    unsigned char m_buffer[MAX_BYTE_LENGTH];
};

#endif