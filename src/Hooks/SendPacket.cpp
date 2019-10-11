#include "Hooks.h"

#include <csignal>

typedef void* ( *SendPacketFn)( CNetworkSystem *thisptr, unsigned int unk1, void *unk2, const char*, unsigned int unk4, unsigned int unk5 );

void* Hooks::SendPacket( CNetworkSystem *thisptr, unsigned int unk1, void *unk2, const char* playername, unsigned int unk4, unsigned int unk5 ) {
    Util::Log("SendPacket Called!\n{\n"
                      "\tuint1(%d)\n"
                      "\tvoid*1(%p)\n"
                      "\tplayername(%s)\n"
                      "\tuint2(%d)\n"
                      "\tuint3(%d)\n}\n",
              unk1, unk2, playername, unk4, unk5
    );
    std::raise( SIGINT );
    return networkSystemVMT->GetOriginalMethod<SendPacketFn>( 28 )( thisptr, unk1, unk2, playername, unk4, unk5 );
}