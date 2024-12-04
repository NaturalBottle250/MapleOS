#include <iostream>
#include <cstring>
#include "Shell.h"
#include "../Components/Memory.h"
#include <cstddef>
#include "../Utilities/SystemColors.h"
#include "Interpreter.h"

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
