#include "Scanner.h"

#include "Interfaces.h"
#include "Utils/Patternfinder.h"

static bool FindGlobalVars() {

	// CSource2Client::SetGlobals()
	// 55                         push    rbp
	// 48 89 E5                   mov     rbp, rsp
	// 53                         push    rbx
	// 48 83 EC 08                sub     rsp, 8
	// 48 85 F6                   test    rsi, rsi
	// 48 8B 1D 1D 30 3A 03       mov     rbx, cs:_gpGlobals

    void ( CSource2Client::*setGlobalsPtr )( void* ) = &CSource2Client::SetGlobals;

    uintptr_t SetGlobals = reinterpret_cast<uintptr_t>( (void*)(client->*setGlobalsPtr) );

	globalVars = **reinterpret_cast<CGlobalVars***>(GetAbsoluteAddress(SetGlobals + 9, 3, 7));
	return true;
}

static bool FindGameEntitySystem()
{
    // CPrediction::ReinitPredictables()
    // Look for string "ReinitPredictables".
    // The start of this function contains both a pointer to CGameEntitySystem and a call to CGameEntitySystem::GetHighestEntityIndex();
	// 55                      push    rbp
	// 48 89 E5                mov     rbp, rsp
	// 41 56                   push    r14
	// 4C 8B 35 F3 A8 2A 02    mov     r14, cs:_g_pGameEntitySystem
	// 41 55                   push    r13
	// 49 89 FD                mov     r13, rdi
	// 41 54                   push    r12
	// 53                      push    rbx
	// 31 DB                   xor     ebx, ebx
	// C6 87 D0 00 00 00 01    mov     byte ptr [rdi+0D0h], 1
	// 49 8B 3E                mov     rdi, [r14]
	// E8 EA 4B E2 FF          call    CGameEntitySystem__GetHighestEntityIndex

    uintptr_t reinitPredictables = PatternFinder::FindPatternInModule("libclient.so", "55 48 89 E5 41 56 4C 8B 35 ?? ?? ?? ?? 41 55 49 89 FD 41 54 53 31", "reinitPredictables");

	if( !reinitPredictables ){
        MC_PRINTF_ERROR("reinitPredictables sig failed\n");
        return false;
    }

    uintptr_t jumpInstructionAddr = reinitPredictables + 33;
    int32_t jumpDisplacement = *reinterpret_cast<int32_t*>(jumpInstructionAddr + 1);
    uintptr_t getHighestEntIndexFnAddr = (jumpInstructionAddr + 5) + jumpDisplacement;

    // CGameEntitySystem::GetHighestEntityIndex()
    // We get the class offset for the highest Ent Index
    // 55                      push    rbp
    // 8B 87 60 A0 01 00       mov     eax, dword ptr ds:stru_1A060.r_offset[rdi]
    // 48 89 E5                mov     rbp, rsp
    // 5D                      pop     rbp

    highestEntIndexOffset = *reinterpret_cast<uint32_t*>(getHighestEntIndexFnAddr + 3);
    entitySystem = **reinterpret_cast<CGameEntitySystem***>( GetAbsoluteAddress(reinitPredictables + 6, 3, 7) );

	return true;
}


static bool FindVScript()
{
	// Shortly after "__ReplaceClosures"
	// 0F 84 F5 00 00 00                       jz      loc_2A31390
	// 48 8B 3D 16 38 A3 03                    mov     rdi, cs:qword_6464AB8
	// 0F B6 D3                                movzx   edx, bl
	// 4C 89 E6                                mov     rsi, r12

	uintptr_t initialLine = PatternFinder::FindPatternInModule("libclient.so", "48 8B 3D ?? ?? ?? ?? 0F B6 D3", "FindVScript");

	if( !initialLine ){
        MC_PRINTF_ERROR("ERROR VScript sig failed\n");
        return false;
    }

    // The compiler did some weird shit here to morph 2 vtables into one.
    // Just need to decrease thisptr by 0x10 to get to bigger vtable. (IGameSystem + CVScriptGameSystem) instead of just (CVScriptGameSystem).
	void* scriptSys = *reinterpret_cast<CVScriptGameSystem**>( GetAbsoluteAddress(initialLine, 3, 7) );
    scriptSys = reinterpret_cast<char*>(scriptSys) - 0x10;
    vscriptSystem = (CVScriptGameSystem*)scriptSys;

	return true;
}

