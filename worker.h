/*
	worker.h
	Question 1 of coding challenge
	Ash Mulekar
	amulekar@gmail.com
	May 13, 2014
*/


uint16_t getMouseDx(uint8_t *buff);
uint16_t getMouseDy(uint8_t *buff);
uint32_t getMouseTimeStamp(uint8_t *buff);
uint8_t getButtonStates(uint8_t *buff);
void printBits(uint16_t i , int numBits);
void handleReport(uint8_t *buff, uint16_t length);

