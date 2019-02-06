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
            MC_PRINTF_ERROR("Couldn't grab localplayer while in-game\n");
        if( dotaPlayerNum != CountVMs(localPlayer) ){
            MC_PRINTF_ERROR("localPlayerVMs does not match; Is: (%d), should be: (%d)\n", CountVMs(localPlayer), dotaPlayerNum);
            mismatchFound = true;
        }
    }

    if( CountVMs(camera) != cameraNum ){
        MC_PRINTF_ERROR("Camera VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(camera), cameraNum);
        mismatchFound = true;
    }
    if( CountVMs(clientMode) != clientModeNum ){
        MC_PRINTF_ERROR("Client Mode VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(clientMode), clientModeNum);
        mismatchFound = true;
    }
    if( CountVMs(gameEventManager) != gameEventManagerNum ){
        MC_PRINTF_ERROR("Game Event Manager VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(gameEventManager), gameEventManagerNum);
        mismatchFound = true;
    }
    if( CountVMs(networkMessages) != networkMessagesNum ){
        MC_PRINTF_ERROR("NetworkMessages VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(networkMessages), networkMessagesNum);
        mismatchFound = true;
    }
    if( CountVMs(gDBPlayPanel) != panoramaCPanel2DNum ){
        MC_PRINTF_ERROR("CPanel2D VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(gDBPlayPanel), panoramaCPanel2DNum);
        mismatchFound = true;
    }

    panorama::IUIPanel *exampleUIPanel = panoramaEngine->AccessUIEngine()->GetPanelArray()->slots[0].panel; // 0 = DotaDashboard
    if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer(exampleUIPanel) ){
        if( CountVMs(exampleUIPanel) != panoramaUIPanelNum ){
            MC_PRINTF_ERROR("UIPanelVMs does not match; Is: (%d), should be: (%d)\n", CountVMs(exampleUIPanel), panoramaUIPanelNum);
            mismatchFound = true;
        }
    } else {
        MC_PRINTF_WARN("UI Panel[0] was INVALID!\n");
    }
    if( CountVMs(viewRender) != viewRenderNum ){
        MC_PRINTF_ERROR("viewRender VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(viewRender), viewRenderNum);
        mismatchFound = true;
    }
    if( CountVMs(vscriptSystem) != vScriptGameSystemNum ){
        MC_PRINTF_ERROR("vScriptSystem VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(vscriptSystem), vScriptGameSystemNum);
        mismatchFound = true;
    }
    if( CountVMs(panoramaEngine->AccessUIEngine()) != panoramaEngineNum ){
        MC_PRINTF_ERROR("Panorama UI Engine VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(panoramaEngine->AccessUIEngine()), panoramaEngineNum);
        mismatchFound = true;
    }
    if( CountVMs(networkClientService) != networkClientServiceNum ){
        MC_PRINTF_ERROR("networkClientService VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(networkClientService), networkClientServiceNum);
        mismatchFound = true;
    } else if( CountVMs(networkClientService->GetIGameClient()) != networkGameClientNum ){
        MC_PRINTF_ERROR("networkClientService->IGameClient() VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(networkClientService->GetIGameClient()), networkGameClientNum);
        mismatchFound = true;
    }
    if( CountVMs(engineServiceMgr) != engineServiceMgrNum ){
        MC_PRINTF_ERROR("EngineServiceMgr VM count does not match; Is: (%d), should be: (%d)\n", CountVMs(engineServiceMgr), engineServiceMgrNum);
        mismatchFound = true;
    }

    return mismatchFound;
}