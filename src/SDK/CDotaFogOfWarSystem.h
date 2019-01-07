#pragma once

class CFoW
{
public:
    virtual void Init() = 0;
    virtual void PostInit() = 0;
    virtual void Shutdown() = 0;
    virtual void GameInit() = 0;
    virtual void GameShutdown() = 0;
    virtual void GamePostInit() = 0;
    virtual void BuildGameSessionManifest() = 0;
    virtual void sub_297A790() = 0;
    virtual void sub_297A7A0() = 0; // These are all empty functions,
    virtual void sub_297A7B0() = 0; // derived from IGameSystem with a couple extras.
    virtual void sub_297A7C0() = 0;
    virtual void sub_297A7D0() = 0;
    virtual void sub_297A7E0() = 0;
    virtual void sub_297A7F0() = 0;
    virtual void sub_3086650() = 0;
    virtual void sub_297A810() = 0;
    virtual void sub_297A820() = 0;
    virtual void sub_30813F0() = 0;
    virtual void sub_297A840() = 0;
    virtual void sub_297A850() = 0;
    virtual void PreRender() = 0;
    virtual void sub_297A870() = 0;
    virtual void sub_297A880() = 0;
    virtual void sub_297A890() = 0;
    virtual void sub_297A8A0() = 0;
    virtual void sub_297A8B0() = 0;
    virtual void sub_297A8C0() = 0;
    virtual void sub_297A8D0() = 0;
    virtual void sub_297A8E0() = 0;
    virtual void sub_297A8F0() = 0;
    virtual void sub_297A900() = 0;
    virtual void sub_297A910() = 0;
    virtual void sub_297A920() = 0;
    virtual const char* GetName() = 0;
    virtual void SetGameSystemGlobalPtrs( void* ) = 0;
    virtual void SetName(const char *) = 0;
    virtual bool DoesGameSystemReallocate() = 0;
    virtual void DESTROY1() = 0;
    virtual void DESTROY2() = 0;
};
