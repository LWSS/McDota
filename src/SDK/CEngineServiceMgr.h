#pragma once

#include "IAppSystem.h"

class ILoopModeFactory;
class IEngineService;
class ISwitchLoopModeStatusNotify;
class IAddonListChangeNotify;
class IPrerequisite;
struct ActiveLoop_t;
struct EventClientOutput_t;
struct RenderDeviceInfo_t;

// xref "Duplicate engine service named" to CEngineServiceMgr::RegisterEngineService()
class CEngineServiceMgr : IAppSystem
{
public:
    virtual void RegisterEngineService( const char *, IEngineService * ) = 0; // 11
    virtual void UnregisterEngineService( const char *, IEngineService * ) = 0;
    virtual void RegisterLoopMode( const char *, ILoopModeFactory *, void ** ) = 0;
    virtual void UnregisterLoopMode( const char *, ILoopModeFactory *, void ** ) = 0;
    virtual void SwitchToLoop( const char *, void *KeyValues, unsigned int, const char *, bool ) = 0;
    virtual const char *GetActiveLoopName( void ) = 0;
    virtual IEngineService *FindService( const char * ) = 0;
    virtual void *GetEngineWindow( void ) = 0;
    virtual void *GetEngineSwapChain( void ) = 0;
    virtual void *GetEngineInputContext( void ) = 0;
    virtual void *GetEngineDeviceInfo( void ) = 0;
    virtual void *GetEngineDeviceWidth( void ) = 0;
    virtual void *GetEngineDeviceHeight( void ) = 0;
    virtual void GetEngineSwapChainSize( int *width, int *height ) = 0;
    virtual void *Plat_GetWindowSafeAreaInsets( void ) = 0; // (NEW) added with 2019 TI battlepass
    virtual bool IsLoopSwitchQueued( void ) = 0;
    virtual bool IsLoopSwitchRequested( void ) = 0;
    virtual void *GetEventDispatcher( void ) = 0;
    virtual void *GetDebugVisualizerMgr( void ) = 0;
    virtual int GetActiveLoopClientServerMode( void ) = 0;
    virtual void PrintStatus( void ) = 0;
    virtual void GetActiveLoop( ActiveLoop_t & ) = 0;
    virtual bool IsLoadingLevel( void ) = 0;
    virtual bool IsInGameLoop( void ) = 0;
    virtual void OnFrameRenderingFinished( bool, EventClientOutput_t const & ) = 0;
    virtual void ChangeVideoMode( RenderDeviceInfo_t & ) = 0;
    virtual void GetVideoModeChange( void ) = 0;
    virtual int GetAddonCount( void ) = 0;
    virtual void *GetAddon( int ) = 0;
    virtual bool IsAddonMounted( const char * ) = 0;
    virtual const char *GetAddonsString( void ) = 0;
    virtual void InstallSwitchLoopModeStatusNotify( ISwitchLoopModeStatusNotify * ) = 0;
    virtual void UninstallSwitchLoopModeStatusNotify( ISwitchLoopModeStatusNotify * ) = 0;
    virtual void InstallAddonListChangeNotify( IAddonListChangeNotify * ) = 0;
    virtual void UninstallAddonListChangeNotify( IAddonListChangeNotify * ) = 0;
    virtual void StartEngineWatchDogThread() = 0; // (NEW) added jan 2020
    virtual void ExitMainLoop( void ) = 0;
    virtual void RegisterPrerequisite( IPrerequisite * ) = 0;
    virtual void *LookupLocalizationToken( const char * ) = 0;
    virtual void UnregisterPrerequisite( IPrerequisite * ) = 0;
};