#include <stdio.h>
#include <conio.h>
#include "rs232.h"
// To compile : gcc -o name.exe src/PC/rs232.c src/PC/PCMain.c
// To run : name.exe

#define ESC_KEY 27
#define COMPORT 2
#define MAX_TRIES 2500000
#define RS232_ReadByte(port) _RS232_ReadByte(port,__LINE__)
#define baudrate 9600

char _RS232_ReadByte(int comport_number, int line){
	char data = -1;
	int count = 0;
	while(RS232_PollComport(comport_number, &data, 1) == 0 && count < MAX_TRIES)
		count++;
	if(count >= MAX_TRIES){
		RS232_CloseComport(COMPORT);
		printf("Attempt to read byte but comport seems not responsive\n");
		exit(-1);
	}
	return data;
}

int main(void){
	int i;
	char charReceived, char2Send = 0;
	printf("Test UART, ready to receive character!!!\n");
	RS232_OpenComport(COMPORT, baudrate);
	char2Send = getch();
	while(char2Send != ESC_KEY){
		RS232_SendByte(COMPORT, char2Send);
		charReceived = RS232_ReadByte(COMPORT);
		printf("%c", charReceived);
		char2Send = getch();
	}
	if(char2Send == ESC_KEY)
		printf("BYE\n");
	RS232_CloseComport(COMPORT);
}