#pragma once
class CGlobalVars
{
public:
	float realtime; //0x0000
	int32_t framecount; //0x0004
	float absoluteFrametime; //0x0008
	float curtime; //0x000C
	float frametime; //0x0010
	int32_t maxClients; //0x0014
	int32_t tickcount; //0x0018
	float intervalPerTick; //0x001C
	float unk; //0x0020
	float interpAmount; //0x0024
	char pad_0028[4]; //0x0028
	bool somebool; //0x002C
	bool somebool2; //0x002D
	char pad_0030[362]; //0x0030
	char* currentMap; //0x0198
	char* currentMapName; //0x01A0
};