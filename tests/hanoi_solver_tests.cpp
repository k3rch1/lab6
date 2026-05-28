#include <gtest/gtest.h>
#include "hanoi_solver.hpp"

TEST(hanoi_solver, move_count) {
    hanoi_solver solver(3, {2, 0, 1});

    ASSERT_EQ(solver.get_moves().size(), 7);
}

TEST(hanoi_solver, move_count_2) {
    hanoi_solver solver(10, {0, 2, 1});

    ASSERT_EQ(solver.get_moves().size(), 1023);
}