#pragma once

#include "SDK/SDK.h"
#include "Utils/vmt.h"

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

// Special Panels
inline panorama::CPanel2D* gDBPlayPanel;

namespace Interfaces
{
	bool FindInterfaces();
	void DumpInterfaces( const char *fileName );
    bool CheckInterfaceVMs();
}
