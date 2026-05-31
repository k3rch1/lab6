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

    disks_label = new QPushButton("disk: 5");
    disks_label->setEnabled(false);
    buttons_layout->addWidget(disks_label);
    disks_slider = new QSlider(Qt::Horizontal);
    disks_slider->setRange(1, 10);
    disks_slider->setValue(5);
    buttons_layout->addWidget(disks_slider);

    timer = new QTimer(this);
    speed_label = new QPushButton("delay: 300");
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

    for (size_t i = 0; i < 3; ++i) towers.append({});
    for (size_t i = disk_count; i > 0; --i) towers[0].push(i);
    solver = new hanoi_solver(disk_count, towers_, towers);

    redraw_towers();

    connect(solve_button, &QPushButton::clicked, [this]() {
            if(manual_mode) {
                reset_game();
                manual_mode = false;
            }
            solve_button->setEnabled(false);
            stop_button->setEnabled(true);
            disks_slider->setEnabled(false);
            timer->start(speed_slider->value());
        }
    );

    connect(stop_button, &QPushButton::clicked, [this]() {
            solve_button->setEnabled(true);
            stop_button->setEnabled(false);
            disks_slider->setEnabled(true);
            timer->stop();
        }
    );

    connect(timer, &QTimer::timeout, [this]() {
            if (!solver->next_move()) {
                timer->stop();
                towers_ = {towers_.to, towers_.from, towers_.aux};
                delete solver;
                solver = new hanoi_solver(disk_count, towers_, towers);
                solve_button->setEnabled(true);
                stop_button->setEnabled(false);
                disks_slider->setEnabled(true);
                return;
            }

            redraw_towers();
        }
    );

    connect(speed_slider, &QSlider::valueChanged, [this](int value) {
        speed_label->setText(QString("delay: %1").arg(value));    
        if (timer->isActive()) {
                timer->setInterval(value);
            }
        }
    );

    connect(disks_slider, &QSlider::valueChanged, [this](int value) {
            disk_count = value;
            disks_label->setText(QString("disk: %1").arg(value));
            reset_game();
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
        "#9b5de5",
        "#0aceb1",
    };

    for (size_t t = 0; t < 3; ++t) {
        auto* tower_widget = new QWidget;
        tower_widget->setMinimumHeight(600);
        tower_widget->setMinimumWidth(250);
        auto* tower_layout = new QVBoxLayout;
        tower_layout->setAlignment(Qt::AlignBottom);

        stack<array_sequence, uint> copy(towers[t]);
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
        auto* click_area = new QPushButton(tower_widget);
        click_area->setFlat(true);
        click_area->setStyleSheet("background-color: transparent; border: none;");
        click_area->setGeometry(tower_widget->rect());
        towers_layout->addWidget(tower_widget);

        connect(click_area, &QPushButton::clicked, [this, t]() {
                if (timer->isActive()) return;
                if (selected_tower == -1) {
                    selected_tower = t;
                    return;
                }
                if (selected_tower == t) {
                    selected_tower = -1;
                    return;
                }
                manual_move(selected_tower, t);
                manual_mode = true;
                selected_tower = -1;
            }
        );
    }
}

void MainWindow::reset_game() {
    timer->stop();
    selected_tower = -1;
    manual_mode = false;
    towers.clear();

    solve_button->setEnabled(true);
    stop_button->setEnabled(false);
    disks_slider->setEnabled(true);

    for (size_t i = 0; i < 3; ++i) towers.append({});
    for (uint i = disk_count; i > 0; --i)  towers[0].push(i);
    delete solver;
    towers_ = {0, 2, 1};
    solver = new hanoi_solver(disk_count, towers_, towers);

    redraw_towers();
}

void MainWindow::manual_move(size_t from, size_t to) {
    if (towers[from].empty()) return;
    auto disk = towers[from].top();
    if (!towers[to].empty() && towers[to].top() < disk) return;
    towers[from].pop();
    towers[to].push(disk);
    redraw_towers();
}