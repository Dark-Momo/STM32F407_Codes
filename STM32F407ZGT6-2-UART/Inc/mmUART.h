/*
 * mmUART.h
 *
 *  Created on: 2021年2月28日
 *      Author: Jian Lao
 */

#ifndef MMUART_H_
#define MMUART_H_

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Top layer API called in main() --------------------------------------- */
void UART_UserSettingInitial(void);
void UART_Process();
// int UART_SendLine(UART_HandleTypeDef *huart, uint8_t * pData, uint8_t LineSize);
// int UART_RecvByte(UART_HandleTypeDef *huart, uint8_t * pData);

#ifdef __cplusplus
}
#endif

#endif /* MMUART_H_ */
