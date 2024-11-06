#include "DiagnoseCodeItemForm.h"
#include "ui_DiagnoseCodeItemForm.h"

DiagnoseCodeItemForm::DiagnoseCodeItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagnoseCodeItemForm)
{
    ui->setupUi(this);
}

DiagnoseCodeItemForm::~DiagnoseCodeItemForm()
{
    delete ui;
}


void DiagnoseCodeItemForm::on_btn_del_clicked()
{
    int idx = property("index").toUInt();
    emit deleteSignal(idx);
}

