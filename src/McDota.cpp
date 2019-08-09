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
void Main()
{
    /* Setup new Signal Handler */
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = SignalHandler;
    sigaction(SIGXCPU, &sa, &oldSa); // set ours and backup the old one at the same time.

    Interfaces::DumpInterfaces( "/tmp/dotainterfaces.txt" );

    if( !Interfaces::FindInterfaces() ){
        ConMsg( "[McDota] FindInterfaces() Failed. Stopping...\n" );
        return;
    }
    if( !Integrity::CheckInterfaceVMs() ){
        MC_PRINTF_ERROR( "CheckInterfaceVMs() Failed. Stopping...\n");
        return;
    }
    if( !Scanner::FindAllSigs() ){
        MC_PRINTF_ERROR("Failed to find one of the Signatures. Stopping...\n");
        return;
    }
    if( Integrity::VMTsHaveMisMatch() ){
        MC_PRINTF_ERROR("One of the VMs has had a Mismatch. Stopping...\n");
        return;
    }
    if( !Settings::RegisterCustomConvars() ){
        MC_PRINTF_ERROR("Error Registering ConVars, Stopping...\n");
        return;
    }
    if( !PaintTraverse::InitFonts() ){
        MC_PRINTF_ERROR("Paint Fonts Failed to Initialize, Stopping...\n");
    }

    cvar->ConsoleColorPrintf( ColorRGBA(10, 210, 10), "[McDota] I'm in like Flynn.\n" );

    int width, height;
    engine->GetScreenSize( width, height );
    MC_PRINTF( "Your Dota 2 was Built on - %s - %s\n", engine->GetBuildDateString(), engine->GetBuildTimeString() );
    MC_PRINTF( "ScreenSize: %dx%d - Max Clients: %d\n", width, height, engine->GetMaxClients() );
    MC_PRINTF( "client @ %p\n", (void*)client );
    MC_PRINTF( "viewRender @ %p\n", (void*)viewRender );
    MC_PRINTF( "clientMode @ %p\n", (void*)clientMode );
    MC_PRINTF( "Camera @ %p\n", (void*)camera );
    MC_PRINTF( "GameEventManger @ %p\n", (void*)gameEventManager );
    MC_PRINTF( "NetworkGameClient @ %p\n",(void*)networkClientService->GetIGameClient() );
    MC_PRINTF( "SoundOpSystem @ %p\n", (void*)soundOpSystem );
    MC_PRINTF( "VScriptSystem @ %p\n", (void*)vscriptSystem );
    MC_PRINTF( "CFontManager @ %p\n", (void*)fontManager );
    MC_PRINTF( "CEngineServiceMgr @ %p\n", (void*)engineServiceMgr );
    MC_PRINTF( "Active Loop Name: (%s) | Addon String: (%s)\n", engineServiceMgr->GetActiveLoopName(), engineServiceMgr->GetAddonsString() );
    MC_PRINTF( "RichPresence @ %p\n", (void*)richPresence );
    MC_PRINTF( "UI Engine @(%p) | Running? (%s)\n", (void*)panoramaEngine->AccessUIEngine(), panoramaEngine->AccessUIEngine()->IsRunning() ? "yes" : "no" );
    MC_PRINTF( "GetAllClasses @ %p\n", (void*)client->GetAllClasses() );
    MC_PRINTF( "ParticleSystemMgr @ %p\n", (void*)particleSystemMgr );
    MC_PRINTF( "CNetworkMessages @ %p\n", (void*)networkMessages );
    MC_PRINTF( "CGameEventSystem @ %p\n", (void*)gameEventSystem );
    //networkClientService->PrintSpawnGroupStatus();
    //networkClientService->PrintConnectionStatus();

    clientVMT = new VMT(client);
    clientVMT->HookVM(Hooks::FrameStageNotify, 29);
    clientVMT->ApplyVMT();

    gameEventManagerVMT = new VMT(gameEventManager);
    gameEventManagerVMT->HookVM(Hooks::FireEventClientSide, 9);
    gameEventManagerVMT->ApplyVMT();

    soundOpSystemVMT = new VMT(soundOpSystem);
    soundOpSystemVMT->HookVM(Hooks::StartSoundEvent, 11);
    soundOpSystemVMT->HookVM(Hooks::StartSoundEvent2, 12);
    soundOpSystemVMT->ApplyVMT();

    clientModeVMT = new VMT(clientMode);
    clientModeVMT->HookVM(Hooks::CreateMove, 28);
    clientModeVMT->ApplyVMT();

    panelVMT = new VMT(panel);
    panelVMT->HookVM(Hooks::PaintTraverse, 55);
    panelVMT->ApplyVMT();

	inputInternalVMT = new VMT(inputInternal);
    inputInternalVMT->HookVM(Hooks::SetKeyCodeState, 96);
    inputInternalVMT->ApplyVMT();

    uiEngineVMT = new VMT(panoramaEngine->AccessUIEngine());
    uiEngineVMT->HookVM(Hooks::DispatchEvent, 49);
    uiEngineVMT->HookVM(Hooks::RunScript, 110);
    uiEngineVMT->ApplyVMT();

    gameEventSystemVMT = new VMT( gameEventSystem );
    gameEventSystemVMT->HookVM(Hooks::PostEventAbstract, 15);
    gameEventSystemVMT->ApplyVMT();

  std::random_device dev;
  srand(dev()); // Seed random # Generator so we can call rand() later

    Util::RemoveLinkMapEntry("libMcDota.so", &mcPrev, &mcCurr, &mcNext);
    Netvars::DumpNetvars( "/tmp/dotanetvars.txt" );
    Netvars::CacheNetvars();

    int localID = engine->GetLocalPlayer();
    auto *localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(localID);
    if( !localPlayer )
        return;

    /* In Game */
    MC_PRINTF("Engine timescale: %f\n", engine->GetTimeScale() );
    MC_PRINTF( "localPlayer: %p, Schema-Name :%s, PlayerName: %s, ID: %d\n", (void*)localPlayer, localPlayer->Schema_DynamicBinding()->bindingName, localPlayer->C_DOTAPlayer__GetPlayerName(), localID );

	//MC_PRINTF( "health: %d, actualHealth: %d\n", localPlayer->C_BaseEntity__GetHealth(), localPlayer->C_BaseEntity__GetActualHealth());

    MC_PRINTF( "MaxClients: %d, Current map: %s (%s)\n", globalVars->maxClients, globalVars->currentMap, globalVars->currentMapName);

}
/* Entrypoint to the Library. Called when loading */
int __attribute__((constructor)) Startup()
{
    /* This detach saves about 0.5 seconds while loading currently */
    /* real	0m3.333s vs real 0m3.875s*/
    std::thread mainThread(Main);
    mainThread.detach();

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
        cvar->FindVar("cl_mouseenable")->SetValue(1);
        cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), "[McDota] I'm outta here.\n");
    } else {
        ConMsg( "[McDota] I'm outta here.\n" );
    }

    /* Restore previous signal handler */
    /* SIGXCPU actually just normally kills the game lol */
    sigaction(SIGXCPU, &oldSa, nullptr );
}
