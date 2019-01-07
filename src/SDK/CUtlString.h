#pragma once

#include "CUtlMemory.h"

class CUtlString
{
public:

    const char* Get()
    {
        return reinterpret_cast<const char*>( m_Memory.m_pMemory );
    }

    CUtlMemory<uint8_t> m_Memory;
    int m_nActualLength;
};