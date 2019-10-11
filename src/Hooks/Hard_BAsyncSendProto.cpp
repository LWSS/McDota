#include "HardHooks.h"

#include "../Interfaces.h"
#include "../Utils/Protobuf.h"

bool HardHooks::MyBAsyncSendProto( IProtoBufSendHandler &handler, unsigned int unk,
                                    CMsgProtoBufHeader const &header, google::protobuf::Message *msg ) {
    Util::Log("[GC]Send - Msg(%p)\n", (void*)msg);
    google::protobuf::Message *copy = msg->New();
    copy->CopyFrom( *msg );

    const google::protobuf::Descriptor* desc = copy->GetDescriptor();
    if( !desc ){
        Util::Log("No Descriptor!\n");
        goto end;
    }

    Util::Log("TypeName: %s\n", desc->name().c_str());
    Util::Protobuf::LogMessageContents( copy );

    //if( strstr( desc->name().c_str(), "CMsgDOTAChatMessage" ) ){
    //    Util::Protobuf::EditFieldTraverseUInt32( msg, "battle_cup_streak", 5 );
    //}
    //std::raise(SIGINT);
end:
    delete copy;
    HardHooks::BAsyncSendProto.Remove();
    bool ret = ((BAsyncSendProtoFn)BAsyncSendProtoFnAddr)( handler, unk, header, msg );
    HardHooks::BAsyncSendProto.Install();
    return ret;
}