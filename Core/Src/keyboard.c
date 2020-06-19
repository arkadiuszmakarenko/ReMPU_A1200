
#include "keyboard.h"
#include "stm32f1xx.h"
#include "main.h"

special_keys_t special_keys;

//Mappings must be valid, we don't expect situation that X,Y pair would never have valid return value.
uint8_t MapKey(uint8_t X,uint8_t Y)
{
	int i = 0;

	for (i = 0; i < KEYCODE_TAB_SIZE; i++)
	{
		if (amigacode[i][0]==X && amigacode[i][1]==Y )
		{
							return amigacode[i][2];
							break;
		}
	}
	return 0;
}


void MapKeys(keyboard_t *keyboard)
{
	uint8_t X;
	uint8_t Y;
	uint8_t keycodes_added = 0;

	for(X = 2; X<8;X++)
	{
		for(Y=0;Y<15;Y++)
		{
			if (keycodes_added >= KEY_PRESSED_MAX)
				{
					break;
				}

			uint16_t XRow = keyboard->keyboard_matrix[X-2];

			uint8_t YVal = (XRow & ( 1 << Y )) >> Y;

			//Process keypress
			if (YVal==1)
			{
				keyboard->keyboard_codes[keycodes_added] = MapKey(X,Y);
				keycodes_added++;
			}

		}
	}

}

uint16_t Read_Y(void)
{
	uint16_t Y_val = 0x8000;

	Y_val = Y_val|HAL_GPIO_ReadPin(PC6_Y0_29_GPIO_Port,PC6_Y0_29_Pin);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PC5_Y1_28_GPIO_Port,PC5_Y1_28_Pin)<<1);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PC4_Y2_27_GPIO_Port,PC4_Y2_27_Pin)<<2);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PC3_Y3_26_GPIO_Port,PC3_Y3_26_Pin)<<3);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PC2_Y4_25_GPIO_Port,PC2_Y4_25_Pin)<<4);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PC1_Y5_24_GPIO_Port,PC1_Y5_24_Pin)<<5);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA8_Y6_23_GPIO_Port,PA8_Y6_23_Pin)<<6);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA7_Y7_22_GPIO_Port,PA7_Y7_22_Pin)<<7);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA6_Y8_21_GPIO_Port,PA6_Y8_21_Pin)<<8);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA5_Y9_20_GPIO_Port,PA5_Y9_20_Pin)<<9);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA4_Y10_19_GPIO_Port,PA4_Y10_19_Pin)<<10);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA3_Y11_18_GPIO_Port,PA3_Y11_18_Pin)<<11);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA2_Y12_17_GPIO_Port,PA2_Y12_17_Pin)<<12);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA1_Y13_16_GPIO_Port,PA1_Y13_16_Pin)<<13);
	Y_val = Y_val|(HAL_GPIO_ReadPin(PA0_Y14_15_GPIO_Port,PA0_Y14_15_Pin)<<14);

	return ~Y_val;
}


void Read_Keyboard(keyboard_raw_t *keyboard)
{


	//X2 - Y0-Y14
	HAL_GPIO_WritePin(PB2_X2_7_GPIO_Port,PB2_X2_7_Pin,GPIO_PIN_RESET);
		keyboard->keyboard_matrix[0] = Read_Y();
	HAL_GPIO_WritePin(PB2_X2_7_GPIO_Port,PB2_X2_7_Pin,GPIO_PIN_SET);

	//X3 - Y0-Y14
	HAL_GPIO_WritePin(PB3_X3_5_GPIO_Port,PB3_X3_5_Pin,GPIO_PIN_RESET);
		keyboard->keyboard_matrix[1] = Read_Y();
	HAL_GPIO_WritePin(PB3_X3_5_GPIO_Port,PB3_X3_5_Pin,GPIO_PIN_SET);

	//X4 - Y0-Y14
	HAL_GPIO_WritePin(PB4_X4_1_GPIO_Port,PB4_X4_1_Pin,GPIO_PIN_RESET);
		keyboard->keyboard_matrix[2] = Read_Y();
	HAL_GPIO_WritePin(PB4_X4_1_GPIO_Port,PB4_X4_1_Pin,GPIO_PIN_SET);

	//X5 - Y0-Y14
	HAL_GPIO_WritePin(PB5_X5_2_GPIO_Port,PB5_X5_2_Pin,GPIO_PIN_RESET);
		keyboard->keyboard_matrix[3] = Read_Y();
	HAL_GPIO_WritePin(PB5_X5_2_GPIO_Port,PB5_X5_2_Pin,GPIO_PIN_SET);

	//X6 - Y0-Y14
	HAL_GPIO_WritePin(PB6_X6_3_GPIO_Port,PB6_X6_3_Pin,GPIO_PIN_RESET);
		keyboard->keyboard_matrix[4] = Read_Y();
	HAL_GPIO_WritePin(PB6_X6_3_GPIO_Port,PB6_X6_3_Pin,GPIO_PIN_SET);

	//X7 - Y0-Y14
	HAL_GPIO_WritePin(PB7_X7_4_GPIO_Port,PB7_X7_4_Pin,GPIO_PIN_RESET);
		keyboard->keyboard_matrix[5] = Read_Y();
	HAL_GPIO_WritePin(PB7_X7_4_GPIO_Port,PB7_X7_4_Pin,GPIO_PIN_SET);


	//special keys
	keyboard->special_keys.lalt = HAL_GPIO_ReadPin(PD5_LALT_13_GPIO_Port, PD5_LALT_13_Pin)^1;
	keyboard->special_keys.lami = HAL_GPIO_ReadPin(PD7_LAMI_14_GPIO_Port,PD7_LAMI_14_Pin)^1;
	keyboard->special_keys.lshf = HAL_GPIO_ReadPin(PD4_LSHIFT_12_GPIO_Port, PD4_LSHIFT_12_Pin)^1;
	keyboard->special_keys.ctrl = HAL_GPIO_ReadPin(PD3_CTRL_11_GPIO_Port, PD3_CTRL_11_Pin)^1;
	keyboard->special_keys.ralt = HAL_GPIO_ReadPin(PD1_RALT_8_GPIO_Port, PD1_RALT_8_Pin)^1;
	keyboard->special_keys.rami = HAL_GPIO_ReadPin(PD2_RAMI_10_GPIO_Port, PD2_RAMI_10_Pin)^1;
	keyboard->special_keys.rshf = HAL_GPIO_ReadPin(PD0_RSHF_6_GPIO_Port, PD0_RSHF_6_Pin)^1;

}



