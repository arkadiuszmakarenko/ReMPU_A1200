#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>


#define KEY_PRESSED_MAX 10


typedef struct {
	uint8_t lami;
	uint8_t lalt;
	uint8_t lshf;
	uint8_t ctrl;
	uint8_t rami;
	uint8_t ralt;
	uint8_t rshf;
} special_keys_t;



typedef struct{
	uint32_t keyboard_matrix[6];
	special_keys_t special_keys;
} keyboard_t;

#define KEYCODE_TAB_SIZE 86 //Still 2 to find codes for
//0x70



//X,Y,Amiga Code
static const uint8_t amigacode[KEYCODE_TAB_SIZE][3] =
{
	{2,	14,		0x45 }, // ESC
	{2,	13,		0x68 }, // NUMLOCK & CLEAR NUM(
	{2,	12,		0x50 }, // F1
	{2,	11,		0x51 }, // F2
	{2,	10,		0x52 }, // F3
	{2,	9,		0x53 }, // F4
	{2,	8,		0x54 }, // F5
	{2,	6,		0x55 }, // F6
	{2,	5,		0x5C }, // NUM/
	{2,	4,		0x56 }, // F7
	{2,	3,		0x57 }, // F8
	{2,	2,		0x58 }, // F9
	{2,	1,		0x59 }, // F10
	{2, 0,		0x5F }, // HELP

	{3,	14, 	0x00 }, // ~
	{3,	13, 	0x01 }, // 1!
	{3,	12, 	0x02 }, // 2@
	{3,	11, 	0x03 }, // 3#
	{3,	10, 	0x04 }, // 4$
	{3,	9,	 	0x05 }, // 5%
	{3,	8, 		0x06 }, // 6^
	{3, 7,      0x07 }, // 7&
	{3,	6,		0x08 }, // 8*
	{3,	5,		0x09 }, // 9(
	{3,	4,		0x0A }, // 0)
	{3,	3,		0x0B }, // -_
	{3,	2,		0x0C }, // +=
	{3,	1,		0x0D }, // |
	{3, 0,      0x4C }, // CURSOR U


	{4,	14,		0x42 }, // TAB
	{4,	13,		0x10 }, // Q
	{4,	12,		0x11 }, // W
	{4,	11,		0x12 }, // E
	{4,	10,		0x13 }, // R
	{4,	9,		0x14 }, // T
	{4,	8,		0x15 }, // Y
	{4,	7,		0x16 }, // U
	{4,	6,		0x17 }, // I
	{4,	5,		0x18 }, // O
	{4,	4,		0x19 }, // P
	{4,	3,		0x1A }, // [{
	{4,	2,		0x1B }, // }]
	{4,	1,		0x2B }, // RETURN
	{4,	0,		0x4F }, // CURSOR L


	{5,	14,		0x62 }, // CAPS LOCK
	{5,	13,		0x20 }, // A
	{5,	12,		0x21 }, // S
	{5,	11,		0x22 }, // D
	{5,	10,		0x23 }, // F
	{5,	9,		0x24 }, // G
	{5,	8,		0x25 }, // H
	{5,	7,		0x26 }, // J
	{5,	6,		0x27 }, // K
	{5,	5,		0x28 }, // L
	{5, 4,		0x29 }, // :;
	{5,	3,		0x2A }, // "'
	//5,2  EUR ?? // Y2
	{5,	1,		0x46 }, // DEL
	{5,	0,		0x4E }, // CURSOR R

	//EUL
	{6,	13,		0x31 }, // Z
	{6,	12,		0x32 }, // X
	{6,	11,		0x33 }, // C
	{6,	10,		0x34 }, // V
	{6,	9,		0x35 }, // B
	{6,	8,		0x36 }, // N
	{6,	7,		0x37 }, // M
	{6,	6,		0x38 }, // <,
	{6,	5,		0x39 }, // >.
	{6,	4,		0x3A }, // ?/
	//6,3 NA
	{6,	2,		0x40 }, // SPACE
	{6,	1,		0x41 }, // BACKSPACE
	{6,	0,		0x4D }, // CURSOR D

	{7, 14,     0x5D }, // NUM *
	{7,	13,     0x5E }, // NUM +
	{7,	12,		0x3F }, // NUM 9
	{7,	11,		0x2F }, // NUM 6
	{7,	10,		0x1F }, // NUM 3
	{7,	9,		0x38 }, // NUM ,
	{7,	8,		0x3E }, // NUM 8
	{7,	7,		0x2E }, // NUM 5
	{7,	6,		0x1E }, // NUM 2
	{7,	5,		0x44 }, // <Enter>
	{7,	4,		0x3D }, // NUM 7
	{7,	3,		0x2D }, // NUM 4
	{7,	2,		0x1D }, // NUM 1
	{7,	1,		0x0F }, // NUM 0
	{7,	0,		0x4A }, // NUM -
} ;





