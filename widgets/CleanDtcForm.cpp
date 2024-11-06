#include "CleanDtcForm.h"
#include "ui_CleanDtcForm.h"

CleanDtcForm::CleanDtcForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CleanDtcForm)
{
    ui->setupUi(this);
}

CleanDtcForm::~CleanDtcForm()
{
    delete ui;
}
