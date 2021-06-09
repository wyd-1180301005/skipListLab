message(STATUS "Building main")   
set(current_path ${PROJECT_SOURCE_DIR}/source/main)

add_executable(main main.cpp)
target_link_libraries(main ${libName_myAllocator})
target_include_directories(main PUBLIC ${current_path} ${PROJECT_SOURCE_DIR}/source/myAllocator ${PROJECT_SOURCE_DIR}/source/skipList)

