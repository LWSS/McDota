#pragma once


namespace Netvars
{
    void DumpNetvars(const char *fileName);

    unsigned int GetNetvar(const char *className, const char *netvarName);
}