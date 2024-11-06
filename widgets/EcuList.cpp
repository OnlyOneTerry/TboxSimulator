#include "EcuList.h"
#include "ui_EcuList.h"
#include "EcuListItem.h"

EcuList::EcuList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuList)
{
    ui->setupUi(this);
}

EcuList::~EcuList()
{
    delete ui;
}

void EcuList::addEcus(DiagnoseNS::Ecus ecu)
{
    EcuListItem * ecuItem = new EcuListItem ;
    ecuItem->setCurrentType(ecu);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(100,36));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,ecuItem);
}