static bool FindPanelArrayOffset()
{
	unsigned int knownGoodOffset = 0x1b8;
	//  CUIEngine::IsValidPanelPointer()
	//
	//   55                      push    rbp
	//   48 81 C7 B8 01 00 00    add     rdi, 1B8h <--------

    bool ( panorama::UIEngine::*isValidPanelPtrPtr )( const panorama::IUIPanel* ) = &panorama::UIEngine::IsValidPanelPointer;

    uintptr_t IsValidPanelPointer = reinterpret_cast<uintptr_t>( (void*)(panoramaEngine->AccessUIEngine()->*isValidPanelPtrPtr) );
	panorama::panelArrayOffset = *(unsigned int*)(IsValidPanelPointer + 19);

	if( panorama::panelArrayOffset != knownGoodOffset ) {
		MC_PRINTF_WARN( "Array Offset Changed. Is (%x), supposed to be (%x)\n", panorama::panelArrayOffset, knownGoodOffset );
	}
	if( panorama::panelArrayOffset > 0x300 || panorama::panelArrayOffset < 0x100 ){
		MC_PRINTF_ERROR("Array Offset Drastic Change. Is (%x)!\n", panorama::panelArrayOffset );
		return false;
	}
	return true;
}

static bool FindViewRender()
{
    //  InitGameSystems()
    // 55                      push    rbp
    // 48 89 E5                mov     rbp, rsp
    // 41 54                   push    r12
    // 53                      push    rbx
    // 48 83 EC 20             sub     rsp, 20h
    // E8 30 2C 71 00          call    GetViewRenderInstance <-------------
	uintptr_t initGameSystemsFunc = PatternFinder::FindPatternInModule("libclient.so", "55 48 89 E5 41 54 53 48 83 EC ?? E8 ?? ?? ?? ?? 48 8B 15", "GetViewRender Function");

    if( !initGameSystemsFunc ){
        MC_PRINTF_ERROR("initGameSystemsFunc sig failed\n");
        return false;
    }
	typedef CViewRender* (* GetViewRenderFn)();
    auto GetViewRender = reinterpret_cast<GetViewRenderFn>(GetAbsoluteAddress(initGameSystemsFunc + 11, 1, 5));
    viewRender = GetViewRender();
    return true;
}

static bool FindClientMode()
{
	// CSource2Client::HudUpdate()
	// 55                      push    rbp
	// 48 89 E5                mov     rbp, rsp
	// 53                      push    rbx
	// 89 F3                   mov     ebx, esi
	// 48 83 EC 18             sub     rsp, 18h
	// E8 30 E5 6E 01          call    sub_44B48D0
	// E8 8B 2C ED FF          call    sub_2C99030
	// 84 C0                   test    al, al
	// 75 37                   jnz     short loc_2DC63E0
	// 31 FF                   xor     edi, edi
	// E8 E0 53 20 00          call    GetClientMode <----------------

    void ( CSource2Client::*hudUpdatePtr )( bool ) = &CSource2Client::HudUpdate;

	uintptr_t hudUpdateFn = reinterpret_cast<uintptr_t>( (void*)(client->*hudUpdatePtr) );

	if( !hudUpdateFn ){
		MC_PRINTF_ERROR("hudUpdateFn is NULL\n");
		return false;
	}
	typedef IClientMode* (*GetClientModeFn) ( int splitScreenslot );
	auto GetClientMode = reinterpret_cast<GetClientModeFn>( GetAbsoluteAddress( hudUpdateFn + 27, 1, 5 ) );

	if( !GetClientMode ){
		MC_PRINTF_ERROR("GetClientMode function is NULL\n");
		return false;
	}

	clientMode = GetClientMode( 0 );
	if( !clientMode ){
		MC_PRINTF_ERROR("GetClientMode function failed to return ClientMode\n");
		return false;
	}

	return true;
}

static bool FindCamera()
{
	// CenterOnLocalPlayersHero(), xref "CMD_SelectHeroStart" and look around there
	// E8 E5 84 09 00          call    GDOTADefaultCamera
	// F3 0F 10 4D EC          movss   xmm1, [rbp+var_14]
	// 31 C9                   xor     ecx, ecx
	// 31 D2                   xor     edx, edx
	

	uintptr_t getCameraFuncAddr = PatternFinder::FindPatternInModule("libclient.so", "E8 ?? ?? ?? ?? F3 0F 10 ?? ?? 31 C9 31 D2", "Get DOTADefaultCamera");

	if( !getCameraFuncAddr ){
		MC_PRINTF_ERROR("Get Camera sig failed\n");
		return false;
	}

	GetCurrentCamera = reinterpret_cast<GetCameraFn>( GetAbsoluteAddress(getCameraFuncAddr, 1, 5) );

	camera = GetCurrentCamera();
	return true;
}


