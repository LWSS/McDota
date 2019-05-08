#include "hooks.h"

typedef void ( *PostEventAbstractFn)( CGameEventSystem *, int, bool, int, const unsigned char *, GameEventHandle_t *, const void *, unsigned long, NetChannelBufType_t );

void Hooks::PostEventAbstract( CGameEventSystem *thisptr, int splitScreenSlot, bool unk, int int2, unsigned char const *bytes, GameEventHandle_t * eventHandle, void const *something,
                               unsigned long dong, NetChannelBufType_t buftype ) {

    Util::Log( "PostEventAbstract Called!\n" );
    gameEventSystemVMT->GetOriginalMethod<PostEventAbstractFn>( 15 )( thisptr, splitScreenSlot, unk, int2, bytes, eventHandle, something, dong, buftype );
}