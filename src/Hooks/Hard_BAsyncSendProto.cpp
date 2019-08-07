#include "HardHooks.h"

#include "../Interfaces.h"
#include "../Utils/Protobuf.h"

bool HardHooks::MyBAsyncSendProto( IProtoBufSendHandler &handler, unsigned int unk,
                                    CMsgProtoBufHeader const &header, google::protobuf::Message const &msg ) {
    Util::Log("AsyncSendProto Yahoo! - Msg(%p)\n", (void*)&msg);
    const google::protobuf::Descriptor* desc = msg.GetDescriptor();
    if( !desc ){
        Util::Log("No Descriptor!\n");
    } else {
        Util::Log("TypeName: %s\n", desc->name().c_str());
        //Util::Protobuf::LogMessageContents( &msg );
    }

    //std::raise(SIGINT);

    HardHooks::BAsyncSendProto.Remove();
    bool ret = ((BAsyncSendProtoFn)BAsyncSendProtoFnAddr)( handler, unk, header, msg );
    HardHooks::BAsyncSendProto.Install();
    return ret;
}