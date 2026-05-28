#include "main_window.hpp"
#include <QFrame>
#include <QPushButton>

MainWindow::MainWindow() {
    auto* central = new QWidget;
    auto* root_layout = new QHBoxLayout;
    auto* buttons_widget = new QWidget;
    auto* buttons_layout = new QVBoxLayout;
    buttons_layout->setAlignment(Qt::AlignLeft);
    buttons_widget->setLayout(buttons_layout);
    buttons_widget->setFixedWidth(220);
    towers_layout = new QHBoxLayout;
    central->setLayout(root_layout);
    root_layout->addWidget(buttons_widget);
    root_layout->addLayout(towers_layout);
    setCentralWidget(central);

    timer = new QTimer(this);
    auto* speed_label = new QPushButton("speed");
    speed_label->setEnabled(false);
    buttons_layout->addWidget(speed_label);
    speed_slider = new QSlider(Qt::Horizontal);
    speed_slider->setRange(50, 1000);
    speed_slider->setValue(300);
    buttons_layout->addWidget(speed_slider);

    solve_button = new QPushButton("solve");
    buttons_layout->addWidget(solve_button);

    stop_button = new QPushButton("stop");
    stop_button->setEnabled(false);
    buttons_layout->addWidget(stop_button);

    for (size_t i = 0; i < 3; ++i) towers.append(new sequence_stack<uint>(new array_sequence<uint>));
    for (size_t i = disk_count; i > 0; --i) towers[0]->push(i);
    solver = new hanoi_solver(disk_count, towers_);

    redraw_towers();

    connect(solve_button, &QPushButton::clicked, [this]() {
            solve_button->setEnabled(false);
            stop_button->setEnabled(true);
            timer->start(speed_slider->value());
        }
    );

    connect(stop_button, &QPushButton::clicked, [this]() {
            solve_button->setEnabled(true);
            stop_button->setEnabled(false);
            timer->stop();
        }
    );

    connect(timer, &QTimer::timeout, [this]() {
            if(towers[towers_.to]->size() == disk_count) {
                timer->stop();
                towers_ = {towers_.to, towers_.from, 1};
                delete solver;
                solver = new hanoi_solver(disk_count, towers_);
                current_move = 0;
                solve_button->setEnabled(true);
                stop_button->setEnabled(false);
                return;
            }

            apply_move(solver->get_moves()[current_move++]);
        }
    );

    connect(speed_slider, &QSlider::valueChanged, [this](int value) {
            if (timer->isActive()) timer->setInterval(value);
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
        "#6a4c93",
        "#f15bb5",
        "#16502a",
        "#0aceb1",
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

        for (size_t i = 0; i < disks.size(); ++i) {
            auto disk = disks[i];
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