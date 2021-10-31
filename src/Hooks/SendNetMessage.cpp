#include "Hooks.h"
#include <csignal>

#include "../Utils/Protobuf.h"
#include "../Utils/Logger.h"

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
    /*
    if( mc_crash_server->GetBool() && strstr( name, "CNETMsg_SignonState" ) ){
        uint32_t signon = Util::Protobuf::GetFieldTraverseUInt32(msg, "signon_state").value();
        if( signon == (uint32_t)SignonState_t::SIGNONSTATE_PRESPAWN ){
            mc_crash_server->SetValue(false);
            int32_t value = 0xADADADAD;//mc_custom_int->GetInt();
            MC_LOGF("Changing localID from %d to %d\n", *(networkClientService->GetIGameClient()->GetLocalDOTAPlayerID()), value);
            *(networkClientService->GetIGameClient()->GetLocalDOTAPlayerID()) = value;
            netChannelVMT->GetOriginalMethod<SendNetMessageFn>(70)( thisptr, messageHandle, msg, type );
            return true;
        }
    }*/

    if( mc_stall_connect->GetBool() && messageHandle->messageID == 7 ) { //CNETMsg_SignonState [7]
        uint32_t signon = Util::Protobuf::GetFieldTraverseUInt32( msg, "signon_state" ).value( );
        if ( signon >= ( uint32_t )SignonState_t::SIGNONSTATE_SPAWN ) {
            return true;
        }
    }

    if( mc_anti_mute->GetBool() && messageHandle->messageID == 394 ){ //CDOTAClientMsg_ChatMessage [394]
        CDOTAClientMsg_ChatMessage *chat = static_cast<CDOTAClientMsg_ChatMessage*>( msg );
        CDOTAClientMsg_TipAlert tip;
        tip.set_tip_text(chat->message_text().c_str());
        netChannelVMT->GetOriginalMethod<SendNetMessageFn>(70)( thisptr, networkMessages->FindNetworkMessage2("CDOTAClientMsg_TipAlert"), &tip, BUF_DEFAULT );
        return true;
    }

    if( mc_send_status->GetBool() ){
        if( messageHandle->messageID == 31 ){ // CCLCMsg_ServerStatus [31]
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(70)( thisptr, messageHandle, msg, type );
            }
        }
    }

    if( mc_send_voice->GetBool() ){
        if( messageHandle->messageID == 22 ){ // CCLCMsg_VoiceData [22]
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(70)( thisptr, messageHandle, msg, type );
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

        MC_LOGF( "NetMessage: Type(%d-%s) - Handle(%p) - Message@: (%p) - info@: (%p) - name(%s) -type(%d)\n", type, Type2String(type), messageHandle, msg, info, info->pProtobufBinding->GetName(), info->pProtobufBinding->GetBufType() );

        if( mc_log_sendnetmsg_to_string->GetBool() ){

            CUtlString string;
            string.m_Memory.m_pMemory = new uint8_t[4096];
            string.m_Memory.m_nAllocationCount = 4096;
            string.m_Memory.m_nGrowSize = 0;
            MC_LOGF( "ToString[%d]: (%s)\n", messageHandle->messageID, info->pProtobufBinding->ToString( msg, &string ) );
            delete[] string.m_Memory.m_pMemory;
            //Util::Protobuf::LogMessageContents(msg);

            std::raise(SIGINT);
        }
    }

end:
    return netChannelVMT->GetOriginalMethod<SendNetMessageFn>(70)( thisptr, messageHandle, msg, type );
}