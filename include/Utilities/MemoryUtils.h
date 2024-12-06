//
// Created by danie on 2024-12-05.
//

#include "Memory.h"
#pragma once
#ifndef MAPLEOS_MEMORYUTILS_H
#define MAPLEOS_MEMORYUTILS_H

inline void* mmalloc(size_t size)
{
    //std::cout << "malloc called with size: " << size << "\n";

    return Memory::GetInstance()->malloc(size);
}

inline void mfree(void* pointer)
{
    return Memory::GetInstance()->free(pointer);
}
#endif //MAPLEOS_MEMORYUTILS_H
