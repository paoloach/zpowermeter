//
// Created by paolo on 31/12/17.
//

#ifndef TESTER_CS5463_H
#define TESTER_CS5463_H
#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi1;
constexpr uint8_t REG_CONFIGURATION=0;
constexpr uint8_t REG_INST_CURRENT=7;
constexpr uint8_t REG_INST_VOLT=8;
constexpr uint8_t REG_ACTIVE_POWER=10;
constexpr uint8_t REG_INST_POWER=9;
constexpr uint8_t REG_RMS_CUR=11;
constexpr uint8_t REG_RMS_VOLT=12;
constexpr uint8_t REG_EPSILON=13;
constexpr uint8_t REG_POWER_OFFSET=13;
constexpr uint8_t REG_STATUS=15;
constexpr uint8_t REG_CURRENT_AC_OFFSET=16;
constexpr uint8_t REG_VOLTAGE_AC_OFFSET=17;
constexpr uint8_t REG_MODE=18;
constexpr uint8_t REG_AVERAGE_REACTIVE_POWER=  20;

constexpr uint32_t E2MODE=0x200;
constexpr uint32_t XVDEL=0x100;
constexpr uint32_t XIDEL=0x80;
constexpr uint32_t IHPF=0x40;
constexpr uint32_t VHPF=0x20;
constexpr uint32_t AFC=0x01;

constexpr uint8_t START_CONVERSIONS=0b11101000;
constexpr uint8_t START_CONVERSIONS_SINGLE=0b11100000;
constexpr uint8_t CALIBRATION_CURRENT_AC_OFFSET = 0b11001101;

class CS5463 {
public:
    uint32_t getRegister(uint8_t reg);
    void setRegister(uint8_t reg, uint32_t value);
    void setCmd(uint8_t reg);
    uint32_t getCurrent();
    uint32_t getRMSCurrent();
    void getCurrent(uint32_t * dest){
        HAL_SPI_TransmitReceive_IT(&hspi1, INSTANTANEOUS_CURRENT, reinterpret_cast<uint8_t *>(dest), 4);
    }
public:
    static uint8_t INSTANTANEOUS_CURRENT[4];
    static uint8_t RMS_CURRENT[4];
    static uint8_t STATUS[4];
    static uint8_t OPERATION_MODE[4];
};


#endif //TESTER_CS5463_H
