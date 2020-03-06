#include "Keyvalue.h"

#include "Crc32.h"
#include "../Utils/Logger.h"

static constexpr uint32_t VBKV_magic = 0x564b4256; // VBKV
struct VBKVHeader {
    uint32_t magic; // VBKV
    uint32_t crc32;
};

static inline std::string GetName( const char* const str, size_t *offsetInBuffer )
{
    // grab null terminated string for keyname
    std::string name((str + *offsetInBuffer));
    //MC_LOGF("Found keyname(%s)\n", name.c_str());
    size_t name_len = name.size() + 1;
    *offsetInBuffer += name_len;

    return name;
}

static std::vector<KVEntry*> ParseBinaryKV_Internal(const char* const data, size_t data_len) {
    std::vector<KVEntry*> vec;

    for( size_t  i = 0; i < data_len; ){
        types_t type = (types_t)data[i];
        i++;

        std::string keyName;

        switch (type) {
            case TYPE_NEWBLOCK: {
                vec.push_back(new KVEntry(type));
                break;
            }
            case TYPE_STRING: {
                keyName = GetName( data, &i );
                std::string strValue( (data + i) );
                vec.push_back(new KVString(keyName, type, strValue));
                i += strValue.size() + 1;
                break;
            }
            case TYPE_INT:
                keyName = GetName( data, &i );
                vec.push_back(new KVInt(keyName, type, *(int*)(data + i)));
                i += sizeof(int);
                break;
            case TYPE_FLOAT:
                keyName = GetName( data, &i );
                vec.push_back(new KVFloat(keyName, type, *(float*)(data + i)));
                i += sizeof(float);
                break;
            case TYPE_PTR:
                keyName = GetName( data, &i );
                vec.push_back(new KVPtr(keyName, type, *(uint32_t*)(data + i)));
                i += sizeof(uint32_t);
                break;
            case TYPE_WSTRING: {
                keyName = GetName( data, &i );
                std::wstring strValue = std::wstring((wchar_t*)(data + i));
                vec.push_back(new KVWString(keyName, type, strValue));
                i += (strValue.size() + 1) * 2;
                break;
            }
            case TYPE_COLOR:
                keyName = GetName( data, &i );
                vec.push_back(new KVColorRGBA(keyName, type, *(ColorRGBA*)(data + i)));
                i += sizeof(ColorRGBA);
                break;
            case TYPE_UINT64:
                keyName = GetName( data, &i );
                vec.push_back(new KVBigInt(keyName, type, *(uint64_t*)(data + i)));
                i += sizeof(uint64_t);
                break;
            case TYPE_ENDBLOCK:
                vec.push_back(new KVEntry(type));
                break;
        }
    }
    return vec;
}

std::vector<KVEntry*> KeyValue::ParseBinaryKV(const char* data, size_t len) {
    VBKVHeader* header = (VBKVHeader*)data;
    uint32_t crcTable;
    std::vector<KVEntry*> parsedKV;

    if (len < sizeof(VBKVHeader)){
        MC_LOGF("ParseBinaryKV: Error- length is too small to be valid.\n");
        return parsedKV;
    }
    if (header->magic != VBKV_magic){
        MC_LOGF("ParseBinaryKV: Error- magic doesn't match.\n");
        return parsedKV;
    }

    data += sizeof(VBKVHeader);
    len -= sizeof(VBKVHeader);



    crcTable = consthash::crc32( data, len );

    if (crcTable != header->crc32) {
        MC_LOGF("ParseBinaryKV: Error- crc doesn't match\n");
        return parsedKV;
    }

    parsedKV = ParseBinaryKV_Internal( data, len );
    MC_LOGF("Parsed %d Keyvalues\n", parsedKV.size() );
    /*
    if (parsedKV.size() != 1) {
        for (auto obj : parsedKV)
            delete obj;

        MC_LOGF("ParseVBKV: Error- size != 1\n");
        return nullptr;
    }*/

    return parsedKV;
}


static std::string SerializeEntryToString(KVEntry* entry) {
    std::string out;
    switch (entry->type) {
        case TYPE_NEWBLOCK: {
            out += '\x00';
            break;
        }
        case TYPE_STRING: {
            out += entry->type;
            out += ((KVString*)entry)->name;
            out += '\0';
            out += ((KVString*)entry)->val;
            out += '\0';
            break;
        }
        case TYPE_INT: {
            out += entry->type;
            out += ((KVInt*)entry)->name;
            out += '\0';
            auto val = ((KVInt*)entry)->val;
            for (size_t i = 0, end = sizeof(val); i < end; i++)
                out += ((char*)&val)[i];
            break;
        }
        case TYPE_FLOAT: {
            out += entry->type;
            out += ((KVFloat*)entry)->name;
            out += '\0';
            auto val = ((KVFloat*)entry)->val;
            for (size_t i = 0, end = sizeof(val); i < end; i++)
                out += ((char*)&val)[i];
            break;
        }
        case TYPE_PTR: {
            out += entry->type;
            out += ((KVPtr*)entry)->name;
            out += '\0';
            auto val = ((KVPtr*)entry)->val;
            for (size_t i = 0, end = sizeof(val); i < end; i++)
                out += ((char*)&val)[i];
            break;
        }
        case TYPE_WSTRING:
            out += entry->type;
            //out += "wstring unsupported";
            MC_LOGF("wstring unsupported!\n");
            out += '\x00';
            break;
        case TYPE_COLOR: {
            out += entry->type;
            out += ((KVColorRGBA*)entry)->name;
            out += '\0';
            auto val = ((KVColorRGBA*)entry)->val;
            for (size_t i = 0, end = sizeof(val); i < end; i++)
                out += ((char*)&val)[i];
            break;
        }
        case TYPE_UINT64: {
            out += entry->type;
            out += ((KVBigInt*)entry)->name;
            out += '\0';
            auto val = ((KVBigInt*)entry)->val;
            for (size_t i = 0, end = sizeof(val); i < end; i++)
                out += ((char*)&val)[i];
            break;
        }
        case TYPE_ENDBLOCK:
            out += '\x0B';
            break;
    }
    return out;
}

std::string KeyValue::SerializeEntriesToString(std::vector<KVEntry *> entries) {
    std::string ret = "VBKV";
    uint32_t crc;
    std::string entriesStr = "";

    if( entries.size() == 0 ){
        return std::string("Empty entries parameter!" );
    }

    for( KVEntry *entry : entries ){
        entriesStr += SerializeEntryToString( entry );
    }

    crc = consthash::crc32( entriesStr.data(), entriesStr.size() );

    for (size_t i = 0, end = sizeof(crc); i < end; i++)
        ret += ( ((char*)&crc)[i] );

    ret += entriesStr;

    return ret;
}