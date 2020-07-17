#pragma once

#include "color.h"

// Calls tier0.dll's export to output a message to the console. Uses printf style parameters.
// Gets resolved at run-time

// This is a nice safe way to output to the console without any requirements.
void ConMsg( const char *format, ... );

// Update with Aghanim's Labyrinth - Valve has removed the printing functions in ICvar.
// Use exported ConColorMsg in tier0
void ConColorMsg( const Color &color, const char *format, ... );