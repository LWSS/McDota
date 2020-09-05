#pragma once
#include <cstring>
#include "IAppSystem.h"
#include "Convar.h"

//xref "VEngineCvar007" to ::QueryInterface() - should be 1st one (moved to libtier0.so)
class ICvar : public IAppSystem
{
public:
	typedef int CVarDLLIdentifier_t;

	virtual CVarDLLIdentifier_t AllocateDLLIdentifier(void) = 0;
	virtual void RegisterConCommand(ConCommandBase *) = 0;
	virtual void UnregisterConCommand(ConCommandBase *) = 0;
	virtual void UnregisterConCommands(int) = 0;
	virtual const char* GetCommandLineValue(char const*) = 0;
	virtual ConCommandBase* FindCommandBase(char const*) = 0;
	virtual const ConCommandBase* FindCommandBase2(char const*) = 0;
	virtual ConVar* FindVar(char const*) = 0;
	virtual const ConVar* FindVar2(char const*) = 0;
	virtual void* FindCommand(char const*) = 0;
	virtual const void* FindCommand2(char const*) = 0;
	virtual void InstallGlobalChangeCallback() = 0;//void (*)(IConVar *,char const*,float)) = 0;
	virtual void RemoveGlobalChangeCallback() = 0;//void (*)(IConVar *,char const*,float)) = 0;
	virtual void CallGlobalChangeCallbacks(ConVar *,char const*,float) = 0;
	virtual void RevertFlaggedConVars(long long) = 0;
	virtual void InstallCVarQuery(void *ICvarQuery) = 0;
	virtual void SetMaxSplitScreenSlots(int) = 0;
	virtual int GetMaxSplitScreenSlots(void) = 0;
	virtual void AddSplitScreenConVars(void) = 0;
	virtual void RemoveSplitScreenConVars(int) = 0;
	virtual void FactoryInternalIterator(void) = 0;
	virtual void InstallConVarListener(void *IConVarListener) = 0;
	virtual void RemoveConVarListener(void *IConVarListener) = 0;
	virtual void GetConVarDetails() = 0;//CUtlVector<CConVarDetail,CUtlMemory<CConVarDetail,int>> &) = 0;
	virtual void ResetConVarsToDefaultValues(char const*) = 0;
	virtual void TakeConVarSnapshot(void) = 0;
	virtual void ResetConVarsToSnapshot(void* ConVarSnapshot_t__ ) = 0;
	virtual void DestroyConVarSnapshot(void* ConVarSnapshot_t__ ) = 0;
	virtual bool IsValid(void) = 0; // added march 2 2020
	virtual void* GetSomething(void) = 0; // added sept 4 2020 - returns [rdi+100h]
};
