/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <io.h>
#include <stdio.h>
#include <ioport.h>

#include "LCD/HD44780.h"
#include "ARM_Libs/Macros.h"
#include "ARM_Libs/Timer.h"


int main (void)
{
	int flag[8] = {0x07,0x07,0x04,0x04,0x15,0x1F,0x0E,0x1F}; // 5x8 custom character
	int plus[8] = {0x04,0x04,0x04,0x1F,0x04,0x04,0x04,0x04};
	char *msg1="LCD Test"; /* Must be 20 char or less*/
	
	board_init();
	sysclk_init();
	int pins = 0x2F;
	REG_PIOC_OER = 0x07F800000;// pull everything high because i dont care 
	PIOC->PIO_SODR = (1 << 29); // turn on back light

	openLCD();
	cmd2LCD(0xC0);
	putsLCD(msg1);
	CChar(flag, 0);
	CChar(plus, 1);
	cposition(0,1);
	putcLCD(0x00);
	putcLCD(0x01);
	

}



