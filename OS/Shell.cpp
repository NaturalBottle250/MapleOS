#include <iostream>
#include "Shell.h"
#include "../Components/Memory.h"
#include <cstddef>
#include "../Utilities/SystemColors.h"
using std::cout, std::endl;


int main()
{

    const char *title = "MapleOS V0.1";

    Memory ram(2);

    size_t page = ram.AllocatePage(1);

    cout << "\nGrabbed page " << page << endl;

    ram.StoreByte(page,'H');
    ram.StoreByte(page,'E');
    ram.StoreByte(page,'Y');


    SystemColors::PrintColored("Printing from RAM: ", PINK_MAGENTA);
    SystemColors::PrintColored(ram.GetPageContent(page,20), RED);

    cout << title;

    return 0;
}

