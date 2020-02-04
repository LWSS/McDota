#pragma once

#include "../Utils/subhook/subhook.h"
#include "../SDK/SDK.h"

// (libclient)
//GCSDK::CGCClient::DispatchPacket(GCSDK::IMsgNetPacket *)
//GCSDK::CGCClient::BSendMessage(GCSDK::CProtoBufMsgBase const&)

namespace HardHooks
{
    inline subhook::Hook DispatchPacket;
    inline subhook::Hook BAsyncSendProto;

    typedef bool ( *DispatchPacketFn)( void *, IMsgNetPacket * );
    typedef bool ( *BAsyncSendProtoFn)( IProtoBufSendHandler &, unsigned int, CMsgProtoBufHeader const&, google::protobuf::Message * );

    bool MyDispatchPacket( void* thisptr, IMsgNetPacket *netPacket );
    bool MyBAsyncSendProto( IProtoBufSendHandler &, unsigned int, CMsgProtoBufHeader const&, google::protobuf::Message * );
}