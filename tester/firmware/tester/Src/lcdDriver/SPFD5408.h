/*
 * SPFD5408.h
 *
 *  Created on: 16 gen 2017
 *      Author: paolo
 */

#ifndef SPFD5408_H_
#define SPFD5408_H_

#include "Pins.h"
#include "BaseAcccess.h"
#include "GFX.h"

class SPFD5408 {
public:
    SPFD5408();
    static LcdID readID(void);
    void begin(LcdID id);
    void reset();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void setAddrWindow(int x1, int y1, int x2, int y2);
    void flood(uint16_t color, uint32_t len);
private:


private:
    LcdID driver;
    int16_t _width;
    int16_t _height; // Display w/h as modified by current rotation
    int16_t cursor_x;
    int16_t cursor_y;
    uint16_t textcolor;
    uint16_t textbgcolor;
    uint8_t textsize;
    uint8_t rotation;
    bool wrap;   // If set, 'wrap' text at right edge of display
    bool _cp437; // If set, use correct CP437 charset (default is off)
};

#endif /* SPFD5408_H_ */
