#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BingeWatch.h"
#include "FileHandle.h"

class BingeWatch : public QMainWindow
{
    Q_OBJECT

public:
    BingeWatch(QWidget* parent = nullptr);
    ~BingeWatch();

protected:
    //页面切换
    void SwitchPageBZhan(const QModelIndex& index);
    void SwitchPageDouYin(const QModelIndex& index);
    void SwitchPageKuaiShou(const QModelIndex& index);

    //添加按钮
    void BtnClkBZhan(bool checked = false);
private:
    Ui::BingeWatchClass ui;
    FileHandle m_fileHandle;
};
