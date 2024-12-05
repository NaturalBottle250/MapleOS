//
// Created by danie on 2024-12-02.
//

#include "../include/Utilities/SystemColors.h"
#include <windows.h>
#include <iostream>

void SystemColors::PrintColored(const char *content, int color)
{
    HANDLE handle =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
    std::cout << content << std::endl;
    SetConsoleTextAttribute(handle, DEFAULT);

}
