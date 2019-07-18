#include "Integritycheck.h"

bool Integrity::VMTsHaveMisMatch( ) {

    uint32_t cameraNum = 42;
    uint32_t clientModeNum = 64;
    uint32_t dotaPlayerNum = 439;
    uint32_t gameEventManagerNum = 17;
    uint32_t networkMessagesNum = 34;
    uint32_t panoramaCPanel2DNum = 80;
    uint32_t panoramaUIPanelNum = 334;
    uint32_t viewRenderNum = 35;
    uint32_t vScriptGameSystemNum = 58;
    uint32_t panoramaEngineNum = 182;
    uint32_t networkClientServiceNum = 69;
    uint32_t networkGameClientNum = 123;

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

    return mismatchFound;
}

/* GetInterface() Adds to interfacesMetaDataList */
bool Integrity::CheckInterfaceVMs( )
{
    bool areVMsGood = true;
    for( unsigned int i = 0; i < grabbedInterfaces.size(); i++ ){
        if( grabbedInterfaces[i].numVMs == 0 )
            continue;
        uint32_t vmCount = CountVMs(grabbedInterfaces[i].interface);

        if( grabbedInterfaces[i].numVMs != vmCount ){
            ConMsg("Warning: Interface \"%s\"(%s) (%p) Has Changed. Expected it to have %d VMs; has %d VMs. Check for Broken offsets and Update interfaces.cpp \n",
                   grabbedInterfaces[i].name,
                   Memory::GetModuleName( (uintptr_t)grabbedInterfaces[i].interface ),
                   grabbedInterfaces[i].interface,
                   grabbedInterfaces[i].numVMs,
                   vmCount);

            areVMsGood = false;
        }
    }
    return areVMsGood;
}