cmake_minimum_required(VERSION 3.10)

# set the project name
project(skipListTest)
# set compiler
set (CMAKE_CXX_COMPILER "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.28.29910\\bin\\Hostx64\\x64\\cl.exe")
set(CXX_STANDARD 17)

set(CONFIG_TYPE $ENV{CMAKE_CONFIG_TYPE} CACHE STRING "" FORCE)
# deal with null env_var
if(CONFIG_TYPE)
  message(STATUS CONFIG_TYPE:)
  message(STATUS ${CONFIG_TYPE})
  else()
  message(FATAL_ERROR "NULL config.")
endif()

if(${CONFIG_TYPE} STREQUAL DEBUG)

  # MUST use FORCE option sothat cached variables are rewritten 
  set(ENABLE_DEBUG_INTERFACE TRUE CACHE BOOL "" FORCE)
  set(ENABLE_TESTING TRUE CACHE BOOL "" FORCE)
  add_definitions(-DENABLE_DEBUG_INTERFACE -DENABLE_TESTING)
  add_compile_options(/Od /std:c++17)

elseif(${CONFIG_TYPE} STREQUAL RELEASE)

  set(ENABLE_DEBUG_INTERFACE FALSE CACHE BOOL "" FORCE)
  set(ENABLE_TESTING FALSE CACHE BOOL "" FORCE)
  add_definitions(-DDISABLE_DEBUG_INTERFACE -DDISABLE_TESTING)
  add_compile_options(/O2 /std:c++17)
  
else()
  message(FATAL_ERROR "unknown config.")
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory(source/skipList binaries/skipList)
add_subdirectory(source/myAllocator binaries/myAllocator)


# test only in debug config
if(${ENABLE_TESTING})
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  add_subdirectory(source/test binaries/test)
  add_subdirectory(source/main binaries/main)
endif()
