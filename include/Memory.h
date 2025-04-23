
#ifndef MAPLEOS_MEMORY_H
#define MAPLEOS_MEMORY_H

#include <cstddef>


#define RAM_SIZE_KB 4
#define MAX_RAM 1024

#define PAGE_SIZE      16
#define PAGE_COUNT     16
#define PAGE_TABLE_SIZE    (PAGE_COUNT * sizeof(Page))


//#define ZERO_ADDRESS PAGE_TABLE_SIZE

#define HEAP_START (ZERO_ADDRESS + (PAGE_COUNT * PAGE_SIZE))
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

struct HeapBlock
{
    size_t size, next;
    bool isFree;
};

class Memory
{

    char* vRAM;
    Page* pageTable;
private:

    static Memory* instance;
    int size, heapStart, zeroAddress = PAGE_TABLE_SIZE;
    size_t GetFrameAddress(size_t frame) const;

    explicit Memory(int size)
    {
        Initialize(RAM_SIZE_KB);
    }

    void PrintPage(int number, bool printEmpty);

public:

    static Memory* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new Memory(RAM_SIZE_KB);
        }
        return instance;
    }
    int Initialize(int sizeKB);
    int InitializeHeap(size_t heapSize);
    size_t AllocatePage(int pID);

    void PrintHeap();

    int StoreByte(size_t frame,char byte);
    int StoreInt(size_t frame, int number);

    void* malloc(size_t memorySize);
    void free(void* pointer);

    char* GetPageContent(size_t frame, int count);
    void DumpPages(int count, bool printEmpty);

    int GetFreeBytes();

    void Reset();

};


#endif //MAPLEOS_MEMORY_H
