#include <iostream>
#include <cstring>
#include "OS/Shell.h"
#include "../include/Memory.h"
#include <cstddef>
#include "../include/Utilities/SystemColors.h"
#include "OS/Interpreter.h"

using namespace std;




const char* Shell::GetInput()
{
    cout << "$ ";

    char* buffer = new char[101]();

    string temp;

    std::getline(std::cin, temp);

    std::strcpy(buffer,temp.c_str());



    return buffer;
}
