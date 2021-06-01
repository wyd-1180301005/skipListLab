cmake_minimum_required(VERSION 3.10)

# set the project name
project(skipListTest)
# set compiler
set (CMAKE_CXX_COMPILER "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.28.29910\\bin\\Hostx64\\x64\\cl.exe")


add_subdirectory(source/skipList binaries/skipList)
add_subdirectory(source/myAllocator binaries/myAllocator)
add_subdirectory(source/test binaries/test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}") 
set(CXX_STANDARD 11)