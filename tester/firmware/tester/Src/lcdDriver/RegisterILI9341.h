/*
 * RegisterILI9341.h
 *
 *  Created on: 20 gen 2017
 *      Author: paolo
 */

#ifndef REGISTERILI9341_H_
#define REGISTERILI9341_H_

#include "BaseAcccess.h"
#include "GFX.h"
#include <array>
#include <vector>

namespace ILI9341 {

    enum class REG {
        NOP = 0,
        Reset = 0x01,
        ReadDisplayIdentification = 0x04,
        ReadID = 0xD3,
        ReadStatus = 0x09,
        ReadDispPowerMode = 0x0A,
        ReadDispMADCTL = 0x0B,
        ReadDispPixelFormat = 0x0C,
        ReadDispImgFormat = 0x0D,
        ReadDispSignMode = 0x0E,
        ReadDispDiagnostic = 0x0F,
        SleepModeOn = 0x10,
        SleepModeOff = 0x11,
        PartialModeOn = 0x12,
        NormalDispOn = 0x13,
        DispInvertOff = 0x20,
        DispInvertOn = 0x21,
        GammaSet = 0x26,
        DisplayOff = 0x28,
        DisplayOn = 0x29,
        ColAddrSet = 0x2A,
        PageAddrSet = 0x2B,
        ColorSet = 0x2D,
        MemoryRead = 0x2E,
        PartialArea = 0x30,
        ViewScrollDef = 0x33,
        TearOff = 0x34,
        TearOn = 0x35,
        MemAccessCtrl = 0x36,
        VertScrollStartAddr = 0x37,
        IdleOff = 0x38,
        IdleOn = 0x39,
        PixelFormatSet = 0x3A,
        WriteMemCont = 0x3C,
        ReadMemCont = 0x3E,
        SetTearScanline = 0x44,
        GetScanLine = 0x45,
        WriteDisplBrightness = 0x51,
        ReadDisplBrightness = 0x52,
        WriteCtrlDispl = 0x53,
        ReadCtrlDispl = 0x54,
        WriteAdaptBrightness = 0x55,
        ReadAdaptBrightness = 0x56,
        WriteCABCMinBrightness = 0x5E,
        ReadCABCMinBrightness = 0x5F,
        FrameCtrl = 0xB1,
        DisplayFnCtl = 0xB6,
        EntryModeSet = 0xB7,
        ReadID1 = 0xDA,
        ReadID2 = 0xDB,
        ReadID3 = 0xDC,
        PowerCtrl1 = 0xC0,
        PowerCtrl2 = 0xC1,
        VCOMCtl1 = 0xC5,
        VCOMCtl2 = 0xC7,
    };

    constexpr uint8_t MADCTL_MY = 0x80;
    constexpr uint8_t MADCTL_MX = 0x40;
    constexpr uint8_t MADCTL_MV = 0x20;
    constexpr uint8_t MADCTL_ML = 0x10;
    constexpr uint8_t MADCTL_RGB = 0x00;
    constexpr uint8_t MADCTL_BGR = 0x08;
    constexpr uint8_t MADCTL_MH = 0x04;

    class RegisterBase {
    protected:
        static void writeIndex(uint8_t index) {
            RS_PORT->BRR = RS_PIN;
            WR_PORT->BRR = WR_PIN;
            setData(index);
            WR_PORT->BSRR = WR_PIN;
        }

        static void writeDataByte(uint8_t byte) {
            RS_PORT->BSRR = RS_PIN;
            WR_PORT->BRR = WR_PIN;
            setData(byte);
            WR_PORT->BSRR = WR_PIN;
        }

    };

    class RegisterRead : public RegisterBase {
    protected:
        static uint8_t readData() {
            RD_PORT->BRR = RD_PIN;
            uint8_t data = ::readData();
            RD_PORT->BSRR = RD_PIN;
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
            return data;
        }
    };

