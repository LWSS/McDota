#pragma once

#include "CBaseEntity.h"
#include "CUtlVector.h"
#include "../Netvars.h"


struct PlayerResourcePlayerTeamData_t
{
    void *unk[2];
    int unk2;
    int heroID; // ex: 48 = luna
    int kills;
    int assists;
    int deaths;
    int streak; // how many kills wo/ dying
    int heroLevel;
    int respawnSeconds; // seconds until respawn. -1 if alive.
    int lastBuybackTime; // last buyback time in seconds since game started
    int entHandle; // I think
    void *_pad[32];
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