#include "Hooks.h"

typedef void (* DispatchEventFn)( panorama::UIEngine*, panorama::IUIEvent * );

void Hooks::DispatchEvent( panorama::UIEngine *thisptr, panorama::IUIEvent *event ) {
    //Util::Log( "Event @ (%p)\n", event );
    //Util::Log( "Event TargetPanel(%d) - EventType(%d)\n", event->GetTargetPanel(), event->GetEventType2() );
    //Util::Log( "Target Panel: (%s) - Event Type: (%s)\n", panoramaEngine->AccessUIEngine()->ResolveSymbol(event->GetTargetPanel()),  panoramaEngine->AccessUIEngine()->ResolveSymbol(event->GetEventType2()));

    uiEngineVMT->GetOriginalMethod<DispatchEventFn>(49)( thisptr, event );
}
