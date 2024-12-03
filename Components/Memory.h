
#ifndef MAPLEOS_MEMORY_H
#define MAPLEOS_MEMORY_H

#include <cstddef>


#define PAGE_COUNT 64
#define RAM_SIZE_KB 4
#define MAX_RAM 1024
struct Page
{
    size_t frame;
    int pID, filledBytes;
    bool write, read;

};
#define PAGE_TABLE_SIZE sizeof(Page)*PAGE_COUNT

class Memory
{
#define PAGE_SIZE (((RAM_SIZE_KB * 1024) - PAGE_TABLE_SIZE)/PAGE_COUNT)
#define ZERO_ADDRESS PAGE_TABLE_SIZE
    char* vRAM;
    Page* pageTable;
private:

    size_t GetFrameAddress(size_t frame);

public:
    Memory(int size)
    {
        Initialize(RAM_SIZE_KB);
    }

    int Initialize(int sizeKB);
    size_t AllocatePage(int pID);

    int StoreByte(size_t frame,char byte);

    char* GetPageContent(size_t frame, int count);

    void Reset();

};


#endif //MAPLEOS_MEMORY_H
