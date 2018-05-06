/*
 * RegisterHX8367.h
 *
 *  Created on: 12 mar 2017
 *      Author: paolo
 */

#ifndef REGISTERHX8367_H_
#define REGISTERHX8367_H_

#include "BaseAcccess.h"
#include <array>
#include <vector>

namespace HX8367 {
enum class REG {
    ReadID = 0,
    DisplayMode = 0x01,
    ColAddrStartH = 0x02,
    ColAddrStartL = 0x03,
    ColAddrEndH = 0x04,
    ColAddrEndL = 0x05,
    RowAddrStartH = 0x06,
    RowAddrStartL = 0x07,
    RowAddrEndH = 0x08,
    RowAddrEndL = 0x09,
    PartAreaStartRowH = 0x0A,
    PartAreaStartRowL = 0x0B,
    PartAreadEndRowH = 0x0C,
    PartAreadEdRowL = 0x0D,
    VertScrollTopFixedAreaH = 0x0E,
    VertScrollTopFixedAreaL = 0x0F,
    VertScrollHeightAreaH = 0x10,
    VertScrollHeightAreaL = 0x11,
    VertScrollButtonAreaH = 0x12,
    VertScrollButtonAreaL = 0x13,
    VertScrollStartAddressH = 0x14,
    VertScrollStartAddressL = 0x15,
    MemoryAccessCtrl = 0x16,
    COLMOD = 0x17,
    OSCCtrl1 = 0x18,
    OSCCtrl2 = 0x19,
    PowerCtrl1 = 0x1A,
    PowerCtrl2 = 0x1B,
    PowerCtrl3 = 0x1C,
    PowerCtrl4 = 0x1D,
    PowerCtrl5 = 0x1E,
    PowerCtrl6 = 0x1F,
    PowerCtrl7 = 0x20,
    SRamWrite = 0x22,
    VCOMCtrl1 = 0x23,
    VCOMCtrl2 = 0x24,
    VCOMCtrl3 = 0x25,
    DisplayCtrll = 0x26,
    DisplayCtrl2 = 0x27,
    DisplayCtrl3 = 0x28,
    FrameRateCtrll = 0x29,
    FrameRateCtrl2 = 0x2A,
    FrameRateCtrl3 = 0x2B,
    FrameRateCtrl4 = 0x2C,
    CycleCtrl1 = 0x2D,
    CycleCtrl2 = 0x2E,
    DisplayInversion = 0x2F,
    RGBInterfaceCtrl1 = 0x31,
    RGBInterfaceCtrl2 = 0x32,
    RGBInterfaceCtrl3 = 0x33,
    RGBInterfaceCtrl4 = 0x34,
    PanelCharacteristic = 0x36,
    OPTCtrl1 = 0x38,
    OPTCtrl2 = 0x39,
    OPTCtrl3 = 0x3A,
    OPTCtrl4 = 0x3B,
    R1Ctrl_1 = 0x40,
    R1Ctrl_2 = 0x41,
    R1Ctrl_3 = 0x42,
    R1Ctrl_4 = 0x43,
    R1Ctrl_5 = 0x44,
    R1Ctrl_6 = 0x45,
    R1Ctrl_7 = 0x46,
    R1Ctrl_8 = 0x47,
    R1Ctrl_9 = 0x48,
    R1Ctrl_10 = 0x49,
    R1Ctrl_11 = 0x4A,
    R1Ctrl_12 = 0x4B,
    R1Ctrl_13 = 0x4C,
    R1Ctrl_18 = 0x50,
    R1Ctrl_19 = 0x51,
    R1Ctrl_20 = 0x52,
    R1Ctrl_21 = 0x53,
    R1Ctrl_22 = 0x54,
    R1Ctrl_23 = 0x55,
    R1Ctrl_24 = 0x56,
    R1Ctrl_25 = 0x57,
    R1Ctrl_26 = 0x58,
    R1Ctrl_27 = 0x59,
    R1Ctrl_28 = 0x5A,
    R1Ctrl_29 = 0x5B,
    R1Ctrl_30 = 0x5C,
    R1Ctrl_35 = 0x5D,
    TECtrl = 0x60,
    ID1 = 0x61,
    ID2 = 0x62,
    ID3 = 0x63,
    TEOutputLine2 = 0x84,
    TEOutputLine1 = 0x85,
    OPTCtrl5 = 0x87,
    OPONCtrl1 = 0xE8,
    OPONCtrl2 = 0xE9,
    PTBACtrl = 0xEA,
    PTBACtr2 = 0xEB,
    STBACtrll = 0xEC,
    STBACtrl2 = 0xED,
    OTPS1B = 0xF1,
    GENON = 0xF2,
    PageSel = 0xFF
};

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

