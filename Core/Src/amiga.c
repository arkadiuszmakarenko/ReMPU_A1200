#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "amiga.h"
#include "stm32f1xx.h"
#include "main.h"
#include "dwt_delay.h"





typedef enum {
	DAT_OUTPUT = 0,
	DAT_INPUT,
} kbd_dir;


static keyboard_t prevkeycode;

static unsigned char prev_keycode = 0xff;

static void amikb_direction(kbd_dir dir);
static void amikb_send(uint8_t code, int press);


// **************************
void amikb_startup(void)
{
	uint8_t AMIGA_INITPOWER = 0xFD; //11111101
	uint8_t AMIGA_TERMPOWER = 0xFE; //11111110

	// De-assert nRESET for Amiga...
	amikb_reset();

	amikb_direction(DAT_OUTPUT); // Default

	HAL_Delay(1000);             // wait for sync
	amikb_send((uint8_t) AMIGA_INITPOWER, 0); // send "initiate power-up"
	DWT_Delay(200);
	amikb_send((uint8_t) AMIGA_TERMPOWER, 0); // send "terminate power-up"


	memset(&prevkeycode.keyboard_codes,0xFF,sizeof(prevkeycode.keyboard_codes));
}



void amikb_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOB,
		KBD_CLOCK_Pin |
		KBD_DATA_Pin  |
		KBD_RESET_Pin, GPIO_PIN_SET);


	GPIO_InitStruct.Pin = KBD_CLOCK_Pin |KBD_DATA_Pin | KBD_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(KBD_RESET_GPIO_Port, KBD_RESET_Pin, GPIO_PIN_RESET); // Clear KBD_RESET pin

}


static void amikb_direction(kbd_dir dir)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO KBD_DAT, GPIO KBD_CLOCK as inputs and KBD_RESET as output */
	GPIO_InitStruct.Pin = KBD_CLOCK_Pin |KBD_DATA_Pin;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	switch (dir)
	{
		case DAT_INPUT:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;

		default:
		case DAT_OUTPUT:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
	}
	HAL_GPIO_Init(KBD_CLOCK_GPIO_Port, &GPIO_InitStruct);

	/* Now configure KBD_RESET_Pin as output */
	GPIO_InitStruct.Pin = KBD_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(KBD_RESET_GPIO_Port, &GPIO_InitStruct);

}

static void amikb_send(uint8_t keycode, int press)
{
	int i;
	//if (keycode == 0x62 || keycode == 0x68 || keycode == 0x1c) // Caps Lock, Num Lock or Scroll Lock Pressed or Released
	//{
		// caps lock doesn't get a key release event when the key is released
		// but rather when the caps lock is toggled off again
		// But what about num lock?


		if (keycode == 0x62 && press == 1)
		{
			HAL_GPIO_TogglePin(PC7_CAPS_LED_31_GPIO_Port, PC7_CAPS_LED_31_Pin);
		}


	// keycode bit transfer order: 6 5 4 3 2 1 0 7 (7 is pressed flag)
	keycode = (keycode << 1) | (~press & 1);
	if (keycode == prev_keycode)
	{
		return;
	}

	prev_keycode = keycode;

	// Set direction DAT & CLOCK as output to ensure the correct
	// movement of the edges (CLK and DAT)
	amikb_direction(DAT_OUTPUT);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET ); // NSS1 low

	// make sure we don't pulse the lines while grabbing control
	// by first reinstating the pullups before changing direction
	HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin, GPIO_PIN_SET); // Normally KBD_DATA pin is HIGH

	// pulse the data line and wait for about 100us
	HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin, GPIO_PIN_RESET); // KBD_DATA pin is LOW
	DWT_Delay(20);
	HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin, GPIO_PIN_SET); // KBD_DATA pin is HIGH
	DWT_Delay(100);

	for (i = 0; i < 8; i++)
	{
		// data line is inverted
		if (keycode & 0x80)
		{
			// a logic 1 is low in hardware
			HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin, GPIO_PIN_RESET);
		}
		else
		{
			// a logic 0 is high in hardware
			HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin, GPIO_PIN_SET);
		}
		keycode <<= 1;
		DWT_Delay(20);
		/* pulse the clock */
		HAL_GPIO_WritePin(KBD_CLOCK_GPIO_Port, KBD_CLOCK_Pin, GPIO_PIN_RESET); // Clear KBD_CLOCK pin
		DWT_Delay(20);
		HAL_GPIO_WritePin(KBD_CLOCK_GPIO_Port, KBD_CLOCK_Pin, GPIO_PIN_SET); // Set KBD_CLOCK pin
		DWT_Delay(20);
	}

	HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin, GPIO_PIN_SET); // Set KBD_DATA pin

	amikb_direction( DAT_INPUT );

