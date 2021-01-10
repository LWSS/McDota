#include "Hooks.h"

#include "../Interfaces.h"
#include "../Utils/Util.h"

typedef void ( *LevelInitFn )( IClientMode*, const char * );

void Hooks::LevelInit( IClientMode *thisptr, const char *newmap ) {
    Interfaces::HookDynamicVMTs();

    clientModeVMT->GetOriginalMethod<LevelInitFn>( 28 )( thisptr, newmap );
}