#ifndef FAULTREPORTWIDGET_H
#define FAULTREPORTWIDGET_H

#include <QWidget>
#include "ReportParent.h"
#include "protoBuf/fault.pb.h"

namespace Ui {
class FaultReportWidget;
}

class LocationForm;

class FaultReportWidget : public ReportParent
{
    Q_OBJECT

public:
    explicit FaultReportWidget(QWidget *parent = nullptr);
    ~FaultReportWidget();
    void initUI();
    void initData();
    bool getFault(FaultNS::Fault& fault);
signals:
    void updateFaultSignal();
private slots:
    void on_btn_addError_clicked();
    void slot_deleteItem(int index);

    void on_btn_apply_clicked();

private:
    Ui::FaultReportWidget *ui;
    LocationForm* location_=nullptr;
    FaultNS::Fault fault_ ;
};

#endif // FAULTREPORTWIDGET_H
