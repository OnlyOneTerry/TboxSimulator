#ifndef ALERTREPORTWIDGET_H
#define ALERTREPORTWIDGET_H

#include <QWidget>
#include "ReportParent.h"
#include "protoBuf/alert.pb.h"
#include "protoBuf/location.pb.h"

namespace Ui {
class AlertReportWidget;
}
class LocationForm;

class AlertReportWidget : public ReportParent
{
    Q_OBJECT

public:
    explicit AlertReportWidget(QWidget *parent = nullptr);
    ~AlertReportWidget();
    void initUI();
    void initData();
    void getAlert(AlertNS::Alert& alert);
signals:
    void updateAlertSignal();
private slots:
    void on_btn_addAlert_clicked();
    void slot_deleteItem(int index);
    void on_btn_apply_clicked();

private:
    Ui::AlertReportWidget *ui;
    LocationForm* location_=nullptr;
};

#endif // ALERTREPORTWIDGET_H
