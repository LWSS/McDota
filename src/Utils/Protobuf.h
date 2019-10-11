#pragma once


#include <google/protobuf/text_format.h>
#include <string>
#include <cstdint>
#include <optional>
#include <vector>

/* Various functions that deal with protobuf messages */
namespace Util::Protobuf
{
    void LogMessageContents( const google::protobuf::Message* m, int tabNum = 0 );

    /* These return true if found/changed */
    bool EditFieldTraverseInt32( google::protobuf::Message* msg, const char *name, int32_t value );
    bool EditFieldTraverseUInt32( google::protobuf::Message* msg, const char *name, uint32_t value );
    bool EditFieldTraverseInt64( google::protobuf::Message* msg, const char *name, int64_t value );
    bool EditFieldTraverseUInt64( google::protobuf::Message* msg, const char *name, uint64_t value );
    bool EditFieldTraverseFloat( google::protobuf::Message* msg, const char *name, float value );
    bool EditFieldTraverseDouble( google::protobuf::Message* msg, const char *name, double value );
    bool EditFieldTraverseBool( google::protobuf::Message* msg, const char *name, bool value );
    //bool EditFieldTraverseString( google::protobuf::Message *msg, const char *name, const std::string& value ); // doesn't work - use protos instead.
    bool EditFieldTraverseEnumValue( google::protobuf::Message* msg, const char *name, int value );

    /* This is the only way to get a string - To set a string, you will need to use proto file */
    const std::string& GetStringReference( const google::protobuf::Message* msg, const char *name, std::string *scratch );

    std::optional<int32_t> GetFieldTraverseInt32( google::protobuf::Message* msg, const char *name );
    std::optional<uint32_t> GetFieldTraverseUInt32( google::protobuf::Message* msg, const char *name );
    std::optional<int64_t> GetFieldTraverseInt64( google::protobuf::Message* msg, const char *name );
    std::optional<uint64_t> GetFieldTraverseUint64( google::protobuf::Message* msg, const char *name );
    std::optional<float> GetFieldTraverseFloat( google::protobuf::Message* msg, const char *name );
    std::optional<double> GetFieldTraverseDouble( google::protobuf::Message* msg, const char *name );
    std::optional<bool> GetFieldTraverseBool( google::protobuf::Message* msg, const char *name );
    std::optional<std::string> GetFieldTraverseString( google::protobuf::Message* msg, const char *name );
    std::optional<int> GetFieldTraverseEnumValue( google::protobuf::Message* msg, const char *name );

    /* Vector returned can be empty */
    std::vector<int32_t> GetRepeatedFieldTraverseInt32( google::protobuf::Message* msg, const char *name );
    std::vector<uint32_t> GetRepeatedFieldTraverseUInt32( google::protobuf::Message* msg, const char *name );
    std::vector<int64_t> GetRepeatedFieldTraverseInt64( google::protobuf::Message* msg, const char *name );
    std::vector<uint64_t> GetRepeatedFieldTraverseUInt64( google::protobuf::Message* msg, const char *name );
    std::vector<float> GetRepeatedFieldTraverseFloat( google::protobuf::Message* msg, const char *name );
    std::vector<double> GetRepeatedFieldTraverseDouble( google::protobuf::Message* msg, const char *name );
    std::vector<bool> GetRepeatedFieldTraverseBool( google::protobuf::Message* msg, const char *name );
    std::vector<std::string> GetRepeatedFieldTraverseString( google::protobuf::Message* msg, const char *name );
    std::vector<int> GetRepeatedFieldTraverseEnumValue( google::protobuf::Message* msg, const char *name );
}