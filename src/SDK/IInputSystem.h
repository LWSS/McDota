#pragma once
#include "vector.h"
#include "IAppSystem.h"

#define MAX_SPLITSCREEN_CLIENT_BITS 2
// this should == MAX_JOYSTICKS in InputEnums.h
#define MAX_SPLITSCREEN_CLIENTS	( 1 << MAX_SPLITSCREEN_CLIENT_BITS ) // 4

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)
#define IN_SPEED		(1 << 17)
#define IN_WALK			(1 << 18)
#define IN_ZOOM			(1 << 19)
#define IN_WEAPON1		(1 << 20)
#define IN_WEAPON2		(1 << 21)
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)
#define IN_GRENADE2		(1 << 24)
#define	IN_ATTACK3		(1 << 25)

enum
{
	MAX_JOYSTICKS = MAX_SPLITSCREEN_CLIENTS,
	MOUSE_BUTTON_COUNT = 5,
};

enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

enum
{
	JOYSTICK_MAX_BUTTON_COUNT = 32,
	JOYSTICK_POV_BUTTON_COUNT = 4,
	JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2,
};

enum InputEventType_t : int
{
    IE_ButtonPressed = 0,	// m_nData contains a ButtonCode_t
    IE_ButtonReleased,		// m_nData contains a ButtonCode_t
    IE_ButtonDoubleClicked,	// m_nData contains a ButtonCode_t
    IE_AnalogValueChanged,	// m_nData contains an AnalogCode_t, m_nData2 contains the value

    IE_FirstSystemEvent = 100,
    IE_Quit = IE_FirstSystemEvent,
    IE_ControllerInserted,	// m_nData contains the controller ID
    IE_ControllerUnplugged,	// m_nData contains the controller ID

    IE_FirstVguiEvent = 1000,	// Assign ranges for other systems that post user events here
    IE_FirstAppEvent = 2000,
};

struct InputEvent_t
{
    InputEventType_t m_nType;   // Type of the event (see InputEventType_t)
    int m_nTick;				// Tick on which the event occurred
    int m_nData;				// Generic 32-bit data, what it contains depends on the event
    int m_nData2;				// Generic 32-bit data, what it contains depends on the event
    int m_nData3;				// Generic 32-bit data, what it contains depends on the event
};

/* Updated for Source 2
 * Generated with
 * for( int key = ButtonCode_t::KEY_FIRST; key <= 512; key++ ) // ( note: values too high cause crash )
        cvar->ConsoleDPrintf( "%s = %d,\n",inputSystem->ButtonCodeToString( (ButtonCode_t)key ), key );
 */
enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

    KEY_0 = 1,
    KEY_1 = 2,
    KEY_2 = 3,
    KEY_3 = 4,
    KEY_4 = 5,
    KEY_5 = 6,
    KEY_6 = 7,
    KEY_7 = 8,
    KEY_8 = 9,
    KEY_9 = 10,
    A = 11,
    B = 12,
    C = 13,
    D = 14,
    E = 15,
    F = 16,
    G = 17,
    H = 18,
    I = 19,
    J = 20,
    K = 21,
    L = 22,
    M = 23,
    N = 24,
    O = 25,
    P = 26,
    Q = 27,
    R = 28,
    S = 29,
    T = 30,
    U = 31,
    V = 32,
    W = 33,
    X = 34,
    Y = 35,
    Z = 36,
    KP_0 = 37,
    KP_1 = 38,
    KP_2 = 39,
    KP_3 = 40,
    KP_4 = 41,
    KP_5 = 42,
    KP_6 = 43,
    KP_7 = 44,
    KP_8 = 45,
    KP_9 = 46,
    KP_DIVIDE = 47,
    KP_MULTIPLY = 48,
    KP_MINUS = 49,
    KP_PLUS = 50,
    KP_ENTER = 51,
    KP_DEL = 52,
    LESSTHAN = 53,
    LBRACKET = 54,
    RBRACKET = 55,
    SEMICOLON = 56,
    APOSTROPHE = 57,
    BACKQUOTE = 58,
    COMMA = 59,
    PERIOD = 60,
    SLASH = 61,
    BACKSLASH = 62,
    MINUS = 63,
    EQUAL = 64,
    ENTER = 65,
    SPACE = 66,
    BACKSPACE = 67,
    TAB = 68,
    CAPSLOCK = 69,
    NUMLOCK = 70,
    ESCAPE = 71,
    SCROLLLOCK = 72,
    INSERT = 73,
    DELETE = 74,
    HOME = 75,
    END = 76,
    PGUP = 77,
    PGDN = 78,
    PAUSE = 79,
    SHIFT = 80,
    RSHIFT = 81,
    ALT = 82,
    RALT = 83,
    CTRL = 84,
    RCTRL = 85,
    LWIN = 86,
    RWIN = 87,
    APP = 88,
    UPARROW = 89,
    LEFTARROW = 90,
    DOWNARROW = 91,
    RIGHTARROW = 92,
    F1 = 93,
    F2 = 94,
    F3 = 95,
    F4 = 96,
    F5 = 97,
    F6 = 98,
    F7 = 99,
    F8 = 100,
    F9 = 101,
    F10 = 102,
    F11 = 103,
    F12 = 104,
    CAPSLOCKTOGGLE = 105,
    NUMLOCKTOGGLE = 106,
    SCROLLLOCKTOGGLE = 107,
    AC_BACK = 108,
    AC_BOOKMARKS = 109,
    AC_FORWARD = 110,
    AC_HOME = 111,
    AC_REFRESH = 112,
    AC_SEARCH = 113,
    AC_STOP = 114,
    AGAIN = 115,
    ALTERASE = 116,
    AMPERSAND = 117,
    ASTERISK = 118,
    AT = 119,
    AUDIOMUTE = 120,
    AUDIONEXT = 121,
    AUDIOPLAY = 122,
    AUDIOPREV = 123,
    AUDIOSTOP = 124,
    BRIGHTNESSDOWN = 125,
    BRIGHTNESSUP = 126,
    CALCULATOR = 127,
    CANCEL = 128,
    CARET = 129,
    CLEAR = 130,
    CLEARAGAIN = 131,
    COLON = 132,
    COMPUTER = 133,
    COPY = 134,
    CRSEL = 135,
    CURRENCYSUBUNIT = 136,
    CURRENCYUNIT = 137,
    CUT = 138,
    DECIMALSEPARATOR = 139,
    DISPLAYSWITCH = 140,
    DOLLAR = 141,
    EJECT = 142,
    EXCLAIM = 143,
    EXECUTE = 144,
    EXSEL = 145,
    F13 = 146,
    F14 = 147,
    F15 = 148,
    F16 = 149,
    F17 = 150,
    F18 = 151,
    F19 = 152,
    F20 = 153,
    F21 = 154,
    F22 = 155,
    F23 = 156,
    F24 = 157,
    FIND = 158,
    GREATER = 159,
    HASH = 160,
    HELP = 161,
    KBDILLUMDOWN = 162,
    KBDILLUMTOGGLE = 163,
    KBDILLUMUP = 164,
    KP_00 = 165,
    KP_000 = 166,
    KP_A = 167,
    KP_AMPERSAND = 168,
    KP_AT = 169,
    KP_B = 170,
    KP_BACKSPACE = 171,
    KP_BINARY = 172,
    KP_C = 173,
    KP_CLEAR = 174,
    KP_CLEARENTRY = 175,
    KP_COLON = 176,
    KP_COMMA = 177,
    KP_D = 178,
    KP_DBLAMPERSAND = 179,
    KP_DBLVERTICALBAR = 180,
    KP_DECIMAL = 181,
    KP_E = 182,
    KP_EQUALS = 183,
    KP_EQUALSAS400 = 184,
    KP_EXCLAM = 185,
    KP_F = 186,
    KP_GREATER = 187,
    KP_HASH = 188,
    KP_HEXADECIMAL = 189,
    KP_LEFTBRACE = 190,
    KP_LEFTPAREN = 191,
    KP_LESS = 192,
    KP_MEMADD = 193,
    KP_MEMCLEAR = 194,
    KP_MEMDIVIDE = 195,
    KP_MEMMULTIPLY = 196,
    KP_MEMRECALL = 197,
    KP_MEMSTORE = 198,
    KP_MEMSUBTRACT = 199,
    KP_OCTAL = 200,
    KP_PERCENT = 201,
    KP_PLUSMINUS = 202,
    KP_POWER = 203,
    KP_RIGHTBRACE = 204,
    KP_RIGHTPAREN = 205,
    KP_SPACE = 206,
    KP_TAB = 207,
    KP_VERTICALBAR = 208,
    KP_XOR = 209,
    LEFTPAREN = 210,
    MAIL = 211,
    MEDIASELECT = 212,
    MODE = 213,
    MUTE = 214,
    OPER = 215,
    OUT = 216,
    PASTE = 217,
    PERCENT = 218,
    PLUS = 219,
    POWER = 220,
    PRINTSCREEN = 221,
    PRIOR = 222,
    QUESTION = 223,
    QUOTEDBL = 224,
    RETURN2 = 225,
    RIGHTPAREN = 226,
    SELECT = 227,
    SEPARATOR = 228,
    SLEEP = 229,
    STOP = 230,
    SYSREQ = 231,
    THOUSANDSSEPARATOR = 232,
    UNDERSCORE = 233,
    UNDO = 234,
    VOLUMEDOWN = 235,
    VOLUMEUP = 236,
    WWW = 237,
    INVERTED_EXCLAMATION_MARK = 238,
    CENT_SIGN = 239,
    POUND_SIGN = 240,
    CURRENCY_SIGN = 241,
    YEN_SIGN = 242,
    BROKEN_BAR = 243,
    SECTION_SIGN = 244,
    DIAERESIS = 245,
    COPYRIGHT_SIGN = 246,
    FEMININE_ORDINAL_INDICATOR = 247,
    LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK = 248,
    NOT_SIGN = 249,
    REGISTERED_SIGN = 250,
    MACRON = 251,
    DEGREE_SIGN = 252,
    DEGREE_SYMBOL = 253,
    PLUS_MINUS_SIGN = 254,
    SUPERSCRIPT_TWO = 255,
    SUPERSCRIPT_THREE = 256,
    ACUTE_ACCENT = 257,
    MICRO_SIGN = 258,
    PILCROW_SIGN = 259,
    MIDDLE_DOT = 260,
    CEDILLA = 261,
    SUPERSCRIPT_ONE = 262,
    MASCULINE_ORDINAL_INDICATOR = 263,
    RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK = 264,
    VULGAR_FRACTION_ONE_QUARTER = 265,
    VULGAR_FRACTION_ONE_HALF = 266,
    VULGAR_FRACTION_THREE_QUARTERS = 267,
    INVERTED_QUESTION_MARK = 268,
    MULTIPLICATION_SIGN = 269,
    SHARP_S = 270,
    A_WITH_GRAVE = 271,
    A_WITH_ACUTE = 272,
    A_WITH_CIRCUMFLEX = 273,
    A_WITH_TILDE = 274,
    A_WITH_DIAERESIS = 275,
    A_WITH_RING_ABOVE = 276,
    AE = 277,
    C_WITH_CEDILLA = 278,
    E_WITH_GRAVE = 279,
    E_WITH_ACUTE = 280,
    E_WITH_CIRCUMFLEX = 281,
    E_WITH_DIAERESIS = 282,
    I_WITH_GRAVE = 283,
    I_WITH_ACUTE = 284,
    I_WITH_CIRCUMFLEX = 285,
    I_WITH_DIAERESIS = 286,
    ETH = 287,
    N_WITH_TILDE = 288,
    O_WITH_GRAVE = 289,
    O_WITH_ACUTE = 290,
    O_WITH_CIRCUMFLEX = 291,
    O_WITH_TILDE = 292,
    O_WITH_DIAERESIS = 293,
    DIVISION_SIGN = 294,
    O_WITH_STROKE = 295,
    U_WITH_GRAVE = 296,
    U_WITH_ACUTE = 297,
    U_WITH_CIRCUMFLEX = 298,
    U_WITH_DIAERESIS = 299,
    Y_WITH_ACUTE = 300,
    THORN = 301,
    Y_WITH_DIAERESIS = 302,
    EURO_SIGN = 303,
    TILDE = 304,
    LEFT_CURLY_BRACKET = 305,
    RIGHT_CURLY_BRACKET = 306,
    VERTICAL_BAR = 307,
    KEY_CYRILLIC_YU = 308,
    KEY_CYRILLIC_E = 309,
    KEY_CYRILLIC_HARD_SIGN = 310,
    KEY_CYRILLIC_HA = 311,
    KEY_CYRILLIC_IO = 312,
    KEY_CYRILLIC_ZHE = 313,
    KEY_CYRILLIC_BE = 314,
    MOUSE1 = 315,
    MOUSE2 = 316,
    MOUSE3 = 317,
    MOUSE4 = 318,
    MOUSE5 = 319,
    MWHEELUP = 320,
    MWHEELDOWN = 321,
    JOY1 = 322,
    JOY2 = 323,
    JOY3 = 324,
    JOY4 = 325,
    JOY5 = 326,
    JOY6 = 327,
    JOY7 = 328,
    JOY8 = 329,
    JOY9 = 330,
    JOY10 = 331,
    JOY11 = 332,
    JOY12 = 333,
    JOY13 = 334,
    JOY14 = 335,
    JOY15 = 336,
    JOY16 = 337,
    JOY17 = 338,
    JOY18 = 339,
    JOY19 = 340,
    JOY20 = 341,
    JOY21 = 342,
    JOY22 = 343,
    JOY23 = 344,
    JOY24 = 345,
    JOY25 = 346,
    JOY26 = 347,
    JOY27 = 348,
    JOY28 = 349,
    JOY29 = 350,
    JOY30 = 351,
    JOY31 = 352,
    JOY32 = 353,

	LAST_KEY_VALUE
};

