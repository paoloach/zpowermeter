//
// Created by paolo on 06/05/18.
//
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "ADE7953.h"

extern SPI_HandleTypeDef hspi1;

void ADE7953::init() {
    HAL_GPIO_WritePin(RESET_CS5463_GPIO_Port, RESET_CS5463_Pin, GPIO_PIN_RESET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(RESET_CS5463_GPIO_Port, RESET_CS5463_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
    version =read(Version);
}

uint8_t ADE7953::read(ADE_Register8Bit reg) {
    HAL_GPIO_WritePin(CS_SPI1_GPIO_Port, CS_SPI1_Pin, GPIO_PIN_RESET);
    uint8_t data[3];
    data[0] = (reg >> 8) & 0xFF;
    data[1] = reg  & 0xFF;
    data[2] = 0x80;

    HAL_SPI_Transmit(&hspi1, data,3, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, data,1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_SPI1_GPIO_Port, CS_SPI1_Pin, GPIO_PIN_SET);
    return data[0];
}
