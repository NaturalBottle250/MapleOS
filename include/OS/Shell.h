
#pragma once
#ifndef MAPLEOS_SHELL_H
#define MAPLEOS_SHELL_H
#include <string>
class Shell
{

public:
    Shell();
    int id;
    const char* GetInput();
    size_t ReadLine(char* buffer, size_t size);
    const void PrintBuffer(const char* buffer);
    void DumpPages(int count = 0, bool printEmpty = false);


private:
    class Memory* memory;

    void PeekMemory();

};



#endif //MAPLEOS_SHELL_H
