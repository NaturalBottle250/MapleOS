//
// Created by danie on 2024-12-05.
//

#include "Memory.h"
#include <sal.h>
#pragma once
#ifndef MAPLEOS_MEMORYUTILS_H
#define MAPLEOS_MEMORYUTILS_H

_Ret_maybenull_
_Post_writable_byte_size_(size)
_Function_class_(ALLOC)
inline void* mmalloc(size_t size)
{
    //std::cout << "malloc called with size: " << size << "\n";

    return Memory::GetInstance()->malloc(size);
}

_Function_class_(FREE)
inline void mfree(void* pointer)
{
    return Memory::GetInstance()->free(pointer);
}
#endif //MAPLEOS_MEMORYUTILS_H
