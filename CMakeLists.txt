cmake_minimum_required(VERSION 3.30)
project(MapleOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(MapleOS OS/Shell.cpp
        OS/Interpreter.cpp
        OS/Interpreter.h
        OS/Shell.h
        OS/System.cpp
        OS/System.h
        Components/Memory.cpp
        Components/Memory.h
        Utilities/SystemColors.cpp
        Utilities/SystemColors.h
        OS/Main.cpp)
