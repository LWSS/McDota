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
    char _pad[0x500];
};