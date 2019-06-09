#include "hooks.h"
#include <csignal>

typedef void ( *PostEventAbstractFn)( CGameEventSystem *, int, bool, int, const unsigned char *, CNetworkSerializerPB*, CMsg_Base*, unsigned long, NetChannelBufType_t );

void Hooks::PostEventAbstract( CGameEventSystem *thisptr, int splitScreenSlot, bool unk, int int2, unsigned char const *bytes, CNetworkSerializerPB* eventHandle,  CMsg_Base *msg,
                               unsigned long dong, NetChannelBufType_t buftype ) {
/*
    CUtlString string;
    string.m_Memory.m_pMemory = new uint8_t[4096];
    string.m_Memory.m_nAllocationCount = 4096;
    string.m_Memory.m_nGrowSize = 4096;

    Util::Log( "PostEvent- slot(%d) - bool(%s) - int2(%d) - bytes(@%p) - event(%s) - msg(@%p) - dong(%d) - buftype(%d) - getname(%s) \nToString(%s)\n",
    splitScreenSlot, unk ? "TRUE" : "FALSE", int2, bytes, eventHandle->GetUnscopedName(), msg, dong, buftype, eventHandle->protobuffBinding->GetName(), eventHandle->protobuffBinding->ToString( msg, &string ) );
    //std::raise(SIGINT);

    delete[] string.m_Memory.m_pMemory;
    */
    gameEventSystemVMT->GetOriginalMethod<PostEventAbstractFn>( 15 )( thisptr, splitScreenSlot, unk, int2, bytes, eventHandle, msg, dong, buftype );
}