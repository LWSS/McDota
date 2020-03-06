#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>

#include "SDK/CSource2Client.h"

namespace Netvars
{
    void DumpNetvars( CSource2Client *clientInterface, const char *fileName );
    void CacheNetvars( CSource2Client *client );

    inline std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> netvars;
}