#ifdef REAL_AMIKEYBOARD_SYNC
#warning "USING REAL AMIGA MOTHERBOARD HANDSHAKE"
	// Now the Amiga CPU send the sync signal lowering the KBD_DAT signal atleast 1 microsecond
	{
		if (keyboard_is_present)
		{
			int hshakepulse_ms = 143;
			int sync;
			for (;;)
			{
				sync = HAL_GPIO_ReadPin(KBD_GPIO_Port, KBD_DATA_Pin);
				if (sync == 0 || hshakepulse_ms == 0)
					break;
				hshakepulse_ms--;
				mdelay(1);
			}
			if (hshakepulse_ms == 0)
			{
				DBG_E("CPU KEYBOARD SYNC not received within 143msec!\r\n");
			}
		}
	}
#else
#warning "USING TIMED HANDSHAKE"
	HAL_Delay(5);// handshake wait 500msec
#endif
	// The following instructions should be useless as the port has been configured as input few
	// lines above... :-/
	HAL_GPIO_WritePin(KBD_DATA_GPIO_Port, KBD_DATA_Pin,  GPIO_PIN_SET); // Set KBD_DATA pin
	HAL_GPIO_WritePin(KBD_CLOCK_GPIO_Port, KBD_CLOCK_Pin, GPIO_PIN_SET); // Set KBD_CLOCK pin
	return;
}

// **************************
void amikb_reset(void)
{
	amikb_direction(DAT_OUTPUT);
	HAL_GPIO_WritePin(KBD_RESET_GPIO_Port, KBD_RESET_Pin, GPIO_PIN_RESET); // Clear KBD_RESET pin
	HAL_GPIO_WritePin(KBD_CLOCK_GPIO_Port, KBD_CLOCK_Pin, GPIO_PIN_RESET); // Clear KBD_CLOCK pin
	HAL_Delay(600);
	HAL_GPIO_WritePin(KBD_RESET_GPIO_Port, KBD_RESET_Pin, GPIO_PIN_SET);   // Set KBD_RESET pin
	HAL_GPIO_WritePin(KBD_CLOCK_GPIO_Port, KBD_CLOCK_Pin, GPIO_PIN_SET);   // Set KBD_CLOCK pin
	prev_keycode = 0xff;
	HAL_GPIO_WritePin(PC7_CAPS_LED_31_GPIO_Port, PC7_CAPS_LED_31_Pin, GPIO_PIN_SET);
}

// ****************************
bool amikb_reset_check(void)
{
	bool is_low;

	amikb_direction( DAT_INPUT );
	is_low = HAL_GPIO_ReadPin(KBD_CLOCK_GPIO_Port, KBD_CLOCK_Pin) == GPIO_PIN_RESET ? true : false;

	return is_low;
}

#define OK_RESET	3 /* 3 special keys to have a KBRESET */

