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
    virtual void Destroy(); // 22
    virtual void Destroy2();
    virtual void AddSplitScreenUser(int splitScreenSlot, void* SplitScreenClient_t); // 24
    virtual void AddBaseUser(int splitScreenSlot, void* SplitScreenClient_t);
    virtual void RemoveSplitScreenUser(int splitScreenSlot);
    virtual int GetActiveSplitScreenPlayerSlot(void);
    virtual void SetActiveSplitScreenPlayerSlot(int splitScreenSlot);
    virtual bool IsValidSplitScreenSlot(int splitScreenSlot);
    virtual int FirstValidSplitScreenSlot(void);
    virtual int NextValidSplitScreenSlot(int splitScreenSlot);
    virtual int  GetNumSplitScreenPlayers(void);
    virtual int GetSplitScreenPlayerEntity(int splitScreenSlot);
    virtual void* GetSplitScreenPlayerNetChan(int splitScreenSlot);
    virtual bool IsDisconnecting(int splitScreenSlot);
    virtual void SetDisconnecting(int splitScreenSlot, bool disconnecting);
    virtual void SetLocalPlayerIsResolvable(const char* unk, int unk2, bool resolvable);
    virtual bool IsLocalPlayerResolvable(void);
    virtual int GetMaxSplitScreenPlayers(void);
    virtual bool IsSplitScreenPlayerEntity(int entIndex);
    virtual int FindSplitPlayerSlot(int entIndex);
    virtual void ReadSomethingFromSteamCloud();
    virtual void WriteSomethingFromSteamCloud();
    virtual void GenerateSomeUserConfigurationFile();
    virtual void EmptyFunc();
};