#pragma once

#include "SDK/SDK.h"
#include "Utils/Vmt.h"

// Interfaces
inline CGlobalVars* globalVars;
inline IVPanel* panel;
inline CSource2Client* client;
inline ICvar* cvar;
inline IEngineClient* engine;
inline IInputInternal* inputInternal;
inline IInputSystem* inputSystem;
inline INetworkClientService* networkClientService;
inline CSplitScreenService* splitScreenService;
inline CGameEntitySystem* entitySystem;
inline CVScriptGameSystem* vscriptSystem;
inline IPanoramaUIEngine* panoramaEngine;
inline CNetworkMessages* networkMessages;
inline CViewRender* viewRender;
inline IClientMode* clientMode;
inline CDotaCamera* camera;
inline CGameEventManager* gameEventManager;
inline CSoundOpSystem* soundOpSystem;
inline CFontManager* fontManager;
inline CEngineServiceMgr* engineServiceMgr;
inline CDOTARichPresence* richPresence;
inline CParticleSystemMgr* particleSystemMgr;
inline CGameEventSystem* gameEventSystem;
inline CNetworkStringTableContainer* networkStrings;
inline IMaterialSystem* materialSystem;
inline CVPhys2World* phys2World;
inline CRenderGameSystem* renderGameSystem;
inline CNetworkSystem* networkSystem;
inline CGCClient* gcClient;
inline CBaseFileSystem* fileSystem; // there is another pointer to this in Logger

// VMT's - these get deleted on module unload.
inline std::unique_ptr<VMT> cameraVMT;
inline std::unique_ptr<VMT> clientVMT;
inline std::unique_ptr<VMT> inputInternalVMT;
inline std::unique_ptr<VMT> panelVMT;
inline std::unique_ptr<VMT> uiEngineVMT;
inline std::unique_ptr<VMT> networkSystemVMT;
inline std::unique_ptr<VMT> netChannelVMT;
inline std::unique_ptr<VMT> clientModeVMT;
inline std::unique_ptr<VMT> soundOpSystemVMT;
inline std::unique_ptr<VMT> gameEventManagerVMT;
inline std::unique_ptr<VMT> particleSystemVMT;

// HardHook Addresses
inline uintptr_t DispatchPacketFnAddr;
inline uintptr_t BAsyncSendProtoFnAddr;

// Functions Types
typedef GameScriptScopesWrapper* (* GetPanoramaScriptScopesFn)( void );
typedef void (* OnAcceptMatchFn)( panorama::CPanel2D* );
typedef void (* GetMatricesForViewFn)( CRenderGameSystem *thisptr, CViewSetup &view, VMatrix *worldToView, VMatrix *viewToProjection, VMatrix *worldToProjection, VMatrix *worldToScreen );
typedef void (* CGameTraceInitFn)( void *thisGameTrace );
typedef void (* CTraceFilterConstructorFn)( void *thisTraceFilter, const void *IHandleEntity_Ignore, int, bool (* handler)( void *IHandleEntity, int ) );
typedef void (* SendMessageGenericClientToGCFn)( const google::protobuf::Message * const msg, EDOTAGCMsg nMsgID );

// Function Pointers
inline GetPanoramaScriptScopesFn GetPanoramaScriptScopes;
inline OnAcceptMatchFn OnAcceptMatch;
inline GetMatricesForViewFn GetMatricesForView;
inline CGameTraceInitFn GameTrace_Init;
inline CTraceFilterConstructorFn CTraceFilter_Constructor;
inline SendMessageGenericClientToGCFn SendMessageGenericClientToGC;

// Viewmatrixes
inline VMatrix *g_WorldToView;
inline VMatrix *g_WorldToScreen;
inline VMatrix *g_WorldToProjection;
inline VMatrix *g_ViewToProjection;

// Other
inline panorama::CPanel2D* gDBPlayPanel; // Special Panel

#define MC_PRINTF(f_, ...) ConColorMsg(Color( 255, 140, 5 ), ("[McDota] " f_), ##__VA_ARGS__)
#define MC_PRINTF(f_, ...) ConColorMsg(Color( 255, 140, 5 ), ("[McDota] " f_), ##__VA_ARGS__)
#define MC_PRINTF_PLAIN(f_, ...) ConColorMsg(Color( 255, 140, 5 ), ("" f_), ##__VA_ARGS__)
#define MC_PRINTF_ERROR(f_, ...) ConColorMsg(Color( 255, 20, 140 ), ("[McDota:%s] " f_ ), __FUNCTION__, ##__VA_ARGS__)
#define MC_PRINTF_WARN(f_, ...) ConColorMsg(Color( 255, 223, 0 ), ("[McDota:%s] " f_ ), __FUNCTION__, ##__VA_ARGS__)

namespace Interfaces
{
	bool FindExportedInterfaces( );
	void DumpInterfaces( const char *fileName );
	void HookDynamicVMTs();
}
