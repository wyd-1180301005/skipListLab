message(STATUS "Building myAllocator")   
set(libName_myAllocator myAllocator CACHE STRING "libName_myAllocator")
set(current_path ${PROJECT_SOURCE_DIR}/source/myAllocator)

add_library(${libName_myAllocator} STATIC myAllocator_origin.cpp) 
target_include_directories(${libName_myAllocator} PUBLIC ${current_path})

