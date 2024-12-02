#include <iostream>
#include "Shell.h"
#include "../Components/Memory.h"

using std::cout, std::endl;


int main()
{

    const char *title = "MapleOS V0.1";

    Memory ram(2);

    cout << ram.AllocatePage(1) << endl;
    cout << title;

    return 0;
}

