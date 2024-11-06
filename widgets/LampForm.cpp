#include "LampForm.h"
#include "ui_LampForm.h"

LampForm::LampForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LampForm)
{
    ui->setupUi(this);
    initUI();
}

LampForm::~LampForm()
{
    delete ui;
}

void LampForm::initUI()
{
   ui->comboBox_lamp_status->addItem("OFF",0);
   ui->comboBox_lamp_status->addItem("ON",1);
   ui->comboBox_lamp_status->addItem("CHARGING",2);

   ui->comboBox_lamp_type->addItem("LOW_BEAM_LIGHT",0);
   ui->comboBox_lamp_type->addItem("HIGH_BEAM_LIGHT",1);
   ui->comboBox_lamp_type->addItem("DAY_TIME_RUNNING_LIGHT",2);
   ui->comboBox_lamp_type->addItem("BACK_POSITION_LIGHT",3);
   ui->comboBox_lamp_type->addItem("LICENSE_PLATE_LIGHT",4);
}

void LampForm::getLampInfo(EventNS::LampInfo &lampInfo)
{
    lampInfo.set_lampstatus((EventNS::LampStatus)ui->comboBox_lamp_status->currentData().toUInt());
    lampInfo.set_lamptype((EventNS::LampType)ui->comboBox_lamp_type->currentData().toUInt());
}

void LampForm::setData(EventNS::LampInfo &lampInfo)
{
   ui->comboBox_lamp_status->setCurrentIndex(lampInfo.lampstatus());
   ui->comboBox_lamp_type->setCurrentIndex(lampInfo.lamptype());
}

void LampForm::on_pushButton_del_clicked()
{
    int index = this->property("index").toInt();
    emit deleteSignal(index);
}

