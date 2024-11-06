#include "EcuAddrItem.h"
#include "ui_EcuAddrItem.h"

EcuAddrItem::EcuAddrItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuAddrItem)
{
    ui->setupUi(this);
}

EcuAddrItem::~EcuAddrItem()
{
    delete ui;
}

void EcuAddrItem::setEcuAddrData(int ecuAddtx, int ecuAddrRx)
{
   ui->lineEdit_ecuAddrRx->setText(QString("%1").arg(ecuAddrRx));
   ui->lineEdit_ecuAddrTx->setText(QString("%1").arg(ecuAddtx));
}
