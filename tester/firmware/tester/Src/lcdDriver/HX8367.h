/*
 * HX8367.h
 *
 *  Created on: 12 mar 2017
 *      Author: paolo
 */

#ifndef HX8367_H_
#define HX8367_H_

#include <functional>
#include <tuple>
#include "GFX.h"

namespace HX8367 {

class HX8367: public GFX  {
public:
    HX8367();
    static bool checkPresence();
    void static reset();
protected:
    void drawPixelInternal(Point && point, Color6Bit && color) override;
    void setAddrWindow(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override;
    void flood(Color6Bit color, uint32_t len) override;
private:
    static constexpr uint32_t DEFAULT_WIDTH = 240;
    static constexpr uint32_t DEFAULT_HEIGTH = 320;
};


}

#endif /* HX8367_H_ */