static bool FindGameEventManager()
{
	// 4C 8D 3D AC 86 3C 02    lea     r15, _gameeventmanager
    void ( CSource2Client::*playerInfoChangedPtr )( int ) = &CSource2Client::PlayerInfoChanged;

    uintptr_t playerInfoChangedFn = reinterpret_cast<uintptr_t>( (void*)(client->*playerInfoChangedPtr) );


    auto gameEventManagerAddr = reinterpret_cast<uintptr_t>( GetAbsoluteAddress(playerInfoChangedFn + 52, 3, 7) );
    if( !gameEventManagerAddr ){
        MC_PRINTF_ERROR("Game Event Manager Addr sig broke!\n");
        return false;
    }

    gameEventManager = **reinterpret_cast<CGameEventManager ***>( gameEventManagerAddr );

    if( !gameEventManager ){
        MC_PRINTF_ERROR("Game Event Manager is NULL\n");
        return false;
    }
    return true;
}

static bool FindDBPlayPanel()
{
	// 48 8B 05 ?? ?? ?? ?? BE 07 00 00 00
	// Right below "disconnect clicked disconnect button"
	// 48 8B 05 E7 99 0A 03    mov     rax, cs:_g_pDBPlayPanel
	// BE 07 00 00 00          mov     esi, 7
	
	uintptr_t playPanelLine = PatternFinder::FindPatternInModule("libclient.so", "48 8B 05 ?? ?? ?? ?? BE 07 00 00 00", "DBPlay Panel");

	if( !playPanelLine ){
		MC_PRINTF_ERROR("DBPlayPanel Sig is broke!\n");
		return false;
	}

	auto playPanelAddr = reinterpret_cast<uintptr_t>( GetAbsoluteAddress( playPanelLine, 3, 7 ) );

	if( !playPanelAddr ){
		MC_PRINTF_ERROR("DBPlayPanelAddr is NULL\n");
		return false;
	}

	gDBPlayPanel = **reinterpret_cast<panorama::CPanel2D***>( playPanelAddr );

	return true;
}

static bool FindSoundOpSystem()
{
    // xref "DOTAMusic.MainLoop" to first function ( it should also have "opvars" and "dota_music_opvars", but NOT "current_music") go to start of function; it is the first cs:xxxxxxxx address
    // 48 8B 1D 53 97 20 03          mov     rbx, cs:off_61D92E0
	// C6 85 90 FE FF FF FF          mov     [rbp+var_170], 0FFh
	// 64 48 8B 04 25 28 00 00 00    mov     rax, fs:28h
	// 48 89 45 E8                   mov     [rbp+var_18], rax
	// 31 C0                         xor     eax, eax
	// C7 85 98 FE FF FF 00 00 00 00 mov     [rbp+var_168], 0
    
    uintptr_t soundOpSystemLine = PatternFinder::FindPatternInModule("libclient.so", "48 8B 1D ?? ?? ?? ?? C6 85 ?? ?? ?? ?? ?? 64 48 8B 04 25 ?? ?? ?? ?? 48 89 ?? ?? 31 C0 C7", "SoundOpSystem");

    if( !soundOpSystemLine ){
        MC_PRINTF_ERROR("SoundOpSystem Sig is broke!\n");
        return false;
    }

    auto soundOpSystemAddr = reinterpret_cast<uintptr_t>( GetAbsoluteAddress( soundOpSystemLine, 3, 7 ) );

    if( !soundOpSystemAddr ){
        MC_PRINTF_ERROR("SoundOpSystemAddr is NULL!\n");
        return false;
    }

    soundOpSystem = **reinterpret_cast<CSoundOpSystem***>( soundOpSystemAddr );

    return true;
}


static bool FindAcceptMatch()
{
	// xref "ui.click_back"
	// CDOTA_DB_Play__OnAcceptMatch proc near
	// 55                      push    rbp
	// 48 89 E5                mov     rbp, rsp
	// 53                      push    rbx
	// 89 F3                   mov     ebx, esi
	// 48 83 EC 08             sub     rsp, 8
	// E8 00 83 9F FF          call    GDOTAGCClientSystem
	// 0F B6 F3                movzx   esi, bl
	// 48 89 C7                mov     rdi, rax

	uintptr_t funcAddr = PatternFinder::FindPatternInModule("libclient.so", "55 48 89 E5 53 89 F3 48 83 EC ?? E8 ?? ?? ?? ?? 0F B6 F3 48 89", "On Accept Match");
	if( !funcAddr ){
		MC_PRINTF_ERROR("On Accept Match Sig is broke!\n");
		return false;
	}
	OnAcceptMatch = reinterpret_cast<OnAcceptMatchFn>( funcAddr );
	return true;
}

