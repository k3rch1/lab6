#pragma once
using uint = unsigned int;

#include "array_sequence.hpp"

struct hanoi_move {
    uint from;
    uint to;
};

class hanoi_solver {
private:
    array_sequence<hanoi_move> moves;

    void solve(uint n, uint from, uint to, uint aux);

public:
    explicit hanoi_solver(uint disks);

    const array_sequence<hanoi_move>& get_moves() const;
};