#pragma once

#include "IAppSystem.h"


//xref "CNetworkStringTable::AddString"
class INetworkStringTable
{
public:
    virtual void DESTROY1();
    virtual void DESTROY2();

    // Table Info
    virtual const char *GetTableName( void );
    virtual int GetTableID( void );
    virtual int GetNumStrings( void );

    // Networking
    virtual void SetTick( int tick );
    virtual int GetTick( void );
    virtual bool ChangedSinceTick( int tick );

    // Accessors (length -1 means don't change user data if string already exits)
    virtual int AddString( bool isServer, const char * value, int length = -1, void const * userData = nullptr );
    virtual const char *GetString( int stringNumber, bool );
    virtual void SetStringUserData( int stringNumber, int length, void const *userData, bool );
    virtual const void *GetStringUserData( int stringNumber, int *length );
    virtual int FindStringIndex( const char *string );
    virtual void SetStringChangedCallback( void *object,void (*)(void *object,INetworkStringTable *stringTable,int stringNumber,char const *newString,void const* newData) );
};

//xref "Tried to create string table '%s'" to CreateStringTable()
class CNetworkStringTableContainer : IAppSystem
{
public:
    virtual void DESTROY();
    virtual void DESTROY2();
    virtual INetworkStringTable* CreateStringTable( const char *tableName, int,int, int ENetworkStringtableFlags );
    virtual void RemoveAllTables( void );
    
    virtual INetworkStringTable* FindTable( const char *tableName );
    virtual INetworkStringTable* GetTable( int tableID );
    virtual int GetNumTables( void );
    
    virtual void SetAllowClientSideAddString( INetworkStringTable *table, bool allow );
};