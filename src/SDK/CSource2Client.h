#pragma once
#include "IAppSystem.h"
#include "IInputSystem.h"
#include "vector.h"
#include "definitions.h"
#include "Schema.h"
#include "CViewSetup.h"

#include "../Utils/Util.h"

class ClientClass
{
public:
	char* m_pNetworkName; //0x0000 //EX: CDOTAPlayer
	char* m_pClassName; //0x0008 //EX: C_DOTAPlayer
	ClientClass* m_pNext; //0x0010
	void* m_pCreateFn; //0x0018
	void* m_pCreateEventFn; //0x0020
	void* m_pDestroyFn; //0x0028
	char pad_0030[8]; //0x0030
	char* m_pLibNameAndClassName; //0x0038 //EX: libclient.so!C_DOTAPlayer
	SchemaRecvTable* recvTable; //0x0040
	char pad_0048[20]; //0x0048
	EClassIds m_ClassID; //0x005C
	void* N00000046; //0x0060
	void* N00000047; //0x0068
};

class RnQueryAttr_t
{
public:
	/*
    virtual bool ShouldHitEntity( void *CEntityInstance )
    {
        Util::Log("Uhhh Should Hit Entity called!\n");
        return true;
    }*/
    void *unk; // defo a pointer
    void *unk2;
    void *unk3;
    int entskipHandle; // 0x18 - 0FFFFFFFFh -1 for none
    unsigned int maskMaybe; // 0x1C
    int type; // 0x20 - have seen 7 and 1.
    int unk4; // 0x24
    bool (* HandleHitEnt)( void *IHandleEntity, int unk ); // 0x28
    unsigned int mask;
    float maxDist; // BIG GUESS 1.0f
};
class RnQueryTerrain : public RnQueryAttr_t
{
public:
	void Init(unsigned int uMask, int entitySkipHandle = 0xFFFFFFFF, bool (* HitEntHandler)( void *, int ) = nullptr )
	{
		unk = 0;
		unk2 = 0;
		unk3 = 0;
		unk4 = 0;
		type = 1;
		entskipHandle = entitySkipHandle;
		maskMaybe = 0x9040000;
		mask = uMask;
		HandleHitEnt = HitEntHandler;
		maxDist = 1.0f;
	}
};

struct Ray_t
{
	VectorAligned start;
	VectorAligned delta;
	VectorAligned startOffset; // zero unless using mins/maxs
	VectorAligned extents;     // ^^
    int _unk;

	bool isRay;
	bool isSwept;
    bool unkBool;
    bool unkBool2;

    void *_unk2;

    void Init(Vector vecStart, Vector vecEnd)
	{
		delta = vecEnd - vecStart;
        delta.w = 0.0f;
		isSwept = (delta.LengthSqr() != 0);
		extents.x = extents.y = extents.z = extents.w = 0.0f;
        isRay = true;
		startOffset.x = startOffset.y = startOffset.z = startOffset.w = 0.0f;
		start = vecStart;
        start.w = 0.0f;
        _unk = 0;
        unkBool = false;
        unkBool2 = false;
        _unk2 = 0;
	}
};

struct CGameTrace
{
    Vector start;
    Vector end;
    Vector normal;
    void *unks[2];
    float fraction;
    char _pad[0x300];
};

