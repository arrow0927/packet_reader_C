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


uint8_t*  createTestBuffer()
{
	uint8_t *buffer = malloc(14*sizeof(uint8_t));
	for(int i = 0; i < 14; i++)
	{
		buffer[i] = 25-i ;
	}
	return buffer;
} 



int main()
{
	uint8_t *buff = createTestBuffer();
	for (int i=0; i < 14; i++)
	{
		printf("[%d], value=%d\n",i, buff[i]);						
	}
	handleReport(buff,  14);
	free(buff);
    return 0;
}
