#include "hooks.h"
#include "../Settings.h"

typedef float (* GetZFarFn)( CDotaCamera*, float );

/* Normally when u zoom out, the edges of the camera do the source engine render blur thing; fixes that */
float Hooks::GetZFar( CDotaCamera *thisptr, float unk ) {
    /* 2500 is normal zfar, 1134 is regular camera distance. 1134 * 2.204 = 2500; */
    return mc_camera_distance->GetFloat() * 2.204f;
}