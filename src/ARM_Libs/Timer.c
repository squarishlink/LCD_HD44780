/*
 * Timer.c
 *
 * Created: 7/31/2013 2:33:46 PM
 *  Author: mfolz
 Very crude timer, helps me get through the tough times at night 
 T.T 
 eventually when i feel less lazy ill make it more accurate 
 */ 

#include "Timer.h"

void Delay_s(int delays){
	while (delays != 0){
		Delay_ms(1000);
		delays--;
	}
}

void Delay_ms(int delayms){
	while (delayms != 0){
		Delay_us(1000);
		delayms--;
	}
}
void Delay_us(int delayus){
	while (delayus != 0){
		Delay();
		delayus--;
	}

}

void Delay(void){
	float usdelay = 0.0;
	usdelay =(1000/ ( (1.0 / 28000000) * 1000000000 ) );
	
	while (usdelay != 0) {
		asm("NOP");
		usdelay--;
	}
}

