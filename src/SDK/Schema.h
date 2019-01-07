#pragma once

struct CSchemaClassBinding {
    CSchemaClassBinding* parent; // I THINK
    const char* bindingName; // ex: C_World
    const char* dllName; // ex: libclient.so
    const char* libName; // ex: client
};