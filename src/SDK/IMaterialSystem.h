#pragma once

#include "IAppSystem.h"

class CMaterial2
{
public:

};

//xref "*** UNKNOWN ***" to GetModeString()
class IMaterialSystem : public IAppSystem
{
public:
	virtual const char* GetModeString(void const *CUtlStringToken) = 0;
	virtual void EnableExtendedMaterialInfo(void) = 0;
	virtual void EnableHeadlessMode(void) = 0;
	virtual CMaterial2* FindOrCreateMaterialFromResource( const char* ) = 0; // invalid name should give the classic checkbox material.
	virtual void SetRenderStateForRenderablePass() = 0;//(CRenderAttributes const*,IRenderContext *,CIntHandle32<RenderInputLayout_t__handle *>,MaterialRenderablePass_t const&,RsStencilStateOverride_t const*,int) = 0;
	virtual void sub_20A50() = 0;
	virtual void sub_20A90() = 0;
	virtual void sub_20AB0() = 0;
    virtual void sub_1E7F0() = 0; // Added with dota anime
	virtual void loc_2BAD0() = 0;
	virtual void DynamicShaderCompile_ReloadAllShaders(void) = 0;
	virtual void sub_SomeShaderStuff() = 0; // added sept 2019 dota+ update.
	virtual bool IsDynamicShaderCompileEnabled(void) = 0;
	virtual void SetMaterialParam_MaterialEditor() = 0;//(CWeakHandle<InfoForResourceTypeIMaterial2>,char const*,char const*)
	virtual void AddFrameUpdateFunc( void (*)(void) ) = 0;
	virtual void RemoveFrameUpdateFunc( void (*)(void) ) = 0;
	virtual void QueueMaterialRefreshAfterConfigChange(void) = 0;
	virtual void sub_21A20() = 0;
	virtual void loc_22390() = 0;
	virtual void loc_22660() = 0;
	virtual void* GetShaderQuality(void) = 0;
	virtual void sub_206C0() = 0;
	virtual void sub_20440() = 0;
	virtual void sub_20450() = 0;
	virtual void sub_20AD0() = 0;
	virtual void sub_222E0() = 0; // Added with aghanim's labyrinth - something to do with shaders.
	virtual void DESTROY() = 0;
	virtual void DESTROY2() = 0;
};