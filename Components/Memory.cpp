//
// Created by Daniel Alzawahra on 2024-12-02.
//
#include <iostream>
#include <sstream>
#include "Memory.h"
#include <windows.h>//"
#include "Utilities/SystemColors.h"
using std::cout, std::endl;

 Memory* Memory::instance = nullptr;

int Memory::Initialize(int sizeKB)
{
    std::ostringstream oss;


    //cout << "Page size " << PAGE_SIZE <<endl;
    size = sizeKB*1024;
    if(sizeKB > MAX_RAM)
    {
        return 1;
    }



    heapStart = PAGE_TABLE_SIZE + (PAGE_COUNT * PAGE_SIZE);
    cout << "Allocating Memory\n";
    vRAM = (char*) std::malloc(size);
    cout << "Size of a heap block: " << sizeof(HeapBlock) << endl;

    size_t heapSize = size - heapStart;

    InitializeHeap(heapSize);

    oss << "Initialized heap of size " << heapSize << " starting at " << heapStart << endl;
    SystemColors::PrintColored(oss.str().c_str(), BRIGHT_WHITE);




    //cout << sizeof(Page) << endl;


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

    oss << "Initialized Page table with size " << PAGE_TABLE_SIZE;
    SystemColors::PrintColored(oss.str().c_str(), RED);

    oss.str("");

    oss << "Memory of size " << size << " initiated at address: "<< &vRAM;
    SystemColors::PrintColored(oss.str().c_str(), BRIGHT_GREEN);
    oss.str("");



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
    oss << "Wrote value '" << byte << "' to address " << address << std::dec
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

    oss << "Storing " << number << " at [" << address << " -> " << address + sizeof(int) - 1 << "]";
    SystemColors::PrintColored(oss.str().c_str(), YELLOW_DARK);

    for(int index = 0; index < sizeof(number); index++)
    {

        vRAM[address+index] = (number >> (index * 8)) & 0xFF;
        page.metadata[page.filledBytes + index] = INT_TYPE;
        page.filledBytes++;





    }
    return 0;
}

size_t Memory::GetFrameAddress(size_t frame)
{
    size_t start = zeroAddress + (PAGE_SIZE * frame);

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

int Memory::InitializeHeap(size_t heapSize)
{

    auto initBlock = reinterpret_cast<HeapBlock *>(&vRAM[heapStart]);

    initBlock->size = heapSize - sizeof(HeapBlock);
    initBlock->isFree = true;
    initBlock->next = 0;

    return 0;
}

void* Memory::malloc(size_t memorySize)
{
    size_t offset = heapStart;


    while (offset < this->size)
    {
        auto* currentBlock = (HeapBlock*)&vRAM[offset];


        if (currentBlock->isFree && currentBlock->size >= memorySize + sizeof(HeapBlock))
        {
            size_t newBlockOffset = memorySize + sizeof(HeapBlock) + offset;
            auto* newBlock = (HeapBlock*)&vRAM[newBlockOffset];

            newBlock->isFree = true;
            newBlock->size = currentBlock->size - memorySize - sizeof(HeapBlock);
            newBlock->next = 0;


            currentBlock->size = memorySize;
            currentBlock->isFree = false;
            currentBlock->next = offset + memorySize + sizeof(HeapBlock);


            return &vRAM[offset + sizeof(HeapBlock)];
        }

        offset = currentBlock->next;

        if (offset == 0)
        {
            break;
        }
    }

    return nullptr;
}

void Memory::free(void *pointer)
{
    if(pointer == nullptr) return;

    size_t blockOffset = (char*)pointer - vRAM - sizeof(HeapBlock);

    auto* targetBlock = (HeapBlock*)&vRAM[blockOffset];

    targetBlock->isFree = true;

    if(targetBlock->next >= size)
        return;

    auto* nextBlock = (HeapBlock*)&vRAM[targetBlock->next];

    if(nextBlock->isFree)
    {
        targetBlock->size += nextBlock->size + sizeof(HeapBlock);

        targetBlock->next = nextBlock->next;
    }


}

void Memory::PrintHeap() {
    size_t offset = heapStart;
    size_t totalMemory = 0;

    while (offset < size) {
        auto* currentBlock = (HeapBlock*)&vRAM[offset];
        size_t blockTotalSize = currentBlock->size + sizeof(HeapBlock);

        cout << "---------\n";
        cout << "Heap Block\n"
             << "Size (user): " << currentBlock->size << "\n"
             << "Total Size: " << blockTotalSize << "\n"
             << "isFree: " << (currentBlock->isFree ? "True" : "False") << "\n"
             << "Next: " << currentBlock->next << endl;
        cout << "---------\n";

        totalMemory += blockTotalSize;
        offset = currentBlock->next;

        if (currentBlock->next == 0) break;
    }

    cout << "Total Heap Size (including metadata): " << totalMemory << " bytes\n";
}
