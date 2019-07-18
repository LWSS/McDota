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

// VMT's
inline VMT* cameraVMT;
inline VMT* clientVMT;
inline VMT* inputInternalVMT;
inline VMT* panelVMT;
inline VMT* uiEngineVMT;
inline VMT* localPlayerVMT;
inline VMT* netChannelVMT;
inline VMT* clientModeVMT;
inline VMT* soundOpSystemVMT;
inline VMT* gameEventManagerVMT;
inline VMT* gameEventSystemVMT;

// Special Panels
inline panorama::CPanel2D* gDBPlayPanel;

#define MC_PRINTF(f_, ...) cvar->ConsoleColorPrintf(ColorRGBA( 255, 140, 5 ), ("[McDota] " f_), ##__VA_ARGS__)
#define MC_PRINTF_ERROR(f_, ...) cvar->ConsoleColorPrintf(ColorRGBA( 225, 5, 5 ), ("[McDota:%s] " f_ ), __FUNCTION__, ##__VA_ARGS__)
#define MC_PRINTF_WARN(f_, ...) cvar->ConsoleColorPrintf(ColorRGBA( 255, 223, 0 ), ("[McDota:%s] " f_ ), __FUNCTION__, ##__VA_ARGS__)

namespace Interfaces
{
	bool FindInterfaces();
	void DumpInterfaces( const char *fileName );
}
