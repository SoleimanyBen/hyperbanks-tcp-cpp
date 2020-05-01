#include "HBLoginPacket.h"
#include <string>

HBLoginPacket::HBLoginPacket(boost::shared_ptr<HBSession> session, char* buffer) : HBPackets(session, buffer) 
{ 
    
}
