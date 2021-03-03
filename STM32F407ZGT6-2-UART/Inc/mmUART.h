/*
 * mmUART.h
 *
 *  Created on: 2021年2月28日
 *      Author: Jian Lao
 */

#ifndef MMUART_H_
#define MMUART_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Global variable definition ------------------------------------------- */

/* Try : Declare a global variable in .h file and define in its .c file.
 * Other .c files can only include this .h to access this variable.
 */
/* Receiving Status :
 * Bit ]15]     : Receive finish.
 * Bit [14] 	: Received 0x0D, which is '\r';
 * Bit [13 - 0]	: Received byte number;
 */

extern uint16_t UART1_REV_Status;





#ifdef __cplusplus
}
#endif

#endif /* MMUART_H_ */