void amikb_process(keyboard_t *data)
{
	int i;
	int j;

	//Check for CTRL+AMIGA+AMIGA reset
	if(data->special_keys.ctrl == 1 && data->special_keys.lami ==1 && data->special_keys.rami == 1)
	{
		amikb_reset();
	}



	// ----------------------------------------------- LEFT

	// LEFT SHIFT
	if (data->special_keys.lshf!=0xFF && (prevkeycode.special_keys.lshf != data->special_keys.lshf))
	{
		prevkeycode.special_keys.lshf = data->special_keys.lshf;
		amikb_send(0x60, data->special_keys.lshf);
	}

	// LEFT ALT
	if (data->special_keys.lalt != 0xFF && (prevkeycode.special_keys.lalt != data->special_keys.lalt))
	{
		prevkeycode.special_keys.lalt = data->special_keys.lalt;
		amikb_send(0x64, data->special_keys.lalt);
	}

	// CTRL
	if (data->special_keys.ctrl != 0xFF && (prevkeycode.special_keys.ctrl != data->special_keys.ctrl))
	{
		prevkeycode.special_keys.ctrl = data->special_keys.ctrl;
		amikb_send(0x63,  data->special_keys.ctrl);
	}

	// LEFT GUI
	if (data->special_keys.lami != 0xFF && (prevkeycode.special_keys.lami != data->special_keys.lami))
	{
		prevkeycode.special_keys.lami = data->special_keys.lami;
		amikb_send(0x66, data->special_keys.lami);
	}

	// ----------------------------------------------- RIGHT

	// RIGHT SHIFT
	if (data->special_keys.rshf != 0xFF && (prevkeycode.special_keys.rshf != data->special_keys.rshf))
	{
		prevkeycode.special_keys.rshf = data->special_keys.rshf;
		amikb_send(0x61, data->special_keys.rshf);
	}

	// RIGHT ALT
	if (data->special_keys.ralt != 0xFF && (prevkeycode.special_keys.ralt != data->special_keys.ralt))
	{
		prevkeycode.special_keys.ralt = data->special_keys.ralt;
		amikb_send(0x65, data->special_keys.ralt);
	}


	// RIGHT GUI
	if (data->special_keys.rami != 0xFF && (prevkeycode.special_keys.rami != data->special_keys.rami))
	{
		prevkeycode.special_keys.rami = data->special_keys.rami;
		amikb_send(0x67, data->special_keys.rami);
	}



	// Send all pressed key
	uint8_t keysToPress[KEY_PRESSED_MAX] = {0};
	uint8_t keysToRelease[KEY_PRESSED_MAX] = {0} ;

	memset(&keysToPress,0xFF,sizeof(keysToPress));
	memset(&keysToRelease,0xFF,sizeof(keysToRelease));


	int idxPress= 0;
	int idxRelease = 0;

	//Find keys to release
	for (i = 0; i < KEY_PRESSED_MAX; i++)
	{
		int found = 0;
		for (j = 0; j < KEY_PRESSED_MAX; j++)
		{
			if (prevkeycode.keyboard_codes[i] == data->keyboard_codes[j] )
			{
				found = 1;
			}
		}

		if(found == 0)
		{
		keysToRelease[idxRelease] = prevkeycode.keyboard_codes[i];
		idxRelease++;
		}

	}

	//Find keys to press (not already pressed)
	for (i = 0; i < KEY_PRESSED_MAX; i++)
	{
		int found = 0;
		for (j = 0; j < KEY_PRESSED_MAX; j++)
		{
			if ( data->keyboard_codes[i] == prevkeycode.keyboard_codes[j])
			{
				found = 1;
			}
		}

		 if (found == 0)
		 {
			keysToPress[idxPress] = data->keyboard_codes[i];
			idxPress++;
		 }
	}

	//Send release keys
	for (i = 0; i < KEY_PRESSED_MAX; i++)
	{
		if (keysToRelease[i] != 0xFF) // Previous key was released
		{
	        amikb_send(keysToRelease[i], 0 /* Released */);
	    }
	}

	//Send press keys
	for (i = 0; i < KEY_PRESSED_MAX; i++)
	{

		if (keysToPress[i] != 0xFF)
		{
			amikb_send(keysToPress[i], 1 /* Pressed */);

		}
	}


	//copy keys for next handling
	for (i = 0; i < KEY_PRESSED_MAX; i++)
	{
		prevkeycode.keyboard_codes[i] = data->keyboard_codes[i];
	}
}



