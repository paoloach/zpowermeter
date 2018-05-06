//
// Created by paolo on 31/12/17.
//

#include <stm32f103xb.h>
#include "MainLoop.h"
#include "lcdDriver/RegisterILI9325.h"
#include "lcdDriver/RegisterILI9341.h"

#include "lcdDriver/SPFD5408.h"
#include "lcdDriver/ILI9325.h"
#include "lcdDriver/ILI9341.h"
#include "lcdDriver/HX8367.h"

extern TIM_HandleTypeDef htim2;
extern SPI_HandleTypeDef hspi1;
MainLoop mainLoop;
#define DATA_SIZE 320
uint32_t current[DATA_SIZE];
uint32_t *iter = current;
uint32_t *end = current + DATA_SIZE;
bool newData;
bool endData;

void SPITxIsr(struct __SPI_HandleTypeDef *hspi);

void handleMainLoop(void) {
    mainLoop.mainLoop();
}

void mainLoopInit(void) {
    mainLoop.init();
    //   hspi1.TxISR = SPITxIsr;
    HAL_TIM_Base_Start_IT(&htim2);
    end = current + DATA_SIZE;
    newData = false;
    endData = false;
}

char buffer[40];

void MainLoop::init() {
    GPIOA->BRR = GPIO_PIN_3;
    activeCS();
    resetOn();
    HAL_Delay(5);
    resetOff();
    HAL_Delay(150);

    while (true) {
        if (ILI9341::ILI9341::checkPresence()) {
            graphics = new ILI9341::ILI9341{};
            break;
        }
    }
    graphics->setForeground(Color6Bit(0, 0, 0));
    graphics->setBackground(Color6Bit(255, 255, 255));
    graphics->setFont(&bigFont);
    GPIOA->BSRR = GPIO_PIN_4;
    HAL_Delay(200);
    GPIOA->BSRR = GPIO_PIN_4 << 16;

    graphics->fillRect(Point(0, 0), 320, 280, WHITE);

}


void MainLoop::mainLoop() {


}

int32_t MainLoop::getInt(uint32_t regPower) const {
    int32_t iValue;
    if (regPower & 0x800000) {
        iValue = 0xFFFFFF - regPower;
        iValue = -iValue;
    } else {
        iValue = regPower;
    }
    return iValue;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (endData == false) {
        iter++;
        newData = true;
        if (iter == end) {
            iter = current;
            endData = true;
        }
    }
}

void SPITxIsr(struct __SPI_HandleTypeDef *hspi) {
    uint8_t *data = reinterpret_cast<uint8_t *>(iter);
    data[0] = 10;
    iter++;
    if (iter == end) {
        iter = current;
        newData = true;
    }
}