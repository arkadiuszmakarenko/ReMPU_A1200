#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "main.h"


#define KEYCODE_TAB_SIZE 89



//X,Y,Amiga Code
static const uint8_t amigacode[KEYCODE_TAB_SIZE][3] =
{
	{2,	14,		0x45 }, // ESC
	{2,	13,		0x5A }, // NUM(
	{2,	12,		0x50 }, // F1
	{2,	11,		0x51 }, // F2
	{2,	10,		0x52 }, // F3
	{2,	9,		0x53 }, // F4
	{2,	8,		0x54 }, // F5
	{2,	6,		0x55 }, // F6
	{2,	7,		0x5B }, // NUM)
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
	{4,	1,		0x44 }, // RETURN
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
	{5,	2,		0x2B }, // EUR EMPTY BUTTON NEAR RETURN
	{5,	1,		0x46 }, // DEL
	{5,	0,		0x4E }, // CURSOR R

	{6, 14,		0x30 }, //EUL EMPTY BUTTON NEAR SHIFT
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
	{7,	9,		0x3C }, // NUM ,
	{7,	8,		0x3E }, // NUM 8
	{7,	7,		0x2E }, // NUM 5
	{7,	6,		0x1E }, // NUM 2
	{7,	5,		0x43 }, // <Enter>
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



void ProcessKeyboard(keyboard_t *keyboard);

