#pragma once

#include "IAppSystem.h"

//xref "INETSUPPORT_001" back to QueryInterface(), it should be right before a stricmp(), the function is small.
class INetSupport : IAppSystem
{
public:
    virtual int GetEngineBuildNumber( void ) = 0;
    virtual void GetBaseServerInfo( void *NetSupport__BaseServerInfo_t ) = 0;
    virtual void GetExtendedServerInfo( void *NetSupport__ExtendedServerInfo_t ) = 0;
    virtual void GetServerInfo( void *NetSupport__ServerInfo_t ) = 0;
    virtual void GetClientInfo( void *NetSupport__ClientInfo_t ) = 0;
    virtual void UpdateServerReservation( unsigned long long reservation ) = 0;
    virtual void UpdateClientReservation( unsigned long long reservation, unsigned long long machineIdHost ) = 0;
    virtual void ReserveServer( ) = 0;//netadr_t const&,netadr_t const&,ulong long,KeyValues *,IMatchAsyncOperationCallback *,IMatchAsyncOperation **
    virtual void OnMatchEvent( void *KeyValues ) = 0;
};