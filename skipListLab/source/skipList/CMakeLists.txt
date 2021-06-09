message(STATUS "Building skipList")    
set(libName_skipList skipList CACHE STRING "libName_skipList")
set(current_path ${PROJECT_SOURCE_DIR}/source/skipList)

aux_source_directory(${current_path} skipList_source)
add_library(${libName_skipList} STATIC ${skipList_source}) 
target_include_directories(${libName_skipList} PUBLIC ${current_path} ${PROJECT_SOURCE_DIR}/source/myAllocator)


