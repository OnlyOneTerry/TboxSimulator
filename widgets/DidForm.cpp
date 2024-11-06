#include "DidForm.h"
#include "ui_DidForm.h"

DidForm::DidForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DidForm)
{
    ui->setupUi(this);
}

DidForm::~DidForm()
{
    delete ui;
}
