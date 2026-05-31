#pragma once
using uint = unsigned int;

#include <QMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include <QSlider>
#include <QPushButton>

#include "array_sequence.hpp"
#include "stack.hpp"
#include "hanoi_solver.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    array_sequence<stack<array_sequence, uint>> towers;

    hanoi_solver* solver;
    uint disk_count = 5;

    QHBoxLayout* towers_layout;

    hanoi_base towers_ = {0, 2, 1};

    QTimer* timer;
    QSlider* speed_slider;
    QSlider* disks_slider;

    QPushButton* solve_button;
    QPushButton* stop_button;
    QPushButton* disks_label;
    QPushButton* speed_label;

    bool manual_mode = false;
    int selected_tower = -1;
public:
    MainWindow();

    ~MainWindow() override;

    void redraw_towers();

    void reset_game();

    void manual_move(size_t from, size_t to);
};