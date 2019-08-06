#include "Gui.h"

#include <algorithm>

#include "../Interfaces.h"

// Javascript to force root panel to have our child and raise it.
const char *cuckProtocol =
                "var parentPanel = $.GetContextPanel();\n"
                "var mcDota = parentPanel.FindChild(\"McDotaMain\");\n"
                "$.Msg(\"Loading Panel: \" + mcDota.id);"
                "mcDota.BLoadLayoutFromString( \"%s\", false, false);\n";

static constexpr unsigned int JS_MAX = 65535;
char jsCode[JS_MAX];
std::string mainXML =
#include "Main.xml"
;

static panorama::IUIPanel* GetHudRoot( ){
    panorama::IUIPanel *panel = panoramaEngine->AccessUIEngine()->GetLastDispatchedEventTargetPanel();

    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(panel) ){
        MC_PRINTF_WARN("Failed to grab Last Event Target Panel!\n");
        return nullptr;
    }
    panorama::IUIPanel *itr = panel;
    panorama::IUIPanel *ret = nullptr;
    while( itr && panoramaEngine->AccessUIEngine()->IsValidPanelPointer(itr) ){
        if( !strcasecmp(itr->GetID(), "DOTAHud") ){
            ret = itr;
            break;
        }
        itr = itr->GetParent();
    }
    return ret;
}

static inline void EscapeQuotes( ) {
    std::string result;
    result.reserve(result.length() * 2);

    for(char i : mainXML){
        switch( i ){
            case '"':
                result += '\\';

            default:
                result += i;
        }
    }
    mainXML = result;
}
static bool SetupAndCheckPanels()
{
    static bool bFirst = true;
    if( bFirst ){
        /* Get rid of newlines in the XML, they mess up the javascript syntax */
        std::replace(mainXML.begin(), mainXML.end(), '\n', ' ');
        /* Escape double-quotes in the XML */
        EscapeQuotes();
        bFirst = false;
    }
    /* Grab needed root panel if we don't have it already */
    if( engine->IsInGame() ){
        panorama::IUIPanel* panel = GetHudRoot();
        if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer( panel ) ){
            MC_PRINTF_WARN( "Could not Get HUD Root Panel! Invalid! (%p)\n", (void*)UI::hudRoot );
            return false;
        }
        UI::hudRoot = panel;
    } else if( !UI::dashRoot ){
        panorama::IUIPanel *panel = panoramaEngine->AccessUIEngine()->GetPanelArray()->slots[0].panel; // 0 = DotaDashboard
        if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer( panel ) ){
            MC_PRINTF_WARN( "Could not Get Dashboard Root Panel! Invalid! (%p)\n", (void*)UI::dashRoot );
            return false;
        }
        UI::dashRoot = panel;
    }
    /* Are we in-game? The Root panel is different */
    panorama::IUIPanel *root = ( engine->IsInGame() ? UI::hudRoot : UI::dashRoot );

    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(root) ){
        MC_PRINTF_WARN("Root panel pointer Invalid(%p)\n", (void*)root);
        return false;
    }
    if( !root->HasBeenLayedOut() ){
        MC_PRINTF_WARN("Root panel has not been layed out yet!\n");
        return false;
    }
    /* Going from menu->In-game OR Vice versa, set the pointer to NULL so we re-grab it below */
    if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer( UI::mcDota ) ){
        if( (engine->IsInGame() && UI::mcDota->GetParent() != UI::hudRoot) ||
            (!engine->IsInGame() && UI::mcDota->GetParent() != UI::dashRoot) ){
            UI::mcDota = nullptr;
        }
    }
    /* Going from in-game back to menu, change the pointer to our existing panel if it is there. */
    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer( UI::mcDota ) && !engine->IsInGame() ){
        panorama::IUIPanel* child = UI::dashRoot->GetLastChild();
        if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer( child ) && strcmp(child->GetID(), "McDotaMain") == 0 ){
            MC_PRINTF("Grabbing existing child McDotaMain\n");
            UI::mcDota = child;
        }
    }
    /* Create our custom panel */
    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer( UI::mcDota ) ){
        MC_PRINTF("Creating McDota Panel...\n");
        // Get rid of newlines, they mess up the javascript syntax
        std::replace(mainXML.begin(), mainXML.end(), '\n', ' ');
        snprintf(jsCode, JS_MAX, cuckProtocol, mainXML.c_str());

        panorama::CPanoramaSymbol type = panoramaEngine->AccessUIEngine()->MakeSymbol("Panel");
        UI::mcDota = panoramaEngine->AccessUIEngine()->CreatePanel(&type, "McDotaMain", root)->panel;
        MC_PRINTF("Root ID: %s\n", root->GetID());
        UI::mcDota->SetParent( root );
    }
    if( !UI::mcDota->HasBeenLayedOut() )
        panoramaEngine->AccessUIEngine()->RunScript(root, jsCode, engine->IsInGame() ? "panorama/layout/base_hud.xml" : "panorama/layout/base.xml", 8, 10, false);

    return true;
}

void UI::ToggleUI()
{
    SetupAndCheckPanels();

    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(UI::mcDota) ){
        MC_PRINTF_WARN("Something is wrong with our mcDota Panel Pointer(%p)\n", (void*)UI::mcDota);
        return;
    }
    if( !UI::mcDota->HasBeenLayedOut() ){
        MC_PRINTF_WARN("mcDota Panel not layed out yet. Try again.\n");
        return;
    }

    UI::mcDota->SetVisible(!UI::mcDota->IsVisible());

    /* Play Menu Open/Close sounds */
    if( UI::mcDota->IsVisible() )
        panoramaEngine->AccessUIEngine()->RunScript(UI::mcDota, "$.DispatchEvent( 'PlaySoundEffect', 'ui_menu_activate_open' );", engine->IsInGame() ? "panorama/layout/base_hud.xml" : "panorama/layout/base.xml", 8, 10, false );
    else
        panoramaEngine->AccessUIEngine()->RunScript(UI::mcDota, "$.DispatchEvent( 'PlaySoundEffect', 'ui_menu_activate_close' );", engine->IsInGame() ? "panorama/layout/base_hud.xml" : "panorama/layout/base.xml", 8, 10, false );

}