enum MouseCodeState_t
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED,
	BUTTON_DOUBLECLICKED,
};

struct CUserCmd
{
	void *vtable;
	int32_t command_number;
	int32_t tick_count;
	Vector viewangles;
	Vector aimdirection; // sidemove/forwardmove for camera
	int32_t buttons;
    int32_t unk;
	unsigned char impulse;
	int32_t weaponselect; //0x0034
	int32_t weaponsubtype; //0x0038
	int32_t randomSeed; //0x003C
	short mouseX; //left-right [0->512)
	short mouseY; //up-down [0->384)
	short _pad;
	short cameraWorldX; // left-right camera pos in world
	short cameraWorldY; // forward-back camera pos in world.
	char _pad2[6]; // some scoreboard/shop stuff
	Vector CursorRay; // where cursor hits in world
};

struct PlatWindow_t__;
struct OsSpecificWindowHandle_t__;
struct InputStandardCursor_t;
struct InputCursorHandle_t;
typedef int AnalogCode_t;
struct InputEvent_t;

// xref "CInputSystem::AttachToWindow" to AttachToWindow()
class IInputSystem : public IAppSystem
{
public:
	// Attach, detach input system from a particular window
	// This window should be the root window for the application
	// Only 1 window should be attached at any given time.
	virtual void AttachToWindow( OsSpecificWindowHandle_t__* ) = 0;
	virtual void DetachFromWindow( OsSpecificWindowHandle_t__ * ) = 0;

