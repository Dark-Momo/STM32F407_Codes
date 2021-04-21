/*
 * mmUART.c
 *
 *  Created on: 2021年2月28日
 *      Author: Jian Lao
 */
#include "stm32f4xx_hal.h"	// For callback functions.

#include "main.h"
#include <stdbool.h>
/* User include ------------------------------------------------------------ */
#include "mmUART.h"

/* Using extern when referred to something declared in other file ---------- */
extern UART_HandleTypeDef huart1;

/* Macro and Buffer definition --------------------------------------------- */
#define Buf_MaxSize 128
// uint8_t DataLinetoSend[Buf_MaxSize];
uint8_t DataLineFromRecv[Buf_MaxSize];

/* Variable to record receiving status ------------------------------------- */

/* Below callback is used to receive the data from XCOM on PC.
 * XCOM will add \r\n to the end of the input text, and then send out.
 * \r : 0x0D; \n : 0x0A
 */

/* Receiving Status 'UART1_Rev_Status':
 * Bit ]15]     : Receive finish.
 * Bit [14] 	: Received 0x0D, which is '\r';
 * Bit [13 - 0]	: Received byte number;
 */
uint16_t UART1_Rev_Status;

uint8_t revChar = '\0'; 	/* Byte receive buffer */
char termiStr[] = "\r\n";

HAL_StatusTypeDef SendRet = HAL_OK;

/* Private Functions prototype --------------------------------------------- */
static void UART_RecvError_RLED(uint32_t ErrorCode);
static void UART_RecvOK_GLED(uint32_t onDurationMs);

/* Functions definition ---------------------------------------------------- */
void UART_UserSettingInitial(void)
{
	// Let both LED in OFF state
	HAL_GPIO_WritePin(LED0_DS0_R_GPIO_Port, LED0_DS0_R_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_DS1_G_GPIO_Port, LED1_DS1_G_Pin, GPIO_PIN_SET);

	// Reset Rev Status and Counter
	UART1_Rev_Status = 0x0000;

	// memset(DataLinetoSend, 	 '\0', Buf_MaxSize);
	memset(DataLineFromRecv, '\0', Buf_MaxSize);

	HAL_NVIC_EnableIRQ(USART1_IRQn);

	// Key point : Initial Receiving issued here
	HAL_UART_Receive_IT(&huart1, &revChar, 1);
}

void UART_Process()
{
	if (UART1_Rev_Status & 0x8000) 	// '/r/n' has been received.
	{
		strcat((char *)DataLineFromRecv, termiStr);	// Append "\r\n" to the end of TX buffer
		SendRet = HAL_UART_Transmit(&huart1, DataLineFromRecv, (UART1_Rev_Status & 0x3FFF) + strlen(termiStr), 10); // 10ms for TX timeout
		if (SendRet != HAL_OK)
		{
			UART_RecvError_RLED(1);
		}
		// Clear RX status
		UART1_Rev_Status = 0x0000;

		// Don't forget to clear sent buffer as below, otherwise when you change the data that
		// will be sent on the fly to a shorter sentence, the received data would have
		// some error at margin part.
		memset(DataLineFromRecv, '\0', Buf_MaxSize);

		// Below will work as an indication of good TX, but bring latency of display.
		UART_RecvOK_GLED(20);
	}
}

// int UART_SendLine(UART_HandleTypeDef *huart, uint8_t * pData, uint8_t LineSize) {}
// int UART_RecvByte(UART_HandleTypeDef *huart, uint8_t * pData) {}
// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
		// RecvCount++;

		if (!(UART1_Rev_Status & 0x8000)) 			// UART1_Rev_Status[15] is not 1, meaning '\n'(0x0A) not received.
		{
			if (UART1_Rev_Status & 0x4000) 				// UART1_Rev_Status[14] is 1, meaning '\r'(0x0D) has been received.
			{
				if (revChar == 0x0A)						// '\n'(0x0A) is received.
				{
					UART1_Rev_Status |= 0x8000;
				}
				else										// '\n'(0x0A) is not received, and abandon this trial.
					UART1_Rev_Status = 0x0000;
			}
			else										// UART1_Rev_Status[14] is 0, meaning '\r'(0x0D) has not been received.
			{
				if (revChar == 0x0D)
				{
					UART1_Rev_Status |= 0x4000;
				}
				else
				{
					DataLineFromRecv[UART1_Rev_Status & 0x3FFF] = revChar;
					UART1_Rev_Status++;

					if (UART1_Rev_Status > Buf_MaxSize - 1)
						UART1_Rev_Status = 0x0000;
				}
			}
		}
		// Here, we don't have 'else' branch for 'UART1_Rev_Status[15] == 1' when this ISR callback is called, because if this happens,
		// that means upper layer receiver has cleared UART1_Rev_Status for last run. We should wait.

		// Key point : Start next round of receiving here.
		HAL_UART_Receive_IT(&huart1, &revChar, 1);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	huart->RxState = HAL_UART_STATE_READY;
	UART1_Rev_Status = 0x0000;
	memset(DataLineFromRecv, '\0', Buf_MaxSize);

	if (huart->ErrorCode & HAL_UART_ERROR_PE) 		// HAL_UART_ERROR_PE == 0x00000001U
	{
		UART_RecvError_RLED(HAL_UART_ERROR_PE);
	}
	else if (huart->ErrorCode & HAL_UART_ERROR_NE) 	// HAL_UART_ERROR_NE == 0x00000002U
	{
		UART_RecvError_RLED(HAL_UART_ERROR_NE);
	}
	else if (huart->ErrorCode & HAL_UART_ERROR_FE) 	// HAL_UART_ERROR_FE == 0x00000004U
	{
		UART_RecvError_RLED(HAL_UART_ERROR_FE);
	}
	else if (huart->ErrorCode & HAL_UART_ERROR_ORE) // HAL_UART_ERROR_ORE == 0x00000008U
	{
		UART_RecvError_RLED(HAL_UART_ERROR_ORE);
	}
	else
	{
		UART_RecvError_RLED(10000);
	}
}

/* Private functions ------------------------------------------------------- */
static void UART_RecvOK_GLED(uint32_t onDurationMs)
{
	HAL_GPIO_WritePin(LED1_DS1_G_GPIO_Port, LED1_DS1_G_Pin, GPIO_PIN_RESET);
	HAL_Delay(onDurationMs);
	HAL_GPIO_WritePin(LED1_DS1_G_GPIO_Port, LED1_DS1_G_Pin, GPIO_PIN_SET);
	HAL_Delay(onDurationMs);
}

static void UART_RecvError_RLED(uint32_t ErrorCode)
{
	HAL_GPIO_WritePin(LED0_DS0_R_GPIO_Port, LED0_DS0_R_Pin, GPIO_PIN_RESET);
	HAL_Delay(500 * ErrorCode); // Unit in ms
	HAL_GPIO_WritePin(LED0_DS0_R_GPIO_Port, LED0_DS0_R_Pin, GPIO_PIN_SET);
}
