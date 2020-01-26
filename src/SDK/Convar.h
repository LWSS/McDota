#pragma once

#include "color.h"
#include "CUtlMemory.h"
#include "CUtlVector.h"

#include <cstdint>

// findflags in console
#define FCVAR_UNREGISTERED	            (1<<0)	// If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY           (1<<1)  // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL                   (1<<2)
#define FCVAR_CLIENTDLL                 (1<<3)

#define FCVAR_PROTECTED                 (1<<5)
#define FCVAR_SPONLY                    (1<<6)
#define FCVAR_ARCHIVE                   (1<<7)
#define FCVAR_NOTIFY                    (1<<8)
#define FCVAR_USERINFO                  (1<<9)

#define FCVAR_PRINTABLEONLY             (1<<10)
#define FCVAR_UNLOGGED                  (1<<11)
#define FCVAR_NEVER_AS_STRING           (1<<12)

#define FCVAR_REPLICATED                (1<<13)
#define FCVAR_CHEAT                     (1<<14)
#define FCVAR_SS                        (1<<15)
#define FCVAR_DEMO                      (1<<16)
#define FCVAR_DONTRECORD                (1<<17)
#define FCVAR_SS_ADDED                  (1<<18)
#define FCVAR_RELEASE                   (1<<19)
#define FCVAR_RELOAD_MATERIALS          (1<<20)
#define FCVAR_RELOAD_TEXTURES           (1<<21)
#define FCVAR_NOT_CONNECTED             (1<<22)
#define FCVAR_MATERIAL_SYSTEM_THREAD    (1<<23)
#define FCVAR_ARCHIVE_XBOX              (1<<24)

#define FCVAR_ACCESSIBLE_FROM_THREADS   (1<<25)

#define FCVAR_LINKED_CONCOMMAND         (1<<26)
#define FCVAR_VCONSOLE_FUZZY_MATCHING   (1<<27)

#define FCVAR_SERVER_CAN_EXECUTE        (1<<28)
#define FCVAR_SERVER_CANNOT_QUERY       (1<<28)
#define FCVAR_VCONSOLE_SET_FOCUS        (1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE     (1<<30)
#define FCVAR_EXECUTE_PER_TICK          (1<<31)


// This ConVar class is now p90
// The vtable is unimplemented and grabbed from an existing convar

struct CVValue_t
{
    char *m_pszString;
    int m_stringLength;
    float m_fValue;
    int m_nValue;
    int _pad4;
};

class ConCommandBase
{
public:
    virtual void DESTROY1() = 0;
    virtual void DESTROY2()= 0;
    virtual bool IsCommand(void)= 0;
    virtual	bool IsBoundedVar(void)= 0;
    virtual	bool IsFlagSet(long long)= 0;
    virtual	void AddFlags(long long)= 0;
    virtual	void RemoveFlags(long long)= 0;
    virtual	long long GetFlags(void)= 0;
    virtual	const char* GetName(void)= 0;
    virtual	const char* GetHelpText(void)= 0;
    virtual	bool IsRegistered(void)= 0;
    virtual	void* GetDLLIdentifier(void)= 0;
    virtual	void Create(char const*,char const*,long long)= 0;
    virtual	void Init(void)= 0;
    virtual	const char* GetBaseName(void)= 0;
    virtual	int GetSplitScreenPlayerSlot(void)= 0;
    virtual	void SetValue(char const*)= 0;
    virtual	void SetValue(float)= 0;
    virtual	void SetValue(int)= 0;
    virtual	void SetValue(Color)= 0;
    virtual	float GetFloat(void)= 0;
    virtual	int GetInt(void)= 0;
    virtual	bool GetBool(void)= 0;
    virtual	void InternalSetValue(char const*)= 0;
    virtual	void InternalSetFloatValue(float)= 0;
    virtual	void InternalSetIntValue(int)= 0;
    virtual	void InternalSetColorValue(Color)= 0;
    virtual	void ClampValue(float &)= 0;
    virtual	void ChangeStringValue(char const*,float)= 0;
    virtual	void Create()= 0;//char const*,char const*,long long,char const*,bool,float,bool,float,void (*)(IConVar *,char const*,float)) = 0;

    ConCommandBase *m_pNext;
    bool m_bRegistered;
    char _pad[7];
    char *m_pszName;
    char *m_pszHelpString;
    uint32_t m_nFlags;
    char _padflags[4]; //alignment
};

class ConVar : public ConCommandBase
{
public:
    void *ConVar_vtable;
    ConVar *parent;
    char *m_pszDefaultValue;
    CVValue_t m_Value;
    bool bHasMin;
    char _pad1[3];
    float m_fMinVal;
    bool bHasMax;
    char _pad2[3];
    float m_fMaxVal;
    CUtlVector<void (*)(ConVar*,char const*,float)>/*,CUtlMemory<void (*)(IConVar*,char const*,float),int> >*/ m_fnChangeCallbacks;
};