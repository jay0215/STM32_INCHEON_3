 /*
 * myLib.c
 *
 *  Created on: Nov 15, 2024
 *      Author: user
 */
#include "main.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;

//#include "C:\Users\user\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.1\Drivers\STM32F4xx_HAL_Driver\Inc\stm32f4xx_hal_i2c.h"

void StandBy()
{
	while(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin));
}
void ProgramStart(char * str)
{
	//printf("\033[2J\033[0;0H");// esc
	cls();
	Cursor(0,0);
	printf("Program Name - %s\r\n", str);
	printf("Press Blue-button(B1) to Start...\r\n");
	StandBy();
	setvbuf(stdin, NULL, _IONBF, 0); // buffer clear
}

int __io_getchar(void)
{
	char ch;
	while(!(HAL_UART_Receive(&huart2, &ch, 1, 10) == HAL_OK));
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
	if(ch == '\r') HAL_UART_Transmit(&huart2, "\n", 1, 10);
	return ch;
}

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10); //
	return ch;
}

void cls()
{

	printf("\033[2J");
}
void Cursor(int x, int y)
{
	char buf[20];
	sprintf(buf,"\033[%d;%dH",y,x);
	//printf("%s",buf);
	puts(buf);
}


