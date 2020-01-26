#pragma once
#include "IAppSystem.h"
#include "Valve/tier1/utldelegateimpl.h"
#include "INetChannel.h"

struct CUtlSlot;
struct IRecipientFilter;

// xref "Attempted to post a message to a NULL" to CGameEventSystem::PostEntityEventAbstract
class CGameEventSystem : IAppSystem
{
public:
    virtual void RegisterGameEvent( GameEventHandle_t * ); // 11
    virtual void RegisterGameEventHandlerAbstract(CUtlSlot *,CUtlAbstractDelegate const&,GameEventHandle_t *,int);
    virtual void UnregisterGameEventHandlerAbstract(CUtlSlot *,CUtlAbstractDelegate const&,GameEventHandle_t *);
    virtual void PostEventAbstract_Local(int splitScreenSlot,GameEventHandle_t *,void const*,unsigned long);
    virtual void PostEventAbstract(int splitScreenSlot,bool,int,unsigned char const*,GameEventHandle_t *,void const*,unsigned long,NetChannelBufType_t);
    virtual void PostEventAbstract(int splitScreenSlot,bool,IRecipientFilter *,GameEventHandle_t *,void const*,unsigned long);
    virtual void PostEntityEventAbstract(const int& CEntityHandle,GameEventHandle_t *,void const*,unsigned long,NetChannelBufType_t);
    virtual void ProcessQueuedEvents(void);
    virtual void GetEventSource(void);
    virtual void PurgeQueuedEvents(void);
};