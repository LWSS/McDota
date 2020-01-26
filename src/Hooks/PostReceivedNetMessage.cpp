#include "Hooks.h"

#include "../Utils/Protobuf.h"
#include "../Settings.h"

typedef void (* PostReceivedNetMessageFn)( INetChannel *, NetMessageHandle_t *, google::protobuf::Message*, NetChannelBufType_t const *);

uint32_t biggestSignon = 0;

void Hooks::PostReceivedNetMessage( INetChannel *thisptr, NetMessageHandle_t *messageHandle, google::protobuf::Message *msg, NetChannelBufType_t const *type ) {

    NetMessageInfo_t *info;
    const char *name;

    if( mc_log_recvnetmsg->GetBool() ){
        info = networkMessages->GetNetMessageInfo( messageHandle );
        name = info->pProtobufBinding->GetName();

        if( mc_log_recvnetmsg_filter_commons ){
            if( strstr(name, "CNETMsg_Tick") ||
                strstr(name, "CSVCMsg_PacketEntities") ){
                goto end;
            }
        }
        Util::Log( "Recv Msg: (%s)\n", name );

        if( mc_log_recvnetmsg_to_string->GetBool() ){
            CUtlString string;
            string.m_Memory.m_pMemory = new uint8_t[4096];
            string.m_Memory.m_nAllocationCount = 4096;
            string.m_Memory.m_nGrowSize = 4096;
            Util::Log( "Net Msg[%d] Received: (%s)\n", messageHandle->messageID, info->pProtobufBinding->ToString( msg, &string ) );
            delete[] string.m_Memory.m_pMemory;
        }
    }

    if( mc_anti_mute->GetBool() && mc_hide_tips->GetBool() ){
        if( messageHandle->messageID == 378 ) { // CDOTAClientMsg_TipAlert [378]
            Util::Log("Suppressing a tipalert\n");
            return;
        }
    }

    /*
    if( strstr( name, "CNETMsg_SignonState" ) ){
        uint32_t signon = Util::Protobuf::GetFieldTraverseUInt32( msg, "signon_state" ).value();
        if( signon > biggestSignon ){
            biggestSignon = signon;
        } else {
            return;
        }
    }*/

end:
    return netChannelVMT->GetOriginalMethod<PostReceivedNetMessageFn>(84)( thisptr, messageHandle, msg, type );
}