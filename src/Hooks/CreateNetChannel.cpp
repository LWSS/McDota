#include "Hooks.h"

#include "../Interfaces.h"
#include "../Utils/Util.h"

typedef INetChannel* (* CreateNetChannelFn)( CNetworkSystem*, int, void *, const char *, unsigned int, unsigned int );

// This will not work for splitscreen slots ( if somehow this code needs to be used for that )
INetChannel* Hooks::CreateNetChannel( CNetworkSystem *thisptr, int unk, void *ns_addr, const char *str, unsigned int uUnk, unsigned int uUnk2 ) {
    netChannelVMT.reset();
    INetChannel *ret = networkSystemVMT->GetOriginalMethod<CreateNetChannelFn>( 26 )( thisptr, unk, ns_addr, str, uUnk, uUnk2 );

    MC_PRINTF( "Grabbing new NetChannel VMT - %p\n", (void*)ret );
    netChannelVMT = std::unique_ptr<VMT>(new VMT( ret ));
    netChannelVMT->HookVM( Hooks::SendNetMessage, 69 );
    netChannelVMT->HookVM( Hooks::PostReceivedNetMessage, 87 );
    netChannelVMT->ApplyVMT();

    return ret;
}