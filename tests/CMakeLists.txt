add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../googletest
    googletest-build
)

enable_testing()

add_executable(
    tests
    stack_tests.cpp
    hanoi_solver_tests.cpp
    ../src/hanoi/hanoi_solver.cpp
    ../include/hanoi_solver.hpp
)

target_include_directories(
    tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(
    tests
    GTest::gtest_main
    lab5
)

include(GoogleTest)

gtest_discover_tests(tests)