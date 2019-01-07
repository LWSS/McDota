#pragma once

// Calls tier0.dll's export to output a message to the console. Uses printf style parameters.
// Gets resolved at run-time

// This is a nice safe way to output to the console without any requirements.
void ConMsg( const char *format, ... );