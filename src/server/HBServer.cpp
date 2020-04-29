#include "HBServer.h"

HBServer::HBServer(boost::asio::io_service& ioService, int port) : m_ioService(ioService), m_acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) 
{ 
	ListenForNewConnection();
}

HBServer::~HBServer()
{

}

void HBServer::ListenForNewConnection()
{
	std::shared_ptr<HBSession> session = std::make_shared<HBSession>(m_ioService);
	m_acceptor.async_accept(
		session->GetSocket(),
		boost::bind(&HBServer::HandleConnection, this, session, boost::asio::placeholders::error)
	);
}

void HBServer::HandleConnection(boost::shared_ptr<HBSession> session, const boost::system::error_code& error)
{
	if (!error)
	{
		session->Start();

		ListenForNewConnection();
	} 
	else 
	{
		std::cout << "[SERVER] Server acception connection error. " << std::endl;
	}
	
}