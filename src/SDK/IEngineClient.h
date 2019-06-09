#pragma once

#include "IAppSystem.h"
#include "CDotaPlayer.h"
#include "INetChannel.h"


// find Function IEngineClient::HideLoadingPlaque with string "OnEngineLevelLoadingFinished"
class NetChannelInfo;
class IEngineClient : IAppSystem
{
public:
	typedef struct player_info_s
	{
		int64_t __pad0;
		union {
			int64_t xuid;
			struct {
				int xuidlow;
				int xuidhigh;
			};
		};
		char name[128];
		int userid;
		char guid[33];
		unsigned int friendsid;
		char friendsname[128];
		bool fakeplayer;
		bool ishltv;
		unsigned int customfiles[4];
		unsigned char filesdownloaded;
	} player_info_t;

    virtual bool IsPaused(void) = 0; // 11
    virtual float GetTimeScale(void) = 0;
    virtual void FindOrCreateWorldSession(void) = 0;
    virtual void GetEntityLumpForTemplate(void) = 0;
    virtual void GetStatsAppID(void) = 0;
    virtual void* GetGameClientFactory(void) = 0;
	virtual void* GetSteamUniverse(void) = 0; // Added Late June 2018
    virtual void ServerCmd( int inputCommandSrc, const char* command ) = 0;
    virtual void ClientCmd( int inputCommandSrc, const char* command ) = 0;
    virtual bool GetPlayerInfo( int iIndex, player_info_t *pInfo ) = 0; // 20
    virtual int GetPlayerForUserID( int ID ) = 0;
    virtual int GetLocalPlayer( int splitScreenSlot = 0 ) = 0;
    virtual long GetLastTimestamp(void) = 0;
    virtual int GetLastServertick(void) = 0;
    // AudioSource funcs
    virtual void GetSentence(void) = 0;
    virtual void GetSentenceLength(void) = 0;
    //
    virtual int GetMaxClients(void) = 0;
    virtual bool IsInGame(void) = 0;
    virtual bool IsConnected(void) = 0;
    virtual void ConNPrintf( int unk, const char* str, ... ) = 0; // 30
    virtual void ConNXPrintf( void * const printf_options_t, const char* str, ... ) = 0;
    virtual INetChannel* GetNetChannelInfo( int splitScreenSlot = 0 ) = 0;
    virtual bool IsPlayingDemo(void) = 0;
    virtual bool IsRecordingDemo(void) = 0;
    virtual bool IsPlayingTimeDemo(void) = 0;
    virtual void ExecuteClientCmd( const char* command ) = 0;
    virtual void ClientCmd_Unrestricted( const char* command ) = 0;
    virtual void __unknown(void) = 0;
    virtual void SetRestrictServerCommands( bool restrict ) = 0;
    virtual void SetRestrictClientCommands( bool restrict ) = 0; // 40
    virtual bool IsLowViolence(void) = 0;
    virtual int GetSplitScreenPlayer( int splitScreenSlot ) = 0;
    virtual bool IsSplitScreenActive(void) = 0;
    virtual bool IsValidSplitScreenSlot( int splitScreenSlot ) = 0;
    virtual int FirstValidSplitScreenSlot(void) = 0;
    virtual int NextValidSplitScreenSlot( int splitScreenSlot ) = 0;
    virtual void GetAvailableAsyncThread(void) = 0;
    virtual void GetScreenSize( int &width, int &height ) = 0;
    virtual bool IsDrawingLoadingImage(void) = 0;
    virtual void HideLoadingPlaque(void) = 0; // 50
    virtual const char* GetGameDirectory(void) = 0;
    virtual const char* GetLevelName(void) = 0;
    virtual const char* GetLevelNameShort(void) = 0;
    virtual void* GetVoiceTweakAPI(void) = 0;
    virtual void EngineStats_BeginFrame(void) = 0; // CEngineStats::BeginFrame
    virtual void EngineStats_EndFrame(void) = 0; // CEngineStats::EndFrame
    virtual void CheckPoint( const char* unknown ) = 0;
    // Demo Recording and Playback related functions
    virtual bool IsDemoPaused(void) = 0;
    virtual bool IsDemoSkipping(void) = 0;
    virtual int GetDemoRecordingTick(void) = 0; // 60
    virtual int GetDemoPlaybackTick(void) = 0;
    virtual int GetDemoPlaybackStartTick(void) = 0;
    virtual float GetDemoPlaybackTimeScale(void) = 0;
    virtual int GetDemoPlaybackTotalTicks(void) = 0;
    virtual const char* GetDemoPlaybackFileName(void) = 0;
    virtual bool IsHLTV(void) = 0;
    //
    virtual void GetMainMenuBackgroundName( char** buffer, int bufferLen ) = 0;
    virtual void GetUILanguage( char** buffer, int bufferLen ) = 0;
    virtual bool IsSkyboxVisibleFromPoint( const Vector &point ) = 0;
    virtual float GetScreenAspectRatio( int width, int height ) = 0; // 70
    virtual int GetEngineBuildNumber(void) = 0;
    virtual const char* GetProductVersionString(void) = 0; // eg "47"
    virtual int GetBuildVersion(void);
	virtual const char* GetBuildDateString() = 0; // ex: "Aug 3 2018"
	virtual const char* GetBuildTimeString() = 0; // ex: "14:00:13"
    virtual int GetConnectedServerNetworkVersion(void) = 0;
	virtual int GetAppID(void) = 0; // steam App ID (570)
	virtual void ReadConfiguration( int splitScreenSlot );
	virtual void SetAchievementMgr( void* achievementMgr ); // 80
	virtual void* GetAchivementMgr( void );
	/* Xbox-Related */
	virtual void OnStorageDeviceAttached( int );
	virtual void OnStorageDeviceDetached( int );

