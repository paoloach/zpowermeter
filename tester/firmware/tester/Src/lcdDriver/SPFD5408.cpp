/*
 * SPFD5408.cpp
 *
 *  Created on: 16 gen 2017
 *      Author: paolo
 */

#include "SPFD5408.h"
#include "Register.h"

#define TFTWIDTH   240
#define TFTHEIGHT  320

SPFD5408::SPFD5408() {
    rotation = 0;
    cursor_y = cursor_x = 0;
    textsize = 1;
    textcolor = 0xFFFF;
    _width = TFTWIDTH;
    _height = TFTHEIGHT;
}

LcdID SPFD5408::readID(void) {
    RS_PORT->BRR=RS_PIN;
    dataPortToRead();
    CS_PORT->BRR = CS_PIN;
    RS_PORT->BRR = RS_PIN;
    RD_PORT->BRR = RD_PIN;
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
       );
    uint8_t hi = ::readData();
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

                  "nop\n" // 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
                  "nop\n"// 14 ns at 70 Mhz
            );

    RD_PORT->BRR = RD_PIN;
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
          );
    uint8_t low = ::readData();

    RD_PORT->BSRR = RD_PIN;
    dataPortToWrite();
    uint16_t code = ((uint16_t) hi << 8) + low;
    if (code == 0x5408)
        return LcdID::ID_SPFD5408;
    else
        return LcdID::ID_UNKNOWN;
}

void SPFD5408::reset(void) {

    idleCS();
    idleWR();
    idleRD();

}

void SPFD5408::begin(LcdID id) {
    if (id == LcdID::ID_SPFD5408) {
        reset();

        driver = id;
        activeCS();

        SPFD5408_DriverOuput::write(0);
        SPFD5408_NVMReadData1::write(0);
        SPFD5408_PowerControl2::write(0);
        SPFD5408_NVMReadData2::write(0);

        // *** SPFD5408 change -- Begin
        // Not tested yet
        //writeRegister8(ILI9341_INVERTOFF, 0);
        //delay(500);
        // *** SPFD5408 change -- End
        setAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
    }
}



void SPFD5408::drawPixel(int16_t x, int16_t y, uint16_t color) {

// Clip
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
        return;

    activeCS();
    setAddrWindow(x, y, _width - 1, _height - 1);
    activeCS();

    SDFP5408_COLOR::write(color);

    idleCS();
}

// Sets the LCD address window (and address counter, on 932X).
// Relevant to rect/screen fills and H/V lines.  Input coordinates are
// assumed pre-sorted (e.g. x2 >= x1).
void SPFD5408::setAddrWindow(int x1, int y1, int x2, int y2) {
    activeCS();
    SPFD5408_WindoHStartAddress::write(x1);
    SPFD5408_WindoHEndAddress::write(x2);
    SPFD5408_WindoVEndAddress::write(y1);
    SPFD5408_WindoVEndAddress::write(y2);
    idleCS();
}

void SPFD5408::flood(uint16_t , uint32_t ) {
//  uint16_t blocks;
//  uint8_t  i, hi = color >> 8,
//              lo = color;
//
//  activeCS();
//  command();
//  if (driver == ID_9341) {
//    write8(0x2C);
//  } else if (driver == ID_932X) {
//    write8(0x00); // High byte of GRAM register...
//    write8(0x22); // Write data to GRAM
//  } else if (driver == ID_HX8357D) {
//    write8(HX8357_RAMWR);
//  } else {
//    write8(0x22); // Write data to GRAM
//  }
//
//  // Write first pixel normally, decrement counter by 1
//  CD_DATA;
//  write8(hi);
//  write8(lo);
//  len--;
//
//  blocks = (uint16_t)(len / 64); // 64 pixels/block
//  if(hi == lo) {
//    // High and low bytes are identical.  Leave prior data
//    // on the port(s) and just toggle the write strobe.
//    while(blocks--) {
//      i = 16; // 64 pixels/block / 4 pixels/pass
//      do {
//        WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 2 bytes/pixel
//        WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // x 4 pixels
//      } while(--i);
//    }
//    // Fill any remaining pixels (1 to 64)
//    for(i = (uint8_t)len & 63; i--; ) {
//      WR_STROBE;
//      WR_STROBE;
//    }
//  } else {
//    while(blocks--) {
//      i = 16; // 64 pixels/block / 4 pixels/pass
//      do {
//        write8(hi); write8(lo); write8(hi); write8(lo);
//        write8(hi); write8(lo); write8(hi); write8(lo);
//      } while(--i);
//    }
//    for(i = (uint8_t)len & 63; i--; ) {
//      write8(hi);
//      write8(lo);
//    }
//  }
//  CS_IDLE;
}

