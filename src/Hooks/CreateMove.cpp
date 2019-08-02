#include "Hooks.h"

#include <csignal>
#include <sstream>

#include "../Utils/Util.h"
#include "../Settings.h"

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

//angle changed with +left/right stays the same.
//position is a delta, changes with arrow keys
bool Hooks::CreateMove( IClientMode *thisptr, CUserCmd* cmd, QAngle &angle, Vector &pos ) {
    /* I'm gonna grab Camera here since this gets called in-game */
    camera = GetCurrentCamera();
    if( camera ){
        if( !cameraVMT || ( cameraVMT && cameraVMT->interface != (void*)camera ) ){
            if( cameraVMT ){
                delete cameraVMT;
            }
            MC_PRINTF("Grabbing new CameraVMT\n");
            cameraVMT = new VMT( camera );
            cameraVMT->HookVM( Hooks::GetFogEnd, 19 );
            cameraVMT->HookVM( Hooks::GetZFar, 20 );
            cameraVMT->HookVM( Hooks::GetFoWAmount, 26 );
            cameraVMT->ApplyVMT();
        }
    }

    if( mc_send_status->GetBool() ){
        engine->ClientCmd_Unrestricted("status");
    }

    if( mc_end_createmove->GetBool() )
        return true;

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

    return clientModeVMT->GetOriginalMethod<CreateMoveFn>( 28 )( thisptr, cmd, angle, pos );
}
