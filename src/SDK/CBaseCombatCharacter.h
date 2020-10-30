#pragma once

#include "CBaseEntity.h"


class CBaseCombatCharacter : public CBaseEntity
{
    virtual bool C_BaseCombatCharacter__AreFootstepsAudible(float unk, bool unk2);
    virtual bool C_BaseCombatCharacter__IsFootstepAudible(float unk, bool unk2);
    virtual float C_BaseCombatCharacter__GetFootstepRunThreshold(void);
    virtual bool C_BasePlayer__IsGhost(void);
    virtual void C_BaseCombatCharacter__UpdateParticles(void);
    virtual void C_BaseCombatCharacter__Weapon_OwnsThisType(const char*, int);
    virtual void C_BaseCombatCharacter__Weapon_GetSlot(const char*, int);
    virtual void C_BasePlayer__Weapon_Switch(void* C_BaseCombatWeapon, int);
    virtual void C_BaseCombatCharacter__GetActiveWeapon() = 0;
    virtual void sub_2863F20();
    virtual void sub_2DC6130();
    virtual void sub_2A5D600();
    virtual void sub_2A5D650(); // 314
};