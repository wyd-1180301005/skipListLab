message(STATUS "Building Tests:")    

# TestmyAllocator
add_executable(TestmyAllocator TestmyAllocator.cpp)
target_link_libraries(TestmyAllocator ${libName_myAllocator})
target_include_directories(TestmyAllocator PUBLIC ${PROJECT_SOURCE_DIR}/source/myAllocator)
