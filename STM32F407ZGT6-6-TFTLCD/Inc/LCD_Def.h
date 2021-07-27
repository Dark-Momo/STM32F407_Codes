/*
 * LCD_Def.h
 *
 *  Created on: Jul 11, 2021
 *      Author: Jian Lao
 */

#ifndef LCD_DEF_H_
#define LCD_DEF_H_

#include <stdint.h>

/* LCD abstract from FSMC address space ------------------------------------------------------ */
/* See the .doc file with the same name of project for why defining as below. */
#define		LCD_BASEADDR 	(uint32_t)(0x6C000000 | 0x0000007E)

/* uint16_t makes sure that FSMC_A6 will be have a toggle from LCD_REG to LCD_RAM. */
typedef struct
{
    uint16_t	LCD_REG;
    uint16_t	LCD_RAM;
} LCD_TypeDef;

#define 	LCD 			( (LCD_TypeDef *) LCD_BASEADDR )

/* LCD device abstract ----------------------------------------------------------------------- */
typedef struct
{
	uint16_t _LCD_ID;
	uint16_t _LCD_Width;		// 480 for my 4.3' LCD
    uint16_t _LCD_Height;       // 800 for my 4.3' LCD
    uint8_t  _LCD_Orientation; 	// Horizon (1) or Vertial (0). Vertical for this example

    /* Think whether below are necessary in structure definition here */
    uint16_t _LCD_WRAM_CMD;		// Offset of Memory Write register. 0x2C00 for NT35510
    uint16_t _LCD_SetX_CMD;		// Offset of register that is used to set current X coordinator
    uint16_t _LCD_SetY_CMD;		// Offset of register that is used to set current Y coordinator
} _LCD_Device;

/* Basic Read and Write Operations to LCD ---------------------------------------------------- */
void LCD_WR_REG(uint16_t regval);
uint16_t LCD_RD_DATA(void);
void LCD_WR_DATA(uint16_t data);

void LCD_WriteReg(uint16_t regaddr, uint16_t regval);

#endif /* LCD_DEF_H_ */
