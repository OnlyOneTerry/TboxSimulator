#include "EcuVersionForm.h"
#include "ui_EcuVersionForm.h"
#include "protoBuf/diagnose.pb.h"

EcuVersionForm::EcuVersionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuVersionForm)
{
    ui->setupUi(this);
}

EcuVersionForm::~EcuVersionForm()
{
    delete ui;
}

void EcuVersionForm::getEcuVersion(ControlNS::ECUVersion &ecuVersion)
{
    int idx = ui->comboBox_ecu->currentIndex();
    DiagnoseNS::Ecus ecu = static_cast<DiagnoseNS::Ecus>(idx);
    ecuVersion.set_ecu(ecu);
    ecuVersion.set_firmware(ui->lineEdit_firmware->text().toStdString());
    ecuVersion.set_software(ui->lineEdit_software->text().toStdString());
    ecuVersion.set_manufacturer(ui->lineEdit_manufacturer->text().toStdString());
    ecuVersion.set_protocol(ui->lineEdit_protocol->text().toStdString());
}

void EcuVersionForm::setData(ControlNS::ECUVersion &ecuVersion)
{
    ui->comboBox_ecu->setCurrentIndex(ecuVersion.ecu());
    ui->lineEdit_firmware->setText(QString::fromStdString(ecuVersion.firmware()));
    ui->lineEdit_software->setText(QString::fromStdString(ecuVersion.software()));
    ui->lineEdit_manufacturer->setText(QString::fromStdString(ecuVersion.manufacturer()));
    ui->lineEdit_protocol->setText(QString::fromStdString(ecuVersion.protocol()));
}

void EcuVersionForm::on_pushButton_del_clicked()
{
    int idex = this->property("index").toUInt();
    emit deleteSignal(idex);
}

