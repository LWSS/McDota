#pragma once
#include "IAppSystem.h"
#include "IInputSystem.h"
#include "vector.h"
#include "definitions.h"
struct RecvProp;

struct DVariant
{
	union
	{
		float m_Float;
		long m_Int;
		char *m_pString;
		void *m_pData;
		float m_Vector[3];
		int64_t m_Int64;
	};

	int m_Type;
};

struct CRecvProxyData
{
	const RecvProp* m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

struct RecvTable
{
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

typedef void (*RecvVarProxyFn) (const CRecvProxyData *pData, void *pStruct, void *pOut);

struct RecvProp
{
	char *m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void *m_pExtraData;
	RecvProp *m_pArrayProp;
	void *m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void *m_DataTableProxyFn;
	RecvTable *m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char *m_pParentArrayPropName;
};

class IClientNetworkable;
typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

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
	void* Schema; //0x0040
	char pad_0048[20]; //0x0048
	EClassIds m_ClassID; //0x005C
	void* N00000046; //0x0060
	void* N00000047; //0x0068
};

/* xref "-pressdemo" to CSource2Client::Init */
class CSource2Client : IAppSystem
{
public:
	virtual void SetGlobals(void* CGlobalVarsBase); // 11
	virtual void InstallStringTableCallback(const char *unk);
	virtual void PlayerInfoChanged(int entIndex);
	virtual void ClearInstancedBaselineFromClientClasses(void);
	virtual void CreateMove(int splitScreenSlot, int unk, bool unk2);
	virtual void sub_2B5FF10();
	virtual void sub_2B5FF30();
	virtual void SendMove(int splitScreenSlot, int unk);
	virtual void ProcessInput(int splitScreenSlot, float unk, bool unk2);
	virtual void WriteUsercmdDeltaToBuffer(int splitScreenSlot, void* bf_write, int from, int to, bool isnewcommand);
	virtual void EncodeUserCmdToBuffer(int splitScreenSlot, void* bf_write, int slot);
	virtual void DecodeIUserCmdFromBuffer(int splitScreenSlot, void* bf_read, int slot);
	virtual void GetEntity2Networkable(int entIndex, void* Entity2Networkable_t);
	virtual const char* GetEntity2ClassName(int entIndex);
	virtual void GetNetworkFieldChangeCallbackQueue(void);
	virtual void NotifyShouldTransmit();
	virtual ClientClass* GetAllClasses(void);
	virtual void ReceivedServerInfo(void* GameSessionConfiguration_t, void* ILoopModePrerequisiteRegistry);
	virtual void FrameStageNotify(ClientFrameStage_t stage); // 29
	virtual void HudVidInit(void);
	virtual void HudUpdate(bool bActive);
	virtual void HudReset(void);
	virtual void HudText(void* client_textmessage_t);
	virtual void IN_ClearStates(void);
	virtual bool IN_IsKeyDown(const char *name, bool isDown);
	virtual void DecalShoot();
	virtual void PlayerDecalShoot();
	virtual void OnLevelLoadingStarted(void);
	virtual void CenterStringOff(void);
	virtual void View_Fade(void* ScreenFade_t);
	virtual void OnSplitScreenStateChanged(void);
	virtual void ResetHudCloseCaption(void);
	virtual int GetPlayerTeamIndex(int entIndex);
	virtual void sub_2B60070();
	virtual bool CanVoiceChat(void);
	virtual void OnFullEntityUpdate(void);
	virtual void OnServerConnectionTimedOut(void const * ns_address);
	virtual void sub_2B60080();
	virtual void sub_2B614E0();
	virtual void sub_2B61530();
	virtual void* GetMouth(int entIndex);
	virtual void UpdateAudioState(void* AudioState_t, int splitScreenSlot);
	virtual void sub_2B60040();
	virtual void sub_2B6E830();
	virtual void View_Render(void* vrect_t);
	virtual void SetBlurFade(float blurFade);
	virtual void* GetSoundSpatialization(int entIndex, void* SpatializationInfo_t);
	virtual void NotifyClientSignon(int unk);
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
	virtual void* GetPlayerViewSetup(int splitScreenSlot);
	virtual void GetBugReportLaunchURLParameters(void* KeyValues);
	virtual void sub_2B61BB0();
	virtual void sub_2B600F0();
	virtual void UpdateProjectedTexture();
	virtual void DeleteProjectedTexture();
	virtual void UpdateDeferredLight();
	virtual void DeleteDeferredLight();
	virtual void TraceRay(void* Ray_t, int RnQueryAttr_t, void* CGameTrace);
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
	virtual void sub_2B65BD0();
};
