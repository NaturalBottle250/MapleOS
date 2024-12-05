//
// Created by danie on 2024-12-05.
//

#include "Memory.h"

#ifndef MAPLEOS_MEMORYUTILS_H
#define MAPLEOS_MEMORYUTILS_H

inline void* malloc(size_t size)
{
    return Memory::GetInstance()->malloc(size);
}

inline void free(void* pointer)
{
    return Memory::GetInstance()->free(pointer);
}
#endif //MAPLEOS_MEMORYUTILS_H
