#include <chrono>
#include <fcntl.h>
#include <sys/stat.h>
#include <csignal>
#include <fstream>
#include <sstream>
#include <zconf.h> //readlink
#include <thread>

#include "GUI/gui.h"
#include "Hacks/NoFog.h"
#include "Hooks/hooks.h"
#include "scanner.h"
#include "interfaces.h"
#include "Utils/util.h"
#include "Utils/util_sdk.h"
#include "Utils/integritycheck.h"
#include "SDK/ConMsg.h"
#include "settings.h"

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

    if( strstr( procName.c_str(), "uload" ) == NULL ){
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
        ConMsg( "FindInterfaces() Failed. Stopping...\n" );
        return;
    }
    if( !Interfaces::CheckInterfaceVMs() ){
        ConMsg( "CheckInterfaceVMs() Failed. Stopping...\n");
        return;
    }

    bool sigsOK = true;
    sigsOK &= Scanner::FindGlobalVars();
    sigsOK &= Scanner::FindGameEntitySystem();
    sigsOK &= Scanner::FindVScript();
    sigsOK &= Scanner::FindCNetworkMessages();
    sigsOK &= Scanner::FindPanelArrayOffset();
    sigsOK &= Scanner::FindViewRender();
    sigsOK &= Scanner::FindClientMode();
    sigsOK &= Scanner::FindCamera();
    sigsOK &= Scanner::FindGameEventManager();
    sigsOK &= Scanner::FindDBPlayPanel();
    sigsOK &= Scanner::FindSoundOpSystem();
    sigsOK &= Scanner::FindAcceptMatch();
    sigsOK &= Scanner::FindWorldToScreen();
    sigsOK &= Scanner::FindRichPresence();
    if( !sigsOK ){
        cvar->ConsoleColorPrintf(ColorRGBA(225, 5, 5),"Failed to find one of the Signatures. Stopping...\n");
        return;
    }
    if( Integrity::VMTsHaveMisMatch() ){
        cvar->ConsoleColorPrintf(ColorRGBA(225, 5, 5),"One of the VMs has had a Mismatch. Stopping...\n");
        return;
    }
    if( !Settings::RegisterCustomConvars() ){
        cvar->ConsoleColorPrintf(ColorRGBA(225, 5, 5),"Error Registering ConVars, Stopping...\n");
        return;
    }
    if( !PaintTraverse::InitFonts() ){
        cvar->ConsoleColorPrintf(ColorRGBA(225, 5, 5),"Paint Fonts Failed to Initialize, Stopping...\n");
    }

    cvar->ConsoleColorPrintf( ColorRGBA(10, 210, 10), "[McDota]I'm in like Flynn.\n" );

    int width, height;
    engine->GetScreenSize( width, height );
    cvar->ConsoleDPrintf( "Your Dota 2 was Built on - %s - %s\n", engine->GetBuildDateString(), engine->GetBuildTimeString() );
    cvar->ConsoleDPrintf( "ScreenSize: %dx%d\n", width, height );
    cvar->ConsoleDPrintf( "Max Clients: %d\n", engine->GetMaxClients() );
    //cvar->ConsoleDPrintf( "Group Count is: %d\n", networkMessages->GetNetworkGroupCount() );
    cvar->ConsoleDPrintf( "FOV is: %f | viewModel FOV is: %f\n", camera->GetFOV(), clientMode->GetViewModelFOV() );
    cvar->ConsoleDPrintf( "client @ %p\n", (void*)client );
    cvar->ConsoleDPrintf( "viewRender @ %p\n", (void*)viewRender );
    cvar->ConsoleDPrintf( "clientMode @ %p\n", (void*)clientMode );
    cvar->ConsoleDPrintf( "Camera @ %p\n", (void*)camera );
    cvar->ConsoleDPrintf( "Min Pitch: %f - Max Pitch: %f\n", camera->GetMinPitch(), camera->GetMaxPitch() );
    cvar->ConsoleDPrintf( "Viewmodel FOV: %f - Blurfade: %f\n", clientMode->GetViewModelFOV(), clientMode->GetBlurFade() );
    cvar->ConsoleDPrintf( "GameEventManger @ %p\n", (void*)gameEventManager );
    cvar->ConsoleDPrintf( "NetworkGameClient @ %p\n",(void*)networkClientService->GetIGameClient() );
    cvar->ConsoleDPrintf( "SoundOpSystem @ %p\n", (void*)soundOpSystem );
    cvar->ConsoleDPrintf( "VScriptSystem @ %p\n", (void*)vscriptSystem );
    cvar->ConsoleDPrintf( "CFontManager @ %p\n", (void*)fontManager );
    cvar->ConsoleDPrintf( "CEngineServiceMgr @ %p\n", (void*)engineServiceMgr );
    cvar->ConsoleDPrintf( "Active Loop Name: (%s) | Addon String: (%s)\n", engineServiceMgr->GetActiveLoopName(), engineServiceMgr->GetAddonsString() );
    cvar->ConsoleDPrintf( "RichPresence @ %p\n", (void*)richPresence );
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

    clientModeVMT = new VMT(clientMode, true);
    clientModeVMT->HookVM(Hooks::CreateMove, 28);
    clientModeVMT->ApplyVMT();

    panelVMT = new VMT(panel);
    panelVMT->HookVM(Hooks::PaintTraverse, 55);
    panelVMT->ApplyVMT();

	inputInternalVMT = new VMT(inputInternal);
    inputInternalVMT->HookVM(Hooks::SetKeyCodeState, 96);
    inputInternalVMT->ApplyVMT();

