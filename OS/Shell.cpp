#include <iostream>
#include <cstring>
#include "OS/Shell.h"
#include "../include/Memory.h"
#include <cstddef>
#include "../include/Utilities/SystemColors.h"
#include "OS/Interpreter.h"
#include "Utilities/MemoryUtils.h"
#include "Utilities/SystemUtils.h"
using namespace std;




const char* Shell::GetInput()
{
    cout << "$ ";

    char* buffer = static_cast<char*>(mmalloc(101));
    memset(buffer, '\0', 101);

    cin.getline(buffer, 101);

    //cout << buffer << endl;


    //cout << GetNextToken(buffer,' ') << " " << GetNextToken(buffer,' ');

    return buffer;
}

