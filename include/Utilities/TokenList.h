//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-23.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef TOKENLIST_H
#define TOKENLIST_H
#include "MemoryUtils.h"

struct TokenList
{
    char** tokens;
    size_t count;

    ~TokenList()
    {
        for (int index = 0; index < count; index++)
            mfree(tokens[index]);

        mfree(tokens);
    }
};

#endif //TOKENLIST_H
