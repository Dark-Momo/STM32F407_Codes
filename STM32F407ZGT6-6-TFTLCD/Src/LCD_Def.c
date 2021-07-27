/*
 * LCD_Def.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Jian Lao
 */

#include "LCD_Def.h"

/* This function will trigger FSMC to write 'regaddr' as data to addr LCD_REG in its view.
 * FSMC will:
 * 1. First issue address LCD_REG, with A6 = 0;
 * 2. Then FSMC will ouput regaddr to its D[15:0].
 *
 * param - regaddr : Register offset on NT35510;
 */
void LCD_WR_REG(uint16_t regaddr)
{
	/* According to Atom Example Code, below line is necessary for -o2 optimization. */
	// regaddr = regaddr;
    LCD->LCD_REG = regaddr;
}

/* Below function should be used after register address is triggered, such as above
 * function LCD_WR_REG(). That is why it doesn't require a register index as parameter.
 */
uint16_t LCD_RD_DATA(void)
{
    return LCD->LCD_RAM;
}

/* Below function should be used after register address is triggered, such as above
 * function LCD_WR_REG(). That is why it doesn't require a register index as parameter.
 */
void LCD_WR_DATA(uint16_t data)
{
	LCD->LCD_RAM = data;
}

/* ********************************************************************************** */

/* Below function is a complete SetAddr - WriteData function */
void LCD_WriteReg(uint16_t regaddr, uint16_t regval)
{
	LCD->LCD_REG = regaddr;
	LCD->LCD_RAM = regval;
}
