//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-25.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef RESETCOMMAND_H
#define RESETCOMMAND_H
#include "Command.h"

class Interpreter;

class ResetCommand : public Command
{
public:
    const char* name() const override { return "reset"; }

    const char* description() const override { return "Resets all variables stored in Shell memory "; }
    size_t minArgs() const override { return 0; }
    size_t maxArgs() const override { return 0; }

    Interpreter* interpreter;
    explicit ResetCommand(Interpreter* interpreter) : interpreter(interpreter) {}
    void Execute(const TokenList &tokens) override;
};



#endif //RESETCOMMAND_H
