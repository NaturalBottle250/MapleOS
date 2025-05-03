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


    size_t nameLength = strlen(name)+1;
    size_t valueLength = strlen(value)+1;

    size_t memorySize = nameLength + valueLength + sizeof(VariableEntry);

    //TODO:: MENTION 1 VS 3 ALLOCATIONS
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

    std::cout << "Stored variable successfully." << std::endl;


}
