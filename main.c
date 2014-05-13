#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

/*
	main.c
	Question 1 of coding challenge
	Ash Mulekar
	amulekar@gmail.com
	May 13, 2014
*/

/*
B0: report format
B1: reserved
B2: dX (bits[7:0])
B3: dY (bits[7:0])
B4[1:0]: Left/Right button states
B4[3:2]: dX (bits[9:8])
B4[5:4]: dY (bits[9:8])
B4[7:6]: timestamp (ms) bits[1:0]
B5: timestamp (ms) bits[9:2]
B6: timestamp (ms) bits[17:10]
*/

uint8_t*  createTestBuffer()
{
	uint8_t *buffer = malloc(14*sizeof(uint8_t));
	for(int i = 0; i < 14; i++)
	{
		buffer[i] = 25-i ;
		printf("[%d], value=%d\n",i, buffer[i]);
	}
	printf("\n");
	return buffer;
} 



int main()
{
	uint8_t *buff = createTestBuffer();
	handleReport(buff,  14);
	free(buff);
    return 0;
}
