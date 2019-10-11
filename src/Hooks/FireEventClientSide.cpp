#include "Hooks.h"

#include "../Settings.h"

typedef bool (* FireEventClientSideFn)( CGameEventManager*, CGameEvent * );

static const char *GameState2String( int state ){
    switch( state ){
        CASE_STRING( GameState::DOTA_GAMERULES_STATE_INIT );
        CASE_STRING( GameState::DOTA_GAMERULES_WAIT_FOR_PLAYERS_TO_LOAD );
        CASE_STRING( GameState::DOTA_GAMERULES_HERO_SELECTION );
        CASE_STRING( GameState::DOTA_GAMERULES_STRATEGY_TIME );
        CASE_STRING( GameState::DOTA_GAMERULES_PREGAME );
        CASE_STRING( GameState::DOTA_GAMERULES_GAME_IN_PROGRESS );
        CASE_STRING( GameState::DOTA_GAMERULES_POSTGAME );
        CASE_STRING( GameState::DOTA_GAMERULES_DISCONNECT );
        CASE_STRING( GameState::DOTA_GAMERULES_TEAM_SHOWCASE );
        CASE_STRING( GameState::DOTA_GAMERULES_CUSTOM_GAME_SETUP );
        CASE_STRING( GameState::DOTA_GAMERULES_WAIT_FOR_MAP_TO_LOAD );
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