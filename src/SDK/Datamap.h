#pragma once

typedef enum _fieldtypes : uint64_t
{
    FIELD_VOID = 0,			// No type or value
    FIELD_FLOAT,			// Any floating point value
    FIELD_STRING,			// A string ID (return from ALLOC_STRING)
    FIELD_VECTOR,			// Any vector, QAngle, or AngularImpulse
    FIELD_QUATERNION,		// A quaternion
    FIELD_INTEGER,			// Any integer or enum
    FIELD_BOOLEAN,			// boolean, implemented as an int, I may use this as a hint for compression
    FIELD_SHORT,			// 2 byte integer
    FIELD_CHARACTER,		// a byte
    FIELD_COLOR32,
    FIELD_EMBEDDED,			// an embedded object with a datadesc, recursively traverse and embedded class/structure based on an additional typedescription
    FIELD_CUSTOM,

    FIELD_CLASSPTR   = 0x0C,
    FIELD_EHANDLE    = 0x0D,

    FIELD_POSITION_VECTOR  = 0x0E,
    FIELD_TIME       = 0x0F,
    FIELD_TICK       = 0x10,
    FIELD_SOUNDNAME  = 0x11,

    FIELD_INPUT      = 0x12,
    FIELD_FUNCTION   = 0x13,

    FIELD_VMATRIX    = 0x14,

    FIELD_VMATRIX_WORLDSPACE  = 0x15,
    FIELD_MATRIX3X4_WORLDSPACE  = 0x16,

    FIELD_INTERVAL   = 0x17,
    FIELD_UNUSED     = 0x18,
    FIELD_VECTOR2D   = 0x19,
    FIELD_INTEGER64  = 0x1A,
    FIELD_VECTOR4D   = 0x1B,
    FIELD_RESOURCE   = 0x1C,
    FIELD_TYPEUNKNOWN  = 0x1D,
    FIELD_CSTRING    = 0x1E,
    FIELD_HSCRIPT    = 0x1F,
    FIELD_VARIANT    = 0x20,
    FIELD_UINT64     = 0x21,
    FIELD_FLOAT64    = 0x22,
    FIELD_POSITIVEINTEGER_OR_NULL  = 0x23,
    FIELD_HSCRIPT_NEW_INSTANCE  = 0x24,
    FIELD_UINT       = 0x25,
    FIELD_UTLSTRINGTOKEN  = 0x26,
    FIELD_QANGLE     = 0x27,
    FIELD_NETWORK_ORIGIN_CELL_QUANTIZED_VECTOR  = 0x28,
    FIELD_HMATERIAL  = 0x29,
    FIELD_HMODEL     = 0x2A,
    FIELD_NETWORK_QUANTIZED_VECTOR  = 0x2B,
    FIELD_NETWORK_QUANTIZED_FLOAT  = 0x2C,
    FIELD_DIRECTION_VECTOR_WORLDSPACE  = 0x2D,
    FIELD_QANGLE_WORLDSPACE  = 0x2E,
    FIELD_QUATERNION_WORLDSPACE  = 0x2F,
    FIELD_HSCRIPT_LIGHTBINDING  = 0x30,

    FIELD_V8_VALUE   = 0x31,
    FIELD_V8_OBJECT  = 0x32,
    FIELD_V8_ARRAY   = 0x33,
    FIELD_V8_CALLBACK_INFO  = 0x34,

    FIELD_UTLSTRING  = 0x35,
    FIELD_NETWORK_ORIGIN_CELL_QUANTIZED_POSITION_VECTOR  = 0x36,
    FIELD_HRENDERTEXTURE  = 0x37,
    FIELD_TYPECOUNT  = 0x38,
} fieldtype_t;

enum
{
    TD_OFFSET_NORMAL = 0,
    TD_OFFSET_PACKED = 1,

    // Must be last
    TD_OFFSET_COUNT,
};

class TypeDescription;

class Datamap
{
public:
    TypeDescription *dataDesc;
    uint64_t numFields;
    const char *className; // Ex: C_DOTAPlayer
    Datamap *baseMap; // Ex: For C_DOTAPlayer it would be next baseclass C_BasePlayer, can be NULL
};

class TypeDescription
{
public:
    fieldtype_t type;
    const char *fieldName;
    int fieldOffset[TD_OFFSET_COUNT];
    void *_unk[5];
    Datamap * td;
    void *_unk2[5];
};

