#pragma once
#include <cstring>
#include "IAppSystem.h"
#include "Convar.h"

#define FCVAR_NONE					0

#define FCVAR_UNREGISTERED			(1<<0)
#define FCVAR_DEVELOPMENTONLY		(1<<1)
#define FCVAR_GAMEDLL				(1<<2)
#define FCVAR_CLIENTDLL				(1<<3)
#define FCVAR_HIDDEN				(1<<4)

#define FCVAR_PROTECTED				(1<<5)
#define FCVAR_SPONLY				(1<<6)
#define FCVAR_ARCHIVE				(1<<7)
#define FCVAR_NOTIFY				(1<<8)
#define FCVAR_USERINFO				(1<<9)
#define FCVAR_CHEAT					(1<<14)

#define FCVAR_PRINTABLEONLY			(1<<10)
#define FCVAR_UNLOGGED				(1<<11)
#define FCVAR_NEVER_AS_STRING		(1<<12)
#define FCVAR_RELEASE				(1<<19)

#define FCVAR_REPLICATED			(1<<13)
#define FCVAR_DEMO					(1<<16)
#define FCVAR_DONTRECORD			(1<<17)

#define FCVAR_NOT_CONNECTED			(1<<22)
#define FCVAR_ARCHIVE_XBOX			(1<<24)
#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)

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
	virtual void InstallGlobalChangeCallback();//void (*)(IConVar *,char const*,float)) = 0;
	virtual void RemoveGlobalChangeCallback();//void (*)(IConVar *,char const*,float)) = 0;
	virtual void CallGlobalChangeCallbacks(ConVar *,char const*,float) = 0;
	virtual void InstallConsoleDisplayFunc(void *IConsoleDisplayFunc) = 0;
	virtual void RemoveConsoleDisplayFunc(void *IConsoleDisplayFunc) = 0;
	virtual void ConsoleColorPrintf(const ColorRGBA& MsgColor, const char* szMsgFormat, ...) = 0;
	virtual void ConsolePrintf(char const*,...) = 0;
	virtual void ConsoleDPrintf(const char* szMsgFormat, ...) = 0;
	virtual void RevertFlaggedConVars(long long) = 0;
	virtual void InstallCVarQuery(void *ICvarQuery) = 0;
	virtual void SetMaxSplitScreenSlots(int) = 0;
	virtual int GetMaxSplitScreenSlots(void) = 0;
	virtual void AddSplitScreenConVars(void) = 0;
	virtual void RemoveSplitScreenConVars(int) = 0;
	virtual void GetConsoleDisplayFuncCount(void) = 0;
	virtual void GetConsoleText(int,char *,unsigned long) = 0;
	virtual void IsMaterialThreadSetAllowed(void) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar *,char const*) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar *,int) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar *,float) = 0;
	virtual void HasQueuedMaterialThreadConVarSets(void) = 0;
	virtual void ProcessQueuedMaterialThreadConVarSets(void) = 0;
	virtual void FactoryInternalIterator(void) = 0;
	virtual void InstallConVarListener(void *IConVarListener) = 0;
	virtual void RemoveConVarListener(void *IConVarListener) = 0;
	virtual void GetConVarDetails();//CUtlVector<CConVarDetail,CUtlMemory<CConVarDetail,int>> &) = 0;
	virtual void ResetConVarsToDefaultValues(char const*) = 0;
	virtual void TakeConVarSnapshot(void) = 0;
	virtual void ResetConVarsToSnapshot(void* ConVarSnapshot_t__ ) = 0;
	virtual void DestroyConVarSnapshot(void* ConVarSnapshot_t__ ) = 0;
};
