//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-25.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef CPU_H
#define CPU_H
#include <cstdint>


class Memory;

class CPU
{
public:

    CPU();
    void Step();

private:

    uint16_t programCounter;

    short registerCount = 8;
    uint8_t registers[8];

    //True if last computation gave a 0
    bool zeroFlag;
    //True if last computation yielded a carry
    bool carryFlag;

    Memory* memory;

    uint8_t Fetch();
};



#endif //CPU_H
