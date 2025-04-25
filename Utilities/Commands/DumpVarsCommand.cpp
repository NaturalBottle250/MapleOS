//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-25.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#include "../../include/Utilities/Commands/DumpVarsCommand.h"

#include <cstring>
#include <iostream>
#include "OS/Interpreter.h"
void DumpVarsCommand::Execute(const TokenList &tokens)
{
    VariableEntry* currentVar = interpreter->variables;
    while (currentVar != nullptr)
    {
        cout << currentVar->name << " --> " << currentVar->value << endl;
        currentVar = currentVar->next;
    }
}
