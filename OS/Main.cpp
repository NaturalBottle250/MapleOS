#include <iostream>
#include "Shell.h"
#include "../Components/Memory.h"
#include <cstddef>
#include "../Utilities/SystemColors.h"
#include "Interpreter.h"
int main()
{
    Shell shell;
    cout << sizeof(shell);
    const char *title = "MapleOS V0.1";

    Memory ram(2);
    Interpreter intepreter;

    size_t page = ram.AllocatePage(1);

    cout << "\nGrabbed page " << page << endl;


    ram.StoreByte(page,'H');
    ram.StoreByte(page,'E');
    ram.StoreByte(page,'Y');

    ram.StoreInt(page,-1);

    SystemColors::PrintColored("Printing from RAM: ", PINK_MAGENTA);
    SystemColors::PrintColored(ram.GetPageContent(page,20), RED);

    cout << title;

    return 0;
}