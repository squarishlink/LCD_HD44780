/*
 * HD44780.c
 *
 * Created: 28/08/2012 9:54:54 PM
 *  Author: Michael
 *  This library works with all HD44780 LCD MODULES 
 */ 
#include "HD44780.h"         /* standard input and output library */



///////////////////////////////////////////////////////////////////////////
/*			LCD		DUE		SAM3X8E
			D4		4		C26
			D5		5		C25	
			D6		6		C24
			D7		7		C23
			E		8		C21
			RS		9		C22 
*/
///////////////////////////////////////////////////////////////////////////
#define  LCD_DAT  REG_PIOC_SODR   /* Port C drives LCD data pins, E, and RS */
///////////////////////////////////////////////////////////////////////////


/*   Confirm the pin out of your LCD Shield or LCD Project board   
    This LCD Shield Uses The last 4 bits of portD for parallel processing 
 */

#define  LCD_E    PORTB1     /* E signal  0000 0010    E is connected to pin9*/
#define  LCD_RS   PORTB0     /* RS signal 0000 0001    RS is connected to pin 8*/
#define  LCD_E_RS 0x07    /* assert both E and RS signal   */
#define	 LCD_BL  PORTB2         


// LCD MODULES void cmd2LCD(char cmd)
void cmd2LCD(char cmd)
{
	int SendCmd=0;
	int i;
	SendCmd = Swap_Bits(cmd);
	SendCmd &=0xF0;           /* zero out the lower 4 bits */
	SendCmd <<= 19;
		
	REG_PIOC_SODR = (SendCmd);
	PIOC->PIO_CODR = 1 << 22; // pull rs LOW 
	PIOC->PIO_SODR = 1 << 21;  /* pull E signal to high */
	Delay_us(3);
		
	PIOC->PIO_CODR = 1 << 21; /*pull e signal low*/
	REG_PIOC_CODR =  (SendCmd);
		
	SendCmd = Swap_Bits(cmd) & 0x0F;    /* extract the lower four bits */
	SendCmd <<= 23;
	REG_PIOC_SODR = (SendCmd);
	PIOC->PIO_SODR = 1 << 21;  /* pull E signal to high */

	Delay_us(3);
	PIOC->PIO_CODR = 1 << 21; // pull e low
	REG_PIOC_CODR =  (SendCmd);
	PIOC->PIO_CODR = 1 << 22; // pull rs low
		
	//LCD_E_RS_DAT &= (0 << LCD_E)| (1<< LCD_BL);  /* pull E clock to low */
	Delay_us(50);       /* wait until the command is complete */
}



void openLCD(void)
{
	//LCD_DIR |=  (1 <<PORTD4) |(1 <<PORTD5) |(1 <<PORTD6) |(1 <<PORTD7);       /* configure LCD_DAT port for output */
	//LCD_E_RS_DIR =  (1 << LCD_E) | (1 << LCD_RS) | (1 << LCD_BL);
	Delay_ms(10);
	cmd2LCD(0x28);        /* set 4-bit data, 2-line display, 5x7 font */
	cmd2LCD(0x0C);        /* turn on display, cursor, blinking */
	cmd2LCD(0x06);        /* move cursor right */
	cmd2LCD(0x01);        /* clear screen, move cursor to home */
	Delay_ms(2);        /* wait until "clear display" command is complete */
}


void putcLCD(char cx)
{
	
	char temp;
	int SendCmd=0;
	int i;
	temp = cx;           /* save a copy of the char  */
	SendCmd = Swap_Bits(cx);
	SendCmd &=0xF0;           /* zero out the lower 4 bits */
	SendCmd <<= 19;
	
	REG_PIOC_SODR = (SendCmd);
	PIOC->PIO_SODR = 1 << 22; // pull rs high
	PIOC->PIO_SODR = 1 << 21;  /* pull E signal to high */
	Delay_us(3);
	
	PIOC->PIO_CODR = 1 << 21; /*pull e signal low*/
	REG_PIOC_CODR =  (SendCmd);
		
	SendCmd = Swap_Bits(cx) & 0x0F;    /* extract the lower four bits */
	SendCmd <<= 23;
	REG_PIOC_SODR = (SendCmd);
	PIOC->PIO_SODR = 1 << 21;  /* pull E signal to high */

	Delay_us(3);
	PIOC->PIO_CODR = 1 << 21; // pull e low
	REG_PIOC_CODR =  (SendCmd);
	PIOC->PIO_SODR = 1 << 22; // pull rs low
	
	//LCD_E_RS_DAT &= (0 << LCD_E)| (1<< LCD_BL);  /* pull E clock to low */
	Delay_us(50);       /* wait until the command is complete */
}

void putsLCD(char *ptr)  /* breaks the string down to characters ie a pointer to an address that holds the string */ 
{
	while (*ptr) {     /* while char pointer is not null*/ 
		putcLCD(*ptr);  /* put the character on the screen on letter at a time */
 		ptr++;   /* increment the memory the pointer points to */ 
	}
}


void clearscreen(void)
{
	cmd2LCD(0x01);  // clears screen  0x08 blanks the display without clearing
	cposition(0,1);   // returns cursor home 
}

void clearline(int line)      
{
	cposition(0,line);  
	for (int i=0; i < 20; i++) {putsLCD(" "); }
	cposition(0,line);
}

void cposition(int x, int y)
{
	int temp = 0x00 + x;
	
	switch(y)
	{
		case 1:
		temp += (0x80);      /// return home
		break;   
		case 2:
		temp += (0xC0);      /// Line 2 
		break;
		case 3:
		temp += (0x94);      /// line 3
		break;
		case 4:
		temp += (0xD4);      /// line 4 
		break;
	}
	cmd2LCD(temp);
}


/*  ************************************************************
Custom character function
	you will need to pass an array of 8 integers see my example code to accomplish this. 
	characters are defined by 8 sets bytes. Each Byte represents one Row(ie 1st byte is 1st row) the first 5 bytes represent the on and off
	states of the pixels.
	Please note that each time a character is defined the cursor returns home. 
*/
void CChar(int *character, int ccram)
{
	int x= 0; /// temp var for counting. 
	char command= (0x40+(ccram*8));  // adds the cc ram address 0x40 + the input for the cc (note: each cc takes 8 bytes) 
	cmd2LCD(command);  /// selects the first location of CG ram 
	
	while (x < 8)
	{
		putcLCD(character[x]);
		x++; 		
	}	
	cmd2LCD(0x80);   /// send curser back home
}







