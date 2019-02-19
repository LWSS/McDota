#include "NoFog.h"

#include "../Interfaces.h"
#include "../Settings.h"

void NoFog::ToggleFog(bool state) {
    CBaseEntity *entity;
    for( int i = 0; i <= entitySystem->GetHighestEntityIndex(); i++ ){
        entity = entitySystem->GetBaseEntity(i);
        if( entity ) {
            if ( strstr( entity->Schema_DynamicBinding()->bindingName, "C_FogController" ) != NULL ) {
                float *maxFogDensity = (float*)((uintptr_t)entity + 0x420);
                *maxFogDensity = state ? 1.0f : 0.0f;
            }
        }
    }
}

void NoFog::ToggleFoW(bool state) {
    if( state )
        camera->SetFOWAmount( 1.0f );
    else
        camera->SetFOWAmount( 0.0f );
}

void NoFog::FrameStageNotify(CSource2Client *thisptr, ClientFrameStage_t stage) {
    if( stage != ClientFrameStage_t::FRAME_START  || !engine->IsInGame() )
        return;

    static bool lastNoFogSetting = false;
    static bool lastNoFoWSetting = false;

    if( lastNoFogSetting != mc_fog_disable->GetBool() )
        NoFog::ToggleFog( !mc_fog_disable->GetBool() );

    if( lastNoFoWSetting != mc_fow_disable->GetBool() )
        NoFog::ToggleFoW( !mc_fow_disable->GetBool() );


    lastNoFogSetting = mc_fog_disable->GetBool();
    lastNoFoWSetting = mc_fow_disable->GetBool();
}