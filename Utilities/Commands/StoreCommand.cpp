//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-04-24.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#include "../../include/Utilities/Commands/StoreCommand.h"

#include <cstring>
#include <iostream>
#include "OS/Interpreter.h"

void StoreCommand::Execute(const TokenList &tokens)
{
    const char* variable = tokens.tokens[1];
    const char* value = tokens.tokens[2];

    size_t variableLength = strlen(variable);
    char* variableCopy = static_cast<char*>(mmalloc(variableLength+1));
    std::memcpy(variableCopy, variable, variableLength+1);

    size_t valueLength = strlen(value);
    char* valueCopy = static_cast<char*>(mmalloc(valueLength+1));
    std::memcpy(valueCopy, value, valueLength+1);


    void* entryMemory = mmalloc(sizeof(VariableEntry));
    auto* entry = new(entryMemory) VariableEntry{variableCopy, valueCopy, interpreter->variables};
    interpreter->variables = entry;

    std::cout << "Stored '" << variableCopy << "' = " << valueCopy << "\n";
}
