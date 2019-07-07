#include "hooks.h"

#include "../Hacks/Zoom.h"
#include "../Settings.h"

typedef void (* FrameStageNotifyFn)( CSource2Client*, ClientFrameStage_t );

//looks like they added stages 7 and 9
static const char* Stage2String( ClientFrameStage_t stage ){
    switch( stage ){
        CASE_STRING( FRAME_UNDEFINED );
        CASE_STRING( FRAME_START );
        CASE_STRING( FRAME_NET_UPDATE_START );
        CASE_STRING( FRAME_NET_UPDATE_POSTDATAUPDATE_START );
        CASE_STRING( FRAME_NET_UPDATE_POSTDATAUPDATE_END );
        CASE_STRING( FRAME_NET_UPDATE_END );
        CASE_STRING( FRAME_RENDER_START );
        CASE_STRING( FRAME_RENDER_END );
        default:
            return std::to_string((int)stage).c_str();
    }
}
void Hooks::FrameStageNotify( CSource2Client *thisptr, ClientFrameStage_t stage ) {
    //MC_PRINTF("FSN: %s\n", Stage2String(stage));
    CDotaPlayer *localPlayer;

    Zoom::FrameStageNotify( thisptr, stage );

    if( mc_send_status->GetBool() ){
        engine->ClientCmd_Unrestricted("status");
    }
    switch( stage ){
        case ClientFrameStage_t::FRAME_START:

            break;
        case ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END:

            if( !netChannelVMT || (engine->GetNetChannelInfo() != (void*)netChannelVMT->interface ) ){
                if( netChannelVMT ){
                    delete netChannelVMT;
                }
                if( engine->GetNetChannelInfo() ) {
                    MC_PRINTF( "Grabbing new NetChannel VMT - %p\n", (void*)engine->GetNetChannelInfo() );
                    netChannelVMT = new VMT( engine->GetNetChannelInfo( ) );
                    netChannelVMT->HookVM( Hooks::SendNetMessage, 62 );
                    netChannelVMT->HookVM( Hooks::PostReceivedNetMessage, 81 );
                    netChannelVMT->ApplyVMT( );
                } else {
                    MC_PRINTF_WARN("GetNetChannelInfo returned null! Aborting NetChannel Hook!\n");
                }
            }

            localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(engine->GetLocalPlayer());
            if( !localPlayer ){
                if( localPlayerVMT )
                    delete localPlayerVMT;
                break;
            }

            if( !localPlayerVMT || (void*)localPlayerVMT->interface != localPlayer ){
                if( localPlayerVMT )
                    delete localPlayerVMT;

                MC_PRINTF("Making new localPlayer VMT\n");
                localPlayerVMT = new VMT( localPlayer );
                localPlayerVMT->HookVM( Hooks::SendMove, 330 );
                localPlayerVMT->HookVM( Hooks::PrepareUnitOrders, 432 );
                localPlayerVMT->ApplyVMT();
                MC_PRINTF("LocalPlayer @ %p\n", (void*)localPlayer);
            }

            break;
        default:
            break;
    }
    return clientVMT->GetOriginalMethod<FrameStageNotifyFn>(29)( thisptr, stage );
}