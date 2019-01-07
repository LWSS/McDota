#pragma once
#include "../SDK/CSource2Client.h"

/* No Fog and No Fog of War (FoW) */
namespace NoFog
{
    void ToggleFog( bool state );
    void ToggleFoW( bool state );

    //Hooks
    void FrameStageNotify( CSource2Client *thisptr, ClientFrameStage_t stage );
}