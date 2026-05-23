#pragma once

#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWidget>

#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "sequence.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow() = default;
    ~MainWindow() = default;

private:
};