#pragma once
using uint = unsigned int;

#include <QMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include <QSlider>
#include <QPushButton>

#include "array_sequence.hpp"
#include "sequence_stack.hpp"
#include "hanoi_solver.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    array_sequence<sequence_stack<uint>*> towers;

    hanoi_solver* solver;

    size_t current_move = 0;

    uint disk_count = 10;

    QHBoxLayout* towers_layout;

    hanoi_base towers_ = {0, 2, 1};

    QTimer* timer;
    QSlider* speed_slider;

    QPushButton* solve_button;
    QPushButton* stop_button;
public:
    MainWindow();

    ~MainWindow() override;

    void redraw_towers();

    void apply_move(const hanoi_move& mv);
};