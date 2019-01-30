#pragma once

class CDOTARichPresence;

typedef void (* SetRPStatusFn)( CDOTARichPresence *, const char * );
inline SetRPStatusFn SetRPStatus;

class CDOTARichPresence
{
public:
    // Sets Rich Status ( normally: finding game/in-game/lvl )
    // Will crash the program if you pass something it doesn't like.
    // Most of the time it requires a '#' as the first character
    //
    // Check out the english localization txt file ( dota_english.txt )
    // OR you can write your own like this "#Bazinga one two three"
    void SetStatus( const char *text )
    {
        SetRPStatus( this, text );
    }
};


