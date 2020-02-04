#pragma once

#include "CBaseCombatCharacter.h"
#include "../Netvars.h"
/*
..........................,,,,______...........................
.....................*&(***************\(%&(...................
................./&%*************************%%,...............
..............&|*******************************\&(.............
............,&|***********************************(%...........
...........#|***************************************\&,........
...........&******************************************((.......
..........&********************************************(#......
.........#|*********************************************(*.....
.........&***********************************************&.....
........((***********************************************&.....
........#*************************************************&....
........&*************************************************|#...
........&**************************************************&...
........&**************************************************#/..
........&***********************@@@@***************@@@#****&,..
......../#**********************#@@@**********\****@@@@****&...      _______________________
.........%|**********************************#@@***********%/..     |                       |
..........&***********************************@@\***********%..    /      Buy Valve Games!  |
..........,&********&*************************\@@***********(*.   /      ___________________|
...........,&*******%**************************&@#**********(*.  /     /
.............&******&**************************\@@**********&,. /    /
.............,&******@**************************&@#********%,../   /
..............&******&|***************@@@@@@@@@@@@@*******&.../  /
..............&*******#(*********************************&.../ /
..............&********\&|******************************)&,./ /
..............&**********&\********%@@@@@@@@@@@@@@#****&..../..
............./#************\*************************]%........
.............%*******(********(%*********************(.........
............*(*****************\&******************)#..........
...........*%**********************&%************%%*...........
..........*#**************************\/((((@//,//.............
 */


