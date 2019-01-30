#include "integritycheck.h"

bool Integrity::VMTsHaveMisMatch( ) {

    uint32_t cameraNum = 41;
    uint32_t clientModeNum = 69;
    uint32_t dotaPlayerNum = 459;
    uint32_t gameEventManagerNum = 17;
    uint32_t networkMessagesNum = 34;
    uint32_t panoramaCPanel2DNum = 91;
    uint32_t panoramaUIPanelNum = 329;
    uint32_t viewRenderNum = 34;
    uint32_t vScriptGameSystemNum = 75;
    uint32_t panoramaEngineNum = 204;
    uint32_t networkClientServiceNum = 77;
    uint32_t networkGameClientNum = 172;
    uint32_t engineServiceMgrNum = 53;

    bool mismatchFound = false;

    if( engine->IsInGame() ){
        int localID = engine->GetLocalPlayer();
        CDotaPlayer *localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(localID);
        if( !localPlayer )
            cvar->ConsoleDPrintf("[%s]ERROR! Couldn't grab localplayer while in-game\n", __func__);
        if( dotaPlayerNum != CountVMs(localPlayer) ){
            cvar->ConsoleDPrintf("[%s]ERROR: localPlayerVMs does not match; Is: (%d), should be: (%d)\n", __func__, CountVMs(localPlayer), dotaPlayerNum);
            mismatchFound = true;
        }
    }

    if( CountVMs(camera) != cameraNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: Camera VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(camera), cameraNum);
        mismatchFound = true;
    }
    if( CountVMs(clientMode) != clientModeNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: Client Mode VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(clientMode), clientModeNum);
        mismatchFound = true;
    }
    if( CountVMs(gameEventManager) != gameEventManagerNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: Game Event Manager VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(gameEventManager), gameEventManagerNum);
        mismatchFound = true;
    }
    if( CountVMs(networkMessages) != networkMessagesNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: networkMessages VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(networkMessages), networkMessagesNum);
        mismatchFound = true;
    }
    if( CountVMs(gDBPlayPanel) != panoramaCPanel2DNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: CPanel2D VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(gDBPlayPanel), panoramaCPanel2DNum);
        mismatchFound = true;
    }

    panorama::IUIPanel *exampleUIPanel = panoramaEngine->AccessUIEngine()->GetPanelArray()->slots[0].panel; // 0 = DotaDashboard
    if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer(exampleUIPanel) ){
        if( CountVMs(exampleUIPanel) != panoramaUIPanelNum ){
            cvar->ConsoleDPrintf("[%s]ERROR: UIPanelVMs does not match; Is: (%d), should be: (%d)\n", __func__, CountVMs(exampleUIPanel), panoramaUIPanelNum);
            mismatchFound = true;
        }
    } else {
        cvar->ConsoleDPrintf("[%s]Warning: UI Panel[0] was INVALID!\n", __func__);
    }
    if( CountVMs(viewRender) != viewRenderNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: viewRender VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(viewRender), viewRenderNum);
        mismatchFound = true;
    }
    if( CountVMs(vscriptSystem) != vScriptGameSystemNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: vScriptSystem VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(vscriptSystem), vScriptGameSystemNum);
        mismatchFound = true;
    }
    if( CountVMs(panoramaEngine->AccessUIEngine()) != panoramaEngineNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: Panorama UI Engine VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(panoramaEngine->AccessUIEngine()), panoramaEngineNum);
        mismatchFound = true;
    }
    if( CountVMs(networkClientService) != networkClientServiceNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: networkClientService VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(networkClientService), networkClientServiceNum);
        mismatchFound = true;
    } else if( CountVMs(networkClientService->GetIGameClient()) != networkGameClientNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: networkClientService->IGameClient() VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(networkClientService->GetIGameClient()), networkGameClientNum);
        mismatchFound = true;
    }
    if( CountVMs(engineServiceMgr) != engineServiceMgrNum ){
        cvar->ConsoleDPrintf("[%s]ERROR: EngineServiceMgr VM count does not match; Is: (%d), should be: (%d)\n", __func__,  CountVMs(engineServiceMgr), engineServiceMgrNum);
        mismatchFound = true;
    }

    return mismatchFound;
}