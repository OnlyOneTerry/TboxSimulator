#include "TpmsInfoForm.h"
#include "ui_TpmsInfoForm.h"

TpmsInfoForm::TpmsInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TpmsInfoForm)
{
    ui->setupUi(this);
}

TpmsInfoForm::~TpmsInfoForm()
{
    delete ui;
}
