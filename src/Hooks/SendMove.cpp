#include "hooks.h"
#include "../Settings.h"

typedef void (* SendMoveFn)( CDotaPlayer*, int );


void Hooks::SendMove( CDotaPlayer *thisptr, int unk ) {
    if( mc_command_repeater->GetBool() ){
        for( int i = 0; i < 30; i ++ ){
            localPlayerVMT->GetOriginalMethod<SendMoveFn>( 332 )( thisptr, unk );
        }
    }
    localPlayerVMT->GetOriginalMethod<SendMoveFn>( 332 )( thisptr, unk );
}