#include <iostream>
#include <cstring>
#include "OS/Shell.h"
#include "Memory.h"
#include <cstddef>
#include "../include/Utilities/SystemColors.h"
#include "OS/Interpreter.h"
#include "Utilities/MemoryUtils.h"
#include "Utilities/SystemUtils.h"
#include "Utilities/TokenList.h"
using namespace std;


Shell::Shell()
{
    this->memory = Memory::GetInstance();
    currentTokens = nullptr;

    interpreter = static_cast<Interpreter*>(mmalloc(sizeof(Interpreter)));
    cout << "Size of interpreter: " << sizeof(Interpreter) << endl;
    new(interpreter) Interpreter();
}

char* Shell::GetInput()
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

    //PrintBuffer(buffer);
    //mfree(buffer);

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

    //Clear overflow
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

void Shell::ProcessInput(char* buffer, char delimiter)
{

    TokenList * tokens = TokenizeInput(buffer, delimiter);

    for (int index = 0; index < tokens->count; index++)
    {
        //cout << tokens->tokens[index] << endl;
    }

    /*
    for (int index = 0; index < tokens->count; index++)
    {
        mfree(tokens->tokens[index]);
    }
    mfree(tokens->tokens);

    mfree(tokens);
    */
    interpreter->InterpretCommand(*tokens);
    tokens->~TokenList();
    mfree(tokens);


    mfree(buffer);
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
Shell::~Shell()
{
    if (interpreter)
    {
        interpreter->~Interpreter();
        mfree(interpreter);
        interpreter = nullptr;
    }

}

TokenList* Shell::TokenizeInput(char *buffer, char delimiter)
{

    size_t spaceCount = 0, index = 0;

    while (buffer[index] != '\0' && buffer[index] != '\n')
    {
        if (buffer[index++] == delimiter) spaceCount++;
    }
    cout << "Space count: " << spaceCount << endl;

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

    TokenList* tokenList = new (mmalloc(sizeof(TokenList))) TokenList{tokens, spaceCount};

    return tokenList;
}
