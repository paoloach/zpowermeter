//
// Created by paolo on 31/12/17.
//

#include "CS5463.h"

extern SPI_HandleTypeDef hspi1;

uint8_t CS5463::INSTANTANEOUS_CURRENT[4] = {REG_INST_CURRENT<<1, 0xFF,0xFF,0xFF};
uint8_t CS5463::RMS_CURRENT[4] = {REG_ACTIVE_POWER << 1, 0xFF,0xFF,0xFF};
uint8_t CS5463::STATUS[4] = {REG_STATUS << 1, 0xFF,0xFF,0xFF};

uint8_t CS5463::OPERATION_MODE[4] = {0b00100100, 0x00,0x00, IHPF | AFC};



static uint8_t SPIDataToRead[4];
uint32_t CS5463::getCurrent() {
    HAL_SPI_TransmitReceive(&hspi1, INSTANTANEOUS_CURRENT, SPIDataToRead, 4, HAL_MAX_DELAY);
    uint32_t a = SPIDataToRead[1];
    uint32_t b = SPIDataToRead[2];
    uint32_t c = SPIDataToRead[3];
    uint32_t result = (a << 16) | (b << 8) | c;
    return result;
}

uint32_t CS5463::getRMSCurrent() {
    HAL_SPI_TransmitReceive(&hspi1, RMS_CURRENT, SPIDataToRead, 4, HAL_MAX_DELAY);
    uint32_t a = SPIDataToRead[1];
    uint32_t b = SPIDataToRead[2];
    uint32_t c = SPIDataToRead[3];
    uint32_t result = (a << 16) | (b << 8) | c;
    return result;
}

uint32_t CS5463::getRegister(uint8_t reg) {
    GPIOA->BRR = GPIO_PIN_4;
    uint8_t SPIRequest[4] = {reg << 1, 0xFF,0xFF,0xFF};
    HAL_SPI_TransmitReceive(&hspi1, SPIRequest, SPIDataToRead, 4, HAL_MAX_DELAY);
    GPIOA->BSRR = GPIO_PIN_4;
    uint32_t a = SPIDataToRead[1];
    uint32_t b = SPIDataToRead[2];
    uint32_t c = SPIDataToRead[3];
    uint32_t result = (a << 16) | (b << 8) | c;
    return result;
}

void CS5463::setRegister(uint8_t reg, uint32_t value) {
    GPIOA->BRR = GPIO_PIN_4;
    uint8_t SPIRequest[4] = {0x40 | (reg << 1), (value >> 16)&0xFF ,(value >> 8) & 0xFF, value & 0xFF};
    HAL_SPI_Transmit(&hspi1, SPIRequest, 4, HAL_MAX_DELAY);
    GPIOA->BSRR = GPIO_PIN_4;
}

void CS5463::setCmd(uint8_t reg) {
    GPIOA->BRR = GPIO_PIN_4;
    HAL_SPI_Transmit(&hspi1, &reg, 1, HAL_MAX_DELAY);
    GPIOA->BSRR = GPIO_PIN_4;
}



