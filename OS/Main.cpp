#include <iostream>
#include "OS/Shell.h"
#include "Memory.h"
#include <cstddef>
#include "Utilities/SystemColors.h"
#include "Utilities/MemoryUtils.h"
#include "OS/Interpreter.h"
int main()
{
    cout << "Hello World!" << endl;
    Memory* ram = Memory::GetInstance();

    void* shellMemory = mmalloc(sizeof(Shell));
    Shell* shell = new(shellMemory) Shell();

    cout << "----------------" << endl;
    const char *title = "MapleOS V0.1";
    cout << title << endl;

    //while (true){}
    char *input = shell->GetInput();
    shell->ProcessInput(input, ' ');


    //while (true)shell.GetInput();

    //Memory ram(2);
    //Interpreter intepreter;



    /*
    size_t page = ram->AllocatePage(1);

    cout << "Grabbed page " << page << endl;


    ram->StoreByte(page,'H');
    ram->StoreByte(page,'E');
    ram->StoreByte(page,'Y');

    ram->StoreInt(page,-1);
    ram->StoreByte(page,'Y');

    SystemColors::PrintColored("Printing from RAM: ", PINK_MAGENTA);
    SystemColors::PrintColored(ram->GetPageContent(page,20), RED);

    cout << title << endl;

    shell->DumpPages(4, false);

    */
    shell->~Shell();
    mfree(shellMemory);

    //ram->PrintHeap();


    return 0;
}