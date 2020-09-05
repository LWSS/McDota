#pragma once

#include "color.h"
#include "vector.h"
#include "CFontManager.h"

typedef unsigned long long VPANEL;

// (libvguirendersurface) - xref "DrawFilledRectFastFade" to ::DrawFilledRectFastFade()
class IVGuiPaintSurface
{
public:
    virtual void destroy();
	virtual void destroy2();
	virtual void Paint3D(void* VguiPaint3DInfo_t ,int n);
	virtual void DisableClipping(bool state);
	virtual void Set3DPaintTempRenderTarget(char const* targetString);
	virtual void Reset3DPaintTempRenderTarget(void);
	virtual void UpdateRefractTexture(bool state);
	virtual void DrawColoredCircle(int x, int y, float radius, int r, int g, int b, int a);
	virtual void DrawFilledRectFastFade(int,int,int,int,int,int,uint,uint,bool);
	virtual void DrawFilledRectFade(int,int,int,int,uint,uint,bool);
	virtual void DrawOutlinedCircle(int x,int y,int radius,int segments);
	virtual void DrawTexturedPolyLine(void* vguiVertex_t, int n);
	virtual void DrawTexturedSubRect(int x0,int y0,int x1,int y1,float texs0,float text0,float texs1,float text1);
	virtual void DrawSetTextFont(HFont font);
	virtual void DrawColoredText(HFont font,int x,int y,int r,int g,int b,int a,char const* text,...);
	virtual void DrawColoredTextRect(HFont font,int x0,int y0,int x1,int y1,int r,int g,int b,int a,char const* text,...);

	virtual void DrawSetColor(int r, int g, int b, int a);
	virtual void DrawSetColor(ColorRGBA color);
	virtual void DrawSetAlphaMultiplier(float alpha);

	virtual void DrawFilledRect(int x0, int y0, int x1, int y1);
	virtual void DrawFilledRectArray(void* vguiIntRect,int n);
	virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1);
	virtual void DrawLine(int x0, int y0, int x1, int y1);
	virtual void DrawPolyLine(int n, void* VGuiPoint_t);

	virtual void DrawSetTextColor(int r, int g, int b, int a);
	virtual void DrawSetTextColor(Color2 color);
	virtual void DrawSetTextPos(int x, int y);

	virtual void DrawPrintText(wchar_t const* text,int textLen, int vguiFontDrawType_t = 0); //FONT_DRAW_DEFAULT
	virtual void DrawUnicodeChar(wchar_t wch, int vguiFontDrawType_t = 0); //FONT_DRAW_DEFAULT
	virtual void DrawRenderCharFromInfo(void* vguiCharRenderInfo);
	virtual void DrawUnicodeString(wchar_t const* text, int vguiFontDrawType_t = 0);
	virtual void DrawFlushText(void);
	virtual void DrawWordBubble(int,int,int,int,int,Color2,Color2,bool,int,int,int);
	virtual void DrawSetTexture(int id);
	virtual void DrawTexturedRect(int x0,int y0,int x1,int y1);
	virtual void DrawTexturedRectEx(void* vguiDrawTexturedRectParms_t);
	virtual void DrawTexturedLine(void* vguiVertex_tStart, void* vguiVertex_tEnd);
	virtual void DrawSetTextureFrame(int id,int nFrame,unsigned int * pFrameCache);
	virtual void DrawTexturedPolygon(int n,void* vguiVertex_t,bool clipVertices = true);
	virtual void DrawGradientFilledRect(int x0,int y0,int x1,int y1, int IVGuiPaintSurfaceEGradientDirection,Color2 one,Color2 two);
	virtual void PlaySound(const char* filename);
	virtual void SetClipRect(int x0,int x1,int y0,int y1);
	virtual void SetZPos(float zPos);
	virtual float GetZPos(void);
	virtual void SetStencilReference(int ref);
	virtual void* DrawGetTextureHandle(int id);
	virtual void PushMakeCurrent(VPANEL panel,bool useInsets);
	virtual void PopMakeCurrent(VPANEL panel);
	virtual float DrawGetAlphaMultiplier(void);
	virtual void DrawGetTextPos(int &x,int &y);
	virtual void DrawGetUnicodeCharRenderInfo(wchar_t ch, void* vguiCharRenderInfo);
	virtual int GetFontTall(HFont font);
	virtual int GetFontAscent(HFont font ,wchar_t wch);
	virtual bool IsFontAdditive(HFont font);
	virtual void GetCharABCwide(HFont font, int ch, int &a, int &b, int &c);
	virtual void GetCharacterWidth(HFont font, int ch);
	virtual void GetKernedCharWidth();
	virtual void GetTextSize(HFont font,wchar_t const* text,int &wide,int &tall);
	virtual int GetTextHeight(HFont font,int x,int &y,char *text,...);
	virtual size_t GetTextLen(HFont font,char const*,...);
	virtual int CreateNewTextureID(bool procedural = false);
	virtual int DrawGetTextureId(char const* filename);
	virtual void DrawSetTextureFile(int id,char const* filename,int hardwareFilter,bool forceReload);
	virtual void DrawGetTextureFile(int id,char * filename,int maxLen);
	virtual void DrawSetTextureRGBA(int id,const unsigned char* rgba,int wide,int tall);
	virtual void DrawGetTextureSize(int id,int &wide,int &tall,bool unk);
	virtual bool IsTextureIDValid(int id);
	virtual void* DrawGetTextureMatInfoFactory(int id);
	virtual void GetScreenSize(int &wide,int &tall);
	virtual bool IsMinimized(VPANEL panel);
	virtual void FlashWindow(VPANEL panel,bool state);
	virtual void SetTitle(VPANEL panel, const wchar_t * title);
	virtual const wchar_t *GetTitle(VPANEL panel);
	virtual void SurfaceGetCursorPos(int &x,int &y);
	virtual void SwapBuffers(VPANEL panel);
	virtual void Invalidate(VPANEL panel);
	virtual bool IsCursorVisible(void);
	virtual bool IsWithin(int x,int y);
	virtual bool HasFocus(void);
	virtual void SolveTraverse(VPANEL panel,bool forceApplySchemeSettings = false);
	virtual void PaintTraverse(IVGuiPaintSurface * surface,VPANEL panel);
	virtual void* GetIconImageForFullPath(char const* pFullPath);
	virtual const char* GetResolutionKey(void);
	virtual int GetTextureNumFrames(int id);
	virtual void GetClipRect(int &x0,int &y0,int &x1,int &y1);
	virtual void Paint3D(void* VguiPaint3DInfo_t);
	virtual void DrawTexturedQuadArray(int n,void* VGuiTexturedQuad_t,bool clip = true);
	virtual void QueueCustomPaintCallbackInternal(void* IVGuiCustomPaintCallback ,int unk);

};