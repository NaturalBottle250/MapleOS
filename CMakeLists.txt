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
        include/Memory.h
        Utilities/SystemColors.cpp
        include/Utilities/SystemColors.h
        OS/Main.cpp
        include/Utilities/MemoryUtils.h
        include/Utilities/SystemUtils.h)