/* xref "-pressdemo" to CSource2Client::Init */
class CSource2Client : IAppSystem
{
public:
	virtual void SetGlobals(void* CGlobalVarsBase); // 11
	virtual void InstallStringTableCallback(const char *tableName);
	virtual void PlayerInfoChanged(int entIndex);
	virtual void ClearInstancedBaselineFromClientClasses(void);
	virtual void CreateMove(int splitScreenSlot, int unk, bool unk2);
	virtual void sub_2B5FF10();
	virtual void sub_2B5FF30();
	virtual void SendMove(int splitScreenSlot, int unk);
	virtual void ProcessInput(int splitScreenSlot, float unk, bool unk2);
	virtual void WriteUsercmdDeltaToBuffer(int splitScreenSlot, void* bf_write, int from, int to, bool isnewcommand); // 20
	virtual void EncodeUserCmdToBuffer(int splitScreenSlot, void* bf_write, int slot);
	virtual void DecodeIUserCmdFromBuffer(int splitScreenSlot, void* bf_read, int slot);
	virtual void GetEntity2Networkable(int entIndex, void* Entity2Networkable_t);
	virtual const char* GetEntity2ClassName(int entIndex);
	virtual void GetNetworkFieldChangeCallbackQueue(void);
	virtual void NotifyShouldTransmit();
	virtual ClientClass* GetAllClasses(void);
	virtual void ReceivedServerInfo(void* GameSessionConfiguration_t, void* ILoopModePrerequisiteRegistry);
	virtual void FrameStageNotify(ClientFrameStage_t stage);
	virtual void HudVidInit(void); // 30
	virtual void HudUpdate(bool bActive);
	virtual void HudReset(void);
	virtual void IN_ClearStates(void);
	virtual bool IN_IsKeyDown(const char *name, bool isDown);
	virtual void OnLevelLoadingStarted(void);
	virtual void CenterStringOff(void);
	virtual void View_Fade(void* ScreenFade_t);
	virtual void OnSplitScreenStateChanged(void);
	virtual int GetPlayerTeamIndex(int entIndex);
	virtual void sub_2B60070();
	virtual bool CanVoiceChat(void);
	virtual void OnFullEntityUpdate(void);
	virtual void OnServerConnectionTimedOut(void const * ns_address);
	virtual void sub_2B60080();
	virtual void UpdateAudioState(void* AudioState_t, int splitScreenSlot);
	virtual void sub_2B60040();
	virtual void sub_2B6E830();
	virtual void View_Render(void* vrect_t);
	virtual void SetBlurFade(float blurFade);
	virtual void* GetSoundSpatialization(int entIndex, void* SpatializationInfo_t);
	virtual void sub_2E35350( void *rsi ); // Added with diretide-2020, sets some sort of utlstring.
	virtual void NotifyClientSignon(int unk);
	virtual int unk_30A6910(); // Added with Furry fetish hero - CUtlString::IsEqual_CaseSensitive
	virtual bool CanRecordDemo(char * unk, int unk2);
	virtual void OnDemoRecordStart(const char* name);
	virtual void OnDemoRecordStop(void);
	virtual void OnDemoPlaybackStart(const char* name, const char*** unk);
	virtual void OnDemoPlaybackStop(void);
	virtual void OnDemoPlaybackGoto();
	virtual void SetupScrubbingData();
	virtual void sub_2B7D850();
	virtual void OnScrubDemo(int unk);
	virtual void OnDemoSkip(int unk, int unk2, bool unk3);
	virtual bool ShouldNopCmdDuringDemoSkip(int unk);
	virtual void InitInstantReplayData(void* InstantReplayMessage_t, int unk);
	virtual void ClearInstantReplayData(void);
	virtual void UpdateProgressBar(float unk, const char* unk2);
	virtual bool ShouldPauseForToolUI(void);
	virtual void UpdateVguiPanels(void);
	virtual void* GetFullscreenClientDLLVPanel(void);
	virtual bool ShouldHideLoadingPlaque(void);
	virtual void GetBugReportInfo(int unk, void* CUtlBuffer, void* CUtlString, void* CUtlString2);
	virtual void OnKeyBindingChanged(ButtonCode_t key, const char* unk, const char* unk2);
	virtual void Source2MouseAccumulationPassThrough(int unk, int unk2);
	virtual void GetCameraPosition(int entIndex, int splitScreenSlot, void* CTransform);
	virtual void GetEyeAngles(int splitScreenSlot, QAngle *out);
	virtual void SnapEyeAngles(int splitScreenSlot, const QAngle &viewAngles);
	virtual void sub_2B65490();
	virtual void GetEntity2AbsOrigin(int entIndex, Vector *out);
	virtual void sub_2B65510();
	virtual void GetEntity2AbsAngles(int entIndex, QAngle *out);
	virtual void sub_2B65710();
	virtual void sub_2B65AA0();
	virtual void* GetEntityInfo(void);
	virtual void DescribeNetworkedField();
	virtual void PerformClientSpecificSetupForPlayerViews();
	virtual CViewSetup* GetPlayerViewSetup(int splitScreenSlot);
	virtual void GetBugReportLaunchURLParameters(void* KeyValues);
	virtual void sub_2B61BB0();
	virtual void sub_2B600F0();
	virtual void UpdateProjectedTexture();
	virtual void DeleteProjectedTexture();
	virtual void UpdateDeferredLight();
	virtual void DeleteDeferredLight();
	virtual int TraceRay(const Ray_t &ray, RnQueryAttr_t filter, CGameTrace* traceOut);
	virtual void GetPointContents(Vector unk, int unk2);
	virtual void LaunchApplicationOnExit(const char* pathMaybe);
	virtual void DotaEconGetSoundReplacement(const char* pathMaybe);
	virtual void sub_2B61B10();
	virtual void sub_2B630A0();
	virtual void NotifyPreSteamRunCallbacks(void);
	virtual bool VoiceReliable(void);
	virtual void UpdateWhenNotInGame(float unk);
	virtual void UpdateGlobalLightFromLightInfos();
	virtual void GetGlobalLightParameters();
	virtual void OnReceivedUpdatedServerPeerList();
	virtual void UpdateEventListeners();
	virtual void GetEconItemSystem();
	virtual void GameCreateNetworkStringTables();
	virtual void NotifyDisconnect();
	virtual void GetModelCombineInfo();
	virtual void sub_2B5FF40();
	virtual void sub_2B60190();
	virtual void sub_2B601A0();
	virtual void sub_2B61460();
	virtual void sub_2B5FF80();
	virtual void sub_2B5FFA0();
	virtual void sub_2B61940();
    virtual void sub_2E32F90(); // added with Diretide-2020
    virtual void sub_2E359D0(); // added with Diretide-2020
	virtual void sub_2B65BD0();
	virtual void sub_someDebugShit(); //%5d: %8.6f msec change ',27h,'%s()',27h,' on field %s(path=%s) fo' db 'r ent %s(%s) name=',27h,'%s',27h,0Ah
};
