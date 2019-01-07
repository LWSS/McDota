#pragma once

typedef unsigned short MaterialHandle_t;

enum MaterialFogMode_t
{
	MATERIAL_FOG_NONE,
	MATERIAL_FOG_LINEAR,
	MATERIAL_FOG_LINEAR_BELOW_FOG_Z,
};

class KeyValues;

class ITexture {
public:
	int GetActualWidth( )
	{
		typedef int (* oGetActualWidth)( void* );
		return getvfunc<oGetActualWidth>( this, 3 )( this );
	}
	int GetActualHeight( )
	{
		typedef int (* oGetActualHeight)( void* );
		return getvfunc<oGetActualHeight>( this, 4 )( this );
	}
};

class IMatRenderContext {
public:
	void *GetThisPtr( ){
		return this;
	}
	int Release( ) {
		typedef int (* oRelease)( void* );
		return getvfunc<oRelease>( this, 1 )( this );
	}
	void SetRenderTarget( ITexture *pTexture ) {
		typedef void (* oSetRenderTarget)( void*, ITexture* );
		return getvfunc<oSetRenderTarget>( this, 6 )( this, pTexture );
	}
	// 14? - SetAmbientLight()

	void FogMode( MaterialFogMode_t fogMode ){
		typedef void (* oFogMode)( void*, MaterialHandle_t );
		return getvfunc<oFogMode>( this, 49 )( this, fogMode );
	}
	void FogColor( float r, float g, float b ){
		typedef void (* oFogColor)( void*, float ,float ,float );
		return getvfunc<oFogColor>( this, 54 )( this, r, g, b );
	}
	void GetFogColor( unsigned char *rgb ){
		typedef void (* oGetFogColor)( void*, unsigned char * );
		return getvfunc<oGetFogColor>( this, 58 )( this, rgb );
	}

	void PushRenderTargetAndViewport( ) {
		typedef void (* oPushRenderTargetAndViewport)( void* );
		return getvfunc<oPushRenderTargetAndViewport>( this, 115 )( this );
	}
	void PopRenderTargetAndViewport( ) {
		typedef void (* oPopRenderTargetAndViewport)( void* );
		return getvfunc<oPopRenderTargetAndViewport>( this, 119 )( this );
	}

	void DrawScreenSpaceRectangle( IMaterial* pMaterial,
								   int destX, int destY, int width, int height,
								   float srcTextureX0, float srcTextureY0, float srcTextureX1, float srcTextureY1,
								   int srcTextureWidth, int srcTextureHeight,
								   void* pClientRenderable, int nXDice, int nYDice ) {
		typedef void (* oDrawScreenSpaceRectangle)( void*, IMaterial* ,
													int , int , int , int ,
													float , float , float , float ,
													int , int ,
													void* , int , int  );
		return getvfunc<oDrawScreenSpaceRectangle>( this, 113 )( this, pMaterial, destX, destY, width, height,
																 srcTextureX0, srcTextureY0, srcTextureX1, srcTextureY1,
																 srcTextureWidth, srcTextureHeight, pClientRenderable,
																 nXDice, nYDice );
	}
};

class IMaterialSystem : public IAppSystem
{
public:
	IMaterial* CreateMaterial(const char* pMaterialName, KeyValues* pVMTKeyValues)
	{
		typedef IMaterial* (* oCreateMaterial)(void*, const char*, KeyValues*);
		return getvfunc<oCreateMaterial>(this, 83)(this, pMaterialName, pVMTKeyValues);
	}

	IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = NULL)
	{
		typedef IMaterial* (* oFindMaterial)(void*, char const*, const char*, bool, const char*);
		return getvfunc<oFindMaterial>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}

	MaterialHandle_t FirstMaterial()
	{
		typedef MaterialHandle_t (* oFirstMaterial)(void*);
		return getvfunc<oFirstMaterial>(this, 86)(this);
	}

	MaterialHandle_t NextMaterial(MaterialHandle_t h)
	{
		typedef MaterialHandle_t (* oNextMaterial)(void*, MaterialHandle_t);
		return getvfunc<oNextMaterial>(this, 87)(this, h);
	}

	MaterialHandle_t InvalidMaterial()
	{
		typedef MaterialHandle_t (* oInvalidMaterial)(void*);
		return getvfunc<oInvalidMaterial>(this, 88)(this);
	}

	IMaterial* GetMaterial(MaterialHandle_t h)
	{
		typedef IMaterial* (* oGetMaterial)(void*, MaterialHandle_t);
		return getvfunc<oGetMaterial>(this, 89)(this, h);
	}

	IMatRenderContext* GetRenderContext() {
		typedef IMatRenderContext* (* oGetRenderContext)( void* );
		return getvfunc<oGetRenderContext>( this, 115 )( this );
	}
};