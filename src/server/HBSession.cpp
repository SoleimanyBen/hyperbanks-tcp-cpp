#include "HBSession.h"

HBSession::HBSession(boost::asio::io_service& ioService) : m_socket(ioService) { }

boost::asio::ip::tcp::socket& HBSession::GetSocket()
{
    return m_socket;
}

void HBSession::ListenForPacket()
{
    m_socket.async_read_some(
        boost::asio::buffer(m_buffer, MAX_BYTE_LENGTH),
        boost::bind(&HBSession::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

template<class T>
void HBSession::SendPacket(T packet)
{

}

template<class T>
T HBSession::DeserializePacket(EPacketType& type)
{
    switch(type)
    {
    case LOGIN:

    case HEARTBEAT:

    case QUERY_FIRMWARE:
    case SET_NEW_ADDRESS:
    case QUERY_POWERBANKS:
    case RENT:
    case RETURN:
    case REMOTE_RESTART:
    case REMOTE_UPDATE:
    case QUERY_ICCID:
    case EJECT:
    }
}

void HBSession::HandleRead(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transferred)
{
    std::cout << "[SESSION] Reading data from unit" << std::endl;
    LoginStruct loginPacket;

    std::stringstream stream;
    // 34 bytes total size
    loginPacket.packetLength = m_buffer[1]; // 2 byte
    loginPacket.cmd = m_buffer[2]; // 1 byte
    loginPacket.version = m_buffer[3]; // 1 byte 
    loginPacket.checkSum = m_buffer[4]; // 1 byte
    loginPacket.token = m_buffer[5], m_buffer[6], m_buffer[7], m_buffer[8]; // 4 bytes
    loginPacket.rand = m_buffer[9], m_buffer[10], m_buffer[11], m_buffer[12]; // 4 bytes
    loginPacket.magic = m_buffer[13], m_buffer[14]; // 2 bytes
    loginPacket.boxIdLength = m_buffer[16]; // 2 bytes
    
    // 16 bytes
    stream << m_buffer[17];
    stream << m_buffer[18];
    stream << m_buffer[19];
    stream << m_buffer[20];
    stream << m_buffer[21];
    stream << m_buffer[22];
    stream << m_buffer[23];
    stream << m_buffer[24];
    stream << m_buffer[25];
    stream << m_buffer[26];
    stream << m_buffer[27];
    stream << m_buffer[28];
    stream << m_buffer[29];
    stream << m_buffer[30];
    stream << m_buffer[31];
    stream << m_buffer[32];

    loginPacket.boxId = stream.str();
    loginPacket.reqDataLen = m_buffer[33], m_buffer[34]; // 2 bytes
    loginPacket.reqData; 

    
    
    if (!error)
    {
        if (VerifyPacket(bytes_transferred))
        {
            EPacketType packetType = GetPacketType();

            std::cout << "GOT PACKET TYPE" << std::endl;
            std::cout << packetType << std::endl;
        }
    
        ListenForPacket();
    }
}

void HBSession::HandleWrite(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Packet send successful" << std::endl;
    }
}

// Verify packet by seeing if PacketLength field matches packet length of packet
bool HBSession::VerifyPacket(size_t packetLength)
{
    uint16_t bufferPacketLength = m_buffer[1] + 0x2;

    if (packetLength == bufferPacketLength)
    {
        return true;
    }

    return false;
}

EPacketType HBSession::GetPacketType()
{
    uint8_t packetCommand = m_buffer[2];

    std::cout << "RECIEVED PACKET COMMAND OF: " << "0x" << std::hex << (int)packetCommand << std::endl;

    for (int i = EPacketType::LOGIN; i != EPacketType::Last; i++)
    {
        if (packetCommand == i)
            return (EPacketType)i;
    }
}