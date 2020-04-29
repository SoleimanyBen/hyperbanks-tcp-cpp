#include "server/HBServer.h"
#include "server/HBSession.h"
#include <boost/asio.hpp>

int main() 
{
    boost::asio::io_service ioService;
    HBServer server(ioService, 6100);

    ioService.run();
}