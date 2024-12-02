
#ifndef MAPLEOS_MEMORY_H
#define MAPLEOS_MEMORY_H

#include <cstddef>

#define PAGE_SIZE 128
#define PAGE_COUNT 128
#define RAM_SIZE_KB 64
#define MAX_RAM 1024
#define PAGE_TABLE_SIZE PAGE_SIZE*PAGE_COUNT
struct Page
{
    size_t frame;
    int pID, filledBytes;
    bool write, read;

};
class Memory
{
    char* vRAM;
    Page* pageTable;
private:

public:
    Memory(int size)
    {
        Initialize(RAM_SIZE_KB);
    }

    int Initialize(int sizeKB);
    size_t AllocatePage(int pID);

    void Reset();

};


#endif //MAPLEOS_MEMORY_H
