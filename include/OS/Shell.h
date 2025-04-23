
#pragma once
#ifndef MAPLEOS_SHELL_H
#define MAPLEOS_SHELL_H
#include <string>
#include "Utilities/MemoryUtils.h"
class Interpreter;

class  TokenList;
class Shell
{

    Interpreter* interpreter;
public:
    Shell();
    int id;
    char* GetInput();
    size_t ReadLine(char* buffer, size_t size);
    const void PrintBuffer(const char* buffer);
    void DumpPages(int count = 0, bool printEmpty = false);
    void ProcessInput(char* buffer, char delimiter);


    ~Shell();

private:
    class Memory* memory;
    TokenList* currentTokens;
    TokenList* TokenizeInput(char* buffer, char delimiter);

    void PeekMemory();

};



#endif //MAPLEOS_SHELL_H
