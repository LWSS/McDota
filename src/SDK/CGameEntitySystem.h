#pragma once

#include "CBaseEntity.h"
#include "ConMsg.h"

#define MAX_ENTITIES_IN_LIST 512
#define MAX_ENTITY_LISTS 64
#define MAX_TOTAL_ENTITIES MAX_ENTITIES_IN_LIST * MAX_ENTITY_LISTS


inline uint32_t highestEntIndexOffset;

class CEntityIdentity {

public:
    CBaseEntity *entity;
    void *dunno;
    int unk;
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
    CBaseEntity* GetBaseEntity( int index )
    {
        if ( index <= -1 || index >= MAX_TOTAL_ENTITIES )
            return nullptr;

        int listToUse = (index / MAX_ENTITIES_IN_LIST);
        if( !m_pEntityList[listToUse] ){
            ConMsg("Tried to Use an EntityList does that not exist yet! List #%d", listToUse);
            return nullptr;
        }
        if( m_pEntityList[listToUse]->m_pIdentities[index % MAX_ENTITIES_IN_LIST].entity ){
            return m_pEntityList[listToUse]->m_pIdentities[index % MAX_ENTITIES_IN_LIST].entity;
        } else {
            return nullptr;
        }
    }

    int GetHighestEntityIndex()
    {
        return *(int*)((uintptr_t)this + highestEntIndexOffset);
    }

    void* unk;
    void* unk2;
    void* unk3;
    CEntityIdentities* m_pEntityList[MAX_ENTITY_LISTS];
};