#pragma once

#include "CBaseEntity.h"

#define MAX_ENTITIES_IN_LIST 512
#define MAX_ENTITY_LISTS 64 // 0x3F
#define MAX_TOTAL_ENTITIES MAX_ENTITIES_IN_LIST * MAX_ENTITY_LISTS // 0x8000

#define LOWORD(a) ((uint16_t)(a))
#define HIWORD(a) ((uint16_t)(((uint32_t)(a) >> 16) & 0xFFFF))

inline uint32_t highestEntIndexOffset;

class CEntityIdentity {

public:
    CBaseEntity *entity;
    void *dunno;
    int entHandle; // LOWORD(handle) & 0x7FFF = entID
    int unk2; // always seems to be -1
    const char* internalName; // these two strings are optional!
    const char* entityName; // ex: item_tpscroll
    void *unkChunk[5];
    CEntityIdentity *prevValid;
    CEntityIdentity *nextValid;
    void *unkptr;
    void *unkptr2;
    void *unkptr3;
};

class CEntityIdentities
{
public:
    CEntityIdentity m_pIdentities[MAX_ENTITIES_IN_LIST];
};

class CGameEntitySystem
{
public:
    // rebuilt from CGameEntitySystem::GetBaseEntity()
    CBaseEntity* GetBaseEntity( int index )
    {
        if ( index <= -1 || index >= ( MAX_TOTAL_ENTITIES - 1 ) )
            return nullptr;

        CEntityIdentities *chunkToUse = m_pIdentityChunks[(index / MAX_ENTITIES_IN_LIST)]; // equal to ( index >> 9 )

        if( !chunkToUse )
            return nullptr;

        CEntityIdentity *identity = &chunkToUse->m_pIdentities[ index % MAX_ENTITIES_IN_LIST ]; // equal to ( index & 1FF )

        if( !identity )
            return nullptr;

        // This is an extra check in the official implementation that I am omitting for speed
        //if( (LOWORD( identity->entHandle ) & 0x7FFF) == index ){
        //    return identity->entity;
        //}

        return identity->entity;
    }

    unsigned int GetEntHandle( int index )
    {
        if ( index <= -1 || index >= ( MAX_TOTAL_ENTITIES - 1 ) )
            return -1;

        CEntityIdentities *chunkToUse = m_pIdentityChunks[(index / MAX_ENTITIES_IN_LIST)]; // equal to ( index >> 9 )

        if( !chunkToUse )
            return -1;

        CEntityIdentity *identity = &chunkToUse->m_pIdentities[ index % MAX_ENTITIES_IN_LIST ]; // equal to ( index & 1FF )

        if( !identity )
            return -1;

        return identity->entHandle;
    }

    int GetHighestEntityIndex()
    {
        return *(int*)((uintptr_t)this + highestEntIndexOffset);
    }

    void* unk;
    void* unk2;
    CEntityIdentities* m_pIdentityChunks[MAX_ENTITY_LISTS];
};