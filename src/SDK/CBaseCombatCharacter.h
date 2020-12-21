#pragma once

#include "CBaseEntity.h"


class CBaseCombatCharacter : public CBaseEntity
{
    virtual bool C_BaseCombatCharacter__AreFootstepsAudible(float unk, bool unk2);
    virtual bool C_BaseCombatCharacter__IsFootstepAudible(float unk, bool unk2);
    virtual float C_BaseCombatCharacter__GetFootstepRunThreshold(void);
    virtual bool C_BasePlayer__IsGhost(void);
};