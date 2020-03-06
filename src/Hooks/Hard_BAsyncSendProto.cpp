#include "HardHooks.h"

#include "../Utils/Protobuf.h"
#include "../Utils/Logger.h"
#include "../protos/mcdota.pb.h"

bool HardHooks::MyBAsyncSendProto( IProtoBufSendHandler &handler, unsigned int unk,
                                    CMsgProtoBufHeader const &header, google::protobuf::Message *msg ) {
    MC_LOGF("[GC]Send - Msg(%p)\n", (void*)msg);
    google::protobuf::Message *copy = msg->New();
    copy->CopyFrom( *msg );

    const google::protobuf::Descriptor* desc = copy->GetDescriptor();
    if( !desc ){
        MC_LOGF("No Descriptor!\n");
        goto end;
    }

    MC_LOGF("TypeName: %s\n", desc->name().c_str());
    Util::Protobuf::LogMessageContents( copy );

    //if( strstr( desc->name().c_str(), "CMsgDOTAChatMessage" ) ){
    //    Util::Protobuf::EditFieldTraverseUInt32( msg, "battle_cup_streak", 5 );
    //}
    //std::raise(SIGINT);
end:
    HardHooks::BAsyncSendProto.Remove();
    bool ret = ((BAsyncSendProtoFn)BAsyncSendProtoFnAddr)( handler, unk, header, msg );
    HardHooks::BAsyncSendProto.Install();

    delete copy;
    return ret;
}