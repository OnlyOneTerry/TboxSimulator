#include "HmiForm.h"
#include "ui_HmiForm.h"

HmiForm::HmiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HmiForm)
{
    ui->setupUi(this);
}

HmiForm::~HmiForm()
{
    delete ui;
}

bool HmiForm::getHmiInfo(StatusNS::HmiInfo &hmiInfo)
{

    hmiInfo_.set_endurancemileage(ui->lineEdit_eduMilelage->text().toUInt());
    hmiInfo_.set_odometro(ui->lineEdit_odoMetro->text().toUInt());
    hmiInfo_.set_revspeed(ui->lineEdit_revSpeed->text().toUInt());
    hmiInfo_.set_speed(ui->lineEdit_speed->text().toUInt());
    int gearPosition = ui->comboBox_gear->currentIndex();
    hmiInfo_.set_gearposition((StatusNS::GearPosition)gearPosition);
    hmiInfo.CopyFrom(hmiInfo_);
    return true;
}

void HmiForm::initData(StatusNS::HmiInfo &hmiInfo)
{
    ui->lineEdit_eduMilelage->setText(QString("%1").arg(hmiInfo.endurancemileage()));
    ui->lineEdit_odoMetro->setText(QString("%1").arg(hmiInfo.odometro()));
    ui->lineEdit_revSpeed->setText(QString("%1").arg(hmiInfo.revspeed()));
    ui->lineEdit_speed->setText(QString("%1").arg(hmiInfo.speed()));
    ui->comboBox_gear->setCurrentIndex(hmiInfo.gearposition());
}
