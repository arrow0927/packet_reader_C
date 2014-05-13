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
	//printf("dx_lower(decimal) = %d\n", dx);
	//printf("dx_lower(binary)= ");
	//printBits(dx , 16);
	uint16_t dx_upper = buff[4]; 
	//printf("dx_upper(decimal) = %d\n",dx_upper);	
	dx_upper = dx_upper & (12) ;
	dx_upper = dx_upper << 6 ;	
	//printf("dx_upper(binary)= ");
	//printBits(dx_upper , 16);
	dx = dx | dx_upper;

	return dx;
}

uint16_t getMouseDy(uint8_t *buff)
{
	uint16_t dy = buff[3]; 
	//printf("dy_lower(decimal) = %d\n", dy);
	//printf("dy_lower(binary)= ");
	//printBits(dy , 16);
	uint16_t dy_upper = buff[4]; 
	//printf("dy_upper(decimal) = %d\n",dy_upper);	
	dy_upper = dy_upper & (48) ;
	//printf("After masking off all but bits 4,5 we have: ");
	//printBits(dy_upper , 16);
	dy_upper = dy_upper << 4 ;	
	//printf("dy_upper(binary)= ");
	//printBits(dy_upper , 16);
	dy = dy | dy_upper;
	
	return dy;
}

uint32_t getMouseTimeStamp(uint8_t *buff)
{
	printf("\n");
	uint32_t ts_lower = buff[4];
	//printf("ts_lower(decimal) = %d\n", ts_lower);
	//printf("ts_lower(binary)= ");
	//printBits(ts_lower , 32);
	ts_lower = ts_lower & (192);
	//printf("After masking off all but bits 6,7\n");
	//printBits(ts_lower , 32);
	ts_lower = ts_lower >> 6;	
	//printf("After shifting right 6 bits we have on bits 0,1: ");
	//printBits(ts_lower , 32);
	uint32_t ts_mid = buff[5];
	//printf("ts_mid(decimal) = %d\n", ts_mid);
	printf("ts_mid(binary)= ");
	//printBits(ts_mid , 32);
	ts_mid = ts_mid << 2;	
	//printf("After shifting left 2 bits\n");
	//printf("ts_mid(binary)= ");
	//printBits(ts_mid , 32);
	uint32_t ts_upper = buff[6];	
	//printf("ts_upper(decimal) = %d\n", ts_upper);
	//printBits(ts_upper , 32);
	ts_upper = ts_upper << 10;	
	//printf("ts_upper(binary) after left shift 10 bits= ");
	//printBits(ts_upper , 32);
	uint32_t ts = ts_lower | ts_mid | ts_upper;
	
	return ts;
	
}



uint8_t getButtonStates(uint8_t *buff)
{
	printf("\n");
	uint8_t buttonBits = buff[4];
	//printf("buttonBits(decimal)= %d\n", buttonBits);
	//printf("buttonBits(binary)= ");
	//printBits(buttonBits , 8);
	buttonBits = buttonBits & 3;
	//printf("After bitmasking with 3\n");
	//printBits(buttonBits , 8);
	
	return buttonBits;
}

void handleReport(uint8_t *buff, uint16_t length)
{
	int s = 1;
	
	for (int j=0; j<length; j++)
	{	
		if(s == 1)
		{
			s = 0;
		}
		else
		{
			s = 1;
		}
		
		
		uint32_t ts , ts1;
		
		uint16_t dx =  getMouseDx(buff);
		printf("dx_total(decimal) = %d\n", dx);
		printf("Mouse Delta X Value in binary=");
		printBits(dx , 16);	
		uint16_t dy =  getMouseDy(buff);
		printf("dy_total(decimal) = %d\n", dy);
		printf("Mouse Delta Y Value in binary=");
		printBits(dy , 16);

		
		if(s == 1)
		{
			ts1 = getMouseTimeStamp(buff);
			printf("timestamp ts1= ");
			printBits(ts1 , 32);
		}
		else
		{
			ts = getMouseTimeStamp(buff);
			printf("timestamp ts=");
			printBits(ts , 32);
		}
		
	
		uint8_t buttonBits =  getButtonStates(buff);
		printf("\nBoth Button States= ");
		printBits(buttonBits , 8);	
	
		uint8_t leftButtonState = buttonBits & 2;
		printf("Left Button State");
		printBits(leftButtonState , 8);
		uint8_t rightButtonState = buttonBits & 1;
		printf("Right Button State=");
		printBits(rightButtonState , 8);

		if(s == 1)
		{
			ts1 = ts1 << 18;
			ts = ts1 | ts;	
			printf("final timestamp ts=\n");
			printBits(ts , 32);

		}
	}
}
