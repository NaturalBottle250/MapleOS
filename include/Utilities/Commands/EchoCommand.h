//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-23.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "Command.h"
#include <iostream>
class EchoCommand : public Command
{
public:
    const char* name() const override { return "echo"; }

    const char* description() const override { return "Prints all its arguments"; }
    size_t minArgs() const override { return 1; }
    size_t maxArgs() const override { return 99; }

    void Execute(const TokenList& tokens) override
    {
        for (size_t index = 1; index < tokens.count; ++index)
            std::cout << tokens.tokens[index] << ' ';
        std::cout << '\n';
    }
};
#endif //ECHOCOMMAND_H
