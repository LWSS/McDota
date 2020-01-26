#include "Hooks.h"

typedef CGameEvent* (* CreateEventFn)( CGameEventManager*, const char *, bool, int * );

// This needs to be hooked to force allow event creation from panorama "GameEvents.SendEventClientSide()"
// Used w/ FireEventClientSide hook to communicate from panorama.
CGameEvent* Hooks::CreateEvent( CGameEventManager *thisptr, const char *name, bool force, int *cookie ) {
    force = true;
    return gameEventManagerVMT->GetOriginalMethod<CreateEventFn>( 7 )( thisptr, name, force, cookie );
}