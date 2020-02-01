#include "Callbacks.h"

#include "../Hooks/Hooks.h"
#include "../Interfaces.h"
#include "../protos/mcdota.pb.h"

void UI::Callbacks::Quarantine( ) {
    CDOTAClientMsg_BeginLastHitChallenge lasthit;

    if( engine->IsInGame() ){
        MC_PRINTF("Sending Quarantine...\n");
        lasthit.set_chosen_lane( 2 );
        lasthit.set_helper_enabled( false );
        Hooks::SendNetMessage( engine->GetNetChannelInfo( ), networkMessages->GetMessageHandleByName( "CDOTAClientMsg_BeginLastHitChallenge" ), &lasthit, BUF_DEFAULT );
    }
}