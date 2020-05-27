#include "GUI/Gui.h"
#include "Hooks/HardHooks.h"
#include "Hooks/Hooks.h"
#include "Interfaces.h"
#include "Netvars.h"
#include "SDK/ConMsg.h"
#include "Scanner.h"
#include "Settings.h"
#include "Utils/Integritycheck.h"
#include "Utils/Util_sdk.h"
#include "Utils/Memory.h"
#include "Utils/Logger.h"

#include <dlfcn.h> //dlopen
#include <link.h> // link map

struct sigaction sa;
struct sigaction oldSa;

void *mcPrev, *mcCurr, *mcNext;

/* We need to restore the linkmap before our unloading will work.
 * The unload script will send a signal that we intercept here */
static void RestoreLinkMapEntry( int sigNum, siginfo_t *si, void * uContext )
{
    if( mcPrev )
    {
        auto *previousEntry = reinterpret_cast<link_map*>(mcPrev);
        previousEntry->l_next = reinterpret_cast<link_map*>(mcCurr);
    }
    if( mcNext )
    {
        auto *nextEntry = reinterpret_cast<link_map*>(mcNext);
        nextEntry->l_prev = reinterpret_cast<link_map*>(mcCurr);
    }
}

/* Removes McDota from Library-Level dynamic library linked list
 * saves the prev/curr/next void ptrs for unloading. */
static void RemoveLinkMapEntry()
{
    auto *map = reinterpret_cast<struct link_map*>(dlopen(nullptr, RTLD_NOW));
    map = map->l_next->l_next;
    while (map) {
        if( strstr( map->l_name, "libMcDota.so" ) != nullptr ){
            mcPrev = map->l_prev;
            mcCurr = map;
            mcNext = map->l_next;
            if( map->l_prev ){
                map->l_prev->l_next = map->l_next;
            }
            if( map->l_next ){
                map->l_next->l_prev = map->l_prev;
            }
            return;
        }
        map = map->l_next;
    }
}

