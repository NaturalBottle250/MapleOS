//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-23.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef COMMAND_H
#define COMMAND_H
#include "Utilities/TokenList.h"


class Command
{
    public:
    virtual ~Command() {}

    virtual const char* name() const = 0;
    virtual const char* description() const = 0;

    virtual size_t minArgs() const = 0;
    virtual size_t maxArgs() const = 0;

    virtual void execute(const TokenList &tokens) = 0;
};



#endif //COMMAND_H
