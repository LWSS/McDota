#include "memoverride.h"

void * operator new(size_t size)
{
    void * p = g_pMemAlloc->Alloc(size);
    return p;
}

void operator delete(void * p)
{
    g_pMemAlloc->Free(p);
}

void operator delete(void*p, std::size_t size)
{
    g_pMemAlloc->Free(p);
}
