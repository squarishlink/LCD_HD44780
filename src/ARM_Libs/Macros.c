/*
 * Macros.c
 *
 * Created: 7/31/2013 2:33:55 PM
 *  Author: mfolz
 */ 


char Swap_Bits(char data)
{
	char result= 0;
	char finalresult=0;
	
	for(char i = 0; i <= 7; ++i)
	{
		if (data & 1 << i) result+= (256 >> (i+1));
	}
	finalresult = 0x0F & (result >>4);
	finalresult += (0xF0 & (result << 4));
	return finalresult;
}
