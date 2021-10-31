#include "Integritycheck.h"

#include "../Interfaces.h"

#include <vector>

static void PrintVMTError( const char *className, uint32_t old, uint32_t now ){
    MC_PRINTF_ERROR("%s VM count does not match! [%d]->[%d]\n", className, old, now);
}

struct VMTEntry
{
    const char *name;
    void **ptrToAddr;
    uint32_t expectedLen;
    VMTEntry( const char *namer, void **ptr, uint32_t len ){
        name = namer;
        ptrToAddr = ptr;
        expectedLen = len;
    }
};

static std::vector<VMTEntry> vms = {
        { "Camera", (void**)&camera, 52 },
        { "Client Mode", (void**)&clientMode, 65 },
        { "Game Event Manager", (void**)&gameEventManager, 17 },
        { "CPanel2D", (void**)&gDBPlayPanel, 82 },
        { "viewRender", (void**)&viewRender, 35 },
        { "vScriptSystem", (void**)&vscriptSystem, 59 },
        { "networkClientService", (void**)&networkClientService, 69 },
};

static const uint32_t dotaPlayerNum = 380;
static const uint32_t baseNPCNum = 185;
static const uint32_t panoramaUIPanelNum = 360;
static const uint32_t uiEngineNum = 185;
static const uint32_t networkGameClientNum = 128;
static const uint32_t netChannelNum = 101;

bool Integrity::VMTsHaveMisMatch( ) {
    bool mismatchFound = false;

    /* In-Game Checks */
    if( engine->IsInGame() ){
        int localID = engine->GetLocalPlayer();
        auto *localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(localID);
        if( !localPlayer ) {
            MC_PRINTF_ERROR( "Couldn't grab localplayer while in-game\n" );
        } else {
            vms.emplace_back( "CDotaPlayer", (void**)&localPlayer, dotaPlayerNum );
        }

        CDotaBaseNPC *baseNPC = nullptr;
        int max = entitySystem->GetHighestEntityIndex();
        for( int i = 1; i <=max; i++ ) {
            CBaseEntity *entity = entitySystem->GetBaseEntity( i );
            if( !entity )
                continue;
            if( strstr( entity->Schema_DynamicBinding()->binaryName, "DOTA_Unit_Hero" ) ){
                baseNPC = (CDotaBaseNPC*)entity;
                break;
            }
        }

        if( !baseNPC ){
            MC_PRINTF_ERROR("Couldn't grab a Base NPC to test.\n");
        } else if( baseNPCNum != CountVMs( baseNPC ) ){
            vms.emplace_back( "BaseNPC", (void**)&baseNPC, baseNPCNum );
        }
    }


    panorama::IUIPanel *exampleUIPanel = panoramaEngine->AccessUIEngine()->GetPanelArray()->slots[0].panel; // 0 = DotaDashboard
    if( !exampleUIPanel || !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(exampleUIPanel) ){
        MC_PRINTF_ERROR("UI Panel[0] was INVALID!\n");
    } else {
        vms.emplace_back( "UIPanel", (void**)&exampleUIPanel, panoramaUIPanelNum );
    }

    auto networkGameClient = networkClientService->GetIGameClient();
    vms.emplace_back( "networkGameClient", (void**)&networkGameClient, networkGameClientNum );

    auto uiEngine = panoramaEngine->AccessUIEngine();
    vms.emplace_back( "Panorama UI Engine", (void**)&uiEngine, uiEngineNum );

    auto netChan = engine->GetNetChannelInfo();
    vms.emplace_back( "NetChannel", (void**)&netChan, netChannelNum );

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