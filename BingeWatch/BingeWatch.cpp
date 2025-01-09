#include "BingeWatch.h"
#include <QStringListModel>
#include <QMessageBox>


BingeWatch::BingeWatch(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tbBZhanView->setColumnWidth(1, 150);
    //页面切换
    connect(ui.lstBZhan, &QListWidget::clicked, this, &BingeWatch::SwitchPageBZhan);
    connect(ui.lstDouYin, &QListWidget::clicked, this, &BingeWatch::SwitchPageDouYin);
    connect(ui.lstKuaiShou, &QListWidget::clicked, this, &BingeWatch::SwitchPageKuaiShou);

    //复选框
    connect(ui.chkAutoDL, &QCheckBox::stateChanged, this, &BingeWatch::OnChkChg);

    //添加按钮
    connect(ui.btnBZhan, &QPushButton::clicked, this, &BingeWatch::BtnClkBZhan);

    //数据变化，自动保存到文件
    connect(ui.tbBZhanSetting, &QTableWidget::cellChanged, this, &BingeWatch::OnCellChg);
    connect(ui.tbBZhanView, &QTableWidget::cellChanged, this, &BingeWatch::OnCellChg);

    //表格样式初始化
    ui.tbBZhanSetting->setColumnWidth(0, 150);

    //表格数据初始化
    InitBZTable();
    InitDYTable();
    InitKSTable();
}

BingeWatch::~BingeWatch()
{}

//B站左侧菜单切换页面
void BingeWatch::SwitchPageBZhan(const QModelIndex& index)
{
    if (index.row() == -1)
    {//选中节点的父节点等于-1，表示这是根节点
        return;
    }
    qDebug().noquote() << "点击了 " << index.data(0).toString() << "->第 " << index.row() << " 行";
    ui.stkWgtBZhan->setCurrentIndex(index.row());
}

//抖音左侧菜单切换页面
void BingeWatch::SwitchPageDouYin(const QModelIndex& index)
{
    if (index.row() == -1)
    {//选中节点的父节点等于-1，表示这是根节点
        return;
    }
    qDebug().noquote() << "点击了 " << index.data(0).toString() << "->第 " << index.row() << " 行";
    ui.stkWgtDouYin->setCurrentIndex(index.row());
}

//快手左侧菜单切换页面
void BingeWatch::SwitchPageKuaiShou(const QModelIndex& index)
{
    if (index.row() == -1)
    {//选中节点的父节点等于-1，表示这是根节点
        return;
    }
    qDebug().noquote() << "点击了 " << index.data(0).toString() << "->第 " << index.row() << " 行";
    ui.stkWgtKuaiShou->setCurrentIndex(index.row());
}

//复选框改变
void BingeWatch::OnChkChg(int state)
{
    QMessageBox::information(NULL, "提示", "自动下载功能未实现");
}

//B站 添加按钮
void BingeWatch::BtnClkBZhan(bool checked)
{
    QString url = ui.edtBZhan->text();
    if (url.isEmpty())
    {//空内容不做处理
        return;
    }

    //加入监控队列
    auto thread = m_fileHandle.GetThread("B站");
    thread->SetUrl(url, ui.tbBZhanSetting);
    ui.edtBZhan->clear();

}

//监控表格数据发生变化 自动保存到文件
void BingeWatch::OnCellChg(int row, int column)
{
    m_fileHandle.SaveConfig();
}

//将数据添加到表格
void BingeWatch::InitTable(QVector<Config>& vec, QTableWidget* TblWgt)
{
    for (auto cfg : vec)
    {
        int nIdx = TblWgt->rowCount();
        TblWgt->insertRow(nIdx);
        TblWgt->setItem(nIdx, 0, new QTableWidgetItem(cfg.szID));
        TblWgt->setItem(nIdx, 1, new QTableWidgetItem(QString::number(cfg.nNumber)));
        TblWgt->setItem(nIdx, 2, new QTableWidgetItem(cfg.szUserName));
    }
}

//初始化 B站 监控表
void BingeWatch::InitBZTable()
{
    auto thread = m_fileHandle.GetThread("B站");
    InitTable(thread->GetVecCfg(), ui.tbBZhanSetting);
}

//初始化 B站 监控表
void BingeWatch::InitDYTable()
{
    auto thread = m_fileHandle.GetThread("抖音");
    InitTable(thread->GetVecCfg(), ui.tbBZhanSetting);
}

//初始化 B站 监控表
void BingeWatch::InitKSTable()
{
    auto thread = m_fileHandle.GetThread("快手");
    InitTable(thread->GetVecCfg(), ui.tbBZhanSetting);
}
