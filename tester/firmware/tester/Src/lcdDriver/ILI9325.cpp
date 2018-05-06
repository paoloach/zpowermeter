/*
 * ILI9325.cpp
 *
 *  Created on: 23 gen 2017
 *      Author: paolo
 */

#include <stdlib.h>
#include "ILI9325.h"
#include "RegisterILI9325.h"

// @formatter:off

std::array<ILI9325::InitCmd, 43> ILI9325::ILI9320_init = {
        ILI9325::InitCmd { ILI9325_REG::ILI9325_StartOdc, 0x0000 },
        { ILI9325_REG::WAIT, 100 },
        { ILI9325_REG::ILI9325_DriverOutControl, 0x100},
        { ILI9325_REG::ILI9325_LCDDriverControl, 0x0700},
        { ILI9325_REG::ILI9325_EntryMode, (1 << 15) | (1 << 14) | (1 << 5) | (1 << 4) },
        { ILI9325_REG::ILI9325_ResizeCtrl, 0x0000 },
        { ILI9325_REG::ILI9325_DisplCtrl2, 0x0202 },
        { ILI9325_REG::ILI9325_DisplCtrl3, 0x0000 },
        { ILI9325_REG::ILI9325_DisplCtrl4, 0x0000 },
        { ILI9325_REG::ILI9325_RGBCtrll, (1 << 1)  | (1 << 0) },
        { ILI9325_REG::ILI9325_FrmMarkerPos, 0x0000 },
        { ILI9325_REG::ILI9325_RGBCtrl2, 0x0000 },
        { ILI9325_REG::WAIT, 50 },
        { ILI9325_REG::ILI9325_DisplCtrl1, (1 << 8) | (1 << 0) },
        { ILI9325_REG::WAIT, 50 },
        { ILI9325_REG::ILI9325_PowerCtrl1, (1 << 12) | (1 << 7) | (1 << 6) },
        { ILI9325_REG::ILI9325_PowerCtrl2, (1 << 2) | (1 << 1) | (1 << 0) }, {
                ILI9325_REG::ILI9325_PowerCtrl3, (1 << 8) | (1 << 4) }, { ILI9325_REG::ILI9320_PowerCtrl4, (1 << 11) | (1 << 9) | (1 << 8) }, { ILI9325_REG::ILI9325_PowerCtrl7, 0 },

        { ILI9325_REG::ILI9325_FrameCtrl, (1 << 15) | (1 << 5) | (0 << 4) }, { ILI9325_REG::WAIT, 50 }, { ILI9325_REG::ILI9325_HorStart, 0x0000 }, { ILI9325_REG::ILI9325_HorEnd, 0x00EF }, {
                ILI9325_REG::ILI9325_VertStart, 0x0000 }, { ILI9325_REG::ILI9325_VertEnd, 0x013F }, { ILI9325_REG::WAIT, 50 }, { ILI9325_REG::ILI9325_DriverOutputCtrl2, (0 << 15) | (1 << 13)
                | (1 << 10) | (1 << 9) | (1 << 8) },
        //{ ILI9325_REG::ILI9325_BaseDisplayCtrl, (1<<0) },
        { ILI9325_REG::ILI9325_BaseDisplayCtrl, (1 << 0) }, { ILI9325_REG::ILI9325_VertScrollCtrl, 0x0000 },

        { ILI9325_REG::ILI9320_PartImage1Display, 0X0000 }, { ILI9325_REG::ILI9320_PartImage1AresStart, 0X0000 }, { ILI9325_REG::ILI9320_PartImage1AreaEnd, 0X0000 }, {
        ILI9325_REG::ILI9320_PartImage2Display, 0X0000 },
        { ILI9325_REG::ILI9320_PartImage2AresStart, 0X0000 },
        { ILI9325_REG::ILI9320_PartImage2AreaEnd, 0X0000 },
        { ILI9325_REG::ILI9325_PanelIfCtrl1, 0X0010 },
        { ILI9325_REG::ILI9325_PanelIfCtrl2, 0X0000 },
        { ILI9325_REG::ILI9320_PanelIfCtrl3, 0x0003 },
        { ILI9325_REG::ILI9325_PanelIfCtrl4, 0x0110 },
        { ILI9325_REG::ILI9320_PanelIfCtrl5, 0X0000 },
        { ILI9325_REG::ILI9320_PanelIfCtrl6, 0X0000 },
        { ILI9325_REG::ILI9325_DisplCtrl1, 0x0173} };

