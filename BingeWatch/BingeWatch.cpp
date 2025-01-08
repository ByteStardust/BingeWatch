#include "BingeWatch.h"
#include <QStringListModel>

BingeWatch::BingeWatch(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tbBZhanView->setColumnWidth(1, 150);
}

BingeWatch::~BingeWatch()
{}
