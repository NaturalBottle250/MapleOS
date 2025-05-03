#include <iostream>
#include <cstring>
#include "OS/Shell.h"
#include "Memory.h"
#include <cstddef>
#include "../include/Utilities/SystemColors.h"
#include "Components/Memory.h"
#include "OS/Interpreter.h"
#include "Utilities/MemoryUtils.h"
#include "Utilities/SystemUtils.h"
#include "Utilities/TokenList.h"
#include "Utilities/Tokenizer.h"
using namespace std;


Shell::Shell(size_t bufferSize)
{
    this->bufferSize = bufferSize;
    buffer = buffer = static_cast<char*>(mmalloc(bufferSize));
    this->memory = Memory::GetInstance();
    currentTokens = nullptr;

    interpreter = static_cast<Interpreter*>(mmalloc(sizeof(Interpreter)));
    cout << "Size of interpreter: " << sizeof(Interpreter) << endl;
    new(interpreter) Interpreter();
}

void Shell::GetInput()
{
    cout << "$>";

    memset(buffer, '\0', bufferSize);
    ReadLine(bufferSize);


}

size_t Shell::ReadLine(size_t size)
{
    size_t index = 0;
    int  currentCharacter = 0;
    while (index + 1 < size &&
        (currentCharacter = cin.get()) != EOF &&
        currentCharacter != '\n')
    {
        buffer[index] = static_cast<char>(currentCharacter);
        index++;
    }
    buffer[index] = '\0';

    //Clear overflow
    if (currentCharacter != '\n' && currentCharacter != EOF)
    {
        int c;
        while ((c = cin.get()) != EOF && c != '\n');
    }
    return index;
}


void Shell::DumpPages(int count, bool printEmpty)
{
    memory->DumpPages(count, printEmpty);
}

void Shell::ProcessInput(char delimiter)
{

    GetInput();
    TokenList* tokens = TokenizeInput(delimiter);

    cout << tokens->count << endl;

    interpreter->InterpretCommand(*tokens);


    tokens->~TokenList();
    mfree(tokens);


    //mfree(buffer);
    memset(buffer, '\0', bufferSize);
}


void Shell::PrintBuffer(const char* buffer)
{
    int index = 0;
    while (buffer[index] != '\0')
    {
        cout << index << " --> " << "'" << buffer[index] << "'" << endl;;
        index++;
    }
}
Shell::~Shell()
{
    if (interpreter)
    {
        interpreter->~Interpreter();
        mfree(interpreter);
        interpreter = nullptr;
    }

}

TokenList* Shell::TokenizeInput(char delimiter)
{
    return Tokenize(buffer, delimiter);

    size_t spaceCount = 0, index = 0;

    while (buffer[index] != '\0' && buffer[index] != '\n')
    {
        if (buffer[index++] == delimiter) spaceCount++;
    }

    //spaceCount + 1 is token count
    spaceCount++;

    char** tokens = static_cast<char**>(mmalloc(sizeof(char*) * spaceCount ));

    char* scanner = buffer;

    index = 0;

    char* token = GetNextToken(scanner, delimiter);

    while (token && index < spaceCount)
    {
        size_t tokenLength = strlen(token);
        char* copyToken = static_cast<char*>(mmalloc(tokenLength+1));
        memcpy(copyToken, token, tokenLength+1);
        mfree(token);

        tokens[index++] = copyToken;
        token = GetNextToken(nullptr, delimiter);
    }


    void* memoryPointer = mmalloc(sizeof(TokenList));
    if (memoryPointer == nullptr)
        cout << "Memory pointer is null" << endl;

    TokenList* tokenList = new (memoryPointer) TokenList{tokens, spaceCount};

    return tokenList;
}
