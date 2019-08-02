#include "HardHooks.h"
#include "../Utils/Util.h"
#include "../Interfaces.h"

#include <csignal>

bool HardHooks::MyDispatchPacket( void *thisptr, CStructNetPacket *IMsgNetPacket ) {
    Util::Log("MyDispatchPacket(%p) - CNetPacket(%p)\n", (void*)IMsgNetPacket, IMsgNetPacket->GetCNetPacket());
    //std::raise(SIGINT);
    //msg.ParseFromArray( IMsgNetPacket->PubData(), IMsgNetPacket->CubData() );
    
    bool rv;
    HardHooks::DispatchPacket.Remove();
    rv = ((DispatchPacketFn)DispatchPacketFnAddr)( thisptr, IMsgNetPacket );
    HardHooks::DispatchPacket.Install();
    return rv;
}