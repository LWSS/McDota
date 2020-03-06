#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../SDK/color.h"

enum types_t : uint8_t {
    TYPE_NEWBLOCK = 0,
    TYPE_STRING,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_PTR,
    TYPE_WSTRING,
    TYPE_COLOR,
    TYPE_UINT64,



    TYPE_ENDBLOCK = 0xB, // technically not accurate
};


/// Example data: data: "VBKV\263\001\211\357\000\000\001keyone_str\000valueone\000\001keytwo_str\000valuetwo\000\002keythree_int\000\010\000\000\000\003keyfour_float\000\000\000\213B\013\013"
/// binary structure is something like this
// VBKV - magic
// \263\001\211\357 - crc
// \000\000 - new block, new block
/// Key Entries
//\001keyone_str\000 valueone\000
//\001keytwo_str\000 valuetwo\000
//\002keythree_int\000 \010\000\000\000
//\003keyfour_float\000 \000\000\213B

//\013\013 - 0xB - end of block, end of block


// WIP keyvalue class. Credits: moofmonkey for original version.
struct KVEntry {
    types_t type;

    KVEntry(types_t type) : type(type) {}
    virtual ~KVEntry() {}
};

#define DEF_ENTRY_TYPE(type_name, val_type) \
struct KV##type_name : public KVEntry {\
    std::string name;\
	val_type val;\
	KV##type_name(std::string name, types_t type, val_type val) : KVEntry(type), name(name), val(val) {}\
}
DEF_ENTRY_TYPE(String, std::string);
DEF_ENTRY_TYPE(Int, int);
DEF_ENTRY_TYPE(Float, float);
DEF_ENTRY_TYPE(Ptr, uint32_t);
DEF_ENTRY_TYPE(WString, std::wstring);
DEF_ENTRY_TYPE(ColorRGBA, ColorRGBA);
DEF_ENTRY_TYPE(BigInt, uint64_t);
#undef DEF_ENTRY_TYPE


namespace KeyValue
{
    std::vector<KVEntry*> ParseBinaryKV(const char* data, size_t len);
    std::string SerializeEntriesToString(std::vector<KVEntry*> entries);
}