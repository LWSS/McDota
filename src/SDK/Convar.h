#pragma once

#include <cstdint>

class ConCommandBase;

// Not really ideal but there's already a Color struct used by the GUI.
struct ColorRGBA
{
    ColorRGBA(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha = 255)
    {
        RGBA[0] = Red;
        RGBA[1] = Green;
        RGBA[2] = Blue;
        RGBA[3] = Alpha;
    }

    unsigned char RGBA[4];
};

class ConVar
{
public:
    virtual void DESTROY1() = 0;
    virtual void DESTROY2() = 0;
    virtual bool IsCommand(void) = 0;
    virtual	bool IsBoundedVar(void) = 0;
    virtual	bool IsFlagSet(long long) = 0;
    virtual	void AddFlags(long long) = 0;
    virtual	void RemoveFlags(long long) = 0;
    virtual	long long GetFlags(void) = 0;
    virtual	const char* GetName(void) = 0;
    virtual	const char* GetHelpText(void) = 0;
    virtual	bool IsRegistered(void) = 0;
    virtual	void* GetDLLIdentifier(void) = 0;
    virtual	void Create(char const*,char const*,long long) = 0;
    virtual	void Init(void) = 0;
    virtual	const char* GetBaseName(void) = 0;
    virtual	int GetSplitScreenPlayerSlot(void) = 0;
    virtual	void SetValue(char const*) = 0;
    virtual	void SetValue(float) = 0;
    virtual	void SetValue(int) = 0;
    virtual	void SetValue(ColorRGBA) = 0;
    virtual	float GetFloat(void) = 0;
    virtual	int GetInt(void) = 0;
    virtual	bool GetBool(void) = 0;
    virtual	void InternalSetValue(char const*) = 0;
    virtual	void InternalSetFloatValue(float) = 0;
    virtual	void InternalSetIntValue(int) = 0;
    virtual	void InternalSetColorValue(ColorRGBA) = 0;
    virtual	void ClampValue(float &) = 0;
    virtual	void ChangeStringValue(char const*,float) = 0;
    virtual	void Create();//char const*,char const*,long long,char const*,bool,float,bool,float,void (*)(IConVar *,char const*,float)) = 0;

    ConCommandBase* next; //0x0008
    bool isRegistered; //0x0010
    char pad_0011[7]; //0x0011
    char* name; //0x0018
    char* description; //0x0020
    uint32_t flags; //0x0028
    char pad[4];
    void* unk; //0x0030
    void* thisptr; //0x0038
    char* strDefault; //0x0040
    char* strValue; //0x0048
    int type;
    float fValue;
    int iValue;
    char _pad[4];
    bool hasMin;
    char _padmin[3];
    float minVal;
    bool hasMax;
    char _padmax[3];
    float maxVal;
    char pad_0070[0x10]; //0x0070-0x80
};

class ConCommandBase
{
public:
    void* vtable;
    ConCommandBase* next; //0x0008
    bool isRegistered; //0x0010
    char pad_0011[7]; //0x0011
    char* name; //0x0018
    char* description; //0x0020
    uint32_t flags; //0x0028
    char pad[4];
    void* unk; //0x0030
    void* thisptr; //0x0038
    char* strDefault; //0x0040
    char* strValue; //0x0048
    int type;
    float fValue;
    int iValue;
    char _pad[4];
    bool hasMin;
    char _padmin[3];
    float minVal;
    bool hasMax;
    char _padmax[3];
    float maxVal;
    char pad_0070[0x10]; //0x0070-0x80
};