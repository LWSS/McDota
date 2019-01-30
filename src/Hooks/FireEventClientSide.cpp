#include "hooks.h"

typedef bool (* FireEventClientSideFn)( CGameEventManager*, CGameEvent * );

bool Hooks::FireEventClientSide( CGameEventManager *thisptr, CGameEvent *event ) {

    //cvar->ConsoleDPrintf("Event Fired! (%s)\n", event->GetName());
    return gameEventManagerVMT->GetOriginalMethod<FireEventClientSideFn>(9)( thisptr, event );
}