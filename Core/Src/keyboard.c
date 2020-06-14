
#include "keyboard.h"
#include "stm32f1xx.h"
#include "main.h"

keyboard_t keyboard = {0};
keyboard_t previous_keyboard = {0};

uint32_t keyboard_matrix[6] = {0};

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


int* Read_Keyboard(void)
{


	//X2 - Y0-Y14

	HAL_GPIO_WritePin(PB2_X2_7_GPIO_Port,PB2_X2_7_Pin,GPIO_PIN_RESET);

	keyboard_matrix[0] = Read_Y();

	HAL_GPIO_WritePin(PB2_X2_7_GPIO_Port,PB2_X2_7_Pin,GPIO_PIN_SET);

	//X3 - Y0-Y14
	HAL_GPIO_WritePin(PB3_X3_5_GPIO_Port,PB3_X3_5_Pin,GPIO_PIN_RESET);

	keyboard_matrix[1] = Read_Y();

	HAL_GPIO_WritePin(PB3_X3_5_GPIO_Port,PB3_X3_5_Pin,GPIO_PIN_SET);

	//X4 - Y0-Y14
	HAL_GPIO_WritePin(PB4_X4_1_GPIO_Port,PB4_X4_1_Pin,GPIO_PIN_RESET);

	keyboard_matrix[2] = Read_Y();

	HAL_GPIO_WritePin(PB4_X4_1_GPIO_Port,PB4_X4_1_Pin,GPIO_PIN_SET);

	//X5 - Y0-Y14
	HAL_GPIO_WritePin(PB5_X5_2_GPIO_Port,PB5_X5_2_Pin,GPIO_PIN_RESET);
	keyboard_matrix[3] = Read_Y();
	HAL_GPIO_WritePin(PB5_X5_2_GPIO_Port,PB5_X5_2_Pin,GPIO_PIN_SET);

	//X6 - Y0-Y14
	HAL_GPIO_WritePin(PB6_X6_3_GPIO_Port,PB6_X6_3_Pin,GPIO_PIN_RESET);
	keyboard_matrix[4] = Read_Y();
	HAL_GPIO_WritePin(PB6_X6_3_GPIO_Port,PB6_X6_3_Pin,GPIO_PIN_SET);

	//X7 - Y0-Y14
	HAL_GPIO_WritePin(PB7_X7_4_GPIO_Port,PB7_X7_4_Pin,GPIO_PIN_RESET);
	keyboard_matrix[5] = Read_Y();
	HAL_GPIO_WritePin(PB7_X7_4_GPIO_Port,PB7_X7_4_Pin,GPIO_PIN_SET);


	return keyboard_matrix;
}




