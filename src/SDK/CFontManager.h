#pragma once
#include "IAppSystem.h"

typedef unsigned long long HFont;

enum class FontFeature : int
{
    FONT_FEATURE_ANTIALIASED_FONTS = 1,
    FONT_FEATURE_DROPSHADOW_FONTS = 2,
    FONT_FEATURE_OUTLINE_FONTS = 6
};

enum class FontFlags : int
{
    FONTFLAG_NONE = 0,
    FONTFLAG_ITALIC = 0x1,
    FONTFLAG_UNDERLINE = 0x2,
    FONTFLAG_STRIKEOUT = 0x4,
    FONTFLAG_SYMBOL = 0x8,
    FONTFLAG_ANTIALIAS = 0x10,
    FONTFLAG_GAUSSIANBLUR = 0x20,
    FONTFLAG_ROTARY = 0x40,
    FONTFLAG_DROPSHADOW = 0x80,
    FONTFLAG_ADDITIVE = 0x100,
    FONTFLAG_OUTLINE = 0x200,
    FONTFLAG_CUSTOM = 0x400,
    FONTFLAG_BITMAP = 0x800,
};

enum class FontDrawType_t : int
{
    // Use the "additive" value from the scheme file
    FONT_DRAW_DEFAULT = 0,

    // Overrides
    FONT_DRAW_NONADDITIVE,
    FONT_DRAW_ADDITIVE,

    FONT_DRAW_TYPE_COUNT = 2,
};

// "DefaultFontAliasGroup" xref to the one that's by a bunch of `mov dword ptr [rax+xx], 0` - this is Init()
// or xref "Tag: %s \n" back to SpewFonts
class CFontManager : IAppSystem
{
public:
    virtual HFont CreateFont(void) = 0;
    virtual void ClearAllFonts(void) = 0;
    virtual void SetLanguage(const char *language) = 0;
    virtual const char* GetLanguage(void) = 0;
    virtual void RegisterCustomFont() = 0; // new function, a guess.
    virtual void FindFontAliasList(void *CUtlStringToken) = 0;
    virtual void RemoveFontAliasList(const char*) = 0;
    virtual void GetFontAliases(const char*) = 0;
    virtual void CreateFontAlias(const char*, const char*, bool) = 0;
    virtual HFont GetFont(const char* name, const char* unk, bool unk2) = 0;  // 20
    virtual void LoadFont(const char*, const char*, int, int, bool, int, int, int, int, int, const char*) = 0;
    virtual HFont FindFont(const char*, bool, const char*) = 0;
    virtual HFont FindOrLoadFont(const char*, const char*, int, int, bool, int, int, int, int, int, const char*) = 0;
    virtual void GetTrueFontName(void const * FontAlias_t) = 0;
    virtual void GetFontRange(const char*, int &, int &, const char*) = 0;
    virtual void SetFontRange(const char*, int, int, const char*) = 0;
    virtual bool SetFontGlyphSet(HFont, const char* windowsFontName, int size, int, int, int, int, int, int flags) = 0;
    virtual void GetFontName(HFont) = 0;
    virtual void GetFontTall(HFont) = 0;
    virtual void GetCharacterWidth(HFont, int) = 0;
    virtual void GetKernedCharWidth(HFont, wchar_t, wchar_t, wchar_t, float &, float &, float &) = 0;
    virtual void GetCharABCwide(HFont, int, int &, int &, int &) = 0;
    virtual void GetTextSize(HFont, const wchar_t*, int &, int &) = 0;
    virtual void GetTextureHandle(int) = 0;
    virtual void GetFontAscent(HFont, wchar_t) = 0;
    virtual void GetFontUnderlined(HFont) = 0;
    virtual bool IsFontAdditive(HFont) = 0;
    virtual void PrecacheFontCharacters(HFont, wchar_t *) = 0;
    virtual void ClearFontTextureCache(void) = 0;
    virtual void GetTextureForChar(HFont, int FontDrawType_t, wchar_t, int *, float **) = 0;
    virtual void ClearTemporaryFontCache(void) = 0;
    virtual void SpewFonts(const char *, float) = 0;
    virtual void DESTROY1() = 0;
    virtual void DESTROY2() = 0;
};

// disabled bitmap fonts with the Ti2019 battlepass
// some threading changes with Diretide 2020