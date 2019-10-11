#include "Hooks.h"

#include "../Hacks/Esp.h"

static VPANEL topPanel = 0;

typedef void (* PaintTraverseFn)( IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool );


bool PaintTraverse::InitFonts( ){
    //ESP::paintFont = fontManager->FindOrLoadFont("Courier New", "MaterialSystem2DefaultDebugFontOutline", 20, 20, true, 20, 20, 20, 20, 0x200, NULL);
    //MC_PRINTF("ESP paintFont is now: %llu\n", ESP::paintFont);
    //fontManager->SpewFonts(NULL, 1.0f);

    /* Handle 2 is always this */
    /* 1: FontHandle:0x00000002, Courier New, MaterialSystem2DefaultDebugFontDefaultFontAliasGroup-no, font:Courier New, tall:15.000000.0, LoadFont used */
    ESP::paintFont = 2;
    return true;
}

void Hooks::PaintTraverse( IVPanel *thisptr, IVGuiPaintSurface *surface, VPANEL panel, bool force_repaint, bool allow_force ) {
    if( !engine->IsInGame() )
        return panelVMT->GetOriginalMethod<PaintTraverseFn>( 55 )( thisptr, surface, panel, force_repaint, allow_force );

    if( !topPanel ){
        if( !strcmp(thisptr->GetName(panel), "RenderSystemTopPanel" ) ){
            topPanel = panel;
        } else {
            return panelVMT->GetOriginalMethod<PaintTraverseFn>( 55 )( thisptr, surface, panel, force_repaint, allow_force );
        }
    }

    /*
    surface->PushMakeCurrent(panel, false);
    int width, height;
    engine->GetScreenSize( width, height );
    surface->DrawSetColor( ColorRGBA(10, 225, 10) );
    surface->DrawLine( width / 2, height / 2, width, height );
    surface->PopMakeCurrent(panel);
    */

    surface->PushMakeCurrent(panel, false);

    ESP::PaintTraverse( thisptr, surface, panel, force_repaint, allow_force );

    surface->PopMakeCurrent(panel);

    return panelVMT->GetOriginalMethod<PaintTraverseFn>( 55 )( thisptr, surface, panel, force_repaint, allow_force );
}