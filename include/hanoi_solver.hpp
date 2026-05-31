#pragma once
using uint = unsigned int;

#include "array_sequence.hpp"
#include "stack.hpp"

struct hanoi_base {
    uint from;
    uint to;
    uint aux;
};

class hanoi_solver {
private:
    uint disks;
    hanoi_base base;
    array_sequence<stack<array_sequence, uint>>& towers;

    uint current_move = 0;

    void make_step(uint a, uint b);

public:
    hanoi_solver(uint disks, hanoi_base base, array_sequence<stack<array_sequence, uint>>& towers);

    bool next_move();

    uint get_current_move() const;
};