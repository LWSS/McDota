#include "GUI/Gui.h"
#include "Hooks/HardHooks.h"
#include "Hooks/Hooks.h"
#include "Interfaces.h"
#include "Netvars.h"
#include "SDK/ConMsg.h"
#include "Scanner.h"
#include "Settings.h"
#include "Utils/Integritycheck.h"
#include "Utils/Util.h"
#include "Utils/Util_sdk.h"
#include "Utils/Memory.h"

#include <csignal>
#include <random>
#include <thread>

const char *Util::logFileName = "/tmp/dota.log";
void *mcPrev, *mcCurr, *mcNext;

struct sigaction sa;
struct sigaction oldSa;

/* We need to restore the linkmap before our unloading will work.
 * The unload script will send a signal that we intercept here */
static void SignalHandler( int sigNum, siginfo_t *si, void * uContext )
{
    std::string path("/proc/");
    path += std::to_string( si->si_pid );
    path += "/comm";

    std::string procName;
    if( Util::GetFileContents( path.c_str(), &procName ) ){
        Util::Log( "Failed to open file (%s) for checking signal sender\n", path.c_str() );
        return;
    }

    if( strstr( procName.c_str(), "uload" ) == nullptr ){
        Util::Log("Received a Foreign Unload Signal from Process: (%s). Intruder alert!", procName.c_str());
        return;
    }

    Util::Log("Unload Signal Received from process (%s), Looks ok.\n", procName.c_str());

    Util::RestoreLinkMapEntry( mcPrev, mcCurr, mcNext );
}
/* Entrypoint to the Library. Called when loading */
int __attribute__((constructor)) Startup()
{
    /* Setup new Signal Handler */
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = SignalHandler;
    sigaction(SIGXCPU, &sa, &oldSa); // set ours and backup the old one at the same time.

    Interfaces::DumpInterfaces( "/tmp/dotainterfaces.txt" );

    if( !Interfaces::FindExportedInterfaces( ) ){
        ConMsg( "[McDota] FindExportedInterfaces() Failed. Stopping...\n" );
        return 1;
    }
    if( !Integrity::CheckInterfaceVMs() ){
        MC_PRINTF_ERROR("CheckInterfaceVMs() Failed. Stopping...\n");
        return 2;
    }
    if( !Scanner::FindAllSigs() ){
        MC_PRINTF_ERROR("Failed to find one of the Signatures. Stopping...\n");
        return 3;
    }
    if( Integrity::VMTsHaveMisMatch() ){
        MC_PRINTF_ERROR("One of the VMs has had a Mismatch. Stopping...\n");
        return 4;
    }
    if( !Settings::RegisterCustomConvars() ){
        MC_PRINTF_ERROR("Error Registering ConVars, Stopping...\n");
        return 5;
    }
    if( !PaintTraverse::InitFonts() ){
        MC_PRINTF_ERROR("Paint Fonts Failed to Initialize, Stopping...\n");
        return 6;
    }

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
    //networkClientService->PrintSpawnGroupStatus();
    //networkClientService->PrintConnectionStatus();

    clientVMT = new VMT(client);
    clientVMT->HookVM(Hooks::FrameStageNotify, 29);
    clientVMT->ApplyVMT();

    clientModeVMT = new VMT(clientMode);
    clientModeVMT->HookVM(Hooks::CreateMove, 29);
    clientModeVMT->HookVM(Hooks::LevelInit, 30);
    clientModeVMT->ApplyVMT();

    gameEventManagerVMT = new VMT(gameEventManager);
    gameEventManagerVMT->HookVM(Hooks::FireEventClientSide, 9);
    gameEventManagerVMT->ApplyVMT();

    soundOpSystemVMT = new VMT(soundOpSystem);
    soundOpSystemVMT->HookVM(Hooks::StartSoundEvent, 11);
    soundOpSystemVMT->HookVM(Hooks::StartSoundEvent2, 12);
    soundOpSystemVMT->ApplyVMT();

    panelVMT = new VMT(panel);
    panelVMT->HookVM(Hooks::PaintTraverse, 55);
    panelVMT->ApplyVMT();

	inputInternalVMT = new VMT(inputInternal);
    inputInternalVMT->HookVM(Hooks::SetKeyCodeState, 96);
    inputInternalVMT->ApplyVMT();

    uiEngineVMT = new VMT(panoramaEngine->AccessUIEngine());
    uiEngineVMT->HookVM(Hooks::RunScript, 110);
    uiEngineVMT->ApplyVMT();

    gameEventSystemVMT = new VMT( gameEventSystem );
    gameEventSystemVMT->HookVM(Hooks::PostEventAbstract, 15);
    gameEventSystemVMT->ApplyVMT();

    particleSystemVMT = new VMT( particleSystemMgr );
    particleSystemVMT->HookVM(Hooks::CreateParticleCollection, 18);
    particleSystemVMT->HookVM(Hooks::DeleteParticleCollection, 19);
    particleSystemVMT->ApplyVMT();

    networkSystemVMT = new VMT( networkSystem );
    networkSystemVMT->HookVM(Hooks::CreateNetChannel, 28);
    networkSystemVMT->ApplyVMT();

    std::random_device dev;
    srand(dev()); // Seed random # Generator so we can call rand() later

    Netvars::DumpNetvars( "/tmp/dotanetvars.txt" );
    Netvars::CacheNetvars();

    if( engine->IsInGame() ){
        Interfaces::HookDynamicVMTs();

        if( (!netChannelVMT || (engine->GetNetChannelInfo() != (void*)netChannelVMT->interface)) ){
            delete netChannelVMT;

            if( engine->GetNetChannelInfo() ) {
                MC_PRINTF( "Grabbing new NetChannel VMT - %p\n", (void*)engine->GetNetChannelInfo() );
                netChannelVMT = new VMT( engine->GetNetChannelInfo( ) );
                netChannelVMT->HookVM( Hooks::SendNetMessage, 66 );
                netChannelVMT->HookVM( Hooks::PostReceivedNetMessage, 84 );
                netChannelVMT->ApplyVMT( );
            } else {
                MC_PRINTF_WARN("GetNetChannelInfo returned null! Aborting NetChannel VMT!\n");
            }
        }
    }

    // TODO: prob move this to ~/.config/
    if( !Util::ReadParticleFiles("/tmp/dotaparticleblacklist.txt", "/tmp/dotaparticletracker.txt" ) ){
        MC_PRINTF_WARN("Specified particle file/s was missing or empty - Particle filters may not be set.\n");
    }

    Util::RemoveLinkMapEntry("libMcDota.so", &mcPrev, &mcCurr, &mcNext);

    return 0;
}
/* Called when un-injecting the library */
void __attribute__((destructor)) Shutdown()
{
    /* Remove Hard Hooks (if any) */
    HardHooks::BAsyncSendProto.Remove();
    HardHooks::DispatchPacket.Remove();

    /* Release all VMTs */
    for( VMT* vmt : createdVMTs ){
        delete vmt;
    }

    /* Reset camera mods */
    if( camera && engine && engine->IsInGame() ){
        camera->SetMinPitch( -1.0f );
        camera->SetMaxPitch( -1.0f );
        camera->SetExtraYaw( 0.0f );
        camera->SetDistanceToLookAtPos( 1134.0f );
    }


    if( panoramaEngine ){
        /* Cleanup panels */
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


    if( cvar ){
        /* Cleanup ConVars we have made */
        for( ConCommandBase* var : Util::createdConvars ){
            cvar->UnregisterConCommand(var);
                delete[] var->name;
                delete[] var->strValue;
                delete[] var->strDefault;
                delete[] var->description;
            delete var;
        }
        cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), "[McDota] I'm outta here.\n");
    } else {
        ConMsg( "[McDota] I'm outta here.\n" );
    }

    /* Restore previous signal handler */
    /* SIGXCPU actually just normally kills the game lol */
    sigaction(SIGXCPU, &oldSa, nullptr );
}
