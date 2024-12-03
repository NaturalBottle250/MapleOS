//
// Created by danie on 2024-12-02.
//
#include <iostream>
#include <sstream>
#include "Memory.h"
#include <windows.h>//"
#include "../Utilities/SystemColors.h"
using std::cout, std::endl;

int Memory::Initialize(int sizeKB)
{

    cout << "Page size " << PAGE_SIZE <<endl;
    int size = sizeKB*1024;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(sizeKB > MAX_RAM)
    {
        return 1;
    }
    vRAM = (char*) malloc(size);

    cout << sizeof(Page);


    pageTable = (Page*) vRAM;



    for(size_t index = 0; index < PAGE_COUNT; index++)
        pageTable[index] = {index,-1,0, true, false};
    cout << "\n";

    std::ostringstream oss;
    oss << "Initialized Page table with size " << PAGE_TABLE_SIZE;
    SystemColors::PrintColored(oss.str().c_str(), RED);

    oss.str("");

    oss << "\nMemory of size " << size << " initiated at address: "<< &vRAM;
    SystemColors::PrintColored(oss.str().c_str(), BRIGHT_GREEN);

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

int Memory::StoreByte(size_t frame, char byte)
{
    Page& page = pageTable[frame];

    size_t address = GetFrameAddress(frame);
    address = address + page.filledBytes++;

    vRAM[address] = byte;

    std::ostringstream oss;
    oss << "Wrote value '" << byte << "' to address " << static_cast<void*>(&vRAM[address])
        << " (frame " << page.frame << ", offset " << page.filledBytes-1 << " at offset " << address <<")";
    SystemColors::PrintColored(oss.str().c_str(), BRIGHT_BLUE);

    oss.str("");
    return 0;
}

size_t Memory::GetFrameAddress(size_t frame)
{
    size_t start = ZERO_ADDRESS + (PAGE_SIZE * frame);

    return start;
}

char *Memory::GetPageContent(size_t frame, int count)
{
    Page& page = pageTable[frame];

    size_t beginAddress= GetFrameAddress(frame);

    char* buffer = new char[count+1]();

    for(int index = 0; index < count && index < page.filledBytes; index++)
    {
        buffer[index] = vRAM[beginAddress+index];
    }

    buffer[count] = '\0';

    return buffer;
}
