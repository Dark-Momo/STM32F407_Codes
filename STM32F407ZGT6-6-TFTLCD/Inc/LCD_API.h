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

/* LCD Color ---------------------------------------------- */
#define COLOR_WHITE			0xFFFF
#define COLOR_BLACK       	0x0000
#define COLOR_RED         	0xF800 // 0b1111 1000 0000 0000
#define COLOR_GREEN       	0x07E0 // 0b0000 0111 1110 0000
#define COLOR_BLUE        	0x001F // 0b0000 0000 0001 1111

#define COLOR_MAGENTA       0xF81F
#define COLOR_CYAN          0x7FFF
#define COLOR_GRAY  		0x8430
#define COLOR_LGRAY 		0xC618

/* LCD API Prototype -------------------------------------- */
void LCD_Init(void);
void LCD_ClearScreen(uint16_t Color);

#endif /* LCD_API_H_ */