static bool FindRichPresence()
{
	// CSource2Client::NotifyClientSignon()
	// 55                      push    rbp
	// 48 89 E5                mov     rbp, rsp
	// 41 54                   push    r12
	// 44 0F B7 E6             movzx   r12d, si
	// 53                      push    rbx
	// 89 F3                   mov     ebx, esi
	// 48 83 EC 10             sub     rsp, 10h
	// E8 8A 85 73 00          call    GDOTAGCClientSystem
	// 44 89 E6                mov     esi, r12d
	// 48 89 C7                mov     rdi, rax
	// E8 0F 20 74 00          call    GDOTAGCClientSystem__NotifyClientSignon(int)
	// E8 7A 85 73 00          call    GDOTAGCClientSystem
	// 89 DA                   mov     edx, ebx
	// C1 EA 10                shr     edx, 10h
	// 83 E2 01                and     edx, 1
	// 88 90 FC 05 00 00       mov     [rax+5FCh], dl
	// E8 17 56 46 00          call    RichPresence   <----------------

	void ( CSource2Client::*notifyClientSignonPtr )( int ) = &CSource2Client::NotifyClientSignon;
	uintptr_t NotifyClientSignon = reinterpret_cast<uintptr_t>( (void*)(client->*notifyClientSignonPtr) );

	typedef CDOTARichPresence* ( *GetRichPresenceFn )();
	auto GetRichPresence = reinterpret_cast<GetRichPresenceFn>( GetAbsoluteAddress(NotifyClientSignon + 52, 1, 5) );

	richPresence = GetRichPresence();


	// xref "active RP" to SetRPStatus()
	uintptr_t funcAddr = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 41 56 41 89 D6 41 55 41 54 49 89 FC 53 48 81", "SetRPStatus" );

	if( !funcAddr ){
		MC_PRINTF_ERROR("SetRPStatus sig is broke!\n");
		return false;
	}

	SetRPStatus = reinterpret_cast<SetRPStatusFn>( funcAddr );
	return true;
}

static bool FindHardHooks()
{
	// GCSDK::CGCClient::DispatchPacket(GCSDK::IMsgNetPacket *)
	// xref for "You have been waiting for"
	DispatchPacketFnAddr = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 49 89 FF 41 56 41 55 41 54 4C 8D 25 ?? ?? ?? ?? 53 48 89 F3 48", "DispatchPacket()" );

	if( !DispatchPacketFnAddr ){
		MC_PRINTF_ERROR("DispatchPacketFn sig is broke!\n");
		return false;
	}

    // GCSDK::CProtoBufMsgBase::BAsyncSendProto(GCSDK::CProtoBufMsgBase::IProtoBufSendHandler &, unsigned int, CMsgProtoBufHeader const&, google::protobuf::Message const&)
    // xref "CProtoBufMsg::BAsyncSendProto"
    BAsyncSendProtoFnAddr = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 41 56 49 89 D6 41 55 41 54 49 89 CC 53 48 83", "BAsyncSendProto()" );
    if( !BAsyncSendProtoFnAddr ){
        MC_PRINTF_ERROR("BAsyncSendProtoFn sig is broke!\n");
        return false;
    }

	return true;
}

static bool FindPhysicsQuery()
{
	// ent_grab(CCommandContext const&, CCommand const&)
	// xref for "ent_grab", there are several that lead back
	// Interface is in a big chunk a couple blocks up from the strings.
	// E8 4C F0 0D 00                      call    sub_2791000
	// 48 89 D9                            mov     rcx, rbx
	// 4C 89 E2                            mov     rdx, r12
	// 4C 89 FE                            mov     rsi, r15
	// 48 8B 05 9C 96 62 02                mov     rax, cs:_g_pPhysicsQuery
	// 48 C7 85 38 FE FF FF 01 30 08 00    mov     [rbp+var_1C8], 83001h
	// 48 8B 38                            mov     rdi, [rax]
	// E8 79 A4 12 00                      call    sub_27DC450
	// F3 0F 10 05 9D 45 67 01             movss   xmm0, cs:dword_3D2657C
	// 0F 2E 85 48 FF FF FF                ucomiss xmm0, [rbp+var_B8]
	// 77 0D                               ja      short loc_26B1FF5

	uintptr_t physicsQueryLine = PatternFinder::FindPatternInModule( "libclient.so", "48 8B 05 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? 08 00", "FindPhysicsQuery" );
	if( !physicsQueryLine ){
		MC_PRINTF_ERROR("FindPhysicsQuery sig is broke!\n");
		return false;
	}

	// Update: physicsQuery seems to just be CVPhys2World now.
	phys2World = ***reinterpret_cast<CVPhys2World****>( GetAbsoluteAddress( physicsQueryLine, 3, 7 ) );

	return true;
}

