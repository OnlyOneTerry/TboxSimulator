#include "PointForm.h"
#include "ui_PointForm.h"

PointForm::PointForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointForm)
{
    ui->setupUi(this);
}

PointForm::~PointForm()
{
    delete ui;
}

void PointForm::setPoint(int latitude, int longitude, int hemisphere)
{
    ui->label_latitude->setText(QString("%1").arg(latitude));
    ui->label_longitude->setText(QString("%1").arg(longitude));
    ui->label_hemisphere->setText(QString("%1").arg(hemisphere));
}
