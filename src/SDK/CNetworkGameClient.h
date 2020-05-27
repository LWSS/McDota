#pragma once

#include "INetChannel.h"

struct EventClientSimulate_t;
struct EventClientPollNetworking_t;
struct EventClientProcessNetworking_t;
struct EventClientSendInput_t;
struct EventClientProcessGameInput_t;
struct EventClientFrameSimulate_t;
struct EventClientAdvanceTick_t;
struct EventClientPostAdvanceTick_t;
struct EventClientOutput_t;
struct InputCommandSource_t;
struct CCommand;
struct AudioState_t;
struct C2S_CONNECT_Message_t;
struct HGameResourceManifest;
class CClientChangeLevelState;
class CCallQueue;

//Net Messages
struct CNETMsg_Tick_t;
struct CNETMsg_StringCmd_t;
struct CNETMsg_SetConVar_t;
struct CNETMsg_SignonState_t;
struct CNETMsg_SpawnGroup_Load_t;
struct CNETMsg_SpawnGroup_ManifestUpdate_t;
struct CNETMsg_SpawnGroup_Unload_t;
struct CNETMsg_SpawnGroup_SetCreationTick_t;
struct CSVCMsg_VoiceInit_t;
struct CSVCMsg_VoiceData_t;
struct CSVCMsg_ServerInfo_t;
struct CSVCMsg_ClassInfo_t;
struct CSVCMsg_FlattenedSerializer_t;
struct CSVCMsg_Menu_t;
struct CSVCMsg_GetCvarValue_t;
struct CSVCMsg_SetPause_t;
struct CSVCMsg_ClearAllStringTables_t;
struct CSVCMsg_CreateStringTable_t;
struct CSVCMsg_UpdateStringTable_t;
struct CSVCMsg_SetView_t;
struct CSVCMsg_PacketEntities_t;
struct CSVCMsg_SplitScreen_t;
struct CSVCMsg_CmdKeyValues_t;
struct CSVCMsg_Sounds_t;
struct CSVCMsg_BSPDecal_t;
struct CSVCMsg_Prefetch_t;
struct CSVCMsg_PacketReliable_t;
struct CSVCMsg_FullFrameSplit_t;
struct CSVCMsg_HLTVStatus_t;

struct NetMessageConnectionClosed_t;
struct NetMessageConnectionCrashed_t;
struct NetMessageSplitscreenUserChanged_t;
struct NetMessagePacketStart_t;
struct NetMessagePacketEnd_t;



