#include "Hooks.h"

#include "../Settings.h"
#include "../GUI/Gui.h"
#include "../protos/mcdota.pb.h"

#include <csignal>

typedef void (* SetKeyCodeStateFn)( IInputInternal*, ButtonCode_t, bool );
typedef bool (* SendNetMessageFn)( INetChannel *thisptr, NetMessageHandle_t *, google::protobuf::Message*, NetChannelBufType_t );

bool EntHitHandler( void *IHandleEntity, int unk )
{
    Util::Log("Ent hit handler REEEE ent(%p) - int(%d)\n", IHandleEntity, unk);
    std::raise(SIGINT);
    return true;
}

bool ShouldDrawParticleSystems( void )
{
    Util::Log("Should draw particle callback\n");
    return false;
}


void Hooks::SetKeyCodeState(IInputInternal* thisptr, ButtonCode_t code, bool pressed)
{
    Vector attachment;
    CBaseEntity* entity;
    CDOTAWearableItem* cosmetic;
    INetworkStringTable *stringTable;
    CDOTAClientMsg_TipAlert tip;
    CNETMsg_SetConVar convar;
    CMsg_CVars_CVar* newConVar;// = convar.mutable_convars()->add_cvars();
    CNETMsg_StringCmd stringCmd;
    CDOTAClientMsg_GuideSelectOption option;
    CDOTAClientMsg_GuideSelected guide;
    std::string meme;

    RnQueryTerrain traceFilter;
    CGameTrace traceOut;
    Ray_t ray;
    Vector temp;

    VMT *entityVMT;

    if( !pressed )
        return inputInternalVMT->GetOriginalMethod<SetKeyCodeStateFn>(96)(thisptr, code, pressed);

    switch( code ){
        case ButtonCode_t::INSERT:
            UI::ToggleUI();
            break;
        case ButtonCode_t::HOME:
            cvar->ConsoleDPrintf("TickCount: %d\n", globalVars->tickcount);
            for( int i = 0; i <= entitySystem->GetHighestEntityIndex(); i++ ){
                entity = entitySystem->GetBaseEntity(i);
                if( entity ){
                    cvar->ConsoleDPrintf("Entity#%d(%p) - Name:(%s)", i, (void*)entity, entity->Schema_DynamicBinding()->bindingName );
                    if( entity->GetOwnerID() >= 0 ){
                        cvar->ConsoleDPrintf(" - Owner:(%d)", entity->GetOwnerID());
                    }
                    cvar->ConsoleDPrintf("\n");
                }
            }
            break;
        case ButtonCode_t::PGUP:
            //vscriptSystem->RunScript("bazinga", false);
            //MC_PRINTF("Local Player ID(%d)\n", *(networkClientService->GetIGameClient()->GetLocalDOTAPlayerID()));
            //newConVar->set_name(mc_custom_str->strValue);
            //newConVar->set_value(mc_custom_str_alt->strValue);
            MC_PRINTF("custom stringcmd\n");
            stringCmd.set_command(mc_custom_str->strValue);
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ) {
                Hooks::SendNetMessage( engine->GetNetChannelInfo( ), networkMessages->GetMessageHandleByName( "CNETMsg_StringCmd" ), &stringCmd, BUF_DEFAULT );
            }
            break;
        case ButtonCode_t::PGDN:
            guide.set_guide_workshop_id( 0 );
            guide.set_is_plus_guide( true );
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ) {
                Hooks::SendNetMessage( engine->GetNetChannelInfo( ), networkMessages->GetMessageHandleByName( "CDOTAClientMsg_GuideSelected" ), &guide, BUF_DEFAULT );
            }
            break;
        case ButtonCode_t::END:
            break;
        case ButtonCode_t::DELETE:
            //networkClientService->GetIGameClient()->ForceFullUpdate("unnamed");
            MC_PRINTF("sending meme\n");
            option.set_option( mc_custom_int->GetInt() );
            option.set_force_recalculate( true );
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ) {
                Hooks::SendNetMessage( engine->GetNetChannelInfo( ), networkMessages->GetMessageHandleByName( "CDOTAClientMsg_GuideSelectOption" ), &option, BUF_DEFAULT );
            }
            break;
        case ButtonCode_t::SCROLLLOCK:
            //richPresence->SetStatus(mc_custom_str->strValue);
            MC_PRINTF("Doing cosmetic particle disable sweep.\n");
            for( int i = 0; i <= entitySystem->GetHighestEntityIndex(); i++ ){
                entity = entitySystem->GetBaseEntity(i);
                if( entity && !strcmp( entity->Schema_DynamicBinding()->bindingName, "C_DOTAWearableItem" ) ){
                    MC_PRINTF("Purging ent %d\n", i);
                    entityVMT = new VMT(entity);
                    entityVMT->HookVM( ShouldDrawParticleSystems, 297 );
                    entityVMT->ApplyVMT();
                }
            }
            break;
        case ButtonCode_t::PAUSE:
            Util::SpewScriptScopes( GetPanoramaScriptScopes(), true );
            break;
        case ButtonCode_t::PRINTSCREEN:
            Util::Log("Tracing a ray good luck!\n");
            //CTraceFilter_Constructor( &traceFilter, nullptr, 0x69696969, EntHitHandler );
            ray.Init( Vector(100.0f, 200.0f, 300.0f), Vector(100.0f, 200.0f, -1200.0f) );
            traceFilter.Init( 0, 0xFFFFFFFF, EntHitHandler );

            GameTrace_Init( &traceOut );
            client->TraceRay( ray, traceFilter, &traceOut );

            Util::Log("Traceout(%p) - filter(%p) - fraction(%f)\n", &traceOut, &traceFilter, traceOut.fraction);
            std::raise(SIGINT);
            /*
             * CVoiceGamerMgrHelper::CanPlayerHearPlayer()
             - calls CEngineServer::GetClientConvarValue(index, "dota_mute_cobroastcasters") every tick i think
             */
            //MC_PRINTF("null convar/value\n");
            //newConVar = convar.mutable_convars()->add_cvars();
            //newConVar->set_name("\0");
            //newConVar->set_value("\0");

            //Hooks::SendNetMessage( engine->GetNetChannelInfo(), networkMessages->GetMessageHandleByName("CNETMsg_SetConVar"), &convar, BUF_DEFAULT );
            break;
        default:
            return inputInternalVMT->GetOriginalMethod<SetKeyCodeStateFn>(96)(thisptr, code, pressed);
    }
}