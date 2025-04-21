#ifndef MAPLEOS_INTERPRETER_H
#define MAPLEOS_INTERPRETER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;
//Thanks, Mr. Jonathan Campbell<3
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
    ERROR_CD,
    ERROR_MKDIR,
};


class Interpreter
{
    using CommandFunction = function<void(const vector<string>& args)>;

    struct CommandInfo
    {
        CommandFunction function;
        size_t minArgs, maxArgs;
        string description;
    };

    unordered_map<string, CommandInfo> commands;

    void RegisterCommand(const string& name, CommandFunction function,
        size_t minArgs, size_t maxArgs, string description);


public:
    Interpreter();
    int help();
    int ParseInput(const string& input);

};


#endif //MAPLEOS_INTERPRETER_H
