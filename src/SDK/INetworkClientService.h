#pragma once
#include "IAppSystem.h"
#include "CNetworkGameClient.h"
#include "INetChannel.h"

// XREF "loopback" back to the first function. It should be right next to another string "address" in the function "AllocateRemoteConnectionClient"
class INetworkClientService : IAppSystem
{
public:
    virtual void GetServiceDependencies() = 0; // 11
    virtual const char* GetName() = 0;
    virtual bool ShouldActivate() = 0;
    virtual void OnLoopActivate() = 0;
    virtual void OnLoopDeactivate() = 0;
    virtual bool IsActive() = 0;
    virtual void SetActive( bool active ) = 0;
    virtual void SetName( const char* name ) = 0;
    virtual void RegisterEventMap() = 0;
    virtual int GetServiceIndex() = 0; // 20
    virtual void SetServiceIndex( int index ) = 0;
    virtual void DESTROY1() = 0;
    virtual void DESTROY2() = 0;
    virtual CNetworkGameClient* GetIGameClient() = 0;
    virtual void SetGameSpawnGroupMgr( void* groupMgr ) = 0;
    virtual void __dunno3() = 0;
    virtual void AllocateRemoteConnectionClient( void* keyValues ) = 0;
    virtual void SetClientSocket( int socket ) = 0;
    virtual void DisconnectGameNow( int disconnectReasonEnum ) = 0;
    virtual void DisconnectGameQueued( int disconnectReasonEnum ) = 0; // 30
    virtual void PrintSpawnGroupStatus( void ) = 0;
    virtual void GetCameraPosition( int splitScreenSlot, void * cTransform ) = 0;
    virtual CNetworkGameClient* GetGameClient( void ) = 0; // same as GetIGameClient()
    virtual bool IsActiveInGame( void ) = 0;
    virtual bool IsConnected( void ) = 0;
    virtual bool IsMultiplayer( void ) = 0;
    virtual bool IsPaused( void ) = 0;
    virtual bool IsDisconnecting( void ) = 0;
    virtual int GetDisconnectReason( void ) = 0;
    virtual int GetLocalPlayer( int splitScreenSlot ) = 0; // 40
    virtual void SendStringCmd( int splitScreenSlot, const char* command ) = 0;
    virtual void SplitScreenConnect( int splitScreenSlot ) = 0;
    virtual int GetMaxSplitScreenPlayers( void ) = 0;
    virtual void* GetNetChannel( void ) = 0;
    virtual void ClockDriftAdjustFrameTime( double diff ) = 0;
    virtual void* GetViewEntity( int splitScreenSlot ) = 0;
    virtual float GetTickInterval( void ) = 0;
    virtual long GetClientTime( void ) = 0;
    virtual long ComputeNextRenderTime( float mightBeFrameDiff ) = 0; // 49
    virtual bool IsEntityReportActive( void ) = 0; // 50
    virtual void* GetEntityReport( void ) = 0;
    virtual void EntityReportTrack() = 0; // lots of classes as params
    virtual bool SendNetMessage( int splitScreenSlot, void* NetMessageHandle_t, void const * something,  NetChannelBufType_t type ) = 0;
    virtual void ReceivedServerInfo() = 0;
    virtual void GetGameSessionInitPrerequisites() = 0;
    virtual void StartChangelevel( void ) = 0;
    virtual int GetClientChangeLevelState( void ) = 0;
    virtual bool IsChangelevelPending( void ) = 0;
    virtual int GetTotalTicks( void ) = 0; // might be long?
    virtual bool SteamIDAllowedToP2PConnect( void* CSteamID ) = 0; // 60
    virtual bool OnLevelLoadingStarted( void ) = 0;
    virtual void* GetNetMessageRelayDispatcher( void ) = 0;
    virtual void __dunno4() = 0; // might be RegisterNetMessage()
    virtual void PrintConnectionStatus( void ) = 0; // same as doing status in console
    virtual void __dunno5() = 0; // might be ProcessConnectionlessPacket()
    virtual void MessageData( unsigned int dunno, unsigned short something, unsigned int somethinElse, unsigned char* someBytes ) = 0;
};