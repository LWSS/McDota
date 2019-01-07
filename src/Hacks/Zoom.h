#pragma once

#include "../SDK/CSource2Client.h"

/* Zoom-out hack and camera related hacks */
namespace Zoom
{
    //Hooks
    void FrameStageNotify( CSource2Client *thisptr, ClientFrameStage_t stage );
}