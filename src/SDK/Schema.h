#pragma once

#include <cstdint>
#include <array>

struct CSchemaClassBinding {
    CSchemaClassBinding* parent;
    const char* bindingName; // ex: C_World
    const char* dllName; // ex: libclient.so
    const char* libName; // ex: client
};


struct Netvar // Size: 0x138
{
    const char *netvarName; // ex: m_nMinGPULevel
    void *_pad[2]; // 0x8
    uint32_t offset; // 0x18
    uint32_t something; // 0x1C
    void *_pad2[10];
    const char *typeName; // ex: uint8
    void *_pad3[5];
};

struct NetvarWrapper
{
    Netvar *netVar;
    char sevenByteSwag[7];
} __attribute__((__packed__));

struct SchemaRecvTable {
    const char *varName;
    void *_pad;
    int32_t numOfVars;
    int32_t something;
    NetvarWrapper *netVarsArray;
};