// xref "Connection lost" to ProcessConnectionCrashed()  (libengine2)
class CNetworkGameClient // AKA: CNetworkGameClientBase
{
public:
    virtual void Init(void) = 0;
    virtual void SetGameSpawnGroupMgr(void *IGameSpawnGroupMgr) = 0;
    virtual void AddRef(void) = 0;
    virtual void Release(void) = 0;
    virtual void* GetGlobals(void) = 0;
    virtual int GetClientTickCount(void) = 0;
    virtual int GetServerTickCount(void) = 0;
    virtual void SetFrameTime(float value) = 0;
    virtual void SetTickRemainder(float value) = 0;
    virtual void ApplyClockDrift(int, int) = 0;
    virtual void Connect(int splitScreenslot, int unk, void const * ns_address) = 0;
    virtual void DisconnectGame(int ENetworkDisconnectionReason) = 0;
    virtual bool IsActive(void) = 0;
    virtual bool IsConnected(void) = 0;
    virtual bool IsConnecting(void) = 0;
    virtual bool IsPaused(void) = 0;
    virtual bool IsSomething(void) = 0; // added Dec 2018
    virtual bool IsInGame(void) = 0;
    virtual bool IsBackgroundMap(void) = 0;
    virtual int GetMaxClients(void) = 0;
    virtual void Simulate(EventClientSimulate_t const&) = 0;
    virtual void ClientPollNetworking(EventClientPollNetworking_t const&) = 0;
    virtual void ClientProcessNetworking(EventClientProcessNetworking_t const&) = 0;
    virtual void OnClientSendInput(EventClientSendInput_t const&) = 0;
    virtual void OnClientProcessGameInput(EventClientProcessGameInput_t const&) = 0;
    virtual void OnClientFrameSimulate(EventClientFrameSimulate_t const&) = 0;
    virtual void OnClientAdvanceTick(EventClientAdvanceTick_t const&) = 0;
    virtual void OnClientPostAdvanceTick(EventClientPostAdvanceTick_t const&) = 0;
    virtual void OnClientOutput(EventClientOutput_t const&) = 0;
    virtual void RequestServerStatus(int splitScreenSlot) = 0;
    virtual void ForceFullUpdate(const char *reasonIThink) = 0;
    virtual void PrintSpawnGroupStatus(void) = 0;
    virtual void GetCameraPosition(int splitScreenSlot, void *CTransform) = 0;
    virtual int GetLocalPlayer(int splitScreenSlot) = 0;
    virtual void ServerCmd(InputCommandSource_t, const char* cmd) = 0;
    virtual void ServerCmd(InputCommandSource_t, CCommand const&) = 0;
    virtual void SendStringCmd(int splitScreenSlot, const char* cmd) = 0;
    virtual void SplitScreenConnect(int splitScreenSlot) = 0;
    virtual int GetMaxSplitScreenPlayers(void) = 0;
    virtual INetChannel* GetNetChannel(int splitScreenSlot) = 0;
    virtual void* GetViewEntity(void) = 0;
    virtual void UpdateAudioState(AudioState_t *, int splitScreenSlot) = 0;
    virtual void ClockDrift_AdjustFrameTime(float) = 0;
    virtual float GetTickInterval(void) = 0;
    virtual float GetTime(void) = 0;
    virtual void ComputeNextRenderTime(float) = 0;
    virtual void ReencodeForVConsole(int entIndex) = 0;
    virtual void PrepareSteamConnectResponse(unsigned long long, bool, void const * ns_address, C2S_CONNECT_Message_t &) = 0;
    virtual bool IsLowViolence(void) = 0;
    virtual void* GetHostVersion(void) = 0;
    virtual void GetLastTimestamp(void) = 0;
    virtual int GetLastServerTick(void) = 0;
    virtual void SetGameSessionManifest(HGameResourceManifest *, HGameResourceManifest *) = 0;
    virtual void SpewSerializer(const char *) = 0;
    virtual void EntityClassCompletion();//char const*,CUtlVector<CUtlString,CUtlMemory<CUtlString,int>> &)
    virtual void ConsistencyCheck(bool) = 0;
    virtual bool IsSpawnGroupAsyncLoaded(unsigned int) = 0;
    virtual void* GetWorldSession(void) = 0;
    virtual const char*  GetSpawnGroupName(unsigned int) = 0;
    virtual void StartChangeLevel(void) = 0;
    virtual void FinishChangeLevel(CClientChangeLevelState *) = 0;
    virtual bool IsChangeLevelPending(void) = 0;
    virtual void GetAllLoadingSpawnGroups();//(CUtlVector<uint,CUtlMemory<uint,int>> *)
    virtual void UpdateSceneObjects(CCallQueue &) = 0;
    virtual void ProcessConnectionlessPacket(void *a2) = 0; //virtual void ProcessConnectionlessPacket(void const * ns_address, void * bf_read) = 0;
    virtual void BlockDisconnectionTracking(bool) = 0;
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;
    virtual void FilterMessage(NetMessageHandle_t *, void const *) = 0;
    virtual void OnShutdownChannel(INetChannel const *, bool) = 0;
    virtual void OnGameEventReceived(NetMessageHandle_t *, NetMessageInfo_t const *, void const *) = 0;
    virtual void sub_5BBB50() = 0;
    virtual void sub_5BBE40() = 0;
    virtual void sub_5C24E0() = 0;
    virtual void ProcessTick(CNETMsg_Tick_t const&) = 0;
    virtual void ProcessStringCmd(CNETMsg_StringCmd_t const&) = 0;
    virtual void ProcessSetConVar(CNETMsg_SetConVar_t const&) = 0;
    virtual void ProcessSignonState(CNETMsg_SignonState_t const&) = 0;
    virtual void ProcessSpawnGroupLoad(CNETMsg_SpawnGroup_Load_t const &) = 0;
    virtual void ProcessSpawnGroup_ManifestUpdate(CNETMsg_SpawnGroup_ManifestUpdate_t const &) = 0;
    virtual void ProcessSpawnGroup_Unload(CNETMsg_SpawnGroup_Unload_t const &) = 0;
    virtual void ProcessSpawnGroup_SetCreationTick(CNETMsg_SpawnGroup_SetCreationTick_t const &) = 0;
    virtual void sub_5A68F0() = 0;
    virtual void ProcessVoiceInit(CSVCMsg_VoiceInit_t const &) = 0;
    virtual void ProcessVoiceData(CSVCMsg_VoiceData_t const &) = 0;
    virtual void sub_5A8180() = 0;
    virtual void ProcessServerInfo(CSVCMsg_ServerInfo_t const &) = 0;
    virtual void ProcessClassInfo(CSVCMsg_ClassInfo_t const &) = 0;
    virtual void ProcessFlattenedSerializer(CSVCMsg_FlattenedSerializer_t const &) = 0;
    virtual void ProcessMenu(CSVCMsg_Menu_t const &) = 0;
    virtual void ProcessGetCvarValue(CSVCMsg_GetCvarValue_t const &) = 0;
    virtual void ProcessSetPause(CSVCMsg_SetPause_t const &) = 0;
    virtual void ProcessClearAllStringTables(CSVCMsg_ClearAllStringTables_t const &) = 0;
    virtual void ProcessCreateStringTable(CSVCMsg_CreateStringTable_t const &) = 0;
    virtual void ProcessUpdateStringTable(CSVCMsg_UpdateStringTable_t const &) = 0;
    virtual void ProcessSetView(CSVCMsg_SetView_t const &) = 0;
    virtual void ProcessPacketEntities(CSVCMsg_PacketEntities_t const &) = 0;
    virtual void ProcessSplitScreen(CSVCMsg_SplitScreen_t const &) = 0;
    virtual void ProcessCmdKeyValues(CSVCMsg_CmdKeyValues_t const &) = 0;
    virtual void ProcessSounds(CSVCMsg_Sounds_t const &) = 0;
    //virtual void ProcessBSPDecal(CSVCMsg_BSPDecal_t const &) = 0; //
    virtual void ProcessPrefetch(CSVCMsg_Prefetch_t const &) = 0;   // this function is either Prefetch or the above BSPDecal. 50/50
    virtual void sub_5A5D50() = 0;
    virtual void ProcessPacketReliable(CSVCMsg_PacketReliable_t const &) = 0;
    virtual void ProcessFullFrameSplit(CSVCMsg_FullFrameSplit_t const &) = 0;
    virtual void ProcessHLTVStatus(CSVCMsg_HLTVStatus_t const &) = 0;
    virtual void sub_5A6180() = 0;
    virtual void ProcessConnectionClosed(NetMessageConnectionClosed_t const &) = 0;
    virtual void ProcessConnectionCrashed(NetMessageConnectionCrashed_t const &) = 0;
    virtual void ProcessChangeSplitScreenUser(NetMessageSplitscreenUserChanged_t const &) = 0;
    virtual void ProcessPacketStart(NetMessagePacketStart_t const &) = 0;
    virtual void ProcessPacketEnd(NetMessagePacketEnd_t const &) = 0;
    virtual void Clear(bool) = 0;
    virtual void FullConnect(void const * ns_address) = 0;
    virtual void SetSignonState(SignonState_t, int, CNETMsg_SignonState_t const *) = 0;
    virtual void RunFrame(void) = 0;
    virtual void InstallStringTableCallback(const char *tableName) = 0;
    virtual void HookClientStringTable(const char *) = 0;
    virtual void GetClientName(int splitScreenSlot) = 0;
    virtual void loc_348070() = 0; //something to do with eventdispatcher
    virtual void OnPreserveEntity(void * CEntityReadInfo) = 0;
    virtual void CopyNewEntity(void *IEntityReport, void *CEntityReadInfo, void *ClientClass, int, unsigned int) = 0;
    virtual void CopyExistingEntity(void *IEntityReport, void *CEntityReadInfo) = 0;
    virtual void CL_ClearState(bool) = 0;
    virtual void OnSwitchLoopModeFinished(const char*, unsigned int, bool) = 0;

    int32_t *GetLocalDOTAPlayerID() {
        return (int32_t*)((uintptr_t)this + 0xAC);
    }
};