#pragma once

#include "definitions.h"

enum ArgTypes_t : uint8_t
{
    VOID = 0x0,
    FLOAT = 0x1,
    _UNK1 = 0x2, // These unknown are so-called "unknown_variant_type" in the game engine as well.
    VECTOR = 0x3,
    QUATERNION = 0x4,
    INTEGER = 0x5,
    BOOLEAN = 0x6,
    _UNK2 = 0x7,
    CHARACTER = 0x8,
    COLOR = 0x9,
    _UNK3 = 0xA,
    _UNK4 = 0xB,
    _UNK5 = 0xC,
    EHANDLE = 0xD,
    _UNK6 = 0xE,
    _UNK7 = 0xF,
    _UNK8 = 0x10,
    _UNK9 = 0x11,
    _UNK10 = 0x12,
    _UNK11= 0x13,
    _UNK12 = 0x14,
    _UNK13 = 0x15,
    _UNK14 = 0x16,
    _UNK15 = 0x17,
    _UNK16 = 0x18,
    VECTOR2D = 0x19,
    INT64 = 0x1A,
    VECTOR4D = 0x1B,
    RESOURCE_HANDLE = 0x1C,
    _UNK17 = 0x1D,
    CSTRING = 0x1E,
    H_SCRIPT = 0x1F,
    VARIANT = 0x20,
    UINT64 = 0x21,
    FLOAT64 = 0x22,
    _UNK18 = 0x23,
    _UNK19 = 0x24,
    UNSIGNED = 0x25,
    UTLSTRINGTOKEN = 0x26,
    QANGLE = 0x27,
    _UNK20 = 0x28,
    _UNK21 = 0x29,
    _UNK22 = 0x2A,
    _UNK23 = 0x2B,
    _UNK24 = 0x2C,
    _UNK25 = 0x2D,
    _UNK26 = 0x2E,
    _UNK27 = 0x2F,
    HSCRIPT_LIGHTBINDING = 0x30,
    JS_VALUE = 0x31,
    JS_OBJECT = 0x32,
    JS_ARRAY = 0x33,
    JS_RAW_ARGS = 0x34,
};

inline const char *GetArgTypeString( ArgTypes_t argType ){
    switch( argType ){
        CASE_STRING(VOID);
        CASE_STRING(FLOAT);
        CASE_STRING(VECTOR);
        CASE_STRING(QUATERNION);
        CASE_STRING(INTEGER);
        CASE_STRING(BOOLEAN);
        CASE_STRING(CHARACTER);
        CASE_STRING(COLOR);
        CASE_STRING(EHANDLE);
        CASE_STRING(VECTOR2D);
        CASE_STRING(INT64);
        CASE_STRING(VECTOR4D);
        CASE_STRING(RESOURCE_HANDLE);
        CASE_STRING(CSTRING);
        CASE_STRING(H_SCRIPT);
        CASE_STRING(VARIANT);
        CASE_STRING(UINT64);
        CASE_STRING(FLOAT64);
        CASE_STRING(UNSIGNED);
        CASE_STRING(UTLSTRINGTOKEN);
        CASE_STRING(QANGLE);
        CASE_STRING(HSCRIPT_LIGHTBINDING);
        CASE_STRING(JS_VALUE);
        CASE_STRING(JS_OBJECT);
        CASE_STRING(JS_ARRAY);
        CASE_STRING(JS_RAW_ARGS);
        default:
            return "UNKNOWN_TYPE_REEEE!";
    }
}

class ScopeFunction
{
public:
    const char *name;
    const char *internalName; // same as above it seems
    const char *description;
    ArgTypes_t returnType;
    uint8_t unkbyte2;
    uint8_t argNum;
    ArgTypes_t argTypes[5];
    void *unk2;
    const char *argNames; // separated by \0's
    void *unk3;
    void *v8WrapperFunc; // maybe a function to get more info?
    void *function; // The actual function
    int _pad;
    int iUnk;
}__attribute__((packed));

class CPanoramaGameScriptScope
{
public:
    const char *name;
    const char *fullName;
    const char *description;
    void *unk;
    uint32_t numFuncs;
    char _pad[4];
    ScopeFunction *funcs;
};

class GameScriptScopesWrapper
{
public:
    CPanoramaGameScriptScope **scopes;
    size_t numScopes;
};