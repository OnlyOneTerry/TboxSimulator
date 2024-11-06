#ifndef TBOXWIDGET_H
#define TBOXWIDGET_H

#include <QWidget>
#include "CommonDef.h"
#include "protoBuf/status.pb.h"
#include "protoBuf/fault.pb.h"
#include "protoBuf/alert.pb.h"
#include "protoBuf/event.pb.h"
#include "protoBuf/control.pb.h"
#include "protoBuf/diagnose.pb.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class TBoxWidget; }
QT_END_NAMESPACE

class StatusReportWidget;
class EventReportWidget;
class FaultReportWidget;
class AlertReportWidget;
class ReportParent;
class RemoteControlWid;
class DiagnoseForm;
class ControlConfigForm;
class PathPlanForm;

class TBoxWidget : public QWidget
{
    Q_OBJECT

public:
    TBoxWidget(QWidget *parent = nullptr);
    ~TBoxWidget();
    void updateCallbackText(QString info);
    void initUI();
    void showReportWid(TBOX::REPORT_WIDGET reportType);
    bool getStatus(StatusNS::Status& status);
    void updateReportStatus(TBOX::REPORT_WIDGET type);
    bool getFault(FaultNS::Fault& fault);
    bool getAlert(AlertNS::Alert& alert);
    bool getEvent(EventNS::Event& event);
    void showRecieveControlInfo(ControlNS::Control& ctrl);
    void showRecieveDiagnoseInfo(DiagnoseNS::Diagnose& diagnose);
    std::vector<std::string> getMarks();
signals:
    void clickedsig();

    void subscribeTopicSig(QString topic);
    void updateStatusSignal();
    void updateAlertSignal();
    void updateEventSignal();
    void updateFaultSignal();
    void responseToControl(QString serialCtrl);
    void updateMarksSignal();
public slots:
    void on_pushButton_clicked();

    void on_btn_subscribe_clicked();

private slots:
    void on_btn_alert_report_clicked();

    void on_btn_event_report_clicked();

    void on_btn_status_report_clicked();

    void on_btn_fault_report_clicked();

private:
    Ui::TBoxWidget *ui;
    StatusReportWidget* status_wid_=nullptr;
    EventReportWidget* event_wid_=nullptr;
    FaultReportWidget* fault_wid_=nullptr;
    AlertReportWidget* alert_wid_=nullptr;
    DiagnoseForm*  diagnose_wid_ = nullptr;
    PathPlanForm* path_plan_form_ = nullptr;
    QVector<ReportParent*> report_wids_;
    TBOX::REPORT_WIDGET report_type_ = TBOX::REPORT_WIDGET::INVALID;
    QMap<QPushButton*,TBOX::REPORT_WIDGET> btn_type_map_;
    RemoteControlWid* remote_contrl_wid_=nullptr;
    ControlConfigForm* control_config_wid_ = nullptr;
};
#endif // TBOXWIDGET_H
