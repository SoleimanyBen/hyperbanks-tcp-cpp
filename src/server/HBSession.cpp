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

void HBSession::SendPacket(char* bytes)
{
    m_socket.async_write_some(
        bytes,
        boost::bind(&HBSession::HandleWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

void HBSession::DeserializePacket(EPacketType& type, size_t bytes_transferred)
{
    switch(type)
    {
        case LOGIN:
            OnLogin((int)bytes_transferred);
            break;
    }
}

void HBSession::HandleRead(boost::shared_ptr<HBSession> session, const boost::system::error_code& error, size_t bytes_transferred)
{
    using ::boost::asio::detail::socket_ops::network_to_host_short;
    using ::boost::asio::detail::socket_ops::network_to_host_long;

    memcpy(&loginStruct, &m_buffer[0], sizeof(LoginStruct));

    loginStruct.size = network_to_host_short(loginStruct.size);
    loginStruct.token = network_to_host_long(loginStruct.token);
    loginStruct.rand = network_to_host_long(loginStruct.rand);
    loginStruct.magic = network_to_host_short(loginStruct.magic);

    char* array = new char[loginStruct.boxIdLength];

    for (int i = 0; i < loginStruct.boxIdLength; i++)
    {
        array[i] = m_buffer[17 + i];
    };

    std::string s(array);
    
    loginStruct.boxId = s;

    char* newStruct = reinterpret_cast<char*>(&loginStruct);

    std::cout << "HEX DUMP OF STRUCTURE" << std::endl;
    hexdump(newStruct, sizeof(LoginStruct));


    if (!error)
    {
        if (VerifyPacket(bytes_transferred))
        {
            EPacketType packetType = GetPacketType();

            std::cout << "GOT PACKET TYPE" << std::endl;
            std::cout << packetType << std::endl;

            DeserializePacket(packetType, bytes_transferred);
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

void HBSession::OnLogin(int transferred_bytes)
{
    // std::stringstream stream;
    
    // for (int i = 0; i < transferred_bytes; i++)
    // {
    //     stream << m_buffer[i];
    // }
    // // memcpy(newChar, m_buffer, transferred_bytes);

    // HBLoginPacket packet(stream.str());

    // std::cout << packet.GetBoxId() << std::endl;
}