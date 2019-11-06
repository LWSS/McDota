#pragma once

#include "vector.h"
class CViewSetup
{
public:
    Vector position;
    Vector angle;
    float fov; //0x0018
    float aspectRatio; //0x001C
    float zNear; //0x0020
    float zFar; //0x0024
    char _pad[0x18C];
    float cameraX;
    float unk[3];
    float cameraY;
    float unk2[3];
    float cameraZ; // 0x01D4
    char _pad2[0x218];
    Vector camPos; // 0x3F0
    char _pad3[0x150];
};