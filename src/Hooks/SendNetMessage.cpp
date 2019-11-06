#include "Hooks.h"
#include <csignal>

#include "../Utils/Protobuf.h"
#include "../Settings.h"

#include "../protos/mcdota.pb.h"

typedef bool (* SendNetMessageFn)( INetChannel *thisptr, NetMessageHandle_t *, google::protobuf::Message*, NetChannelBufType_t );

static const char* Type2String( NetChannelBufType_t type )
{
    switch( type )
    {
        CASE_STRING( BUF_DEFAULT );
        CASE_STRING( BUF_RELIABLE );
        CASE_STRING( BUF_UNRELIABLE );
        CASE_STRING( BUF_VOICE );
        default:
            return "UNKNOWN Type!";
    }
}

long lastSetConVarMsg = 0;
bool Hooks::SendNetMessage( INetChannel *thisptr, NetMessageHandle_t *messageHandle, google::protobuf::Message* msg, NetChannelBufType_t type ) {
    std::string scratch;
    NetMessageInfo_t *info;
    const char *name;

    info = networkMessages->GetNetMessageInfo(messageHandle);
    name = info->pProtobufBinding->GetName();

    /*
    if( mc_crash_server->GetBool() && strstr( name, "CNETMsg_SignonState" ) ){
        uint32_t signon = Util::Protobuf::GetFieldTraverseUInt32(msg, "signon_state").value();
        if( signon == (uint32_t)SignonState_t::SIGNONSTATE_PRESPAWN ){
            mc_crash_server->SetValue(false);
            int32_t value = 0xADADADAD;//mc_custom_int->GetInt();
            Util::Log("Changing localID from %d to %d\n", *(networkClientService->GetIGameClient()->GetLocalDOTAPlayerID()), value);
            *(networkClientService->GetIGameClient()->GetLocalDOTAPlayerID()) = value;
            netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, msg, type );
            return true;
        }
    }*/

    if( mc_stall_connect->GetBool() && strstr( name, "CNETMsg_SignonState" ) ) {
        uint32_t signon = Util::Protobuf::GetFieldTraverseUInt32( msg, "signon_state" ).value( );
        if ( signon >= ( uint32_t )SignonState_t::SIGNONSTATE_PRESPAWN ) {
            return true;
        }
    }

    /*
    if( strstr( name, "CCLCMsg_ClientInfo" ) ){
        Util::Log("Suppressing clientinfo...\n");
        return true;
    }
    if( strstr( name, "CMsgSource1LegacyListenEvents" ) ){
        Util::Log("Suppressing listen events\n");
        return true;
    }*/

    if( mc_anti_mute->GetBool() && strstr( name, "CNETMsg_StringCmd" ) ){
        CNETMsg_StringCmd *ree = static_cast<CNETMsg_StringCmd*>( msg );
        std::string command = std::string(ree->command().c_str());
        if( command.find("say_team") == 0 ){
            command.erase(0, 10);
            command.pop_back();
            CDOTAClientMsg_TipAlert tip;
            tip.set_tip_text(command);
            static auto msgHandle = networkMessages->GetMessageHandleByName("TipAlert");
            netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, msgHandle, &tip, BUF_DEFAULT );
            return true;
        } else if( command.find("say") == 0 ){
            command.erase(0, 5);
            command.pop_back();
            CDOTAClientMsg_TipAlert tip;
            tip.set_tip_text(command);
            static auto msgHandle = networkMessages->GetMessageHandleByName("TipAlert");
            netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, msgHandle, &tip, BUF_DEFAULT );
            return true;
        }
    }

    if( mc_send_status->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( strstr(name, "CCLCMsg_ServerStatus") != nullptr ){
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, msg, type );
            }
        }
    }

    if( mc_send_voice->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( strstr(name, "CCLCMsg_VoiceData") != nullptr ){
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, msg, type );
            }
        }
    }

    if( mc_log_sendnetmsg->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( mc_log_sendnetmsg_filter_commons->GetBool() ){
            if( strstr(name, "CNETMsg_Tick")
                || strstr(name, "CCLCMsg_Move")
                || strstr(name, "CCLCMsg_BaselineAck") ){
                goto end;
            }
        }

        Util::Log( "NetMessage: Type(%d-%s) - Handle(%p) - Message@: (%p) - info@: (%p) - name(%s) -type(%d)\n", type, Type2String(type), messageHandle, msg, info, info->pProtobufBinding->GetName(), info->pProtobufBinding->GetBufType() );

        if( mc_log_sendnetmsg_to_string->GetBool() ){

            CUtlString string;
            string.m_Memory.m_pMemory = new uint8_t[4096];
            string.m_Memory.m_nAllocationCount = 4096;
            string.m_Memory.m_nGrowSize = 4096;
            info->pProtobufBinding->ToString( msg, &string );
            //Util::Log( "ToString: (%s)\n", info->pProtobufBinding->ToString( msg, &string ) );
            delete[] string.m_Memory.m_pMemory;
            /*
            if( strstr(name, "CDOTAClientMsg_SetUnitShareFlag") != NULL ){
                Util::Protobuf::EditFieldTraverseUInt32( msg, "playerID", (unsigned int)mc_custom_int->GetInt() );
                Util::Protobuf::EditFieldTraverseBool( msg, "state", true );
            }*/
            //std::string out;
            //msg->SerializeToString( &out );


            string.m_Memory.m_pMemory = new uint8_t[4096];
            string.m_Memory.m_nAllocationCount = 4096;
            string.m_Memory.m_nGrowSize = 4096;
            Util::Log( "ToString: (%s)\n", info->pProtobufBinding->ToString( msg, &string ) );
            delete[] string.m_Memory.m_pMemory;
            //Util::Protobuf::LogMessageContents(msg);

            std::raise(SIGINT);
        }
    }

end:
    return netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, msg, type );
}