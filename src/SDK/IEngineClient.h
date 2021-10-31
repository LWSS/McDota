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
    virtual int GetMaxClients(void) = 0;
    virtual bool IsInGame(void) = 0;
    virtual bool IsConnected(void) = 0;
    virtual INetChannel* GetNetChannelInfo( int splitScreenSlot = 0 ) = 0;
    virtual bool IsPlayingDemo(void) = 0;
    virtual void sub_37C290(void) = 0; // added post-overwatch on Feb 11, 2021
    virtual bool IsRecordingDemo(void) = 0;
    virtual bool IsPlayingTimeDemo(void) = 0;
    virtual void ExecuteClientCmd( const char* command ) = 0;
    virtual void ClientCmd_Unrestricted( const char* command ) = 0;
    virtual void __unknown(void) = 0;
    virtual void SetRestrictServerCommands( bool restrict ) = 0;
    virtual void SetRestrictClientCommands( bool restrict ) = 0;
    virtual bool IsLowViolence(void) = 0;
    virtual int GetSplitScreenPlayer( int splitScreenSlot ) = 0;
    virtual bool IsSplitScreenActive(void) = 0;
    virtual bool IsValidSplitScreenSlot( int splitScreenSlot ) = 0;
    virtual int FirstValidSplitScreenSlot(void) = 0;
    virtual int NextValidSplitScreenSlot( int splitScreenSlot ) = 0;
    virtual void GetAvailableAsyncThread(void) = 0;
    virtual void GetScreenSize( int &width, int &height ) = 0;
    virtual bool IsDrawingLoadingImage(void) = 0;
    virtual void HideLoadingPlaque(void) = 0; // 47
    virtual const char* GetLevelName(void) = 0;
    virtual const char* GetLevelNameShort(void) = 0;
    virtual void* GetVoiceTweakAPI(void) = 0;
    virtual void CheckPoint( const char* unknown ) = 0;
    // Demo Recording and Playback related functions
    virtual bool IsDemoPaused(void) = 0;
    virtual bool IsDemoSkipping(void) = 0;
    virtual int GetDemoRecordingTick(void) = 0;
    virtual int GetDemoPlaybackTick(void) = 0;
    virtual int GetDemoPlaybackStartTick(void) = 0;
    virtual float GetDemoPlaybackTimeScale(void) = 0;
    virtual int GetDemoPlaybackTotalTicks(void) = 0;
    virtual const char* GetDemoPlaybackFileName(void) = 0;
    // New! Overwatch related functions. Added with Dota Overwatch.
    virtual void sub_379EA0() = 0; // Snuck in a small update a few days after overwatch update.
    virtual void sub_379D40() = 0;
    virtual bool sub_379D90() = 0;
    virtual void sub_379DE0() = 0;
    virtual void sub_379E30() = 0;
    virtual void sub_379E80() = 0;
    virtual void sub_387190() = 0; // added w/ Road to TI10
    virtual bool IsHLTV(void) = 0;
    //
    virtual void GetUILanguage( char** buffer, int bufferLen ) = 0;
    virtual float GetScreenAspectRatio( int width, int height ) = 0;
    virtual int GetEngineBuildNumber(void) = 0;
    virtual const char* GetProductVersionString(void) = 0; // eg "47"
    virtual int GetBuildVersion(void) = 0;
	virtual const char* GetBuildDateString() = 0; // ex: "Aug 3 2018"
	virtual const char* GetBuildTimeString() = 0; // ex: "14:00:13"
    virtual int GetConnectedServerNetworkVersion(void) = 0;
	virtual int GetAppID(void) = 0; // steam App ID (570)
	virtual void ReadConfiguration( int splitScreenSlot ) = 0;
	virtual void SetAchievementMgr( void* achievementMgr ) = 0;
	virtual void* GetAchivementMgr( void ) = 0;
	/* Xbox-Related */
	virtual void OnStorageDeviceAttached( int ) = 0;
	virtual void OnStorageDeviceDetached( int ) = 0;

	virtual void SetLocalPlayerIsResolvable( const char*, int slot, bool state ) = 0;
	virtual bool IsLocalPlayerResolvable( void ) = 0;
	virtual void RegisterDemoCustomDataCallback() = 0; //(CUtlSymbolLarge,void (*)(uchar *,ulong) = 0)
	virtual void RecordDemoCustomData(void (*)(unsigned char *,unsigned long),void const*,unsigned long) = 0; //"IEngineClient::RecordDemoCustomData(): "
	virtual void SetPitchScale( float pitch ) = 0;
	virtual float GetPitchScale( void ) = 0;
	virtual void* DSPGetCurrentDASRoomNew(void) = 0;
	virtual void* DSPGetCurrentDASRoomChanged(void) = 0;
	virtual void* DSPGetCurrentDASRoomSkyAbove(void) = 0;
	virtual bool IsRecordingVoice( void ) = 0;
	virtual void SetTimeScale( float timescale ) = 0;
	virtual void SetGameStatsData( void* CGameStatsData ) = 0;
	virtual void* GetGameStatsData( void ) = 0;
	virtual int GetBugSubmissionsCount( void ) = 0;
	virtual void ClearBugSubmissionsCount( void ) = 0;
	virtual float GetServerSimulationFrameTime( void ) = 0;
	virtual float GetServerTickTimes( ) = 0; //(ulong long,CUtlVector<IVEngineClient2::ServerTickTime_t,CUtlMemory<IVEngineClient2::ServerTickTime_t,int>> &)
	virtual bool IsInCommentaryMode( void ) = 0;
	virtual bool IsTransitioningToLoad( void ) = 0;
	virtual void SetConnectionPassword( const char* password ) = 0;
	virtual void* GetSteamAPIContext( void ) = 0;
	virtual void ServerCmdKeyValues( void* KeyValues ) = 0;
	virtual void TickProgressBar( void ) = 0;
	virtual void* GetMainWindow( void ) = 0;
	virtual void DrawSelectedPanel( int panelHandle ) = 0;
	virtual bool IsPanelInFocusList( unsigned long long ) = 0;
	virtual bool IsViewEntity( int entIndex ) = 0;
	virtual int GetViewEntity( int splitScreenSlot = 0 ) = 0; // returns ent index I think.
	virtual void TouchLight( void* dlight_t ) = 0;

	/* SOUP START */
	virtual void SetAreaState( unsigned char*, unsigned char* ) = 0;
	virtual void SetDemoTime( float time ) = 0;
	virtual void FlashWindow( void ) = 0;
	virtual void DesktopNotify( const char*, const char* ) = 0;
	virtual void AlertUser() = 0;
	virtual void GetDemoGameInfo() = 0; //(google::protobuf::Message &)
	virtual void GetDemoFileGameInfo() = 0; //(char const*,google::protobuf::Message &)
	virtual void DecompressBZipFile( const char*, const char* ) = 0;
	/* SOUP END */

	virtual void UnzipZip( const char*, const char*, const char*, bool, bool, bool) = 0;
	/* Functions only for Windows */
	virtual void SOSSetOpvarFloat() = 0;
	virtual void SOSGetOpvarFloat() = 0;

	virtual bool GameLoadFailed( void ) = 0;
	virtual void SetGameLoadFailed( bool state ) = 0;
	/* Soup after this point */
	virtual void LoadSpawnGroup( void* SpawnGroupDesc_t ) = 0;
	virtual void UnloadSpawnGroup( unsigned int, int ESpawnGroupUnloadOption ) = 0;
	virtual void SetSpawnGroupDescription( unsigned int, const char* ) = 0;
	virtual void _pad() = 0;
	virtual void _pad2() = 0;
	virtual void _pad3() = 0;
	virtual void _pad4() = 0;
	virtual void _pad5() = 0;
	virtual void _pad6() = 0;
	virtual void _pad7() = 0;
	virtual void _pad8() = 0;
	virtual void _pad9() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;

	virtual bool IsClientLocalToActiveServer( void ) = 0;
	virtual void PostReceivedNetMessage() = 0; //(NetMessageHandle_t__ *,void const*,NetChannelBufType_t)
    virtual void sub_36BAB0() = 0;
    virtual void sub_36BAA0() = 0;
    virtual void sub_36BA90() = 0;
    virtual void sub_36BA80() = 0;
    virtual void sub_36BA70() = 0;
    virtual void RenderSystemOptionFlags() = 0;
    virtual void sub_36BA50() = 0;
    virtual void sub_36BA40() = 0;
    virtual void sub_36BA20() = 0; // hlp 100
    virtual void sub_36BA00() = 0;
    virtual void sub_36B9F0() = 0;
    virtual void sub_36B9E0() = 0;
    virtual void sub_36B9D0() = 0;
    virtual void sub_36B9C0() = 0;
    virtual void sub_36B9B0() = 0;
    virtual void sub_36B9A0() = 0;
    virtual void sub_36B990() = 0;
    virtual void sub_36B980() = 0;
    virtual void sub_36B970() = 0;
    virtual void sub_36B960() = 0;
    virtual void sub_36B950() = 0;
    virtual void sub_36B940() = 0;
    virtual void CreateMinidump() = 0;
    virtual void LowViolence() = 0;
    virtual void LowViolence2() = 0;
    virtual void sub_36B890() = 0;
    virtual void sub_36B8B0() = 0;
    virtual void sub_3828E0() = 0;
    virtual void hlp_120() = 0;
    virtual void sub_3828D0() = 0;
    virtual void NEW_NEMESTICE() = 0; // added with nemestice
    virtual void sub_3819C0() = 0;
    virtual void sub_381C50() = 0;
};
