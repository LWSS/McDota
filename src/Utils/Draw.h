#pragma once

#include "../SDK/vmatrix.h"
#include "../SDK/vector.h"

namespace Draw
{
    // True on fail ( behind player or something )
    bool WorldToScreen( const Vector &spot, int &xOut, int &yOut, const VMatrix &vMatrix );
}