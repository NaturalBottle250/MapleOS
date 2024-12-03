//
// Created by danie on 2024-12-01.
//

#ifndef MAPLEOS_INTERPRETER_H
#define MAPLEOS_INTERPRETER_H

#include <string>

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

public:
    int help();
    int ParseInput(const string& input);

};


#endif //MAPLEOS_INTERPRETER_H
