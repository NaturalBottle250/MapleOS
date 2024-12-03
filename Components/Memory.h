
#ifndef MAPLEOS_MEMORY_H
#define MAPLEOS_MEMORY_H

#include <cstddef>


#define PAGE_COUNT 64
#define RAM_SIZE_KB 20
#define MAX_RAM 1024
#define PAGE_TABLE_SIZE sizeof(Page)*PAGE_COUNT
//#define PAGE_SIZE (((RAM_SIZE_KB * 1024) - PAGE_TABLE_SIZE)/PAGE_COUNT)
#define PAGE_SIZE 58
#define ZERO_ADDRESS PAGE_TABLE_SIZE
enum DataType
{
    EMPTY_TYPE, CHAR_TYPE, INT_TYPE, FLOAT_TYPE, STRING_TYPE
};

struct Page
{
    size_t frame;
    int pID, filledBytes;
    bool write, read;
    DataType metadata[PAGE_SIZE];
};


class Memory
{

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
    int StoreInt(size_t frame, int number);

    char* GetPageContent(size_t frame, int count);

    void Reset();

};


#endif //MAPLEOS_MEMORY_H
