#pragma once

#include "CDotaBaseNPC.h"

enum class DotaUnitOrder_t : int {
    DOTA_UNIT_ORDER_NONE = 0,
    DOTA_UNIT_ORDER_MOVE_TO_POSITION = 1,
    DOTA_UNIT_ORDER_MOVE_TO_TARGET = 2,
    DOTA_UNIT_ORDER_ATTACK_MOVE = 3,
    DOTA_UNIT_ORDER_ATTACK_TARGET = 4,
    DOTA_UNIT_ORDER_CAST_POSITION = 5,
    DOTA_UNIT_ORDER_CAST_TARGET = 6,
    DOTA_UNIT_ORDER_CAST_TARGET_TREE = 7,
    DOTA_UNIT_ORDER_CAST_NO_TARGET = 8,
    DOTA_UNIT_ORDER_CAST_TOGGLE = 9,
    DOTA_UNIT_ORDER_HOLD_POSITION = 10,
    DOTA_UNIT_ORDER_TRAIN_ABILITY = 11,
    DOTA_UNIT_ORDER_DROP_ITEM = 12,
    DOTA_UNIT_ORDER_GIVE_ITEM = 13,
    DOTA_UNIT_ORDER_PICKUP_ITEM = 14,
    DOTA_UNIT_ORDER_PICKUP_RUNE = 15,
    DOTA_UNIT_ORDER_PURCHASE_ITEM = 16,
    DOTA_UNIT_ORDER_SELL_ITEM = 17,
    DOTA_UNIT_ORDER_DISASSEMBLE_ITEM = 18,
    DOTA_UNIT_ORDER_MOVE_ITEM = 19,
    DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO = 20,
    DOTA_UNIT_ORDER_STOP = 21,
    DOTA_UNIT_ORDER_TAUNT = 22,
    DOTA_UNIT_ORDER_BUYBACK = 23,
    DOTA_UNIT_ORDER_GLYPH = 24,
    DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH = 25,
    DOTA_UNIT_ORDER_CAST_RUNE = 26,
    DOTA_UNIT_ORDER_PING_ABILITY = 27,
    DOTA_UNIT_ORDER_MOVE_TO_DIRECTION = 28,
    DOTA_UNIT_ORDER_PATROL = 29,
    DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION = 30,
    DOTA_UNIT_ORDER_RADAR = 31,
    DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK = 32,
    DOTA_UNIT_ORDER_CONTINUE = 33,
    DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED = 34,
    DOTA_UNIT_ORDER_CAST_RIVER_PAINT = 35,
    DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT = 36,
};
enum PlayerOrderIssuer_t : int {
    DOTA_ORDER_ISSUER_SELECTED_UNITS = 0,
    DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY = 1,
    DOTA_ORDER_ISSUER_HERO_ONLY = 2,
    DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY = 3
};
enum OrderQueueBehavior_t : int {
    DOTA_ORDER_QUEUE_DEFAULT = 0,
    DOTA_ORDER_QUEUE_NEVER = 1,
    DOTA_ORDER_QUEUE_ALWAYS = 2,
};

