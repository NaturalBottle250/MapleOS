//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-05-02.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#include "../include/Utilities/Tokenizer.h"

#include "Utilities/SystemUtils.h"

TokenList * Tokenize(char *buffer, char delimiter)
{

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
        std::cout << "Memory pointer is null" << std::endl;

    TokenList* tokenList = new (memoryPointer) TokenList{tokens, spaceCount};

    return tokenList;
}
