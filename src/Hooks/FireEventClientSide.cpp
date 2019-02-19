#include "hooks.h"

#include "../Settings.h"

typedef bool (* FireEventClientSideFn)( CGameEventManager*, CGameEvent * );

static const char *GameState2String( int state ){
    switch( state ){
        case DOTA_GAMERULES_STATE_INIT:
            return "DOTA_GAMERULES_STATE_INIT";
        case DOTA_GAMERULES_WAIT_FOR_PLAYERS_TO_LOAD:
            return "DOTA_GAMERULES_WAIT_FOR_PLAYERS_TO_LOAD";
        case DOTA_GAMERULES_HERO_SELECTION:
            return "DOTA_GAMERULES_HERO_SELECTION";
        case DOTA_GAMERULES_STRATEGY_TIME:
            return "DOTA_GAMERULES_STRATEGY_TIME";
        case DOTA_GAMERULES_PREGAME:
            return "DOTA_GAMERULES_PREGAME";
        case DOTA_GAMERULES_GAME_IN_PROGRESS:
            return "DOTA_GAMERULES_GAME_IN_PROGRESS";
        case DOTA_GAMERULES_POSTGAME:
            return "DOTA_GAMERULES_POSTGAME";
        case DOTA_GAMERULES_DISCONNECT:
            return "DOTA_GAMERULES_DISCONNECT";
        case DOTA_GAMERULES_TEAM_SHOWCASE:
            return "DOTA_GAMERULES_TEAM_SHOWCASE";
        case DOTA_GAMERULES_CUSTOM_GAME_SETUP:
            return "DOTA_GAMERULES_CUSTOM_GAME_SETUP";
        case DOTA_GAMERULES_WAIT_FOR_MAP_TO_LOAD:
            return "DOTA_GAMERULES_WAIT_FOR_MAP_TO_LOAD";

        default:
            return std::to_string( state ).c_str();
    }
}

bool Hooks::FireEventClientSide( CGameEventManager *thisptr, CGameEvent *event ) {
    const char *eventName;

    if( mc_log_clientevents->GetBool() ){
        eventName = event->GetName();
        Util::Log("Event Fired! (%s)", eventName);
        if( !strcmp( eventName, "dota_game_state_change" ) ){
            Util::Log("\n    Transitioning from State (%s) -> (%s)", GameState2String( event->GetInt("old_state") ), GameState2String( event->GetInt("new_state") ) );
        }
        Util::Log("\n");
    }
    return gameEventManagerVMT->GetOriginalMethod<FireEventClientSideFn>(9)( thisptr, event );
}