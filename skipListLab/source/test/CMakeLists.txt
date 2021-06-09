message(STATUS "Building Tests:")    

enable_testing()

# testHelper
add_library(testHelper STATIC testHelper.cpp)
target_include_directories(
    testHelper
    PUBLIC ${PROJECT_BINARY_DIR}/_deps/googletest-src/googletest/include
)

# TestmyAllocator
add_executable(TestmyAllocator TestmyAllocator.cpp)
target_link_libraries(
    TestmyAllocator 
    ${libName_myAllocator}
    testHelper
    gtest_main
)
target_include_directories(
    TestmyAllocator 
    PUBLIC ${PROJECT_SOURCE_DIR}/source/myAllocator 
    PUBLIC ${PROJECT_BINARY_DIR}/_deps/googletest-src/googletest/include
)

# TestskipList
add_executable(TestskipList TestskipList.cpp)
target_link_libraries(
    TestskipList 
    ${libName_skipList}
    testHelper
    gtest_main
)
target_include_directories(
    TestskipList 
    PUBLIC ${PROJECT_SOURCE_DIR}/source/skipList
    PUBLIC ${PROJECT_SOURCE_DIR}/source/myAllocator
    PUBLIC ${PROJECT_BINARY_DIR}/_deps/googletest-src/googletest/include
)

include(GoogleTest)
gtest_discover_tests(TestmyAllocator)
gtest_discover_tests(TestskipList)

