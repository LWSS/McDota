#pragma once

struct AppSystemInfo_t
{
    const char* m_pModuleName;
    const char* m_pInterfaceName;
};

enum InitReturnVal_t
{
    INIT_FAILED = 0,
    INIT_OK,

    INIT_LAST_VAL,
};

enum AppSystemTier_t
{
    APP_SYSTEM_TIER0 = 0,
    APP_SYSTEM_TIER1,
    APP_SYSTEM_TIER2,
    APP_SYSTEM_TIER3,

    APP_SYSTEM_TIER_OTHER,
};

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

/* Things that at the start of the Officially exported Interfaces */
/* Note that some classes may not include all of these */
class IAppSystem
{
public:
    virtual void Connect( CreateInterfaceFn factory ) = 0;
    virtual void Disconnect() = 0;
    // Here's where systems can access other interfaces implemented by this object
    // Returns NULL if it doesn't implement the requested interface
    virtual void* QueryInterface(const char* interfaceName) = 0; // normally has string of interface in it. EX: "PanoramaUIEngine001"
    virtual InitReturnVal_t Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Preshutdown() = 0;
    // Returns all dependent libraries
    virtual const AppSystemInfo_t* GetDependencies() = 0;
    virtual AppSystemTier_t GetTier() = 0;
    // Reconnect to a particular interface
    virtual void Reconnect(void* factory, const char* pInterfaceName) = 0;
    virtual bool IsSingleton() = 0;
    virtual void GetBuildType() = 0; // 10
};