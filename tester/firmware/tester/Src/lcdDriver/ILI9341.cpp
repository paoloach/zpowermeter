/*
 * ILI9341.cpp
 *
 *  Created on: 26 feb 2017
 *      Author: paolo
 */

#include "ILI9341.h"

namespace ILI9341 {

ILI9341::ILI9341() {
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGTH;
    driver = LcdID::ID_9341;
    activeCS();

    resetOn();
    HAL_Delay(5);
    resetOff();
    HAL_Delay(150);

    auto ILI9341Id = ReadId::read();

    if (ILI9341Id[0] == 0x00 && ILI9341Id[1] == 0x93 && ILI9341Id[2] == 0x41) {
        driver = LcdID::ID_9341;
    }
    if (ILI9341Id[0] == 0x00 && ILI9341Id[1] == 0x93 && ILI9341Id[2] == 0x42) {
        driver = LcdID::ID_9342;
    }

    DisplayOff::apply();
    PowerCtl1::write(0x23);
    PowerCtl2::write(0x10);
    VCOMCtl1::write(0x3e28);
    VCOMCtl2::write(0x86);
    //VCOMCtl2::write(0xC0);
    if (driver == LcdID::ID_9341)
        MemAccessCtrl::write(MADCTL_MY);
   if (driver == LcdID::ID_9342)
        MemAccessCtrl::write(MADCTL_MX);
    PixelFormatSet::write(0x66);
    FrameCtrl::write(0x1B00);
    DisplayFnCtl::write(0x08, 0x82, 0x27);
    EntryModeSet::write(0x07);
    DisplayInvertOn::apply();
    SleepOff::apply();
    HAL_Delay(150);
    DisplayOn::apply();
    HAL_Delay(500);

    setAddrWindow(0, 0, width - 1, height - 1);

    flood(Color6Bit(255,255,255), width*height);

    idleCS();
}

bool ILI9341::checkPresence() {
    activeCS();
    resetOn();
    HAL_Delay(5);
    resetOff();
    HAL_Delay(150);

    bool result = false;
    auto ILI9341Id = ReadId::read();
    idleCS();

    if (ILI9341Id[0] == 0x00 && ILI9341Id[1] == 0x93 && ILI9341Id[2] == 0x41){
        result = true;
    }
    if (ILI9341Id[0] == 0x00 && ILI9341Id[1] == 0x93 && ILI9341Id[2] == 0x42){
        result = true;
    }
    return result;
}

void ILI9341::setAddrWindow(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    ColAddrSet::write((left >> 8), left, right >> 8, right);
    PageAddrSet::write(top >> 8, top, bottom >> 8, bottom);
}

void ILI9341::flood(Color6Bit color, uint32_t len) {
    MemoryWrite::write(color, len);
}

void ILI9341::drawPixel(Point p, Color6Bit color) {
    if ((p.x < 0) || (p.y < 0) || (p.x >= width) || (p.y >= height))
        return;
    activeCS();
    setAddrWindow(p.x, p.y, width - 1, height - 1);
    MemoryWrite::write(color);
    idleCS();
}

void ILI9341::drawPixelInternal(Point && p, Color6Bit && color) {
    setAddrWindow(p.x, p.y, width - 1, height - 1);
    MemoryWrite::write(color);
}

} // end namespace ILI9341
