/*
 * mm_WWDG.c
 *
 *  Created on: May 19, 2021
 *      Author: Jian Lao
 */

#include "main.h"

extern WWDG_HandleTypeDef hwwdg;

void mm_WWDG_Init(void)
{
	// Let RED LED ON when reset as an indication, and only happens at initialization.
	HAL_GPIO_WritePin(R_LED_GPIO_Port, R_LED_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
}

void mm_WWDG_Process(void)
{
	// Let RED LED OFF in main while().
	HAL_GPIO_WritePin(R_LED_GPIO_Port, R_LED_Pin, GPIO_PIN_SET);
}

/* ---------------------------------------------------------------------------------- */
/* In initial setting:
 * Counter = 127; Window = 0x5F; Prescaler = WWDG_PRESCALER_8 (WDGTB[1:0] = 0b11);
 * PCLK1=42MHz(T = 0.0208uS);
 *
 * So, When T6 of Counter changes from 1 to 0, the time is:
 * 0.0208 * 4096 * 8 * 64 = 43620uS = 43.6mS.
 *
 * Logic analyzer got 49.15mS.
 */
/* ---------------------------------------------------------------------------------- */

/* Below Callback is called in void HAL_WWDG_IRQHandler(WWDG_HandleTypeDef *hwwdg)
 * with parameters hwwdg, which is the one defined in main().
 *
 * WWDG only have 1 IRQ, which is EWI, happening at counter decreases to 0x40.
 * The HAL_WWDG_IRQHandler() only clears the IRQ flag of EWI, and calls this callback.
 */

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
	HAL_WWDG_Refresh(hwwdg); // Must have, otherwise keep reseting the MCU.
	HAL_GPIO_TogglePin(G_LED_GPIO_Port, G_LED_Pin); // Green LED toggles.
}
