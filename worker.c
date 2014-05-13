#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/*
	worker.c
	Question 1 of coding challenge
	Ash Mulekar
	amulekar@gmail.com
	May 13, 2014
*/


/* Print statements are left in functions deliberately to aid in debugging and seeing values */


/* utlity function that helps see the underlying bits of a variable */
void printBits(uint16_t dx , int numBits)
{	
	for (int y= numBits-1; y >= 0; y-- )
	{
		if((dx & (1 << y )) != 0)
		  	printf("1");
		else
		  	printf("0");
	}
	printf("\n");
}


/* 
Mouse deltas are extracted from Byte[2] and Byte[4] 
There are 10 bits in the mouse deltas, which would require variable of
size at least "uint16_t". 
*/
uint16_t getMouseDx(uint8_t *buff)
{
	uint16_t dx = buff[2]; 
	uint16_t dx_upper = buff[4]; 
	dx_upper = dx_upper & (12) ;
	dx_upper = dx_upper << 6 ;	
	dx = dx | dx_upper;

	return dx;
}

uint16_t getMouseDy(uint8_t *buff)
{
	uint16_t dy = buff[3]; 
	uint16_t dy_upper = buff[4]; 

	dy_upper = dy_upper & (48) ;
	dy_upper = dy_upper << 4 ;	
	dy = dy | dy_upper;
	
	return dy;
}

/*
Time stamp is extracted from Byte[4], Byte[5], Byte[6] and the previous packet as well
*/
uint32_t getMouseTimeStamp(uint8_t *buff)
{
	uint32_t ts_lower = buff[4];
	ts_lower = ts_lower & (192);
	ts_lower = ts_lower >> 6;	
	uint32_t ts_mid = buff[5];
	ts_mid = ts_mid << 2;	
	uint32_t ts_upper = buff[6];	
	ts_upper = ts_upper << 10;	
	uint32_t ts = ts_lower | ts_mid | ts_upper;
	
	return ts;
	
}


/*
Button States extracted from Byte[4]
*/
uint8_t getButtonStates(uint8_t *buff)
{
	uint8_t buttonBits = buff[4];
	buttonBits = buttonBits & 3;
	
	return buttonBits;
}

void handleReport(uint8_t *buff, uint16_t length)
{
	int s = 1;
	uint32_t ts , ts1;
	uint16_t dx;
	uint16_t dy;
	uint8_t leftButtonState;
	uint8_t rightButtonState;
	
	for (int j=0; j<length; j++)
	{	
		if(s == 1)
			s = 0;
		else
			s = 1;
		
		dx =  getMouseDx(buff);
		
		dy =  getMouseDy(buff);
		
		if(s == 1)
		{
			ts1 = getMouseTimeStamp(buff);
		}
		else
		{
			ts = getMouseTimeStamp(buff);
		}
		
	
		uint8_t buttonBits =  getButtonStates(buff);
	
		leftButtonState = buttonBits & 2;
	
		rightButtonState = buttonBits & 1;

		if(s == 1)
		{
			ts1 = ts1 << 18;
			ts = ts1 | ts;	
		}
	}
	printf("dx_total(decimal) = %d\n", dx);
	printf("Mouse Delta X Value in binary=");
	printBits(dx , 16);
	
	printf("dy_total(decimal) = %d\n", dy);
	printf("Mouse Delta Y Value in binary=");
	printBits(dy , 16);
	
	printf("Left Button State= ");
	printBits(leftButtonState , 8);
	
	printf("Right Button State= ");
	printBits(rightButtonState , 8);
	
	printf("final timestamp ts= ");
	printBits(ts , 32);
	
}
