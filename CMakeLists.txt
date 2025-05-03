cmake_minimum_required(VERSION 3.30)
project(MapleOS)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(MapleOS Components/Memory.cpp
        OS/Shell.cpp
        OS/Interpreter.cpp
        include/OS/Interpreter.h
        include/OS/Shell.h
        OS/System.cpp
        include/OS/System.h
        include/Components/Memory.h
        Utilities/SystemColors.cpp
        include/Utilities/SystemColors.h
        OS/Main.cpp
        include/Utilities/MemoryUtils.h
        include/Utilities/SystemUtils.h
        include/Utilities/Commands/Command.h
        include/Utilities/TokenList.h
        include/Utilities/Commands/EchoCommand.h
        Utilities/Commands/StoreCommand.cpp
        include/Utilities/Commands/StoreCommand.h
        Utilities/Commands/ResetCommand.cpp
        include/Utilities/Commands/ResetCommand.h
        Utilities/Commands/DumpVarsCommand.cpp
        include/Utilities/Commands/DumpVarsCommand.h
        Components/CPU.cpp
        include/Components/CPU.h
        Languages/Assembler.cpp
        include/Languages/Assembler.h
        Utilities/Tokenizer.cpp
        include/Utilities/Tokenizer.h
)
