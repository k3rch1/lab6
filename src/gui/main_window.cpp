#include "main_window.hpp"
#include <QFrame>
#include <QPushButton>

MainWindow::MainWindow() {
    auto* central = new QWidget;
    auto* root_layout = new QVBoxLayout;
    auto* buttons_layout = new QHBoxLayout;
    buttons_layout->setAlignment(Qt::AlignLeft);
    towers_layout = new QHBoxLayout;
    central->setLayout(root_layout);
    root_layout->addLayout(buttons_layout);
    root_layout->addLayout(towers_layout);
    setCentralWidget(central);

    auto* solve_button = new QPushButton("solve");
    buttons_layout->addWidget(solve_button);

    for (size_t i = 0; i < 3; ++i) towers.append(new sequence_stack<uint>(new array_sequence<uint>));
    for (size_t i = 0; i < disk_count; ++i) towers[0]->push(i);
    solver = new hanoi_solver(disk_count);

    redraw_towers();

    connect(solve_button, &QPushButton::clicked, [this]() {
            for (size_t i = 0; i < solver->get_moves().size(); ++i) apply_move(solver->get_moves()[i]);
        }
    );
}

MainWindow::~MainWindow() {
    delete solver;
}

void MainWindow::redraw_towers() {
    while (towers_layout->count()) {
        auto* item = towers_layout->takeAt(0);

        delete item->widget();
        delete item;
    }
    
    array_sequence<QString> colors = {
        "#ff595e",
        "#ff924c",
        "#ffca3a",
        "#8ac926",
        "#52a675",
        "#1982c4",
        "#6a4c93"
    };

    for (size_t t = 0; t < 3; ++t) {
        auto* tower_widget = new QWidget;
        tower_widget->setMinimumWidth(250);
        auto* tower_layout = new QVBoxLayout;
        tower_layout->setAlignment(Qt::AlignBottom);

        sequence_stack<uint> copy(*towers[t]);
        array_sequence<uint> disks;

        while (!copy.empty()) {
            disks.append(copy.top());
            copy.pop();
        }

        for (size_t i = disks.size(); i > 0; --i) {
            auto disk = disks[i - 1];
            auto* disk_widget = new QFrame;

            disk_widget->setFixedHeight(30);
            disk_widget->setFixedWidth(40 + disk * 30);
            disk_widget->setStyleSheet(QString("background-color: %1; border-radius: 8px;").arg(colors[disk % colors.size()]));
            tower_layout->addWidget(disk_widget, 0, Qt::AlignHCenter);
        }

        tower_widget->setLayout(tower_layout);
        towers_layout->addWidget(tower_widget);
    }
}

void MainWindow::apply_move(const hanoi_move& mv) {
    auto disk = towers[mv.from]->top();
    towers[mv.from]->pop();
    towers[mv.to]->push(disk);

    redraw_towers();
}