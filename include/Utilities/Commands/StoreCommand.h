//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-24.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef STORECOMMAND_H
#define STORECOMMAND_H
#include "Command.h"


class Interpreter;

class StoreCommand : public Command
{
public:
    const char* name() const override { return "store"; }

    const char* description() const override { return "Stores or updates var x with value y 'store x y'"; }
    size_t minArgs() const override { return 2; }
    size_t maxArgs() const override { return 2; }

    Interpreter* interpreter;
    explicit StoreCommand(Interpreter* interpreter) : interpreter(interpreter) {}
    void Execute(const TokenList &tokens) override;
};



#endif //STORECOMMAND_H
