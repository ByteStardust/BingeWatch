#include "BingeWatch.h"
#include <QStringListModel>

BingeWatch::BingeWatch(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QStringListModel model;
    QStringList data = { "查看", "设置" };
    model.setStringList(data);
    ui.lstBZhan->setModel(&model);
    ui.lstBZhan->show();
}

BingeWatch::~BingeWatch()
{}
