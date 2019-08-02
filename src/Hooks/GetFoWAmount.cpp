#include "Hooks.h"

#include "../Settings.h"

typedef float (* GetFoWAmountFn)( CDotaCamera* );

float Hooks::GetFoWAmount( CDotaCamera *thisptr ) {
    if( mc_fow_disable->GetBool() ){
        return 0.0f;
    }
    return cameraVMT->GetOriginalMethod<GetFoWAmountFn>( 26 )( thisptr );
}