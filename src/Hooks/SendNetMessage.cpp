#include "Hooks.h"
#include <csignal>

#include "../Utils/Protobuf.h"
#include "../Settings.h"

#include <google/protobuf/text_format.h>

typedef bool (* SendNetMessageFn)( INetChannel *thisptr, NetMessageHandle_t *, void const*, NetChannelBufType_t );

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

    NetMessageInfo_t *info;
    const char *name;

    if( mc_allow_customnames->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();
        if( strstr( name, "CNETMsg_SetConVar" ) != nullptr ){
            if( Util::GetEpochMs() - lastSetConVarMsg < 100 ){
                return true;
            }
            lastSetConVarMsg = Util::GetEpochMs();
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

    if( mc_command_repeater->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( strstr(name, "CDOTAClientMsg_ExecuteOrders") != nullptr ){
            CUtlString string;
            string.m_Memory.m_pMemory = new uint8_t[4096];
            string.m_Memory.m_nAllocationCount = 4096;
            string.m_Memory.m_nGrowSize = 4096;
            info->pProtobufBinding->ToString( msg, &string );
            static int seq = 5000;
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                Util::Protobuf::EditFieldTraverseInt32(msg, "sequence_number", seq++);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, msg, type );
            }
            delete[] string.m_Memory.m_pMemory;
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

        Util::Log( "NetMessage: Type(%d-%s) - Message@: (%p) - info@: (%p) - name(%s) -type(%d)\n", type, Type2String(type), msg, info, info->pProtobufBinding->GetName(), info->pProtobufBinding->GetBufType() );

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