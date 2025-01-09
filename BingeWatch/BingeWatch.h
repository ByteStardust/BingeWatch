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

private slots:
    //页面切换
    void SwitchPageBZhan(const QModelIndex& index);
    void SwitchPageDouYin(const QModelIndex& index);
    void SwitchPageKuaiShou(const QModelIndex& index);

    //复选框点击改变
    void OnChkChg(int state);

    //添加按钮
    void BtnClkBZhan(bool checked = false);

    //表格数据改变
    void OnCellChg(int row, int column);
protected:
    //初始化表格信息
    void InitTable(QVector<Config>& vec,QTableWidget* TblWgt);
    void InitBZTable();
    void InitDYTable();
    void InitKSTable();

private:
    Ui::BingeWatchClass ui;
    FileHandle m_fileHandle;
};
