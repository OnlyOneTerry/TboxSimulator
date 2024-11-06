#ifndef EVENTREPORTWIDGET_H
#define EVENTREPORTWIDGET_H

#include <QWidget>
#include"ReportParent.h"
#include "protoBuf/event.pb.h"
#include "protoBuf/location.pb.h"

namespace Ui {
class EventReportWidget;
}

class EventReportWidget : public ReportParent
{
    Q_OBJECT

public:
    explicit EventReportWidget(QWidget *parent = nullptr);
    ~EventReportWidget();
    void initUI();
    void initData();
    void clearContentLayout();
    void getEvent(EventNS::Event& event);
    void updateApplyBtnEnableStatus();
signals:
    void updateEventSignal();
public slots:
    void slotShowCurrentContent(int currentIndex);
    void slot_deleteItem(int index);

    void on_btn_addEvent_clicked();

    void on_btn_apply_clicked();
private:
    Ui::EventReportWidget *ui;
    EventNS::Event data_event_;
};

#endif // EVENTREPORTWIDGET_H
