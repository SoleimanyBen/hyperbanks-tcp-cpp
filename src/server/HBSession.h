#ifndef HBSESSION_HEADER
#define HBSESSION_HEADER

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../enums/EPacketType.h"
#include "../packets/HBPackets.h"
#include "../packets/HBLoginPacket.h"

#define MAX_BYTE_LENGTH 1024

struct LoginStruct 
{
    uint16_t packetLength;
    uint8_t cmd;
    uint8_t version;
    uint8_t checkSum;
    uint32_t token;
    uint32_t rand;
    uint16_t magic;
    uint16_t boxIdLength;
    std::string boxId;
    uint16_t reqDataLen;
    char reqData[4];
};

class HBSession : public boost::enable_shared_from_this<HBSession>
{
public:
    HBSession(boost::asio::io_service& ioService);

    boost::asio::ip::tcp::socket& GetSocket();

    void ListenForPacket();

    void HandleRead(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transfered);
    void HandleWrite(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transferred);

    template<class T>
    void SendPacket(T packet);
    
    void DeserializePacket(EPacketType& type, size_t transferred_bytes);

    bool VerifyPacket(size_t packetLength);
    EPacketType GetPacketType();

    void OnLogin(int transferred_bytes);
    
private:
    boost::asio::ip::tcp::socket m_socket;

    char m_buffer[MAX_BYTE_LENGTH];
};

#endif