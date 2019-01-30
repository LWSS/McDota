#include "interfaces.h"

#include <link.h> // dl_iterate_phdr

#include "Utils/patternfinder.h" //dlinfo_t
#include "Utils/util.h"

bool Interfaces::FindInterfaces()
{
    client = GetInterface<CSource2Client>("../../dota/bin/linuxsteamrt64/libclient.so", "Source2Client002", 134 );
    cvar = GetInterface<ICvar>( "./libvstdlib.so", "VEngineCvar007", 52 );
    engine = GetInterface<IEngineClient>( "./libengine2.so", "Source2EngineToClient001", 166 );
    inputSystem = GetInterface<IInputSystem>( "./libinputsystem.so", "InputSystemVersion001", 88 );
    inputInternal = GetInterface<IInputInternal>("./libvgui2.so", "VGUI_InputInternal001", 101 );
    networkClientService = GetInterface<INetworkClientService>("./libengine2.so", "NetworkClientService_001", 77 );
    panel = GetInterface<IVPanel>("./libvgui2.so", "VGUI_Panel010", 82 );
    splitScreenService = GetInterface<CSplitScreenService>("./libengine2.so", "SplitScreenService_001", 44 );
    panoramaEngine = GetInterface<IPanoramaUIEngine>("./libpanorama.so", "PanoramaUIEngine001", 17 );
    fontManager = GetInterface<CFontManager>("./libmaterialsystem2.so", "FontManager_001", 48 );
    engineServiceMgr = GetInterface<CEngineServiceMgr>("./libengine2.so", "EngineServiceMgr001", 53 );

    if( !requestedInterfaces.empty() ){
        for( long unsigned int i = 0; i < requestedInterfaces.size(); i ++ ){
            if( !requestedInterfaces[i].interface ){
                ConMsg( "Interface: (%s) is Null!\n", requestedInterfaces[i].name );
            }
        }
        return false;
    }
    return true;
}

void Interfaces::DumpInterfaces( const char *fileName )
{
	static std::vector<dlinfo_t> modules;

	dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
		dlinfo_t library_info = {};

		library_info.library = info->dlpi_name;
		library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
		library_info.size = info->dlpi_phdr[0].p_memsz;

		modules.push_back(library_info);

		return 0;
	}, nullptr);

	FILE *logFile;
	logFile = fopen(fileName, "a");
    setbuf( logFile, NULL ); // turn off buffered I/O so it writes even if a crash occurs soon after.
    fprintf(logFile, "\n\n***************** Start of Log *****************\n");
    for ( const dlinfo_t& module: modules )
    {
        if( !module.library )
            continue;
        if( strcasestr( module.library, "dota" ) == NULL ) // want dota to be in filepath
            continue;
        if( strcasestr( module.library, "libsteam_api.so" ) )
            continue;
        if( strcasestr( module.library, "libvideo.so" ) )
            continue;

        fprintf(logFile, "-- Module Name: %s --\n", module.library);

        void *library = dlopen(module.library, RTLD_NOLOAD | RTLD_NOW);
        if ( library == NULL ){
            fprintf(logFile, "**Couldn't open library**\n");
            continue;
        }

        void *createInterfaceSym = dlsym(library, "CreateInterface");
        if ( createInterfaceSym == NULL ) {
            fprintf( logFile, "**Couldn't find CreateInterface**\n" );
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
            fprintf(logFile, "ERROR: Couldn't find Interface List in Module: %s\n", module.library);
            continue;
        }

        InterfaceReg* interface_head = *reinterpret_cast<InterfaceReg**>(interface_list);

        std::vector<const char*> interface_name;

        for (InterfaceReg *cur_interface = interface_head; cur_interface; cur_interface = cur_interface->m_pNext)
            interface_name.push_back(cur_interface->m_pName);

        if ( interface_name.empty() ){
            fprintf(logFile, "Interface List is Empty!\n");
            continue;
        }


        for (auto interface : interface_name)
            fprintf(logFile, "\t%s\n", interface);

        fprintf(logFile, "\n");
    }
	fclose(logFile);
}

/* GetInterface() Adds to interfacesMetaDataList */
bool Interfaces::CheckInterfaceVMs( )
{
    bool areVMsGood = true;
    for( unsigned int i = 0; i < grabbedInterfaces.size(); i++ ){
        if( grabbedInterfaces[i].numVMs == 0 )
            continue;
        uint32_t vmCount = CountVMs(grabbedInterfaces[i].interface);

        if( grabbedInterfaces[i].numVMs != vmCount ){
            ConMsg("Warning: Interface \"%s\" Has Changed. Expected it to have %d VMs; has %d VMs. Check for Broken offsets and Update interfaces.cpp \n",
                   grabbedInterfaces[i].name,
                   grabbedInterfaces[i].numVMs,
                   vmCount);

            areVMsGood = false;
        }
    }
    return areVMsGood;
}