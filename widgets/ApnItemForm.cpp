#include "ApnItemForm.h"
#include "ui_ApnItemForm.h"

ApnItemForm::ApnItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApnItemForm)
{
    ui->setupUi(this);
}

ApnItemForm::~ApnItemForm()
{
    delete ui;
}

void ApnItemForm::getAPn(int &channel, std::string &apn)
{
    channel = ui->lineEdit_channel->text().toUInt();
    apn = ui->lineEdit_apn->text().toStdString();
}

void ApnItemForm::setApn(int channel, std::string apn)
{
    ui->lineEdit_channel->setText(QString("%1").arg(channel));
    ui->lineEdit_apn->setText(QString::fromStdString(apn));
}

void ApnItemForm::on_btn_del_clicked()
{
    int idex = this->property("index").toUInt();
    emit deleteSignal(idex);
}

