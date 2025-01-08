#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BingeWatch.h"

class BingeWatch : public QMainWindow
{
    Q_OBJECT

public:
    BingeWatch(QWidget *parent = nullptr);
    ~BingeWatch();

private:
    Ui::BingeWatchClass ui;
};
