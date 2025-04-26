//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-25.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#include "../include/Components/CPU.h"

#include "Components/Memory.h"

CPU::CPU()
{
    memory = Memory::GetInstance();

    programCounter = 0;

    for (int index = 0; index < registerCount; index++)
        registers[index] = 0;


    zeroFlag = false;
    carryFlag = false;
}

void CPU::Step()
{
}

uint8_t CPU::Fetch()
{
    //Read from Memory


    return 0;
}
