#ifndef MAPLEOS_INTERPRETER_H
#define MAPLEOS_INTERPRETER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "Utilities/Commands/Command.h"
using namespace std;
//Thanks to Mr.Jonathan Campbell
enum Error
{
    NO_ERROR,
    FILE_DOES_NOT_EXIST,
    FILE_ERROR,
    NO_MEM_SPACE,
    READY_QUEUE_FULL,
    SCHEDULING_ERROR,
    TOO_MANY_TOKENS,
    TOO_FEW_TOKENS,
    NON_ALPHANUMERIC_TOKEN,
    BAD_COMMAND,
    COMMAND_EXECUTION_ERROR,
    COMMAND_NOT_FOUND,
};

struct TokenList;


struct CommandNode
{
    Command* command;
    CommandNode* next;
};


class Interpreter
{
    CommandNode* head = nullptr;
    using CommandFunction = function<void(const vector<string>& args)>;

    struct CommandInfo
    {
        char name[16];
        CommandFunction function;
        size_t minArgs, maxArgs;
        char description[121];
    };

    unordered_map<string, CommandInfo> commands;



public:
    Interpreter();
    ~Interpreter();
    void help();
    void Execute(const vector<string>& tokens);

    void RegisterCommands();
    void RegisterCommand(Command* command);

    Error InterpretCommand(TokenList& tokens);


};


#endif //MAPLEOS_INTERPRETER_H
