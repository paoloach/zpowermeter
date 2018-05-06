/*
 * BaseAcccess.h
 *
 *  Created on: 18 gen 2017
 *      Author: paolo
 */

#ifndef BASEACCCESS_H_
#define BASEACCCESS_H_

#include "stm32f1xx_hal.h"
#include "Pins.h"

inline void dataPortToWrite() {
    GPIO_InitTypeDef gpioInit;

    gpioInit.Pin = GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpioInit);
}

inline void dataPortToRead() {
    GPIO_InitTypeDef gpioInit;

    gpioInit.Pin = GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                   |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    gpioInit.Mode = GPIO_MODE_INPUT;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpioInit);
}



inline void setData(uint8_t data) {
    uint32_t d = (uint32_t )data << 3;
    uint32_t dr = (data ^ 0xFF) << (3 + 16);

    GPIOB->BSRR = d | dr;
}


inline uint8_t readData() {
    return (GPIOB->IDR >> 3) & 0xFF;
}

inline void resetOn() {
    RESET_PORT->BRR=RESET_PIN;
}

inline void resetOff() {
    RESET_PORT->BSRR=RESET_PIN;
}

inline void activeWR() {
    WR_PORT->BRR=WR_PIN;
}

inline void idleWR() {
    WR_PORT->BSRR=WR_PIN;
}

inline void activeRD() {
    RD_PORT->BRR=RD_PIN;
}

inline void idleRD() {
    RD_PORT->BSRR=RD_PIN;
}

inline void activeCS() {
    CS_PORT->BRR=CS_PIN;
}

inline void idleCS() {
    CS_PORT->BSRR=CS_PIN;
}

inline void command() {
    RS_PORT->BRR=RS_PIN;
}

inline void data() {
    RS_PORT->BSRR=RS_PIN;
}

inline void strobeWR() {
    activeWR();
// Wait for 70 ns
    __asm(
            "nop\n" // 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
    );
    idleWR();
}

inline void write(uint8_t value) {
    setData(value);
    strobeWR();
}




#endif /* BASEACCCESS_H_ */
