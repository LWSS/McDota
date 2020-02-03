#include "Hooks.h"

#include "../Settings.h"
#include "../GUI/Callbacks.h"

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

// `tree_cut` is an event that we hijack to communicate from panorama.
// It is normally never used in the game, even when cutting a tree.
// Why resort to this semi-ghetto method? Well I didn't want to include v8, especially when it needs to be version matched to the game's old version (5.8.283 - Feb 25 2017)
// IUIEvent would be more appropriate but calling the custom events didn't want to work.
bool Hooks::FireEventClientSide( CGameEventManager *thisptr, CGameEvent *event ) {
    const char *eventName;
    int actionID = 0;

    if( mc_log_clientevents->GetBool() ){
        eventName = event->GetName();
        Util::Log("Event[%d] Fired! (%s)", event->GetID(), eventName);
        if( !strcmp( eventName, "dota_game_state_change" ) ){
            Util::Log("\n    Transitioning from State (%s) -> (%s)", GameState2String( event->GetInt("old_state") ), GameState2String( event->GetInt("new_state") ) );
        }
        Util::Log("\n");
    }

    // tree_cut
    if( event->GetID() == 281 ){
        actionID = event->GetInt( "action", 0 );
        if( !actionID ){
            Util::Log("tree_cut: No \"action\" supplied!\n");
            return true;
        }
        switch( actionID ){
            case 1:
                break;
            default:
                break;
        }

        return true;
    }

    return gameEventManagerVMT->GetOriginalMethod<FireEventClientSideFn>(9)( thisptr, event );
}