	virtual int GetActiveSplitScreenPlayerSlot( void );
	virtual void SetActiveSplitScreenPlayerSlot( int splitScreenSlot );
	virtual void SetLocalPlayerIsResolvable( const char*, int slot, bool state );
	virtual bool IsLocalPlayerResolvable( void );
	virtual void* GetSinglePlayerSharedMemorySpace( const char*, int );
	virtual void RegisterDemoCustomDataCallback(); //(CUtlSymbolLarge,void (*)(uchar *,ulong)) // 90
	virtual void RecordDemoCustomData(void (*)(unsigned char *,unsigned long),void const*,unsigned long);
	virtual void SetPitchScale( float pitch );
	virtual float GetPitchScale( void );
	virtual void* DSPGetCurrentDASRoomNew(void);
	virtual void* DSPGetCurrentDASRoomChanged(void);
	virtual void* DSPGetCurrentDASRoomSkyAbove(void);
	virtual bool IsRecordingVoice( void );
	virtual void SetTimeScale( float timescale );
	virtual void SetGameStatsData( void* CGameStatsData );
	virtual void* GetGameStatsData( void );
	virtual void UpdateDAndELights( void );
	virtual int GetBugSubmissionsCount( void );
	virtual void ClearBugSubmissionsCount( void );
	virtual float GetServerSimulationFrameTime( void );
	virtual float GetServerTickTimes( ); //(ulong long,CUtlVector<IVEngineClient2::ServerTickTime_t,CUtlMemory<IVEngineClient2::ServerTickTime_t,int>> &)
	virtual bool IsInCommentaryMode( void );
	virtual void SetBlurFade( float fade );
	virtual bool IsTransitioningToLoad( void );
	virtual void SearchPathsChangedAfterInstall( void ); // might be bool?
	virtual void SetConnectionPassword( const char* password );
	virtual void* GetSteamAPIContext( void );
	virtual void ServerCmdKeyValues( void* KeyValues );
	virtual void* GetStartupImage( void );
	virtual void* GetBackgroundMovie( void );
	virtual void* GetBackgroundMusic( void );
	virtual void TickProgressBar( void );
	virtual void* GetMainWindow( void );
	virtual void DrawSelectedPanel( int panelHandle );
	virtual bool IsPanelInFocusList( unsigned long long );
	virtual bool IsViewEntity( int entIndex );
	virtual int GetViewEntity( int splitScreenSlot = 0 ); // returns ent index I think.
	virtual void TouchLight( void* dlight_t );

	/* SOUP START */
	virtual void SetAreaState( unsigned char*, unsigned char* );
	virtual void ChangePVSSpawnGroupHandle( unsigned int );
	virtual void SetDemoTime( float time );
	virtual void FlashWindow( void );
	virtual void DesktopNotify( const char*, const char* );
	virtual void GetDemoGameInfo(); //(google::protobuf::Message &)
	virtual void GetDemoFileGameInfo(); //(char const*,google::protobuf::Message &)
	virtual void DecompressBZipFile( const char*, const char* );
	virtual void _unk1();
	virtual void _unk2();
	/* SOUP END */

	virtual void UnzipZip( const char*, const char*, const char*, bool, bool, bool);
	/* Functions only for Windows */
	virtual void SOSSetOpvarFloat();
	virtual void SOSGetOpvarFloat();

	virtual bool GameLoadFailed( void );
	virtual void SetGameLoadFailed( bool state );
	/* Soup after this point */
	virtual void LoadSpawnGroup( void* SpawnGroupDesc_t );
	virtual void UnloadSpawnGroup( unsigned int, int ESpawnGroupUnloadOption );
	virtual void SetSpawnGroupDescription( unsigned int, const char* );
	virtual void _pad();
	virtual void _pad2();
	virtual void _pad3();
	virtual void _pad4();
	virtual void _pad5();
	virtual void _pad6();
	virtual void _pad7();
	virtual void _pad8();
	virtual void _pad9();
	virtual void _pad10();
	virtual void _pad11();

	virtual bool IsClientLocalToActiveServer( void );
	virtual void PostReceivedNetMessage(); //(NetMessageHandle_t__ *,void const*,NetChannelBufType_t)
	// some more ...
};