// find SetPlayerUnderwater with "Player.AmbientUnderWater"
class CDotaPlayer : public CBaseCombatCharacter
{
public:
    virtual void sub_2A5EB10(); // 315
    virtual void sub_2A5EB12();
    virtual void sub_2A5EB13();
    virtual void sub_2A5EB14();
    virtual void sub_2A5F750();
    virtual void sub_285FCF0();
    virtual void C_BasePlayer__OnBecomeLocalPlayer(void);
    virtual void unk_newEmptyFunc(); // added with summer scrub pt2
    virtual void C_BasePlayer__CalcView(Vector &eyeOrigin, QAngle &eyeAngles, float &zNear, float &zFar, float &fov);
    virtual void C_BasePlayer__CalcViewModelView(const Vector& eyeOrigin, const QAngle& eyeAngles);
    virtual void C_BasePlayer__CalcRoll(const QAngle& angles, const Vector& velocity, float rollangle, float rollspeed);
    virtual bool C_BasePlayer__IsInThirdPersonView(void);
    virtual void C_BasePlayer__SetPlayerUnderwater(bool underwater);
    virtual void sub_2A5DCC0();
    virtual void sub_2A5DCA0();
    virtual void sub_2A5DD70();
    virtual bool C_BasePlayer__Weapon_CanUse(void* C_BaseCombatWeapon);
    virtual void C_BasePlayer__Weapon_DropPrimary(void);
    virtual void C_DOTAPlayer__SendMove(int unk);
    virtual void unk_EmptyFunc(); // added with summer scrub pt2
    virtual void* C_BasePlayer__FindUseEntity(float unk, float unk2, float unk3, bool *unk4, bool unk5);
    virtual bool C_BasePlayer__IsUsableEntity(void* C_BaseEntity, unsigned int unk);
    virtual void sub_28646E0();
    virtual int CDOTAPlayer__GetObserverMode(void); // realunderwater+20
    virtual void* C_BasePlayer__GetObserverTarget(void);
    virtual bool C_BasePlayer__IsBot(void);
    virtual void C_BasePlayer__TeamChange(DOTATeam_t team);
    virtual const char* C_BasePlayer__GetFlashlightTextureName(void);
    virtual float C_BasePlayer__GetFlashlightFOV(void);
    virtual float C_BasePlayer__GetFlashlightFarZ(void);
    virtual void C_BasePlayer__GetFlashlightLinearAtten(void);
    virtual bool C_BasePlayer__CastsFlashlightShadows(void);
    virtual Vector* C_BasePlayer__GetFlashlightOffset(void); //realunderwater+30
    virtual bool C_BasePlayer__IsAllowedToSwitchWeapons(void);
    virtual void unknown(); // added around 5/13/18. Returns 0 by default.
    virtual void*C_BasePlayer__GetRenderedWeaponModel(void);
    virtual bool C_BasePlayer__IsOverridingViewModel(void);
    virtual void C_BasePlayer__ThirdPersonSwitch(bool thirdperson);
    virtual void sub_2CAF2C0(); // added mid-july 2018. Possibly related to CViewAngleAnimation::RunAnimation
    virtual int C_DOTAPlayer__GetPlayerID(void);
    virtual bool C_BasePlayer__CanSetSoundMixer(void); //comp2
    virtual void C_BasePlayer__PlayerSolidMask(bool unk); // 83011h
    virtual void C_BasePlayer__PreThink(void);
    virtual void C_BasePlayer__PostThink(void);
    virtual void C_BasePlayer__ItemPreFrame(void);
    virtual void C_BasePlayer__ItemPostFrame(void);
    virtual void C_BasePlayer__AbortReload(void);
    virtual void C_BasePlayer__SelectLastItem(void);
    virtual void C_BasePlayer__Weapon_SetLast(void* C_BaseCombatWeapon);
    virtual bool C_BasePlayer__Weapon_ShouldSetLast(void* C_BaseCombatWeapon, void* C_BaseCombatWeapon2);
    virtual bool C_BasePlayer__Weapon_ShouldSelectItem(void* C_BaseCombatWeapon);
    virtual void* C_BasePlayer__GetLastWeapon(void);
    virtual void* C_BasePlayer__SelectItem(const char* name, int unk);
    virtual void* C_BasePlayer__SelectItem(void* C_BaseCombatWeapon);
    virtual void C_BasePlayer__UpdateClientData(void);
    virtual float C_DOTAPlayer__GetFOV(void);
    virtual float C_DOTAPlayer__GetDefaultFOV(void);
    virtual bool C_BasePlayer__IsZoomed(void);
    virtual float C_DOTAPlayer__GetNearZ(void);
    virtual float C_DOTAPlayer__GetFarZ(void); //floatZero
    virtual void ViewPunch( const QAngle& out );
    virtual void sub_2C8F980(); // added late June 2018, takes 2 args, sets them in class.
    virtual void C_BasePlayer__OverrideView(void* CViewSetup);
    virtual Vector* C_BasePlayer__GetPlayerMins(void);
    virtual Vector* C_BasePlayer__GetPlayerMaxs(void);
    virtual ColorRGBA C_DOTAPlayer__GetPlayerColor(void);
    virtual CBaseEntity* C_BasePlayer__GetUseEntity(void);
    virtual CBaseEntity* C_BasePlayer__GetHeldEntity(void);
    virtual void C_BasePlayer__SetAnimation(int PLAYER_ANIM);
    virtual QAngle* C_BasePlayer__GetPunchAngle(void);
    virtual bool sub_2AF93E0(); // added after ti8 - returns 1 by default.
    virtual float C_BasePlayer__GetMinFOV(void);
    virtual void C_BasePlayer__UpdateStepSound(void* CPhysSurfaceProperties, const Vector &pos, const Vector &unk);
    virtual void C_BasePlayer__PlayStepSound(Vector &pos, void* CPhysSurfaceProperties, float unk, bool unk2);
    virtual void C_BasePlayer__GetFootstepSurface(const Vector &pos, const char* unk); // RegisterStringToken0
    virtual void C_BasePlayer__GetStepSoundVelocities(float *outSpeedX, float *outSpeedY);
    virtual void C_BasePlayer__OnAchievementAchieved(int iAchievement);
    virtual void sub_2AF9440(); // added after ti8
    virtual void sub_2AF9450(); // ^^
    virtual void sub_2860060();
    virtual void sub_2F8BA00(); // added with battlepass 2020
    virtual void C_BasePlayer__CalcPlayerView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
    virtual int loc_2DCC4F0(); //diretide 2020 - returns 0
    virtual float sub_2C339B0(); //diretide 2020 - returns a float from inside.
    virtual void C_DOTAPlayer__CalcObserverView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov); //switch: 7 cases
    virtual void C_BasePlayer__GetChaseCamViewOffset(void *targetC_BaseEntity );
    virtual void C_BasePlayer__CalcChaseCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
    virtual void C_BasePlayer__CalcInEyeCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
    virtual void C_BasePlayer__CalcDeathCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
    virtual void C_BasePlayer__CalcRoamingView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
    virtual void C_BasePlayer__CalcFreezeCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
    virtual void C_BasePlayer__SetLocalViewAngles(const QAngle &viewAngles);
    virtual void C_BasePlayer__SetViewAngles(const QAngle& ang);
    virtual bool C_BasePlayer__IsDucked(void);
    virtual bool C_BasePlayer__IsDucking(void);
    virtual float C_BasePlayer__GetFallVelocity(void);
    virtual CBaseEntity* C_BasePlayer__FindEntityClassForward(char* className);// Return C_BaseEntity*
    virtual CBaseEntity* C_BasePlayer__FindEntityForward(bool fHull);          // ^^
    virtual CBaseEntity* C_BasePlayer__FindPickerEntityClass(char* className); // ^^
    virtual CBaseEntity* C_BasePlayer__FindPickerEntity(void);                 // ^^
    virtual void C_BasePlayer__FindEntityInheritingFromForward(void* CSchemaClassBindingBase);
    virtual void C_DOTAPlayer__FindPickerEntityInheritingFrom(void* CSchemaClassBindingBase);
    virtual void C_DOTAPlayer__ProcessMouseclick(ButtonCode_t button, bool unk, bool unk2);
    /* Valve made this non-virtual jan 2020 :^) */
    //virtual void C_DotaPlayer__PrepareUnitOrders(DotaUnitOrder_t order, int entHandle, Vector movePosition, int abilityIndex,PlayerOrderIssuer_t orderIssuer, CDotaBaseNPC* entity, OrderQueueBehavior_t queueBehavior, bool showEffects);
    virtual void* C_DOTAPlayer__GetValidCursor(void);
    virtual bool C_DOTAPlayer__ShouldRegenerateOriginFromCellBits(void);
};