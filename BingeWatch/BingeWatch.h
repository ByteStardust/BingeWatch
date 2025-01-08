#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BingeWatch.h"

class BingeWatch : public QMainWindow
{
    Q_OBJECT

public:
    BingeWatch(QWidget *parent = nullptr);
    ~BingeWatch();

protected:
    //“≥√Ê«–ªª
    void SwitchPageBZhan(const QModelIndex& index);
    void SwitchPageDouYin(const QModelIndex& index);
    void SwitchPageKuaiShou(const QModelIndex& index);

    //ÃÌº”∞¥≈•
    void BtnClkBZhan(bool checked = false);
private:
    Ui::BingeWatchClass ui;
};
