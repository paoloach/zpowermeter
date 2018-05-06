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
CS5463 cs5463;
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

    GPIOA->BSRR = GPIO_PIN_3;

//    HAL_SPI_Transmit(&hspi1, CS5463::OPERATION_MODE, 4, HAL_MAX_DELAY);
//    graphics->drawString(Point(0, 200), "Start calibration");
//    cs5463.setRegister(REG_MODE, VHPF | IHPF);
//    //Timer::sleep(10);
//    cs5463.setCmd(CALIBRATION_CURRENT_AC_OFFSET);
//    while (true) {
//        uint32_t status = cs5463.getRegister(REG_STATUS);
//        sprintf(buffer, "Status: %06X", status);
//        graphics->drawString(Point(0, 160), buffer);
//        uint32_t mode = cs5463.getRegister(REG_MODE);
//        sprintf(buffer, "mode: %06X", mode);
//        graphics->drawString(Point(0, 140), buffer);
//        if (status & 0x800000)
//            break;
//    }
//    graphics->drawString(Point(0, 200), "END calibration ");
//    HAL_Delay(1000);
    //cs5463.setRegister(REG_MODE, VHPF | IHPF);
    initCS();
    graphics->fillRect(Point(0, 0), 320, 280, WHITE);

}

void MainLoop::initCS() const {
    cs5463.setRegister(REG_CURRENT_AC_OFFSET, -310000);
    cs5463.setRegister(REG_POWER_OFFSET, 1200000);
    cs5463.setRegister(REG_VOLTAGE_AC_OFFSET, -900000);
    cs5463.setRegister(REG_MODE,  VHPF | IHPF | AFC);
    cs5463.setRegister(REG_CONFIGURATION, 0x000001);
    cs5463.setCmd(START_CONVERSIONS);
}

int count = 0;

void MainLoop::mainLoop() {
    initCS();
    uint32_t regStatus = cs5463.getRegister(REG_STATUS);
    count = 0;

    while ((regStatus & 0x800000) == 0) {
        count++;
        regStatus = cs5463.getRegister(REG_STATUS);
    };
    //cs5463.setCmd(START_CONVERSIONS_SINGLE);
    uint32_t regRmsCur = cs5463.getRegister(REG_RMS_CUR);
    uint32_t regRmsVolt = cs5463.getRegister(REG_RMS_VOLT);
    uint32_t regPower = cs5463.getRegister(REG_ACTIVE_POWER);
    uint32_t regVACOff = cs5463.getRegister(REG_VOLTAGE_AC_OFFSET);
    uint32_t regIACOff = cs5463.getRegister(REG_CURRENT_AC_OFFSET);
    uint32_t regReactive = cs5463.getRegister(REG_AVERAGE_REACTIVE_POWER);

    uint32_t  cur = ((uint64_t )regRmsCur*1000)/((uint64_t )4*0xFFFFFF);
    sprintf(buffer, "rms cur: %d     ", regRmsCur);
    graphics->drawString(Point(0, 20), buffer);
    sprintf(buffer, "rms volt: %d     ", regRmsVolt);
    graphics->drawString(Point(0, 40), buffer);
    sprintf(buffer, "status: %06X     ", regStatus);
    graphics->drawString(Point(0, 80), buffer);
    sprintf(buffer, "VACOff: %d     ", getInt(regVACOff));
    graphics->drawString(Point(0, 100), buffer);
    sprintf(buffer, "IACOff: %d     ", getInt(regIACOff));
    graphics->drawString(Point(0, 120), buffer);
    sprintf(buffer, "Reactive: %d     ", getInt(regReactive));
    graphics->drawString(Point(0, 140), buffer);


    int32_t power = getInt(regPower);
    sprintf(buffer, "Power: %d    ", power);
    graphics->drawString(Point(0, 60), buffer);




//    cs5463.setRegister(REG_STATUS, 0);
//    count++;
//    if (newData) {
//        if (endData) {
//            graphics->fillRect(Point(0, 0), graphics->width - 1, graphics->height - 1, Color6Bit(255, 255, 255));
//            uint32_t max = 0;
//            for (int i = 10; i < 320; i++) {
//                uint32_t value = current[i];
//                if (current[i] > 0x800000)
//                    value = (~value & 0xFFFFFF);
//                if (value > max)
//                    max = value;
//            }
//            uint32_t scale = max / 100;
//            if (scale > 1000) {
//                scale = 1000 * (scale / 1000);
//            } else if (scale > 100) {
//                scale = 100 * (scale / 100);
//            }
//
    //           sprintf(buffer, "scale: %u", scale);

    //           graphics->drawString(Point(0,200), buffer);
    //           sprintf(buffer, "max: %u", max);
//            graphics->drawString(Point(0,180), buffer);
//            uint32_t reg= cs5463.getRegister(REG_ACTIVE_POWER);
//            sprintf(buffer, "Power: %06X", reg);
//            graphics->drawString(Point(0,160), buffer);
//            cs5463.setRegister(REG_STATUS, 0);

//            uint32_t  prevY=120;
//            for(int i = 10; i < 320; i++ ) {
//                uint32_t y;
//                if (current[i] > 0x800000) {
//                    uint32_t value = (~current[i] & 0xFFFFFF) ;
//                    value = value / scale;
//                    y = 120-value;
//                } else {
//                    uint32_t value = current[i];
//                    value = value / scale;
//                    y = value + 120;
//                }
//                graphics->drawLine(Point(i-1, prevY),Point(i, y), Color6Bit(0,0,0));
//                prevY = y;
//
//            }
//
//
//            iter = current;
//            endData=false;
//            newData= false;
//
//        } else {
//            GPIOA->BRR = GPIO_PIN_4;
//
//            *iter = cs5463.getCurrent();
//            newData = false;
//            GPIOA->BSRR = GPIO_PIN_4;
//        }
//    }
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