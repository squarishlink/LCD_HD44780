/*
 * HD44780.h
 *
 * Created: 28/08/2012 9:52:43 PM
 *  Author: Michael
 */


#ifndef HD44780_H_INCLUDED
#define HD44780_H_INCLUDED

#include <asf.h>
#include <io.h>
#include <stdio.h>
#include <ioport.h>

#include "ARM_Libs/Macros.h"
#include "ARM_Libs/Timer.h"

void cmd2LCD(char cmd);   // Send command to the screen
void openLCD(void);      // send commands to setup the screen 4 bit, etc
void putcLCD(char cx);    // send char to the lcd
void putsLCD(char *ptr);  // send full string to lcd
void clearscreen(void);   // send command to clear the screen of characters
void clearline(int line);   // send command to clear a specific  line.
void cposition(int x, int y);  // set position of curser (x,y) positions starting at 0,1
int checkPress(void);   // Useful only for the DFROBOT LCD KEYPAD SHIELD(might be useful for others however you will need to change the A2D values) returns values 1-10 depending on key press
void CChar(int *character, int ccram);





#endif /* HD44780_H_ *//