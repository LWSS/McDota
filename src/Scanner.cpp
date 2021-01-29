#include "Scanner.h"

#include "Interfaces.h"
#include "Utils/Patternfinder.h"

static bool FindGlobalVars() {

	// CSource2Client::SetGlobals()
	// 55                      push    rbp
    // 48 85 F6                test    rsi, rsi
    // 48 89 E5                mov     rbp, rsp
    // 48 89 35 D2 8C A0 02    mov     cs:_gpGlobals, rsi

    void ( CSource2Client::*setGlobalsPtr )( void* ) = &CSource2Client::SetGlobals;

    uintptr_t SetGlobals = reinterpret_cast<uintptr_t>( (void*)(client->*setGlobalsPtr) );

    MC_PRINTF("setglobalsPtr (%p)\n", (void*)(client->*setGlobalsPtr) );

	globalVars = *reinterpret_cast<CGlobalVars**>(GetAbsoluteAddress(SetGlobals + 7, 3, 7));
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

    uintptr_t getHighestEntIndexFnAddr = GetAbsoluteAddress( reinitPredictables + 33, 1, 5 );

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
	// Xref "SetCameraYaw" - right above it will be CDOTA_PanoramaScript_GameUI::SetCameraYaw()
	// In here, the first function is GDOTADefaultCamera() which we will sig.

	uintptr_t getCameraFuncAddr = PatternFinder::FindPatternInModule("libclient.so", "55 BF FF FF FF FF 48 89 E5 E8 ?? FF FF FF 48 85 C0 74", "GDOTADefaultCamera()");

	if( !getCameraFuncAddr ){
		MC_PRINTF_ERROR("Get Camera sig failed\n");
		return false;
	}

	GetCurrentCamera = reinterpret_cast<GetCameraFn>( getCameraFuncAddr );

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
	// 48 89 1D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 89 C7
	// xref  "file://{resources}/layout/play.xml". DBPlay panel is a few lines above it.
	// 48 89 1D 73 45 C3 01    mov     cs:DBPlayPanel, rbx   <-------------------------
	// E8 B6 CA AD FE          call    __Znwm          ; operator new(ulong)
	// 48 89 C7                mov     rdi, rax
	// 49 89 C4                mov     r12, rax
	// E8 BB D6 82 FF          call    loc_2C50EA0
	// 48 8B 05 2C 0E 92 01    mov     rax, cs:off_4D44618

	uintptr_t playPanelLine = PatternFinder::FindPatternInModule("libclient.so", "48 89 1D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 89 C7", "DBPlay Panel");

	if( !playPanelLine ){
		MC_PRINTF_ERROR("DBPlayPanel Sig is broke!\n");
		return false;
	}

	auto playPanelAddr = reinterpret_cast<uintptr_t>( GetAbsoluteAddress( playPanelLine, 3, 7 ) );

	if( !playPanelAddr ){
		MC_PRINTF_ERROR("DBPlayPanelAddr is NULL\n");
		return false;
	}

	gDBPlayPanel = *reinterpret_cast<panorama::CPanel2D**>( playPanelAddr );

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
	auto GetRichPresence = reinterpret_cast<GetRichPresenceFn>( GetAbsoluteAddress(NotifyClientSignon + 38, 1, 5) );

	richPresence = GetRichPresence();


	// xref "active RP" to SetRPStatus()
	uintptr_t funcAddr = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 41 56 41 89 D6 41 55 49 89 FD 41 54 53 48 81 EC", "SetRPStatus" );

	if( !funcAddr ){
		MC_PRINTF_ERROR("SetRPStatus sig is broke!\n");
		return false;
	}

	SetRPStatus = reinterpret_cast<SetRPStatusFn>( funcAddr );
	return true;
}

static bool FindGCFunctions()
{
	// GCSDK::CGCClient::DispatchPacket(GCSDK::IMsgNetPacket *)
	// xref for "You have been waiting for"
	DispatchPacketFnAddr = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 41 56 41 55 41 54 49 89 FC 53 48 89 F3 48 83 EC ?? 48 8B 3D", "DispatchPacket()" );

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

	// SendMessageGenericClientToGC(const google::protobuf::Message *const msg, uint32 nMsgID)
	// xref for "DOTAPartySearch--Searching", there is 2, look for one that is Not at the end of a function.
	// Follow the green arrow to the next block....

	// E8 3B 39 19 00          call    sub_37F9EC0
	// 48 89 C7                mov     rdi, rax
	// E8 03 D7 1B 00          call    SendMessageGenericClientToGC_Wrapper <---- go into this function.
	// 5B                      pop     rbx

	// the last block in that function contains the target. (2nd to last function call)
	// 83 4D E0 01             or      [rbp+var_20], 1
	// 48 89 45 D0             mov     [rbp+var_30], rax
	// C7 45 E8 00 00 00 00    mov     [rbp+var_18], 0
	// E8 79 0E 64 00          call    SendMessageGenericClientToGC <-----
	// 48 8D 05 D2 72 7F 01    lea     rax, off_501AFD0
	// 48 89 DF                mov     rdi, rbx

	uintptr_t line = PatternFinder::FindPatternInModule( "libclient.so", "C7 45 ?? 00 00 00 00 E8 ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 48 89 DF", "SendMessageGenericClientToGC()" );
	if( !line ){
		MC_PRINTF_ERROR("SendMessageGenericClientToGC sig is broke!\n");
		return false;
	}

    line = GetAbsoluteAddress( line + 7, 1, 5 );
	SendMessageGenericClientToGC = reinterpret_cast<SendMessageGenericClientToGCFn>( line );

    // Grab Game coordinator client in here too.
    // 55                      push    rbp
    // 89 F2                   mov     edx, esi
    // 48 89 FE                mov     rsi, rdi
    // 48 8B 3D CB E6 59 01    mov     rdi, cs:s_pGCClient
    gcClient = *reinterpret_cast<CGCClient**>( GetAbsoluteAddress( line + 6, 3, 7 ) );
	return true;
}