class C_DOTABaseAbility;
// xref "%s_Abilities" to CreateDictionaries() OR "-herorecorder" to ParsePortraitInfo
class CDotaBaseNPC : public CBaseCombatCharacter
{
public:
    inline bool IsIllusion() {
        static uint32_t offset = Netvars::netvars["C_DOTA_BaseNPC_Hero"]["m_hReplicatingOtherHeroModel"]; //credits to hollow @UC
        if( !offset )
            return false;
        uintptr_t handle = *(uintptr_t*)((uintptr_t)this + offset);
        return (handle != 0xffffffff);
    }
    virtual void sub_2B07D70() = 0; // 308
    virtual void sub_2B08240() = 0;
    virtual void sub_2B08940() = 0;
    virtual void sub_290E410() = 0;
    virtual void sub_290E430() = 0;
    virtual void sub_290E450() = 0;
    virtual void sub_290E470() = 0;
    virtual void sub_290E471() = 0;
    virtual void sub_2B42550() = 0;
    virtual void sub_2D38700() = 0;
    virtual void sub_2A99C60() = 0;
    virtual void sub_2CBFE80() = 0;
    virtual float C_DOTA_BaseNPC__GetZChangeSpeed(void) = 0;
    virtual float C_DOTA_BaseNPC__GetBonusFlyHeight(void) = 0; // 320
    virtual bool C_DOTA_BaseNPC__ShouldDoFlyHeightVisual(void) = 0;
    virtual void sub_2ED6660() = 0;
    virtual bool C_DOTA_BaseNPC__IsPortraitEntity(void) = 0;
    virtual int C_DOTA_BaseNPC__GetHealthPercent(void) = 0;
    virtual float C_DOTA_BaseNPC__GetHealthThinkRegen(void) = 0;
    virtual float C_DOTA_BaseNPC__GetMana(void) = 0;
    virtual float C_DOTA_BaseNPC__GetMaxMana(void) = 0;
    virtual float C_DOTA_BaseNPC__GetManaThinkRegen(void) = 0;
    virtual void unk_29ae2c0() = 0;
    virtual void unk_29ae2f0() = 0;
    virtual float C_DOTA_BaseNPC__GetPhysicalArmorBaseValue() = 0;
    virtual void sub_2EAF5C0() = 0;
    virtual void sub_2EAF8A0() = 0;
    virtual void sub_2ED6700() = 0;
    virtual void sub_2EAF460() = 0;
    virtual void sub_2EB0140() = 0;
    virtual void sub_2F67100() = 0;
    virtual void sub_2F673B0() = 0;
    virtual void sub_2EAF550() = 0;
    virtual void sub_2EB6610() = 0;
    virtual void sub_2F67470() = 0;
    virtual float C_DOTA_BaseNPC__GetBaseMagicalResistanceValue(void) = 0;
    virtual float C_DOTA_BaseNPC__IncreasedAttackSpeed() = 0;
    virtual float C_DOTA_BaseNPC__GetBaseMoveSpeed() = 0;
    virtual float C_DOTA_BaseNPC__GetIdealSpeed() = 0;
    virtual void sub_2D10A70() = 0;
    virtual void C_DOTA_BaseNPC__LoadVoiceResources( void const *CEntityPrecacheContext ) = 0;
    virtual void sub_2D15050() = 0;
    virtual bool C_DOTA_BaseNPC__IsValidAbilityToCast( C_DOTABaseAbility *ability ) = 0;
    virtual void sub_27F8410() = 0;
    virtual void loc_2B523C0() = 0;
    virtual void sub_2E9B4A0() = 0;
    virtual void loc_2E978C0() = 0;
    virtual void sub_2E978F0() = 0;
    virtual void sub_2ED6760() = 0;
    virtual void sub_2ED6790() = 0;
    virtual void sub_2E97920() = 0;
    virtual void loc_2ED67E0() = 0;
    virtual void loc_2ED6810() = 0;
    virtual void sub_2ED6850() = 0;
    virtual void sub_2ED6860() = 0;
    virtual void sub_2ED6870() = 0;
    virtual void sub_2ED6890() = 0;
    virtual void sub_2ED6891() = 0;
    virtual void sub_287ADD0() = 0; // added w/ 2020 new bloom extender. returns 0
    virtual bool C_DOTA_BaseNPC__IsDemon(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsRoshan(void) = 0;
    virtual bool C_DOTA_BaseNPC__ShouldForwardPurchaseRequest(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsZombie(void) = 0;
    virtual bool C_DOTA_BaseNPC__CanAcceptTargetToAttack(CBaseEntity* target) = 0;
    virtual void sub_2ED6910() = 0;
    virtual void C_DOTA_BaseNPC__UpdateSelectionRing(void) = 0;
    virtual void C_DOTA_BaseNPC__OverrideSelectionPriority(int priority) = 0;
    virtual void C_DOTA_BaseNPC__UpdateBasedOnDormancy(bool) = 0;
    virtual bool C_DOTA_BaseNPC__CanBeSelected(void) = 0;
    virtual int C_DOTA_BaseNPC__GetEffectiveInvisibilityLevel(void) = 0;
    virtual void C_DOTA_BaseNPC__ComputeTranslucencyType(void) = 0;
    virtual const char* C_DOTA_BaseNPC__GetUnitLabel(void) = 0;
    virtual void loc_2E97990() = 0;
    virtual void sub_2ED6960() = 0;
    virtual void sub_2ED6980() = 0;
    virtual void sub_2EB9C60() = 0;
    virtual CDotaBaseNPC* C_DOTA_BaseNPC__GetChosenTarget(void) = 0;
    virtual int C_DOTA_BaseNPC__GetDamageMin(void) = 0;
    virtual int C_DOTA_BaseNPC__GetDamageMax(void) = 0;
    virtual float C_DOTA_BaseNPC__GetDamageBonus(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsRooted(void) = 0;
    virtual void sub_2ED6A30() = 0;
    virtual void sub_2EDBCA0() = 0;
    virtual bool C_DOTA_BaseNPC__IsDisarmed(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsAttackImmune(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsSilenced(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsMuted(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsStunned(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsHexed(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsInvisible(void) = 0; // not usable on enemies
    virtual bool C_DOTA_BaseNPC__IsInvulnerable(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsMagicImmune(void) = 0;
    virtual bool C_DOTA_BaseNPC__NoUnitCollision(void) = 0;
    virtual bool C_DOTA_BaseNPC__ProvidesVision(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsNightmared(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsEvadeDisabled(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsUnselectable(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsSpeciallyDeniable(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsFrozen(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsCommandRestricted(void) = 0;
    virtual bool C_DOTA_BaseNPC__NotOnMiniMap(void) = 0;
    virtual bool C_DOTA_BaseNPC__NotOnMiniMapForEnemies(void) = 0;
    virtual void sub_2ED6C30() = 0;
    virtual bool C_DOTA_BaseNPC__IsLowAttackPriority(void) = 0;
    virtual bool C_DOTA_BaseNPC__NoHealthBar(void) = 0;
    virtual bool C_DOTA_BaseNPC__NoTeamMoveTo(void) = 0;
    virtual bool C_DOTA_BaseNPC__NoTeamSelect(void) = 0;
    virtual bool C_DOTA_BaseNPC__PassivesDisabled(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsDominated(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsBlind(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsOutOfGame(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsFakeAlly(void) = 0;
    virtual void sub_2D3B320() = 0;
    virtual void sub_2D3B321() = 0;
    virtual void sub_2D3F810() = 0;
    virtual void C_DOTA_BaseNPC__OnStatesAdded(unsigned long long unk) = 0;
    virtual void C_DOTA_BaseNPC__OnStatesRemoved(unsigned long long unk) = 0;
    virtual void C_DOTA_BaseNPC__OnDebuffStateAdded( unsigned int ) = 0;
    virtual void C_DOTA_BaseNPC__OnDebuffStateRemoved( unsigned int ) = 0;
    virtual bool C_DOTA_BaseNPC__HasMovementCapability(void) = 0;
    virtual bool C_DOTA_BaseNPC__HasFlyingVision(void) = 0;
    virtual bool C_DOTA_BaseNPC__IsFlyingVisually(void) = 0;
    virtual void sub_2D3B770() = 0;
    virtual void C_DOTA_BaseNPC__CalculateActivityModifiers(int) = 0;
    virtual bool C_DOTA_BaseNPC__IsInventoryEnabled(void) = 0;
    virtual void C_DOTA_BaseNPC__GetSoundSet(void) = 0;
    virtual void C_DOTA_BaseNPC__GetSelectionGroup(void) = 0;
    virtual void C_DOTA_BaseNPC__GainedModifier(void* CDOTA_Buff) = 0;
    virtual void C_DOTA_BaseNPC__LostModifier(void* CDOTA_Buff) = 0;
    virtual bool C_DOTA_BaseNPC__IsIllusion(void) = 0; // not usable on enemies
    virtual void sub_2EDC3A0() = 0;
    virtual bool C_DOTA_BaseNPC__UnitStatsNeedsRefresh() = 0;
    virtual void sub_2D3F930() = 0;
    virtual int C_DOTA_BaseNPC__GetSpeechPitchLevel(void) = 0;
    virtual bool C_DOTA_BaseNPC__ShouldTranslateResponse(void) = 0;
    virtual bool C_DOTA_BaseNPC__CanSpeak(int unk) = 0;
    virtual bool C_DOTA_BaseNPC__UsesCustomSpeechOperatorStack(void) = 0;
    virtual void sub_2D10110() = 0;
    virtual void sub_2D0EF60() = 0;
    virtual void sub_2D100C0() = 0;
    virtual void sub_2D13940() = 0;
    virtual void sub_2D139A0() = 0;
    virtual void sub_2D3B7F0() = 0;
    virtual void sub_2D13A10() = 0;
    virtual void sub_2D3B490() = 0;
    virtual void sub_2ED6EF0() = 0;
    virtual bool C_DOTA_BaseNPC__ShouldPerformLean(void) = 0;
    virtual void C_DOTA_BaseNPC__UsesConstantGesture(bool) = 0;
    virtual void C_DOTA_BaseNPC__GetConstantGestureWeight() = 0;
    virtual void C_DOTA_BaseNPC__GetConstantGestureCycle() = 0;
    virtual void C_DOTA_BaseNPC__GestureCycleComplete() = 0;
    virtual void C_DOTA_BaseNPC__ParsePortraitInfo(void *KeyValues) = 0;
    virtual CDotaPlayer* C_DOTA_BaseNPC__GetPlayerOwner(void) = 0;
    virtual int C_DOTA_BaseNPC__GetPlayerOwnerID(void) = 0;
    virtual bool C_DOTA_BaseNPC__HasModifiedAbilityParticleName(const char* abilityMaybe) = 0;
    virtual const char* C_DOTA_BaseNPC__GetModifiedAbilityParticleName(const char* abilityMaybe) = 0;
    virtual const char*  C_DOTA_BaseNPC__GetVoiceFile(void) = 0;
    virtual ColorRGBA C_DOTA_BaseNPC__GetUnitColor(void) = 0;
    virtual void C_DOTA_BaseNPC__GetAbilityLayout(void) = 0;
    virtual void C_DOTA_BaseNPC_Hero__IsModelIndexOriginalModel() = 0;
    virtual void C_DOTA_BaseNPC__UpdateAttributesForArcanaLevel() = 0;
    virtual void C_DOTA_BaseNPC__ApplyAdditionalPortraitParticles() = 0;
    virtual void sub_2D0FFE0() = 0;
    virtual void sub_2D0FFF0() = 0;
    virtual void C_DOTA_BaseNPC__BuildAttachedParticleFilter() = 0;
    virtual void sub_2D156C0() = 0;
    virtual void sub_2DE04E0() = 0;
    virtual void C_DOTA_BaseNPC__UpdateNonCacheableWearableData() = 0;
    virtual void C_DOTA_BaseNPC_Hero__CreateDictionaries() = 0;
    virtual void C_DOTA_BaseNPC_Hero__PopulateDictionaries() = 0;
    virtual void C_DOTA_BaseNPC__SharedLoadNPCData() = 0;
    virtual void C_DOTA_BaseNPC__ComputeOverriddenGeneratingItem() = 0;

    /*
    virtual void sub_2D3B580() = 0;
    virtual void C_DOTA_BaseNPC_Hero__NotifyResourceStatusChange() = 0;
    virtual float C_DOTA_BaseNPC_Hero__GetHeroSpecialStrength(void) = 0;
    virtual float C_DOTA_BaseNPC_Hero__GetHeroSpecialAgility(void) = 0;
    virtual float C_DOTA_BaseNPC_Hero__GetHeroSpecialIntellect(void) = 0;
    virtual int C_DOTA_BaseNPC_Hero__GetGold(void) = 0;
    virtual void sub_2D391B0() = 0;
    virtual bool C_DOTA_BaseNPC_Hero__SetupBones(matrix3x4_t *pBoneToWorldOut, int maxBones, float boneMask, float currentTime) = 0;
    virtual void sub_2FA8B50() = 0;
    virtual void C_DOTA_BaseNPC_Hero__PostModelCombinerParticleUpdate() = 0;
    virtual void C_DOTA_BaseNPC_Hero__ModelCombineFinished() = 0;
    virtual void C_DOTA_BaseNPC_Hero__ModelCombineAbort() = 0;
    */
};