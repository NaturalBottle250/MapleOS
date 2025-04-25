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
    const char* name = tokens.tokens[1];
    const char* value = tokens.tokens[2];

    cout << name << " " << value << endl;

    size_t nameLength = strlen(name)+1;
    size_t valueLength = strlen(value)+1;

    size_t memorySize = nameLength + valueLength + sizeof(VariableEntry);

    char* entryMemory = static_cast<char*>(mmalloc(memorySize));

    auto* entry = new (entryMemory) VariableEntry
    {
    entryMemory + sizeof(VariableEntry),
        entryMemory + sizeof(VariableEntry) + nameLength,
        interpreter->variables
    };
    interpreter->variables = entry;

    std::memcpy(entry->name, name, nameLength);
    std::memcpy(entry->value, value, valueLength);

    std::cout << "Stored '" << entry->name << "' = '" << entry->value << "'\n";

    /*
    char* variableCopy = static_cast<char*>(mmalloc(variableLength+1));
    std::memcpy(variableCopy, variable, variableLength+1);

    char* valueCopy = static_cast<char*>(mmalloc(valueLength+1));
    std::memcpy(valueCopy, value, valueLength+1);


    void* entryMemory = mmalloc(sizeof(VariableEntry));
    if (interpreter->variables == nullptr)
    {
        auto* entry = new(entryMemory) VariableEntry{variableCopy, valueCopy, nullptr};
        interpreter->variables = entry;
    }
    else
    {
        auto* entry = new(entryMemory) VariableEntry{variableCopy, valueCopy, interpreter->variables};
        interpreter->variables = entry;
    }
    std::cout << "Stored '" << variableCopy << "' = " << valueCopy << "\n";

    */
}
