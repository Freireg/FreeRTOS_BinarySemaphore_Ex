/*
 * User.h
 *
 *  Created on: Mar 29, 2021
 *      Author: GF Almeida
 */

#ifndef USER_H_
#define USER_H_

#include "main.h"
#include "stm32f4xx.h"

/**
  * @brief  Touch panel information structure
  */
struct dados_cadastrais{ //struct parameters
		uint8_t name[40];
		uint8_t id[20];
		uint8_t age[20];
		uint8_t nro[20];
		uint8_t gender[30];
	};
//struct dados_cadastrais paciente; //defined struct variable


#endif /* USER_H_ */