/*
	{0x30 }, // <SHIFT> international?
	//{0x43 }, // ENTER
	{KEY_LEFTSHIFT,              0x60 }, // LSHIFT
	{KEY_RIGHTSHIFT,             0x61 }, // RSHIFT

	{KEY_LEFTCONTROL,            0x63 }, // LCTRL
	{KEY_LEFTALT,                0x64 }, // LALT
	{KEY_RIGHTALT,               0x65 }, // RALT
	{KEY_LEFT_GUI,               0x66 }, // LWIN
	{KEY_RIGHT_GUI,              0x67 }, // RWIN
	{KEY_APPLICATION,            0x5F }, // APP - HELP
	{KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE, 0x3C }, // KEYPAD '.'

	{KEY_PRINTSCREEN,            0x0E }, // SPARE
	{KEY_SCROLL_LOCK,            0x1C }, // SPARE
	{KEY_PAUSE,                  0x2C }, // SPARE
	{KEY_HOME,                   0x3B }, // SPARE
	{KEY_PAGEUP,                 0x3F }, // PGUP
	{KEY_PAGEDOWN,               0x1F }, // PGDOWN

*/


/*
	{KEY_GRAVE_ACCENT_AND_TILDE, 0x00 }, // ~
	{KEY_1_EXCLAMATION_MARK,     0x01 }, // 1!
	{KEY_2_AT,                   0x02 }, // 2@
	{KEY_3_NUMBER_SIGN,          0x03 }, // 3#
	{KEY_4_DOLLAR,               0x04 }, // 4$
	{KEY_5_PERCENT,              0x05 }, // 5%
	{KEY_6_CARET,                0x06 }, // 6^
	{KEY_7_AMPERSAND,            0x07 }, // 7&
	{KEY_8_ASTERISK,             0x08 }, // 8*
	{KEY_9_OPARENTHESIS,         0x09 }, // 9(
	{KEY_0_CPARENTHESIS,         0x0A }, // 0)
	{KEY_MINUS_UNDERSCORE,       0x0B }, // -_
	{KEY_EQUAL_PLUS,             0x0C }, // +=
	{KEY_BACKSLASH_VERTICAL_BAR, 0x0D }, // |
	{KEY_KEYPAD_0_INSERT,        0x0F }, // NUM 0
	{KEY_Q,                      0x10 }, // Q
	{KEY_W,                      0x11 }, // W
	{KEY_E,                      0x12 }, // E
	{KEY_R,                      0x13 }, // R
	{KEY_T,                      0x14 }, // T
	{KEY_Y,                      0x15 }, // Y
	{KEY_U,                      0x16 }, // U
	{KEY_I,                      0x17 }, // I
	{KEY_O,                      0x18 }, // O
	{KEY_P,                      0x19 }, // P
	{KEY_OBRACKET_AND_OBRACE,    0x1A }, // [{
	{KEY_CBRACKET_AND_CBRACE,    0x1B }, // }]
	{KEY_KEYPAD_1_END,           0x1D }, // NUM 1
	{KEY_KEYPAD_2_DOWN_ARROW,    0x1E }, // NUM 2
	{KEY_KEYPAD_3_PAGEDN,        0x1F }, // NUM 3
	{KEY_A,                      0x20 }, // A
	{KEY_S,                      0x21 }, // S
	{KEY_D,                      0x22 }, // D
	{KEY_F,                      0x23 }, // F
	{KEY_G,                      0x24 }, // G
	{KEY_H,                      0x25 }, // H
	{KEY_J,                      0x26 }, // J
	{KEY_K,                      0x27 }, // K
	{KEY_L,                      0x28 }, // L
	{KEY_SEMICOLON_COLON,        0x29 }, // :;
	{KEY_SINGLE_AND_DOUBLE_QUOTE,0x2A }, // "'
	{KEY_ENTER,                  0x44 }, // <Enter>
	{KEY_KEYPAD_4_LEFT_ARROW,    0x2D }, // NUM 4
	{KEY_KEYPAD_5,               0x2E }, // NUM 5
	{KEY_KEYPAD_6_RIGHT_ARROW,   0x2F }, // NUM 6
	{KEY_INTERNATIONAL2,         0x30 }, // <SHIFT> international?
	{KEY_Z,                      0x31 }, // Z
	{KEY_X,                      0x32 }, // X
	{KEY_C,                      0x33 }, // C
	{KEY_V,                      0x34 }, // V
	{KEY_B,                      0x35 }, // B
	{KEY_N,                      0x36 }, // N
	{KEY_M,                      0x37 }, // M
	{KEY_COMMA_AND_LESS,         0x38 }, // <,
	{KEY_KEYPAD_COMMA,           0x38 }, // NUM ,
	{KEY_DOT_GREATER,            0x39 }, // >.
	{KEY_SLASH_QUESTION,         0x3A }, // ?/
	{KEY_KEYPAD_7_HOME,          0x3D }, // NUM 7
	{KEY_KEYPAD_8_UP_ARROW,      0x3E }, // NUM 8
	{KEY_KEYPAD_9_PAGEUP,        0x3F }, // NUM 9
	{KEY_SPACEBAR,               0x40 }, // SPACE
	{KEY_BACKSPACE,              0x41 }, // BACKSPACE
	{KEY_TAB,                    0x42 }, // TAB
	{KEY_KEYPAD_ENTER,           0x43 }, // ENTER
	{KEY_RETURN,                 0x2B }, // RETURN
	{KEY_ESCAPE,                 0x45 }, // ESC
	{KEY_DELETE,                 0x46 }, // DEL
	{KEY_KEYPAD_MINUS,           0x4A }, // NUM -
	{KEY_UPARROW,                0x4C }, // CURSOR U
	{KEY_DOWNARROW,              0x4D }, // CURSOR D
	{KEY_RIGHTARROW,             0x4E }, // CURSOR R
	{KEY_LEFTARROW,              0x4F }, // CURSOR L
	{KEY_F1,                     0x50 }, // F1
	{KEY_F2,                     0x51 }, // F2
	{KEY_F3,                     0x52 }, // F3
	{KEY_F4,                     0x53 }, // F4
	{KEY_F5,                     0x54 }, // F5
	{KEY_F6,                     0x55 }, // F6
	{KEY_F7,                     0x56 }, // F7
	{KEY_F8,                     0x57 }, // F8
	{KEY_F9,                     0x58 }, // F9
	{KEY_F10,                    0x59 }, // F10
	{KEY_KEYPAD_SLASH,           0x5C }, // /
	{KEY_KEYPAD_ASTERIKS,        0x5D }, // NUM *
	{KEY_KEYPAD_PLUS,            0x5E }, // NUM +
	{KEY_F12,                    0x5F }, // HELP
	{KEY_LEFTSHIFT,              0x60 }, // LSHIFT
	{KEY_RIGHTSHIFT,             0x61 }, // RSHIFT
	{KEY_CAPS_LOCK,              0x62 }, // CAPS
	{KEY_LEFTCONTROL,            0x63 }, // LCTRL
	{KEY_LEFTALT,                0x64 }, // LALT
	{KEY_RIGHTALT,               0x65 }, // RALT
	{KEY_LEFT_GUI,               0x66 }, // LWIN
	{KEY_RIGHT_GUI,              0x67 }, // RWIN
	{KEY_APPLICATION,            0x5F }, // APP - HELP
	{KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE, 0x3C }, // KEYPAD '.'
	{KEY_KEYPAD_NUM_LOCK_AND_CLEAR, 0x68 }, // NUMLOCK & CLEAR
	{KEY_PRINTSCREEN,            0x0E }, // SPARE
	{KEY_SCROLL_LOCK,            0x1C }, // SPARE
	{KEY_PAUSE,                  0x2C }, // SPARE
	{KEY_HOME,                   0x3B }, // SPARE
	{KEY_PAGEUP,                 0x3F }, // PGUP
	{KEY_PAGEDOWN,               0x1F }, // PGDOWN
	{KEY_END1,                   0x49 }, // SPARE
	{KEY_INSERT,                 0x4B }, // SPARE
	{KEY_NONE,                   0x5B }, // SPARE
	{KEY_NONE,                   0x6A }, // SPARE
	{KEY_NONE,                   0x6B }, // SPARE
	{KEY_NONE,                   0x6C }, // SPARE
	{KEY_NONE,                   0x6D }, // SPARE
	{KEY_NONE,                   0x6E }, // SPARE
	{KEY_NONE,                   0x6F }, // SPARE
*/

keyboard_t Read_Keyboard(void);

