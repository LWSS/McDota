#pragma once

struct CSchemaClassBinding {
    CSchemaClassBinding* parent;
    const char* bindingName; // ex: C_World
    const char* dllName; // ex: libclient.so
    const char* libName; // ex: client
};