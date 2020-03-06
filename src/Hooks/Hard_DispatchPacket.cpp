#include "HardHooks.h"

#include "../Utils/Protobuf.h"
#include "../Utils/Logger.h"
#include "../protos/mcdota.pb.h"

#include <csignal>


bool HardHooks::MyDispatchPacket( void *thisptr, IMsgNetPacket *netPacket ) {
    MC_LOGF("[GC]Recv(%p) - type(%s) - len(%d)\n", (void*)netPacket, EDOTAGCMsg2String( netPacket->GetEMsg() ).c_str(), netPacket->CubData());
    std::raise(SIGINT);
    //msg.ParseFromArray( IMsgNetPacket->PubData(), IMsgNetPacket->CubData() );

    bool rv;
    HardHooks::DispatchPacket.Remove();
    rv = ((DispatchPacketFn)DispatchPacketFnAddr)( thisptr, netPacket );
    HardHooks::DispatchPacket.Install();
    return rv;
}