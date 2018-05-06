/*
 * GFX.h
 *
 *  Created on: 23 gen 2017
 *      Author: paolo
 */

#ifndef GFX_H_
#define GFX_H_

#include <memory>
#include <stdint.h>
#include "BaseAcccess.h"

enum class LcdID {
    ID_932X, ID_7575, ID_9341, ID_9342, ID_HX8357D, ID_SPFD5408, ID_S6D0129, ID_HX8367, ID_UNKNOWN
};


enum class DriverQuality {
    OFF, SMALL, MEDIUM_LOW, MEDIUM, MEDIUM_HIGH, HIGHT
};

struct Font {
    uint8_t xSize;
    uint8_t ySize;
    uint8_t offset;
    uint16_t numchars;
    bool row;
    const uint8_t * data;
};

extern const Font bigFont;

class Color6Bit {
private:
    uint8_t components[3];
public:
    constexpr Color6Bit(uint8_t red, uint8_t blue, uint8_t green) :
            components { red, blue, green } {
    }

    bool operator==(Color6Bit & a) {
        return components[0] == a.components[0] && components[1] == a.components[1] && components[2] == a.components[2];
    }

    bool operator!=(Color6Bit & a) {
        return components[0] != a.components[0] || components[1] != a.components[1] || components[2] != a.components[2];
    }

    uint8_t getRed() {
        return components[0];
    }
    uint8_t getGreen() {
        return components[1];
    }
    uint8_t getBlue() {
        return components[2];
    }
    void setRGB(uint8_t r, uint8_t g, uint8_t b) {
        components[0] = r << 2;
        components[1] = g << 2;
        components[2] = b << 2;
    }
};

constexpr Color6Bit WHITE(255,255,255);
constexpr Color6Bit BLACK(0,0,0);
constexpr Color6Bit DARKGRAY(0x40,0x40,0x40);
constexpr Color6Bit GRAY(0x80,0x80,0x80);
constexpr Color6Bit LIGHTGRAY(0xC0,0xC0,0xC0);

class Point {

public:
    Point( Point && point): x(point.x), y(point.y){}

    Point( Point & point): x(point.x), y(point.y){}

    Point & operator=(const Point & a){
        x = a.x;
        y = a.y;
        return *this;
    }


    constexpr Point(int x, int y) :
            x(x), y(y) {
    }
    constexpr Point() :
            x(0xFFFF), y(0xFFFF) {
    }

    int16_t x;
    int16_t y;
};

class GFX {
public:
    GFX();
    virtual ~GFX() = default;

    void drawPixel(Point && point, Color6Bit color) {
        if ((point.x < 0) || (point.y < 0) || (point.x >= width) || (point.y >= height))
            return;
        activeCS();
        drawPixelInternal(std::move(point), std::move(color));
        idleCS();
    }
    virtual void drawPixelInternal(Point && point, Color6Bit && color)=0;
    virtual void setAddrWindow(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) =0;
    virtual void flood(Color6Bit color, uint32_t len)=0;

    void drawFastHLine(Point p, uint16_t length, Color6Bit color);
    void drawFastVLine(Point point, uint16_t length, Color6Bit color);
    void drawLine(Point start, Point end, Color6Bit color);
    void drawCircle(Point center, int16_t r, Color6Bit color);
    void drawCircleHelper(Point center, int16_t r, uint8_t cornername, Color6Bit color);
    void fillCircle(Point center, int16_t r, Color6Bit color);
    void drawRect(Point leftTop, int16_t w, int16_t h, Color6Bit color);
    void fillRect(Point && leftTop, int16_t w, int16_t h, Color6Bit color);
    void drawRoundRect(Point leftTop, int16_t w, int16_t h, int16_t r, Color6Bit color);
    void fillRoundRect(Point leftTop, int16_t w, int16_t h, int16_t r, Color6Bit color);
    void drawChar(Point p, unsigned char c, uint8_t size);
    void drawChar(Point p, unsigned char c);
    void drawString(Point && p, const char * s);
    void setFont(const Font * font) {
        this->font = font;
    }
    void setForeground(Color6Bit color) {
        foreground = color;
    }
    void setBackground(Color6Bit color) {
        background = color;
    }

    uint16_t width;
    uint16_t height;
private:
    void fillCircleHelper(Point c, int16_t r, uint8_t cornername, int16_t delta, Color6Bit color);
    void putCharPixel(Point p, uint8_t bits, uint8_t size);
protected:
    LcdID driver;

    const Font * font;
    Color6Bit foreground;
    Color6Bit background;
};

#endif /* GFX_H_ */
