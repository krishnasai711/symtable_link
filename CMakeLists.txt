cmake_minimum_required(VERSION 3.10)
project(SymbolTable CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(test_linked ${CMAKE_SOURCE_DIR}/src/symtable_link.cpp ${CMAKE_SOURCE_DIR}/tests/symtable_test.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(test_linked ${GTEST_LIBRARIES} pthread)

set_target_properties(test_linked PROPERTIES CLEAN_DIRECTORIES "build")

add_custom_target(run_tests
    COMMAND test_linked
    DEPENDS test_linked
)