/*  // CAN BE UNSTABLE! RELATED TO THREADS
    uiEngineVMT = new VMT(panoramaEngine->AccessUIEngine());
    uiEngineVMT->HookVM(Hooks::RunScript, 110);
    uiEngineVMT->ApplyVMT();
*/
    cvar->ConsoleDPrintf("UI Engine @(%p) | Running? (%s)\n", (void*)panoramaEngine->AccessUIEngine(), panoramaEngine->AccessUIEngine()->IsRunning() ? "yes" : "no");

    srand(time(NULL)); // Seed random # Generator so we can call rand() later

    Util::RemoveLinkMapEntry("libMcDota.so", &mcPrev, &mcCurr, &mcNext);



    int localID = engine->GetLocalPlayer();
    CDotaPlayer *localPlayer = (CDotaPlayer*)entitySystem->GetBaseEntity(localID);
    if( !localPlayer )
        return;

    /* In Game */
    cvar->ConsoleDPrintf("Engine timescale: %f\n", engine->GetTimeScale() );
    cvar->ConsoleDPrintf( "localPlayer: %p, Schema-Name :%s, PlayerName: %s, ID: %d\n", (void*)localPlayer, localPlayer->Schema_DynamicBinding()->bindingName, localPlayer->C_DOTAPlayer__GetPlayerName(), localID );

	//cvar->ConsoleDPrintf( "health: %d, actualHealth: %d\n", localPlayer->C_BaseEntity__GetHealth(), localPlayer->C_BaseEntity__GetActualHealth());

    cvar->ConsoleDPrintf( "MaxClients: %d, Current map: %s (%s)\n", globalVars->maxClients, globalVars->currentMap, globalVars->currentMapName);

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

        /* Reset Fog */
        NoFog::ToggleFoW( true );
        NoFog::ToggleFog( true );
    }


    if( panoramaEngine ){
        /* Cleanup panels */
        if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer( UI::mcDota ) ){
            UI::mcDota->RemoveAndDeleteChildren();
            panorama::IUIPanel *root = UI::mcDota->GetParent();
            if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer( root ) ){
                root->RemoveChild( UI::mcDota );
            } else {
                cvar->ConsoleDPrintf("ERROR unloading, root panel is invalid! (%p)\n", root );
            }
        }
    }


    if( cvar ){
        /* Cleanup ConVars we have made */
        for( ConCommandBase* var : Util::createdConvars ){
            cvar->UnregisterConCommand(var);
            if( var->name ){
                delete[] var->name;
            }
            if( var->strValue ){
                delete[] var->strValue;
            }
            if( var->strDefault ){
                delete[] var->strDefault;
            }
            if( var->description ){
                delete[] var->description;
            }
            delete var;
        }
        cvar->FindVar("cl_mouseenable")->SetValue(1);
        cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), "[McDota] I'm outta here.\n");
    } else {
        ConMsg( "[McDota] I'm outta here.\n" );
    }

    /* Restore previous signal handler */
    /* SIGXCPU actually just normally kills the game lol */
    sigaction(SIGXCPU, &oldSa, NULL );
}
