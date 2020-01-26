#pragma once

enum class GameState : int
{
    DOTA_GAMERULES_STATE_INIT = 0,
    DOTA_GAMERULES_WAIT_FOR_PLAYERS_TO_LOAD,
    DOTA_GAMERULES_HERO_SELECTION,
    DOTA_GAMERULES_STRATEGY_TIME,
    DOTA_GAMERULES_PREGAME,
    DOTA_GAMERULES_GAME_IN_PROGRESS,
    DOTA_GAMERULES_POSTGAME,
    DOTA_GAMERULES_DISCONNECT,
    DOTA_GAMERULES_TEAM_SHOWCASE,
    DOTA_GAMERULES_CUSTOM_GAME_SETUP,
    DOTA_GAMERULES_WAIT_FOR_MAP_TO_LOAD
};

// xref "splitscreenplayer" to some function, double click `off_xxxxxxxx` to get to vtable
class CGameEvent
{
public:
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;

    virtual const char* GetName( void ) = 0;
    virtual int GetID( void ) = 0;

    virtual bool IsReliable( void ) = 0;
    virtual bool IsLocal( void ) = 0;
    virtual bool IsEmpty( char const* keyname = nullptr ) = 0;

    virtual bool GetBool( char const* keyname = nullptr, bool defaultValue = false ) = 0;
    virtual int GetInt( char const* keyname = nullptr, int defaultValue = 0 ) = 0;
    virtual uint64_t GetUint64( char const* keyname = nullptr, uint64_t DefaultValue = 0 ) = 0;
    virtual float GetFloat( char const* keyname = nullptr, float defaultValue = 0.0f ) = 0;
    virtual const char* GetString( char const* keyname = nullptr, char const* defaultValue = nullptr ) = 0;
    virtual const void* GetPtr( char const* keyname = nullptr ) = 0;

    virtual void SetBool( char const* keyname, bool value ) = 0;
    virtual void SetInt( char const* keyname, int value ) = 0;
    virtual void SetUint64( char const* keyname, uint64_t value ) = 0;
    virtual void SetFloat( char const* keyname, float value ) = 0;
    virtual void SetString( char const* keyname, char const* value ) = 0;
    virtual void SetPtr( char const* keyname, void const* value ) = 0;

    virtual void* GetDataKeys( void ) = 0;
};

class CGameEventListener2
{
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;

    virtual void FireGameEvent( CGameEvent* event ) = 0;
};

// xref "CGameEventManager::AddListener" to AddListener()
class CGameEventManager
{
public:
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;
    virtual int LoadEventsFromFile( const char *filename ) = 0;
    virtual void Reset(void) = 0;
    virtual bool AddListener( CGameEventListener2 *listener, const char *eventName, bool serverSide ) = 0;
    virtual bool FindListener( CGameEventListener2 *listener, const char *eventName ) = 0;
    virtual void RemoveListener( CGameEventListener2 *listener ) = 0;
    virtual CGameEvent* CreateEvent( const char* name, bool force = false, int *cookie = nullptr ) = 0;
    virtual bool FireEvent( CGameEvent *event, bool dontBroadcast ) = 0;
    virtual bool FireEventClientSide( CGameEvent *event ) = 0;
    virtual CGameEvent* DuplicateEvent( CGameEvent *event ) = 0;
    virtual void FreeEvent( CGameEvent *event ) = 0;
    virtual bool SerializeEvent( CGameEvent *event, void *Source1LegacyGameEvent ) = 0;
    virtual CGameEvent* UnserializeEvent( void const *Source1LegacyGameEvent ) = 0;
    virtual bool LookupEventId( const char *id ) = 0;
    virtual void sub_2C16A80() = 0;
    virtual void sub_2C69980() = 0;
};