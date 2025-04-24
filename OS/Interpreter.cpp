#include <iostream>

#include "OS/Interpreter.h"

#include <string.h>

#include "Utilities/Commands/EchoCommand.h"
#include "Utilities/Commands/StoreCommand.h"

using namespace std;


Interpreter::Interpreter()
{

    RegisterCommands();
    cout << "Interpreter created" << endl;


}

Interpreter::~Interpreter()
{
    //Destroy Variables
    VariableEntry* currentVariable = variables;
    while (currentVariable)
    {
        VariableEntry* next = currentVariable->next;

        mfree(currentVariable->name);
        mfree(currentVariable->value);

        currentVariable->~VariableEntry();

        mfree(currentVariable);
        currentVariable = next;
    }
    //Destroy Commands
    CommandNode* currentNode = head;
    while (currentNode)
    {
        CommandNode* nextNode = currentNode->next;

        currentNode->command->~Command();
        mfree(currentNode->command);

        currentNode->~CommandNode();
        mfree(currentNode);
        currentNode = nextNode;
    }
    cout << "Interpreter destroyed" << endl;
}

void Interpreter::RegisterCommands()
{
    //ECHO
    void* echoMemory = mmalloc(sizeof(EchoCommand));
    Command* echoCommand = new(echoMemory) EchoCommand();
    RegisterCommand(echoCommand);

    //STORE
    void* storeMemory = mmalloc(sizeof(StoreCommand));
    Command* storeCommand = new (storeMemory) StoreCommand(this);
    RegisterCommand(storeCommand);
}

void Interpreter::RegisterCommand(Command *command)
{
    // ReSharper disable once CppDFAMemoryLeak
    void* nodeMemory = mmalloc(sizeof(CommandNode));
    CommandNode* commandNode = new(nodeMemory) CommandNode{command, head};
    head = commandNode;

}

Error Interpreter::InterpretCommand(TokenList &tokens)
{
    for (CommandNode* commandNode = head; commandNode; commandNode = commandNode->next)
    {
        Command* command = commandNode->command;
        if (strcmp(tokens.tokens[0], command->name()) == 0)
        {
            if (tokens.count - 1 > command->maxArgs())
                return TOO_MANY_TOKENS;
            if (tokens.count - 1 < command->minArgs())
                return TOO_FEW_TOKENS;


            command->Execute(tokens);

        }
    }



    return COMMAND_NOT_FOUND;
}




