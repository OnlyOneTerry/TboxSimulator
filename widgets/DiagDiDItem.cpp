#include "DiagDiDItem.h"
#include "ui_DiagDiDItem.h"

DiagDiDItem::DiagDiDItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagDiDItem)
{
    ui->setupUi(this);
}

DiagDiDItem::~DiagDiDItem()
{
    delete ui;
}

void DiagDiDItem::setDidAndDidValue(DiagnoseNS::DiagDID &diagDid)
{
  ui->lineEdit_did->setText(QString("%1").arg(diagDid.did()));
  ui->lineEdit_didvalue->setText(QString::fromStdString(diagDid.didvalue()));
}
