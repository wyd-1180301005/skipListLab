message(STATUS "Building testHelper")    
set(exeName_test test)           

aux_source_directory(${PROJECT_SOURCE_DIR}/source/test test_source)
add_executable(${exeName_test} ${test_source})
target_include_directories(${exeName_test} PUBLIC ${PROJECT_SOURCE_DIR}/source/skipList)
target_link_libraries(${exeName_test} ${libName_skipList})
target_include_directories(${exeName_test} PUBLIC ${PROJECT_SOURCE_DIR}/source/myAllocator)
target_link_libraries(${exeName_test} ${libName_myAllocator})

find_file(TestmyAllocator_source "TestmyAllocator.cpp" ${current_path})
add_executable(TestmyAllocator  ${myAllocator_source} ${TestmyAllocator_source})
target_link_libraries(${TestmyAllocator} ${libName_myAllocator})
target_include_directories(${libName_myAllocator} PUBLIC ${current_path})