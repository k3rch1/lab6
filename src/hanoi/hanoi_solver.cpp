#include "hanoi_solver.hpp"

hanoi_solver::hanoi_solver(uint disks, hanoi_base base, array_sequence<stack<array_sequence, uint>>& towers) : disks(disks), base(base), towers(towers) {}

void hanoi_solver::make_step(uint a, uint b) {
    if (towers[a].empty()) {
        auto disk = towers[b].top();
        towers[b].pop();
        towers[a].push(disk);
        return;
    }

    if (towers[b].empty()) {
        auto disk = towers[a].top();
        towers[a].pop();
        towers[b].push(disk);
        return;
    }

    if (towers[a].top() < towers[b].top()) {
        auto disk = towers[a].top();
        towers[a].pop();
        towers[b].push(disk);
    }
    else {
        auto disk = towers[b].top();
        towers[b].pop();
        towers[a].push(disk);
    }
}

bool hanoi_solver::next_move() {
    if (towers[base.to].size() == disks)
        return false;

    uint step_ = current_move % 3;

    if (disks % 2) {
        switch (step_) {
        case 0:
            make_step(base.from, base.to);
            break;

        case 1:
            make_step(base.from, base.aux);
            break;

        case 2:
            make_step(base.aux, base.to);
            break;
        }
    }
    else {
        switch (step_) {
        case 0:
            make_step(base.from, base.aux);
            break;

        case 1:
            make_step(base.from, base.to);
            break;

        case 2:
            make_step(base.aux, base.to);
            break;
        }
    }

    ++current_move;

    return true;
}

uint hanoi_solver::get_current_move() const {
    return current_move;
}