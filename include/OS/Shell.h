
#pragma once
#ifndef MAPLEOS_SHELL_H
#define MAPLEOS_SHELL_H
#include <string>
#include "Utilities/MemoryUtils.h"
class Interpreter;

class  TokenList;
class Shell
{
    char* buffer;
    Interpreter* interpreter;
    size_t bufferSize;
public:
    Shell(size_t bufferSize);
    int id;
    void GetInput();
    size_t ReadLine(size_t size);
    void PrintBuffer(const char* buffer);
    void DumpPages(int count = 0, bool printEmpty = false);
    void ProcessInput(char delimiter);


    ~Shell();

private:
    class Memory* memory;
    TokenList* currentTokens;
    TokenList* TokenizeInput(char delimiter);

    void PeekMemory();

};



#endif //MAPLEOS_SHELL_H
