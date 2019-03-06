#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>

namespace Netvars
{
    void DumpNetvars(const char *fileName);
    void CacheNetvars();

    inline std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> netvars;
}