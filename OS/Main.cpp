#include <iostream>
#include "OS/Shell.h"
#include "Memory.h"
#include <cstddef>
#include "Utilities/SystemColors.h"
#include "OS/Interpreter.h"
int main()
{
    Shell shell;
    const char *title = "MapleOS V0.1";

    Memory* ram = Memory::GetInstance();
    //Memory ram(2);
    Interpreter intepreter;

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

    cout << title;

     */
    return 0;
}