#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"



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
	for (int i=0; i < 14/*sizeof(buff)*/; i++)
	{
		printf("[%d], value=%d\n",i, buff[i]);						
	}

	handleReport(buff,  14);
	
	free(buff);
    return 0;
}
