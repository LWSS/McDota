#pragma once
#include "IAppSystem.h"
#include "CDotaPlayer.h"

class CBaseEngineService : IAppSystem
{
public:
    virtual void GetServiceDependencies(); // 11
    virtual const char* GetName();
    virtual bool ShouldActivate();
    virtual void OnLoopActivate();
    virtual void OnLoopDeactivate();
    virtual bool IsActive();
    virtual void SetActive(bool active);
    virtual void SetName(const char* name);
    virtual void RegisterEventMap();
    virtual int GetServiceIndex(); // 20
    virtual void SetServiceIndex(int index); // 21
};

// "OnEngineSplitscreenClientAdded" to AddSplitScreenUser
class CSplitScreenService : CBaseEngineService
{
public:
    virtual void Destroy() = 0; // 22
    virtual void Destroy2()= 0;
    virtual void AddSplitScreenUser(int splitScreenSlot, void* SplitScreenClient_t) = 0; // 24
    virtual void AddBaseUser(int splitScreenSlot, void* SplitScreenClient_t)= 0;
    virtual void RemoveSplitScreenUser(int splitScreenSlot)= 0;
    virtual int GetActiveSplitScreenPlayerSlot(void)= 0;
    virtual void SetActiveSplitScreenPlayerSlot(int splitScreenSlot)= 0;
    virtual bool IsValidSplitScreenSlot(int splitScreenSlot)= 0;
    virtual int FirstValidSplitScreenSlot(void)= 0;
    virtual int NextValidSplitScreenSlot(int splitScreenSlot)= 0;
    virtual int GetNumSplitScreenPlayers(void)= 0;
    virtual int GetSplitScreenPlayerEntity(int splitScreenSlot)= 0;
    virtual void* GetSplitScreenPlayerNetChan(int splitScreenSlot)= 0;
    virtual bool IsDisconnecting(int splitScreenSlot)= 0;
    virtual void SetDisconnecting(int splitScreenSlot, bool disconnecting)= 0;
    virtual void SetLocalPlayerIsResolvable(const char* unk, int unk2, bool resolvable)= 0;
    virtual bool IsLocalPlayerResolvable(void)= 0;
    virtual int GetMaxSplitScreenPlayers(void)= 0;
    virtual bool IsSplitScreenPlayerEntity(int entIndex)= 0;
    virtual int FindSplitPlayerSlot(int entIndex)= 0;
    virtual void ReadSomethingFromSteamCloud()= 0;
    virtual void WriteSomethingToSteamCloud()= 0;
    virtual void GenerateSomeUserConfigurationFile()= 0;
    virtual void EmptyFunc()= 0;
    virtual void EmptyFunc2()= 0;
};