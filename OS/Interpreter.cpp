#include <iostream>

#include "OS/Interpreter.h"

using namespace std;


Interpreter::Interpreter()
{
    cout << "Interpreter created" << endl;
}

Interpreter::~Interpreter()
{
}


void Interpreter::RegisterCommand(const string &name, CommandFunction function, size_t minArgs, size_t maxArgs,
                                  string description)
{
}


