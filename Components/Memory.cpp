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

    cout << sizeof(Page) << endl;


    pageTable = (Page*) vRAM;


    for (size_t index = 0; index < PAGE_COUNT; index++)
    {
        Page& page = pageTable[index];
        page.frame = index;
        page.pID = -1;
        page.filledBytes = 0;
        page.write = true;
        page.read = false;

        for (size_t i = 0; i < PAGE_SIZE; i++)
        {
            page.metadata[i] = EMPTY_TYPE;
        }
    }
    cout << "Paged RAM: " << PAGE_COUNT * PAGE_SIZE <<"\n";

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
    page.metadata[page.filledBytes-1] = CHAR_TYPE;

    std::ostringstream oss;
    oss << "Wrote value '" << byte << "' to address 0x" << std::hex <<address << std::dec
        << " (frame " << page.frame << ", offset " << page.filledBytes-1 << " at actual "<< static_cast<void*>(&vRAM[address])  <<")";
    SystemColors::PrintColored(oss.str().c_str(), BRIGHT_BLUE);

    oss.str("");
    return 0;
}

int Memory::StoreInt(size_t frame, int number)
{
    Page& page = pageTable[frame];

    size_t address = GetFrameAddress(frame);
    address = address + page.filledBytes;

    //page.filledBytes+= sizeof(number);

    std::ostringstream oss;

    for(int index = 0; index < sizeof(number); index++)
    {

        vRAM[address+index] = (number >> (index * 8)) & 0xFF;
        page.metadata[page.filledBytes + index] = INT_TYPE;
        page.filledBytes++;



        int value = static_cast<int>(vRAM[address + index]);
        oss << "Storing " << value
            << " at 0x" << std::hex << (address + index)
            << " (actual address: " << static_cast<void*>(&vRAM[address + index]) << ")";
        SystemColors::PrintColored(oss.str().c_str(), YELLOW_DARK);

        oss.str("");
    }
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

    std::ostringstream oss;
    char* buffer = new char[count + 1]();

    for (int index = 0; index < count && index < page.filledBytes; )
    {
        DataType type = page.metadata[index];

        if (type == INT_TYPE)
        {
            int number = 0;
            for (int i = 0; i < sizeof(int); i++)
            {
                number |= (vRAM[beginAddress + index + i] & 0xFF) << (i * 8);
            }

            oss  << number << " ";
            index += sizeof(int);
        }
        else if (type == CHAR_TYPE)
        {
            oss << vRAM[beginAddress + index] << " ";
            index += 1;
        }
        else
        {
            index += 1;
        }
    }

    std::string result = oss.str();
    memcpy(buffer, result.c_str(), result.size());

    return buffer;
}
