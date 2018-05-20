//
// Created by paolo on 06/05/18.
//

#ifndef TESTER_ADE7953_H
#define TESTER_ADE7953_H

#include <cstdint>

enum ADE_Register8Bit{
    Version=0x702
};

class ADE7953 {
public:
    void init();

    uint8_t read(ADE_Register8Bit reg);
    uint8_t  version;
};


#endif //TESTER_ADE7953_H
