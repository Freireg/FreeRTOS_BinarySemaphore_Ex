/*
 * Printer.h
 *
 *  Created on: Mar 29, 2021
 *      Author: GF Almeida
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "main.h"
#include "stm32f4xx.h"
#include "User.h"

/**
  * @ Printer functions
  */
#define SET_HEIGHT_4	0x04
#define SET_HEIGHT_3	0x03
#define SET_HEIGHT_2	0x02
//Formatting functions start:

void line_feed(void){ //Run over one line
	uint8_t lf[] = " ";
	lf[1] = 0x0A;
	HAL_UART_Transmit(&huart2, lf, 2, 500);
}

void left_margin(int input){ //Set left margin start
	uint8_t tformat[3];
	tformat[0] = 0x1B;
	tformat[1] = 0x6C;
	tformat[2] = input;
	HAL_UART_Transmit(&huart2, tformat, 3, 500);
}

void enlarge (int input){ //Set the width to 2 and the height to the input value
	uint8_t width[3];
	width[0] = 0x1B;
	width[1] = 0x55;
	width[2] = 0x02;
	HAL_UART_Transmit(&huart2, width, 3, 500);
	uint8_t height[3];
	height[0] = 0x1B;
	height[1] = 0x56;
	height[2] = input;
	HAL_UART_Transmit(&huart2, height, 3, 500);
}

void receive_data(uint8_t*pName, uint8_t sizeName, uint8_t*pAge, uint8_t sizeAge, uint8_t*pId, uint8_t*pNro, uint8_t*pSexo, uint8_t sizeGender){
	struct dados_cadastrais paciente; //defined struct variable

//changing struct values to be sent
	memcpy(paciente.name, pName, sizeName);
	paciente.name[sizeName] = 0x0A;
	memcpy(paciente.age, pAge, sizeAge);
	paciente.age[sizeAge] = 0x0A;

	memcpy(paciente.id, pId,2);
	paciente.id[2] = 0x0A;
	memcpy(paciente.nro, pNro, 2);
	paciente.nro[2] = 0x0A;
	memcpy(paciente.gender, pSexo, 10);
	paciente.gender[sizeGender] = 0x0A;

	send_data(paciente);
}

void send_data(struct dados_cadastrais user){
	uint8_t title[] = "Test Report";
	int sizeTitle = sizeof(title);
	title[sizeTitle-1] = 0x0A;
	uint8_t line[] = "- - - - - - - - - - - - ";
	int sizeLine = sizeof(line);
	line[sizeLine-1] = 0x0A;

	enlarge(SET_HEIGHT_3);
	line_feed();
	line_feed();
	HAL_UART_Transmit(&huart2, line, sizeLine, 500);
	HAL_UART_Transmit(&huart2, "Item   Resultado   Ref.", 23, 500);
	line_feed();
	HAL_UART_Transmit(&huart2, line, sizeLine, 500);
	HAL_UART_Transmit(&huart2,"Hora: ", 6, 500);
	line_feed();
	HAL_UART_Transmit(&huart2,"Codigo de barras: ", 18, 500);
	line_feed();
	HAL_UART_Transmit(&huart2, user.age, sizeof(user.age) +1, 500);
	HAL_UART_Transmit(&huart2, user.gender, sizeof(user.gender)+1, 1000);
	HAL_UART_Transmit(&huart2, user.name, sizeof(user.name) +1, 500);
	HAL_UART_Transmit(&huart2, user.id, 3, 500);
	HAL_UART_Transmit(&huart2, user.nro, 4, 500);
	HAL_UART_Transmit(&huart2, line, sizeLine, 500);
	left_margin(0x0C);
	HAL_UART_Transmit(&huart2, title, sizeTitle+1, 500);
	left_margin(0x00);
	line_feed();
}

#endif /* PRINTER_H_ */
