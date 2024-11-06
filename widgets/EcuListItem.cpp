#include "EcuListItem.h"
#include "ui_EcuListItem.h"

EcuListItem::EcuListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuListItem)
{
    ui->setupUi(this);
}

EcuListItem::~EcuListItem()
{
    delete ui;
}

void EcuListItem::setCurrentType(DiagnoseNS::Ecus &ecuType)
{
    ui->comboBox_ecu->setCurrentIndex(ecuType);
}
