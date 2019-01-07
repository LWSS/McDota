#include "hooks.h"
#include <csignal>

#include "../Utils/util.h"
#include "../settings.h"

typedef bool (* SendNetMessageFn)( INetChannel *thisptr, NetMessageHandle_t *, void const*, NetChannelBufType_t );

static char saved[2048];


static const char* Type2String( NetChannelBufType_t type )
{
    switch( type )
    {
        case NetChannelBufType_t::BUF_DEFAULT:
            return "Default";
        case NetChannelBufType_t::BUF_RELIABLE:
            return "Reliable";
        case NetChannelBufType_t::BUF_UNRELIABLE:
            return "UnReliable";
        case NetChannelBufType_t::BUF_VOICE:
            return "Voice";
        default:
            return "UNKNOWN!";
    }
}

static VMT* bindingVMT;

typedef void (* ToStringFn)( void const *, CUtlString * );

void ToString( void const * thisptr, CUtlString *str )
{
    Util::Log("ToString called - this: %p - str: %p\n", thisptr, (void*)str);
    std::raise(SIGINT);
    bindingVMT->GetOriginalMethod<ToStringFn>( 2 )( thisptr, str );
}

bool Hooks::SendNetMessage( INetChannel *thisptr, NetMessageHandle_t *messageHandle, void const* something, NetChannelBufType_t type ) {

    NetMessageInfo_t *info;
    const char *name;
    static bool bFirst = true;
    if( bFirst ){
        cvar->ConsoleDPrintf("Net Msg! Handle: %d, Type: %d(%s), something @ (%p)\n", *messageHandle, type, Type2String(type), something );
        memcpy(saved, something, 2048);
        cvar->ConsoleDPrintf("Copying 2048 bytes to: (%p)\n", (void*)saved);
        bFirst = false;
    }

    if( mc_send_status->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( strstr(name, "CCLCMsg_ServerStatus") != NULL ){
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, something, type );
            }
        }
    }


    if( mc_send_voice->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( strstr(name, "CCLCMsg_VoiceData") != NULL ){
            for( int i = 0; i < mc_send_freq->GetInt(); i++ ){
                engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
                engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
                netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, something, type );
            }
        }
    }

    if( mc_log_sendnetmsg->GetBool() ){
        info = networkMessages->GetNetMessageInfo(messageHandle);
        name = info->pProtobufBinding->GetName();

        if( mc_log_sendnetmsg_filter_commons->GetBool() ){
            if( !strstr(name, "CNETMsg_Tick") && !strstr(name, "CCLCMsg_Move") && !strstr(name, "CCLCMsg_BaselineAck") ){
                Util::Log( "NetMessage: Type(%d-%s) - Message@: (%p) - info@: (%p) - name(%s) -type(%d)\n", type, Type2String(type), something, info, info->pProtobufBinding->GetName(), info->pProtobufBinding->GetBufType() );

                //net_showmsg 1
                //bindingVMT = new VMT( info->pProtobufBinding );
                //bindingVMT->HookVM(ToString, 2);
                //bindingVMT->ApplyVMT();
                //std::string str("bazinga");
                //info->pProtobufBinding->ToString(str);
            }
        } else {
            Util::Log( "NetMessage: Type(%d-%s) - Message@: (%p) - info@: (%p) - name(%s) -type(%d)\n", type, Type2String(type), something, info, info->pProtobufBinding->GetName(), info->pProtobufBinding->GetBufType() );
            std::raise(SIGINT);
        }
    }

    return netChannelVMT->GetOriginalMethod<SendNetMessageFn>(62)( thisptr, messageHandle, something, type );

}