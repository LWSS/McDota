#pragma once

#include "CBaseEntity.h"
#include "CUtlVector.h"
#include "../Netvars.h"

struct PlayerResourcePlayerTeamData_t
{
    void *vtable;
    void *SmartPointer_pChainEntity;
    ChangeAccessorFieldPathIndex_t m_PathIndex;
    char _pad[2];
    int m_nSelectedHeroID; // ex: 48 = luna
    int m_iKills;
    int m_iAssists;
    int m_iDeaths;
    int m_iStreak; // how many kills wo/ dying
    int m_iLevel;
    int m_iRespawnSeconds; // seconds until respawn. -1 if alive.
    int m_iLastBuybackTime; // last buyback time in seconds since game started
    int m_hSelectedHero;
    void *_pad2[32];
};

class CDOTAPlayerResource : CBaseEntity
{
public:
    CUtlVector< PlayerResourcePlayerTeamData_t > * GetPlayerTeamData( ){
        static uint32_t offset = Netvars::netvars["C_DOTA_PlayerResource"]["m_vecPlayerTeamData"];
        if( !offset )
            return nullptr;
        return reinterpret_cast<CUtlVector< PlayerResourcePlayerTeamData_t > *>( ( uintptr_t(this) + offset ) );
    }
};