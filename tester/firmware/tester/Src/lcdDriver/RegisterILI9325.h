/*
 * RegisterILI9325.h
 *
 *  Created on: 20 gen 2017
 *      Author: paolo
 */

#ifndef REGISTERILI9325_H_
#define REGISTERILI9325_H_

#include "BaseAcccess.h"
#include "GFX.h"

enum class ILI9325_REG {
    ILI9325_INVALDREG = 0xFFFF,
    WAIT = 0xFFFE,
    ILI9325_StartOdc = 0x00,
    ILI9325_DriverCodeRead = 0x00,
    ILI9325_DriverOutControl = 0x01,
    ILI9325_LCDDriverControl = 0x02,
    ILI9325_EntryMode = 0x03,
    ILI9325_ResizeCtrl = 0x04,
    ILI9325_DisplCtrl1 = 0x07,
    ILI9325_DisplCtrl2 = 0x08,
    ILI9325_DisplCtrl3 = 0x09,
    ILI9325_DisplCtrl4 = 0x0A,
    S6D0129_FrameCycleControl = 0x0B,
    ILI9325_RGBCtrll = 0x0C,
    ILI9325_FrmMarkerPos = 0x0D,
    ILI9325_RGBCtrl2 = 0x0F,


    ILI9325_PowerCtrl1 = 0x10,
    ILI9325_PowerCtrl2 = 0x11,
    ILI9325_PowerCtrl3 = 0x12,
    ILI9325_PowerCtrl4 = 0x13,
    S6D0129_PowerCtrl4 = 0x13,
    ILI9320_PowerCtrl4 = 0x14,
    ILI9325_RamAddressHor = 0x20,
    ILI9325_RamAddressVert = 0x21,
    ILI9325_RamRW = 0x22,
    ILI9325_PowerCtrl7 = 0x29,
    ILI9325_FrameCtrl = 0x2B,
    ILI9325_GammCtrl1 = 0x30,
    ILI9325_GammCtrl2 = 0x31,
    ILI9325_GammCtrl3 = 0x32,
    ILI9325_GammCtrl4 = 0x35,
    ILI9325_GammCtrl5 = 0x36,
    ILI9325_GammCtrl6 = 0x37,
    ILI9325_GammCtrl7 = 0x38,
    ILI9325_GammCtrl8 = 0x39,
    ILI9325_GammCtrl9 = 0x3C,
    ILI9325_GammCtrl10 = 0x3D,

    S6D0129_GammCtrl1 = 0x30,
    S6D0129_GammCtrl2 = 0x31,
    S6D0129_GammCtrl3 = 0x32,
    S6D0129_GammCtrl4 = 0x33,
    S6D0129_GammCtrl5 = 0x34,
    S6D0129_GammCtrl6 = 0x35,
    S6D0129_GammCtrl7 = 0x36,
    S6D0129_GammCtrl8 = 0x37,
    S6D0129_GammCtrl9 = 0x38,
    S6D0129_GammCtrl10 = 0x39,

    S6D0129_GateScanPosizion = 0x40,
    S6D0129_VerticalScrollControl = 0x41,
    S6D0129_ScreenDriverPosEnd1 = 0x42,
    S6D0129_ScreenDriverPosStart1 = 0x43,
    S6D0129_ScreenDriverPosEnd2 = 0x44,
    S6D0129_ScreenDriverPosStart2 = 0x45,
    S6D0129_HorWindowAddress = 0x46,
    S6D0129_VertWindowAddressEnd = 0x47,
    S6D0129_VertWindowAddressStart = 0x48,
    ILI9325_HorStart = 0x50,
    ILI9325_HorEnd = 0x51,
    ILI9325_VertStart = 0x52,
    ILI9325_VertEnd = 0x53,
    ILI9325_DriverOutputCtrl2 = 0x60,
    ILI9325_BaseDisplayCtrl = 0x61,
    ILI9325_VertScrollCtrl = 0x6A,
    ILI9320_PartImage1Display=0x80,
    ILI9320_PartImage1AresStart=0x81,
    ILI9320_PartImage1AreaEnd=0x82,
    ILI9320_PartImage2Display=0x83,
    ILI9320_PartImage2AresStart=0x84,
    ILI9320_PartImage2AreaEnd=0x85,

    ILI9325_PanelIfCtrl1 = 0x90,
    ILI9325_PanelIfCtrl2 = 0x92,
    ILI9320_PanelIfCtrl3= 0x93,
    ILI9325_PanelIfCtrl4 = 0x95,
    ILI9320_PanelIfCtrl5 = 0x97,
    ILI9320_PanelIfCtrl6 = 0x98
};

class RegisterBaseILI9325 {
public:
    static void writeIndex(uint8_t index) {
        RS_PORT->BRR = RS_PIN;
        WR_PORT->BRR = WR_PIN;
        setData(0);
        WR_PORT->BSRR = WR_PIN;
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        WR_PORT->BRR = WR_PIN;
        setData(index);
        WR_PORT->BSRR = WR_PIN;
    }

