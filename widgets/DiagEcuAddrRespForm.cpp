#include "DiagEcuAddrRespForm.h"
#include "ui_DiagEcuAddrRespForm.h"

DiagEcuAddrRespForm::DiagEcuAddrRespForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagEcuAddrRespForm)
{
    ui->setupUi(this);
}

DiagEcuAddrRespForm::~DiagEcuAddrRespForm()
{
    delete ui;
}
