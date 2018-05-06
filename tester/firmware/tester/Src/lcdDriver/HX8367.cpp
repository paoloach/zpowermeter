/*
 * HX8367.cpp
 *
 *  Created on: 12 mar 2017
 *      Author: paolo
 */

#include "HX8367.h"
#include "RegisterHX8367.h"

namespace HX8367 {

HX8367::HX8367() {
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGTH;
    driver = LcdID::ID_HX8367;

    activeCS();

    PTBACtrl1::write(0x00);
    PTBACtrl2::write(0x20);
    STBACtrl1::write(0x0C);
    STBACtrl2::write(0xC4);
    OPONCtrl1::write(0x38);
    OPONCtrl2::write(0x10);
    OTPS1B::write(0x01);
    GENON::write(0x10);

    PowerCtrl2::write(0x1B);
    PowerCtrl1::write(0x01);
    VCOMCtrl2::write(0x2F);
    VCOMCtrl3::write(0x57);
    VCOMCtrl1::write(0x88);

    OSCCtrl1::write(0x34);
    OSCCtrl2::write(0x01);

    DisplayMode::write(00);
    PowerCtrl6::write(0x88);
    HAL_Delay(5);
    PowerCtrl6::write(0x80);
    HAL_Delay(3);
    PowerCtrl6::write(0x90);
    HAL_Delay(5);
    PowerCtrl6::write(0xD0);
    HAL_Delay(5);
    COLMOD::write(0x66);
    PanelCharacteristic::write(0);
    DisplayCtrl3::write(0x38);
    HAL_Delay(40);
    DisplayCtrl3::write(0x3F);
    MemoryAccessCtrl::write(0x48);

    setAddrWindow(0, 0, width - 1, height - 1);
    flood(Color6Bit(0,0,0), width*height);

    idleCS();
}

bool HX8367::checkPresence() {
    activeCS();
    resetOn();
    HAL_Delay(5);
    resetOff();
    HAL_Delay(120);

    volatile auto id = ID::read();
    idleCS();

    return id == 0x67;
}

void HX8367::drawPixelInternal(Point && point, Color6Bit && color) {
    setAddrWindow(point.x, point.y, point.x+1, point.y+1);

    SRamWrite::write(color);
}

void HX8367::setAddrWindow(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    ColAddrStartH::write(left >> 8);
    ColAddrStartL::write(left & 0xFF);
    ColAddrEndH::write(right >> 8);
    ColAddrEndL::write(right & 0xFF);
    RowAddrStartH::write(top >> 8);
    RowAddrStartL::write(top & 0xFF);
    RowAddrEndH::write(bottom >> 8);
    RowAddrEndL::write(bottom & 0xFF);
}

void HX8367::flood(Color6Bit color, uint32_t len) {
    SRamWrite::write(color, len);
}

}

