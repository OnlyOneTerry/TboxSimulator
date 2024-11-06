#include "TBoxWidget.h"
#include "./ui_TBoxWidget.h"
#include "StatusReportWidget.h"
#include "EventReportWidget.h"
#include "FaultReportWidget.h"
#include "AlertReportWidget.h"
#include "RemoteControlWid.h"
#include "DiagnoseForm.h"
#include "ControlConfigForm.h"
#include "PathPlanForm.h"

#include <QDebug>

TBoxWidget::TBoxWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TBoxWidget)
{
    ui->setupUi(this);
    initUI();

    event_wid_->setVisible(false);
    fault_wid_->setVisible(false);
    alert_wid_->setVisible(false);

}

TBoxWidget::~TBoxWidget()
{
    delete ui;
}

void TBoxWidget::updateCallbackText(QString info)
{
    ui->textEdit_callback->clear();
    ui->textEdit_callback->setText(info);
}

void TBoxWidget::initUI()
{
    status_wid_=new StatusReportWidget;
    event_wid_=new EventReportWidget;
    fault_wid_=new FaultReportWidget;
    alert_wid_=new AlertReportWidget;
    remote_contrl_wid_ = new RemoteControlWid;
    diagnose_wid_ = new DiagnoseForm;
    path_plan_form_ = new PathPlanForm;
    connect(remote_contrl_wid_,SIGNAL(responseToControl(QString)),this,SIGNAL(responseToControl(QString)));

    connect(status_wid_,SIGNAL(updateStatusSignal()),this,SIGNAL(updateStatusSignal()));
    connect(event_wid_,SIGNAL(updateEventSignal()),this,SIGNAL(updateEventSignal()));
    connect(fault_wid_,SIGNAL(updateFaultSignal()),this,SIGNAL(updateFaultSignal()));
    connect(alert_wid_,SIGNAL(updateAlertSignal()),this,SIGNAL(updateAlertSignal()));

    ui->verticalLayout_report->addWidget(status_wid_);
    ui->verticalLayout_report->addWidget(event_wid_);
    ui->verticalLayout_report->addWidget(fault_wid_);
    ui->verticalLayout_report->addWidget(alert_wid_);
    ui->verticalLayout_path_plan->addWidget(path_plan_form_);


    report_wids_.push_back(status_wid_);
    report_wids_.push_back(event_wid_);
    report_wids_.push_back(fault_wid_);
    report_wids_.push_back(alert_wid_);

    btn_type_map_.insert(ui->btn_alert_report,TBOX::REPORT_WIDGET::REPORT_ALERT);
    btn_type_map_.insert(ui->btn_event_report,TBOX::REPORT_WIDGET::REPORT_EVENT);
    btn_type_map_.insert(ui->btn_fault_report,TBOX::REPORT_WIDGET::REPORT_FAULT);
    btn_type_map_.insert(ui->btn_status_report,TBOX::REPORT_WIDGET::REPORT_STATUS);

    showReportWid(TBOX::REPORT_WIDGET::REPORT_STATUS);
    updateReportStatus(TBOX::REPORT_WIDGET::REPORT_STATUS);

    ui->verticalLayout_control->addWidget(remote_contrl_wid_);

    ui->verticalLayout_diagnose->addWidget(diagnose_wid_);

    control_config_wid_ = new ControlConfigForm;

    ui->verticalLayout_resp_config->addWidget(control_config_wid_);
}

void TBoxWidget::showReportWid(TBOX::REPORT_WIDGET reportType)
{
    foreach(auto wid , report_wids_)
    {
        TBOX::REPORT_WIDGET type =wid->getReportType();
        wid->setVisible(type == reportType);
    }
}

bool TBoxWidget::getStatus(StatusNS::Status &status)
{
    if(status_wid_)
    {
        status_wid_->getStatus(status);
        return true;
    }
    return false;
}

void TBoxWidget::updateReportStatus(TBOX::REPORT_WIDGET type)
{
    QMap<QPushButton*,TBOX::REPORT_WIDGET>::iterator iter = btn_type_map_.begin();

    for(;iter!=btn_type_map_.end();iter++)
    {
        if(iter.value()==type)
        {
            iter.key()->setStyleSheet("QPushButton{background-color:#4caf50;color:white;}");
        }
        else
        {
            iter.key()->setStyleSheet("QPushButton{background-color:white;color:black;}");
        }
    }
}

bool TBoxWidget::getFault(FaultNS::Fault &fault)
{
    if(fault_wid_)
    {
        fault_wid_->getFault(fault);
        return true;
    }
    return false;
}

bool TBoxWidget::getAlert(AlertNS::Alert &alert)
{
    if(alert_wid_)
    {
        alert_wid_->getAlert(alert);
        return true;
    }

    return false;
}

bool TBoxWidget::getEvent(EventNS::Event &event)
{
    if(event_wid_)
    {
        event_wid_->getEvent(event);
        return true;
    }

    return false;
}

void TBoxWidget::showRecieveControlInfo(ControlNS::Control &ctrl)
{
    remote_contrl_wid_->setControl(ctrl);
}

void TBoxWidget::showRecieveDiagnoseInfo(DiagnoseNS::Diagnose &diagnose)
{
    diagnose_wid_->setDiagnoseData(diagnose);
}

std::vector<std::string> TBoxWidget::getMarks()
{
    if(path_plan_form_)
    {
        return path_plan_form_->getMarks();
    }
    return std::vector<std::string>();
}

void TBoxWidget::on_pushButton_clicked()
{
    emit clickedsig();
}

void TBoxWidget::on_btn_subscribe_clicked()
{
    emit subscribeTopicSig(ui->lineEdit_topic->text());
}

void TBoxWidget::on_btn_alert_report_clicked()
{
    showReportWid(TBOX::REPORT_WIDGET::REPORT_ALERT);
    report_type_ = TBOX::REPORT_WIDGET::REPORT_ALERT;
    updateReportStatus(TBOX::REPORT_WIDGET::REPORT_ALERT);
}

void TBoxWidget::on_btn_event_report_clicked()
{
    showReportWid(TBOX::REPORT_WIDGET::REPORT_EVENT);
    report_type_ = TBOX::REPORT_WIDGET::REPORT_EVENT;
    updateReportStatus(TBOX::REPORT_WIDGET::REPORT_EVENT);
}

void TBoxWidget::on_btn_status_report_clicked()
{
    showReportWid(TBOX::REPORT_WIDGET::REPORT_STATUS);
    report_type_ = TBOX::REPORT_WIDGET::REPORT_STATUS;
    updateReportStatus(TBOX::REPORT_WIDGET::REPORT_STATUS);
}

void TBoxWidget::on_btn_fault_report_clicked()
{
    showReportWid(TBOX::REPORT_WIDGET::REPORT_FAULT);
    report_type_ = TBOX::REPORT_WIDGET::REPORT_FAULT;
    updateReportStatus(TBOX::REPORT_WIDGET::REPORT_FAULT);
}

