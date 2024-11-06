#include "StatusReportWidget.h"
#include "ui_StatusReportWidget.h"
#include "HmiForm.h"
#include "BmsSKInfoForm.h"
#include "TboxSkInfoForm.h"
#include "BmsSKInfoListForm.h"
#include "CommonDef.h"
#include <iostream>
#include <fstream>

StatusReportWidget::StatusReportWidget(QWidget *parent) :
    ReportParent(TBOX::REPORT_WIDGET::REPORT_STATUS,parent),
    ui(new Ui::StatusReportWidget)
{
    ui->setupUi(this);
    InitUI();
    initData();
}

StatusReportWidget::~StatusReportWidget()
{
    delete ui;
}

void StatusReportWidget::InitUI()
{
    hmiInfo_form_=new HmiForm();
    tbSkInfo_form_=new TboxSkInfoForm();
    bmsInfo_form_ = new BmsSKInfoForm(false);
    bmsSkInfo_list_form_ = new BmsSKInfoListForm();

    ui->verticalLayout_hmi->addWidget(hmiInfo_form_);
    ui->verticalLayout_tbx->addWidget(tbSkInfo_form_);
    ui->verticalLayout_bms->addWidget(bmsInfo_form_);
    ui->verticalLayout_bmsSKinfo->addWidget(bmsSkInfo_list_form_);
}

void StatusReportWidget::initData()
{
    std::ifstream readFile("./configure/status.pb",std::ios::in|std::ios::binary);
    if(!readFile)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }
    //unSerialize
    StatusNS::Status status;

    status.ParseFromIstream(&readFile);
    StatusNS::HmiInfo hmiInfo = status.hmiinfo();
    hmiInfo_form_->initData(hmiInfo);

    //StatusNS::BmsInfo bmsInfo = status.bmsinfo();
    //bool isVersion_2 = bmsInfo_form_->initData(bmsInfo);
    bool isVersion_2 = status.has_tpmsinfo();
    if(isVersion_2)
    {
        ui->radioButton_2->setChecked(true);
        ui->radioButton_1->setChecked(false);
        on_radioButton_2_clicked();
        StatusNS::BmsInfo bmsInfo = status.bmsinfo();
        bmsInfo_form_->initData(bmsInfo);
        StatusNS::TboxInfo tbxInfo = status.tboxinfo();
        tbSkInfo_form_->initData(tbxInfo);
        StatusNS::TpmsInfo tpmsInfo = status.tpmsinfo();
        ui->lineEdit_frontPressure->setText(QString("%1").arg(tpmsInfo.fronttirepressure()));
        ui->lineEdit_rearPressure->setText(QString("%1").arg(tpmsInfo.reartirepressure()));
        ui->lineEdit_frontTemp->setText(QString("%1").arg(tpmsInfo.fronttiertemp()));
        ui->lineEdit_rearTemp->setText(QString("%1").arg(tpmsInfo.reartiretemp()));
    }
    else
    {
        ui->radioButton_2->setChecked(false);
        ui->radioButton_1->setChecked(true);
        bmsSkInfo_list_form_->initData(status);
        on_radioButton_1_clicked();
        StatusNS::TboxSKInfo tbxInfo = status.tboxskinfo();
        tbSkInfo_form_->initData(tbxInfo);
    }

}

bool StatusReportWidget::getStatus(StatusNS::Status &status)
{
    status.CopyFrom(data_status_);
    return true;
}

void StatusReportWidget::on_pushButton_apply_clicked()
{
    StatusNS::HmiInfo* hmiInfo =  data_status_.mutable_hmiinfo();
    hmiInfo_form_->getHmiInfo(*hmiInfo);
    StatusNS::BmsInfo* bmsSkInfo = data_status_.mutable_bmsinfo();
    bmsInfo_form_->getInfo(*bmsSkInfo);
    bmsSkInfo_list_form_->getInfo(data_status_);
    if(ui->radioButton_1->isChecked())
    {

        StatusNS::TboxSKInfo* tbxSkInfo = data_status_.mutable_tboxskinfo();
        tbSkInfo_form_->getTboxSkInfo(*tbxSkInfo);
    }
    else if(ui->radioButton_2->isChecked())
    {
        StatusNS::TboxInfo* tbxInfo = data_status_.mutable_tboxinfo();
        tbSkInfo_form_->getTboxInfo(*tbxInfo);

        StatusNS::TpmsInfo* tpmsInfo = data_status_.mutable_tpmsinfo();
        tpmsInfo->set_fronttiertemp(ui->lineEdit_frontPressure->text().toUInt());
        tpmsInfo->set_reartiretemp(ui->lineEdit_rearTemp->text().toUInt());
        tpmsInfo->set_fronttirepressure(ui->lineEdit_frontPressure->text().toUInt());
        tpmsInfo->set_reartirepressure(ui->lineEdit_rearPressure->text().toUInt());
        tpmsInfo->set_status(ui->lineEdit_status->text().toUInt());

    }

    //emit updateStatusSignal();
    std::string serializeStr = data_status_.SerializeAsString();
    saveAsString("./configure/status.pb",serializeStr);
}


void StatusReportWidget::on_radioButton_1_clicked()
{
    ui->groupBox_bmsSkInfo->setVisible(true);
    ui->groupBox_bmsInfo->setVisible(false);
    ui->groupBox_tboxInfo->setTitle("TboxSKInfo");
    ui->groupBox_tirepressure->setVisible(false);
}


void StatusReportWidget::on_radioButton_2_clicked()
{
    ui->groupBox_bmsSkInfo->setVisible(false);
    ui->groupBox_bmsInfo->setVisible(true);
    ui->groupBox_tboxInfo->setTitle("TboxInfo");
    ui->groupBox_tirepressure->setVisible(true);
}

