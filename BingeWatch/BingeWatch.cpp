#include "BingeWatch.h"
#include <QStringListModel>
#include "Tool.h"
#include "MonitorThread.h"

BingeWatch::BingeWatch(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tbBZhanView->setColumnWidth(1, 150);
    //页面切换
    connect(ui.lstBZhan, &QListWidget::clicked, this, &BingeWatch::SwitchPageBZhan);
    connect(ui.lstDouYin, &QListWidget::clicked, this, &BingeWatch::SwitchPageDouYin);
    connect(ui.lstKuaiShou, &QListWidget::clicked, this, &BingeWatch::SwitchPageKuaiShou);

    //添加按钮
    connect(ui.btnBZhan, &QPushButton::clicked, this, &BingeWatch::SwitchPageKuaiShou);
}

BingeWatch::~BingeWatch()
{}

void BingeWatch::SwitchPageBZhan(const QModelIndex& index)
{
    if (index.row() == -1)
    {//选中节点的父节点等于-1，表示这是根节点
        return;
    }
    qDebug().noquote() << "点击了 " << index.data(0).toString() << "->第 " << index.row() << " 行";
    ui.stkWgtBZhan->setCurrentIndex(index.row());
}

void BingeWatch::SwitchPageDouYin(const QModelIndex& index)
{
    if (index.row() == -1)
    {//选中节点的父节点等于-1，表示这是根节点
        return;
    }
    qDebug().noquote() << "点击了 " << index.data(0).toString() << "->第 " << index.row() << " 行";
    ui.stkWgtDouYin->setCurrentIndex(index.row());
}

void BingeWatch::SwitchPageKuaiShou(const QModelIndex& index)
{
    if (index.row() == -1)
    {//选中节点的父节点等于-1，表示这是根节点
        return;
    }
    qDebug().noquote() << "点击了 " << index.data(0).toString() << "->第 " << index.row() << " 行";
    ui.stkWgtKuaiShou->setCurrentIndex(index.row());
}

void BingeWatch::BtnClkBZhan(bool checked)
{
    QString url = ui.edtBZhan->text();
    if (url.isEmpty())
    {//空内容不做处理
        return;
    }

    //加入表格显示


    //加入监控队列
}
