#include "hooks.h"

#include "../Settings.h"

float Hooks::GetFogEnd( CDotaCamera *thisptr, float unk ) {
    if( mc_fog_disable->GetBool() ){
        return 0.0f;
    }
    return mc_camera_distance->GetFloat() * 4.0f;
}