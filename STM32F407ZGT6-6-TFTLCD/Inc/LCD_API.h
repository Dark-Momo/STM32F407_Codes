/*
 * LCD_API.h
 *
 *  Created on: Jul 13, 2021
 *      Author: Jian Lao
 */

#ifndef LCD_API_H_
#define LCD_API_H_

#include <stdbool.h>

// NT35510 REG Offset
#define	NT35510_REG_READ_ID1 	0xDA00
#define NT35510_REG_READ_ID2 	0xDB00
#define NT35510_REG_READ_ID3 	0xDC00

#define NT35510_REG_MEMWR 		0x2C00
#define NT35510_REG_ROWADDRSET 	0x2B00
#define NT35510_REG_COLADDRSET 	0x2A00

#define NT35510_REG_MADCTL 		0x3600

/* LCD Display and Scan Direction ------------------------- */
#define Display_Horizontal	1
#define Display_Vertical	0

#define L2R_U2D  0	// From Left to Right, Up to Bottom

/* LCD API Prototype -------------------------------------- */
void LCD_Init(void);

#endif /* LCD_API_H_ */
