#include "hooks.h"
#include "../Settings.h"

typedef void (* SendMoveFn)( CDotaPlayer*, int );

// int is normally zero, not sure when it changes.
void Hooks::SendMove( CDotaPlayer *thisptr, int unk ) {
    /*
    if( mc_command_repeater->GetBool() ){
        cvar->ConsoleDPrintf("Sending %d Times...\n", mc_send_freq->GetInt());
        for( int i = 0; i < mc_send_freq->GetInt(); i ++ ){
            localPlayerVMT->GetOriginalMethod<SendMoveFn>( 330 )( thisptr, unk );
        }
    }
     */
    localPlayerVMT->GetOriginalMethod<SendMoveFn>( 330 )( thisptr, unk );
}