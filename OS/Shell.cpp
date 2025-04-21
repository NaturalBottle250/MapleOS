#include <iostream>
#include <cstring>
#include "OS/Shell.h"
#include "Memory.h"
#include <cstddef>
#include "../include/Utilities/SystemColors.h"
#include "OS/Interpreter.h"
#include "Utilities/MemoryUtils.h"
#include "Utilities/SystemUtils.h"
using namespace std;


Shell::Shell()
{
    this->memory = Memory::GetInstance();
}

const char* Shell::GetInput()
{
    cout << "$>";

    char* buffer = static_cast<char*>(mmalloc(101));
    memset(buffer, '\0', 101);

    //cin.getline(buffer, 101);
    ReadLine(buffer, 101);

    //cout << buffer << endl;


    //cout << GetNextToken(buffer,' ') << " " << GetNextToken(nullptr,' ');
    // const char* token = GetNextToken(buffer, ' ');
    // while (token != nullptr)
    // {
    //     cout << token << " ";
    //     token = GetNextToken(nullptr, ' ');
    // }
    // cout << endl;

    PrintBuffer(buffer);
    mfree(buffer);

    return buffer;
}

size_t Shell::ReadLine(char* buffer, size_t size)
{
    size_t index = 0;
    int  currentCharacter = 0;
    while (index + 1 < size &&
        (currentCharacter = std::cin.get()) != EOF &&
        currentCharacter != '\n')
    {
        buffer[index] = static_cast<char>(currentCharacter);
        index++;
    }
    buffer[index] = '\0';

    if (currentCharacter != '\n' && currentCharacter != EOF)
    {
        int c;
        while ((c = std::cin.get()) != EOF && c != '\n');
    }
    return index;
}


void Shell::DumpPages(int count, bool printEmpty)
{
    memory->DumpPages(count, printEmpty);
}


const void Shell::PrintBuffer(const char* buffer)
{
    int index = 0;
    while (buffer[index] != '\0')
    {
        cout << index << " --> " << "'" << buffer[index] << "'" << endl;;
        index++;
    }
}
