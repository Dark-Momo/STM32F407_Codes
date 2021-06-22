/*
 * mm_TIM3_Basic.c
 *
 *  Created on: Jun 18, 2021
 *      Author: Jian Lao
 */

#include "main.h"
#include "mm_TIM3_Basic.h"

extern TIM_HandleTypeDef htim3;

void mm_TIM3_Basic_Init(void)
{
	HAL_GPIO_WritePin(RLED_GPIO_Port, RLED_Pin, GPIO_PIN_SET); 	// Turn off Red LED at initial stage
	HAL_GPIO_WritePin(GLED_GPIO_Port, GLED_Pin, GPIO_PIN_SET); 	// Turn off Green LED at initial stage

	HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		HAL_GPIO_TogglePin(RLED_GPIO_Port, RLED_Pin);
		HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
	}
}


