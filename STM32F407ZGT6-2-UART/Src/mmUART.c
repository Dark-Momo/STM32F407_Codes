/*
 * mmUART.c
 *
 *  Created on: 2021年2月28日
 *      Author: Jian Lao
 */
#include "stm32f4xx_hal.h"	// For callback functions.

#include "mmUART.h"


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
