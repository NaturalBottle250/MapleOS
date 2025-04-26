//
// Created by Daniel Alzawahra on 2024-12-02.
//
#include <iostream>
#include <sstream>
#include "Memory.h"
#include "Components/Memory.h"

#include <windows.h>//"
#include "Utilities/SystemColors.h"
using std::cout, std::endl;

 Memory* Memory::instance = nullptr;

int Memory::Initialize(int sizeKB)
{
    std::ostringstream oss;


    cout << "Page size in table: " << sizeof(Page) <<endl;
    size = sizeKB*1024;
    if(sizeKB > MAX_RAM)
    {
        return 1;
    }



    heapStart = PAGE_TABLE_SIZE + (PAGE_COUNT * PAGE_SIZE);
    cout << "Allocating Memory\n";
    cout << "Page Table size: " << heapStart << endl;
    cout << "Heap Start: " << heapStart << endl;

    vRAM = static_cast<char *>(std::malloc(size));
    memset(vRAM, 0, size);
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
    SystemColors::PrintColored(oss.str().c_str(), BRIGHT_BLUE);

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

    oss << "Wrote value [" << number << "] at [" << address << " -> " << address + sizeof(int) - 1 << "]";
    oss << " (frame " << page.frame << ", offset " << page.filledBytes << " at actual "<< static_cast<void*>(&vRAM[address])  <<")";

    for(int index = 0; index < sizeof(number); index++)
    {

        vRAM[address+index] = (number >> (index * 8)) & 0xFF;
        page.metadata[page.filledBytes + index] = INT_TYPE;
        page.filledBytes++;
    }

    SystemColors::PrintColored(oss.str().c_str(), YELLOW_DARK);

    return 0;
}

size_t Memory::GetFrameAddress(size_t frame) const
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

    while (offset != 0)
    {
        auto* currentBlock = reinterpret_cast<HeapBlock*>(&vRAM[offset]);

        if (currentBlock->isFree && currentBlock->size >= memorySize + sizeof(HeapBlock))
        {
            size_t leftover = currentBlock->size - memorySize - sizeof(HeapBlock);
            if (leftover > 0)
            {
                size_t newOffset = offset + sizeof(HeapBlock) + memorySize;
                auto* newBlock = reinterpret_cast<HeapBlock*>(&vRAM[newOffset]);

                newBlock->isFree = true;
                newBlock->size   = leftover;
                newBlock->next   = currentBlock->next;

                currentBlock->size      = memorySize;
                currentBlock->isFree    = false;
                currentBlock->next      = newOffset;
            }
            else
                currentBlock->isFree = false;

            return &vRAM[offset + sizeof(HeapBlock)];
        }

        offset = currentBlock->next;
    }

    return nullptr;
}


void Memory::free(void* pointer)
{
    if (!pointer) return;
    size_t offset = static_cast<char*>(pointer) - vRAM - sizeof(HeapBlock);
    auto* targetBlock = reinterpret_cast<HeapBlock*>(&vRAM[offset]);
    targetBlock->isFree = true;

    // Merge with the next block
    if (targetBlock->next)
    {
        auto* nextBlock = reinterpret_cast<HeapBlock*>(&vRAM[targetBlock->next]);
        if (nextBlock->isFree)
        {
            targetBlock->size += sizeof(HeapBlock) + nextBlock->size;
            targetBlock->next  = nextBlock->next;
        }
    }

    // Merge with the previous block
    size_t scanOffset = heapStart;
    while (scanOffset)
    {
        auto* currentBlock = reinterpret_cast<HeapBlock*>(&vRAM[scanOffset]);
        if (currentBlock->next == offset && currentBlock->isFree)
        {
            currentBlock->size += sizeof(HeapBlock) + targetBlock->size;
            currentBlock->next  = targetBlock->next;
            break;
        }
        scanOffset = currentBlock->next;
    }
}


void Memory::PrintHeap()
{
    size_t offset = heapStart;
    size_t totalMemory = 0, freeMemory = 0;

    while (offset < size)
    {
        auto* currentBlock = (HeapBlock*)&vRAM[offset];
        size_t blockTotalSize = currentBlock->size + sizeof(HeapBlock);

        cout << "---------\n";
        cout << "Heap Block\n"
             << "Usable size: " << currentBlock->size << "\n"
             << "Total Size: " << blockTotalSize << "\n"
             << "isFree: " << (currentBlock->isFree ? "True" : "False") << "\n"
             << "Next: " << currentBlock->next << endl;
        cout << "---------\n";

        totalMemory += blockTotalSize;
        if (currentBlock->isFree) freeMemory += blockTotalSize;
        offset = currentBlock->next;

        if (currentBlock->next == 0) break;
    }

    cout << "Total Heap Size (including metadata): " << totalMemory << " bytes\n";
    cout << "Free Heap Size: " << freeMemory - sizeof(HeapBlock) << " bytes\n";
}


void Memory::DumpPages(int count, bool printEmpty)
{
    int counter = count;
    if (count > PAGE_COUNT) count = PAGE_COUNT;
    if (count == 0)
    {
        counter = PAGE_COUNT;
    }
    for (int index = 0; index < counter; index++)
    {
        PrintPage(index, printEmpty);
    }


}

int Memory::GetFreeBytes()
{
    int counter;
    for (int index = heapStart; index < size; index++)
    {

    }
}


void Memory::PrintPage(int number, bool printEmpty)
{
    const Page& p = pageTable[number];
    bool isEmpty = (p.pID == -1);

    if (!isEmpty || (isEmpty && printEmpty))
    {
        cout << "Printing page " << number << "\n"
             << "-----------------\n";

        if (!isEmpty)
        {
            cout << "frame = "     << p.frame       << "\n"
                 << "pid = "       << p.pID        << "\n"
                 << "used = "      << p.filledBytes<< "\n"
                 << "R = "         << p.read        << "\n"
                 << "W = "         << p.write       << "\n";
        }
        else
        {
            cout << "Page is not being used\n";
        }

        cout << "-----------------\n";
    }
}
