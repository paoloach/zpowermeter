/*
 * Pins.h
 *
 *  Created on: 16 gen 2017
 *      Author: paolo
 */

#ifndef PINS_H_
#define PINS_H_

#include "stm32f1xx_hal.h"


/**
 * RESET -> A8
 * CS --> A9
 * RS --> A10
 * WR --> B14
 * RD --> B15
 * D0 --> B3
 * D1 --> B4
 * D2 --> B5
 * D3 --> B6
 * D4 --> B7
 * D5 --> B8
 * D6 --> B9
 * D7 --> B10
 */


#define RESET_PORT GPIOA
#define RESET_PIN  GPIO_PIN_8
#define CS_PORT GPIOA
#define CS_PIN  GPIO_PIN_9
#define RS_PORT GPIOA
#define RS_PIN  GPIO_PIN_10
#define WR_PORT GPIOB
#define WR_PIN  GPIO_PIN_14
#define RD_PORT GPIOB
#define RD_PIN  GPIO_PIN_15

#endif /* PINS_H_ */
