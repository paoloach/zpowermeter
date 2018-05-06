//
// Created by paolo on 31/12/17.
//

#ifndef TESTER_MAINLOOP_H
#define TESTER_MAINLOOP_H

#ifdef __cplusplus

#include "lcdDriver/GFX.h"
#include "CS5463.h"

extern "C" void handleMainLoop(void);
extern "C" void mainLoopInit(void);

class MainLoop {
public:
    void init();
    void mainLoop();

private:
    GFX * graphics;

    void initCS() const;

    int32_t getInt(uint32_t regPower) const;
};

#else

void handleMainLoop(void);
void mainLoopInit(void);

#endif


#endif //TESTER_MAINLOOP_H
