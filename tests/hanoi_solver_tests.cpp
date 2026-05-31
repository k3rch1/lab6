#include <gtest/gtest.h>
#include "hanoi_solver.hpp"

TEST(hanoi_solver, move_count_3) {
    array_sequence<stack<array_sequence, uint>> towers;

    for (size_t i = 0; i < 3; ++i) towers.append({});
    for (uint i = 3; i > 0; --i) towers[2].push(i);
    hanoi_solver solver(3, {2, 0, 1}, towers);
    for (;solver.next_move(););

    ASSERT_EQ(solver.get_current_move(), 7u);
}

TEST(hanoi_solver, move_count_10) {
    array_sequence<stack<array_sequence, uint>> towers;

    for (size_t i = 0; i < 3; ++i) towers.append({});
    for (uint i = 10; i > 0; --i) towers[0].push(i);
    hanoi_solver solver(10, {0, 2, 1}, towers);
    for (;solver.next_move(););

    ASSERT_EQ(solver.get_current_move(), 1023u);
}