std::array<ILI9325::InitCmd, 48> ILI9325::ILI9235_init = { ILI9325::InitCmd { ILI9325_REG::ILI9325_StartOdc, 0x001 }, { ILI9325_REG::WAIT, 50 }, { ILI9325_REG::ILI9325_DriverOutControl, 0x0100 }, {
        ILI9325_REG::ILI9325_LCDDriverControl, 0x0700 }, { ILI9325_REG::ILI9325_EntryMode, 0x1030 }, { ILI9325_REG::ILI9325_ResizeCtrl, 0x0000 }, { ILI9325_REG::ILI9325_DisplCtrl2, 0x0202 }, {
        ILI9325_REG::ILI9325_DisplCtrl3, 0x0000 }, { ILI9325_REG::ILI9325_DisplCtrl4, 0x0000 }, { ILI9325_REG::ILI9325_RGBCtrll, 0x0000 }, { ILI9325_REG::ILI9325_FrmMarkerPos, 0x0000 }, {
        ILI9325_REG::ILI9325_RGBCtrl2, 0x0000 }, { ILI9325_REG::ILI9325_PowerCtrl1, 0x0000 }, { ILI9325_REG::ILI9325_PowerCtrl2, 0x0007 }, { ILI9325_REG::ILI9325_PowerCtrl3, 0x0000 }, {
        ILI9325_REG::ILI9325_PowerCtrl4, 0x0000 }, { ILI9325_REG::WAIT, 200 }, { ILI9325_REG::ILI9325_PowerCtrl1, 0x1690 }, { ILI9325_REG::ILI9325_PowerCtrl2, 0x0227 }, { ILI9325_REG::WAIT, 50 }, {
        ILI9325_REG::ILI9325_PowerCtrl3, 0x001A }, { ILI9325_REG::WAIT, 50 }, { ILI9325_REG::ILI9325_PowerCtrl4, 0x1800 }, { ILI9325_REG::ILI9325_PowerCtrl7, 0x002A }, { ILI9325_REG::WAIT, 50 }, {
        ILI9325_REG::ILI9325_GammCtrl1, 0x0000 }, { ILI9325_REG::ILI9325_GammCtrl2, 0x0000 }, { ILI9325_REG::ILI9325_GammCtrl3, 0x0000 }, { ILI9325_REG::ILI9325_GammCtrl4, 0x0206 }, {
        ILI9325_REG::ILI9325_GammCtrl5, 0x0808 }, { ILI9325_REG::ILI9325_GammCtrl6, 0x0007 }, { ILI9325_REG::ILI9325_GammCtrl7, 0x0201 }, { ILI9325_REG::ILI9325_GammCtrl8, 0x0000 }, {
        ILI9325_REG::ILI9325_GammCtrl9, 0x0000 }, { ILI9325_REG::ILI9325_GammCtrl10, 0x0000 }, { ILI9325_REG::ILI9325_RamAddressHor, 0x0000 }, { ILI9325_REG::ILI9325_RamAddressVert, 0x0000 }, {
        ILI9325_REG::ILI9325_HorStart, 0x0000 }, { ILI9325_REG::ILI9325_HorEnd, 0x00EF }, { ILI9325_REG::ILI9325_VertStart, 0x0000 }, { ILI9325_REG::ILI9325_VertEnd, 0x013F }, {
        ILI9325_REG::ILI9325_DriverOutputCtrl2, 0xA700 }, { ILI9325_REG::ILI9325_BaseDisplayCtrl, 0x0003 }, { ILI9325_REG::ILI9325_VertScrollCtrl, 0x0000 },
        { ILI9325_REG::ILI9325_PanelIfCtrl1, 0X0010 }, { ILI9325_REG::ILI9325_PanelIfCtrl2, 0X0000 }, { ILI9325_REG::ILI9325_PanelIfCtrl4, 0X1100 }, { ILI9325_REG::ILI9325_DisplCtrl1, 0x0133 } };

