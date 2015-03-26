#ifndef MRAGPP_INPUTKEYS_H_INCLUDED
#define MRAGPP_INPUTKEYS_H_INCLUDED

// Values taken from SDL_scancode.h

typedef enum
{
    MKEY_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /*@{*/

    MKEY_A = 4,
    MKEY_B = 5,
    MKEY_C = 6,
    MKEY_D = 7,
    MKEY_E = 8,
    MKEY_F = 9,
    MKEY_G = 10,
    MKEY_H = 11,
    MKEY_I = 12,
    MKEY_J = 13,
    MKEY_K = 14,
    MKEY_L = 15,
    MKEY_M = 16,
    MKEY_N = 17,
    MKEY_O = 18,
    MKEY_P = 19,
    MKEY_Q = 20,
    MKEY_R = 21,
    MKEY_S = 22,
    MKEY_T = 23,
    MKEY_U = 24,
    MKEY_V = 25,
    MKEY_W = 26,
    MKEY_X = 27,
    MKEY_Y = 28,
    MKEY_Z = 29,

    MKEY_1 = 30,
    MKEY_2 = 31,
    MKEY_3 = 32,
    MKEY_4 = 33,
    MKEY_5 = 34,
    MKEY_6 = 35,
    MKEY_7 = 36,
    MKEY_8 = 37,
    MKEY_9 = 38,
    MKEY_0 = 39,

    MKEY_RETURN = 40,
    MKEY_ESCAPE = 41,
    MKEY_BACKSPACE = 42,
    MKEY_TAB = 43,
    MKEY_SPACE = 44,

    MKEY_MINUS = 45,
    MKEY_EQUALS = 46,
    MKEY_LEFTBRACKET = 47,
    MKEY_RIGHTBRACKET = 48,
    MKEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    MKEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate MKEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    MKEY_SEMICOLON = 51,
    MKEY_APOSTROPHE = 52,
    MKEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    MKEY_COMMA = 54,
    MKEY_PERIOD = 55,
    MKEY_SLASH = 56,

    MKEY_CAPSLOCK = 57,

    MKEY_F1 = 58,
    MKEY_F2 = 59,
    MKEY_F3 = 60,
    MKEY_F4 = 61,
    MKEY_F5 = 62,
    MKEY_F6 = 63,
    MKEY_F7 = 64,
    MKEY_F8 = 65,
    MKEY_F9 = 66,
    MKEY_F10 = 67,
    MKEY_F11 = 68,
    MKEY_F12 = 69,

    MKEY_PRINTSCREEN = 70,
    MKEY_SCROLLLOCK = 71,
    MKEY_PAUSE = 72,
    MKEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    MKEY_HOME = 74,
    MKEY_PAGEUP = 75,
    MKEY_DELETE = 76,
    MKEY_END = 77,
    MKEY_PAGEDOWN = 78,
    MKEY_RIGHT = 79,
    MKEY_LEFT = 80,
    MKEY_DOWN = 81,
    MKEY_UP = 82,

    MKEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    MKEY_KP_DIVIDE = 84,
    MKEY_KP_MULTIPLY = 85,
    MKEY_KP_MINUS = 86,
    MKEY_KP_PLUS = 87,
    MKEY_KP_ENTER = 88,
    MKEY_KP_1 = 89,
    MKEY_KP_2 = 90,
    MKEY_KP_3 = 91,
    MKEY_KP_4 = 92,
    MKEY_KP_5 = 93,
    MKEY_KP_6 = 94,
    MKEY_KP_7 = 95,
    MKEY_KP_8 = 96,
    MKEY_KP_9 = 97,
    MKEY_KP_0 = 98,
    MKEY_KP_PERIOD = 99,

    MKEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    MKEY_APPLICATION = 101, /**< windows contextual menu, compose */
    MKEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    MKEY_KP_EQUALS = 103,
    MKEY_F13 = 104,
    MKEY_F14 = 105,
    MKEY_F15 = 106,
    MKEY_F16 = 107,
    MKEY_F17 = 108,
    MKEY_F18 = 109,
    MKEY_F19 = 110,
    MKEY_F20 = 111,
    MKEY_F21 = 112,
    MKEY_F22 = 113,
    MKEY_F23 = 114,
    MKEY_F24 = 115,
    MKEY_EXECUTE = 116,
    MKEY_HELP = 117,
    MKEY_MENU = 118,
    MKEY_SELECT = 119,
    MKEY_STOP = 120,
    MKEY_AGAIN = 121,   /**< redo */
    MKEY_UNDO = 122,
    MKEY_CUT = 123,
    MKEY_COPY = 124,
    MKEY_PASTE = 125,
    MKEY_FIND = 126,
    MKEY_MUTE = 127,
    MKEY_VOLUMEUP = 128,
    MKEY_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     MKEY_LOCKINGCAPSLOCK = 130,  */
/*     MKEY_LOCKINGNUMLOCK = 131, */
/*     MKEY_LOCKINGSCROLLLOCK = 132, */
    MKEY_KP_COMMA = 133,
    MKEY_KP_EQUALSAS400 = 134,

    MKEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    MKEY_INTERNATIONAL2 = 136,
    MKEY_INTERNATIONAL3 = 137, /**< Yen */
    MKEY_INTERNATIONAL4 = 138,
    MKEY_INTERNATIONAL5 = 139,
    MKEY_INTERNATIONAL6 = 140,
    MKEY_INTERNATIONAL7 = 141,
    MKEY_INTERNATIONAL8 = 142,
    MKEY_INTERNATIONAL9 = 143,
    MKEY_LANG1 = 144, /**< Hangul/English toggle */
    MKEY_LANG2 = 145, /**< Hanja conversion */
    MKEY_LANG3 = 146, /**< Katakana */
    MKEY_LANG4 = 147, /**< Hiragana */
    MKEY_LANG5 = 148, /**< Zenkaku/Hankaku */
    MKEY_LANG6 = 149, /**< reserved */
    MKEY_LANG7 = 150, /**< reserved */
    MKEY_LANG8 = 151, /**< reserved */
    MKEY_LANG9 = 152, /**< reserved */

    MKEY_ALTERASE = 153, /**< Erase-Eaze */
    MKEY_SYSREQ = 154,
    MKEY_CANCEL = 155,
    MKEY_CLEAR = 156,
    MKEY_PRIOR = 157,
    MKEY_RETURN2 = 158,
    MKEY_SEPARATOR = 159,
    MKEY_OUT = 160,
    MKEY_OPER = 161,
    MKEY_CLEARAGAIN = 162,
    MKEY_CRSEL = 163,
    MKEY_EXSEL = 164,

    MKEY_KP_00 = 176,
    MKEY_KP_000 = 177,
    MKEY_THOUSANDSSEPARATOR = 178,
    MKEY_DECIMALSEPARATOR = 179,
    MKEY_CURRENCYUNIT = 180,
    MKEY_CURRENCYSUBUNIT = 181,
    MKEY_KP_LEFTPAREN = 182,
    MKEY_KP_RIGHTPAREN = 183,
    MKEY_KP_LEFTBRACE = 184,
    MKEY_KP_RIGHTBRACE = 185,
    MKEY_KP_TAB = 186,
    MKEY_KP_BACKSPACE = 187,
    MKEY_KP_A = 188,
    MKEY_KP_B = 189,
    MKEY_KP_C = 190,
    MKEY_KP_D = 191,
    MKEY_KP_E = 192,
    MKEY_KP_F = 193,
    MKEY_KP_XOR = 194,
    MKEY_KP_POWER = 195,
    MKEY_KP_PERCENT = 196,
    MKEY_KP_LESS = 197,
    MKEY_KP_GREATER = 198,
    MKEY_KP_AMPERSAND = 199,
    MKEY_KP_DBLAMPERSAND = 200,
    MKEY_KP_VERTICALBAR = 201,
    MKEY_KP_DBLVERTICALBAR = 202,
    MKEY_KP_COLON = 203,
    MKEY_KP_HASH = 204,
    MKEY_KP_SPACE = 205,
    MKEY_KP_AT = 206,
    MKEY_KP_EXCLAM = 207,
    MKEY_KP_MEMSTORE = 208,
    MKEY_KP_MEMRECALL = 209,
    MKEY_KP_MEMCLEAR = 210,
    MKEY_KP_MEMADD = 211,
    MKEY_KP_MEMSUBTRACT = 212,
    MKEY_KP_MEMMULTIPLY = 213,
    MKEY_KP_MEMDIVIDE = 214,
    MKEY_KP_PLUSMINUS = 215,
    MKEY_KP_CLEAR = 216,
    MKEY_KP_CLEARENTRY = 217,
    MKEY_KP_BINARY = 218,
    MKEY_KP_OCTAL = 219,
    MKEY_KP_DECIMAL = 220,
    MKEY_KP_HEXADECIMAL = 221,

    MKEY_LCTRL = 224,
    MKEY_LSHIFT = 225,
    MKEY_LALT = 226, /**< alt, option */
    MKEY_LGUI = 227, /**< windows, command (apple), meta */
    MKEY_RCTRL = 228,
    MKEY_RSHIFT = 229,
    MKEY_RALT = 230, /**< alt gr, option */
    MKEY_RGUI = 231, /**< windows, command (apple), meta */

    MKEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /*@}*//*Usage page 0x07*/

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /*@{*/

    MKEY_AUDIONEXT = 258,
    MKEY_AUDIOPREV = 259,
    MKEY_AUDIOSTOP = 260,
    MKEY_AUDIOPLAY = 261,
    MKEY_AUDIOMUTE = 262,
    MKEY_MEDIASELECT = 263,
    MKEY_WWW = 264,
    MKEY_MAIL = 265,
    MKEY_CALCULATOR = 266,
    MKEY_COMPUTER = 267,
    MKEY_AC_SEARCH = 268,
    MKEY_AC_HOME = 269,
    MKEY_AC_BACK = 270,
    MKEY_AC_FORWARD = 271,
    MKEY_AC_STOP = 272,
    MKEY_AC_REFRESH = 273,
    MKEY_AC_BOOKMARKS = 274,

    /*@}*//*Usage page 0x0C*/

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /*@{*/

    MKEY_BRIGHTNESSDOWN = 275,
    MKEY_BRIGHTNESSUP = 276,
    MKEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    MKEY_KBDILLUMTOGGLE = 278,
    MKEY_KBDILLUMDOWN = 279,
    MKEY_KBDILLUMUP = 280,
    MKEY_EJECT = 281,
    MKEY_SLEEP = 282,

    MKEY_APP1 = 283,
    MKEY_APP2 = 284,

    /*@}*//*Walther keys*/

    /* Add any other keys here. */

    MKEY_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} MragppKeys;

#define MBUTTON_LEFT   0
#define MBUTTON_MIDDLE 1
#define MBUTTON_RIGHT  2
#define MBUTTON_X1     3
#define MBUTTON_X2     4
#define MBUTTON_COUNT  5

#define TOUCH_FINGER_COUNT 11

#endif