    template<REG r>
    class RegisterApply : public RegisterBase {
    public:
        static void apply() {
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterWrite8Bits : public RegisterBase {
    public:
        static void write(uint8_t byte) {
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
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
            writeDataByte(byte);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterWrite16Bits : public RegisterBase {
    public:
        static void write(uint16_t word) {
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(word);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte((word >> 8));
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterWrite24Bits : public RegisterBase {
    public:
        static void write(uint8_t byte1, uint8_t byte2, uint8_t byte3) {
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte1);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte2);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte3);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterWrite32Bits : public RegisterBase {
    public:
        static void write(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte1);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte2);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte3);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte4);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterWrite40Bits : public RegisterBase {
    public:
        static void write(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5) {
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte1);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte2);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte3);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte4);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(byte5);
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterRead1Byte : public RegisterRead {
    public:
        static uint8_t read() {
            uint8_t result;
            CS_PORT->BRR = CS_PIN;
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            RS_PORT->BRR=RS_PIN;
            dataPortToRead();
            RS_PORT->BSRR = RS_PIN;

            readData();
            result = readData();
            dataPortToWrite();
            return result;
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterRead3Bytes : public RegisterRead {
    public:
        static std::array<uint8_t, 3> read() {
            std::array<uint8_t, 3> result;
            CS_PORT->BRR = CS_PIN;
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            RS_PORT->BRR = RS_PIN;
            dataPortToRead();
            RS_PORT->BSRR = RS_PIN;

            readData();
            result[0] = readData();
            result[1] = readData();
            result[2] = readData();
            dataPortToWrite();
            return result;
        }

    private:
        const static REG index = r;
    };

    template<REG r>
    class RegisterRead4Bytes : public RegisterRead {
    public:
        static std::array<uint8_t, 4> read() {
            std::array<uint8_t, 4> result;
            CS_PORT->BRR = CS_PIN;
            RegisterBase::writeIndex(static_cast<uint8_t>(index));
            RS_PORT->BRR=RS_PIN;
            dataPortToRead();
            RS_PORT->BSRR = RS_PIN;

            readData();
            result[0] = readData();
            result[1] = readData();
            result[2] = readData();
            result[3] = readData();
            dataPortToWrite();
            return result;
        }

    private:
        const static REG index = r;
    };

    class MemoryWrite : public RegisterBase {
    public:
        static void write(Color6Bit &color) {

            RegisterBase::writeIndex(0x2C);
            RS_PORT->BSRR = RS_PIN;
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(color.getBlue());
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(color.getGreen());
            __asm(
            "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            writeDataByte(color.getRed());
        }

        static void write(Color6Bit color, uint32_t count) {

            RegisterBase::writeIndex(0x2C);
            RS_PORT->BSRR = RS_PIN;
            for (; count > 0; count--) {
                __asm(
                "nop\n" // 14 ns at 70 Mhz
                        "nop\n"// 14 ns at 70 Mhz
                        "nop\n"// 14 ns at 70 Mhz
                );
                writeDataByte(color.getBlue());
                __asm(
                "nop\n" // 14 ns at 70 Mhz
                        "nop\n"// 14 ns at 70 Mhz
                        "nop\n"// 14 ns at 70 Mhz
                );
                writeDataByte(color.getGreen());
                __asm(
                "nop\n" // 14 ns at 70 Mhz
                        "nop\n"// 14 ns at 70 Mhz
                        "nop\n"// 14 ns at 70 Mhz
                );
                writeDataByte(color.getRed());
            }
        }
    };

    class MemoryRead : public RegisterRead {
    public:
        static std::vector<Color6Bit> read(uint16_t count) {

            std::vector<Color6Bit> result;

            RegisterBase::writeIndex(0x2E);
            RS_PORT->BRR=RS_PIN;
            dataPortToRead();
            RS_PORT->BSRR = RS_PIN;
            readData();
            for (; count > 0; count--) {
                result.emplace_back(readData(), readData(), readData());
            }
            return result;
        }
    };

    using Reset= RegisterApply<REG::Reset>;
    using DisplayInvertOff= RegisterApply<REG::DispInvertOff>;
    using DisplayInvertOn= RegisterApply<REG::DispInvertOn>;

    using DisplayOff= RegisterApply<REG::DisplayOff>;
    using DisplayOn= RegisterApply<REG::DisplayOn>;

    using SleepOff= RegisterApply<REG::SleepModeOff>;

    using PowerCtl1= RegisterWrite8Bits<REG::PowerCtrl1>;
    using PowerCtl2= RegisterWrite8Bits<REG::PowerCtrl2>;
    using VCOMCtl1= RegisterWrite16Bits<REG::VCOMCtl1>;
    using VCOMCtl2= RegisterWrite8Bits<REG::VCOMCtl2>;
    using MemAccessCtrl= RegisterWrite8Bits<REG::MemAccessCtrl>;
    using PixelFormatSet= RegisterWrite8Bits<REG::PixelFormatSet>;
    using FrameCtrl= RegisterWrite16Bits<REG::FrameCtrl>;
    using EntryModeSet= RegisterWrite8Bits<REG::EntryModeSet>;
    using ColAddrSet= RegisterWrite32Bits<REG::ColAddrSet>;
    using PageAddrSet= RegisterWrite32Bits<REG::PageAddrSet>;
    using DisplayFnCtl= RegisterWrite24Bits<REG::DisplayFnCtl>;
    using WriteCtrlDispl= RegisterWrite8Bits<REG::WriteCtrlDispl>;

    using ReadId= RegisterRead3Bytes<REG::ReadID>;
    using ReadDisplayIdentification= RegisterRead3Bytes<REG::ReadDisplayIdentification>;
    using DisplayStatus= RegisterRead4Bytes<REG::ReadStatus>;
    using DisplayPowerMode= RegisterRead1Byte<REG::ReadDispPowerMode>;
    using SelfDiagnostic= RegisterRead1Byte<REG::ReadDispDiagnostic>;
    using ReadDisplayCtl= RegisterRead1Byte<REG::ReadCtrlDispl>;

} // end namespace ILI9341

#endif /* REGISTERILI9341_H_ */
