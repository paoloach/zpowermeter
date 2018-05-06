/*
 * Register.h
 *
 *  Created on: 18 gen 2017
 *      Author: paolo
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include "BaseAcccess.h"

class RegisterBaseSPFD5408 {
protected:
    static void write(uint8_t r, uint32_t d) {
        activeCS();
        command();
        ::write(r);
        data();
        ::write((uint8_t) (d >> 24));
        ::write((uint8_t) (d >> 16));
        ::write((uint8_t) (d >> 8));
        ::write(d);
        idleCS();
        ;
    }

    static void write(uint8_t index, uint16_t data) {
        uint8_t hi, lo;
        command();
        ::write(0);
        ::write(index);
        hi = data >> 8;
        lo = data & 0x0FF;
        ::data();
        ::write(hi);
        ::write(lo);
    }

    static void writeDouble(uint8_t index, uint16_t data) {
        uint8_t hi, lo;
        command();
        ::write(index);
        hi = data >> 8;
        lo = data & 0x0FF;
        ::data();
        ::write(hi);
        ::write(lo);
    }

    static void write(uint8_t index, uint8_t data) {
        command();
        ::write(index);
        ::data();
        ::write(data);
    }

    // Set value of 2 TFT registers: Two 8-bit addresses (hi & lo), 16-bit value
    static void writePair(uint8_t aH, uint8_t aL, uint16_t d) {
        uint8_t hi = d >> 8;
        uint8_t lo = d & 0xFF;
        command();
        ::write(aH);
        data();
        ::write(hi);
        command();
        ::write(aL);
        data();
        ::write(lo);
    }
};

template<uint8_t I>
class Register: public RegisterBaseSPFD5408 {
public:
    static void write(uint16_t data) {
        RegisterBaseSPFD5408::write(index, data);
    }
private:
    static constexpr uint8_t index = I;
};

template<uint8_t I>
class Register8Bit: public RegisterBaseSPFD5408 {
public:
    static void write(uint8_t data) {
        RegisterBaseSPFD5408::write(index, data);
    }
private:
    static constexpr uint8_t index = I;
};

template<uint8_t I>
class Register32Bit: public RegisterBaseSPFD5408 {
public:
    static void write(uint32_t data) {
        RegisterBaseSPFD5408::write(index, data);
    }
private:
    static constexpr uint8_t index = I;
};

template<uint8_t I>
class Register8BitDouble: public RegisterBaseSPFD5408 {
public:
    static void write(uint16_t data) {
        RegisterBaseSPFD5408::writeDouble(index, data);
    }
private:
    static constexpr uint8_t index = I;
};

template<uint8_t A, uint8_t B>
class RegisterPair: public RegisterBaseSPFD5408 {
public:
    static void write(uint16_t data) {
        RegisterBaseSPFD5408::writePair(a, b, data);
    }
private:
    static constexpr uint8_t a = A;
    static constexpr uint8_t b = B;
};

using SPFD5408_DriverOuput=Register<0x01>;
using SPFD5408_LCDACDriverControoler=Register<0x02>;
using SPFD5408_EntryMode=Register<0x03>;
using SPFD5408_ResizingControl=Register<0x04>;
using SPFD5408_DisplayControl1=Register<0x07>;
using SPFD5408_DisplayControl2=Register<0x08>;
using SPFD5408_DisplayControl3=Register<0x09>;
using SPFD5408_DisplayControl4=Register<0x0A>;
using SPFD5408_ExternalInterfaceControl1=Register<0x0C>;
using SPFD5408_FrameMarkerPosition=Register<0x0D>;
using SPFD5408_ExternalInterfaceControl2=Register<0x0F>;
using SPFD5408_PowerControl1=Register<0x10>;
using SPFD5408_PowerControl2=Register<0x11>;
using SPFD5408_PowerControl3=Register<0x12>;
using SPFD5408_PowerControl4=Register<0x13>;
using SPFD5408_PowerControl5=Register<0x14>;
using SPFD5408_GRamSetHorzAddress=Register<0x20>;
using SPFD5408_GRamSetVertAddress=Register<0x21>;
using SPFD5408_GRamData=Register<0x22>;
using SPFD5408_NVMReadData1=Register<0x28>;
using SPFD5408_NVMReadData2=Register<0x29>;
using SPFD5408_NVMReadData3=Register<0x2A>;
using SPFD5408_GammaControl1=Register<0x30>;
using SPFD5408_GammaControl2=Register<0x31>;
using SPFD5408_GammaControl3=Register<0x32>;
using SPFD5408_GammaControl4=Register<0x33>;
using SPFD5408_GammaControl5=Register<0x34>;
using SPFD5408_GammaControl6=Register<0x35>;
using SPFD5408_GammaControl7=Register<0x36>;
using SPFD5408_GammaControl8=Register<0x37>;
using SPFD5408_GammaControl9=Register<0x38>;
using SPFD5408_GammaControl10=Register<0x39>;
using SPFD5408_GammaControl11=Register<0x3A>;
using SPFD5408_GammaControl12=Register<0x3B>;
using SPFD5408_GammaControl13=Register<0x3C>;
using SPFD5408_GammaControl14=Register<0x3D>;
using SPFD5408_WindoHStartAddress=Register<0x50>;
using SPFD5408_WindoHEndAddress=Register<0x51>;
using SPFD5408_WindoVStartAddress=Register<0x52>;
using SPFD5408_WindoVEndAddress=Register<0x53>;
using SPFD5408_DriverOutputControl=Register<0x60>;
using SPFD5408_ImageDisplayControl=Register<0x61>;
using SPFD5408_VerticalScrollingControl=Register<0x6A>;
using SPFD5408_DisplayPosition1=Register<0x80>;
using SPFD5408_GRamStartLineAddress1=Register<0x81>;
using SPFD5408_GRamEndLineAddress1=Register<0x82>;
using SPFD5408_DisplayPosition2=Register<0x83>;
using SPFD5408_GRamStartLineAddress2=Register<0x84>;
using SPFD5408_GRamEndLineAddress2=Register<0x85>;
using SPFD5408_PanelInterfaceControl1=Register<0x90>;
using SPFD5408_PanelInterfaceControl2=Register<0x92>;
using SPFD5408_PanelInterfaceControl3=Register<0x93>;
using SPFD5408_PanelInterfaceControl4=Register<0x94>;
using SPFD5408_PanelInterfaceControl5=Register<0x95>;
using SPFD5408_PanelInterfaceControl6=Register<0x97>;
using SPFD5408_NVMControl1=Register<0xA0>;
using SPFD5408_NVMControl2=Register<0xA1>;
using SPFD5408_CalibrationControl=Register<0xA4>;


using ILI9341_SOFTRESET=Register<0x01>;
using ILI9341_SLEEPIN=Register<0x10>;
using ILI9341_SLEEPOUT=Register<0x11>;
using ILI9341_NORMALDISP=Register<0x13>;
using ILI9341_INVERTOFF=Register<0x20>;
using ILI9341_INVERTON=Register<0x21>;
using ILI9341_GAMMASET=Register<0x26>;
using ILI9341_DISPLAYOFF=Register<0x28>;
using ILI9341_DISPLAYON=Register<0x29>;
using ILI9341_COLADDRSET=Register32Bit<0x2A>;
using ILI9341_PAGEADDRSET=Register32Bit<0x2B>;
using ILI9341_MEMORYWRITE=Register<0x2C>;
using ILI9341_PIXELFORMAT=Register<0x3A>;
using ILI9341_FRAMECONTROL=Register<0xB1>;
using ILI9341_DISPLAYFUNC=Register<0xB6>;
using ILI9341_ENTRYMODE=Register<0xB7>;
using ILI9341_POWERCONTROL1=Register<0xC0>;
using ILI9341_POWERCONTROL2=Register<0xC1>;
using ILI9341_VCOMCONTROL1=Register<0xC5>;
using ILI9341_VCOMCONTROL2=Register<0xC7>;
using ILI9341_MEMCONTROL=Register<0x36>;
using ILI9341_MADCTL=Register<0x36>;

using HX8347G_MEMACCESS=Register8Bit<0x16>;
using HX8347G_COLADDRSTART = RegisterPair<0x02, 0x03>;
using HX8347G_COLADDRSTEND = RegisterPair<0x04, 0x05>;
using HX8347G_ROWADDRSTART = RegisterPair<0x06, 0x07>;
using HX8347G_ROWADDREND = RegisterPair<0x08, 0x09>;
using HX8347G_COLOR = Register8BitDouble<0x22>;

using SDFP5408_COLOR = Register8BitDouble<0x2C>;

#endif /* REGISTER_H_ */
