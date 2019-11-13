#include "Hooks.h"

#include <sstream>

#include "../Settings.h"
#include "../protos/mcdota.pb.h"

typedef bool (* CreateMoveFn)( IClientMode*, CUserCmd*, QAngle&, Vector& );

std::stringstream ss;
static std::string Buttons2ButtonStr( int32_t buttons ) {

    ss.str("");
    ss.clear();
    if( buttons & IN_ATTACK )
        ss << "| IN_ATTACK ";
    if( buttons & IN_JUMP )
        ss << "| IN_JUMP ";
    if( buttons & IN_DUCK )
        ss << "| IN_DUCK ";
    if( buttons & IN_FORWARD )
        ss << "| IN_FORWARD ";
    if( buttons & IN_BACK )
        ss << "| IN_BACK ";
    if( buttons & IN_USE )
        ss << "| IN_USE ";
    if( buttons & IN_CANCEL )
        ss << "| IN_CANCEL ";
    if( buttons & IN_LEFT )
        ss << "| IN_LEFT ";
    if( buttons & IN_RIGHT )
        ss << "| IN_RIGHT ";
    if( buttons & IN_MOVELEFT )
        ss << "| IN_MOVELEFT ";
    if( buttons & IN_MOVERIGHT )
        ss << "| IN_MOVERIGHT ";
    if( buttons & IN_ATTACK2 )
        ss << "| IN_ATTACK2 ";
    if( buttons & IN_RUN )
        ss << "| IN_RUN ";
    if( buttons & IN_RELOAD )
        ss << "| IN_RELOAD ";
    if( buttons & IN_ALT1 )
        ss << "| IN_ALT1 ";
    if( buttons & IN_ALT2 )
        ss << "| IN_ALT2 ";
    if( buttons & IN_SCORE )
        ss << "| IN_SCORE ";
    if( buttons & IN_SPEED )
        ss << "| IN_SPEED ";
    if( buttons & IN_WALK )
        ss << "| IN_WALK ";
    if( buttons & IN_ZOOM )
        ss << "| IN_ZOOM ";
    if( buttons & IN_WEAPON1 )
        ss << "| IN_WEAPON1 ";
    if( buttons & IN_WEAPON2 )
        ss << "| IN_WEAPON2 ";
    if( buttons & IN_BULLRUSH )
        ss << "| IN_BULLRUSH ";
    if( buttons & IN_GRENADE1 )
        ss << "| IN_GRENADE1 ";
    if( buttons & IN_GRENADE2 )
        ss << "| IN_GRENADE2 ";
    if( buttons & IN_ATTACK3 )
        ss << "| IN_ATTACK3 ";

    return ss.str();
}

bool lineInProgress = false;

//angle changed with +left/right stays the same.
//position is a delta, changes with arrow keys
bool Hooks::CreateMove( IClientMode *thisptr, CUserCmd* cmd, QAngle &angle, Vector &pos ) {
    bool ret;
    CDotaPlayer *localPlayer;

    camera = GetCurrentCamera();
    if( !cameraVMT || ( cameraVMT && cameraVMT->interface != (void*)camera ) ){
        delete cameraVMT;

        if( camera ){
            MC_PRINTF("Grabbing new CameraVMT\n");
            cameraVMT = new VMT( camera );
            cameraVMT->HookVM( Hooks::GetFogEnd, 19 );
            cameraVMT->HookVM( Hooks::GetZFar, 20 );
            cameraVMT->HookVM( Hooks::GetFoWAmount, 26 );
            cameraVMT->ApplyVMT();
            MC_PRINTF("Camera @ %p\n", (void*)camera);
        } else {
            MC_PRINTF_WARN("GetCurrentCamera() returned null! Aborting CameraVMT.\n");
        }
    }

    localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(engine->GetLocalPlayer());
    if( (!localPlayerVMT || (void*)localPlayerVMT->interface != localPlayer) ){
        delete localPlayerVMT;
        if( localPlayer ){
            MC_PRINTF("Making new localPlayer VMT\n");
            localPlayerVMT = new VMT( localPlayer );
            localPlayerVMT->HookVM( Hooks::PrepareUnitOrders, 442 );
            localPlayerVMT->ApplyVMT();
            MC_PRINTF("LocalPlayer @ %p\n", (void*)localPlayer);
        } else {
            MC_PRINTF_WARN("Localplayer is null! Aborting localPlayerVMT.\n");
        }
    }

    if( (!networkGameClientVMT || (networkClientService->GetIGameClient()) != (CNetworkGameClient*)networkGameClientVMT->interface) ){
        delete networkGameClientVMT;

        if( networkClientService->GetIGameClient() ){
            MC_PRINTF( "Grabbing new NetworkGameClient VMT - %p\n", (void*)networkClientService->GetIGameClient() );
            networkGameClientVMT = new VMT( networkClientService->GetIGameClient() );
            networkGameClientVMT->ApplyVMT();
        } else {
            MC_PRINTF_WARN("GetIGameClient() returned null! Aborting NetworkGameClient VMT.\n");
        }
    }

    if( (!netChannelVMT || (engine->GetNetChannelInfo() != (void*)netChannelVMT->interface)) ){
        delete netChannelVMT;

        if( engine->GetNetChannelInfo() ) {
            MC_PRINTF( "Grabbing new NetChannel VMT - %p\n", (void*)engine->GetNetChannelInfo() );
            netChannelVMT = new VMT( engine->GetNetChannelInfo( ) );
            netChannelVMT->HookVM( Hooks::SendNetMessage, 62 );
            netChannelVMT->HookVM( Hooks::PostReceivedNetMessage, 81 );
            netChannelVMT->ApplyVMT( );
        } else {
            MC_PRINTF_WARN("GetNetChannelInfo returned null! Aborting NetChannel VMT!\n");
        }
    }

    if( mc_send_status->GetBool() ){
        engine->ClientCmd_Unrestricted("status");
    }

    if( mc_end_createmove->GetBool() ){
        cmd->tick_count = 0;
        return true;
    }

    if( mc_airstuck_on->GetBool() ){
        MC_PRINTF("Airstucking...\n");
        //cmd->command_number = 16777216;
        cmd->tick_count = 16777216;
    }
    if( mc_log_createmove->GetBool() ){
        Util::Log("CreateMove: UserCmd @ %p, "
                          "\n-Viewangle(%f,%f,%f)"
                          "\n-CommandNum: %d"
                          "\n-TickCount: %d"
                          "\n-AimDirection(%f,%f,%f)"
                          "\n-buttons: (%d)%s"
                          "\n-impulse: %d"
                          "\nAngle(%f,%f,%f) - Pos(%f,%f,%f)\n\n",
                  (void*)cmd,
                  cmd->viewangles.x, cmd->viewangles.y, cmd->viewangles.z,
                  cmd->command_number,
                  cmd->tick_count,
                  cmd->aimdirection.x, cmd->aimdirection.y, cmd->aimdirection.z,
                  cmd->buttons, Buttons2ButtonStr(cmd->buttons).c_str(),
                  cmd->impulse,
                  angle.x, angle.y, angle.z, pos.x, pos.y, pos.z);

    }

    ret = clientModeVMT->GetOriginalMethod<CreateMoveFn>( 29 )( thisptr, cmd, angle, pos );
    CreateMove::lastMouse3D = cmd->CursorRay;
    return ret;
}