/* Entrypoint to the Library. Called when loading */
int __attribute__((constructor)) Startup()
{
    /* Setup new Signal Handler */
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = RestoreLinkMapEntry;
    sigaction(SIGXCPU, &sa, &oldSa); // set ours and backup the old one at the same time.

    if( !Interfaces::FindExportedInterfaces( ) ){
        ConMsg( "[McDota] FindExportedInterfaces() Failed. Stopping...\n" );
        return 1;
    }
    if( !Integrity::CheckInterfaceVMs() ){
        ConMsg( "[McDota] CheckInterfaceVMs() Failed. Stopping...\n" );
        return 2;
    }
    /* The filesystem interface will only look in search paths. Add one so we can write in /tmp/. */
    fileSystem->AddSearchPath( "/tmp/", "TMPDIR", SearchPathAdd_t::PATH_ADD_TO_TAIL, 1 );
    /* Create our logfile in /tmp/ */
    Logger::logFile = fileSystem->Open("dota.log", "a+", "TMPDIR" );
    if( !Logger::logFile ){
        MC_PRINTF_ERROR("Couldn't create the logfile! Stopping...\n");
        return 3;
    }
    if( !Scanner::FindAllSigs() ){
        MC_PRINTF_ERROR("Failed to find one of the Signatures. Stopping...\n");
        return 4;
    }
    if( Integrity::VMTsHaveMisMatch() ){
        MC_PRINTF_ERROR("One of the VMs has had a Mismatch. Stopping...\n");
        return 5;
    }
    if( !Settings::RegisterCustomConvars() ){
        MC_PRINTF_ERROR("Error Registering ConVars, Stopping...\n");
        return 6;
    }
    if( !PaintTraverse::InitFonts() ){
        MC_PRINTF_ERROR("Paint Fonts Failed to Initialize, Stopping...\n");
        return 7;
    }

    Interfaces::DumpInterfaces( "/tmp/dotainterfaces.txt" );

    cvar->ConsoleColorPrintf( ColorRGBA(10, 210, 10), "[McDota] I'm in like Flynn.\n" );

    int width, height;
    engine->GetScreenSize( width, height );
    MC_PRINTF( "Your Dota 2 was Built on - %s - %sPST\n", engine->GetBuildDateString(), engine->GetBuildTimeString() );
    MC_PRINTF( "ScreenSize: %dx%d - Max Clients: %d\n", width, height, engine->GetMaxClients() );
    MC_PRINTF( "client @ %p - [%s]\n", (void*)client, Memory::GetModuleName((uintptr_t(client))) );
    MC_PRINTF( "viewRender @ %p - [%s]\n", (void*)viewRender, Memory::GetModuleName((uintptr_t(viewRender))) );
    MC_PRINTF( "clientMode @ %p - [%s]\n", (void*)clientMode, Memory::GetModuleName((uintptr_t(clientMode))) );
    MC_PRINTF( "Camera @ %p - [%s]\n", (void*)camera, Memory::GetModuleName((uintptr_t(camera))) );
    MC_PRINTF( "GameEventManger @ %p - [%s]\n", (void*)gameEventManager, Memory::GetModuleName((uintptr_t(gameEventManager))) );
    MC_PRINTF( "SoundOpSystem @ %p - [%s]\n", (void*)soundOpSystem, Memory::GetModuleName((uintptr_t(soundOpSystem))) );
    MC_PRINTF( "VScriptSystem @ %p - [%s]\n", (void*)vscriptSystem, Memory::GetModuleName((uintptr_t(vscriptSystem))) );
    MC_PRINTF( "CFontManager @ %p - [%s]\n", (void*)fontManager, Memory::GetModuleName((uintptr_t(fontManager))) );
    MC_PRINTF( "CEngineServiceMgr @ %p - [%s]\n", (void*)engineServiceMgr, Memory::GetModuleName((uintptr_t(engineServiceMgr))) );
    MC_PRINTF( "RichPresence @ %p - [%s]\n", (void*)richPresence, Memory::GetModuleName((uintptr_t(richPresence))) );
    MC_PRINTF( "ParticleSystemMgr @ %p - [%s]\n", (void*)particleSystemMgr, Memory::GetModuleName((uintptr_t(particleSystemMgr))) );
    MC_PRINTF( "CNetworkMessages @ %p - [%s]\n", (void*)networkMessages, Memory::GetModuleName((uintptr_t(networkMessages))) );
    MC_PRINTF( "CGameEventSystem @ %p - [%s]\n", (void*)gameEventSystem, Memory::GetModuleName((uintptr_t(gameEventSystem))) );
    MC_PRINTF( "CVPhys2World @ %p - [%s]\n", (void*)phys2World, Memory::GetModuleName((uintptr_t(phys2World))) );
    MC_PRINTF( "UI Engine @(%p) | Running? (%s)\n", (void*)panoramaEngine->AccessUIEngine(), panoramaEngine->AccessUIEngine()->IsRunning() ? "yes" : "no" );
    MC_PRINTF( "Active Loop Name: (%s) | Addon String: (%s)\n", engineServiceMgr->GetActiveLoopName(), engineServiceMgr->GetAddonsString() );
    MC_PRINTF( "NetworkGameClient @ %p - [%s]\n",(void*)networkClientService->GetIGameClient(), Memory::GetModuleName( uintptr_t(networkClientService->GetIGameClient()) ) );
    MC_PRINTF( "GetAllClasses @ %p - [%s]\n", (void*)client->GetAllClasses(), Memory::GetModuleName( uintptr_t(client->GetAllClasses()) ) );
    MC_PRINTF( "World2Screen @ %p - RenderGameSystem @ %p\n", g_WorldToScreen, renderGameSystem);
    MC_PRINTF( "Camera @ %p\n", (void*)camera );

    clientVMT = std::unique_ptr<VMT>(new VMT(client));
    clientVMT->HookVM(Hooks::FrameStageNotify, 29);
    clientVMT->ApplyVMT();

    clientModeVMT = std::unique_ptr<VMT>(new VMT(clientMode));
    clientModeVMT->HookVM(Hooks::CreateMove, 29);
    clientModeVMT->HookVM(Hooks::LevelInit, 30);
    clientModeVMT->ApplyVMT();

    gameEventManagerVMT = std::unique_ptr<VMT>(new VMT(gameEventManager));
    gameEventManagerVMT->HookVM(Hooks::CreateEvent, 7);
    gameEventManagerVMT->HookVM(Hooks::FireEventClientSide, 9);
    gameEventManagerVMT->ApplyVMT();

    soundOpSystemVMT = std::unique_ptr<VMT>(new VMT(soundOpSystem));
    soundOpSystemVMT->HookVM(Hooks::StartSoundEvent, 11);
    soundOpSystemVMT->HookVM(Hooks::StartSoundEvent2, 12);
    soundOpSystemVMT->ApplyVMT();

    panelVMT = std::unique_ptr<VMT>(new VMT(panel));
    panelVMT->HookVM(Hooks::PaintTraverse, 55);
    panelVMT->ApplyVMT();

	inputInternalVMT = std::unique_ptr<VMT>(new VMT(inputInternal));
    inputInternalVMT->HookVM(Hooks::SetKeyCodeState, 96);
    inputInternalVMT->ApplyVMT();

    uiEngineVMT = std::unique_ptr<VMT>(new VMT(panoramaEngine->AccessUIEngine()));
    uiEngineVMT->HookVM(Hooks::RunScript, 111);
    uiEngineVMT->ApplyVMT();

    particleSystemVMT = std::unique_ptr<VMT>(new VMT( particleSystemMgr ));
    particleSystemVMT->HookVM(Hooks::CreateParticleCollection, 18);
    particleSystemVMT->HookVM(Hooks::DeleteParticleCollection, 19);
    particleSystemVMT->ApplyVMT();

    networkSystemVMT = std::unique_ptr<VMT>(new VMT( networkSystem ));
    networkSystemVMT->HookVM(Hooks::CreateNetChannel, 28);
    networkSystemVMT->ApplyVMT();

    Netvars::DumpNetvars( client, "/tmp/dotanetvars.txt" );
    Netvars::CacheNetvars( client );

    if( engine->IsInGame() ){
        Interfaces::HookDynamicVMTs();

        if( engine->GetNetChannelInfo() ) {
            MC_PRINTF( "Grabbing new NetChannel VMT - %p\n", (void*)engine->GetNetChannelInfo() );
            netChannelVMT = std::unique_ptr<VMT>(new VMT( engine->GetNetChannelInfo( ) ));
            netChannelVMT->HookVM( Hooks::SendNetMessage, 71 );
            netChannelVMT->HookVM( Hooks::PostReceivedNetMessage, 89 );
            netChannelVMT->ApplyVMT( );
        } else {
            MC_PRINTF_WARN("GetNetChannelInfo returned null! Aborting NetChannel VMT!\n");
        }
    }

    if( !Util::ReadParticleFiles( "TMPDIR", "dotaparticleblacklist.txt", "dotaparticletracker.txt" ) ){
        MC_PRINTF_WARN("Specified particle file/s was missing or empty - Particle filters may not be set.\n");
    }

    RemoveLinkMapEntry();

    return 0;
}
/* Called when un-injecting the library */
void __attribute__((destructor)) Shutdown()
{
    /* Remove Hard Hooks (if any) */
    HardHooks::BAsyncSendProto.Remove();
    HardHooks::DispatchPacket.Remove();

    /* Reset camera mods */
    if( camera && engine && engine->IsInGame() ){
        camera->SetMinPitch( -1.0f );
        camera->SetMaxPitch( -1.0f );
        camera->SetExtraYaw( 0.0f );
        camera->SetDistanceToLookAtPos( 1200.0f );
    }

    /* Cleanup panels */
    if( panoramaEngine ){
        if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer( UI::mcDota ) ){
            UI::mcDota->RemoveAndDeleteChildren();
            panorama::IUIPanel *root = UI::mcDota->GetParent();
            if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer( root ) ){
                root->RemoveChild( UI::mcDota );
            } else {
                MC_PRINTF("ERROR unloading, root panel is invalid! (%p)\n", root );
            }
        }
    }

    /* Cleanup ConVars we have made */
    if( cvar ){
        for( ConVar* var : Util::createdConvars ){
            cvar->UnregisterConCommand(var);
                delete[] var->m_pszName;
                delete[] var->m_Value.m_pszString;
                delete[] var->m_pszDefaultValue;
                delete[] var->m_pszHelpString;
                delete[] var->m_fnChangeCallbacks.m_pElements;
            delete (char*)var; // cast so we dont invoke destructor
        }
        cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), "[McDota] I'm outta here.\n");
    } else {
        ConMsg( "[McDota] I'm outta here.\n" );
    }

    /* Close logfile */
    fileSystem->Close( Logger::logFile );
    /* Remove our added filesystem search path. */
    fileSystem->RemoveSearchPath( "/tmp/", "TMPDIR" );

    /* Restore previous signal handler */
    /* SIGXCPU actually just normally kills the game lol */
    sigaction(SIGXCPU, &oldSa, nullptr );
}
