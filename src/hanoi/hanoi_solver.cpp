#include "hanoi_solver.hpp"

hanoi_solver::hanoi_solver(uint disks) {
    solve(disks, 0, 2, 1);
}

void hanoi_solver::solve(uint n,uint from, uint to, uint aux) {
    if (n == 0) return;
    solve(n - 1, from, aux, to);
    moves.append({from, to});
    solve(n - 1, aux, to, from);
}

const array_sequence<hanoi_move>& hanoi_solver::get_moves() const {
    return moves;
}