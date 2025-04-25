//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-25.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef DUMPVARSCOMMAND_H
#define DUMPVARSCOMMAND_H
#include "Command.h"
#include "OS/Interpreter.h"
#include "Utilities/TokenList.h"


class DumpVarsCommand : public Command
{
public:
    const char* name() const override { return "dumpvars"; }

    const char* description() const override { return "Prints all the Shell variables"; }
    size_t minArgs() const override { return 0; }
    size_t maxArgs() const override { return 0; }

    Interpreter* interpreter;
    explicit DumpVarsCommand(Interpreter* interpreter) : interpreter(interpreter) {}
    void Execute(const TokenList &tokens) override;
};



#endif //DUMPVARSCOMMAND_H
