#include "Gui.h"

#include <algorithm>
#include <fstream>

#include "../Interfaces.h"

std::string mainXML =
#include "Main.xml"
;

// https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string gen_random(const int len)
{
    std::string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    srand((unsigned) time(NULL));

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;
}

static panorama::IUIPanel* GetHudRoot( ){
    panorama::IUIPanel *itr = nullptr;

    for( int i = 0; i < 4096; i++ ) {
        itr = panoramaEngine->AccessUIEngine( )->GetPanelArray( )->slots[i].panel;

        if ( !panoramaEngine->AccessUIEngine( )->IsValidPanelPointer( itr ) )
            continue;

        while ( itr && panoramaEngine->AccessUIEngine( )->IsValidPanelPointer( itr ) ) {
            if ( !strcasecmp( itr->GetID( ), "DOTAHud" ) ) {
                return itr;
            }
            itr = itr->GetParent();
        }
    }
    return nullptr;
}

static bool SetupAndCheckPanels()
{
    static std::string xmlFile = "/tmp/";
    static bool bFirst = true;
    // Dump our XML to file, then make the game load it, nice and EZ
    if( bFirst )
    {
        xmlFile += gen_random(6);
        xmlFile += ".xml";

        std::ofstream out(xmlFile);
        out << mainXML;
        out.close();

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

        panorama::CPanoramaSymbol type = panoramaEngine->AccessUIEngine()->MakeSymbol("Panel");
        UI::mcDota = panoramaEngine->AccessUIEngine()->CreatePanel(&type, "McDotaMain", root)->panel;
        MC_PRINTF("Root ID: %s\n", root->GetID());
        UI::mcDota->SetParent( root );
    }
    // Load the file, then delete it
    if( !UI::mcDota->HasBeenLayedOut() )
    {
        std::string fileStr = "file://" + xmlFile;
        UI::mcDota->LoadLayoutFile(fileStr.c_str(), true);
        remove(xmlFile.c_str());
    }

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