	// Enables/disables input. PollInputState will not update current
	// button/analog states when it is called if the system is disabled.
	virtual void EnableInput( bool state ) = 0;

	// Enables/disables the windows message pump. PollInputState will not
	// Peek/Dispatch messages if this is disabled
	virtual void EnableMessagePump( bool state ) = 0;

	virtual void PollInputState( bool ) = 0;
	// Gets time of last polling in ms
	[[nodiscard]] virtual int GetPollTick( void ) const = 0;

	virtual bool IsButtonDown( ButtonCode_t code ) = 0;

	virtual int GetButtonPressedTick( ButtonCode_t code ) = 0;
	virtual int GetButtonReleasedTick( ButtonCode_t code ) = 0;
	// Gets the value of an analog input device this frame
	// Includes joysticks, mousewheel, mouse
	virtual int GetAnalogValue( AnalogCode_t code ) = 0;
	virtual int GetAnalogDelta( AnalogCode_t code ) = 0;

	virtual void sub_10920() = 0;
	virtual void sub_108F0() = 0;
	virtual void sub_10900() = 0;

	// Returns the input events since the last poll
	virtual int GetEventCount( void ) = 0;
	virtual InputEvent_t* GetEventData( void ) = 0;
	virtual void* GetEvents( void ) = 0;

