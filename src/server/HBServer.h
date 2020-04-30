#ifndef HBSERVER_HEADER
#define HBSERVER_HEADER

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "./enums/EPacketType.h"
#include "./HBSession.h"

class HBServer
{
public:
    HBServer(boost::asio::io_service& ioService, int port);
    // ~HBServer();

    void ListenForConnection(); // Method to start accepting connections

    void HandleConnection(boost::shared_ptr<HBSession> session, const boost::system::error_code& error);
    
private:
    boost::asio::io_service& m_ioService;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif