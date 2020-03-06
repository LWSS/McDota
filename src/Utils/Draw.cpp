#include "Draw.h"

// FrustumTransform
bool Draw::WorldToScreen( const Vector &spot, int &xOut, int &yOut, const VMatrix &vMatrix ) {
    float w;
    float x,y;
    x = vMatrix[0][0] * spot[0] + vMatrix[0][1] * spot[1] + vMatrix[0][2] * spot[2] + vMatrix[0][3];
    y = vMatrix[1][0] * spot[0] + vMatrix[1][1] * spot[1] + vMatrix[1][2] * spot[2] + vMatrix[1][3];
    //	z		 = vMatrix[2][0] * spot[0] + vMatrix[2][1] * spot[1] + vMatrix[2][2] * spot[2] + vMatrix[2][3];
    w		 = vMatrix[3][0] * spot[0] + vMatrix[3][1] * spot[1] + vMatrix[3][2] * spot[2] + vMatrix[3][3];

    bool behind;
    if( w < 0.001f )
    {
        behind = true;
    }
    else
    {
        behind = false;
        float invw = 1.0f / w;
        x *= invw;
        y *= invw;
    }

    xOut = (int)x;
    yOut = (int)y;

    return behind;
}