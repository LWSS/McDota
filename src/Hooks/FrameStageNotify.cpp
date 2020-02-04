#include "Hooks.h"

#include "../Hacks/Zoom.h"
#include "../Settings.h"
#include "../Hooks/HardHooks.h"

typedef void (* FrameStageNotifyFn)( CSource2Client*, ClientFrameStage_t );

//looks like they added stages 7 and 9
static const char* Stage2String( ClientFrameStage_t stage ){
    switch( stage ){
        CASE_STRING( FRAME_UNDEFINED );
        CASE_STRING( FRAME_START );
        CASE_STRING( FRAME_NET_UPDATE_START );
        CASE_STRING( FRAME_NET_UPDATE_POSTDATAUPDATE_START );
        CASE_STRING( FRAME_NET_UPDATE_POSTDATAUPDATE_END );
        CASE_STRING( FRAME_NET_UPDATE_END );
        CASE_STRING( FRAME_RENDER_START );
        CASE_STRING( FRAME_RENDER_END );
        default:
            return "gaaaa";
    }
}
void Hooks::FrameStageNotify( CSource2Client *thisptr, ClientFrameStage_t stage ) {
    //MC_PRINTF("FSN: %s\n", Stage2String(stage));
    Zoom::FrameStageNotify( thisptr, stage );
    return clientVMT->GetOriginalMethod<FrameStageNotifyFn>(29)( thisptr, stage );
}