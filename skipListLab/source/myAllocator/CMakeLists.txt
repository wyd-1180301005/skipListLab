message(STATUS "Building myAllocator")    
set(libName_myAllocator myAllocator CACHE STRING "libName_myAllocator")
set(current_path ${PROJECT_SOURCE_DIR}/source/myAllocator)

find_file(myAllocator_source "myAllocator.cpp" ${current_path})
add_library(${libName_myAllocator} STATIC ${myAllocator_source}) 
target_include_directories(${libName_myAllocator} PUBLIC ${current_path})

find_file(TestmyAllocator_source "TestmyAllocator.cpp" ${current_path})
add_executable(TestmyAllocator ${TestmyAllocator_source})
target_include_directories(${libName_myAllocator} PUBLIC ${current_path})