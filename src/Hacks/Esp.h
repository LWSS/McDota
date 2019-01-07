#pragma once

#include "../SDK/IVPanel.h"

namespace ESP
{
    inline HFont paintFont = 0;

    //Hooks
    void PaintTraverse( IVPanel *thisptr, IVGuiPaintSurface *surface, VPANEL panel, bool force_repaint, bool allow_force );
}