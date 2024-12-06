#include <iostream>
#include <cstring>
#include "MemoryUtils.h"
#ifndef MAPLEOS_SYSTEMUTILS_H
#define MAPLEOS_SYSTEMUTILS_H


int CountTokens(const char* input, char regex)
{
    int index = 0, count = 1;
    while(input[index] != '\0')
    {
        if(input[index] == regex)
            count++;
        index++;
    }

    return count;
}
char* GetNextToken(const char* input, char regex)
{
    static const char* currentPosition = nullptr;

    if (input != nullptr)
        currentPosition = input;

    if (currentPosition == nullptr || *currentPosition == '\0')
        return nullptr;

    const char* start = currentPosition;
    const char* end = currentPosition;

    while (*end != '\0' && *end != regex)
        end++;

    size_t tokenLength = end - start;

    char* token = static_cast<char*>(mmalloc(tokenLength + 1));
    std::strncpy(token, start, tokenLength);
    token[tokenLength] = '\0';

    if (*end == '\0')
         currentPosition = nullptr;
    else currentPosition = end + 1;


    return token;
}

#endif //MAPLEOS_SYSTEMUTILS_H
