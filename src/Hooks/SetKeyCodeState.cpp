#include "Hooks.h"

#include "../Settings.h"
#include "../GUI/Gui.h"
#include "../protos/mcdota.pb.h"
#include "../Utils/Logger.h"

#include <csignal>

typedef void (* SetKeyCodeStateFn)( IInputInternal*, ButtonCode_t, bool );
typedef bool (* SendNetMessageFn)( INetChannel *thisptr, NetMessageHandle_t *, google::protobuf::Message*, NetChannelBufType_t );

bool EntHitHandler( void *IHandleEntity, int unk )
{
    MC_LOGF("Ent hit handler REEEE ent(%p) - int(%d)\n", IHandleEntity, unk);
    std::raise(SIGINT);
    return true;
}

bool ShouldDrawParticleSystems( void )
{
    MC_LOGF("Should draw particle callback\n");
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
    static CDOTAClientMsg_MatchMetadata metadataMsg;
    static bool cacheMetaData = false;
    static int cachedSize = -1;
    CDOTAMatchMetadata metadata;
    std::string meme;
    CDOTAPlayerResource *playerResource;
    CUtlVector< PlayerResourcePlayerTeamData_t > *teamData;

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
            MC_PRINTF("TickCount: %d\n", globalVars->tickcount);
            MC_PRINTF("Curtime: %f\n", globalVars->curtime);
            MC_PRINTF("Seconds since start: %f\n", (float(globalVars->tickcount) * globalVars->intervalPerTick) );
            for( int i = 0; i <= entitySystem->GetHighestEntityIndex(); i++ ){
                entity = entitySystem->GetBaseEntity(i);
                if( entity ){
                    MC_PRINTF("Entity#%d(%p) - Name:(%s)", i, (void*)entity, entity->Schema_DynamicBinding()->binaryName );
                    if( entity->GetOwnerID() >= 0 ){
                        MC_PRINTF(" - Owner:(%d)", entity->GetOwnerID());
                    }
                    MC_PRINTF("\n");
                }
            }
            break;
        case ButtonCode_t::PGUP:
            //vscriptSystem->RunScript("bazinga", false);
            //MC_PRINTF("Local Player ID(%d)\n", *(networkClientService->GetIGameClient()->GetLocalDOTAPlayerID()));
            //newConVar->set_name(mc_custom_str->strValue);
            //newConVar->set_value(mc_custom_str_alt->strValue);
            MC_PRINTF("Handle - (%s)\n", networkMessages->GetMessageHandleByName(mc_custom_str->m_Value.m_pszString) ?
                                                    networkMessages->GetMessageHandleByName(mc_custom_str->m_Value.m_pszString)->unscopedName : "null" );
            break;
        case ButtonCode_t::PGDN:
            /*
            guide.set_guide_workshop_id( 0 );
            guide.set_is_plus_guide( true );
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ) {
                Hooks::SendNetMessage( engine->GetNetChannelInfo( ), networkMessages->GetMessageHandleByName( "CDOTAClientMsg_GuideSelected" ), &guide, BUF_DEFAULT );
            }*/
            break;
        case ButtonCode_t::END:
            for( int i = 0; i <= entitySystem->GetHighestEntityIndex(); i++ ){
                entity = entitySystem->GetBaseEntity(i);
                if( !entity ) continue;
                if( strstr( entity->Schema_DynamicBinding()->binaryName, "C_DOTA_PlayerResource" ) ){
                    playerResource = reinterpret_cast<CDOTAPlayerResource*>( entity );
                    teamData = playerResource->GetPlayerTeamData();
                    if( teamData ) {
                        MC_PRINTF( "TeamData @ %p - num(%d)\n", (void*)playerResource->GetPlayerTeamData(), playerResource->GetPlayerTeamData()->Count() );
                        MC_PRINTF("elements @ %p\n", (void*)teamData->m_pElements);
                        for( int i = 0; i < teamData->Count(); i++ ){
                            MC_PRINTF("element %d @ %p\n", i, (void*)&teamData->operator[](i) );
                            MC_PRINTF( "player %d is level %d - has %d kills - %d deaths\n", i, teamData->operator[](i).m_iLevel, teamData->operator[](i).m_iKills, teamData->operator[](i).m_iDeaths);
                        }
                    }
                }
            }
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
            break;
        case ButtonCode_t::PAUSE:
            //Util::SpewScriptScopes( GetPanoramaScriptScopes(), true );
            MC_PRINTF("Sending metadata\n");
            static uint32_t id = 0;
            id++;
            metadataMsg.set_match_id( id );

            if( !cacheMetaData || cachedSize != mc_send_freq->GetInt() ){
                for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                    CDOTAMatchMetadata_Team *team = metadata.add_teams();
                    team->Clear();
                    for( int j = 0; j < mc_send_freq->GetInt(); j++ ){
                        CDOTAMatchMetadata_Team_Player *player = team->add_players();
                        player->Clear();
                        for( int k = 0; k < mc_send_freq->GetInt(); k++ ){
                            CSOEconItem *econItem = player->add_equipped_econ_items();
                            econItem->Clear();
                        }
                    }
                }
                metadataMsg.set_metadata( metadata.SerializeAsString() );
                MC_PRINTF("cached metadata msg\n");
                cacheMetaData = true;
                cachedSize = mc_send_freq->GetInt();
            }

            Hooks::SendNetMessage( engine->GetNetChannelInfo( ), networkMessages->GetMessageHandleByName( "CDOTAClientMsg_MatchMetadata" ), &metadataMsg, BUF_DEFAULT );
            break;
        case ButtonCode_t::PRINTSCREEN:
            MC_LOGF("Tracing a ray good luck!\n");
            //CTraceFilter_Constructor( &traceFilter, nullptr, 0x69696969, EntHitHandler );
            ray.Init( Vector(100.0f, 200.0f, 300.0f), Vector(100.0f, 200.0f, -1200.0f) );
            traceFilter.Init( 0, 0xFFFFFFFF, EntHitHandler );

            GameTrace_Init( &traceOut );
            client->TraceRay( ray, traceFilter, &traceOut );

            MC_LOGF("Traceout(%p) - filter(%p) - fraction(%f)\n", &traceOut, &traceFilter, traceOut.fraction);
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
        case ButtonCode_t::F11:
            if( !mc_hide_tips->GetBool() || !mc_anti_mute->GetBool() ){
                break;
            }
            tip.set_tip_text("<img src=\"panel-background://ChatCorePanel\"/>"
                                     "<img src=\"panel-background://HudChat\"/>"
                                     "<img src=\"panel-background://ChatLinesContainer\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatCorePanel\"/>"
                                     "<img src=\"panel-background://HudChat\"/>"
                                     "<img src=\"panel-background://ChatLinesContainer\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatCorePanel\"/>"
                                     "<img src=\"panel-background://HudChat\"/>"
                                     "<img src=\"panel-background://ChatLinesContainer\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatLinesPanel\"/>"
                                     "<img src=\"panel-background://ChatCorePanel\"/>"
                                     "<img src=\"panel-background://HudChat\"/>"
                                     "<img src=\"panel-background://ChatLinesContainer\"/><br><br><br><br><br><br><br><br><br><br><br>"
            );

            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                Hooks::SendNetMessage( engine->GetNetChannelInfo(), networkMessages->GetMessageHandleByName("TipAlert"), &tip, BUF_DEFAULT );
            }
            //eventPoints.set_event_id( 22 );
            //eventPoints.set_account_id( 87214030 );
            //SendMessageGenericClientToGC(&eventPoints, EDOTAGCMsg::k_EMsgDOTAGetEventPoints);
            break;
        default:
            return inputInternalVMT->GetOriginalMethod<SetKeyCodeStateFn>(96)(thisptr, code, pressed);
    }
}