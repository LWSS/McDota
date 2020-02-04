#include "HardHooks.h"
#include "../Interfaces.h"

#include <csignal>

bool HardHooks::MyDispatchPacket( void *thisptr, IMsgNetPacket *IMsgNetPacket ) {
    CNetPacket *pkt = IMsgNetPacket->GetCNetPacket();

    Util::Log("[GC]Recv(%p) - CNetPacket(%p) - type(%s) - len(%d)\n", (void*)IMsgNetPacket, pkt, EDOTAGCMsg2String( IMsgNetPacket->GetEMsg() ), IMsgNetPacket->CubData());
    std::raise(SIGINT);
    //msg.ParseFromArray( IMsgNetPacket->PubData(), IMsgNetPacket->CubData() );

    bool rv;
    HardHooks::DispatchPacket.Remove();
    rv = ((DispatchPacketFn)DispatchPacketFnAddr)( thisptr, IMsgNetPacket );
    HardHooks::DispatchPacket.Install();
    return rv;
}