static bool FindPhysicsQuery()
{
	// MaterialFootstepSound() - xref "LeftFoot" to find this function.
    // 48 8B 05 E7 CA 5D 02                mov     rax, cs:_g_pPhysicsQuery
    // 48 C7 85 48 FD FF FF 01 30 18 00    mov     [rbp+var_2B8], 183001h
    // 48 8B 38                            mov     rdi, [rax]
    // E8 EC 34 0B 00                      call    TraceRay

    // valid masks...
    // 0x83001
    // 0x183001
    // 0x181003
    // 0x3011
	uintptr_t physicsQueryLine = PatternFinder::FindPatternInModule( "libclient.so", "48 8B 05 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 48 8B 38 E8", "_g_pPhysicsQuery" );
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

static bool FindTraceFuncs()
{
    // Xref "Pass table - Inputs: start, end, min, max, mask, ignore  -- outputs: pos, fraction, hit, enthit, startsolid" to CVScriptGameSystem::InstallScriptBindings()
    // Script_Traceline will be loaded into rax shortly below.
    // look for CGameTrace::Init() at the start of a big chunk
    uintptr_t line = PatternFinder::FindPatternInModule( "libclient.so", "55 48 89 E5 41 57 41 56 41 55 41 54 53 48 89 FB 48 83 EC 18 4C 8B 25 ?? ?? ?? ?? 4D", "CGameTrace::Init()" );
    if( !line ){
        MC_PRINTF_ERROR("CGameTrace::Init() sig is broke!\n");
        return false;
    }
    GameTrace_Init = reinterpret_cast<CGameTraceInitFn>( line );

    // towards the end of that big chunk where u found Init(), look for another function. This function will have `mov dword ptr [rdi+28h], 7` in the first chunk.
    // This function is CTraceFilterSimple::CTraceFilterSimple(IHandleEntity const*, int, bool (*)(IHandleEntity*, int))
    line = PatternFinder::FindPatternInModule( "libclient.so", "55 48 8D 05 ?? ?? ?? ?? 48 89 E5 41 56 41 89 D6", "CTraceFilter::CTraceFilter()" );
    if( !line ){
        MC_PRINTF_ERROR("CTraceFilter::CTraceFilter sig is broke!\n");
        return false;
    }

    CTraceFilter_Constructor = reinterpret_cast<CTraceFilterConstructorFn>( line );
    return true;
}

static bool FindRenderDevice()
{
   // Xref "CreateDevice: Requested DX level %d" to CRenderDeviceMgrGL::CreateDevice()
   // look a couple blocks below the string...
   // E8 0D 42 FC FF          call    LoadVideoConfig
   // 44 89 F1                mov     ecx, r14d
   // 44 89 E2                mov     edx, r12d
   // 89 DE                   mov     esi, ebx
   // 48 8B 05 DE F1 30 00    mov     rax, cs:_g_pRenderDeviceGL <----------- This one (it also has more xref's than below)
   // 4C 8B 2D 7F ED 30 00    mov     r13, cs:_g_pRenderDeviceBase
   // 48 8B 38                mov     rdi, [rax]
   // 49 89 7D 00             mov     [r13+0], rdi
   // E8 9B CE FF FF          call    InitDevice

   if( Util::GetGraphicsApiType() != GFX_API::OPENGL ){
       MC_PRINTF_ERROR("Does anyone use the vulkan port?\nIf so, you'll have to add another sig here %s", __LINE__);
       return false;
   }

   uintptr_t line = PatternFinder::FindPatternInModule("librendersystemgl.so", "48 8B 05 ?? ?? ?? ?? 4C 8B 2D ?? ?? ?? ?? 48", "CRenderDeviceGL");
   if( !line ){
       MC_PRINTF_ERROR("FindRenderDevice sig is broke!\n");
       return false;
   }


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
	sigsOK &= FindAcceptMatch();
	//sigsOK &= FindRichPresence(); // removed for now, unused and silly - can do this easier
	sigsOK &= FindGCFunctions();
	sigsOK &= FindPhysicsQuery();
	sigsOK &= FindRenderGameSystem();
	sigsOK &= FindPanoramaScriptScopes();
    sigsOK &= FindTraceFuncs();

	return sigsOK;
}











