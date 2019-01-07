#pragma once

class CViewSetup
{
public:
    float x; //0x0000
    float y; //0x0004
    float z; //0x0008
    float pitch; //0x000C
    float yaw; //0x0010
    float roll; //0x0014
    float fov; //0x0018
    float aspectRatio; //0x001C
    float zNear; //0x0020
    float zFar; //0x0024
};