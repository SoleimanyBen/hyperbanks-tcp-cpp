#include "HBServer.h"

HBServer::HBServer(boost::asio::io_service& ioService, int port) : m_ioService(ioService), m_acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) 
{ 
	std::cout << "[SERVER] Server started on port ::" << port << std::endl;
	
	ListenForConnection();
}

void HBServer::ListenForConnection()
{
	boost::shared_ptr<HBSession> session = boost::make_shared<HBSession>(m_ioService);
	m_acceptor.async_accept(
		session->GetSocket(),
		boost::bind(&HBServer::HandleConnection, this, session, boost::asio::placeholders::error)
	);
}

void HBServer::HandleConnection(boost::shared_ptr<HBSession> session, const boost::system::error_code& error)
{
	if (!error)
	{
		session->ListenForPacket();

		ListenForConnection();
	} 
	else 
	{
		std::cout << "[SERVER] Server acception connection error. " << std::endl;
	}
	
}