//
// Created by danie on 2024-12-02.
//
#include <iostream>
#include "Memory.h"
#include <windows.h>//"

using std::cout, std::endl;

int Memory::Initialize(int sizeKB)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(sizeKB > MAX_RAM)
    {
        return 1;
    }
    vRAM = (char*) malloc(sizeKB * 1024);

    cout << sizeof(Page);


    pageTable = (Page*) vRAM;



    for(size_t index = 0; index < PAGE_COUNT; index++)
        pageTable[index] = {index,-1, true, false};
    cout << "\n";

    SetConsoleTextAttribute(handle,2);
    cout << "Initialized Page table with size " << PAGE_TABLE_SIZE << endl;
    SetConsoleTextAttribute(handle,10);

    cout << "\nMemory of size " << sizeKB * 1024 << " initiated at address: "<< &vRAM << endl;
    SetConsoleTextAttribute(handle,7);
    return 0;
}

size_t Memory::AllocatePage(int pID)
{
    for(size_t index = 0; index < PAGE_COUNT; index++)
    {
        if(pageTable[index].pID == -1)
        {
            pageTable[index].pID = pID;
            return index;
        }
    }
        return -1;
}
