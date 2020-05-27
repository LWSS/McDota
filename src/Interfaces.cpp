#include "Interfaces.h"

#include "Utils/Patternfinder.h" //dlinfo_t
#include "Utils/Logger.h"
#include "Hooks/Hooks.h"

#include <link.h> // dl_iterate_phdr

bool Interfaces::FindExportedInterfaces( )
{
    client = GetInterface<CSource2Client>("../../dota/bin/linuxsteamrt64/libclient.so", "Source2Client002", 131 );
    cvar = GetInterface<ICvar>( "./libvstdlib.so", "VEngineCvar007", 53 );
    engine = GetInterface<IEngineClient>( "./libengine2.so", "Source2EngineToClient001", 168 );
    inputSystem = GetInterface<IInputSystem>( "./libinputsystem.so", "InputSystemVersion001", 89 );
    inputInternal = GetInterface<IInputInternal>("./libvgui2.so", "VGUI_InputInternal001", 101 );
    networkClientService = GetInterface<INetworkClientService>("./libengine2.so", "NetworkClientService_001", 68 );
    panel = GetInterface<IVPanel>("./libvgui2.so", "VGUI_Panel010", 82 );
    splitScreenService = GetInterface<CSplitScreenService>("./libengine2.so", "SplitScreenService_001", 47 );
    panoramaEngine = GetInterface<IPanoramaUIEngine>("./libpanorama.so", "PanoramaUIEngine001", 17 );
    fontManager = GetInterface<CFontManager>("./libmaterialsystem2.so", "FontManager_001", 45 );
    engineServiceMgr = GetInterface<CEngineServiceMgr>("./libengine2.so", "EngineServiceMgr001", 51 );
    particleSystemMgr = GetInterface<CParticleSystemMgr>("./libparticles.so", "ParticleSystemMgr003", 48 );
    networkMessages = GetInterface<CNetworkMessages>("./libnetworksystem.so", "NetworkMessagesVersion001", 35 );
    gameEventSystem = GetInterface<CGameEventSystem>("./libengine2.so", "GameEventSystemClientV001", 21 );
    networkStrings = GetInterface<CNetworkStringTableContainer>("./libengine2.so", "Source2EngineToClientStringTable001", 19);
    materialSystem = GetInterface<IMaterialSystem>("./libmaterialsystem2.so", "VMaterialSystem2_001", 37);
    networkSystem = GetInterface<CNetworkSystem>("./libnetworksystem.so", "NetworkSystemVersion001", 74);
    fileSystem = GetInterface<CBaseFileSystem>( "./libfilesystem_stdio.so", "VFileSystem017", 178);
    fs = fileSystem;

    if( !requestedInterfaces.empty() ){
        for(auto & requestedInterface : requestedInterfaces){
            if( !requestedInterface.interface ){
                ConMsg( "Interface: (%s) is Null!\n", requestedInterface.name );
            }
        }
        return false;
    }
    return true;
}

void Interfaces::DumpInterfaces( const char *fileName )
{
	static std::vector<dlinfo_t> modules;
    FileHandle_t dumpFile = fileSystem->Open( "dotainterfaces.txt", "w", "TMPDIR" );

    if( !dumpFile ){
        MC_PRINTF_ERROR("Couldn't create dumpfile for interfaces!\n");
        return;
    }

	dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
		dlinfo_t library_info = {};

		library_info.library = info->dlpi_name;
		library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
		library_info.size = info->dlpi_phdr[0].p_memsz;

		modules.push_back(library_info);

		return 0;
	}, nullptr);

    fileSystem->FPrintf( dumpFile, "\n\n***************** Start of Log *****************\n");

    for ( const dlinfo_t& module: modules )
    {
        if( !module.library )
            continue;
        if( !strcasestr( module.library, "dota" ) ) // want dota to be in filepath
            continue;
        if( strcasestr( module.library, "libsteam_api.so" ) )
            continue;
        if( strcasestr( module.library, "libvideo.so" ) )
            continue;

        fileSystem->FPrintf( dumpFile, "-- Module Name: %s --\n", module.library);

        void *library = dlopen(module.library, RTLD_NOLOAD | RTLD_NOW);
        if ( library == nullptr ){
            fileSystem->FPrintf( dumpFile, "**Couldn't open library**\n");
            continue;
        }

        void *createInterfaceSym = dlsym(library, "CreateInterface");
        if ( createInterfaceSym == nullptr ) {
            fileSystem->FPrintf( dumpFile,  "**Couldn't find CreateInterface**\n" );
            dlclose(library);
            continue;
        }

        uintptr_t jump_instruction_addr = uintptr_t(createInterfaceSym) + 5;
        int32_t jump_displacement = *reinterpret_cast<int32_t*>(jump_instruction_addr + 1);
        uintptr_t createinterfaceinternal_addr = (jump_instruction_addr + 5) + jump_displacement;

        uintptr_t interface_list = createinterfaceinternal_addr;
        interface_list += *reinterpret_cast<int32_t*>(createinterfaceinternal_addr + 19); // relative offset to list
        interface_list += 23; // RIP after the address.

        dlclose(library);
        if( !interface_list )
        {
            fileSystem->FPrintf( dumpFile,  "ERROR: Couldn't find Interface List in Module: %s\n", module.library);
            continue;
        }

        InterfaceReg* interface_head = *reinterpret_cast<InterfaceReg**>(interface_list);

        std::vector<const char*> interface_name;

        for (InterfaceReg *cur_interface = interface_head; cur_interface; cur_interface = cur_interface->m_pNext)
            interface_name.push_back(cur_interface->m_pName);

        if ( interface_name.empty() ){
            fileSystem->FPrintf( dumpFile,  "Interface List is Empty!\n");
            continue;
        }


        for (auto interface : interface_name)
            fileSystem->FPrintf( dumpFile, "\t%s\n", interface);

        fileSystem->FPrintf( dumpFile,  "\n");
    }

    fs->FPrintf(dumpFile, "\n\n***************** End of Log *****************\n");

    fileSystem->Close( dumpFile );
}

// Hook VMTs for interfaces that are not static (in-game entities, etc.)
void Interfaces::HookDynamicVMTs( ) {
    camera = GetCurrentCamera();

    if( camera ){
        cameraVMT.reset();
        MC_PRINTF("Grabbing new Camera VMT - (%p)\n", (void*)camera);
        cameraVMT = std::unique_ptr<VMT>(new VMT( camera ));
        cameraVMT->HookVM( Hooks::GetFogEnd, 19 );
        cameraVMT->HookVM( Hooks::GetZFar, 20 );
        cameraVMT->HookVM( Hooks::GetFoWAmount, 26 );
        cameraVMT->ApplyVMT();
    } else {
        MC_PRINTF_WARN("GetCurrentCamera() returned null! Aborting CameraVMT.\n");
    }
}