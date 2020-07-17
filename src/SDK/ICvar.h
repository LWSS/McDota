#pragma once
#include <cstring>
#include "IAppSystem.h"
#include "Convar.h"

//xref "Parent and child ConVars with different" to RegisterConCommand
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
	virtual void IsMaterialThreadSetAllowed(void) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar *,char const*) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar *,int) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar *,float) = 0;
	virtual void HasQueuedMaterialThreadConVarSets(void) = 0;
	virtual void ProcessQueuedMaterialThreadConVarSets(void) = 0;
	virtual void FactoryInternalIterator(void) = 0;
	virtual void InstallConVarListener(void *IConVarListener) = 0;
	virtual void RemoveConVarListener(void *IConVarListener) = 0;
	virtual void GetConVarDetails() = 0;//CUtlVector<CConVarDetail,CUtlMemory<CConVarDetail,int>> &) = 0;
	virtual void ResetConVarsToDefaultValues(char const*) = 0;
	virtual void TakeConVarSnapshot(void) = 0;
	virtual void ResetConVarsToSnapshot(void* ConVarSnapshot_t__ ) = 0;
	virtual void DestroyConVarSnapshot(void* ConVarSnapshot_t__ ) = 0;
	virtual bool IsValid(void) = 0; // added march 2 2020
};
