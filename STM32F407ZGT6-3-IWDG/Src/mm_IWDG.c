/*
 * mm_IWDG.c
 *
 *  Created on: May 5, 2021
 *      Author: Jian Lao
 */

#include "main.h"
#include "mm_IWDG.h"

/* IWDG Handler defined in main.c -------------------- */
extern IWDG_HandleTypeDef hiwdg;

static void startUp_LED(uint32_t onDuration);

/* User Init ----------------------------------------- */
void mm_IWDG_Init(void)
{
	startUp_LED(200);

	// 'IWDG_PRESCALER_32' and '4095' will set timeout to 4.096 second.
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
	hiwdg.Init.Reload = 4095;

	if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
	{
		// RLED stay on if user initialize failed.
		HAL_GPIO_WritePin(RLED_DS0_GPIO_Port, RLED_DS0_Pin, GPIO_PIN_RESET);
    }
}

void IWDG_Process(void)
{
	if (HAL_GPIO_ReadPin(KEY_WKUP_GPIO_Port, KEY_WKUP_Pin) == GPIO_PIN_SET)
		HAL_IWDG_Refresh(&hiwdg);

	HAL_Delay(20);
}

static void startUp_LED(uint32_t onDuration)
{
	HAL_GPIO_WritePin(RLED_DS0_GPIO_Port, RLED_DS0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLED_DS1_GPIO_Port, GLED_DS1_Pin, GPIO_PIN_SET);

	HAL_Delay(onDuration);

	HAL_GPIO_WritePin(RLED_DS0_GPIO_Port, RLED_DS0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLED_DS1_GPIO_Port, GLED_DS1_Pin, GPIO_PIN_RESET);

	HAL_Delay(onDuration);

	HAL_GPIO_WritePin(RLED_DS0_GPIO_Port, RLED_DS0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLED_DS1_GPIO_Port, GLED_DS1_Pin, GPIO_PIN_SET);

	HAL_Delay(onDuration);

	HAL_GPIO_WritePin(RLED_DS0_GPIO_Port, RLED_DS0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLED_DS1_GPIO_Port, GLED_DS1_Pin, GPIO_PIN_RESET);

	HAL_Delay(onDuration);

	HAL_GPIO_WritePin(RLED_DS0_GPIO_Port, RLED_DS0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLED_DS1_GPIO_Port, GLED_DS1_Pin, GPIO_PIN_SET);
}


