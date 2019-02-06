#include "hooks.h"

#include "../Hacks/NoFog.h"
#include "../Hacks/Zoom.h"
#include "../settings.h"

typedef void (* FrameStageNotifyFn)( CSource2Client*, ClientFrameStage_t );

//looks like they added stages 7 and 9
static const char* Stage2String( ClientFrameStage_t stage ){
    switch( stage ){
        case ClientFrameStage_t::FRAME_UNDEFINED:
            return "FRAME_UNDEFINED";
        case ClientFrameStage_t::FRAME_START:
            return "FRAME_START";
        case ClientFrameStage_t::FRAME_NET_UPDATE_START:
            return "FRAME_NET_UPDATE_START";
        case ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START:
            return "FRAME_NET_UPDATE_POSTDATAUPDATE_START";
        case ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END:
            return "FRAME_NET_UPDATE_POSTDATAUPDATE_END";
        case ClientFrameStage_t::FRAME_NET_UPDATE_END:
            return "FRAME_NET_UPDATE_END";
        case ClientFrameStage_t::FRAME_RENDER_START:
            return "FRAME_RENDER_START";
        case ClientFrameStage_t::FRAME_RENDER_END:
            return "FRAME_RENDER_END";
        default:
            return std::to_string((int)stage).c_str();
    }
}
void Hooks::FrameStageNotify( CSource2Client *thisptr, ClientFrameStage_t stage ) {
    //MC_PRINTF("FSN: %s\n", Stage2String(stage));
    CDotaPlayer *localPlayer;

    NoFog::FrameStageNotify( thisptr, stage );
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
                    MC_PRINTF( "Grabbing new NetChannel VMT\n" );
                    netChannelVMT = new VMT( engine->GetNetChannelInfo( ) );
                    netChannelVMT->HookVM( Hooks::SendNetMessage, 62 );
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
                localPlayerVMT = new VMT( localPlayer, true );
                localPlayerVMT->HookVM( Hooks::SendMove, 332 );
                localPlayerVMT->HookVM( Hooks::PrepareUnitOrders, 435 );
                localPlayerVMT->ApplyVMT();
                MC_PRINTF("LocalPlayer @ %p\n", (void*)localPlayer);
            }

            break;
        default:
            break;
    }
    return clientVMT->GetOriginalMethod<FrameStageNotifyFn>(29)( thisptr, stage );
}