std::array<ILI9325::InitCmd, 29> ILI9325::S6D0129_init = { ILI9325::InitCmd { ILI9325_REG::ILI9325_StartOdc, 0x001 }, { ILI9325_REG::WAIT, 50 }, { ILI9325_REG::S6D0129_PowerCtrl4, 0x040B }, {
        ILI9325_REG::ILI9325_PowerCtrl3, 0x0070 }, { ILI9325_REG::WAIT, 250 }, { ILI9325_REG::ILI9325_PowerCtrl2, 0x3704 }, { ILI9325_REG::ILI9325_PowerCtrl1, 0x1600 }, { ILI9325_REG::WAIT, 20 }, {
        ILI9325_REG::ILI9325_DriverOutControl, 0x0927 }, { ILI9325_REG::ILI9325_LCDDriverControl, 0x0700 }, { ILI9325_REG::ILI9325_EntryMode, 0x9030 }, { ILI9325_REG::ILI9325_DisplCtrl1, 0x0004 }, {
        ILI9325_REG::ILI9325_DisplCtrl2, 0x0505 }, { ILI9325_REG::ILI9325_DisplCtrl3, 0x0000 }, { ILI9325_REG::S6D0129_FrameCycleControl, 0x0000 }, { ILI9325_REG::ILI9325_RGBCtrll, 0x0003 }, {
        ILI9325_REG::S6D0129_GateScanPosizion, 0x0000 }, { ILI9325_REG::S6D0129_HorWindowAddress, 0xEF00 }, { ILI9325_REG::S6D0129_VertWindowAddressEnd, 0x013F }, {
        ILI9325_REG::S6D0129_VertWindowAddressStart, 0x0000 }, { ILI9325_REG::S6D0129_GammCtrl1, 0x0000 }, { ILI9325_REG::S6D0129_GammCtrl2, 0x0006 }, { ILI9325_REG::S6D0129_GammCtrl3, 0x0000 }, {
        ILI9325_REG::S6D0129_GammCtrl4, 0x0707 }, { ILI9325_REG::S6D0129_GammCtrl5, 0x0700 }, { ILI9325_REG::S6D0129_GammCtrl6, 0x0303 }, { ILI9325_REG::S6D0129_GammCtrl7, 0x0007 }, {
        ILI9325_REG::S6D0129_GammCtrl8, 0x1100 }, { ILI9325_REG::S6D0129_GammCtrl9, 0x1100 }

//        1. Start oscillation executed (OSC = 1)
//        2. Driver output control (NL5–0 = 100111, SS = 0, GS = 0, EPL=0, VSPL=0, HSPL=0, DP3. LCD driving AC control (FLD1-0 = 01, B/C = 0, EOR = 0)
//        4. Entry mode set (TRI = 0, DFM = 0, I/D1-0 = 11: Increment by 1, AM = 0: Horizontal mo5. Display control 1 (PT1-0 = 00, VLE2–1 = 00: No vertical scroll, SPT = 0, GON = 0, CL = = 0, D1–0 = 00: Display off)
//        6. Display control 2 (FP3-0 = 1000, BP3-0 = 1000)
//        7. Display control 3 (PTG1-0= 00, ISC3-0 = 0000)
//        8. Frame cycle control (NO1-0 = 00, SDT1-0 = 00, VCIR1-0 = 00: no charge sharing, DIVRTN3-0 = 0000: 16 clock cycle in 1H period)
//        9. External display interface (RIM1-0=00:18-bit RGB interface, DM1-0=00: operated bsystem interface)
//        10. Power control 1 (SAP2-0 = 000, BT2-0 = 000, DC2–0 = 011, SLP = 0, STB = 0: Stand11. Power control 2 (GVD5-0 = 000000, VC2-0 = 000)
//        12. Power control 3 (PON = 0, PON1 = 0, AON = 0)
//        13. Power control 4 (VCMR = 0, VCM5-0 = 000000, VML5-0 = 000000)
//        14. RAM address set (AD16–0 = 00000h)
//        15. Gamma control
//        (PKP02–00 = 000, PKP12–10 = 000, PKP22–20 = 000, PKP32–30 = 000,
//        PK42–40 = 000, PKP52–50 = 000, PRP02–00 = 000, PRP12–10 = 000)
//        (PKN02–00 = 000, PKN12–10 = 000, PKN22–20 = 000, PKN32–30 = 000,
//        PKN42–40 = 000, PKN52–50 = 000, PRN02–00 = 000, PRN12–10 = 000)
//        VRP14–00 = 00000, VRP03–00 = 0000, VRN14–00 = 00000, VRN03–00 = 0000)
//        16. Gate scanning starting position (SCN5-0 = 000000)
//        17. Vertical scroll (VL8–0 = 00000000)
//        18. 1st screen division (SE18-10 = 100111111, SS18-10 = 00000000)
//        19. 2nd screen division (SE28-20 = 100111111, SS27-20 = 00000000)
//        20. Horizontal RAM address position (HEA7-0 = 11101111, HSA7-0 = 00000000)
//        21. Vertical RAM address position (VEA8-0 = 100111111, VSA8-0 = 00000000)

        };

// @formatter:on