    static uint8_t readData() {
        RS_PORT->BRR=RS_PIN;
        dataPortToRead();
        RD_PORT->BRR = RD_PIN;
        RS_PORT->BSRR = RS_PIN;
        // Wait for about 80ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );

        uint8_t data = ::readData();
        dataPortToWrite();
        RD_PORT->BSRR = RD_PIN;
        return data;
    }

};

template<REG r>
class Register: public RegisterBase {
public:
    static void write(uint8_t data) {
        RegisterBase::writeIndex(static_cast<uint8_t>(index));
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        RegisterBase::writeDataByte(data);
    }

    static uint8_t read() {
        RegisterBase::writeIndex(static_cast<uint8_t>(index));
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );

        return RegisterBase::readData();
    }
private:
    const static REG index = r;
};

class SRamWrite: public RegisterBase {
public:
    static void write(Color6Bit color) {
        command();
        writeIndex(static_cast<uint8_t>(REG::SRamWrite));
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
        // wait 50ns
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
    }
    static void write(Color6Bit color, uint32_t len) {
        command();
        writeIndex(static_cast<uint8_t>(REG::SRamWrite));
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        data();
        for (; len > 0; len--) {
            activeWR();
            setData(color.getRed());
            idleWR();
            // wait 42ns
            __asm(
                    "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            activeWR();
            setData(color.getBlue()); // Use more that 50ns
            idleWR();
            // wait 42ns
            __asm(
                    "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
            activeWR();
            setData(color.getGreen()); // Use more that 50ns
            idleWR();
            // wait 42ns
            __asm(
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }
    }
};

using ID = Register<REG::ReadID>;

using ColAddrStartH =Register<REG::ColAddrStartH>;
using ColAddrStartL =Register<REG::ColAddrStartL>;
using ColAddrEndH =Register<REG::ColAddrEndH>;
using ColAddrEndL =Register<REG::ColAddrEndL>;
using RowAddrStartH =Register<REG::RowAddrStartH>;
using RowAddrStartL =Register<REG::RowAddrStartL>;
using RowAddrEndH =Register<REG::RowAddrEndH>;
using RowAddrEndL =Register<REG::RowAddrEndL>;

using DisplayMode =Register<REG::DisplayMode>;
using MemoryAccessCtrl =Register<REG::MemoryAccessCtrl>;
using COLMOD =Register<REG::COLMOD>;
using OSCCtrl1 =Register<REG::OSCCtrl1>;
using OSCCtrl2 =Register<REG::OSCCtrl2>;

using PowerCtrl1 =Register<REG::PowerCtrl1>;
using PowerCtrl2 =Register<REG::PowerCtrl2>;
using PowerCtrl3 =Register<REG::PowerCtrl3>;
using PowerCtrl4 =Register<REG::PowerCtrl4>;
using PowerCtrl5 =Register<REG::PowerCtrl5>;
using PowerCtrl6 =Register<REG::PowerCtrl6>;
using PowerCtrl7 =Register<REG::PowerCtrl7>;

using DisplayCtrll =Register<REG::DisplayCtrll>;
using DisplayCtrl2 =Register<REG::DisplayCtrl2>;
using DisplayCtrl3 =Register<REG::DisplayCtrl3>;

using VCOMCtrl1 =Register<REG::VCOMCtrl1>;
using VCOMCtrl2 =Register<REG::VCOMCtrl2>;
using VCOMCtrl3 =Register<REG::VCOMCtrl3>;

using PanelCharacteristic =Register<REG::PanelCharacteristic>;

using PTBACtrl1 =Register<REG::PTBACtrl>;
using PTBACtrl2 =Register<REG::PTBACtr2>;
using STBACtrl1 =Register<REG::STBACtrll>;
using STBACtrl2 =Register<REG::STBACtrl2>;
using OPONCtrl1 =Register<REG::OPONCtrl1>;
using OPONCtrl2 =Register<REG::OPONCtrl2>;
using OTPS1B = Register<REG::OTPS1B>;
using GENON = Register<REG::GENON>;

}

#endif /* REGISTERHX8367_H_ */
