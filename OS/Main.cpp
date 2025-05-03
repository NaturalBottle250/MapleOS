#include <iostream>
#include "OS/Shell.h"
#include "Memory.h"
#include <cstddef>
#include <cstdint>
#include <sstream>

#include "Components/Memory.h"
#include "Languages/Assembler.h"
#include "Utilities/SystemColors.h"
#include "Utilities/MemoryUtils.h"
#include "OS/Interpreter.h"
#include "Utilities/Tokenizer.h"


void RunOS()
{

    cout << "Hello World! " << sizeof(int*) << endl;
    Memory* ram = Memory::GetInstance();

    std::ostringstream oss;
    oss << "Hello World!" << endl;
    SystemColors::PrintColored(oss.str().c_str(), RED);

    void* shellMemory = mmalloc(sizeof(Shell));
    Shell* shell = new(shellMemory) Shell(101);

    cout << "----------------" << endl;
    const char *title = "MapleOS V0.1";
    cout << title << endl;


    //while (true){}
    for (int index = 0; index < 10; index++)
    {

        shell->ProcessInput(' ');
        //ram->PrintHeap();

    }



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

}

void TestAssembler()
{
    char buffer[] = "LOADI R0 55";
    TokenList* tokens = Tokenize(buffer, ' ');

    std::cout << "Buffer: " << buffer << std::endl;

    //tokens->Print();

    std::vector<uint8_t> bytes = Assembler::AssembleTokens(*tokens);

    std::cout << "Bytecode:";
    for (uint8_t b : bytes)
    {
        std::cout << " 0x" << std::hex << static_cast<int>(b);
    }
    std::cout << std::dec << std::endl;

    tokens->~TokenList();
    mfree(tokens);
}


int main()
{
    TestAssembler();

    return 0;
}