	// Posts a user-defined event into the event queue; this is expected
	// to be called in overridden wndprocs connected to the root panel.
	virtual void PostUserEvent( const InputEvent_t &) = 0;
	virtual int GetJoystickCount( void ) = 0;

	// Enable/disable joystick, it has perf costs
	virtual void EnableJoystickInput( int nJoystick, bool state ) = 0;

	// Enable/disable diagonal joystick POV (simultaneous POV buttons down)
	virtual void EnableJoystickDiagonalPOV( int nJoystick, bool state ) = 0;

	// Sample the joystick and append events to the input queue
	virtual void SampleDevices( void ) = 0;

	virtual void SetRumble( float leftMotor, float rightMotor, int userId ) = 0;
	virtual void StopRumble( int userId ) = 0;

	virtual void ResetInputState( void ) = 0;
	// Sets a player as the primary user - all other controllers will be ignored.
	virtual void SetPrimaryUserID( int userId ) = 0;

	// Convert back + forth between ButtonCode/AnalogCode + strings
	virtual const char* CodeToString( ButtonCode_t code ) = 0;
	virtual const char* CodeToStringAnalog( AnalogCode_t code ) = 0;
	virtual ButtonCode_t StringToButtonCode( const char *) = 0;
	virtual AnalogCode_t StringToAnalogCode( const char *) = 0;

	// Sleeps until input happens. Pass a negative number to sleep infinitely
	virtual void SleepUntilInput( int maxSleepTimeMS = -1 ) = 0;

	virtual void VirtualKeyToButtonCode( int nVirtKey ) = 0;
	virtual int ButtonCodeToVirtualKey( ButtonCode_t code ) = 0;

	// How many times have we called PollInputState?
	virtual int GetPollCount( void ) = 0;

	virtual void SetCursorPosition( int x, int y, PlatWindow_t__ *window ) = 0;
	virtual void IsWindowAttached( PlatWindow_t__ * ) = 0;
	virtual void GetStandardCursor( InputStandardCursor_t ) = 0;
	virtual void SetStandardCursor( InputStandardCursor_t, InputCursorHandle_t *) = 0;
	virtual void sub_10A00() = 0;
	virtual void sub_10A20() = 0;
	virtual void sub_10A30() = 0;
	virtual void sub_11920() = 0;
	virtual void sub_11BC0() = 0;
	virtual void sub_15910() = 0;
	virtual void sub_12C50() = 0;
	virtual void sub_10B20() = 0;
	virtual void sub_11AC0() = 0;
	virtual void sub_10960() = 0;
	virtual void sub_13B40() = 0;
	virtual void sub_10A50() = 0;
	virtual void sub_11A80() = 0;
	virtual bool HasMouseFocus( void ) = 0;
	virtual void GetInputEventName( InputEventType_t ) = 0;
	virtual bool IsAppActive( void ) = 0;
	virtual bool IsXBoxControllerConnected( void ) = 0;
	virtual void StartDraggingWindow( OsSpecificWindowHandle_t__ *) = 0;
	virtual void SetCursorClip( PlatWindow_t__ * ) = 0;
	virtual void EnablePowerManagement( bool state ) = 0;
	virtual void EnableSystemCommands( unsigned int, bool ) = 0;
	virtual void SetMouseParams( const int *, int ) = 0;
	virtual void GetMouseParams( int *, int ) = 0;
	virtual void SetRelativeMouseMode( bool ) = 0;
	virtual void DebugSpew( void ) = 0;
	virtual char GetASCIICharForButtonPressed( const InputEvent_t & ) = 0;
	virtual unsigned int ButtonCodeToSDLKey( ButtonCode_t code ) = 0;
	virtual ButtonCode_t SDLKeyToButtonCode( unsigned int ) = 0;
	virtual void* CodeToLocalKeyNameUTF8( ButtonCode_t code ) = 0;
	virtual bool GetButtonCodeIsScanCode( void ) = 0;
	virtual void SetButtonCodeIsScanCode( bool state ) = 0;
	virtual void sub_117F0() = 0;
	virtual void sub_10A90() = 0;
	virtual void IME_Stuff() = 0;
	virtual void sub_10E30() = 0;
	virtual void sub_10E90() = 0;
	virtual void sub_10AA0() = 0;
	virtual void DESTROY() = 0;
	virtual void DESTROY2() = 0;

};

class IInputInternal;