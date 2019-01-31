#include "hooks.h"

#include "../settings.h"

typedef bool (* FireEventClientSideFn)( CGameEventManager*, CGameEvent * );

bool Hooks::FireEventClientSide( CGameEventManager *thisptr, CGameEvent *event ) {

    if( mc_log_clientevents->GetBool() ){
        Util::Log("Event Fired! (%s)\n", event->GetName());
    }
    return gameEventManagerVMT->GetOriginalMethod<FireEventClientSideFn>(9)( thisptr, event );
}