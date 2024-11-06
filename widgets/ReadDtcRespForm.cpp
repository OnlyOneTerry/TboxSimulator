#include "ReadDtcRespForm.h"
#include "ui_ReadDtcRespForm.h"
#include "EcuDtcItem.h"

ReadDtcRespForm::ReadDtcRespForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadDtcRespForm)
{
    ui->setupUi(this);
}

ReadDtcRespForm::~ReadDtcRespForm()
{
    delete ui;
}

void ReadDtcRespForm::setEcuDtcData(DiagnoseNS::ReadDTC &readDtc)
{
    int size  = readDtc.ecu_size();
    for(int i = 0;i<size;i++)
    {
        EcuDtcItem* ecuDtcItem = new EcuDtcItem ;
        DiagnoseNS::Ecus ecu = readDtc.ecu(i);
        ecuDtcItem->setEcuType(ecu);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(80,250));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,ecuDtcItem);
    }
}
