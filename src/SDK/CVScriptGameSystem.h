#pragma once

typedef unsigned long long HSCRIPT ; // looks to be used for script scope.
class CVScriptGameSystem
{
public:
    virtual void IGameSystem__Init(void) = 0;
	virtual void IGameSystem__PostInit(void) = 0;
	virtual void IGameSystem__Shutdown(void) = 0;
	virtual void CVScriptGameSystem__GameInit(void* const EventGameInit_t) = 0;
	virtual void CVScriptGameSystem__GameShutdown(void* const EventGameShutdown_t) = 0;
	virtual void sub_27924A0() = 0;// All these functions are empty void functions.
	virtual void sub_27924B0() = 0;// they aren't that great
	virtual void sub_285D370() = 0;
	virtual void sub_27924D0() = 0;
	virtual void sub_27924E0() = 0;
	virtual void sub_27924F0() = 0;
	virtual void sub_2792500() = 0;
	virtual void sub_2792510() = 0;
	virtual void sub_2792520() = 0;
	virtual void sub_2792530() = 0;
	virtual void sub_2792540() = 0;
	virtual void sub_2792550() = 0;
	virtual void sub_2792560() = 0;
	virtual void sub_2792570() = 0;
	virtual void sub_2792580() = 0;
	virtual void sub_2792590() = 0;
	virtual void sub_27925A0() = 0;
	virtual void sub_27925B0() = 0;
	virtual void sub_27925C0() = 0;
	virtual void sub_27925D0() = 0;
	virtual void sub_27925E0() = 0;
	virtual void sub_27925F0() = 0;
	virtual void OnServerGamePostSimulate(void* EventServerGamePostSimulate_t) = 0;
	virtual void OnClientGamePostSimulate(void* EventClientGamePostSimulate_t) = 0;
	virtual void FrameBoundary(void* EventGameFrameBoundary_t) = 0;
	virtual void OutOfGameFrameBoundary(void* EventOutOfGameFrameBoundary_t) = 0;
	virtual void SaveGame(void* EventSaveGame_t) = 0;
	virtual void RestoreGame(void* EventRestoreGame_t) = 0;
	virtual const char* GetName(void) = 0;
	virtual void SetGameSystemGlobalPtrs(void* addr) = 0;
	virtual void SetName(const char* name) = 0;
	virtual bool DoesGameSystemReallocate(void) = 0;
	virtual void Destroy1() = 0;
	virtual void Destroy2() = 0;
	virtual void YouForgot_DECLARE_GAME_SYSTEM_InYourClassDefinition() = 0;
	virtual void VScriptInit(void) = 0;
	virtual void VScriptTerm(void) = 0;
	virtual bool IsVScriptInitialized(void) = 0;
	virtual bool IsEntityCreationAllowedInScripts(void) = 0;
	virtual void* GetVM(void) = 0;
	virtual void CompileScript(const char* name, bool unk) = 0;
	virtual void RunScript(const char* name, HSCRIPT scope, bool unk) = 0;
	virtual void RunScript(const char* name, bool unk) = 0;
	virtual void RunScript(const char* name) = 0;
	virtual HSCRIPT FetchCachedScriptScope(const char* name) = 0;
	virtual void ClearCachedScripts(void) = 0;
	virtual void ReloadCachedScripts(void) = 0;
	virtual void RegisterGameEventListenersInScope(HSCRIPT scope) = 0;
	virtual void UnRegisterGameEventListenersInScope(HSCRIPT scope) = 0;
	virtual void ClearScriptGameEventListeners(void) = 0;
	virtual int GetScriptLanguage(void) = 0; // I think lua is #1?
	virtual void InstallScriptBindings(void) = 0; // Registers all the available commands the scripting language can use.
	virtual void RemoveScriptBindings(void) = 0; // unregisters all commands. ^^
};