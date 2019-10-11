#pragma once

#include "../Utils/subhook/subhook.h"
#include "../SDK/SDK.h"

// (libclient)
//GCSDK::CGCClient::DispatchPacket(GCSDK::IMsgNetPacket *)
//GCSDK::CGCClient::BSendMessage(GCSDK::CProtoBufMsgBase const&)

namespace HardHooks
{
    inline subhook::Hook DispatchPacket;
    inline subhook::Hook BSendMessage;
    inline subhook::Hook BAsyncSendProto;
    inline subhook::Hook InitFromPacketInternal;

    typedef bool ( *DispatchPacketFn)( void *, CStructNetPacket * );
    typedef void ( *BSendMessageFn)( void *, CProtoBufMsgBase * );
    typedef bool ( *BAsyncSendProtoFn)( IProtoBufSendHandler &, unsigned int, CMsgProtoBufHeader const&, google::protobuf::Message * );
    typedef void ( *InitFromPacketInternalFn )( CProtoBufMsgBase *thisptr, CStructNetPacket *IMsgNetPacket );
    typedef void ( *CProtoBufMsgBaseConstructorFn )( CProtoBufMsgBase *babyMsg, unsigned int type );

    bool MyDispatchPacket( void* thisptr, CStructNetPacket *IMsgNetPacket );
    void MyBSendMessage( void* thisptr, CProtoBufMsgBase *msg );
    bool MyBAsyncSendProto( IProtoBufSendHandler &, unsigned int, CMsgProtoBufHeader const&, google::protobuf::Message * );
    void MyInitFromPacketInternal( CProtoBufMsgBase *thisptr, CStructNetPacket *IMsgNetPacket );
}