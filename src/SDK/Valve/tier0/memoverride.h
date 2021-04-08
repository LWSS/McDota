#pragma once

#include <cstddef>

class IMemAlloc
{
public:
    virtual void *Alloc( unsigned long size ) = 0;
    virtual void *Realloc( const void *pMem, unsigned long size ) = 0;
    virtual void Free( const void *pMem ) = 0;
    virtual void sub_466F0() = 0;
    virtual void sub_465B0() = 0;
    virtual void sub_457C0() = 0;
    virtual void sub_46510() = 0;
    virtual void sub_463B0() = 0;
    virtual void sub_457E0() = 0;
    virtual void sub_46310() = 0;
    virtual void sub_45880() = 0;
    virtual void sub_45000() = 0;
    virtual void sub_45010() = 0;
    virtual void sub_45020() = 0;
    virtual void sub_45030() = 0;
    virtual void sub_458C0() = 0;
    virtual void sub_45040() = 0;
    virtual void sub_45050() = 0;
    virtual void sub_45060() = 0;
    virtual void sub_45070() = 0;
    virtual void sub_45080() = 0;
    virtual size_t GetSize( const void *pMem ) = 0;
};

// Resolved at runtime in tier0
extern "C" IMemAlloc *g_pMemAlloc;

// Should override for all of McDota
void * operator new(size_t size);
void operator delete(void * p);
void operator delete(void*p, std::size_t size);