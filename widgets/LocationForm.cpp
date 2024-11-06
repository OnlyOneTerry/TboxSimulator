#include "LocationForm.h"
#include "ui_LocationForm.h"

LocationForm::LocationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationForm)
{
    ui->setupUi(this);
    ui->pushButton_del->setVisible(false);
}

LocationForm::~LocationForm()
{
    delete ui;
}

bool LocationForm::getLocation(LocationNS::Location &location)
{
    location.set_altitude(ui->lineEdit_altitude->text().toUInt());
    location.set_angle(ui->lineEdit_angle->text().toUInt());
    location.set_hemisphere(ui->lineEdit_hemisphere->text().toUInt());
    location.set_longitude(ui->lineEdit_longtuitude->text().toUInt());
    location.set_satnumber(ui->lineEdit_satNumber->text().toUInt());
    location.set_speed(ui->lineEdit_speed->text().toUInt());
    location.set_valid(ui->checkBox_valid->isChecked());
    location.set_latitude(ui->lineEdit_latuitude->text().toUInt());
    location.set_timestamp(ui->lineEdit_timestamp->text().toUInt());
     return true;
}

void LocationForm::setData(LocationNS::Location &location)
{
    ui->checkBox_valid->setChecked(location.valid());
    ui->lineEdit_altitude->setText(QString("%1").arg(location.altitude()));
    ui->lineEdit_angle->setText(QString("%1").arg(location.angle()));
    ui->lineEdit_hemisphere->setText(QString("%1").arg(location.hemisphere()));
    ui->lineEdit_latuitude->setText(QString("%1").arg(location.latitude()));
    ui->lineEdit_longtuitude->setText(QString("%1").arg(location.longitude()));
    ui->lineEdit_satNumber->setText(QString("%1").arg(location.satnumber()));
    ui->lineEdit_speed->setText(QString("%1").arg(location.speed()));
    ui->lineEdit_timestamp->setText(QString("%1").arg(location.timestamp()));
    ui->lineEdit_latuitude->setText(QString("%1").arg(location.latitude()));
}

void LocationForm::setData(std::string &location)
{
   LocationNS::Location loc;
   loc.ParseFromString(location);
   setData(loc);
}

void LocationForm::showDelBtn(bool visible)
{
    ui->pushButton_del->setVisible(visible);
}

void LocationForm::on_pushButton_del_clicked()
{
    int idex = this->property("index").toUInt();
    emit deleteSignal(idex);
}

