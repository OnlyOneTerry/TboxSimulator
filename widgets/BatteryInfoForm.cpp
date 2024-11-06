#include "BatteryInfoForm.h"
#include "ui_BatteryInfoForm.h"

BatteryInfoForm::BatteryInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BatteryInfoForm)
{
    ui->setupUi(this);
}

BatteryInfoForm::~BatteryInfoForm()
{
    delete ui;
}

void BatteryInfoForm::getBatteryInfo(EventNS::BatteryInfo &batteryInfo)
{
    batteryInfo.set_charging(ui->checkBox_charging->isChecked());
    batteryInfo.set_quantity(ui->lineEdit_batQuantity->text().toUInt());
    batteryInfo.set_range(ui->lineEdit_batRange->text().toUInt());
    batteryInfo.set_cycle(ui->lineEdit_batCycle->text().toUInt());
    batteryInfo.set_remaining(ui->lineEdit_batRemain->text().toUInt());
    batteryInfo.set_temp(ui->lineEdit_batTemp->text().toUInt());
    batteryInfo.set_bmsid(ui->lineEdit_bmsId->text().toUInt());
}

void BatteryInfoForm::setData(EventNS::BatteryInfo &batteryInfo)
{
    ui->lineEdit_batCycle->setText(QString("%1").arg(batteryInfo.cycle()));
    ui->lineEdit_batQuantity->setText(QString("%1").arg(batteryInfo.quantity()));
    ui->lineEdit_batRange->setText(QString("%1").arg(batteryInfo.range()));
    ui->lineEdit_batRemain->setText(QString("%1").arg(batteryInfo.remaining()));
    ui->lineEdit_batTemp->setText(QString("%1").arg(batteryInfo.temp()));
    ui->lineEdit_bmsId->setText(QString("%1").arg(batteryInfo.bmsid()));
    ui->checkBox_charging->setChecked(batteryInfo.charging());
}

void BatteryInfoForm::on_pushButton_del_clicked()
{
    int index =  this->property("index").toInt();
    emit  deleteSignal(index);
}

