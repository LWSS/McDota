#include "Zoom.h"

#include "../interfaces.h"
#include "../settings.h"

void Zoom::FrameStageNotify(CSource2Client *thisptr, ClientFrameStage_t stage) {
    if( stage != ClientFrameStage_t::FRAME_START || !engine->IsInGame() )
        return;

    if( mc_camera_distance->GetFloat() > 49.0f )
        camera->SetDistanceToLookAtPos( mc_camera_distance->GetFloat() );

    if( mc_camera_yaw_add->GetFloat() > 0.1f )
        camera->SetExtraYaw( mc_camera_yaw_add->GetFloat() );
    else
        camera->SetExtraYaw( 0.0f );


    if( mc_camera_pitch_add->GetFloat() > 1.0f || mc_camera_pitch_add->GetFloat() < 0.1f ){
        camera->SetMinPitch( mc_camera_pitch_add->GetFloat() );
        camera->SetMaxPitch( mc_camera_pitch_add->GetFloat() );
    }
}