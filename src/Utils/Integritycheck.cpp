#include "Integritycheck.h"

static void PrintVMTError( const char *className, uint32_t old, uint32_t now ){
    MC_PRINTF_ERROR("%s VM count does not match! [%d]->[%d]\n", className, old, now);
}

struct VMTEntry
{
    const char *name;
    void **ptrToAddr;
    uint32_t expectedLen;
} vms[] = {
        { "Camera", (void**)&camera, 42 },
        { "Client Mode", (void**)&clientMode, 65 },
        { "Game Event Manager", (void**)&gameEventManager, 17 },
        { "NetworkMessages", (void**)&networkMessages, 34 },
        { "CPanel2D", (void**)&gDBPlayPanel, 81 },
        { "viewRender", (void**)&viewRender, 35 },
        { "vScriptSystem", (void**)&vscriptSystem, 58 },
        { "networkClientService", (void**)&networkClientService, 69 },
};

bool Integrity::VMTsHaveMisMatch( ) {
    uint32_t dotaPlayerNum = 443;
    uint32_t panoramaUIPanelNum = 338;
    uint32_t uiEngineNum = 182;
    uint32_t networkGameClientNum = 124;

    bool mismatchFound = false;

    /* Custom Checks */
    if( engine->IsInGame() ){
        int localID = engine->GetLocalPlayer();
        auto *localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(localID);
        if( !localPlayer )
            MC_PRINTF_ERROR("Couldn't grab localplayer while in-game\n");
        if( dotaPlayerNum != CountVMs(localPlayer) ){
            PrintVMTError( "localPlayer", dotaPlayerNum, CountVMs( localPlayer ) );
            mismatchFound = true;
        }
    }

    panorama::IUIPanel *exampleUIPanel = panoramaEngine->AccessUIEngine()->GetPanelArray()->slots[0].panel; // 0 = DotaDashboard
    if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer(exampleUIPanel) ){
        if( CountVMs(exampleUIPanel) != panoramaUIPanelNum ){
            PrintVMTError( "UIPanel", panoramaUIPanelNum, CountVMs( exampleUIPanel ) );
            mismatchFound = true;
        }
    } else {
        MC_PRINTF_WARN("UI Panel[0] was INVALID!\n");
    }

    if( CountVMs(networkClientService->GetIGameClient()) != networkGameClientNum ){
        PrintVMTError( "networkGameClient", networkGameClientNum, CountVMs( networkClientService->GetIGameClient( ) ) );
        mismatchFound = true;
    }

    if( CountVMs(panoramaEngine->AccessUIEngine()) != uiEngineNum ){
        PrintVMTError( "Panorama UI Engine", uiEngineNum, CountVMs( panoramaEngine->AccessUIEngine( ) ) );
        mismatchFound = true;
    }

    /* Static Checks */
    for( const VMTEntry &i : vms ){
        uint32_t num = CountVMs( *i.ptrToAddr );
        if( num != i.expectedLen ){
            PrintVMTError( i.name, i.expectedLen, num );
            mismatchFound = true;
        }
    }

    return mismatchFound;
}

/* GetInterface() Adds to interfacesMetaDataList */
bool Integrity::CheckInterfaceVMs( )
{
    bool areVMsGood = true;
    for(auto & grabbedInterface : grabbedInterfaces){
        if( grabbedInterface.numVMs == 0 )
            continue;
        uint32_t vmCount = CountVMs(grabbedInterface.interface);

        if( grabbedInterface.numVMs != vmCount ){
            ConMsg("Warning: Interface \"%s\"(%s) (%p) Has Changed. Expected it to have %d VMs; has %d VMs. Check for Broken offsets and Update interfaces.cpp \n",
                   grabbedInterface.name,
                   Memory::GetModuleName( (uintptr_t)grabbedInterface.interface ),
                   grabbedInterface.interface,
                   grabbedInterface.numVMs,
                   vmCount);

            areVMsGood = false;
        }
    }
    return areVMsGood;
}