    static void writeData(uint16_t data) {
        WR_PORT->BRR = WR_PIN;
        setData(data >> 8);
        WR_PORT->BSRR = WR_PIN;
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        WR_PORT->BRR = WR_PIN;
        // Wait for 50 ns
        setData(data); // Use more that 50ns
        WR_PORT->BSRR = WR_PIN;
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
    }

    static void writeStrobe() {
        activeWR();
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );

        idleWR();
        // wait 50ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        activeWR();
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        idleWR();
    }
};

class RegisterWriteBaseILI9325: public RegisterBaseILI9325 {
};

class RegisterReadBaseILI9325: public RegisterBaseILI9325 {
public:
    static uint16_t read16Bit() {
        RD_PORT->BRR = RD_PIN;
        uint8_t hi = ::readData();
        RD_PORT->BSRR = RD_PIN;
        // wait 150 ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );

        RD_PORT->BRR = RD_PIN;
        uint8_t low = ::readData();
        // wait 150 ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        RD_PORT->BSRR = RD_PIN;
        return ((uint16_t) hi << 8) | low;
    }
};

template<ILI9325_REG I>
class RegisterReadILI9325: public RegisterReadBaseILI9325 {
public:
    static uint16_t get() {
        RegisterBaseILI9325::writeIndex(static_cast<uint16_t>(index));
        RS_PORT->BRR=RS_PIN;
        dataPortToRead();
        RS_PORT->BSRR=RS_PIN;
        uint16_t value = read16Bit();
        dataPortToWrite();
        return value;
    }
private:
    static constexpr ILI9325_REG index = I;
};

template<ILI9325_REG I>
class RegisterWriteILI9325: public RegisterReadBaseILI9325 {
public:
    static void write(uint16_t dataToWrite) {
        command();
        RegisterBaseILI9325::writeIndex(static_cast<uint8_t>(index));
        data();
        RegisterBaseILI9325::writeData(dataToWrite);
    }
private:
    static constexpr ILI9325_REG index = I;
};

