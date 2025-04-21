
#include "OS/Interpreter.h"


Interpreter::Interpreter()
{
}


void Interpreter::RegisterCommand(const string &name, CommandFunction function, size_t minArgs, size_t maxArgs,
    string description)
{
}


int Interpreter::ParseInput(const string &input)
{
    return 0;
}