ILI9325::ILI9325(bool swapX) :
        swapX(swapX) {
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGTH;
    activeCS();
    resetOn();
    HAL_Delay(5);
    resetOff();
    HAL_Delay(200);

    uint16_t code = ILI9325_DriverCodeRead::get();
    dataPortToWrite();
    if (code == 0x0129) {
        driver = LcdID::ID_S6D0129;
        initS6D0129();
    }
    if (code == 0x9325) {
        driver = LcdID::ID_932X;
        initILI9325();
    }
    if (code == 0x9320) {
        driver = LcdID::ID_932X;
        initILI9320();
        swapX = true;
    }
    flood(Color6Bit(0, 0, 0), DEFAULT_HEIGTH * DEFAULT_WIDTH);
    setAddrWindow(0,0,width-1,height-1);
}

bool ILI9325::checkPresence() {

    activeCS();
    resetOn();
    HAL_Delay(5);
    resetOff();
    HAL_Delay(150);

    bool result = false;
    uint16_t code = ILI9325_DriverCodeRead::get();
    if (code == 0x0129)
        result = true;
    if (code == 0x9325)
        result = true;
    if (code == 0x9320)
        result = true;
    idleCS();
    return result;
}

void ILI9325::initILI9325() {
    for (auto cmd : ILI9235_init) {
        if (cmd.reg == ILI9325_REG::WAIT) {
            HAL_Delay(cmd.arg);
        } else {
            command();
            RegisterBaseILI9325::writeIndex(static_cast<uint16_t>(cmd.reg));
            data();
            RegisterBaseILI9325::writeData(cmd.arg);
        }
    }
}

void ILI9325::initILI9320() {
    for (auto cmd : ILI9320_init) {
        if (cmd.reg == ILI9325_REG::WAIT) {
            HAL_Delay(cmd.arg);
        } else {
            command();
            RegisterBaseILI9325::writeIndex(static_cast<uint16_t>(cmd.reg));
            data();
            RegisterBaseILI9325::writeData(cmd.arg);
        }
    }
}

void ILI9325::initS6D0129() {
    for (auto cmd : S6D0129_init) {
        if (cmd.reg == ILI9325_REG::WAIT) {
            HAL_Delay(cmd.arg);
        } else {
            command();
            RegisterBaseILI9325::writeIndex(static_cast<uint16_t>(cmd.reg));
            data();
            RegisterBaseILI9325::writeData(cmd.arg);
        }
    }
    ILI9325_DisplCtrl1::write(0x0017);
    ILI9325_RamAddressHor::write(0);
    ILI9325_RamAddressVert::write(0);
    flood(Color6Bit(0, 0, 0), DEFAULT_HEIGTH * DEFAULT_WIDTH);
//    ILI9325_DisplCtrl1::write(0x0017);
}



void ILI9325::setAddrWindow(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    if (driver == LcdID::ID_932X) {
        ILI9325_HorStart::write(left);
        ILI9325_HorEnd::write(right);
        ILI9325_VertStart::write(top);
        ILI9325_VertEnd::write(bottom);
    }
    if (driver == LcdID::ID_S6D0129) {
        auto t = (left & 0xFF) | ((right & 0xFF) << 8);
        S6D019_HorWindowAddress::write(t);
        S6D019_VertWindowAddressStart::write(top);
        S6D019_VertWindowAddressEnd::write(bottom);
    }
    ILI9325_RamAddressHor::write(left);
    ILI9325_RamAddressVert::write(top);
}

void ILI9325::reset() {
    idleCS();
    idleWR();
    idleRD();

    activeCS();
    command();
    __asm(
            "nop\n" // 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
    );
    RegisterBaseILI9325::writeIndex(0);
    for (uint8_t i = 0; i < 3; i++)
        RegisterBaseILI9325::writeStrobe(); // Three extra 0x00s
    idleCS();
}

void ILI9325::flood(Color6Bit color, uint32_t len) {
    ILI9325_RamRW::write(color, len);
}

void ILI9325::drawPixelInternal( Point && p, Color6Bit && color) {

    ILI9325_RamAddressHor::write(p.x);
    ILI9325_RamAddressVert::write(p.y);
    ILI9325_RamRW::write(color);
}

void ILI9325::setDriverQuality(DriverQuality driverQuality) {
    if (driver == LcdID::ID_932X) {
        if (driverQuality == DriverQuality::OFF) {
            ILI9325_PowerCtrl1::setDriverQuality(driverQuality, 0x1600);
        } else {
            ILI9325_PowerCtrl1::setDriverQuality(DriverQuality::MEDIUM, 0x1600);
        }
    } else {
        ILI9325_PowerCtrl1::setDriverQuality(driverQuality, 0x1600);
    }
}

