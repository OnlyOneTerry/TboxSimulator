#include "BmsSKInfoForm.h"
#include "ui_BmsSKInfoForm.h"

BmsSKInfoForm::BmsSKInfoForm(bool delBtnVisible,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BmsSKInfoForm)
{
    ui->setupUi(this);
    ui->pushButton_del->setVisible(delBtnVisible);
}

BmsSKInfoForm::~BmsSKInfoForm()
{
    delete ui;
}

bool BmsSKInfoForm::getInfo(StatusNS::BmsInfo &bmsInfo)
{
    bmsInfo.set_bmsvoltage(ui->lineEdit_bmsVoltage->text().toUInt());
    bmsInfo.set_bmselectric(ui->lineEdit_bmsEletric->text().toUInt());
    bmsInfo.set_bmssoc(ui->lineEdit_soc->text().toUInt());
    bmsInfo.set_bmstemp(ui->lineEdit_temp->text().toUInt());
    return true;
}

bool BmsSKInfoForm::getInfo(StatusNS::BmsSKInfo &bmsSKInfo)
{
    bmsSKInfo.set_bmsvoltage(ui->lineEdit_bmsVoltage->text().toUInt());
    bmsSKInfo.set_bmselectric(ui->lineEdit_bmsEletric->text().toUInt());
    bmsSKInfo.set_bmssoc(ui->lineEdit_soc->text().toUInt());
    bmsSKInfo.set_bmstemp(ui->lineEdit_temp->text().toUInt());
    return true;
}

bool BmsSKInfoForm::initData(StatusNS::BmsInfo& bmsInfo)
{
     ui->lineEdit_bmsVoltage->setText(QString("%1").arg(bmsInfo.bmsvoltage()));
     ui->lineEdit_bmsEletric->setText(QString("%1").arg(bmsInfo.bmselectric()));
     ui->lineEdit_soc->setText(QString("%1").arg(bmsInfo.bmssoc()));
     ui->lineEdit_temp->setText(QString("%1").arg(bmsInfo.bmstemp()));

     if(ui->lineEdit_bmsEletric->text()=="0"&&ui->lineEdit_bmsVoltage->text()=="0"&&ui->lineEdit_soc->text()=="0"&&ui->lineEdit_temp->text()=="0")
     {
         return false;
     }
     else
     {
         return true;
     }
}

bool BmsSKInfoForm::initData(StatusNS::BmsSKInfo &bmsSkInfo)
{
     ui->lineEdit_bmsVoltage->setText(QString("%1").arg(bmsSkInfo.bmsvoltage()));
     ui->lineEdit_bmsEletric->setText(QString("%1").arg(bmsSkInfo.bmselectric()));
     ui->lineEdit_soc->setText(QString("%1").arg(bmsSkInfo.bmssoc()));
     ui->lineEdit_temp->setText(QString("%1").arg(bmsSkInfo.bmstemp()));
}


void BmsSKInfoForm::on_pushButton_del_clicked()
{
    int idex = this->property("index").toUInt();
    emit deleteSignal(idex);
}