void ProcessKeyboard(keyboard_t *keyboard)
{

	keyboard_raw_t keyboard_raw[DEBOUNCE_KEYBOARD];

	//debounce routine
	//read 3 times data on keyboard
	uint8_t debouce_counter = 0;
	for(debouce_counter = 0;debouce_counter < DEBOUNCE_KEYBOARD;debouce_counter++)
	{
		 Read_Keyboard(&keyboard_raw[debouce_counter]);
		 HAL_Delay(1);

	}

	//if at this point hardcoded for 3, need to automate it.



		if (keyboard_raw[0].keyboard_matrix[0]==keyboard_raw[1].keyboard_matrix[0] && keyboard_raw[1].keyboard_matrix[0]==keyboard_raw[2].keyboard_matrix[0])
		{
			keyboard->keyboard_matrix[0]=keyboard_raw[0].keyboard_matrix[0];
		}

		if (keyboard_raw[0].keyboard_matrix[1]==keyboard_raw[1].keyboard_matrix[1] && keyboard_raw[1].keyboard_matrix[1]==keyboard_raw[2].keyboard_matrix[1])
		{
			keyboard->keyboard_matrix[1]=keyboard_raw[0].keyboard_matrix[1];
		}

		if (keyboard_raw[0].keyboard_matrix[2]==keyboard_raw[1].keyboard_matrix[2] && keyboard_raw[1].keyboard_matrix[2]==keyboard_raw[2].keyboard_matrix[2])
		{
			keyboard->keyboard_matrix[2]=keyboard_raw[0].keyboard_matrix[2];
		}

		if (keyboard_raw[0].keyboard_matrix[3]==keyboard_raw[1].keyboard_matrix[3] && keyboard_raw[1].keyboard_matrix[3]==keyboard_raw[2].keyboard_matrix[3])
		{
			keyboard->keyboard_matrix[3]=keyboard_raw[0].keyboard_matrix[3];
		}

		if (keyboard_raw[0].keyboard_matrix[4]==keyboard_raw[1].keyboard_matrix[4] && keyboard_raw[1].keyboard_matrix[4]==keyboard_raw[2].keyboard_matrix[4])
		{
			keyboard->keyboard_matrix[4]=keyboard_raw[0].keyboard_matrix[4];
		}

		if (keyboard_raw[0].keyboard_matrix[5]==keyboard_raw[1].keyboard_matrix[5] && keyboard_raw[1].keyboard_matrix[5]==keyboard_raw[2].keyboard_matrix[5])
		{
			keyboard->keyboard_matrix[5]=keyboard_raw[0].keyboard_matrix[5];
		}


		if (keyboard_raw[0].special_keys.ctrl == keyboard_raw[1].special_keys.ctrl && keyboard_raw[1].special_keys.ctrl == keyboard_raw[2].special_keys.ctrl)
		{
			keyboard->special_keys.ctrl = keyboard_raw[0].special_keys.ctrl;
		}

		if (keyboard_raw[0].special_keys.lalt == keyboard_raw[1].special_keys.lalt && keyboard_raw[1].special_keys.lalt == keyboard_raw[2].special_keys.lalt)
		{
			keyboard->special_keys.lalt = keyboard_raw[0].special_keys.lalt;
		}

		if (keyboard_raw[0].special_keys.lami == keyboard_raw[1].special_keys.lami && keyboard_raw[1].special_keys.lami == keyboard_raw[2].special_keys.lami)
		{
			keyboard->special_keys.lami = keyboard_raw[0].special_keys.lami;
		}

		if (keyboard_raw[0].special_keys.lshf == keyboard_raw[1].special_keys.lshf && keyboard_raw[1].special_keys.lshf == keyboard_raw[2].special_keys.lshf)
		{
			keyboard->special_keys.lshf = keyboard_raw[0].special_keys.lshf;
		}

		if (keyboard_raw[0].special_keys.ralt == keyboard_raw[1].special_keys.ralt && keyboard_raw[1].special_keys.ralt == keyboard_raw[2].special_keys.ralt)
		{
			keyboard->special_keys.ralt = keyboard_raw[0].special_keys.ralt;
		}

		if (keyboard_raw[0].special_keys.rami == keyboard_raw[1].special_keys.rami && keyboard_raw[1].special_keys.rami == keyboard_raw[2].special_keys.rami)
		{
			keyboard->special_keys.rami = keyboard_raw[0].special_keys.rami;
		}

		if (keyboard_raw[0].special_keys.rshf == keyboard_raw[1].special_keys.rshf && keyboard_raw[1].special_keys.rshf == keyboard_raw[2].special_keys.rshf)
		{
			keyboard->special_keys.rshf = keyboard_raw[0].special_keys.rshf;
		}

	//Map data
		MapKeys(keyboard);


}