static bool FindRenderGameSystem()
{
	// CViewRender::OnRenderStart() - lots of goodies in this function.
	// 48 8B 05 3C F3 32 02    mov     rax, cs:_g_pRenderGameSystem
	// 4C 8D 63 10             lea     r12, [rbx+10h]
	// C6 83 B0 10 00 00 01    mov     byte ptr [rbx+10B0h], 1
	// 48 8D 15 A2 98 4E 02    lea     rdx, g_WorldToView
	// 4C 89 E6                mov     rsi, r12
	// 4C 8D 0D 18 98 4E 02    lea     r9, g_WorldToScreen
	// 4C 8D 05 D1 97 4E 02    lea     r8, _g_WorldToProjection
	// 48 8B 38                mov     rdi, [rax]
	// 48 8D 0D 47 98 4E 02    lea     rcx, g_ViewToProjection
	// E8 02 B3 CC FF          call    CRenderGameSystem__GetMatricesForView
	uintptr_t line = PatternFinder::FindPatternInModule( "libclient.so", "48 8B 05 ?? ?? ?? ?? 4C 8D 63 10 C6", "FindRenderGameSystem" );
	if( !line ){
		MC_PRINTF_ERROR("FindRenderGameSystem sig is broke!\n");
		return false;
	}

	renderGameSystem = **reinterpret_cast<CRenderGameSystem***>( GetAbsoluteAddress( line, 3, 7 ) );
	line += 18; // go to worldToView line
	g_WorldToView = reinterpret_cast<VMatrix*>( GetAbsoluteAddress( line, 3, 7 ) );
	line += 10;
	g_WorldToScreen = reinterpret_cast<VMatrix*>( GetAbsoluteAddress( line, 3, 7 ) );
	line += 7;
	g_WorldToProjection = reinterpret_cast<VMatrix*>( GetAbsoluteAddress( line, 3, 7 ) );
	line += 10;
	g_ViewToProjection = reinterpret_cast<VMatrix*>( GetAbsoluteAddress( line, 3, 7 ) );
	line += 7;
	GetMatricesForView = reinterpret_cast<GetMatricesForViewFn>( GetAbsoluteAddress( line, 1, 5 ) );
	return true;
}

static bool FindPanoramaScriptScopes()
{
	// xref "Usage: cl_panorama_script_help" to callback for that concmd. First function that the callback calls is our target.
	// GetPanoramaScriptScopes
	uintptr_t line = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 41 56 41 55 41 54 53 48 83 EC ?? 80 3D ?? ?? ?? ?? 00 0F", "GetPanoramaScriptScopes" );
	if( !line ){
		MC_PRINTF_ERROR("FindPanoramaScriptScopes sig is broke!\n");
		return false;
	}

	GetPanoramaScriptScopes = reinterpret_cast<GetPanoramaScriptScopesFn>( line );
	return true;
}

bool Scanner::FindAllSigs( )
{
	bool sigsOK = true;

	sigsOK &= FindGlobalVars();
	sigsOK &= FindGameEntitySystem();
	sigsOK &= FindVScript();
	sigsOK &= FindPanelArrayOffset();
	sigsOK &= FindViewRender();
	sigsOK &= FindClientMode();
	sigsOK &= FindCamera();
	sigsOK &= FindGameEventManager();
	sigsOK &= FindDBPlayPanel();
	sigsOK &= FindSoundOpSystem();
	sigsOK &= FindAcceptMatch();
	sigsOK &= FindRichPresence();
	sigsOK &= FindHardHooks();
	sigsOK &= FindPhysicsQuery();
	sigsOK &= FindRenderGameSystem();
	sigsOK &= FindPanoramaScriptScopes();

	return sigsOK;
}