class ILI9325_RamRW: public RegisterReadBaseILI9325 {
public:
    static void write(Color6Bit color) {
        command();
        RegisterBaseILI9325::writeIndex(static_cast<uint8_t>(ILI9325_REG::ILI9325_RamRW));
        data();
        activeWR();
        setData(color.getRed());
        idleWR();
        // wait 50ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        activeWR();
        // Wait for 50 ns
        setData(color.getGreen()); // Use more that 50ns
        idleWR();
        // wait 50ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        activeWR();
        // Wait for 50 ns
        setData(color.getBlue()); // Use more that 50ns
        idleWR();
    }
    static void write(Color6Bit color, uint32_t len) {
        for (; len > 0; len--) {
            command();
            RegisterBaseILI9325::writeIndex(static_cast<uint16_t>(ILI9325_REG::ILI9325_RamRW));
            data();
            activeWR();
            setData(color.getRed());
            idleWR();
            // wait 50ns
            __asm(
                    "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            activeWR();
            // Wait for 50 ns
            setData(color.getBlue()); // Use more that 50ns
            idleWR();
            // wait 50ns
            __asm(
                    "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            activeWR();
            // Wait for 50 ns
            setData(color.getGreen()); // Use more that 50ns
            idleWR();
        }
    }
};

class ILI9325_PowerCtrl1: public RegisterWriteILI9325<ILI9325_REG::ILI9325_PowerCtrl1> {
public:
    void static setDriverQuality(DriverQuality quality, uint16_t otherBits) {
        uint8_t val = otherBits & 0xC7FF;
        switch (quality) {
        case DriverQuality::OFF:
            break;
        case DriverQuality::SMALL:
            val |= 0x0800;
            break;
        case DriverQuality::MEDIUM_LOW:
            val |= 0x1000;
            break;
        case DriverQuality::MEDIUM:
            val |= 0x1800;
            break;
        case DriverQuality::MEDIUM_HIGH:
            val |= 0x2000;
            break;
        case DriverQuality::HIGHT:
            val |= 0x2800;
            break;
        }
        RegisterWriteILI9325::write(val);
    }
};

using ILI9325_StartOdc = RegisterWriteILI9325<ILI9325_REG::ILI9325_StartOdc>;
using ILI9325_DriverCodeRead = RegisterReadILI9325<ILI9325_REG::ILI9325_DriverCodeRead>;
using ILI9325_DriverOutControl = RegisterWriteILI9325<ILI9325_REG::ILI9325_DriverOutControl>;
using ILI9325_LCDDriverControl = RegisterWriteILI9325<ILI9325_REG::ILI9325_LCDDriverControl>;

using ILI9325_EntryMode = RegisterWriteILI9325<ILI9325_REG::ILI9325_EntryMode>;
using ILI9325_ResizeCtrl = RegisterWriteILI9325<ILI9325_REG::ILI9325_ResizeCtrl>;
using ILI9325_DisplCtrl1 = RegisterWriteILI9325<ILI9325_REG::ILI9325_DisplCtrl1>;
using ILI9325_DisplCTrl2 = RegisterWriteILI9325<ILI9325_REG::ILI9325_DisplCtrl2>;
using ILI9325_DisplCtrl3 = RegisterWriteILI9325<ILI9325_REG::ILI9325_DisplCtrl3>;
using ILI9325_DisplCTrl4 = RegisterWriteILI9325<ILI9325_REG::ILI9325_DisplCtrl4>;
using ILI9325_RGBCtrll = RegisterWriteILI9325<ILI9325_REG::ILI9325_RGBCtrll>;
using ILI9325_FrmMarkerPos = RegisterWriteILI9325<ILI9325_REG::ILI9325_FrmMarkerPos>;
using ILI9325_RGBCtrl2 = RegisterWriteILI9325<ILI9325_REG::ILI9325_RGBCtrl2>;
using ILI9325_PowerCtrl2 = RegisterWriteILI9325<ILI9325_REG::ILI9325_PowerCtrl2>;
using ILI9325_PowerCtrl3 = RegisterWriteILI9325<ILI9325_REG::ILI9325_PowerCtrl3>;
using ILI9325_PowerCtrl4 = RegisterWriteILI9325<ILI9325_REG::ILI9325_PowerCtrl4>;
using ILI9325_RamAddressHor = RegisterWriteILI9325<ILI9325_REG::ILI9325_RamAddressHor>;
using ILI9325_RamAddressVert = RegisterWriteILI9325<ILI9325_REG::ILI9325_RamAddressVert>;
using ILI9325_PowerCtrl7 = RegisterWriteILI9325<ILI9325_REG::ILI9325_PowerCtrl7>;
using ILI9325_FrameCtrl = RegisterWriteILI9325<ILI9325_REG::ILI9325_FrameCtrl>;
using ILI9325_GammCtrl1= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl1>;
using ILI9325_GammCtrl2= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl2>;
using ILI9325_GammCtrl3= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl3>;
using ILI9325_GammCtrl4= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl4>;
using ILI9325_GammCtrl5= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl5>;
using ILI9325_GammCtrl6= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl6>;
using ILI9325_GammCtrl7= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl7>;
using ILI9325_GammCtrl8= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl8>;
using ILI9325_GammCtrl9= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl9>;
using ILI9325_GammCtrl10= RegisterWriteILI9325<ILI9325_REG::ILI9325_GammCtrl10>;
using ILI9325_HorStart= RegisterWriteILI9325<ILI9325_REG::ILI9325_HorStart>;
using ILI9325_HorEnd= RegisterWriteILI9325<ILI9325_REG::ILI9325_HorEnd>;
using ILI9325_VertStart= RegisterWriteILI9325<ILI9325_REG::ILI9325_VertStart>;
using ILI9325_VertEnd= RegisterWriteILI9325<ILI9325_REG::ILI9325_VertEnd>;
using ILI9325_DriverOutputCtrl2= RegisterWriteILI9325<ILI9325_REG::ILI9325_DriverOutputCtrl2>;
using ILI9325_BaseDisplayCtrl= RegisterWriteILI9325<ILI9325_REG::ILI9325_BaseDisplayCtrl>;
using ILI9325_VertScrollCtrl= RegisterWriteILI9325<ILI9325_REG::ILI9325_VertScrollCtrl>;
using ILI9325_PanelIfCtrl1= RegisterWriteILI9325<ILI9325_REG::ILI9325_PanelIfCtrl1>;
using ILI9325_PanelIfCtrl2= RegisterWriteILI9325<ILI9325_REG::ILI9325_PanelIfCtrl2>;
using ILI9325_PanelIfCtrl4= RegisterWriteILI9325<ILI9325_REG::ILI9325_PanelIfCtrl4>;

using S6D019_GateScanPosizion= RegisterWriteILI9325<ILI9325_REG::S6D0129_GateScanPosizion>;
using S6D019_VerticalScrollControl= RegisterWriteILI9325<ILI9325_REG::S6D0129_VerticalScrollControl>;
using S6D019_ScreenDriverPosEnd1= RegisterWriteILI9325<ILI9325_REG::S6D0129_ScreenDriverPosEnd1>;
using S6D019_ScreenDriverPosStart1= RegisterWriteILI9325<ILI9325_REG::S6D0129_ScreenDriverPosStart1>;
using S6D019_ScreenDriverPosEnd2= RegisterWriteILI9325<ILI9325_REG::S6D0129_ScreenDriverPosEnd2>;
using S6D019_ScreenDriverPosStart2= RegisterWriteILI9325<ILI9325_REG::S6D0129_ScreenDriverPosStart2>;
using S6D019_HorWindowAddress= RegisterWriteILI9325<ILI9325_REG::S6D0129_HorWindowAddress>;
using S6D019_VertWindowAddressEnd= RegisterWriteILI9325<ILI9325_REG::S6D0129_VertWindowAddressEnd>;
using S6D019_VertWindowAddressStart= RegisterWriteILI9325<ILI9325_REG::S6D0129_VertWindowAddressStart>;

#endif /* REGISTERILI9325_H_ */

